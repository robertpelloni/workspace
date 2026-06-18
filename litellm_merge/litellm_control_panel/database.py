import sqlite3
import datetime

DB_NAME = "provider_metrics.db"


def init_db():
    """Initializes the SQLite database with the required schema."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()

    # Providers table
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS providers (
            provider_name TEXT PRIMARY KEY,
            is_free_provider BOOLEAN DEFAULT 1,
            consecutive_empty_cycles INTEGER DEFAULT 0,
            last_checked TIMESTAMP
        )
    """)

    # Model history table — enhanced with reliability tracking
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS model_history (
            model_id TEXT PRIMARY KEY,
            provider_name TEXT,
            manually_skipped BOOLEAN DEFAULT 0,
            is_blacklisted BOOLEAN DEFAULT 0,
            skip_expiry TIMESTAMP,
            failure_count INTEGER DEFAULT 0,
            retry_after TIMESTAMP,
            avg_latency REAL DEFAULT 0,
            min_latency REAL DEFAULT 999,
            max_latency REAL DEFAULT 0,
            p50_latency REAL DEFAULT 0,
            p95_latency REAL DEFAULT 0,
            last_success TIMESTAMP,
            last_failure TIMESTAMP,
            total_probes INTEGER DEFAULT 0,
            total_successes INTEGER DEFAULT 0,
            total_failures INTEGER DEFAULT 0,
            consecutive_successes INTEGER DEFAULT 0,
            consecutive_failures INTEGER DEFAULT 0,
            uptime_pct REAL DEFAULT 0,
            score_avg REAL DEFAULT 0,
            score_best REAL DEFAULT 0,
            context_length INTEGER DEFAULT 0,
            parameters INTEGER DEFAULT 0,
            first_seen TIMESTAMP,
            FOREIGN KEY (provider_name) REFERENCES providers(provider_name)
        )
    """)

    # Probe history — individual probe results over time
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS probe_history (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            model_id TEXT NOT NULL,
            provider_name TEXT NOT NULL,
            timestamp TIMESTAMP NOT NULL,
            latency REAL,
            success BOOLEAN NOT NULL,
            error_code INTEGER,
            error_message TEXT,
            score REAL DEFAULT 0,
            context_length INTEGER DEFAULT 0,
            parameters INTEGER DEFAULT 0
        )
    """)

    # Usage table
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS usage (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            model_id TEXT,
            timestamp TIMESTAMP,
            prompt_tokens INTEGER,
            completion_tokens INTEGER,
            cost_saved REAL DEFAULT 0
        )
    """)

    # Model Pricing table
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS model_pricing (
            model_id TEXT PRIMARY KEY,
            provider TEXT,
            prompt_price REAL,
            completion_price REAL,
            last_updated TIMESTAMP
        )
    """)

    # Activity Log table
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS activity_log (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            timestamp TIMESTAMP NOT NULL,
            event_type TEXT NOT NULL,
            model_id TEXT,
            details TEXT
        )
    """)

    # Stability Metrics table
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS stability_metrics (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            timestamp TIMESTAMP NOT NULL,
            qpm REAL,
            tps REAL
        )
    """)

    # Create indexes for fast queries
    cursor.execute(
        "CREATE INDEX IF NOT EXISTS idx_probe_model ON probe_history(model_id)"
    )
    cursor.execute(
        "CREATE INDEX IF NOT EXISTS idx_probe_time ON probe_history(timestamp)"
    )
    cursor.execute(
        "CREATE INDEX IF NOT EXISTS idx_probe_success ON probe_history(success)"
    )

    # Schema Migration: Ensure cost_saved exists in usage table
    try:
        cursor.execute("ALTER TABLE usage ADD COLUMN cost_saved REAL DEFAULT 0")
    except sqlite3.OperationalError:
        # Column already exists
        pass

    conn.commit()
    conn.close()


# ── Model Probe Recording ──────────────────────────────────────────────────


