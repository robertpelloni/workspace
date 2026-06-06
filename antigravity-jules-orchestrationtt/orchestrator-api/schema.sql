-- orchestrator-api/schema.sql

CREATE TABLE workflow_templates (
  id SERIAL PRIMARY KEY,
  name VARCHAR(255) UNIQUE NOT NULL,
  definition_json JSONB NOT NULL,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE workflow_instances (
  id SERIAL PRIMARY KEY,
  template_id INTEGER REFERENCES workflow_templates(id),
  status VARCHAR(50) NOT NULL,
  context_json JSONB NOT NULL,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE jules_tasks (
  id SERIAL PRIMARY KEY,
  workflow_instance_id INTEGER REFERENCES workflow_instances(id),
  jules_task_id VARCHAR(255) NOT NULL,
  status VARCHAR(50) NOT NULL,
  plan_summary TEXT,
  pr_url TEXT,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE action_log (
  id SERIAL PRIMARY KEY,
  workflow_instance_id INTEGER REFERENCES workflow_instances(id),
  action_type VARCHAR(100) NOT NULL,
  result TEXT,
  timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_workflow_status ON workflow_instances(status);
CREATE INDEX idx_jules_task_status ON jules_tasks(status);
CREATE INDEX idx_workflow_created ON workflow_instances(created_at DESC);
