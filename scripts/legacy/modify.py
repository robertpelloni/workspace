import sys

with open('update_repos_v3.py', 'r', encoding='utf-8') as f:
    content = f.read()

content = content.replace('processed_repos_v3.txt', 'processed_repos_v4.txt')
content = content.replace('failed_repos_v3.log', 'failed_repos_v4.log')

# Replace abort with exit
content = content.replace('run_command("git merge --abort", cwd, ignore_errors=True)', 'sys.exit(1)')

push_logic_start = '# 5. Push to Origin'

remote_merge_logic = '''# 5. Merge remote feature branches for robertpelloni repos
    remotes_v = run_command("git remote -v", cwd, ignore_errors=True)
    if remotes_v and "robertpelloni" in remotes_v.lower():
        remote_branches_out = run_command("git branch -r", cwd, ignore_errors=True)
        if remote_branches_out:
            for rb in remote_branches_out.split(chr(10)):
                rb = rb.strip()
                if "origin/" in rb and "HEAD" not in rb:
                    branch_name = rb.replace("origin/", "")
                    if branch_name not in [default_branch, "master", "main"] and branch_name not in local_branches:
                        print(f"Attempting to merge remote branch '{rb}' into {default_branch}...")
                        try:
                            merge_res = run_command(f"git merge {rb}", cwd, timeout=120)
                            if merge_res is None:
                                msg = f"Merge failed for {rb}. Stopping script so you can resolve it!"
                                print(msg)
                                log_failure(cwd, msg)
                                sys.exit(1)
                        except:
                            msg = f"Feature merge failed for remote branch {rb}. Stopping script so you can resolve it!"
                            print(msg)
                            log_failure(cwd, msg)
                            sys.exit(1)

    # 6. Push to Origin'''

content = content.replace(push_logic_start, remote_merge_logic)

with open('update_repos_v4.py', 'w', encoding='utf-8') as f:
    f.write(content)
