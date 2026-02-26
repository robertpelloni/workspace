-- migrations/001_initial_schema.sql

-- Enable UUID extension
CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

-- Workflow templates table
CREATE TABLE workflow_templates (
  id SERIAL PRIMARY KEY,
  name VARCHAR(255) UNIQUE NOT NULL,
  description TEXT,
  definition_json JSONB NOT NULL,
  enabled BOOLEAN DEFAULT true,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Workflow instances table with enhanced tracking
CREATE TABLE workflow_instances (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  template_id INTEGER REFERENCES workflow_templates(id),
  status VARCHAR(50) NOT NULL,
  context_json JSONB NOT NULL,
  error_message TEXT,
  retry_count INTEGER DEFAULT 0,
  started_at TIMESTAMP,
  completed_at TIMESTAMP,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  
  CONSTRAINT valid_status CHECK (status IN (
    'pending', 'running', 'awaiting_approval', 
    'executing', 'completed', 'failed', 'cancelled'
  ))
);

-- Jules tasks table
CREATE TABLE jules_tasks (
  id SERIAL PRIMARY KEY,
  workflow_instance_id UUID REFERENCES workflow_instances(id) ON DELETE CASCADE,
  jules_task_id VARCHAR(255) NOT NULL UNIQUE,
  status VARCHAR(50) NOT NULL,
  plan_summary TEXT,
  pr_url TEXT,
  pr_number INTEGER,
  files_changed INTEGER,
  lines_added INTEGER,
  lines_removed INTEGER,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Action log for audit trail
CREATE TABLE action_log (
  id SERIAL PRIMARY KEY,
  workflow_instance_id UUID REFERENCES workflow_instances(id) ON DELETE CASCADE,
  action_type VARCHAR(100) NOT NULL,
  action_config JSONB,
  result JSONB,
  success BOOLEAN,
  error_message TEXT,
  duration_ms INTEGER,
  timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Webhook events for debugging
CREATE TABLE webhook_events (
  id SERIAL PRIMARY KEY,
  source VARCHAR(50) NOT NULL,
  event_type VARCHAR(100) NOT NULL,
  payload JSONB NOT NULL,
  processed BOOLEAN DEFAULT false,
  workflow_instance_id UUID REFERENCES workflow_instances(id),
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Approval queue
CREATE TABLE approval_queue (
  id SERIAL PRIMARY KEY,
  workflow_instance_id UUID REFERENCES workflow_instances(id) ON DELETE CASCADE,
  plan_summary TEXT NOT NULL,
  estimated_files_changed INTEGER,
  risk_level VARCHAR(20),
  requested_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  approved_by VARCHAR(255),
  approved_at TIMESTAMP,
  decision VARCHAR(20),
  notes TEXT,
  
  CONSTRAINT valid_decision CHECK (decision IN ('approved', 'rejected', null))
);

-- Performance indexes
CREATE INDEX idx_workflow_status ON workflow_instances(status);
CREATE INDEX idx_workflow_created ON workflow_instances(created_at DESC);
CREATE INDEX idx_workflow_template ON workflow_instances(template_id);
CREATE INDEX idx_jules_task_status ON jules_tasks(status);
CREATE INDEX idx_jules_workflow ON jules_tasks(workflow_instance_id);
CREATE INDEX idx_webhook_processed ON webhook_events(processed, created_at);
CREATE INDEX idx_approval_pending ON approval_queue(decision) WHERE decision IS NULL;

-- Trigger to update updated_at timestamp
CREATE OR REPLACE FUNCTION update_updated_at_column()
RETURNS TRIGGER AS $$
BEGIN
    NEW.updated_at = CURRENT_TIMESTAMP;
    RETURN NEW;
END;
$$ language 'plpgsql';

CREATE TRIGGER update_workflow_instances_updated_at BEFORE UPDATE ON workflow_instances
FOR EACH ROW EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_jules_tasks_updated_at BEFORE UPDATE ON jules_tasks
FOR EACH ROW EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_workflow_templates_updated_at BEFORE UPDATE ON workflow_templates
FOR EACH ROW EXECUTE FUNCTION update_updated_at_column();
