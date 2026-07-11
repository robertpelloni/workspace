"""Apply engine integration patches for Extension API"""
path = r'C:\Users\hyper\codewhale-source\crates\tui\src\core\engine.rs'

with open(path, 'r', encoding='utf-8') as f:
    content = f.read()

# 1. Add use import at top of file
content = content.replace(
    'use crate::resource_telemetry::',
    'use codewhale_extension::ExtensionManager;\nuse crate::resource_telemetry::',
    1
)
print("Step 1 OK: import added")

# 2. Add extension_manager field to Engine struct
# Use single-line matching for reliability
old_field = 'shared_paused: Arc<StdMutex<bool>>,\n}'
# This appears in both EngineHandle and Engine structs.
# We need to replace only the SECOND one (Engine struct).
# Read the file content and manually find the right position.
idx_first = content.find(old_field)
if idx_first >= 0:
    idx_second = content.find(old_field, idx_first + len(old_field))
    if idx_second >= 0:
        # Replace the second occurrence (Engine struct)
        new_field = 'shared_paused: Arc<StdMutex<bool>>,\n    extension_manager: std::sync::Arc<codewhale_extension::ExtensionManager>,\n}'
        content = content[:idx_second] + new_field + content[idx_second + len(old_field):]
        print("Step 2 OK: Engine struct field added")
    else:
        # Only one occurrence found - EngineHandle was already patched or something
        # Just replace the first one and hope for the best
        new_field = 'shared_paused: Arc<StdMutex<bool>>,\n    extension_manager: std::sync::Arc<codewhale_extension::ExtensionManager>,\n}'
        content = content[:idx_first] + new_field + content[idx_first + len(old_field):]
        print("Step 2 WARN: Only 1 occurrence found, replaced anyway")
else:
    print("Step 2 FAIL: Cannot find shared_paused field")
    raise SystemExit(1)

# 3. Initialize extension_manager in Engine struct constructor
old_init = 'shared_paused: shared_paused.clone(),\n        };\n        let handle = EngineHandle {'
assert old_init in content, "Cannot find Engine constructor end"
new_init = '''shared_paused: shared_paused.clone(),
            extension_manager: {
                let mut mgr = codewhale_extension::ExtensionManager::new();
                codewhale_tn_extension::TormentNexusExtension::register(&mut mgr);
                std::sync::Arc::new(mgr)
            },
        };
        let handle = EngineHandle {'''
content = content.replace(old_init, new_init, 1)
print("Step 3 OK: Engine constructor init added")

# 4. Add BeforeAgentStart dispatch
old_dispatch = '            .observe_user_message(&content, &self.session.workspace);'
assert old_dispatch in content, f"Cannot find observe_user_message"
new_dispatch = old_dispatch + '''

        let results = self.extension_manager
            .dispatch(&codewhale_extension::HookEvent::BeforeAgentStart {
                system_prompt: String::new(),
                prompt: content.clone(),
                is_first_turn: self.turn_counter <= 1,
            })
            .await;'''
content = content.replace(old_dispatch, new_dispatch, 1)
print("Step 4 OK: BeforeAgentStart dispatch added")

with open(path, 'w', encoding='utf-8') as f:
    f.write(content)

# Verify
with open(path, 'r', encoding='utf-8') as f:
    r = f.read()

ok = True
for check in [
    'extension_manager: std::sync::Arc<codewhale_extension::ExtensionManager>,',
    'TormentNexusExtension::register',
    'HookEvent::BeforeAgentStart'
]:
    count = r.count(check)
    status = 'OK' if count == 1 else 'WARN' if count > 1 else 'FAIL'
    print(f"  {status}: '{check}' found {count} time(s)")
    if count != 1:
        ok = False

if ok:
    print("\nAll patches applied successfully!")
else:
    print("\nSome patches have issues - check above")
