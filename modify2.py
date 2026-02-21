with open('update_repos_v5.py', 'r', encoding='utf-8') as f:
    text = f.read()

text = text.replace('f"git merge {branch} --allow-unrelated-histories -X ours -m "Merge {branch} into {default_branch}"", cwd, ignore_errors=True)', 'f"git merge {branch} --allow-unrelated-histories -X ours -m 'Merge {branch} into {default_branch}'", cwd, ignore_errors=True)')

with open('update_repos_v5.py', 'w', encoding='utf-8') as f:
    f.write(text)
