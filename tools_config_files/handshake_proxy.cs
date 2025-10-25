using System;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

// HandshakeProxy: emits a minimal MCP header immediately, then execs the real server and
// bridges STDIN/STDOUT/STDERR transparently.
// Usage:
//   handshake_proxy.exe "C:\Path\to\server.exe" arg1 arg2 ...
// Design notes:
// - Writes ONLY "Content-Length: 0\r\n\r\n" to STDOUT at start (no other stdout preamble).
// - Then starts target server with redirected stdio and pumps bytes both directions.
// - Exits with child's exit code.
// - Any diagnostics are written to STDERR to avoid corrupting MCP streams.

class Program
{
    static async Task<int> Main(string[] args)
    {
        if (args.Length < 1)
        {
            Console.Error.WriteLine("Usage: handshake_proxy.exe <targetExe> [args...]");
            return 64; // EX_USAGE
        }

        string targetExe = args[0];
        string targetArgs = BuildArgs(args, 1);

        // 1) Emit minimal MCP header immediately to wake Codex reader
        try
        {
            var header = Encoding.ASCII.GetBytes("Content-Length: 0\r\n\r\n");
            await Console.OpenStandardOutput().WriteAsync(header, 0, header.Length);
            await Console.Out.FlushAsync();
        }
        catch (Exception ex)
        {
            Console.Error.WriteLine("Failed to write MCP header: " + ex.Message);
            // Continue anyway; best-effort wake
        }

        // 2) Start child process with fully redirected stdio
        var psi = new ProcessStartInfo
        {
            FileName = targetExe,
            Arguments = targetArgs,
            UseShellExecute = false,
            RedirectStandardInput = true,
            RedirectStandardOutput = true,
            RedirectStandardError = true,
            CreateNoWindow = true,
        };

        // Best-effort working directory: current directory
        try { psi.WorkingDirectory = Environment.CurrentDirectory; } catch { }

        Process child;
        try
        {
            child = new Process { StartInfo = psi, EnableRaisingEvents = true };
            if (!child.Start())
            {
                Console.Error.WriteLine("Failed to start target process.");
                return 127;
            }
        }
        catch (Exception ex)
        {
            Console.Error.WriteLine("Error starting target: " + ex.Message);
            return 127;
        }

        // 3) Bridge streams
        var stdinToChild = PumpAsync(Console.OpenStandardInput(), child.StandardInput.BaseStream, suppressErrors: true);
        var childOutToStdout = PumpAsync(child.StandardOutput.BaseStream, Console.OpenStandardOutput(), suppressErrors: true);
        var childErrToStderr = PumpAsync(child.StandardError.BaseStream, Console.OpenStandardError(), suppressErrors: true);

        // 4) Wait for child to exit
        try
        {
            await Task.WhenAll(WaitForExitAsync(child), stdinToChild, childOutToStdout, childErrToStderr);
        }
        catch
        {
            // ignore aggregate errors from pumps on shutdown
        }

        int code = 0;
        try { code = child.ExitCode; } catch { code = 1; }

        return code;
    }

    static string BuildArgs(string[] args, int start)
    {
        if (start >= args.Length) return string.Empty;
        var sb = new StringBuilder();
        for (int i = start; i < args.Length; i++)
        {
            if (i > start) sb.Append(' ');
            sb.Append(QuoteArg(args[i]));
        }
        return sb.ToString();
    }

    static string QuoteArg(string s)
    {
        // Basic Windows quoting: wrap in quotes if space or special chars; escape embedded quotes by doubling.
        if (string.IsNullOrEmpty(s)) return "\"\"";
        if (s.IndexOfAny(new[] { ' ', '\t', '"', '&', '|', '<', '>', '^' }) >= 0)
        {
            return "\"" + s.Replace("\"", "\"\"") + "\"";
        }
        return s;
    }

    static async Task PumpAsync(Stream from, Stream to, bool suppressErrors)
    {
        var buf = new byte[8192];
        try
        {
            while (true)
            {
                int n = await from.ReadAsync(buf, 0, buf.Length);
                if (n <= 0) break;
                await to.WriteAsync(buf, 0, n);
                await to.FlushAsync();
            }
        }
        catch
        {
            if (!suppressErrors) throw;
        }
        finally
        {
            try { to.Flush(); } catch { }
            // Do not close stdout/stderr; allow consumer to control their lifecycle.
        }
    }

    static Task WaitForExitAsync(Process p)
    {
        var tcs = new TaskCompletionSource<bool>(TaskCreationOptions.RunContinuationsAsynchronously);
        try
        {
            if (p.HasExited)
            {
                tcs.SetResult(true);
            }
            else
            {
                p.Exited += (s, e) => tcs.TrySetResult(true);
            }
        }
        catch
        {
            tcs.TrySetResult(true);
        }
        return tcs.Task;
    }
}