def record_probe(
    model_id,
    provider_name,
    latency,
    success,
    error_code=None,
    error_message=None,
    score=0,
    context_length=0,
    parameters=0,
):
    """Record a single probe result and update aggregate model stats.
    This is the single entry point for all probe data — success or failure.
    """
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    now = datetime.datetime.now()

    # 1. Insert into probe_history
    cursor.execute(
        """
        INSERT INTO probe_history (model_id, provider_name, timestamp, latency, success,
                                    error_code, error_message, score, context_length, parameters)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    """,
        (
            model_id,
            provider_name,
            now,
            latency,
            success,
            error_code,
            error_message,
            score,
            context_length,
            parameters,
        ),
    )

    # 2. Ensure provider exists
    cursor.execute(
        "INSERT OR IGNORE INTO providers (provider_name) VALUES (?)", (provider_name,)
    )

    # 3. Ensure model_history row exists
    cursor.execute(
        """
        INSERT OR IGNORE INTO model_history (model_id, provider_name, first_seen)
        VALUES (?, ?, ?)
    """,
        (model_id, provider_name, now),
    )

    # 4. Update model_history aggregates
    if success:
        # Get current stats for running calculations
        cursor.execute(
            """
            SELECT avg_latency, min_latency, max_latency, total_probes,
                   total_successes, consecutive_successes, p50_latency, parameters
            FROM model_history WHERE model_id = ?
        """,
            (model_id,),
        )
        row = cursor.fetchone()
        if row:
            curr_avg = row[0] if row[0] else latency
            curr_min = row[1] if row[1] and row[1] < 999 else latency
            curr_max = row[2] if row[2] else 0
            total = (row[3] or 0) + 1
            successes = (row[4] or 0) + 1
            consec_succ = (row[5] or 0) + 1
            curr_p50 = row[6] if row[6] else latency
            stored_params = row[7] if row[7] else 0
        else:
            curr_avg = latency
            curr_min = latency
            curr_max = latency
            total = 1
            successes = 1
            consec_succ = 1
            curr_p50 = latency
            stored_params = 0

        new_avg = curr_avg * 0.7 + latency * 0.3  # EMA
        new_min = min(curr_min, latency)
        new_max = max(curr_max, latency)
        new_params = parameters if parameters > 0 else stored_params

        # Compute p50 from recent probes (last 20)
        cursor.execute(
            """
            SELECT latency FROM probe_history
            WHERE model_id = ? AND success = 1 AND latency IS NOT NULL
            ORDER BY timestamp DESC LIMIT 20
        """,
            (model_id,),
        )
        recent = [r[0] for r in cursor.fetchall()]
        if recent:
            recent.sort()
            new_p50 = recent[len(recent) // 2]
        else:
            new_p50 = latency

        # Uptime percentage
        cursor.execute(
            """
            SELECT COUNT(*) FROM probe_history
            WHERE model_id = ? AND timestamp > ?
        """,
            (model_id, now - datetime.timedelta(days=7)),
        )
        total_recent = cursor.fetchone()[0]
        cursor.execute(
            """
            SELECT COUNT(*) FROM probe_history
            WHERE model_id = ? AND success = 1 AND timestamp > ?
        """,
            (model_id, now - datetime.timedelta(days=7)),
        )
        success_recent = cursor.fetchone()[0]
        uptime = (success_recent / total_recent * 100) if total_recent > 0 else 100

        # Score tracking
        cursor.execute(
            "SELECT score_best FROM model_history WHERE model_id = ?", (model_id,)
        )
        best_score_row = cursor.fetchone()
        best_score = best_score_row[0] if best_score_row and best_score_row[0] else 0
        new_best_score = max(best_score, score)
        new_avg_score = 0
        if score > 0:
            cursor.execute(
                """
                SELECT AVG(score) FROM probe_history
                WHERE model_id = ? AND score > 0
                ORDER BY timestamp DESC LIMIT 20
            """,
                (model_id,),
            )
            avg_row = cursor.fetchone()
            new_avg_score = avg_row[0] if avg_row and avg_row[0] else score

        cursor.execute(
            """
            UPDATE model_history SET
                avg_latency = ?,
                min_latency = ?,
                max_latency = ?,
                p50_latency = ?,
                failure_count = 0,
                consecutive_successes = ?,
                consecutive_failures = 0,
                total_probes = ?,
                total_successes = ?,
                last_success = ?,
                uptime_pct = ?,
                score_avg = ?,
                score_best = ?,
                context_length = ?,
                parameters = ?,
                retry_after = NULL
            WHERE model_id = ?
        """,
            (
                new_avg,
                new_min,
                new_max,
                new_p50,
                consec_succ,
                total,
                successes,
                now,
                uptime,
                new_avg_score,
                new_best_score,
                context_length,
                new_params,
                model_id,
            ),
        )
    else:
        # Failure case
        cursor.execute(
            """
            SELECT failure_count, total_probes, total_failures, consecutive_failures
            FROM model_history WHERE model_id = ?
        """,
            (model_id,),
        )
        row = cursor.fetchone()
        fail_count = (row[0] if row else 0) + 1
        total = (row[1] if row else 0) + 1
        total_fails = (row[2] if row else 0) + 1
        consec_fails = (row[3] if row else 0) + 1

        retry_after = None
        if fail_count >= 3:
            retry_after = now + datetime.timedelta(hours=2)

        # Uptime percentage
        cursor.execute(
            """
            SELECT COUNT(*) FROM probe_history
            WHERE model_id = ? AND timestamp > ?
        """,
            (model_id, now - datetime.timedelta(days=7)),
        )
        total_recent = cursor.fetchone()[0]
        cursor.execute(
            """
            SELECT COUNT(*) FROM probe_history
            WHERE model_id = ? AND success = 1 AND timestamp > ?
        """,
            (model_id, now - datetime.timedelta(days=7)),
        )
        success_recent = cursor.fetchone()[0]
        uptime = (success_recent / total_recent * 100) if total_recent > 0 else 0

        cursor.execute(
            """
            UPDATE model_history SET
                failure_count = ?,
                consecutive_successes = 0,
                consecutive_failures = ?,
                total_probes = ?,
                total_failures = ?,
                last_failure = ?,
                retry_after = ?,
                uptime_pct = ?
            WHERE model_id = ?
        """,
            (
                fail_count,
                consec_fails,
                total,
                total_fails,
                now,
                retry_after,
                uptime,
                model_id,
            ),
        )

    conn.commit()
    conn.close()


# ── Legacy wrappers (for backward compat) ──────────────────────────────────


def update_model_latency(model_id, provider_name, latency):
    """Legacy: records a successful probe."""
    record_probe(model_id, provider_name, latency, success=True)


def handle_test_failure(model_id, provider_name):
    """Legacy: records a failed probe."""
    record_probe(model_id, provider_name, latency=None, success=False)


# ── Query Functions ─────────────────────────────────────────────────────────


def get_candidate_models():
    """Fetches models that are not manually skipped, haven't crashed repeatedly,
    and belong to active free providers."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    query = """
        SELECT model_id, provider_name FROM model_history
        WHERE manually_skipped = 0
          AND failure_count < 3
          AND provider_name IN (
              SELECT provider_name FROM providers WHERE is_free_provider = 1
          )
    """
    cursor.execute(query)
    candidates = cursor.fetchall()
    conn.close()
    return candidates


def get_model_stats(model_id):
    """Returns full reliability stats for a model."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute(
        """
        SELECT model_id, provider_name, avg_latency, min_latency, max_latency,
               p50_latency, total_probes, total_successes, total_failures,
               consecutive_successes, consecutive_failures, uptime_pct,
               score_avg, score_best, last_success, last_failure,
               parameters, context_length
        FROM model_history WHERE model_id = ?
    """,
        (model_id,),
    )
    row = cursor.fetchone()
    conn.close()
    if not row:
        return None
    return {
        "id": row[0],
        "provider": row[1],
        "avg_latency": row[2],
        "min_latency": row[3],
        "max_latency": row[4],
        "p50_latency": row[5],
        "total_probes": row[6],
        "successes": row[7],
        "failures": row[8],
        "consec_successes": row[9],
        "consec_failures": row[10],
        "uptime_pct": row[11],
        "score_avg": row[12],
        "score_best": row[13],
        "last_success": row[14],
        "last_failure": row[15],
        "parameters": row[16],
        "context_length": row[17],
    }


