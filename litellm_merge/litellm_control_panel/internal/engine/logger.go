package engine

import (
	"database/sql"
	"fmt"
	"sync"
	"time"

	"github.com/robertpelloni/litellm_control_panel/internal/db"
)

type LogEntry struct {
	Timestamp time.Time `json:"timestamp"`
	Message   string    `json:"message"`
}

type EventLogger struct {
	mu     sync.Mutex
	Logs   []LogEntry
	MaxLen int
	DB     *sql.DB
}

func NewEventLogger(maxLen int, database *sql.DB) *EventLogger {
	return &EventLogger{
		MaxLen: maxLen,
		Logs:   make([]LogEntry, 0),
		DB:     database,
	}
}

func (l *EventLogger) Log(message string) {
	l.mu.Lock()
	defer l.mu.Unlock()

	entry := LogEntry{
		Timestamp: time.Now(),
		Message:   message,
	}
	l.Logs = append(l.Logs, entry)
	if len(l.Logs) > l.MaxLen {
		l.Logs = l.Logs[1:]
	}

	if l.DB != nil {
		db.LogPersistent(l.DB, message)
	}

	fmt.Printf("[%s] %s\n", entry.Timestamp.Format("15:04:05"), message)
}

func (l *EventLogger) GetLogs() []LogEntry {
	l.mu.Lock()
	defer l.mu.Unlock()

	// Return a copy
	res := make([]LogEntry, len(l.Logs))
	copy(res, l.Logs)
	return res
}
