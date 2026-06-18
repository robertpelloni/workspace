import os
import sys

def add_to_startup():
    """Adds the application to Windows startup via the registry."""
    if sys.platform != 'win32':
        print("Startup integration only supported on Windows.")
        return

    import winreg
    key_path = r"Software\Microsoft\Windows\CurrentVersion\Run"
    app_name = "FreeLLM"
    exe_path = os.path.realpath(sys.executable if getattr(sys, 'frozen', False) else sys.argv[0])

    try:
        key = winreg.OpenKey(winreg.HKEY_CURRENT_USER, key_path, 0, winreg.KEY_SET_VALUE)
        winreg.SetValueEx(key, app_name, 0, winreg.REG_SZ, exe_path)
        winreg.CloseKey(key)
        print(f"Added {app_name} to startup: {exe_path}")
    except Exception as e:
        print(f"Failed to add to startup: {e}")

def remove_from_startup():
    """Removes the application from Windows startup."""
    if sys.platform != 'win32':
        return

    import winreg
    key_path = r"Software\Microsoft\Windows\CurrentVersion\Run"
    app_name = "FreeLLM"

    try:
        key = winreg.OpenKey(winreg.HKEY_CURRENT_USER, key_path, 0, winreg.KEY_SET_VALUE)
        winreg.DeleteValue(key, app_name)
        winreg.CloseKey(key)
        print(f"Removed {app_name} from startup.")
    except FileNotFoundError:
        pass
    except Exception as e:
        print(f"Failed to remove from startup: {e}")

if __name__ == "__main__":
    # Test (will only work on Windows)
    add_to_startup()