def get_model_probe_history(model_id, limit=50):
    """Returns recent probe history for a model."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute(
        """
        SELECT timestamp, latency, success, error_code, score
        FROM probe_history
        WHERE model_id = ?
        ORDER BY timestamp DESC LIMIT ?
    """,
        (model_id, limit),
    )
    rows = cursor.fetchall()
    conn.close()
    return [
        {
            "timestamp": r[0],
            "latency": r[1],
            "success": r[2],
            "error_code": r[3],
            "score": r[4],
        }
        for r in rows
    ]


def get_leaderboard(sort_by="score_best", limit=20):
    """Returns top models sorted by a reliability metric.

    sort_by options: score_best, score_avg, avg_latency, min_latency,
                     p50_latency, uptime_pct, total_successes
    """
    allowed = {
        "score_best",
        "score_avg",
        "avg_latency",
        "min_latency",
        "p50_latency",
        "uptime_pct",
        "total_successes",
    }
    if sort_by not in allowed:
        sort_by = "score_best"

    ascending = sort_by in {"avg_latency", "p50_latency", "min_latency"}

    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    query = f"""
        SELECT model_id, provider_name, avg_latency, p50_latency, min_latency,
               total_probes, total_successes, total_failures, uptime_pct,
               score_avg, score_best, parameters, context_length,
               consecutive_successes, last_success
        FROM model_history
        WHERE manually_skipped = 0 AND is_blacklisted = 0
          AND total_probes > 0
        ORDER BY {sort_by} {"ASC" if ascending else "DESC"}
        LIMIT ?
    """
    cursor.execute(query, (limit,))
    rows = cursor.fetchall()
    conn.close()

    results = []
    for r in rows:
        results.append(
            {
                "id": r[0],
                "provider": r[1],
                "avg_latency": r[2],
                "p50_latency": r[3],
                "min_latency": r[4],
                "total_probes": r[5],
                "successes": r[6],
                "failures": r[7],
                "uptime_pct": r[8],
                "score_avg": r[9],
                "score_best": r[10],
                "parameters": r[11],
                "context_length": r[12],
                "consec_successes": r[13],
                "last_success": r[14],
            }
        )
    return results


def get_reliability_trend(model_id, days=7):
    """Returns daily reliability summary for a model over the past N days."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    since = datetime.datetime.now() - datetime.timedelta(days=days)
    cursor.execute(
        """
        SELECT DATE(timestamp) as day,
               COUNT(*) as total,
               SUM(CASE WHEN success = 1 THEN 1 ELSE 0 END) as successes,
               AVG(CASE WHEN success = 1 AND latency IS NOT NULL THEN latency END) as avg_lat,
               MIN(CASE WHEN success = 1 AND latency IS NOT NULL THEN latency END) as min_lat,
               MAX(CASE WHEN success = 1 AND latency IS NOT NULL THEN latency END) as max_lat
        FROM probe_history
        WHERE model_id = ? AND timestamp > ?
        GROUP BY DATE(timestamp)
        ORDER BY day DESC
    """,
        (model_id, since),
    )
    rows = cursor.fetchall()
    conn.close()
    return [
        {
            "day": r[0],
            "total": r[1],
            "successes": r[2],
            "avg_lat": r[3],
            "min_lat": r[4],
            "max_lat": r[5],
        }
        for r in rows
    ]


