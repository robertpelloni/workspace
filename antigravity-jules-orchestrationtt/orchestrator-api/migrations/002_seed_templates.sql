-- migrations/002_seed_templates.sql

INSERT INTO workflow_templates (name, description, definition_json) VALUES
(
  'dependency-update',
  'Weekly automated dependency maintenance',
  '{
    "name": "Dependency Update",
    "trigger": {
      "type": "scheduled",
      "cron": "0 2 * * 1",
      "condition": "outdated_dependencies_detected"
    },
    "task": {
      "repo": "{{repo_name}}",
      "title": "Weekly dependency update",
      "description": "Update all non-breaking dependencies. Run full test suite. Update CHANGELOG.md with changes.",
      "labels": ["dependencies", "automated"],
      "approval_required": false,
      "scope": ["package.json", "requirements.txt", "go.mod", "Cargo.toml"],
      "safety_checks": ["tests_pass", "no_breaking_changes", "security_audit_clean"]
    },
    "post_actions": [
      {"type": "notify", "target": "slack", "channel": "#deployments"},
      {"type": "github_review_request", "reviewers": ["@scarmonit-bot"]}
    ]
  }'::jsonb
),
(
  'bugfix-from-issue',
  'Automated bugfix triggered by issue label',
  '{
    "name": "Automated Bugfix",
    "trigger": {
      "type": "github_webhook",
      "event": "issue_labeled",
      "label": "bug-auto"
    },
    "task": {
      "repo": "{{repo_name}}",
      "title": "Fix: {{issue_title}}",
      "description": "{{issue_body}}\n\nReproduce the issue, identify root cause, implement fix, add regression test.",
      "labels": ["bugfix", "automated"],
      "approval_required": true,
      "max_files_changed": 5,
      "safety_checks": ["tests_pass", "no_new_warnings"]
    },
    "post_actions": [
      {"type": "github_comment", "message": "Jules has created a fix PR. Plan: {{plan_summary}}"},
      {"type": "link_issue", "issue_number": "{{trigger_issue_number}}"}
    ]
  }'::jsonb
),
(
  'feature-implementation',
  'Feature implementation from issue comments',
  '{
    "name": "Feature Implementation",
    "trigger": {
      "type": "github_webhook",
      "event": "issue_comment",
      "pattern": "@jules implement"
    },
    "task": {
      "repo": "{{repo_name}}",
      "title": "Feature: {{issue_title}}",
      "description": "{{issue_body}}\n\nImplement the feature according to spec. Add unit tests. Update API documentation if endpoints change.",
      "labels": ["feature", "automated"],
      "approval_required": true,
      "scope": ["src/", "tests/", "docs/api/"],
      "safety_checks": ["tests_pass", "coverage_maintained", "api_docs_updated"]
    },
    "pre_actions": [
      {"type": "notify", "target": "slack", "message": "Starting feature implementation: {{issue_title}}"}
    ],
    "post_actions": [
      {"type": "github_review_request", "reviewers": ["{{issue_author}}"]},
      {"type": "deploy_preview", "service": "render", "environment": "staging"}
    ]
  }'::jsonb
),
(
  'security-patch',
  'High-priority security vulnerability patching',
  '{
    "name": "Security Patch",
    "trigger": {
      "type": "webhook",
      "source": "security_scanner",
      "severity": ["high", "critical"]
    },
    "task": {
      "repo": "{{repo_name}}",
      "title": "Security: {{vulnerability_id}}",
      "description": "Patch vulnerability: {{vulnerability_description}}\n\nCVE: {{cve_id}}\nAffected: {{affected_package}}@{{version}}\n\nUpgrade to safe version and verify no breaking changes.",
      "labels": ["security", "automated", "priority-high"],
      "approval_required": false,
      "priority": "high",
      "timeout_minutes": 30,
      "safety_checks": ["tests_pass", "vulnerability_resolved", "no_new_vulns"]
    },
    "post_actions": [
      {"type": "notify", "target": "pagerduty", "severity": "warning"},
      {"type": "github_auto_merge", "conditions": ["all_checks_pass", "no_conflicts"]},
      {"type": "deploy", "target": "production", "strategy": "canary"}
    ]
  }'::jsonb
),
(
  'documentation-sync',
  'Automatic documentation synchronization',
  '{
    "name": "Documentation Sync",
    "trigger": {
      "type": "github_webhook",
      "event": "push",
      "branch": "main",
      "path_filter": ["src/**/*.ts", "src/**/*.go", "src/**/*.py"]
    },
    "task": {
      "repo": "{{repo_name}}",
      "title": "Docs: Update for {{commit_sha_short}}",
      "description": "Sync documentation with code changes from {{commit_message}}\n\nUpdate JSDoc/docstrings, README examples, and API reference. Generate OpenAPI spec if endpoints changed.",
      "labels": ["documentation", "automated"],
      "approval_required": false,
      "scope": ["docs/", "README.md", "*.md"],
      "safety_checks": ["links_valid", "examples_tested"]
    },
    "post_actions": [
      {"type": "deploy_docs", "target": "agent.scarmonit.com/docs"},
      {"type": "github_comment", "target": "commit", "message": "Documentation updated automatically"}
    ]
  }'::jsonb
);
