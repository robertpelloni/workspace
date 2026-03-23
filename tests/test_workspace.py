import os
import unittest

class TestWorkspaceIntegrity(unittest.TestCase):

    def test_critical_submodules_exist(self):
        """Verify that all critical submodules are cloned and present."""
        critical_submodules = [
            'bobui', 'bobfilez', 'borg', 'f-zerox', 'MarbleBlast', 'supersaber',
            'antigravity-autopilot', 'jules-autopilot'
        ]
        for submodule in critical_submodules:
            self.assertTrue(os.path.exists(submodule) and os.path.isdir(submodule), f"Submodule {submodule} is missing")

    def test_build_scripts_exist(self):
        """Verify that our orchestration scripts are intact."""
        scripts = ['build_all.py', 'scripts/update_repos_v6.py', 'scripts/generate_submodule_dashboard.py']
        for script in scripts:
            self.assertTrue(os.path.exists(script), f"Crucial script {script} is missing")

    def test_gitmodules_validity(self):
        """Check that .gitmodules is readable and contains expected paths."""
        self.assertTrue(os.path.exists('.gitmodules'), ".gitmodules is missing")
        with open('.gitmodules', 'r', encoding='utf-8') as f:
            content = f.read()
            self.assertIn('path = borg', content, "borg is not in .gitmodules")
            self.assertIn('path = f-zerox', content, "f-zerox is not in .gitmodules")

if __name__ == '__main__':
    unittest.main()