def get_last_rankings():
    """Fetches top 10 models from history based on best score and reliability."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    query = """
        SELECT model_id, provider_name, avg_latency, p50_latency,
               score_best, uptime_pct, total_probes, parameters, context_length
        FROM model_history
        WHERE manually_skipped = 0
          AND is_blacklisted = 0
          AND avg_latency > 0
          AND total_probes >= 1
        ORDER BY score_best DESC, uptime_pct DESC, avg_latency ASC
        LIMIT 10
    """
    cursor.execute(query)
    rows = cursor.fetchall()
    conn.close()
    results = []
    for r in rows:
        results.append(
            {
                "id": r[0],
                "provider": r[1],
                "parameters": r[7] if r[7] and r[7] > 0 else 100,
                "latency": r[2] if r[2] else 0,
                "score": r[4] if r[4] else 0,
                "p50_latency": r[3] if r[3] else 0,
                "uptime_pct": r[5] if r[5] else 0,
                "context_length": r[8] if r[8] else 0,
            }
        )
    return results


# ── Manual Overrides ────────────────────────────────────────────────────────


def set_model_skip_status(model_id, skipped=True, duration_hours=24):
    """Manually skip a model for a specified duration."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    expiry = None
    if skipped:
        expiry = datetime.datetime.now() + datetime.timedelta(hours=duration_hours)
    cursor.execute(
        """
        UPDATE model_history SET manually_skipped = ?, skip_expiry = ?
        WHERE model_id = ?
    """,
        (1 if skipped else 0, expiry, model_id),
    )
    conn.commit()
    conn.close()


