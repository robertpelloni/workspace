package main

import (
    "fmt"
    "log"
    "net/http"
    "time"

    "gorm.io/driver/sqlite"
    "gorm.io/gorm"
    "gorm.io/gorm/logger"
)

// MemoryChunk represents a vectorized fragment of the repository for RAG
type MemoryChunk struct {
    gorm.Model
    Content    string
    FilePath   string
    Embedding  string // Placeholder for actual vector BLOB
}

// Session represents an overarching AI orchestrator session execution tracking
type Session struct {
    gorm.Model
    Status     string
    Summary    string
    EndTime    *time.Time
}

var DB *gorm.DB

func initDB() {
    var err error
    // Configure SQLite DB using GORM
    DB, err = gorm.Open(sqlite.Open("../borg.db"), &gorm.Config{
        Logger: logger.Default.LogMode(logger.Info),
    })
    if err != nil {
        log.Fatalf("Failed to connect to SQLite database: %v", err)
    }

    // Auto-migrate schema structures into SQLite
    err = DB.AutoMigrate(&MemoryChunk{}, &Session{})
    if err != nil {
        log.Fatalf("Failed to migrate database schemas: %v", err)
    }

    fmt.Println("SQLite database initialized and schemas migrated.")
}

func main() {
    fmt.Println("Jules Autopilot (Go Primary Runtime) initialized.")
    initDB()

    // Manifest endpoint for Borg assimilation
    http.HandleFunc("/api/manifest", func(w http.ResponseWriter, r *http.Request) {
        w.Header().Set("Content-Type", "application/json")
        fmt.Fprintf(w, `{"status": "online", "version": "1.0.1", "capabilities": ["orchestration", "execution", "healing", "rag"]}`)
    })

    // Fleet Summary API
    http.HandleFunc("/api/fleet/summary", func(w http.ResponseWriter, r *http.Request) {
        var activeJobs int64
        DB.Model(&Session{}).Where("status = ?", "ACTIVE").Count(&activeJobs)

        w.Header().Set("Content-Type", "application/json")
        fmt.Fprintf(w, `{"active_jobs": %d, "status": "healthy"}`, activeJobs)
    })

    // Fallback static SPA serving placeholder
    http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
        w.Write([]byte("Jules Autopilot API Server is active."))
    })

    port := "8080"
    fmt.Printf("Server running on port %s\n", port)
    log.Fatal(http.ListenAndServe(":"+port, nil))
}
