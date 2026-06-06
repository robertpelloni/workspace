import os
import sqlite3
import subprocess
import unittest
import json

def run_cmd(cmd, cwd=None):
    try:
        res = subprocess.run(cmd, cwd=cwd, shell=True, capture_output=True, text=True, encoding='utf-8', errors='ignore')
        return res.stdout.strip()
    except:
        return ""

class TestWorkspaceIntegrity(unittest.TestCase):

    def test_critical_submodules_exist(self):
        """Verify that all critical submodules are cloned and present."""
        critical_submodules = [
            'bobui', 'bobfilez', 'borg', 'f-zerox', 'MarbleBlast', 'supersaber',
            'antigravity-autopilot', 'jules-autopilot', 'Maestro'
        ]
        for submodule in critical_submodules:
            self.assertTrue(os.path.exists(submodule) and os.path.isdir(submodule), f"Submodule {submodule} is missing")

    def test_build_scripts_exist(self):
        """Verify that our orchestration scripts are intact."""
        scripts = [
            'build_all.py', 
            'scripts/update_repos_v6.py', 
            'scripts/generate_advanced_dashboard.py',
            'scripts/prune_broken_submodules.py',
            'scripts/workspace_indexer.py',
            'scripts/search_workspace.py'
        ]
        for script in scripts:
            self.assertTrue(os.path.exists(script), f"Crucial script {script} is missing")

    def test_gitmodules_validity(self):
        """Check that .gitmodules is readable and contains expected paths."""
        self.assertTrue(os.path.exists('.gitmodules'), ".gitmodules is missing")
        with open('.gitmodules', 'r', encoding='utf-8') as f:
            content = f.read()
            self.assertIn('path = borg', content, "borg is not in .gitmodules")
            self.assertIn('path = Maestro', content, "Maestro is not in .gitmodules")

    def test_maestro_remote(self):
        """Verify Maestro remote is correctly set to robertpelloni/Maestro."""
        remote_url = run_cmd('git config --file .gitmodules --get submodule.Maestro.url')
        self.assertIn('robertpelloni/Maestro', remote_url, f"Maestro remote URL is incorrect: {remote_url}")
        
        # Also check the actual remote in the submodule
        if os.path.exists('Maestro/.git'):
            sub_remote = run_cmd('git -C Maestro remote get-url origin')
            self.assertIn('robertpelloni/Maestro', sub_remote, f"Maestro submodule remote is incorrect: {sub_remote}")

    def test_workspace_index_integrity(self):
        """Check if the search index exists and has data."""
        db_path = 'workspace_index.db'
        self.assertTrue(os.path.exists(db_path), "Search index database is missing")
        
        conn = sqlite3.connect(db_path)
        cursor = conn.cursor()
        try:
            cursor.execute("SELECT count(*) FROM files_metadata")
            count = cursor.fetchone()[0]
            self.assertGreater(count, 0, "Search index 'files_metadata' table is empty")            
            cursor.execute("SELECT count(*) FROM files_fts")
            fts_count = cursor.fetchone()[0]
            self.assertGreater(fts_count, 0, "FTS index is empty")
        finally:
            conn.close()

    def test_health_metadata_consistency(self):
        """Ensure workspace health metadata refers to existing projects."""
        self.assertTrue(os.path.exists('workspace_health.json'))
        with open('workspace_health.json', 'r') as f:
            health = json.load(f)
            for project in health:
                if project == "ROOT": continue
                # Handle slash in names like bobmani/bobmania
                path = project
                self.assertTrue(os.path.exists(path), f"Project {project} in health report does not exist on disk")

if __name__ == '__main__':
    unittest.main()