def set_model_blacklist_status(model_id, blacklisted=True):
    """Permanently blacklist a model."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute(
        "UPDATE model_history SET is_blacklisted = ? WHERE model_id = ?",
        (1 if blacklisted else 0, model_id),
    )
    conn.commit()
    conn.close()


def clear_skip_list():
    """Resets all manual skips."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute("UPDATE model_history SET manually_skipped = 0, skip_expiry = NULL")
    conn.commit()
    conn.close()


def clear_blacklist():
    """Resets all blacklisted models."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute("UPDATE model_history SET is_blacklisted = 0")
    conn.commit()
    conn.close()


# ── Usage Tracking ──────────────────────────────────────────────────────────


def log_usage(model_id, prompt_tokens=0, completion_tokens=0):
    """Logs model usage and calculates estimated cost saved."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()

    # Get current pricing for this model
    cursor.execute(
        "SELECT prompt_price, completion_price FROM model_pricing WHERE model_id = ?",
        (model_id,),
    )
    row = cursor.fetchone()

    cost_saved = 0
    if row:
        pp, cp = row
        # Pricing is typically per 1M tokens in APIs, adjust calculation if needed
        # OpenRouter pricing is already in small decimals (USD per token)
        cost_saved = (prompt_tokens * pp) + (completion_tokens * cp)

    cursor.execute(
        """
        INSERT INTO usage (model_id, timestamp, prompt_tokens, completion_tokens, cost_saved)
        VALUES (?, ?, ?, ?, ?)
    """,
        (
            model_id,
            datetime.datetime.now(),
            prompt_tokens,
            completion_tokens,
            cost_saved,
        ),
    )
    conn.commit()
    conn.close()


