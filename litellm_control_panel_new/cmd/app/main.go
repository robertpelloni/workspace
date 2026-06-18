package main

import (
	"bytes"
	"context"
	"fmt"
	"log"
	"net/http"
	"os"
	"os/exec"
	"path/filepath"
	"strconv"
	"time"

	"github.com/gen2brain/beeep"
	"github.com/getlantern/systray"
	"github.com/robertpelloni/freellm/internal/config"
	"github.com/robertpelloni/freellm/internal/db"
	"github.com/robertpelloni/freellm/internal/engine"
	"github.com/robertpelloni/freellm/internal/icon"
	"github.com/robertpelloni/freellm/internal/proxy"
	"github.com/robertpelloni/freellm/internal/ui"
	"github.com/skratchdot/open-golang/open"
)

func notify(title, message string) {
	beeep.Notify(title, message, "")
}

// menuAction represents a click event from any menu item
type menuAction struct {
	id   string
	data string
}

// menuEventBus collects all menu clicks into a single channel
var menuEventBus = make(chan menuAction, 256)

func click(id, data string) {
	select {
	case menuEventBus <- menuAction{id: id, data: data}:
	default:
		log.Printf("menuEventBus full, dropping action %s", id)
	}
}

// watchMenuItem launches a goroutine that sends a menu action when the item is clicked
func watchMenuItem(item *systray.MenuItem, id, data string) {
	go func() {
		for range item.ClickedCh {
			click(id, data)
		}
	}()
}

func main() {
	lockFile := filepath.Join(os.TempDir(), "freellm.lock")
	if data, err := os.ReadFile(lockFile); err == nil {
		if pid, err := strconv.Atoi(string(bytes.TrimSpace(data))); err == nil {
			if proc, err := os.FindProcess(pid); err == nil {
				if proc.Signal(nil) == nil {
					log.Fatalf("Another FreeLLM instance is already running (PID %d)", pid)
				}
			}
		}
		os.Remove(lockFile)
	}
	os.WriteFile(lockFile, []byte(fmt.Sprintf("%d", os.Getpid())), 0644)
	defer os.Remove(lockFile)

	systray.Run(onReady, onExit)
}

