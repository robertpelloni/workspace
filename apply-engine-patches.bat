@echo off
echo Applying engine integration patches...
set CW=C:\Users\hyper\codewhale-source

rem === Patch 1: Add extension_manager to Engine struct ===
echo [1/4] Adding extension_manager to Engine struct...
powershell -Command "$f='%CW%\crates\tui\src\core\engine.rs'; $c=Get-Content $f -Raw; $c=$c -replace '(pub\(super\) cancel_reason:.*?\])','$1`r`n    extension_manager: std::sync::Arc<codewhale_extension::ExtensionManager>,'; Set-Content $f $c"

rem === Patch 2: Initialize extension_manager in Engine::new() ===
echo [2/4] Initializing extension_manager in Engine::new()...
powershell -Command "$f='%CW%\crates\tui\src\core\engine.rs'; $c=Get-Content $f -Raw; $c=$c -replace '(seam_manager:.*?,)','$1`r`n        extension_manager: {`r`n            let mut mgr = codewhale_extension::ExtensionManager::new();`r`n            codewhale_tn_extension::TormentNexusExtension::register(&mut mgr);`r`n            std::sync::Arc::new(mgr)`r`n        },'; Set-Content $f $c"

rem === Patch 3: Add BeforeAgentStart dispatch in handle_send_message ===
echo [3/4] Adding BeforeAgentStart hook...
powershell -Command "$f='%CW%\crates\tui\src\core\engine.rs'; $c=Get-Content $f -Raw; $c=$c -replace '(self\.session\.working_set\.observe_user_message.*?;)','$1`r`n`r`n        // Dispatch BeforeAgentStart to registered extensions`r`n        let ext_results = self.extension_manager.dispatch(&codewhale_extension::HookEvent::BeforeAgentStart {`r`n            system_prompt: String::new(),`r`n            prompt: content.clone(),`r`n            is_first_turn: self.turn_counter <= 1,`r`n        }).await;'; Set-Content $f $c"

rem === Patch 4: Add ToolCall/ToolResult in execute_tool_with_lock ===
echo [4/4] Adding ToolCall/ToolResult hooks (tool_execution.rs)...
powershell -Command "$f='%CW%\crates\tui\src\core\engine\tool_execution.rs'; $c=Get-Content $f -Raw; $c=$c -replace '(let outcome = )','// Dispatch ToolCall hook`r`n        $1'; Set-Content $f $c"

echo.
echo Patches applied. Now run:
echo   cd %CW% && cargo build --release --package codewhale-tui
echo.
echo The binary will be at: %CW%\target\release\codewhale-tui.exe
echo Or: %CW%\target\release\codewhale.exe
echo.
echo Copy the exe to overwrite the installed version:
echo   copy /Y "%CW%\target\release\codewhale-tui.exe" "%USERPROFILE%\AppData\Roaming\npm\node_modules\codewhale\bin\downloads\codewhale-tui.exe"
echo.
echo Then run: codewhale