def update_model_pricing(model_id, provider, prompt_price, completion_price):
    """Updates the pricing information for a model."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute(
        """
        INSERT INTO model_pricing (model_id, provider, prompt_price, completion_price, last_updated)
        VALUES (?, ?, ?, ?, ?)
        ON CONFLICT(model_id) DO UPDATE SET
            prompt_price = EXCLUDED.prompt_price,
            completion_price = EXCLUDED.completion_price,
            last_updated = EXCLUDED.last_updated
    """,
        (model_id, provider, prompt_price, completion_price, datetime.datetime.now()),
    )
    conn.commit()
    conn.close()


def get_savings_summary():
    """Returns total estimated cost saved and breakdown per model."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()

    cursor.execute("SELECT SUM(cost_saved) FROM usage")
    total = cursor.fetchone()[0] or 0

    cursor.execute("""
        SELECT model_id, SUM(cost_saved), SUM(prompt_tokens + completion_tokens)
        FROM usage
        GROUP BY model_id
        HAVING SUM(cost_saved) > 0
        ORDER BY SUM(cost_saved) DESC
    """)
    breakdown = cursor.fetchall()
    conn.close()
    return total, breakdown


def log_activity(event_type, model_id=None, details=None):
    """Logs an internal system event."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute(
        """
        INSERT INTO activity_log (timestamp, event_type, model_id, details)
        VALUES (?, ?, ?, ?)
    """,
        (datetime.datetime.now(), event_type, model_id, details),
    )
    conn.commit()
    conn.close()


def get_recent_activity(limit=100):
    """Retrieves recent activity logs."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute(
        """
        SELECT timestamp, event_type, model_id, details
        FROM activity_log
        ORDER BY timestamp DESC LIMIT ?
    """,
        (limit,),
    )
    rows = cursor.fetchall()
    conn.close()
    return rows


def get_protocol_health_metrics(hours=24):
    """Aggregates protocol-specific health and execution metrics."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cutoff = datetime.datetime.now() - datetime.timedelta(hours=hours)

    # 1. Error Rate (Health Failure events vs total events)
    cursor.execute("""
        SELECT
            COUNT(*),
            SUM(CASE WHEN event_type = 'Health Check Failure' OR event_type = 'Protocol Error' THEN 1 ELSE 0 END)
        FROM activity_log
        WHERE timestamp > ?
    """, (cutoff,))
    counts = cursor.fetchone()
    total_events = counts[0] or 0
    total_errors = counts[1] or 0
    error_rate = (total_errors / total_events * 100) if total_events > 0 else 0

    # 2. Execution Durations (Sync durations)
    cursor.execute("""
        SELECT details FROM activity_log
        WHERE event_type = 'Protocol Sync' AND timestamp > ?
    """, (cutoff,))
    sync_logs = cursor.fetchall()
    durations = []
    import re
    for row in sync_logs:
        # Expecting details like "Cycle took 12.5s"
        match = re.search(r'took (\d+\.?\d*)s', row[0])
        if match:
            durations.append(float(match.group(1)))

    avg_duration = sum(durations) / len(durations) if durations else 0
    max_duration = max(durations) if durations else 0

    conn.close()
    return {
        "error_rate": error_rate,
        "total_errors": total_errors,
        "avg_sync_duration": avg_duration,
        "max_sync_duration": max_duration,
        "sync_count": len(durations)
    }


def get_performance_summary():
    """Aggregates TTFT and success rates from probe_history."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()

    # 24h average TTFT and success rate
    cutoff = datetime.datetime.now() - datetime.timedelta(hours=24)
    cursor.execute(
        """
        SELECT
            COUNT(*),
            AVG(CASE WHEN success = 1 THEN latency END),
            SUM(CASE WHEN success = 1 THEN 1 ELSE 0 END) * 100.0 / COUNT(*)
        FROM probe_history
        WHERE timestamp > ?
    """,
        (cutoff,),
    )
    summary = cursor.fetchone()

    # Breakdown by provider
    cursor.execute(
        """
        SELECT
            provider_name,
            AVG(latency),
            SUM(CASE WHEN success = 1 THEN 1 ELSE 0 END) * 100.0 / COUNT(*)
        FROM probe_history
        WHERE timestamp > ?
        GROUP BY provider_name
    """,
        (cutoff,),
    )
    provider_breakdown = cursor.fetchall()

    conn.close()
    return {
        "total_probes": summary[0] or 0,
        "avg_ttft": summary[1] or 0,
        "success_rate": summary[2] or 0,
        "providers": provider_breakdown,
    }