func onReady() {
	// ============================================================
	//  Initialize Core Services
	// ============================================================

	systray.SetIcon(icon.Gray)
	systray.SetTitle("FreeLLM")
	systray.SetTooltip("FreeLLM - Starting...")

	database, err := db.InitDB()
	if err != nil {
		log.Fatalf("Failed to init DB: %v", err)
	}

	eventLogger := engine.NewEventLogger(100, database)

	apiKeys := map[string]string{
		"openrouter":   os.Getenv("OPENROUTER_API_KEY"),
		"groq":         os.Getenv("GROQ_API_KEY"),
		"github":       os.Getenv("GITHUB_TOKEN"),
		"deepinfra":    os.Getenv("DEEPINFRA_API_KEY"),
		"cerebras":     os.Getenv("CEREBRAS_API_KEY"),
		"huggingface":  os.Getenv("HUGGINGFACE_API_KEY"),
		"nvidia":       os.Getenv("NVIDIA_NIM_API_KEY"),
		"gemini":       os.Getenv("GEMINI_API_KEY"),
		"anthropic":    os.Getenv("ANTHROPIC_API_KEY"),
		"mistral":      os.Getenv("MISTRAL_API_KEY"),
		"cohere":       os.Getenv("COHERE_API_KEY"),
		"sambanova":    os.Getenv("SAMBANOVA_API_KEY"),
		"fireworks":    os.Getenv("FIREWORKS_API_KEY"),
		"hyperbolic":   os.Getenv("HYPERBOLIC_API_KEY"),
		"cloudflare":   os.Getenv("CLOUDFLARE_API_KEY"),
		"opencode_zen": os.Getenv("OPENCODE_ZEN_API_KEY"),
		"codestral":    os.Getenv("CODESTRAL_API_KEY"),
		"nvidia_nim":   os.Getenv("NVIDIA_API_KEY"),
	}

	keyCount := 0
	for _, v := range apiKeys {
		if v != "" {
			keyCount++
		}
	}
	log.Printf("API keys configured: %d/%d providers have keys", keyCount, len(apiKeys))

	benchmarker := engine.NewBenchmarker(apiKeys, 100, eventLogger)

	cfgPath := "freellm-config.yaml"
	cfg, err := config.LoadConfig(cfgPath)
	if err != nil {
		log.Printf("Warning: freellm-config.yaml not found, using defaults: %v", err)
		cfg = &config.Config{Port: 4000}
	}

	config.WatchConfig(cfgPath, func(newCfg *config.Config) {
		log.Println("Applying new configuration...")
		cfg = newCfg
		if newCfg.Providers != nil {
			for p, pcfg := range newCfg.Providers {
				if pcfg.BaseURL != "" {
					benchmarker.BaseURLs[p] = pcfg.BaseURL
				}
				if pcfg.ModelsURL != "" {
					benchmarker.BaseURLs[p+"_models"] = pcfg.ModelsURL
				}
				if pcfg.Completions != "" {
					benchmarker.BaseURLs[p+"_completions"] = pcfg.Completions
				}
			}
		}
	})

	proxyPort := cfg.Port
	if proxyPort == 0 {
		proxyPort = 4000
	}
	if envPort := os.Getenv("FREELLM_PORT"); envPort != "" {
		if p, err := strconv.Atoi(envPort); err == nil && p > 0 {
			proxyPort = p
		}
	}

	gateway := proxy.NewGateway(10, database)
	gateway.RestoreQueue()

	go func() {
		addr := fmt.Sprintf(":%d", proxyPort)
		log.Printf("Starting FreeLLM Proxy on %s", addr)
		if err := http.ListenAndServe(addr, gateway); err != nil {
			log.Printf("Proxy failed: %v", err)
		}
	}()

	uiServer := ui.NewUIServer(database, eventLogger, gateway)
	go func() {
		log.Println("Starting Web Dashboard on :8080")
		if err := uiServer.Start(":8080"); err != nil {
			log.Printf("UI Server failed: %v", err)
		}
	}()

	// ============================================================
	//  State
	// ============================================================

	routingEnabled := true
	autoPilot := true
	refreshTrigger := make(chan bool, 1)
	fullRefreshInterval := 60 * time.Minute
	pulseInterval := 10 * time.Minute
	lastFullRefresh := time.Time{}
	menuBuilt := false

	// ============================================================
	//  Build Static Menu (matches Python version layout)
	//  Model submenus are flat (2 levels max) to work on Windows.
	//  Each model is listed as a clickable item under its group.
	//  Clicking a model = Set as Primary.
	//  Skip/Blacklist are separate items per model.
	// ============================================================

	// --- Top ---
	mRouting := systray.AddMenuItemCheckbox("Master Routing", "Enable request routing", true)
	watchMenuItem(mRouting, "toggle_routing", "")

	mCopyModel := systray.AddMenuItem("Copy Active Model", "Copy primary model ID to clipboard")
	watchMenuItem(mCopyModel, "copy_active_model", "")

	systray.AddSeparator()

	// --- Status ---
	mStatus := systray.AddMenuItem("FreeLLM: Starting | Primary: None", "Current status")
	mStatus.Disable()

	systray.AddSeparator()

	// --- Primary Actions ---
	mOpen := systray.AddMenuItem("Open LLM Interface", "Open the LLM chat in browser")
	watchMenuItem(mOpen, "open_interface", "")

	mSettings := systray.AddMenuItem("Settings", "Open settings")
	watchMenuItem(mSettings, "open_settings", "")

	systray.AddSeparator()

	// --- UI Windows ---
	mQuickQuery := systray.AddMenuItem("Quick Query", "Send a quick query to the LLM")
	watchMenuItem(mQuickQuery, "open_quick_query", "")

	mModelComparison := systray.AddMenuItem("Model Comparison", "Compare model responses side by side")
	watchMenuItem(mModelComparison, "open_comparison", "")

	mDashboard := systray.AddMenuItem("Show Dashboard", "Open monitoring dashboard")
	watchMenuItem(mDashboard, "open_dashboard", "")

	mLeaderboard := systray.AddMenuItem("Model Leaderboard", "View model rankings")
	watchMenuItem(mLeaderboard, "open_leaderboard", "")

	mSavings := systray.AddMenuItem("Cost Savings", "View cost savings report")
	watchMenuItem(mSavings, "open_savings", "")

	mMonitoring := systray.AddMenuItem("Monitoring Dashboard", "Real-time monitoring")
	watchMenuItem(mMonitoring, "open_monitoring", "")

	mProtocol := systray.AddMenuItem("Protocol Oversight", "View protocol compliance")
	watchMenuItem(mProtocol, "open_protocol", "")

	mExecution := systray.AddMenuItem("Execution Dashboard", "View execution metrics")
	watchMenuItem(mExecution, "open_execution", "")

	mSystemStatus := systray.AddMenuItem("System Status", "View system health")
	watchMenuItem(mSystemStatus, "open_status", "")

	systray.AddSeparator()

	// --- ★ Primary Models Submenu (flat, populated dynamically) ---
	mPrimaryGroup := systray.AddMenuItem("★ Primary (0)", "Primary model group — click model to set as #1")

	// --- Fallback Models Submenu (flat, populated dynamically) ---
	mFallbackGroup := systray.AddMenuItem("  Fallback (0)", "Fallback model group")

	systray.AddSeparator()

	// --- Auto-Pilot & Refresh ---
	mAutoPilot := systray.AddMenuItemCheckbox("Auto-Pilot Mode", "Automatically benchmark and route", true)
	watchMenuItem(mAutoPilot, "toggle_autopilot", "")

	mRefreshNow := systray.AddMenuItem("Refresh Now", "Force a model refresh now")
	watchMenuItem(mRefreshNow, "refresh_now", "")

	systray.AddSeparator()

	// --- Enable Providers Submenu (populated dynamically) ---
	mProviders := systray.AddMenuItem("Enable Providers", "Toggle provider on/off")

	// --- Documentation ---
	mDocs := systray.AddMenuItem("Documentation", "Open FreeLLM documentation")
	watchMenuItem(mDocs, "open_docs", "")

	// --- Start with Windows ---
	mStartup := systray.AddMenuItem("Start with Windows", "Launch on system startup")
	mStartupEnable := mStartup.AddSubMenuItem("Enable", "Add to Windows startup")
	watchMenuItem(mStartupEnable, "startup_enable", "")
	mStartupDisable := mStartup.AddSubMenuItem("Disable", "Remove from Windows startup")
	watchMenuItem(mStartupDisable, "startup_disable", "")

	// --- Maintenance ---
	mMaintenance := systray.AddMenuItem("Maintenance", "System maintenance options")
	mMaintClearSkips := mMaintenance.AddSubMenuItem("Clear Skip List", "Clear all manual model skips")
	watchMenuItem(mMaintClearSkips, "maint_clear_skips", "")
	mMaintClearBlacklist := mMaintenance.AddSubMenuItem("Clear Blacklist", "Remove all blacklisted models")
	watchMenuItem(mMaintClearBlacklist, "maint_clear_blacklist", "")
	mMaintResetStats := mMaintenance.AddSubMenuItem("Reset Provider Stats", "Reset all provider and model statistics")
	watchMenuItem(mMaintResetStats, "maint_reset_stats", "")
	mMaintCleanupProbes := mMaintenance.AddSubMenuItem("Cleanup Old Probes (>90d)", "Delete probe history older than 90 days")
	watchMenuItem(mMaintCleanupProbes, "maint_cleanup_probes", "")
	mMaintBackupConfig := mMaintenance.AddSubMenuItem("Backup FreeLLM Config", "Save current config to .bak")
	watchMenuItem(mMaintBackupConfig, "maint_backup_config", "")
	mMaintRestoreConfig := mMaintenance.AddSubMenuItem("Restore FreeLLM Config", "Restore config from .bak backup")
	watchMenuItem(mMaintRestoreConfig, "maint_restore_config", "")

	systray.AddSeparator()

	// --- FreeLLM Control ---
	mControl := systray.AddMenuItem("FreeLLM Control", "Proxy control options")
	mControlRefresh := mControl.AddSubMenuItem("Refresh Models", "Re-discover and benchmark all models")
	watchMenuItem(mControlRefresh, "control_refresh", "")
	mControlViewLogs := mControl.AddSubMenuItem("View Proxy Logs", "Open log viewer")
	watchMenuItem(mControlViewLogs, "control_view_logs", "")
	mControlViewEngineLogs := mControl.AddSubMenuItem("View Engine Logs", "View engine/benchmark logs")
	watchMenuItem(mControlViewEngineLogs, "control_view_engine_logs", "")
	mControlViewConfig := mControl.AddSubMenuItem("View Config", "Open config editor")
	watchMenuItem(mControlViewConfig, "control_view_config", "")

	systray.AddSeparator()

	// --- Quit ---
	mQuit := systray.AddMenuItem("Quit", "Quit FreeLLM")
	watchMenuItem(mQuit, "quit", "")

	// ============================================================
	//  Build Dynamic Model Items (FLAT — max 2 nesting levels)
	//
	//  Structure per model (under ★ Primary / Fallback submenu):
	//    ★ model-name (provider) 2.1s score=85    [click = Set as Primary]
	//       ↳ Skip (24h)                          [click = skip 24h]
	//       ↳ Blacklist                            [click = blacklist]
	//       ↳ ↓ Demote to Fallback  (primary only)
	//       ↳ ↑ Promote to Primary   (fallback only)
	//       ↳ ↑ Move Up              (not first)
	//       ↳ ↓ Move Down            (not last)
	//
	//  This keeps it at exactly 2 levels: Group → Item + Actions
	//  Windows systray renders this correctly.
	// ============================================================

	rebuildDynamicMenu := func() {
		if menuBuilt {
			return // systray doesn't support removing items, build once
		}

		models := gateway.GetModels()
		if len(models) == 0 {
			return // don't build yet, don't set menuBuilt so it retries later
		}
		primaryCount := gateway.PrimaryCount

		pCount := primaryCount
		if len(models) < pCount {
			pCount = len(models)
		}
		fCount := len(models) - primaryCount
		if fCount < 0 {
			fCount = 0
		}

		mPrimaryGroup.SetTitle(fmt.Sprintf("★ Primary (%d)", pCount))
		mFallbackGroup.SetTitle(fmt.Sprintf("  Fallback (%d)", fCount))

		for i, m := range models {
			isPrimary := i < primaryCount

			latStr := "?"
			if m.Latency > 0 {
				latStr = fmt.Sprintf("%.2fs", m.Latency)
			}
			scoreStr := ""
			if m.Score > 0 {
				scoreStr = fmt.Sprintf("score=%.0f", m.Score)
			}
			paramsStr := ""
			if m.Parameters > 0 {
				paramsStr = fmt.Sprintf("%dB", m.Parameters)
			}
			groupTag := "★"
			if !isPrimary {
				groupTag = "  "
			}

			// Model label is a flat item under the group submenu.
			// Clicking it sets it as primary (#1).
			label := fmt.Sprintf("%s %s (%s) %s %s %s", groupTag, m.ID, m.Provider, paramsStr, latStr, scoreStr)

			var parent *systray.MenuItem
			if isPrimary {
				parent = mPrimaryGroup
			} else {
				parent = mFallbackGroup
			}

			mEntry := parent.AddSubMenuItem(label, m.ID)

			// --- Set as Primary ★ (clicking the model name itself also does this) ---
			mSetPrimary := mEntry.AddSubMenuItem("★ Set as Primary", "Make "+m.ID+" the #1 model")
			watchMenuItem(mSetPrimary, "model_set_primary", m.ID)

			// --- Set as Fallback ---
			mSetFallback := mEntry.AddSubMenuItem("↕ Set as Fallback", "Make "+m.ID+" the top fallback model")
			watchMenuItem(mSetFallback, "model_set_fallback", m.ID)

			// Skip (24h)
			mSkip := mEntry.AddSubMenuItem("Skip (24h)", "Skip "+m.ID+" for 24 hours")
			watchMenuItem(mSkip, "model_skip", m.ID)

			// Blacklist
			mBL := mEntry.AddSubMenuItem("Blacklist", "Permanently blacklist "+m.ID)
			watchMenuItem(mBL, "model_blacklist", m.ID)

			if isPrimary {
				// Demote
				mDemote := mEntry.AddSubMenuItem("↓ Demote to Fallback", "Move "+m.ID+" to fallback group")
				watchMenuItem(mDemote, "model_demote", m.ID)

				// Move Up (if not already #1)
				if i > 0 {
					mUp := mEntry.AddSubMenuItem("↑ Move Up", "Move "+m.ID+" higher in priority")
					watchMenuItem(mUp, "model_move_up", m.ID)
				}

				// Move Down (if not last in primary group)
				if i < primaryCount-1 && i < len(models)-1 {
					mDown := mEntry.AddSubMenuItem("↓ Move Down", "Move "+m.ID+" lower in priority")
					watchMenuItem(mDown, "model_move_down", m.ID)
				}
			} else {
				// Promote
				mPromote := mEntry.AddSubMenuItem("↑ Promote to Primary", "Move "+m.ID+" to primary group")
				watchMenuItem(mPromote, "model_promote", m.ID)

				// Move Up (if not first in fallback)
				if i > primaryCount {
					mUp := mEntry.AddSubMenuItem("↑ Move Up", "Move "+m.ID+" higher in priority")
					watchMenuItem(mUp, "model_move_up", m.ID)
				}

				// Move Down (if not last)
				if i < len(models)-1 {
					mDown := mEntry.AddSubMenuItem("↓ Move Down", "Move "+m.ID+" lower in priority")
					watchMenuItem(mDown, "model_move_down", m.ID)
				}
			}
		}

		// Build provider toggle checkboxes
		providerHealth, _ := db.GetProviderHealth(database)
		for _, ph := range providerHealth {
			cb := mProviders.AddSubMenuItemCheckbox(ph.Name,
				fmt.Sprintf("Toggle %s (latency=%.1fs, success=%.0f%%)", ph.Name, ph.AvgLatency, ph.SuccessRate),
				ph.Enabled)
			watchMenuItem(cb, "toggle_provider", ph.Name)
		}

		menuBuilt = true
	}

	// ============================================================
	//  Tray Status Update
	// ============================================================

	updateTrayStatus := func() {
		models := gateway.GetModels()
		if len(models) == 0 {
			systray.SetIcon(icon.Gray)
			systray.SetTooltip("FreeLLM - No models available")
			mStatus.SetTitle("FreeLLM: Offline | Primary: None")
			return
		}
		top := models[0]
		lat := top.Latency

		var primaryLabel string
		if lat < 0.5 {
			systray.SetIcon(icon.Green)
			primaryLabel = fmt.Sprintf("%s (%.2fs)", top.ID, lat)
		} else if lat < 1.5 {
			systray.SetIcon(icon.Yellow)
			primaryLabel = fmt.Sprintf("%s (%.2fs)", top.ID, lat)
		} else {
			systray.SetIcon(icon.Red)
			primaryLabel = fmt.Sprintf("%s (%.2fs)", top.ID, lat)
		}

		systray.SetTooltip(fmt.Sprintf("FreeLLM - Primary: %s", primaryLabel))
		mStatus.SetTitle(fmt.Sprintf("FreeLLM: Live | Primary: %s | %d models", primaryLabel, len(models)))
	}

	// ============================================================
	//  Background Workers
	// ============================================================

	go func() {
		for {
			ctx := context.Background()
			now := time.Now()
			timeSinceFull := now.Sub(lastFullRefresh)

			if timeSinceFull >= fullRefreshInterval || lastFullRefresh.IsZero() {
				log.Println("Full refresh: benchmarking all candidates...")
				systray.SetIcon(icon.Yellow)
				mStatus.SetTitle("FreeLLM: Syncing...")
				notify("FreeLLM Sync", "Full model discovery started...")

				candidates := benchmarker.FetchModels(ctx, database)
				log.Printf("Discovered %d model candidates", len(candidates))

				ranked := benchmarker.RunBenchmark(ctx, candidates, database)
				gateway.UpdateModels(ranked)
				uiServer.UpdateModels(ranked)

				for _, m := range ranked {
					db.UpdateModelPricing(database, m.ID, m.Provider, m.PromptPrice, m.CompletionPrice)
				}

				topModel := "none"
				if len(ranked) > 0 {
					topModel = ranked[0].ID
					notify("Sync Complete", fmt.Sprintf("Top Model: %s (%.2fs)", topModel, ranked[0].Latency))
				}
				db.LogActivity(database, "Sync Complete", topModel, fmt.Sprintf("Ranked %d models", len(ranked)))
				lastFullRefresh = time.Now()
				updateTrayStatus()
				rebuildDynamicMenu()
			} else {
				if routingEnabled {
					currentModels := gateway.GetModels()
					if len(currentModels) > 0 {
						ranked, changed := benchmarker.QuickPulse(ctx, currentModels, 5, database)
						if changed {
							gateway.UpdateModels(ranked)
							uiServer.UpdateModels(ranked)
							log.Println("Quick pulse: rankings changed")
						}
					}
				}
				updateTrayStatus()
			}

			select {
			case <-refreshTrigger:
			case <-time.After(pulseInterval):
			}
		}
	}()

	go func() {
		ticker := time.NewTicker(60 * time.Second)
		for range ticker.C {
			var qpm int
			var totalTokens int
			oneMinAgo := time.Now().Add(-1 * time.Minute)
			err := database.QueryRow("SELECT COUNT(*), SUM(prompt_tokens + completion_tokens) FROM usage WHERE timestamp > ?", oneMinAgo).Scan(&qpm, &totalTokens)
			if err == nil {
				tps := float64(totalTokens) / 60.0
				db.LogStabilityMetric(database, float64(qpm), tps)
			}
			updateTrayStatus()
		}
	}()

	go func() {
		ticker := time.NewTicker(24 * time.Hour)
		for range ticker.C {
			count, _ := db.PruneOldData(database, 30)
			log.Printf("Pruned %d old records", count)
		}
	}()

	go func() {
		failCount := 0
		startupGrace := time.Now().Add(60 * time.Second)
		for {
			time.Sleep(1 * time.Minute)
			models := gateway.GetModels()
			if len(models) == 0 {
				continue
			}

			// Check top 3 models, not just #1
			topCheck := 3
			if len(models) < topCheck {
				topCheck = len(models)
			}
			allHealthy := false
			var lastErr error
			for i := 0; i < topCheck; i++ {
				m := models[i]
				ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
				_, err := benchmarker.MeasureLatency(ctx, m.ID, m.Provider)
				cancel()
				if err == nil {
					allHealthy = true
					break
				}
				lastErr = err
			}

			if !allHealthy {
				if time.Now().Before(startupGrace) {
					continue
				}
				failCount++
				top := models[0]
				log.Printf("Health check failed for top %d models (%d/3): %v", topCheck, failCount, lastErr)
				db.LogActivity(database, "Health Check Failure", top.ID, fmt.Sprintf("Attempt %d/3 failed", failCount))
				if failCount == 1 {
					notify("Health Alert", fmt.Sprintf("Health check failed for %s (%d/3)", top.ID, failCount))
				}
				systray.SetIcon(icon.Red)
			} else {
				failCount = 0
			}

			if failCount >= 3 {
				log.Println("Proactive health threshold reached. Triggering refresh...")
				db.LogActivity(database, "Fallback Triggered", models[0].ID, "Consecutive health failures")
				select {
				case refreshTrigger <- true:
				default:
				}
				failCount = 0
			}
		}
	}()

	// Deferred initial menu build — retry until models are loaded
	go func() {
		for i := 0; i < 60; i++ {
			time.Sleep(10 * time.Second)
			if menuBuilt {
				return
			}
			models := gateway.GetModels()
			if len(models) > 0 {
				rebuildDynamicMenu()
				return
			}
		}
	}()

	// ============================================================
	//  Central Menu Event Handler
	// ============================================================

	go func() {
		for action := range menuEventBus {
			switch action.id {

			// --- Top Section ---
			case "toggle_routing":
				routingEnabled = !routingEnabled
				log.Printf("Master Routing: %v", routingEnabled)

			case "copy_active_model":
				models := gateway.GetModels()
				if len(models) > 0 {
					modelID := models[0].ID
					exec.Command("powershell", "-Command",
						fmt.Sprintf("Set-Clipboard -Value '%s'", modelID)).Run()
					notify("FreeLLM", fmt.Sprintf("Copied: %s", modelID))
				}

			// --- Primary Actions ---
			case "open_interface":
				open.Run(fmt.Sprintf("http://localhost:%d", proxyPort))

			case "open_settings":
				open.Run("http://localhost:8080#config-tab")

			// --- UI Windows ---
			case "open_quick_query":
				open.Run(fmt.Sprintf("http://localhost:%d", proxyPort))

			case "open_comparison":
				open.Run("http://localhost:8080#comparison-tab")

			case "open_dashboard":
				open.Run("http://localhost:8080")

			case "open_leaderboard":
				open.Run("http://localhost:8080#rankings-tab")

			case "open_savings":
				open.Run("http://localhost:8080#savings-tab")

			case "open_monitoring":
				open.Run("http://localhost:8080#monitoring-tab")

			case "open_protocol":
				open.Run("http://localhost:8080#protocol-tab")

			case "open_execution":
				open.Run("http://localhost:8080#execution-tab")

			case "open_status":
				open.Run("http://localhost:8080#status-tab")

			// --- Auto-Pilot & Refresh ---
			case "toggle_autopilot":
				autoPilot = !autoPilot
				log.Printf("Auto-Pilot: %v", autoPilot)

			case "refresh_now":
				log.Println("Refreshing models...")
				systray.SetIcon(icon.Yellow)
				mStatus.SetTitle("FreeLLM: Refreshing...")
				lastFullRefresh = time.Time{}
				select {
				case refreshTrigger <- true:
				default:
				}

			// --- Documentation ---
			case "open_docs":
				open.Run("https://docs.freellm.ai/")

			// --- Startup ---
			case "startup_enable":
				config.SetStartWithWindows(true)
				notify("FreeLLM", "Start with Windows enabled")

			case "startup_disable":
				config.SetStartWithWindows(false)
				notify("FreeLLM", "Start with Windows disabled")

			// --- Maintenance ---
			case "maint_clear_skips":
				db.ClearSkips(database)
				notify("FreeLLM", "Skip list cleared")

			case "maint_clear_blacklist":
				db.ClearBlacklist(database)
				notify("FreeLLM", "Blacklist cleared")

			case "maint_reset_stats":
				db.ResetStats(database)
				notify("FreeLLM", "All provider and model stats reset")

			case "maint_cleanup_probes":
				count, err := db.PruneOldData(database, 90)
				if err == nil {
					notify("FreeLLM", fmt.Sprintf("Cleaned up %d old probe records", count))
				}

			case "maint_backup_config":
				data, err := os.ReadFile(cfgPath)
				if err == nil {
					os.WriteFile(cfgPath+".bak", data, 0644)
					notify("FreeLLM", "Config backed up to "+cfgPath+".bak")
				}

			case "maint_restore_config":
				data, err := os.ReadFile(cfgPath + ".bak")
				if err == nil {
					os.WriteFile(cfgPath, data, 0644)
					notify("FreeLLM", "Config restored from backup")
					if newCfg, err := config.LoadConfig(cfgPath); err == nil {
						cfg = newCfg
					}
				} else {
					notify("FreeLLM", "No backup config found")
				}

			// --- FreeLLM Control ---
			case "control_refresh":
				systray.SetIcon(icon.Yellow)
				mStatus.SetTitle("FreeLLM: Refreshing...")
				lastFullRefresh = time.Time{}
				select {
				case refreshTrigger <- true:
				default:
				}

			case "control_view_logs":
				open.Run("http://localhost:8080#logs-tab")

			case "control_view_engine_logs":
				open.Run("http://localhost:8080#engine-logs-tab")

			case "control_view_config":
				open.Run("http://localhost:8080#config-tab")

			// --- Model Actions ---
			case "model_set_primary":
				log.Printf("Setting %s as primary ★", action.data)
				gateway.SetModelPrimary(action.data)
				db.LogActivity(database, "Set Primary", action.data, "Manually set as primary model")
				notify("FreeLLM", fmt.Sprintf("Primary set to: %s", action.data))
				updateTrayStatus()

			case "model_set_fallback":
				log.Printf("Setting %s as fallback", action.data)
				gateway.SetAsFallback(action.data)
				db.LogActivity(database, "Set Fallback", action.data, "Manually set as fallback model")
				notify("FreeLLM", fmt.Sprintf("Fallback set to: %s", action.data))

			case "model_demote":
				log.Printf("Demoting %s to fallback", action.data)
				gateway.DemoteModel(action.data)
				db.LogActivity(database, "Demote Model", action.data, "Demoted to fallback group")
				notify("FreeLLM", fmt.Sprintf("Demoted: %s", action.data))

			case "model_promote":
				log.Printf("Promoting %s to primary", action.data)
				gateway.PromoteModel(action.data)
				db.LogActivity(database, "Promote Model", action.data, "Promoted to primary group")
				notify("FreeLLM", fmt.Sprintf("Promoted: %s", action.data))
				updateTrayStatus()

			case "model_move_up":
				log.Printf("Moving %s up", action.data)
				gateway.MoveModelUp(action.data)

			case "model_move_down":
				log.Printf("Moving %s down", action.data)
				gateway.MoveModelDown(action.data)

			case "model_skip":
				log.Printf("Skipping %s for 24h", action.data)
				db.SkipModel(database, action.data, 24)
				db.LogActivity(database, "Skip Model", action.data, "Skipped for 24 hours")
				notify("FreeLLM", fmt.Sprintf("Skipped (24h): %s", action.data))

			case "model_blacklist":
				log.Printf("Blacklisting %s", action.data)
				db.BlacklistModel(database, action.data)
				db.LogActivity(database, "Blacklist Model", action.data, "Permanently blacklisted")
				notify("FreeLLM", fmt.Sprintf("Blacklisted: %s", action.data))

			// --- Provider Toggle ---
			case "toggle_provider":
				providers, _ := db.GetProviderHealth(database)
				var currentEnabled bool
				for _, p := range providers {
					if p.Name == action.data {
						currentEnabled = p.Enabled
						break
					}
				}
				newState := !currentEnabled
				log.Printf("Toggling provider %s: enabled=%v", action.data, newState)
				db.SetProviderStatus(database, action.data, newState)
				db.LogActivity(database, "Toggle Provider", action.data,
					fmt.Sprintf("Provider %s: enabled=%v", action.data, newState))

			// --- Quit ---
			case "quit":
				systray.Quit()
				return
			}
		}
	}()
}

func onExit() {}