def log_stability_metric(qpm, tps):
    """Logs system stability metrics (Load Analysis)."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute("""
        INSERT INTO stability_metrics (timestamp, qpm, tps)
        VALUES (?, ?, ?)
    """, (datetime.datetime.now(), qpm, tps))
    conn.commit()
    conn.close()


def get_load_history(limit=60):
    """Retrieves recent stability metrics for charting."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute("""
        SELECT timestamp, qpm, tps
        FROM stability_metrics
        ORDER BY timestamp DESC LIMIT ?
    """, (limit,))
    rows = cursor.fetchall()
    conn.close()
    return rows


def get_total_usage():
    """Returns total query count and token counts."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute(
        "SELECT COUNT(*), SUM(prompt_tokens), SUM(completion_tokens) FROM usage"
    )
    row = cursor.fetchone()
    conn.close()
    return row if row else (0, 0, 0)


# ── Maintenance ─────────────────────────────────────────────────────────────


def reset_all_stats():
    """Resets provider failures and model histories, but keeps probe_history."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute(
        "UPDATE providers SET consecutive_empty_cycles = 0, is_free_provider = 1"
    )
    cursor.execute("""
        UPDATE model_history SET
            failure_count = 0, retry_after = NULL,
            avg_latency = 0, min_latency = 999, max_latency = 0, p50_latency = 0,
            total_probes = 0, total_successes = 0, total_failures = 0,
            consecutive_successes = 0, consecutive_failures = 0, uptime_pct = 0,
            score_avg = 0, score_best = 0
    """)
    conn.commit()
    conn.close()


def cleanup_old_probes(days=90):
    """Remove probe history older than N days to keep the DB compact."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cutoff = datetime.datetime.now() - datetime.timedelta(days=days)
    cursor.execute("DELETE FROM probe_history WHERE timestamp < ?", (cutoff.isoformat(),))
    deleted = cursor.rowcount
    conn.commit()
    conn.close()
    return deleted


def get_provider_status():
    """Fetches all provider health info."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute("""
        SELECT provider_name, is_free_provider, consecutive_empty_cycles, last_checked
        FROM providers
    """)
    stats = cursor.fetchall()
    conn.close()
    return stats


def update_provider_cycle(provider_name, found_models: bool, has_api_key: bool = True):
    """Updates consecutive empty cycles and flags if provider seems to have no free models.

    If has_api_key is False, we skip the cycle count entirely (a provider without
    credentials can't be expected to return models, so counting empty cycles would
    be a false signal that triggers a death-spiral blacklist).
    """
    if not has_api_key:
        return  # Don't penalize providers that lack credentials
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    if found_models:
        cursor.execute(
            """
            UPDATE providers SET consecutive_empty_cycles = 0, is_free_provider = 1,
                                 last_checked = ?
            WHERE provider_name = ?
        """,
            (datetime.datetime.now(), provider_name),
        )
    else:
        cursor.execute(
            "SELECT consecutive_empty_cycles FROM providers WHERE provider_name = ?",
            (provider_name,),
        )
        row = cursor.fetchone()
        count = (row[0] if row else 0) + 1
        is_free = 1 if count < 3 else 0
        cursor.execute(
            """
            INSERT INTO providers (provider_name, consecutive_empty_cycles, is_free_provider, last_checked)
            VALUES (?, ?, ?, ?)
            ON CONFLICT(provider_name) DO UPDATE SET
                consecutive_empty_cycles = ?, is_free_provider = ?, last_checked = ?
        """,
            (
                provider_name,
                count,
                is_free,
                datetime.datetime.now(),
                count,
                is_free,
                datetime.datetime.now(),
            ),
        )
    conn.commit()
    conn.close()


if __name__ == "__main__":
    init_db()
    print("Database initialized successfully.")
