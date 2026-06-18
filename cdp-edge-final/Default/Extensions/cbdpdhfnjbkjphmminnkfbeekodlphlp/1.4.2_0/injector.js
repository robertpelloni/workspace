(function(){"use strict";const Ze="gemini-folders-injector-host",Xe="geminiFoldersData",Ut=['button[data-test-id="delete-button"]','[data-test-id="delete-button"] button','[role="menuitem"][data-test-id="delete-button"]','button[aria-label*="delete" i]',"button.delete-btn"],jt=['button[data-test-id="confirm-button"]','[data-test-id="confirm-button"] button','gem-button[data-test-id="confirm-button"] button','button[aria-label*="confirm" i]',"button.confirm-btn"],ft=['[data-test-id="actions-menu-button"] button','gem-icon-button[data-test-id="actions-menu-button"] button','button[data-test-id="actions-menu-button"]','button[aria-label^="More options"]','button[aria-label*="More options"]','button[aria-label*="actions" i]','button[aria-label*="menu" i]',"button.menu-button","button.actions-button"],Yt=["div.cdk-overlay-container",'[role="dialog"]',".modal-container",".overlay-container"];let z=null,u=null,Pe="light",Se=!1,Je,w={folders:[],chatMetadata:{},settings:{hideFolderedChats:!1},selectedItems:[],modalType:null};function Ro(){return("10000000-1000-4000-8000"+-1e11).replace(/[018]/g,e=>(e^crypto.getRandomValues(new Uint8Array(1))[0]&15>>e/4).toString(16))}function Wt(e){return new Promise(t=>setTimeout(t,e))}function Kt(e,t){let n;return function(...r){const i=()=>{clearTimeout(n),e(...r)};clearTimeout(n),n=setTimeout(i,t)}}function Vo(e){if(!e)return e;const t=e.toString();return t.indexOf("T")!==-1?new Date(e).getTime():t.indexOf(".")!==-1&&t.split(".")[0].length===10?new Date(e*1e3).getTime():t.indexOf(".")!==-1&&t.split(".")[0].length===13?new Date(e).getTime():t.length===13?new Date(e).getTime():t.length===10?new Date(e*1e3).getTime():e}function Uo(e){if(!e)return e;const t=new Date,n=new Date;n.setDate(n.getDate()-1);const o=t.getDate(),r=t.getMonth()+1,i=t.getFullYear(),a=e.getDate(),d=e.getMonth()+1,p=e.getFullYear();return o===a&&r===d&&i===p?`Today ${e.toLocaleTimeString("en-US",{hour:"numeric",minute:"numeric"})}`:n.getDate()===a&&n.getMonth()+1===d&&n.getFullYear()===p?`Yesterday ${e.toLocaleTimeString("en-US",{hour:"numeric",minute:"numeric"})}`:`${e.toLocaleDateString("en-US",{year:"2-digit",month:"2-digit",day:"2-digit"})} ${e.toLocaleTimeString("en-US",{hour:"numeric",minute:"numeric"})}`}const pe=(function(){const t=new Map,n=new Set;function o(p){for(const[s,g]of t.entries())p-g>1e4&&t.delete(s)}function r(p,s){try{let g="";return s&&(s.correlationId&&(g+=`|corr:${s.correlationId}`),s.plan&&(g+=`|plan:${s.plan}`),s.feature&&(g+=`|feat:${s.feature}`),s.fromVersion&&s.toVersion&&(g+=`|ver:${s.fromVersion}->${s.toVersion}`)),g||(g=`|v:${typeof CONFIG<"u"&&CONFIG.VERSION?CONFIG.VERSION:"unknown"}`),`${p}${g}`}catch{return p}}function i(p){const s={};for(const g in p||{}){if(!Object.prototype.hasOwnProperty.call(p,g)||g.toLowerCase().includes("email")||g.toLowerCase().includes("code"))continue;const c=p[g];typeof c=="string"?s[g]=c.slice(0,200):s[g]=c}return s}async function a(){let p=null;try{p=(await chrome.storage?.local?.get("gt_install_id"))?.gt_install_id||null}catch{}let s=null;try{s=window.geminiAPI?.getUserInfo?.().userId||null}catch{}let g=null;try{g=window.geminiAPI?.getPlan?.()||null}catch{}const c=typeof CONFIG<"u"&&CONFIG.VERSION?CONFIG.VERSION:null,b=navigator.userAgentData?.brands?.[0]?.brand||navigator.userAgent||"unknown";let C="unknown";try{C=typeof Me=="function"?Me():"unknown"}catch{}return{installId:p,userId:s,plan:g,extVersion:c,schemaVersion:1,platform:b,pageTheme:C,ts:Date.now()}}async function d(p,s={}){try{if(!CONFIG?.FEATURES?.trackAnalytics||!window?.geminiAPI?.trackEvent)return;const g=r(p,s),c=Date.now();if(o(c),t.has(g)||n.has(g))return;n.add(g);const C={...await a(),...i(s)};C.eventId=typeof crypto<"u"&&crypto.randomUUID?crypto.randomUUID():`${c}-${Math.random().toString(36).slice(2)}`,await window.geminiAPI.trackEvent(p,C),t.set(g,c),n.delete(g)}catch{}}return{track:d}})();function Qe(e,t){e&&(t?(e.classList.add("loading"),e.disabled=!0,e.dataset.originalText=e.textContent):(e.classList.remove("loading"),e.disabled=!1,e.dataset.originalText&&(e.textContent=e.dataset.originalText,delete e.dataset.originalText)))}function jo(e,t="Success!"){if(!e)return;e.classList.remove("loading"),e.classList.add("success");const n=e.textContent;e.textContent=t,setTimeout(()=>{e.classList.remove("success"),e.textContent=n,e.disabled=!1},2e3)}function Yo(e,t="Error"){if(!e)return;e.classList.remove("loading"),e.classList.add("error");const n=e.textContent;e.textContent=t,setTimeout(()=>{e.classList.remove("error"),e.textContent=n,e.disabled=!1},2e3)}function Q(e,t="success"){document.querySelectorAll(".prompt-toast").forEach(a=>a.remove()),u&&u.querySelectorAll(".prompt-toast").forEach(d=>d.remove());const o=document.getElementById("gt-fallback-toast-container");o&&o.querySelectorAll(".prompt-toast").forEach(d=>d.remove());const r=document.createElement("div");r.className=`prompt-toast ${t}`,r.textContent=e,r.setAttribute("role","status"),r.setAttribute("aria-live","polite"),at().appendChild(r),requestAnimationFrame(()=>{r.classList.add("show")}),setTimeout(()=>{r.classList.remove("show"),setTimeout(()=>r.remove(),300)},3e3)}try{window.showToast=Q}catch{}function Zt(e,t,n,o="info"){document.querySelectorAll(".prompt-toast").forEach(g=>g.remove()),u&&u.querySelectorAll(".prompt-toast").forEach(c=>c.remove());const i=document.getElementById("gt-fallback-toast-container");i&&i.querySelectorAll(".prompt-toast").forEach(c=>c.remove());const a=document.createElement("div");a.className=`prompt-toast ${o}`,a.setAttribute("role","status"),a.setAttribute("aria-live","polite");const d=document.createElement("span");d.textContent=e;const p=document.createElement("button");p.className="toast-action",p.type="button",p.textContent=t||"Action",p.addEventListener("click",()=>{try{n&&n()}catch{}a.classList.remove("show"),setTimeout(()=>a.remove(),200)}),a.appendChild(d),a.appendChild(p),at().appendChild(a),requestAnimationFrame(()=>{a.classList.add("show")}),setTimeout(()=>{a.classList.remove("show"),setTimeout(()=>a.remove(),300)},5e3)}try{window.showToastWithAction=Zt}catch{}function X(e){Q(e,"error")}function Wo(e,t="info"){Q(e,t)}let Le=null,Ie=null;function at(){if(Ie&&document.body.contains(Ie))return Ie;if(Ie=document.createElement("div"),Ie.id="gt-fallback-toast-container",document.body.appendChild(Ie),!document.getElementById("gt-fallback-toast-styles")){const e=document.createElement("style");e.id="gt-fallback-toast-styles",e.textContent=`
                /* Dark mode toast styles (default) */
                .prompt-toast { 
                    position: fixed; bottom: 32px; left: 50%; transform: translateX(-50%) translateY(100px);
                    background: #131314; color: #e3e3e3; padding: 14px 20px; border-radius: 24px;
                    box-shadow: 0 4px 12px rgba(0,0,0,0.4), 0 0 0 1px rgba(255,255,255,0.08);
                    font-size: 14px; font-weight: 400; line-height: 20px;
                    font-family: 'Google Sans', -apple-system, BlinkMacSystemFont, sans-serif;
                    z-index: 2147483647; opacity: 0; transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
                    max-width: 90vw; min-width: 200px;
                    display: inline-flex; align-items: center; gap: 12px;
                }
                .prompt-toast.show { opacity: 1; transform: translateX(-50%) translateY(0); }
                .prompt-toast.success { background: #131314; color: #e3e3e3; }
                .prompt-toast.error   { background: #131314; color: #f28b82; }
                .prompt-toast.info    { background: #131314; color: #e3e3e3; }
                .prompt-toast .toast-action {
                    background: transparent;
                    color: #8ab4f8;
                    border: none;
                    border-radius: 20px;
                    padding: 6px 16px;
                    font-size: 14px;
                    font-weight: 500;
                    cursor: pointer;
                    margin-left: 4px;
                    font-family: 'Google Sans', -apple-system, BlinkMacSystemFont, sans-serif;
                    transition: background 0.2s ease;
                }
                .prompt-toast .toast-action:hover {
                    background: rgba(138, 180, 248, 0.08);
                }
                .prompt-toast .toast-action:active {
                    background: rgba(138, 180, 248, 0.16);
                }
                
                /* Light mode toast styles */
                body.light-theme .prompt-toast,
                body[data-theme="light"] .prompt-toast,
                .light-mode .prompt-toast {
                    background: #ffffff;
                    color: #3c4043;
                    box-shadow: 0 1px 3px rgba(60,64,67,0.3), 0 1px 2px rgba(60,64,67,0.15);
                }
                body.light-theme .prompt-toast.success,
                body[data-theme="light"] .prompt-toast.success,
                .light-mode .prompt-toast.success,
                body.light-theme .prompt-toast.info,
                body[data-theme="light"] .prompt-toast.info,
                .light-mode .prompt-toast.info {
                    background: #ffffff;
                    color: #3c4043;
                }
                body.light-theme .prompt-toast.error,
                body[data-theme="light"] .prompt-toast.error,
                .light-mode .prompt-toast.error {
                    background: #ffffff;
                    color: #d33333;
                }
                body.light-theme .prompt-toast .toast-action,
                body[data-theme="light"] .prompt-toast .toast-action,
                .light-mode .prompt-toast .toast-action {
                    color: #1a73e8;
                }
                body.light-theme .prompt-toast .toast-action:hover,
                body[data-theme="light"] .prompt-toast .toast-action:hover,
                .light-mode .prompt-toast .toast-action:hover {
                    background: rgba(26, 115, 232, 0.08);
                }
                body.light-theme .prompt-toast .toast-action:active,
                body[data-theme="light"] .prompt-toast .toast-action:active,
                .light-mode .prompt-toast .toast-action:active {
                    background: rgba(26, 115, 232, 0.16);
                }
            `,document.head.appendChild(e)}return Ie}function bt(){if(Le)return;Le=document.createElement("div"),Le.className="processing-overlay",Le.innerHTML=`
            <div class="processing-content">
                <div class="spinner"></div>
                <div class="processing-text">Processing payment...</div>
                <div class="processing-subtext">This may take up to 30 seconds</div>
            </div>
        `;const e=document.createElement("style");e.textContent=`
            .processing-overlay {
                position: fixed;
                top: 0;
                left: 0;
                right: 0;
                bottom: 0;
                background: rgba(0, 0, 0, 0.7);
                display: flex;
                align-items: center;
                justify-content: center;
                z-index: 100000;
                animation: fadeIn 0.3s ease-in;
            }
            
            .processing-content {
                background: var(--surface-color, white);
                border-radius: 12px;
                padding: 32px;
                text-align: center;
                box-shadow: 0 8px 32px rgba(0, 0, 0, 0.2);
            }
            
            .spinner {
                width: 48px;
                height: 48px;
                border: 3px solid var(--border-color, #e0e0e0);
                border-top-color: #4285f4;
                border-radius: 50%;
                margin: 0 auto 16px;
                animation: spin 1s linear infinite;
            }
            
            .processing-text {
                color: var(--text-primary, #202124);
                font-size: 16px;
                font-weight: 500;
                margin-bottom: 8px;
            }
            
            .processing-subtext {
                color: var(--text-secondary, #5f6368);
                font-size: 14px;
            }
            
            @keyframes fadeIn {
                from { opacity: 0; }
                to { opacity: 1; }
            }
            
            @keyframes spin {
                to { transform: rotate(360deg); }
            }
        `,u.appendChild(e),u.appendChild(Le)}function xt(){Le&&(Le.remove(),Le=null)}function Ko(e,t){const n=s=>{const g=/^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(s);return g?{r:parseInt(g[1],16),g:parseInt(g[2],16),b:parseInt(g[3],16)}:null},o=s=>{const[g,c,b]=[s.r,s.g,s.b].map(C=>(C=C/255,C<=.03928?C/12.92:Math.pow((C+.055)/1.055,2.4)));return .2126*g+.7152*c+.0722*b},r=n(e),i=n(t);if(!r||!i)return!1;const a=o(r),d=o(i);return(Math.max(a,d)+.05)/(Math.min(a,d)+.05)>=4.5}function et(e){return new Promise(t=>setTimeout(t,e))}function Re(e,t=document){if(!t)return null;for(const n of e)try{const o=t.querySelector(n);if(o)return o}catch{}return null}function yt(e,t=document,n=7e3){return new Promise((o,r)=>{const i=Re(e,t);if(i&&i.offsetParent!==null&&!i.disabled)return o(i);let a=0;const d=150,p=setInterval(()=>{a+=d;const s=Re(e,t);s&&s.offsetParent!==null&&!s.disabled?(clearInterval(p),o(s)):a>=n&&(clearInterval(p),r(new Error(`Element not actionable within ${n}ms`)))},d)})}async function vt(){try{window.geminiStorage||(window.geminiStorage=new GeminiToolboxStorage,await window.geminiStorage.initialize());const e=window.geminiStorage.getAllFolders(),t=window.geminiStorage.getSettings(),n=window.geminiStorage.state.chatMetadata||{};w.chatMetadata=n,w.folders=e.map(o=>({id:o.id,name:o.name,chatIds:o.chatIds||[],parentId:o.parentId||null,createdAt:o.createdAt,updatedAt:o.updatedAt})),w.settings=t}catch{try{const t=await chrome.storage.local.get(Xe);w.folders=t[Xe]?.folders||[],w.settings=t[Xe]?.settings||{hideFolderedChats:!1},w.folders.length>0}catch{w.folders=[],w.settings={hideFolderedChats:!1}}}}function Zo(){}async function Ne(){try{if(!chrome.runtime?.id)return;window.geminiStorage||(window.geminiStorage=new GeminiToolboxStorage,await window.geminiStorage.initialize()),await window.geminiStorage.updateSettings(w.settings);for(const n of w.folders)window.geminiStorage.getFolder(n.id)?await window.geminiStorage.updateFolder(n.id,{name:n.name,chatIds:n.chatIds,parentId:n.parentId}):(window.geminiStorage.state.folders[n.id]={id:n.id,name:n.name,chatIds:n.chatIds||[],parentId:n.parentId||null,createdAt:n.createdAt||new Date().toISOString(),updatedAt:new Date().toISOString()},n.chatIds&&n.chatIds.forEach(r=>{window.geminiStorage.state.chatFolderMapping[r]=n.id}));const e=new Set(w.folders.map(n=>n.id)),t=Object.keys(window.geminiStorage.state.folders);for(const n of t)e.has(n)||await window.geminiStorage.deleteFolder(n);await window.geminiStorage.saveState()}catch(e){if(e.message?.includes("Extension context invalidated"))return;try{if(!chrome.runtime?.id)return;const t={folders:w.folders,settings:w.settings};await chrome.storage.local.set({[Xe]:t})}catch(t){t.message?.includes("Extension context invalidated"),u&&X("Failed to save folder data. Changes may be lost.")}}}function it(e){if(!e||typeof e!="string")return null;const t=e.trim().replace(/^["']|["']$/g,"").split(/[?#]/)[0];return!t||t==="new"||t==="chat"?null:t.startsWith("c_")?t:/^[a-z0-9_-]{8,}$/i.test(t)?`c_${t}`:t}function st(e){if(!e||typeof e!="string")return null;const t=e.replace(/&quot;/g,'"').replace(/&#34;/g,'"').replace(/&amp;/g,"&"),n=t.match(/["'](c_[a-z0-9_-]{8,})["']/i);if(n&&n[1])return it(n[1]);const o=t.match(/\/app\/(?:c_)?([a-z0-9_-]{8,})/i);return o&&o[1]?it(o[1]):null}function qe(e){return e?e.matches?.('a[href*="/app/"]')?e:e.querySelector?.('a[href*="/app/"]')||null:null}function K(e){if(!e)return null;const t=e.getAttribute?.("jslog"),n=st(t||"");if(n)return n;const o=e.querySelector?.('[jslog*="BardVeMetadataKey"], a[jslog]'),r=st(o?.getAttribute("jslog")||"");if(r)return r;const i=qe(e),a=st(i?.getAttribute("href")||"");if(a)return a;const d=e.getAttribute?.("data-test-id")||e.getAttribute?.("data-testid");return d&&d.startsWith("conversation_c_")?it(d.substring(13)):null}function Ae(e,t="Untitled conversation"){if(!e)return t;let o=e.querySelector?.(".conversation-title, .title-text, .label-and-badge, .title")?.textContent?.trim();if(!o){const r=qe(e);o=r?.getAttribute("aria-label")||r?.textContent?.trim()}return o||(o=e.textContent?.trim()),o=(o||t).replace(/\s+/g," ").trim(),o||t}function Xt(e,t=null){const n=w.chatMetadata?w.chatMetadata[e]:null;if(n?.url)return n.url.startsWith("http")?n.url:`https://gemini.google.com${n.url.startsWith("/")?"":"/"}${n.url}`;const r=qe(t)?.getAttribute("href");if(r)return r.startsWith("http")?r:`https://gemini.google.com${r.startsWith("/")?"":"/"}${r}`;const i=e&&e.startsWith("c_")?e.substring(2):e;return i?`https://gemini.google.com/app/${i}`:null}function Z(){const e=['conversations-list [data-test-id="conversation"]','conversations-list [data-testid="conversation"]','conversations-list gem-nav-list-item a[href*="/app/"]','[role="navigation"] [data-test-id="conversation"]','[role="navigation"] a[href*="/app/"]'],t=[];return e.forEach(n=>{try{document.querySelectorAll(n).forEach(o=>{const r=o.matches?.('a[href*="/app/"]')&&o.closest('[data-test-id="conversation"], [data-testid="conversation"], gem-nav-list-item, [role="listitem"], li')||o;r&&!t.includes(r)&&K(r)&&t.push(r)})}catch{}}),t}function Jt(e){if(!e)return!1;if(e.querySelector('mat-icon[fonticon="push_pin"], .conversation-pin-icon'))return!0;const n=e.querySelector(".cdk-visually-hidden");return!!(n&&n.textContent&&n.textContent.toLowerCase().includes("pinned")||[e.getAttribute("jslog"),...Array.from(e.querySelectorAll?.("[jslog]")||[]).map(r=>r.getAttribute("jslog"))].filter(Boolean).map(r=>r.replace(/&quot;/g,'"')).some(r=>/\["[^"]+",null,1(?:,|\])/.test(r)))}function Xo(e){if(!e||e.length<7)return"var(--gf-text-primary)";const t=parseInt(e.slice(1,3),16),n=parseInt(e.slice(3,5),16),o=parseInt(e.slice(5,7),16);return(t*299+n*587+o*114)/1e3>155?"#000000":"#FFFFFF"}function Me(){const e=document.body,t=document.documentElement;if(e.classList.contains("dark-theme")||e.classList.contains("dark_mode_toggled")||e.classList.contains("dark-mode")||e.classList.contains("dark"))return"dark";if(e.classList.contains("light-theme")||e.classList.contains("light-mode")||e.classList.contains("light"))return"light";const n=t.getAttribute("data-theme");if(n==="dark")return"dark";if(n==="light")return"light";const o=window.getComputedStyle(e).backgroundColor;if(o&&o!=="rgba(0, 0, 0, 0)"&&o!=="transparent"){const r=o.match(/\d+/g);if(r&&r.length>=3)return(parseInt(r[0])*299+parseInt(r[1])*587+parseInt(r[2])*114)/1e3<128?"dark":"light"}return window.matchMedia&&window.matchMedia("(prefers-color-scheme: dark)").matches?"dark":"light"}function Qt(){if(!u)return;const e=document.createElement("style");if(e.textContent=`
            :host { 
                /* Active theme variables - will be dynamically updated */
                --gf-bg-primary: #272A2C;
                font-family: 'Google Sans', 'Roboto', sans-serif;
                --gf-bg-secondary: #1E2124;
                --gf-text-primary: #E3E3E3;
                --gf-text-secondary: #C2C2C2;
                --gf-border-color: #404040;
                --gf-hover-bg: #3A3D40;
                --gf-accent-primary: #8AB4F8;
                --gf-accent-danger: #F28B82;
                --gf-accent-success: #34A853;
                --gf-accent-warning: #FFA726;
                --gf-bg-input: #1E2124;
                
                /* Overlays and Shadows */
                --gf-overlay-bg: rgba(0, 0, 0, 0.6);
                --gf-overlay-bg-medium: rgba(0, 0, 0, 0.5);
                --gf-overlay-bg-light: rgba(0, 0, 0, 0.3);
                --gf-shadow-sm: 0 2px 4px rgba(0, 0, 0, 0.1);
                --gf-shadow-md: 0 4px 12px rgba(0, 0, 0, 0.15);
                --gf-shadow-lg: 0 8px 32px rgba(0, 0, 0, 0.3);
                --gf-shadow-xl: 0 16px 48px rgba(0, 0, 0, 0.4);
                --gf-text-tertiary: #9CA3AF;
                --gf-white: #FFFFFF;
                
                /* ONE MODAL SHELL TO RULE THEM ALL */
                --modal-width: 560px;
                --modal-radius: 12px;
                --modal-padding: 32px;
                --modal-shadow: 0 4px 24px rgba(0, 0, 0, 0.18);
                --modal-footer-gap: 24px;
                
                /* Animation System */
                --anim-instant: 50ms;
                --anim-fast: 150ms;
                --anim-normal: 200ms;
                --anim-medium: 300ms;
                --anim-slow: 500ms;
                --ease-out: cubic-bezier(0.25, 0.46, 0.45, 0.94);
                --ease-in-out: cubic-bezier(0.42, 0, 0.58, 1);
                --ease-elastic: cubic-bezier(0.34, 1.56, 0.64, 1);
                
                /* TYPOGRAPHY & COLOR HIERARCHY */
                --title-size: 20px;
                --title-weight: 500;  /* Standardized from 600 */
                --title-top-padding: 24px;
                --body-size: 14px;
                --body-weight: 400;
                --button-size: 14px;
                --button-weight: 500;
                
                /* Typography System */
                --font-size-h2: 20px;
                --font-size-h3: 16px;
                --font-size-h4: 14px;
                --font-size-body: 14px;
                --font-size-small: 13px;
                --font-size-tiny: 12px;
                --font-size-badge: 11px;
                --font-weight-normal: 400;
                --font-weight-medium: 500;
                --font-weight-semibold: 600;
                
                /* LISTS: ONE ROW SPEC */
                --row-height: var(--space-12);
                --row-padding: var(--space-3) var(--space-4);
                --list-border: #E2E8F0;
                --hover-bg-subtle: rgba(0, 0, 0, 0.04);
                
                /* Spacing System (8-point grid) */
                --space-0: 0px;
                --space-1: 4px;   /* Minimal */
                --space-2: 8px;   /* Tight */
                --space-3: 12px;  /* Compact */
                --space-4: 16px;  /* Default */
                --space-5: 20px;  /* Medium */
                --space-6: 24px;  /* Large */
                --space-8: 32px;  /* Extra large */
                --space-10: 40px; /* Huge */
                --space-12: 48px; /* Massive */
                --space-16: 64px; /* Giant */
                
                /* Component-specific spacing */
                --modal-header-padding: var(--space-6) var(--space-6) var(--space-4) var(--space-6);
                --modal-body-padding: 0 var(--space-6) var(--space-6) var(--space-6);
                --modal-footer-padding: var(--space-4) var(--space-6) var(--space-6) var(--space-6);
                --button-padding-x: var(--space-6);
                --button-padding-y: var(--space-3);
                --button-padding-small: var(--space-2) var(--space-4);
                --input-padding: var(--space-3) var(--space-4);
                --gap-small: var(--space-2);
                --gap-medium: var(--space-3);
                --gap-large: var(--space-4);
                --gap-xl: var(--space-6);
                
                /* FOOTER GRID & BUTTONS */
                --btn-primary-min: 100px;
                --btn-secondary-min: 100px;
                --btn-gap: 8px;
                
                /* INTERACTION STATES */
                --focus-ring: 0 0 0 2px var(--gf-accent-primary);
                --animation-duration: var(--anim-fast);
                --disabled-opacity: 0.6;
                --hover-opacity: 0.9;
                
                /* CLOSE BUTTON */
                --close-btn-size: 32px;
                --close-btn-padding: 8px;
            }
            .sidebar-tab { 
                display: flex; align-items: center; gap: var(--gap-medium);
                padding: 10px; margin: 4px 0; border-radius: var(--space-2);
                cursor: pointer; font-size: 14px; color: var(--gf-text-primary);
                position: relative;
            }
            /* Full-row hover for the banner, and keep highlighted while menu is open */
            .sidebar-tab:hover,
            .sidebar-tab:has(#gemini-toolbox-btn[aria-expanded="true"]) {
                background-color: var(--gf-hover-bg);
                border-radius: var(--space-2);
            }

            /* Gemini Toolbox Button and Dropdown */
.toolbox-button {
                display: flex; align-items: center; gap: 8px; flex-wrap: nowrap;
                width: 100%; padding: 0; border: none; background: none;
                cursor: pointer; font-size: 14px; color: var(--gf-text-primary);
            }
.toolbox-button:hover { background: transparent; }
.toolbox-button:focus {
                outline: none;
                box-shadow: inset 0 0 0 2px var(--gf-accent-primary);
            }
            /* Hide banner focus ring while menu is expanded */
            .toolbox-button[aria-expanded="true"] {
                box-shadow: none !important;
            }
            .toolbox-button:focus:not(:focus-visible) {
                box-shadow: none;
            }

            .dropdown-arrow {
                margin-left: auto;
                transition: transform var(--anim-normal) var(--ease-out);
            }
            .dropdown-arrow.rotated {
                transform: rotate(180deg);
            }

            .toolbox-dropdown {
                position: absolute;
                top: 100%;
                left: 0;
                right: 0;
                min-width: 200px;
                background-color: var(--gf-bg-primary);
                border: 1px solid var(--gf-border-color);
                border-radius: var(--space-2);
                margin-top: 4px;
                padding: 4px 0;
                box-shadow: 
                    var(--gf-shadow-md),
                    var(--gf-shadow-sm),
                    inset 0 0 0 1px rgba(255, 255, 255, 0.04);
                z-index: 2147483647;
                max-height: 60vh;
                overflow-y: auto;
                opacity: 0;
                transform: translateY(-8px);
                transition: 
                    opacity var(--anim-fast) var(--ease-out),
                    transform var(--anim-fast) var(--ease-out),
                    box-shadow var(--anim-fast) var(--ease-out);
                pointer-events: none;
            }
            .toolbox-dropdown.show {
                opacity: 1;
                transform: translateY(0);
                pointer-events: auto;
            }

            
            /* Responsive dropdown adjustments */
            @media (max-width: 400px) {
                .toolbox-dropdown {
                    min-width: 180px;
                    font-size: 14px;
                }
                
                .dropdown-item {
                    padding: 12px 14px;
                }
                
                .dropdown-shortcut {
                    display: none;
                }
            }

            .dropdown-group {
                padding: 0;
            }
            .dropdown-group-label {
                padding: var(--space-2) var(--space-4) 6px var(--space-4);
                font-size: 10px;
                font-weight: 600;
                text-transform: uppercase;
                letter-spacing: 1px;
                color: var(--gf-text-tertiary);
                opacity: 1;
                min-height: 32px;
                display: flex;
                align-items: center;
            }
            .dropdown-divider {
                height: 1px;
                background-color: var(--gf-border-color);
                margin: 4px 0;
                opacity: 0.2;
            }
            .dropdown-item {
                display: grid;
                grid-template-columns: 16px 1fr auto auto;
                align-items: center;
                gap: 6px;
                padding: var(--space-3) var(--space-4);
                cursor: pointer;
                color: var(--gf-text-primary);
                font-size: 13px;
                transition: background-color var(--anim-fast) var(--ease-out), transform var(--anim-instant) var(--ease-out);
                position: relative;
                min-height: 48px;
                box-sizing: border-box;
            }
            .dropdown-item:hover {
                background-color: var(--gf-hover-bg);
                transition: background-color var(--anim-instant) var(--ease-out);
            }
            .dropdown-item:focus {
                outline: none;
                background-color: var(--gf-hover-bg);
                box-shadow: inset 0 0 0 2px var(--gf-accent-primary);
            }
            .dropdown-item:focus:not(:focus-visible) {
                box-shadow: none;
            }
            .dropdown-item:active {
                transform: scale(0.98);
                background-color: var(--gf-active-bg, rgba(255, 255, 255, 0.1));
                transition: transform var(--anim-instant) var(--ease-out);
            }
            .dropdown-icon {
                opacity: 0.7;
                transition: opacity var(--anim-normal) var(--ease-out);
                flex-shrink: 0;
                display: flex;
                align-items: center;
                justify-content: center;
                width: 16px;
                height: 16px;
            }
            .dropdown-item:hover .dropdown-icon {
                opacity: 1;
            }
            .dropdown-item.destructive {
                color: var(--gf-accent-danger);
            }
            .dropdown-item.destructive .dropdown-icon {
                color: var(--gf-accent-danger);
            }
            .dropdown-item.destructive:hover {
                background-color: rgba(255, 101, 101, 0.1);
            }
            .dropdown-group:first-child .dropdown-item:first-of-type {
                padding-top: 6px;
            }
            .dropdown-badge {
                margin-left: auto;
                margin-right: var(--space-2);
                padding: 2px 6px;
                font-size: 11px;
                font-weight: 600;
                background-color: var(--gf-badge-bg, rgba(255, 255, 255, 0.1));
                color: var(--gf-text-secondary);
                border-radius: 10px;
                min-width: 18px;
                text-align: center;
                display: none;
            }
            .dropdown-badge:not(:empty) {
                display: inline-block;
            }
            .dropdown-shortcut {
                margin-left: 8px;
                padding: 2px 6px;
                font-size: 10px;
                font-weight: var(--font-weight-medium);
                font-family: 'SF Mono', 'Roboto Mono', 'Menlo', monospace;
                background-color: var(--gf-keycap-bg, rgba(255, 255, 255, 0.05));
                color: var(--gf-text-tertiary);
                border: 1px solid var(--gf-keycap-border, rgba(255, 255, 255, 0.06));
                border-radius: 2px;
                letter-spacing: 0.2px;
                white-space: nowrap;
                display: inline-flex;
                align-items: center;
                justify-content: center;
                min-width: 24px;
                height: 16px;
                box-sizing: border-box;
            }
            .dropdown-badge:empty + .dropdown-shortcut {
                margin-left: auto;
            }
            
            /* Responsive adjustments for narrow sidebars */
            /* Mobile Touch Target Improvements */
            @media (hover: none) and (pointer: coarse) {
                /* Increase touch targets for mobile */
                .button, .primary, .secondary, .danger {
                    min-height: 48px;
                    min-width: 48px;
                }
                
                .icon-btn, .modal-close {
                    width: 48px;
                    height: 48px;
                }
                
                .dropdown-item {
                    min-height: 48px;
                    padding: var(--input-padding);
                }
                
                .list-item {
                    min-height: 56px;
                }
                
                input[type="text"], input[type="search"] {
                    min-height: 48px;
                    font-size: 16px; /* Prevent zoom on iOS */
                }
            }
            
            /* Responsive Design */
            @media (max-width: 768px) {
                .gemini-modal-content {
                    width: 95%;
                    max-width: none;
                    max-height: 90vh;
                    margin: 10px;
                }
                
                .modal-header {
                    padding: 16px 16px 12px 16px;
                }
                
                .modal-body {
                    padding: var(--space-4);
                }
                
                .modal-footer {
                    padding: 12px 16px 16px 16px;
                    flex-wrap: wrap;
                    gap: 8px;
                    min-height: 64px;
                }
                
                .modal-footer button {
                    flex: 1;
                    min-width: 100px;
                }
                
                /* Stack buttons on very small screens */
                @media (max-width: 480px) {
                    .modal-footer {
                        flex-direction: column;
                    }
                    
                    .modal-footer button {
                        width: 100%;
                    }
                }
            }
            
            @media (max-width: 320px) {
                .dropdown-shortcut {
                    display: none;
                }
                .dropdown-item span {
                    white-space: nowrap;
                    overflow: hidden;
                    text-overflow: ellipsis;
                }
                
                /* Reduce font sizes on very small screens */
                .modal-header h2 {
                    font-size: var(--text-lg);
                }
                
                .button {
                    font-size: 13px;
                    padding: 10px 16px;
                    min-height: 40px;
                }
            }

            /* Modal Backdrop - Lighter opacity for better context */
            .infi-chatgpt-modal {
                position: fixed; top: 0; left: 0; width: 100vw; height: 100vh;
                background-color: var(--gf-overlay-bg-medium);
                z-index: 9999;
                display: flex; align-items: center; justify-content: center;
                backdrop-filter: blur(2px); /* Subtle blur for context */
                opacity: 0;
                animation: modalFadeIn 140ms ease-out forwards;
            }
            @keyframes modalFadeIn {
                from {
                    opacity: 0;
                }
                to {
                    opacity: 1;
                }
            }
            .infi-chatgpt-modal.closing {
                animation: modalFadeOut 90ms ease-in forwards;
            }
            @keyframes modalFadeOut {
                from {
                    opacity: 1;
                }
                to {
                    opacity: 0;
                }
            }

            /* Blocking Modal - Stronger overlay for operations in progress */
            .infi-chatgpt-modal.modal-blocking {
                background-color: var(--gf-overlay-bg);
                backdrop-filter: blur(4px);
                cursor: wait;
            }
            
            .infi-chatgpt-modal.modal-blocking .modal-content {
                pointer-events: auto;
            }

            /* Modal Content Box - ONE MODAL SHELL TO RULE THEM ALL */
            .modal-content {
                width: var(--modal-width);
                background-color: var(--gf-bg-secondary);
                border-radius: var(--modal-radius);
                border: 1px solid var(--gf-border-color);
                box-shadow: var(--modal-shadow);
                color: var(--gf-text-primary);
                display: flex; flex-direction: column;
                max-height: 80vh;
                transform: scale(0.98);
                animation: modalScaleIn 140ms ease-out forwards;
            }
            
            /* Fixed size for manage-single-folder modal for premium feel */
            #manage-single-folder-modal .modal-content,
            .modal-content.modal-manage-single-folder-modal {
                width: 640px !important;
                min-height: 480px !important;
                max-height: 72vh !important;
                display: flex !important;
                flex-direction: column !important;
            }
            
            #manage-single-folder-modal .modal-body {
                flex: 1 1 auto !important;
                overflow-y: auto !important;
                min-height: 0 !important;
            }
            
            /* Ensure non-prompt-library modals maintain their original size */
            .modal-content.modal-add-folder-modal,
            .modal-content.modal-edit-folder-modal,
            .modal-content.modal-delete-folder-modal {
                min-height: auto !important;
                height: auto !important;
            }
            
            /* Add chats modal needs more vertical space */
            .modal-content.modal-add-chats-modal {
                min-height: auto !important;
                height: auto !important;
                max-height: 90vh !important;
            }
            
            /* Reduce padding for add chats modal to maximize chat list space */
            #add-chats-modal .modal-body {
                padding: 12px 24px !important;
                gap: 8px !important;
            }
            
            .modal-content.modal-upgrade-modal {
                min-height: auto !important;
                height: auto !important;
                max-height: 90vh !important;
                max-width: 650px !important;
                background: var(--gf-bg-primary) !important;
            }
            
            .modal-upgrade-modal .button.button-ghost {
                background: transparent;
                border: none;
                color: var(--gf-text-tertiary);
                transition: opacity 0.2s;
            }
            
            .modal-upgrade-modal .button.button-ghost:hover {
                opacity: 0.7;
                background: transparent;
            }

            
            /* Specific height for manage folders to prevent expansion */
            .modal-content.modal-manage-folders-modal {
                height: 85vh !important;
                max-height: 85vh !important;
                min-height: 600px !important;
            }
            
            /* Override any prompt library styles on other modals */
            #manage-folders-modal .modal-content {
                height: 85vh !important;
                max-height: 85vh !important;
                min-height: 600px !important;
            }
            
            /* More specific override for all non-prompt-library modals (excluding manage-single-folder and manage-folders) */
            .infi-chatgpt-modal:not(#prompt-library-modal):not(#manage-single-folder-modal):not(#manage-folders-modal) .modal-content {
                min-height: auto !important;
                height: auto !important;
            }
            @keyframes modalScaleIn {
                from {
                    transform: scale(0.98);
                    opacity: 0;
                }
                to {
                    transform: scale(1);
                    opacity: 1;
                }
            }
            .modal-header {
                display: flex; justify-content: space-between; align-items: center;
                padding: 24px 24px 16px 24px; /* Standardized: 24px top, 24px sides, 16px bottom */
                border-bottom: 1px solid var(--gf-border-color);
            }
            .modal-header h2 { 
                margin: 0; 
                font-size: var(--font-size-h2); 
                font-weight: var(--font-weight-medium); 
                font-family: 'Google Sans', 'Roboto', sans-serif;
                color: var(--gf-text-primary);
                flex-grow: 1;
            }
            .modal-close {
                width: 36px; height: 36px;
                padding: var(--space-2);
                border: none; background: none;
                border-radius: 6px;
                cursor: pointer;
                display: flex; align-items: center; justify-content: center;
                color: var(--gf-text-secondary);
                transition: all var(--anim-normal) var(--ease-out);
                margin-left: 16px;
                box-sizing: border-box;
            }
            .modal-close:hover {
                background-color: var(--gf-hover-bg);
                color: var(--gf-text-primary);
            }
            .modal-close:focus {
                outline: none;
                box-shadow: 0 0 0 3px rgba(138, 180, 248, 0.3);
            }
            .modal-close:focus:not(:focus-visible) {
                box-shadow: none;
            }
            .modal-close svg {
                width: 20px; height: 20px;
            }
            .modal-body { 
                padding: 24px; 
                display: flex; flex-direction: column;
                flex-grow: 1;
                overflow-y: auto;
                gap: 16px; /* 8pt grid spacing */
                font-family: 'Google Sans', 'Roboto', sans-serif;
            }
            .modal-footer {
                padding: 16px 24px 24px 24px; /* Standardized: 16px top, 24px sides, 24px bottom */
                margin-top: var(--modal-footer-gap);
                border-top: 1px solid var(--gf-border-color);
                display: flex;
                justify-content: space-between;
                align-items: center;
                gap: 16px;
                min-height: 72px; /* Ensure consistent footer height */
                box-sizing: border-box;
            }
            .modal-actions {
                display: flex;
                gap: var(--gap-medium);
                margin-left: auto; /* Push actions to right */
                align-items: center;
            }
            
            /* Footer Grid System */
            .modal-footer.footer-grid {
                display: grid;
                grid-template-columns: 1fr auto;
                align-items: center;
            }
            
            .modal-footer.footer-center {
                justify-content: center;
            }
            
            .modal-footer.footer-spread {
                justify-content: space-between;
            }
            
            /* Footer with left-aligned content */
            .footer-left-content {
                display: flex;
                align-items: center;
                gap: 16px;
                flex-wrap: nowrap; /* keep on one line */
            }
            
            /* Checkbox styling */
            .select-all-checkbox,
            .bulk-delete-checkbox,
            .export-chat-checkbox {
                width: 20px;
                height: 20px;
                accent-color: var(--gf-accent-primary);
                cursor: pointer;
                margin: 0;
                flex-shrink: 0;
            }
            
            .select-all-label {
                display: flex;
                align-items: center;
                gap: 8px;
                cursor: pointer;
                color: var(--gf-accent-primary);
                font-weight: 500;
                font-size: 14px;
                user-select: none;
                white-space: nowrap;    /* prevent Select + All from wrapping */
                line-height: 1;         /* align to baseline nicely */
            }
            
            .select-all-label:hover {
                opacity: 0.8;
            }
            
            .select-all-counter {
                color: var(--gf-text-secondary);
                font-size: 14px;
                margin-left: 8px;
                white-space: nowrap;   /* keep 0 selected on one line */
                line-height: 1;
            }
            
            /* Protected foldered chats styles */
            .bulk-delete-item.foldered-protected {
                opacity: 0.6;
            }
            
            .bulk-delete-item.foldered-protected .bulk-delete-checkbox {
                pointer-events: none;
                opacity: 0.5;
            }
            
            .bulk-delete-item .protected-badge {
                font-size: 11px;
                padding: 2px 6px;
                border-radius: 10px;
                background: var(--gf-hover-bg);
                color: var(--gf-text-secondary);
                margin-left: 8px;
                font-weight: 500;
            }
             .infi-chatgpt-manageTabs-content {
                display: flex; flex-direction: column;
                height: 100%;
            }
            #folder-list-container {
                flex-grow: 1;
                overflow-y: auto;
                margin-top: var(--space-4);
            }
             .infi-chatgpt-manageTabs-buttonsContainer {
                margin-top: auto; /* Pushes to the bottom */
                padding-top: 16px;
                text-align: right;
            }
            /* Base Button System */
            .button {
                /* Reset & Core */
                border: none;
                border-radius: var(--space-2);
                cursor: pointer;
                font-family: 'Google Sans', 'Roboto', sans-serif;
                font-size: 14px;
                font-weight: 500;
                text-decoration: none;
                white-space: nowrap;
                user-select: none;
                box-sizing: border-box;
                
                /* Layout */
                display: inline-flex;
                align-items: center;
                justify-content: center;
                gap: var(--gap-small);
                
                /* Sizing - Default large */
                padding: var(--button-padding-y) var(--button-padding-x);
                min-height: var(--space-12);
                min-width: var(--space-12);
                
                /* Animation */
                transition: all var(--anim-normal) var(--ease-out);
                position: relative;
                overflow: hidden;
                
                /* Default appearance (secondary) */
                background-color: transparent;
                color: var(--gf-text-primary);
                border: 1px solid var(--gf-border-color);
            }
            
            /* Button hover states */
            .button:hover:not(:disabled) {
                transform: translateY(-1px);
                box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);
            }
            
            .button:active:not(:disabled) {
                transform: translateY(0);
                box-shadow: none;
            }
            
            /* Focus states */
            .button:focus-visible {
                outline: 2px solid var(--gf-accent-primary);
                outline-offset: 2px;
            }
            
            /* Disabled state */
            .button:disabled {
                opacity: 0.6;
                cursor: not-allowed;
                transform: none !important;
                box-shadow: none !important;
            }
            
            /* Size modifiers */
            .button-small {
                padding: var(--button-padding-small);
                min-height: 36px;
                font-size: 13px;
            }
            
            .button-medium {
                padding: 10px var(--space-5);
                min-height: var(--space-10);
            }
            
            .button-icon {
                padding: var(--space-2);
                min-width: 36px;
                min-height: 36px;
                width: 36px;
                height: 36px;
            }
            
            /* Type modifiers */
            .button.primary {
                background-color: var(--gf-accent-primary);
                color: var(--gf-button-text, var(--gf-white)) !important;
                border-color: transparent;
                min-width: var(--btn-primary-min);
            }
            
            .button.primary:hover:not(:disabled) {
                background-color: var(--gf-accent-primary);
                opacity: 0.9;
            }
            
            .button.primary:focus-visible {
                box-shadow: 0 0 0 3px rgba(66, 133, 244, 0.4);
            }
            
            .button.secondary {
                /* Already default styles */
                min-width: var(--btn-secondary-min);
            }
            
            .button.secondary:hover:not(:disabled) {
                background-color: var(--gf-hover-bg);
            }
            
            .button.secondary:focus-visible {
                box-shadow: 0 0 0 3px rgba(138, 180, 248, 0.3);
                border-color: var(--gf-accent-primary);
            }
            
            .button.danger {
                background-color: var(--gf-accent-danger);
                color: var(--gf-white);
                border-color: transparent;
            }
            
            .button.danger:hover:not(:disabled) {
                background-color: var(--gf-accent-danger);
                opacity: 0.9;
            }
            
            .button.danger:focus-visible {
                box-shadow: 0 0 0 3px rgba(239, 68, 68, 0.4);
            }
            /* Icon button (extends button) */
            .icon-btn {
                /* Inherit from button */
                background: transparent;
                border: none;
                color: var(--gf-text-secondary);
                width: 36px;
                height: 36px;
                min-width: 36px;
                min-height: 36px;
                padding: var(--space-2);
                border-radius: 6px;
                display: inline-flex;
                align-items: center;
                justify-content: center;
                transition: all var(--anim-normal) var(--ease-out);
                cursor: pointer;
                box-sizing: border-box;
            }
            
            .icon-btn:hover:not(:disabled) {
                background-color: var(--gf-hover-bg);
                color: var(--gf-text-primary);
                transform: none; /* Don't lift icon buttons */
            }
            
            .icon-btn:focus-visible {
                outline: 2px solid var(--gf-accent-primary);
                outline-offset: 2px;
            }

            /* Form & List Styles */
            input[type="text"], input[type="search"] {
                width: 100%;
                padding: 8px 16px;
                background-color: var(--gf-bg-input);
                border: 1px solid var(--gf-border-color);
                color: var(--gf-text-primary);
                border-radius: 6px;
                box-sizing: border-box; /* Important */
                font-size: 14px;
                font-family: 'Google Sans', 'Roboto', sans-serif;
                transition: border-color var(--anim-normal) var(--ease-out), box-shadow var(--anim-normal) var(--ease-out);
            }
            input[type="text"]:focus, input[type="search"]:focus {
                outline: none;
                border-color: var(--gf-accent-primary);
                box-shadow: 0 0 0 3px rgba(138, 180, 248, 0.3);
            }
            
            input[type="text"]:focus:not(:focus-visible), 
            input[type="search"]:focus:not(:focus-visible) {
                box-shadow: none;
            }

            /* Select elements consistent with inputs */
            select {
                width: 100%;
                padding: 8px 16px;
                background-color: var(--gf-bg-input);
                border: 1px solid var(--gf-border-color);
                color: var(--gf-text-primary);
                border-radius: 6px;
                box-sizing: border-box;
                font-size: 14px;
                font-family: 'Google Sans', 'Roboto', sans-serif;
                transition: border-color var(--anim-normal) var(--ease-out), box-shadow var(--anim-normal) var(--ease-out);
                appearance: none;
                -webkit-appearance: none;
                -moz-appearance: none;
                background-image: none; /* keep neutral, UI may add arrow if desired */
            }
            select:focus {
                outline: none;
                border-color: var(--gf-accent-primary);
                box-shadow: 0 0 0 3px rgba(138, 180, 248, 0.3);
            }

            /* Format selector layout */
            .format-select {
                display: flex;
                align-items: center;
                gap: 8px;
                margin-left: 12px;
                white-space: nowrap;   /* keep label + control on one line */
                line-height: 1;
            }
            .format-select label {
                font-size: 13px;
                color: var(--gf-text-secondary);
                white-space: nowrap;
            }
            .format-select select {
                height: 36px;          /* normalize control height */
                line-height: 36px;
                padding: 0 12px;
            }
            .list-item {
                display: flex; align-items: center; gap: 10px;
                padding: var(--row-padding); border-radius: 6px; margin-bottom: 4px;
                min-height: var(--row-height);
            }
            .list-item:hover { background-color: var(--gf-hover-bg); }
            .list-item:focus-within {
                outline: 2px solid var(--gf-accent-primary);
                outline-offset: -2px;
            }
            .list-item .item-title {
                flex-grow: 1;
                cursor: pointer;
            }

            /* Make entire chat rows clickable in Add Chats modal */
            .chat-item {
                cursor: pointer;
            }

            .list-item .item-controls {
                display: flex;
                align-items: center;
                gap: 8px;
                color: var(--gf-text-secondary);
            }
            
            .list-item .add-subfolder-btn {
                opacity: 0;
                transition: opacity var(--anim-normal) var(--ease-in-out);
            }
            
            .list-item:hover .add-subfolder-btn {
                opacity: 1;
            }

            .icon-btn {
                background: none;
                border: none;
                cursor: pointer;
                color: var(--gf-text-secondary);
            }

/* --- NEW: Bulk Delete Modal Specific Styles --- */
            /* Export chat compact header/actions/footer to maximize list space */
            #export-chat-modal .premium-modal-header {
                padding: 12px 20px !important;
                min-height: 48px !important;
                flex: 0 0 auto !important;
            }
            #export-chat-modal .premium-modal-actions {
                padding: 8px 20px !important;
                min-height: 48px !important;
                gap: 12px !important;
                flex: 0 0 auto !important;
            }
            #export-chat-modal .premium-modal-footer {
                padding: 12px 20px !important;
                min-height: 56px !important;
                flex: 0 0 auto !important;
            }

            
            /* Export Chat premium layout (scoped to its modal) */
            #export-chat-modal .modal-body {
                flex: 1 1 auto !important;
                display: flex !important;
                flex-direction: column !important;
                overflow-y: hidden !important;
                padding: 0 !important;
                gap: 0 !important;
                min-height: 0 !important;
            }
#export-chat-modal .premium-modal-body {
                flex: 1 1 auto;
                display: flex;
                flex-direction: column;
                overflow-y: hidden;
                padding: 12px 20px;
                gap: 0;
                min-height: 0;
            }
#export-chat-modal #export-chat-list {
                flex: 1 1 auto;
                overflow-y: auto;
                margin: 0;
                padding: 0 8px 0 0; /* slim scrollbar space */
                background: transparent;
                border: none;
                min-height: 0;
            }
            
            /* Compact row style for Export (mirror Bulk Delete) */
            #export-chat-modal .bulk-delete-item {
                display: flex;
                align-items: center;
                gap: 12px !important;
                padding: 12px 12px !important;
                min-height: 48px !important;
                border-radius: 8px;
                background: transparent;
                border: none;
box-shadow: inset 0 -1px 0 color-mix(in srgb, var(--gf-border-color) 35%, transparent);
                transition: background 120ms ease, box-shadow 120ms ease;
            }
            #export-chat-modal .bulk-delete-item:hover {
                background: var(--gf-hover-bg);
            }
            #export-chat-modal .bulk-delete-item:last-child {
                box-shadow: none;
            }
            #export-chat-modal .bulk-delete-item:has(.bulk-delete-checkbox:checked) {
                background: color-mix(in srgb, var(--gf-accent-primary) 10%, transparent);
                box-shadow:
                    inset 3px 0 0 var(--gf-accent-primary),
                    inset 0 -1px 0 color-mix(in srgb, var(--gf-border-color) 20%, transparent);
            }
            
            /* Keep boxed style only if used outside export modal (legacy) */
            .legacy-export-chat-list {
                margin-top: var(--space-4);
                max-height: 400px;
                overflow-y: auto;
                padding-right: 10px; /* For scrollbar */
                scroll-behavior: smooth;
                background-color: var(--gf-bg-secondary);
                border: 1px solid var(--gf-border-color);
                border-radius: var(--space-2);
                padding: var(--space-2);
            }
            /* Bulk Delete list fills the body; only this scrolls */
            #bulk-delete-list {
                flex: 1 1 auto;
                max-height: none !important;
                overflow-y: auto;
                overflow-x: hidden;
                padding-right: 10px; /* For scrollbar */
                margin-top: var(--space-2);
                padding: 0;
                background: transparent;
                border: none;
                border-radius: 0;
                box-sizing: border-box;
            }
            /* Footer controls inside body should not shrink */
            #bulk-delete-controls {
                flex-shrink: 0;
                margin-top: var(--space-4);
            }
            .bulk-delete-item {
                display: flex;
                align-items: center;
                padding: var(--row-padding);
                border-radius: 8px;
                margin-bottom: 6px;
                min-height: var(--row-height);
                transition: all var(--anim-fast) var(--ease-out);
                gap: var(--gap-medium);
                background-color: var(--gf-bg-secondary);
                border: 1px solid transparent;
            }
            .bulk-delete-item:hover {
                background-color: var(--gf-hover-bg);
                border-color: var(--gf-border-color);
            }
            .bulk-delete-item:has(.bulk-delete-checkbox:checked) {
                border-color: var(--gf-accent-primary);
                box-shadow: 0 0 0 2px rgba(138, 180, 248, 0.35);
                background-color: var(--gf-bg-secondary);
            }
            .bulk-delete-item:focus-within {
                border-color: var(--gf-accent-primary);
                box-shadow: 0 0 0 2px rgba(138, 180, 248, 0.35);
            }
            #bulk-delete-search:focus {
                border-color: var(--gf-accent-primary) !important;
                box-shadow: 0 0 0 2px rgba(138, 180, 248, 0.2) !important;
            }
            .bulk-delete-item input[type="checkbox"] {
                margin-right: 12px;
                width: 18px;
                height: 18px;
            }
            .bulk-delete-item .item-title {
                font-size: 14px;
                font-weight: 400;
                color: var(--gf-text-primary);
                white-space: nowrap;
                overflow: hidden;
                text-overflow: ellipsis;
            }
             #bulk-delete-controls {
                padding-top: 16px;
                border-top: 1px solid var(--gf-border-color);
                display: flex;
                justify-content: space-between;
                align-items: center;
            }
            #bulk-delete-select-all-container {
                display: flex;
                align-items: center;
            }
             #bulk-delete-status {
                font-size: 14px;
                color: var(--gf-text-secondary);
            }
            #bulk-delete-search-container {
                margin-bottom: var(--space-4);
            }
            #bulk-delete-search {
                transition: border-color var(--anim-normal) var(--ease-out), box-shadow var(--anim-normal) var(--ease-out);
            }
            
            /* Premium Modal Styles */
            .modal-content.modal-manage-folders-modal {
                width: min(800px, 92vw) !important;
                max-width: 800px !important;
                height: 85vh !important;
                min-height: 600px !important;
                max-height: 85vh !important;
                display: flex !important;
                flex-direction: column !important;
                padding: 0 !important;
                border-radius: 16px !important;
                box-shadow: 
                    0 20px 25px -5px rgba(0, 0, 0, 0.1),
                    0 10px 10px -5px rgba(0, 0, 0, 0.04),
                    0 0 0 1px rgba(0, 0, 0, 0.05) !important;
                overflow: hidden !important;
            }

            /* Fixed shell for Bulk Delete modal (same guardrails as folders) */
            .modal-content.modal-bulk-delete-modal {
                width: min(800px, 92vw) !important;
                max-width: 800px !important;
                height: 85vh !important;
                min-height: 600px !important;
                max-height: 85vh !important;
                display: flex !important;
                flex-direction: column !important;
                padding: 0 !important;
                border-radius: 16px !important;
                overflow: hidden !important;
            }

            /* Fixed shell for Export Chat modal */
            .modal-content.modal-export-chat-modal {
                width: min(800px, 92vw) !important;
                max-width: 800px !important;
                height: 85vh !important;
                min-height: 600px !important;
                max-height: 85vh !important;
                display: flex !important;
                flex-direction: column !important;
                padding: 0 !important;
                border-radius: 16px !important;
                overflow: hidden !important;
            }
            #export-chat-modal .modal-content.modal-export-chat-modal {
                height: 85vh !important;
                max-height: 85vh !important;
                min-height: 600px !important;
            }

            /* Fixed shell for Settings modal */
            .modal-content.modal-settings-modal {
                width: min(800px, 92vw) !important;
                max-width: 800px !important;
                height: 85vh !important;
                min-height: 600px !important;
                max-height: 85vh !important;
                display: flex !important;
                flex-direction: column !important;
                padding: 0 !important;
                border-radius: 16px !important;
                overflow: hidden !important;
            }
            #settings-modal .modal-header {
                padding: 16px 24px !important;
                min-height: 56px !important;
                border-bottom: 1px solid var(--gf-border-color);
                flex: 0 0 auto;
            }
            #settings-modal .modal-body {
                flex: 1 1 auto !important;
                overflow-y: auto !important;
                min-height: 0 !important;
                padding: 16px 24px !important;
            }

            /* Highest specificity to lock Bulk Delete modal size */
            #bulk-delete-modal .modal-content.modal-bulk-delete-modal {
                height: 85vh !important;
                max-height: 85vh !important;
                min-height: 600px !important;
            }

            /* Make only the list scroll within Bulk Delete */
            #bulk-delete-modal .modal-body,
            #bulk-delete-modal .premium-modal-body {
                flex: 1 1 auto !important;
                display: flex !important;
                flex-direction: column !important;
                overflow-y: hidden !important;
                overflow-x: hidden !important;
                min-height: 0 !important;
                padding: 16px 24px !important; /* compact vertical padding */
                gap: 12px !important;
            }

            /* Bulk Delete compact layout overrides (scoped) */
            #bulk-delete-modal .premium-modal-header {
                padding: 16px 24px !important;
                min-height: 56px !important;
            }
            #bulk-delete-modal .premium-modal-actions {
                padding: 12px 24px !important;
                min-height: 56px !important;
                gap: 12px !important;
            }
            #bulk-delete-modal .premium-modal-footer {
                padding: 16px 24px !important;
                min-height: 64px !important;
            }
            #bulk-delete-modal .premium-search-input { 
                max-width: none !important; /* allow full-width search when space allows */
            }
            #bulk-delete-modal #bulk-delete-list {
                margin-top: 0 !important;
                padding-right: 8px; /* slimmer scrollbar space */
            }
            
            /* Compact row style for Bulk Delete only */
            #bulk-delete-modal .bulk-delete-item {
                display: flex;
                align-items: center;
                gap: 12px !important;
                padding: 12px 12px !important; /* 12px vertical */
                min-height: 48px !important;       /* 48px row height */
                border-radius: 8px;
                background: transparent;
                border: none;
                box-shadow: inset 0 -1px 0 color-mix(in srgb, var(--gf-border-color) 35%, transparent);
                transition: background 120ms ease, box-shadow 120ms ease;
            }
            #bulk-delete-modal .bulk-delete-item:hover {
                background: var(--gf-hover-bg);
            }
            #bulk-delete-modal .bulk-delete-item:last-child {
                box-shadow: none; /* no separator on last row */
            }
            
            /* Selected state: tint + left accent */
            #bulk-delete-modal .bulk-delete-item:has(.bulk-delete-checkbox:checked) {
                background: color-mix(in srgb, var(--gf-accent-primary) 10%, transparent);
                box-shadow:
                    inset 3px 0 0 var(--gf-accent-primary),
                    inset 0 -1px 0 color-mix(in srgb, var(--gf-border-color) 20%, transparent);
            }
            
            .dark-theme .modal-content.modal-manage-folders-modal {
                box-shadow: 
                    0 20px 25px -5px rgba(0, 0, 0, 0.3),
                    0 10px 10px -5px rgba(0, 0, 0, 0.2),
                    0 0 0 1px rgba(255, 255, 255, 0.1) !important;
            }
            
            /* Ensure modal maintains consistent size */
            .modal-content.modal-manage-folders-modal * {
                box-sizing: border-box;
            }
            
            /* Highest specificity to lock modal size */
            #manage-folders-modal .modal-content.modal-manage-folders-modal {
                height: 85vh !important;
                max-height: 85vh !important;
                min-height: 600px !important;
                display: flex !important;
                flex-direction: column !important;
            }
            
            /* Premium Modal Header */
            .premium-modal-header {
                display: flex;
                align-items: center;
                justify-content: space-between;
                padding: 24px 28px;
                border-bottom: 1px solid var(--gf-border-color);
                flex: 0 0 auto;
                min-height: 72px;
            }
            
            .premium-modal-title {
                font-size: 20px;
                font-weight: 600;
                color: var(--gf-text-primary);
                margin: 0;
                font-family: 'Google Sans', -apple-system, BlinkMacSystemFont, sans-serif;
            }
            
            .premium-modal-close {
                width: 36px;
                height: 36px;
                padding: 0;
                border: none;
                background: transparent;
                color: var(--gf-text-secondary);
                cursor: pointer;
                border-radius: 8px;
                display: flex;
                align-items: center;
                justify-content: center;
                transition: all 0.14s ease-out;
            }
            
            .premium-modal-close:hover {
                background: var(--gf-hover-bg);
                color: var(--gf-text-primary);
            }
            
            .premium-modal-close svg {
                width: 20px;
                height: 20px;
            }
            
            /* Premium Modal Actions Bar */
            .premium-modal-actions {
                display: flex;
                align-items: center;
                gap: 16px;
                padding: 24px 28px;
                border-bottom: 1px solid var(--gf-border-color);
                flex: 0 0 auto;
                background: var(--gf-bg-primary);
                min-height: 76px;
            }
            
            /* Premium Button Styles */
            .premium-button {
                padding: 10px 20px;
                border-radius: 10px;
                font-size: 14px;
                font-weight: 500;
                border: none;
                cursor: pointer;
                display: inline-flex;
                align-items: center;
                gap: 8px;
                transition: all 0.14s ease-out;
                font-family: 'Google Sans', -apple-system, BlinkMacSystemFont, sans-serif;
                white-space: nowrap;
            }
            
            .premium-button-primary {
                background: var(--gf-accent-primary);
                color: white;
            }
            
            .premium-button-primary:hover {
                opacity: 0.9;
                transform: translateY(-1px);
                box-shadow: 0 4px 12px rgba(66, 133, 244, 0.3);
            }
            
            .premium-button-secondary {
                background: transparent;
                color: var(--gf-text-primary);
                border: 1px solid var(--gf-border-color);
            }
            
            .premium-button-secondary:hover {
                background: var(--gf-hover-bg);
            }
            
            /* Premium danger button */
            .premium-button-danger {
                background: var(--gf-accent-danger);
                color: #fff;
            }
            .premium-button-danger:hover:enabled {
                filter: brightness(0.95);
                transform: translateY(-1px);
                box-shadow: 0 4px 12px rgba(234, 67, 53, 0.25);
            }
            .premium-button-danger:disabled {
                opacity: 0.5;
                cursor: not-allowed;
            }
            
            /* Premium Search Input */
            .premium-search-input {
                flex: 1;
                max-width: 300px;
                padding: 10px 16px;
                border: 1px solid var(--gf-border-color);
                border-radius: 10px;
                background: var(--gf-bg-input);
                color: var(--gf-text-primary);
                font-size: 14px;
                transition: all 0.14s ease-out;
            }
            
            .premium-search-input:focus {
                outline: none;
                border-color: var(--gf-accent-primary);
                box-shadow: 0 0 0 3px rgba(66, 133, 244, 0.1);
            }
            
            /* Premium Checkbox */
            .premium-checkbox-label {
                display: flex;
                align-items: center;
                gap: 8px;
                margin-left: auto;
                font-size: 14px;
                color: var(--gf-text-secondary);
                cursor: pointer;
                user-select: none;
            }
            
            .premium-checkbox {
                width: 18px;
                height: 18px;
                accent-color: var(--gf-accent-primary);
            }
            
            /* Premium Modal Body */
            .premium-modal-body {
                flex: 1 1 auto;
                overflow-y: auto;
                overflow-x: hidden !important;
                padding: 24px 28px;
                min-height: 0;
                width: 100%;
                box-sizing: border-box;
            }
            
            /* Ensure folder list container doesn't overflow */
            #folder-list-container {
                overflow-x: hidden !important;
                width: 100%;
                max-width: 100%;
            }
            
            /* Premium Folder List */
            .premium-folder-list {
                display: flex;
                flex-direction: column;
                gap: 16px;
                overflow-x: hidden;
                width: 100%;
            }
            
            .premium-folder-item {
                display: flex;
                align-items: center;
                justify-content: space-between;
                padding: 14px 16px;
                border-radius: 10px;
                background: var(--gf-bg-secondary);
                transition: all 0.14s ease-out;
                min-height: 60px;
                box-sizing: border-box;
                width: 100%;
                max-width: 100%;
                overflow: hidden;
            }
            
            .subfolder-spacer {
                display: inline-block;
                flex-shrink: 0;
            }
            
            .premium-folder-item:hover {
                background: var(--gf-hover-bg);
                transform: translateX(4px);
            }
            
            .premium-folder-content {
                display: flex;
                align-items: center;
                gap: 16px;
                flex: 1;
                min-width: 0;
                overflow: hidden;
            }
            
            .premium-folder-icon {
                color: var(--gf-text-secondary);
                flex-shrink: 0;
            }
            
            .premium-folder-name {
                font-size: 15px;
                font-weight: 500;
                color: var(--gf-text-primary);
                flex: 1;
                min-width: 0;
                overflow: hidden;
                text-overflow: ellipsis;
                white-space: nowrap;
            }
            
            .premium-folder-count {
                padding: 4px 10px;
                background: var(--gf-bg-primary);
                border-radius: 12px;
                font-size: 13px;
                color: var(--gf-text-secondary);
                font-weight: 500;
                margin-right: 8px;
            }
            
            .premium-folder-actions {
                display: flex;
                align-items: center;
                gap: 8px;
                opacity: 1;
                transition: opacity 0.14s ease-out;
                flex-shrink: 0;
            }
            
            .premium-icon-btn {
                width: 44px;
                height: 44px;
                padding: 0;
                border: none;
                background: transparent;
                color: var(--gf-text-secondary);
                cursor: pointer;
                border-radius: 8px;
                display: flex;
                align-items: center;
                justify-content: center;
                transition: all 0.15s ease;
                position: relative;
            }
            
            .premium-icon-btn:hover {
                background: var(--gf-bg-primary);
                color: var(--gf-text-primary);
            }
            
            .premium-icon-btn.delete-folder-btn:hover {
                background: rgba(239, 68, 68, 0.1);
                color: var(--gf-accent-danger);
            }
            
            /* Premium Modal Footer */
            .premium-modal-footer {
                display: flex;
                align-items: center;
                justify-content: flex-end;
                gap: 16px;
                padding: 24px 28px;
                border-top: 1px solid var(--gf-border-color);
                background: var(--gf-bg-primary);
                flex: 0 0 auto;
                min-height: 76px;
            }
            
            /* Premium Empty State */
            .premium-empty-state {
                text-align: center;
                padding: 48px 24px;
                color: var(--gf-text-secondary);
                font-size: 15px;
            }
            
            /* Premium Scrollbar */
            .premium-modal-body::-webkit-scrollbar {
                width: 8px;
            }
            
            .premium-modal-body::-webkit-scrollbar-track {
                background: transparent;
            }
            
            .premium-modal-body::-webkit-scrollbar-thumb {
                background: var(--gf-border-color);
                border-radius: 4px;
            }
            
            .premium-modal-body::-webkit-scrollbar-thumb:hover {
                background: var(--gf-text-tertiary);
            }
            #bulk-delete-search:focus {
                outline: none;
                border-color: var(--gf-accent-primary);
            }
            #bulk-delete-counter {
                font-weight: 500;
            }
            
            /* Chat Tools Tabbed Interface */
            .chat-tools-tabs {
                display: flex;
                gap: 4px;
                padding: 8px 24px 0;
                border-bottom: 2px solid var(--gf-border-color);
                background: var(--gf-bg-secondary);
                flex-shrink: 0;
            }
            
            .chat-tools-tab {
                display: flex;
                align-items: center;
                gap: 8px;
                padding: 10px 20px;
                border: none;
                background: transparent;
                color: var(--gf-text-secondary);
                cursor: pointer;
                border-radius: 8px 8px 0 0;
                transition: all 0.2s ease;
                position: relative;
                font-size: 14px;
                font-weight: 500;
                border-bottom: 3px solid transparent;
                margin-bottom: -2px;
            }
            
            .chat-tools-tab svg {
                opacity: 0.7;
                transition: opacity 0.2s ease;
            }
            
            .chat-tools-tab:hover {
                background: var(--gf-hover-bg);
                color: var(--gf-text-primary);
            }
            
            .chat-tools-tab:hover svg {
                opacity: 1;
            }
            
            .chat-tools-tab.active {
                background: var(--gf-bg-primary);
                color: var(--gf-accent-primary);
                border-bottom-color: var(--gf-accent-primary);
            }
            
            .chat-tools-tab.active svg {
                opacity: 1;
            }
            

            
            .premium-badge-small {
                font-size: 10px;
                padding: 2px 6px;
                background: linear-gradient(135deg, #f59e0b, #d97706);
                color: white;
                border-radius: 4px;
                font-weight: 600;
                margin-left: 4px;
            }
            
            .chat-tools-premium-badge {
                font-size: 10px;
                padding: 2px 8px;
                background: var(--gf-accent-primary);
                color: var(--gf-button-text);
                border: none;
                border-radius: 10px;
                font-weight: 600;
                margin-left: 6px;
                text-transform: none;
                letter-spacing: normal;
                line-height: 18px;
            }
            
            .tab-panel {
                display: none;
                animation: tabFadeIn 0.2s ease;
                flex: 1;
                min-height: 0;
                overflow: hidden;
            }
            
            .tab-panel.active {
                display: flex;
                flex-direction: column;
            }
            
            @keyframes tabFadeIn {
                from { 
                    opacity: 0; 
                    transform: translateY(-4px); 
                }
                to { 
                    opacity: 1; 
                    transform: translateY(0); 
                }
            }
            
            /* Chat Tools Modal Specific Adjustments */
            #chat-tools-modal .modal-content {
                display: flex;
                flex-direction: column;
                max-height: 80vh;
                height: auto;
            }
            
            #chat-tools-modal .premium-modal-header {
                border-bottom: none;
                flex-shrink: 0;
                padding: 16px 24px 8px;
                min-height: auto;
            }
            
            #chat-tools-modal .chat-tools-tabs {
                flex-shrink: 0;
            }
            
            #chat-tools-modal .tab-panel .premium-modal-actions {
                padding: 12px 24px 10px;
                flex-shrink: 0;
                min-height: auto;
            }
            
            #chat-tools-modal .tab-panel .premium-modal-body {
                padding: 16px 24px;
                flex: 1;
                min-height: 0;
                overflow-y: auto;
                max-height: none;
            }
            
            /* Export tab specific: make only the list scroll, not the body */
            #chat-tools-modal #export-tab-panel {
                animation: none !important; /* Disable animation to prevent jank with many items */
            }
            
            #chat-tools-modal #export-tab-panel .premium-modal-body {
                flex: 1 1 auto !important;
                display: flex !important;
                flex-direction: column !important;
                overflow-y: hidden !important;
                overflow-x: hidden !important;
                min-height: 0 !important;
                padding: 16px 24px !important;
                gap: 0 !important;
            }
            
            #chat-tools-modal #export-chat-list {
                flex: 1 1 auto;
                overflow-y: auto;
                overflow-x: hidden;
                margin: 0;
                padding: 0 8px 0 0;
                background: transparent;
                border: none;
                min-height: 0;
                /* Performance optimizations for smooth scrolling with many items */
                will-change: scroll-position;
                contain: layout style paint;
                transform: translateZ(0);
                scroll-behavior: smooth;
                -webkit-overflow-scrolling: touch;
            }
            
            /* Bulk delete tab specific: make only the list scroll, not the body */
            #chat-tools-modal #bulk-delete-tab-panel {
                animation: none !important; /* Disable animation to prevent jank with many items */
            }
            
            #chat-tools-modal #bulk-delete-tab-panel .premium-modal-body {
                flex: 1 1 auto !important;
                display: flex !important;
                flex-direction: column !important;
                overflow-y: hidden !important;
                overflow-x: hidden !important;
                min-height: 0 !important;
                padding: 16px 24px !important;
                gap: 0 !important;
            }
            
            #chat-tools-modal #bulk-delete-tab-panel .premium-modal-footer {
                flex: 0 0 auto !important;
                min-height: 64px !important;
                padding: 12px 24px !important;
            }
            
            #chat-tools-modal #bulk-delete-tab-panel #bulk-delete-list {
                flex: 1 1 auto;
                overflow-y: auto;
                overflow-x: hidden;
                margin: 0;
                padding: 0 8px 0 0;
                background: transparent;
                border: none;
                min-height: 0;
                max-height: none !important;
                /* Performance optimizations for smooth scrolling with many items */
                will-change: scroll-position;
                contain: layout style paint;
                transform: translateZ(0);
                scroll-behavior: smooth;
                -webkit-overflow-scrolling: touch;
            }
            
            /* Optimize item hover performance - remove expensive transitions */
            #chat-tools-modal .bulk-delete-item {
                transition: background 100ms ease;
                will-change: background;
            }
            
            #chat-tools-modal .tab-panel .premium-modal-footer {
                padding: 12px 24px;
                flex-shrink: 0;
                min-height: auto;
            }
            
            /* Export status and progress sections within tabs */
            #chat-tools-modal #export-chat-status {
                flex-shrink: 0;
            }
            
            /* Compact search inputs and buttons in chat tools */
            #chat-tools-modal .premium-search-input {
                padding: 8px 12px;
                min-height: 36px;
                height: 36px;
            }
            
            #chat-tools-modal .premium-button {
                padding: 8px 16px;
                min-height: 36px;
                height: 36px;
            }
            
            #chat-tools-modal .premium-checkbox-label {
                min-height: 36px;
            }
            
            /* Responsive tab styles */
            @media (max-width: 768px) {
                .chat-tools-tab span:not(.chat-tools-premium-badge) {
                    font-size: 13px;
                }
                
                .chat-tools-tab {
                    padding: 10px 16px;
                    gap: 6px;
                }
            }
            
            @media (max-width: 480px) {
                .chat-tools-tabs {
                    padding: 12px 16px 0;
                    gap: 2px;
                }
                
                .chat-tools-tab {
                    padding: 8px 12px;
                    font-size: 12px;
                }
                
                .chat-tools-tab svg {
                    width: 14px;
                    height: 14px;
                }
            }

            /* Compact padding for pinned messages modal */
            #pinned-messages-modal .premium-modal-header {
                padding: 16px 24px;
                min-height: 56px;
            }
            
            #pinned-messages-modal .premium-modal-actions {
                padding: 12px 24px;
                min-height: 60px;
            }
            
            #pinned-messages-modal .premium-modal-body {
                padding: 16px 24px;
            }
            
            #pinned-messages-modal .premium-modal-footer {
                padding: 12px 24px;
                min-height: 56px;
            }

            /* Light theme adjustments for modals */
            :host(.light-theme) .infi-chatgpt-modal {
                background-color: var(--gf-overlay-bg-light);
            }
            :host(.light-theme) .infi-chatgpt-modal.modal-blocking {
                background-color: rgba(0, 0, 0, 0.45);
            }
            :host(.light-theme) .modal-content {
                background-color: var(--gf-white);
                box-shadow: 0 5px 20px rgba(0,0,0,0.15);
                color: var(--gf-text-primary);
            }
            :host(.light-theme) .modal-header h2 {
                color: var(--gf-text-primary);
            }
            :host(.light-theme) .toolbox-dropdown {
                background: var(--gf-bg-primary);
                box-shadow: 
                    0 4px 6px rgba(0, 0, 0, 0.08),
                    0 1px 3px rgba(0, 0, 0, 0.04),
                    inset 0 0 0 1px rgba(0, 0, 0, 0.04);
            }
            :host(.light-theme) .gemini-modal-content {
                box-shadow: 0 8px 32px rgba(0, 0, 0, 0.15);
            }
            :host(.light-theme) #bulk-delete-search {
                background: var(--gf-white);
                border-color: var(--gf-border-color);
                color: var(--gf-text-primary);
            }
            :host(.light-theme) #bulk-delete-search:focus {
                border-color: var(--gf-accent-primary);
                box-shadow: 0 0 0 2px rgba(29, 78, 216, 0.2);
            }
            :host(.light-theme) #bulk-delete-search::placeholder {
                color: var(--gf-text-secondary);
            }
            :host(.light-theme) .secondary:hover {
                background-color: var(--gf-border-color);
            }
            :host(.light-theme) .list-item:hover {
                background-color: var(--gf-hover-bg);
            }
:host(.light-theme) .bulk-delete-item {
                background-color: var(--gf-white);
                color: var(--gf-text-primary);
            }
            :host(.light-theme) .bulk-delete-item:hover {
                background-color: var(--gf-bg-secondary);
            }
            :host(.light-theme) .bulk-delete-item label {
                color: var(--gf-text-primary);
            }
:host(.light-theme) #bulk-delete-list {
                background-color: var(--gf-white);
                border: 1px solid #D1D5DB;
                border-radius: var(--space-2);
                padding: var(--space-3);
            }
            :host(.light-theme) #bulk-delete-controls {
                background-color: var(--gf-bg-primary);
                border-top: 1px solid #D1D5DB;
                padding: var(--space-4);
                margin: 0 -20px -20px -20px;
                border-radius: 0 0 12px 12px;
            }
            :host(.light-theme) #bulk-delete-counter {
                color: var(--gf-text-secondary);
                font-weight: 500;
            }
            :host(.light-theme) #bulk-delete-list::-webkit-scrollbar-track {
                background: #F3F4F6;
            }
            :host(.light-theme) #bulk-delete-list::-webkit-scrollbar-thumb {
                background: #D1D5DB;
            }
            :host(.light-theme) #bulk-delete-list::-webkit-scrollbar-thumb:hover {
                background: #1D4ED8;
            }

            /* Chat Exporter Styles */
            .gemini-modal-backdrop {
                position: fixed;
                z-index: 2000;
                left: 0;
                top: 0;
                width: 100%;
                height: 100%;
                background-color: rgba(0, 0, 0, 0.6);
                backdrop-filter: blur(4px);
                display: flex;
                align-items: center;
                justify-content: center;
            }

            .gemini-modal-content {
                background-color: var(--gf-bg-primary);
                color: var(--gf-text-primary);
                border: 1px solid var(--gf-border-color);
                width: 90%;
                max-width: 720px;
                border-radius: 12px;
                box-shadow: 0 8px 32px rgba(0, 0, 0, 0.5);
                display: flex;
                flex-direction: column;
                max-height: 80vh;
            }

            .gemini-modal-header {
                padding: 16px 24px;
                border-bottom: 1px solid var(--gf-border-color);
                display: flex;
                justify-content: space-between;
                align-items: center;
                flex-shrink: 0;
            }

            .gemini-modal-header h2 {
                margin: 0;
                font-size: 20px;
                font-weight: 500;
            }

            .gemini-modal-close-btn {
                background: none;
                border: none;
                color: var(--gf-text-secondary);
                font-size: 28px;
                font-weight: 300;
                cursor: pointer;
                line-height: 1;
                padding: 4px;
                border-radius: 50%;
                transition: all var(--anim-normal) var(--ease-out);
            }
            .gemini-modal-close-btn:hover {
                background-color: var(--gf-hover-bg);
                color: var(--gf-text-primary);
            }

            .gemini-modal-body {
                padding: 16px 24px;
                overflow-y: auto;
                flex-grow: 1;
            }

            .gemini-modal-list {
                display: flex;
                flex-direction: column;
                gap: 8px;
            }

            .gemini-modal-list-item {
                padding: var(--input-padding);
                background-color: var(--gf-bg-secondary);
                border-radius: var(--space-2);
                cursor: pointer;
                transition: background-color var(--anim-normal) var(--ease-out);
                font-size: 14px;
                white-space: nowrap;
                overflow: hidden;
                text-overflow: ellipsis;
                min-height: 48px;
                display: flex;
                align-items: center;
                box-sizing: border-box;
            }
            .gemini-modal-list-item:hover {
                background-color: var(--gf-hover-bg);
            }
            .gemini-modal-list-item:focus-within {
                outline: 2px solid var(--gf-accent-primary);
                outline-offset: -2px;
            }

            .gemini-modal-empty-state, .gemini-modal-loader {
                text-align: center;
                padding: 40px;
                color: var(--gf-text-secondary);
                font-style: italic;
            }

            .format-selector {
                display: grid;
                grid-template-columns: repeat(auto-fit, minmax(100px, 1fr));
                gap: var(--gap-medium);
            }

            .format-btn {
                padding: var(--input-padding);
                font-size: 14px;
                font-weight: 500;
                border-radius: var(--space-2);
                cursor: pointer;
                background-color: var(--gf-bg-secondary);
                color: var(--gf-text-primary);
                border: 1px solid var(--gf-border-color);
                transition: all var(--anim-normal) var(--ease-out);
                min-height: 48px;
                display: inline-flex;
                align-items: center;
                justify-content: center;
                box-sizing: border-box;
            }
            .format-btn:hover {
                background-color: var(--gf-accent-primary);
                color: var(--gf-bg-primary);
                border-color: var(--gf-accent-primary);
            }


            #exporter-overlay {
                position: fixed;
                top: 0; left: 0; width: 100vw; height: 100vh;
                background-color: rgba(0,0,0,0.75);
                z-index: 2147483647;
                display: flex;
                justify-content: center;
                align-items: center;
                color: #fff;
                font-family: 'Google Sans', sans-serif;
            }
            .exporter-overlay-content {
                text-align: center;
            }
            .exporter-spinner {
                border: 4px solid rgba(255, 255, 255, 0.2);
                border-top: 4px solid #fff;
                border-radius: 50%;
                width: 50px;
                height: 50px;
                animation: spin 1s linear infinite;
                margin: 0 auto 20px auto;
            }
            .exporter-message {
                font-size: 18px;
                font-weight: 500;
            }

            @keyframes spin {
                0% { transform: rotate(0deg); }
                100% { transform: rotate(360deg); }
            }
            
            /* Loading States */
            .loading {
                position: relative;
                pointer-events: none;
                opacity: 0.7;
            }
            
            .loading::after {
                content: '';
                position: absolute;
                width: 20px;
                height: 20px;
                top: 50%;
                left: 50%;
                margin-left: -10px;
                margin-top: -10px;
                border: 2px solid transparent;
                border-top-color: currentColor;
                border-radius: 50%;
                animation: spin 0.8s linear infinite;
            }
            
            /* Button Loading State */
            .button.loading {
                color: transparent;
            }
            
            .button.loading::after {
                border-width: 2px;
                border-top-color: var(--gf-white);
            }
            
            /* Success State Animation */
            @keyframes successPulse {
                0% { transform: scale(1); }
                50% { transform: scale(1.05); }
                100% { transform: scale(1); }
            }
            
            @keyframes checkmark {
                0% { 
                    stroke-dashoffset: 100;
                    opacity: 0;
                }
                50% {
                    opacity: 1;
                }
                100% { 
                    stroke-dashoffset: 0;
                    opacity: 1;
                }
            }
            
            .success {
                animation: successPulse var(--anim-medium) var(--ease-out);
            }
            
            /* Error State Animation */
            @keyframes errorShake {
                0%, 100% { transform: translateX(0); }
                25% { transform: translateX(-4px); }
                75% { transform: translateX(4px); }
            }
            
            .error {
                animation: errorShake var(--anim-normal) var(--ease-out);
                border-color: var(--gf-accent-danger) !important;
                color: var(--gf-accent-danger) !important;
            }
            
            /* Skeleton Loading */
            @keyframes shimmer {
                0% {
                    background-position: -200% 0;
                }
                100% {
                    background-position: 200% 0;
                }
            }
            
            .skeleton {
                background: linear-gradient(
                    90deg,
                    var(--gf-bg-secondary) 25%,
                    var(--gf-hover-bg) 50%,
                    var(--gf-bg-secondary) 75%
                );
                background-size: 200% 100%;
                animation: shimmer 1.5s ease-in-out infinite;
                border-radius: 4px;
            }
            
            /* Ripple Effect */
            @keyframes ripple {
                0% {
                    transform: scale(0);
                    opacity: 1;
                }
                100% {
                    transform: scale(4);
                    opacity: 0;
                }
            }
            
            .ripple {
                position: relative;
                overflow: hidden;
            }
            
            .ripple::before {
                content: '';
                position: absolute;
                top: 50%;
                left: 50%;
                width: 0;
                height: 0;
                border-radius: 50%;
                background: rgba(255, 255, 255, 0.5);
                transform: translate(-50%, -50%);
                transition: width 0.6s, height 0.6s;
            }
            
            .ripple:active::before {
                width: 300px;
                height: 300px;
            }
            
            /* Screen reader only text */
            .sr-only {
                position: absolute;
                width: 1px;
                height: 1px;
                padding: 0;
                margin: -1px;
                overflow: hidden;
                clip: rect(0, 0, 0, 0);
                white-space: nowrap;
                border: 0;
            }
            
            /* Focus styles for keyboard navigation */
            *:focus {
                outline: 2px solid var(--gf-accent-primary);
                outline-offset: 2px;
            }
            
            button:focus-visible,
            input:focus-visible,
            select:focus-visible,
            textarea:focus-visible,
            [tabindex]:focus-visible {
                outline: 2px solid var(--gf-accent-primary);
                outline-offset: 2px;
                box-shadow: 0 0 0 4px rgba(26, 115, 232, 0.1);
            }
            
            .dropdown-item:focus {
                background-color: var(--gf-hover-bg);
                outline: none;
                box-shadow: inset 0 0 0 2px var(--gf-accent-primary);
            }
            
            /* Smooth Progress Indicator */
            .progress-smooth {
                position: relative;
                height: 4px;
                background: var(--gf-bg-secondary);
                border-radius: 2px;
                overflow: hidden;
            }
            
            .progress-smooth::after {
                content: '';
                position: absolute;
                top: 0;
                left: 0;
                bottom: 0;
                width: 30%;
                background: var(--gf-accent-primary);
                animation: indeterminate 1.5s ease-in-out infinite;
            }
            
            @keyframes indeterminate {
                0% {
                    left: -30%;
                    width: 30%;
                }
                50% {
                    width: 50%;
                }
                100% {
                    left: 100%;
                    width: 30%;
                }
            }
            
            /* Disabled state improvements */
            .button:disabled,
            .icon-btn:disabled {
                opacity: 0.5;
                cursor: not-allowed;
                transform: none !important;
            }
            
            .button:disabled:hover,
            .icon-btn:disabled:hover {
                background-color: initial;
                transform: none !important;
            }
            
            /* Active states for better feedback */
            .button:active:not(:disabled),
            .icon-btn:active:not(:disabled) {
                transform: scale(0.98);
            }
            
            .list-item:active {
                transform: scale(0.99);
                transition: transform var(--anim-instant) var(--ease-out);
            }
            
            /* Toast notification styles - Gemini Native Look */
            .prompt-toast {
                position: fixed;
                bottom: 32px;
                left: 50%;
                transform: translateX(-50%) translateY(100px);
                background: var(--toast-bg, #131314);
                color: var(--toast-text, #e3e3e3);
                padding: 14px 20px;
                border-radius: 24px;
                box-shadow: var(--toast-shadow, 0 4px 12px rgba(0,0,0,0.4), 0 0 0 1px rgba(255,255,255,0.08));
                font-size: 14px;
                font-weight: 400;
                line-height: 20px;
                font-family: 'Google Sans', -apple-system, BlinkMacSystemFont, sans-serif;
                z-index: 10001;
                opacity: 0;
                transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
                max-width: 90vw;
                min-width: 220px;
                display: inline-flex;
                align-items: center;
                gap: 12px;
            }

            .prompt-toast .toast-action {
                background: transparent;
                color: var(--toast-action, #8ab4f8);
                border: none;
                border-radius: 20px;
                padding: 6px 16px;
                font-size: 14px;
                font-weight: 500;
                cursor: pointer;
                margin-left: 4px;
                font-family: 'Google Sans', -apple-system, BlinkMacSystemFont, sans-serif;
                transition: background 0.2s ease;
            }

            .prompt-toast .toast-action:hover {
                background: var(--toast-action-hover, rgba(138, 180, 248, 0.08));
            }
            
            .prompt-toast .toast-action:active {
                background: var(--toast-action-active, rgba(138, 180, 248, 0.16));
            }
            
            .prompt-toast.show {
                opacity: 1;
                transform: translateX(-50%) translateY(0);
            }
            
            /* All toast types use theme-aware backgrounds */
            .prompt-toast.success {
                background: var(--toast-bg, #131314);
                color: var(--toast-text, #e3e3e3);
            }
            
            .prompt-toast.error {
                background: var(--toast-bg, #131314);
                color: var(--toast-error-text, #f28b82);
            }
            
            .prompt-toast.info {
                background: var(--toast-bg, #131314);
                color: var(--toast-text, #e3e3e3);
            }
            
            /* Premium Modal Shell Styles */
            .modal-manage-folders-modal .modal-content {
                width: min(800px, 92vw) !important;
                max-height: 85vh !important;
                border-radius: 16px !important;
                overflow: hidden !important;
                display: flex !important;
                flex-direction: column !important;
                background: var(--gf-bg-primary) !important;
                box-shadow: 0 20px 60px rgba(0, 0, 0, 0.3), 0 0 0 1px rgba(255, 255, 255, 0.08) !important;
            }
            
            /* Premium Modal Header */
            .premium-modal-header {
                padding: 24px;
                border-bottom: 1px solid var(--gf-border-color);
                display: flex;
                align-items: center;
                justify-content: space-between;
                flex-shrink: 0;
            }
            
            .premium-modal-title {
                margin: 0;
                font-size: 20px;
                font-weight: 600;
                color: var(--gf-text-primary);
                line-height: 1.2;
            }
            
            .premium-modal-close {
                width: 32px;
                height: 32px;
                display: flex;
                align-items: center;
                justify-content: center;
                background: transparent;
                border: none;
                border-radius: 8px;
                cursor: pointer;
                color: var(--gf-text-secondary);
                transition: all 150ms ease;
            }
            
            .premium-modal-close:hover {
                background: var(--gf-hover-bg);
                color: var(--gf-text-primary);
            }
            
            .premium-modal-close svg {
                width: 18px;
                height: 18px;
            }
            
            /* Premium Modal Actions Row */
            .premium-modal-actions {
                padding: 20px 24px;
                border-bottom: 1px solid var(--gf-border-color);
                display: flex;
                align-items: center;
                gap: 12px;
                flex-shrink: 0;
            }
            
            /* Premium Buttons */
            .premium-button {
                height: 36px;
                padding: 0 16px;
                border-radius: 8px;
                font-size: 14px;
                font-weight: 500;
                border: none;
                cursor: pointer;
                display: inline-flex;
                align-items: center;
                gap: 8px;
                transition: all 150ms ease;
                white-space: nowrap;
                font-family: inherit;
            }
            
            .premium-button-primary {
                background: var(--gf-accent-primary);
                color: var(--gf-button-text);
            }
            
            .premium-button-primary:hover {
                opacity: 0.9;
            }
            
            .premium-button-secondary {
                background: transparent;
                color: var(--gf-text-primary);
                border: 1px solid var(--gf-border-color);
            }
            
            .premium-button-secondary:hover {
                background: var(--gf-hover-bg);
            }
            
            /* Premium Search Input */
            .premium-search-input {
                flex: 1;
                height: 36px;
                padding: 0 14px;
                border: 1px solid var(--gf-border-color);
                border-radius: 8px;
                background: var(--gf-bg-secondary);
                color: var(--gf-text-primary);
                font-size: 14px;
                transition: all 150ms ease;
            }
            
            .premium-search-input:focus {
                outline: none;
                border-color: var(--gf-accent-primary);
                background: var(--gf-bg-input);
            }
            
            .premium-search-input::placeholder {
                color: var(--gf-text-tertiary);
            }
            
            /* Premium Checkbox */
            .premium-checkbox-label {
                display: flex;
                align-items: center;
                gap: 8px;
                font-size: 14px;
                color: var(--gf-text-primary);
                cursor: pointer;
                user-select: none;
            }
            
            .premium-checkbox {
                width: 16px;
                height: 16px;
                cursor: pointer;
            }
            
            /* Premium Modal Body - Scrollable Content */
            .premium-modal-body {
                flex: 1;
                padding: 20px 24px 24px;
                overflow-y: auto;
                overflow-x: hidden;
                min-height: 0;
            }
            
            /* Premium Folder List */
            .premium-folder-list {
                display: flex;
                flex-direction: column;
                gap: 2px;
            }
            
            .premium-folder-list .list-item {
                min-height: 48px;
                padding: 8px 12px;
                border-radius: 8px;
                transition: background 150ms ease;
            }
            
            .premium-folder-list .list-item:hover {
                background: var(--gf-hover-bg);
            }
            
            /* Premium Modal Footer */
            .premium-modal-footer {
                padding: 24px;
                border-top: 1px solid var(--gf-border-color);
                display: flex;
                justify-content: flex-end;
                gap: 12px;
                flex-shrink: 0;
            }
            
            /* Scrollbar Styling */
            .premium-modal-body::-webkit-scrollbar {
                width: 8px;
            }
            
            .premium-modal-body::-webkit-scrollbar-track {
                background: transparent;
            }
            
            .premium-modal-body::-webkit-scrollbar-thumb {
                background: var(--gf-border-color);
                border-radius: 4px;
            }
            
            .premium-modal-body::-webkit-scrollbar-thumb:hover {
                background: var(--gf-text-tertiary);
            }
        `,u.appendChild(e),!u.getElementById("plan-chip-styles")){const t=document.createElement("style");t.id="plan-chip-styles",t.textContent=`
                /* Keep title/chip on one line without breaking layout */
#gemini-toolbox-btn #toolbox-title {
                    flex: 0 1 auto;
                    white-space: nowrap;         /* keep on one line */
                    display: inline-flex;
                    align-items: center;
                }

                .plan-chip {
                    margin-left: 8px;
                    padding: 2px 8px;
                    border-radius: 10px;
                    font-size: 11px;
                    font-weight: 600;
                    line-height: 18px;
                    border: 1px solid var(--gf-border-color);
                    color: var(--gf-text-secondary);
                    background: var(--gf-bg-secondary);
                    white-space: nowrap;       /* Prevent internal wrap */
                    flex: 0 0 auto;            /* Keep full chip visible */
                }
                .plan-chip--premium {
                    color: var(--gf-button-text) !important;  /* Black in dark mode, white in light mode */
                    background: var(--gf-accent-primary);
                    border-color: transparent;
                }
            `,u.appendChild(t)}setTimeout(()=>{Ve()},100)}function Ve(){if(!z)return;Pe=Me();const e=Pe==="dark";e?(z.style.setProperty("--gf-bg-primary","#272A2C"),z.style.setProperty("--gf-bg-secondary","#1E2124"),z.style.setProperty("--gf-text-primary","#E3E3E3"),z.style.setProperty("--gf-text-secondary","#C2C2C2"),z.style.setProperty("--gf-text-tertiary","#9CA3AF"),z.style.setProperty("--gf-border-color","#404040"),z.style.setProperty("--gf-hover-bg","#3A3D40"),z.style.setProperty("--gf-accent-primary","#8AB4F8"),z.style.setProperty("--gf-accent-danger","#B00020"),z.style.setProperty("--gf-success-text","#FFFFFF"),z.style.setProperty("--gf-danger-text","#FFFFFF"),z.style.setProperty("--gf-info-text","#1A1A1A"),z.style.setProperty("--gf-bg-input","#1E2124"),z.style.setProperty("--gf-white","#FFFFFF"),z.style.setProperty("--gf-button-text","#1a1a1a"),z.style.setProperty("--toast-bg","#131314"),z.style.setProperty("--toast-text","#e3e3e3"),z.style.setProperty("--toast-error-text","#f28b82"),z.style.setProperty("--toast-action","#8ab4f8"),z.style.setProperty("--toast-action-hover","rgba(138, 180, 248, 0.08)"),z.style.setProperty("--toast-action-active","rgba(138, 180, 248, 0.16)"),z.style.setProperty("--toast-shadow","0 4px 12px rgba(0,0,0,0.4), 0 0 0 1px rgba(255,255,255,0.08)")):(z.style.setProperty("--gf-bg-primary","#F0F4F8"),z.style.setProperty("--gf-bg-secondary","#FFFFFF"),z.style.setProperty("--gf-text-primary","#1F2937"),z.style.setProperty("--gf-text-secondary","#5B6670"),z.style.setProperty("--gf-border-color","#D1D5DB"),z.style.setProperty("--gf-hover-bg","#E5E7EB"),z.style.setProperty("--gf-accent-primary","#1D4ED8"),z.style.setProperty("--gf-accent-danger","#DC2626"),z.style.setProperty("--gf-accent-warning","#F59E0B"),z.style.setProperty("--gf-success-text","#FFFFFF"),z.style.setProperty("--gf-danger-text","#FFFFFF"),z.style.setProperty("--gf-info-text","#FFFFFF"),z.style.setProperty("--gf-bg-input","#FFFFFF"),z.style.setProperty("--gf-white","#FFFFFF"),z.style.setProperty("--gf-button-text","#FFFFFF"),z.style.setProperty("--toast-bg","#ffffff"),z.style.setProperty("--toast-text","#3c4043"),z.style.setProperty("--toast-error-text","#d33333"),z.style.setProperty("--toast-action","#1a73e8"),z.style.setProperty("--toast-action-hover","rgba(26, 115, 232, 0.08)"),z.style.setProperty("--toast-action-active","rgba(26, 115, 232, 0.16)"),z.style.setProperty("--toast-shadow","0 1px 3px rgba(60,64,67,0.3), 0 1px 2px rgba(60,64,67,0.15)")),u&&u.host&&u.querySelectorAll("*").forEach(o=>{o.style&&(o.style.opacity="0.999",requestAnimationFrame(()=>{o.style.opacity=""}))}),u&&u.host&&(e?(u.host.classList.remove("light-theme"),u.host.classList.add("dark-theme")):(u.host.classList.add("light-theme"),u.host.classList.remove("dark-theme")));const t=u&&u.getElementById("prompt-library-modal");t&&(e?t.classList.remove("prompt-library-light"):t.classList.add("prompt-library-light")),window.geminiToolboxDebug={detectTheme:Me,applyTheme:Ve,currentTheme:()=>Pe}}function eo(){if(!u)return null;const e=u.getElementById("toolbox-title");if(!e)return null;let t=u.getElementById("plan-chip");return t||(t=document.createElement("span"),t.id="plan-chip",t.className="plan-chip",t.setAttribute("aria-live","polite"),e.insertAdjacentElement("afterend",t)),t}function tt(e){const t=eo();t&&(t.className="plan-chip",e?(t.textContent="Premium",t.classList.add("plan-chip--premium"),t.setAttribute("aria-label","Premium plan active")):(t.textContent="Free",t.setAttribute("aria-label","Free plan")))}function to(){return`
            <div id="gemini-toolbox-container" class="sidebar-tab">
                <div id="gemini-toolbox-btn" class="toolbox-button" 
                     role="button" 
                     tabindex="0"
                     aria-label="Gemini Toolbox menu"
                     aria-expanded="false"
                     aria-controls="gemini-toolbox-dropdown">
                <svg width="24" height="24" viewBox="0 0 512 512" fill="none" xmlns="http://www.w3.org/2000/svg" aria-hidden="true">
                    <path d="M270.0 139.5 L240.5 139.0 L240.5 95.0 L255.0 70.5 L270.5 94.0 L270.0 139.5 Z M49.0 190.5 L35.5 177.0 L30.5 158.0 L72.0 138.5 L104.0 103.5 L132.0 93.5 L163.0 92.5 L201.5 109.0 L169.0 109.5 L149.0 118.5 L138.5 132.0 L150.5 154.0 L116.0 174.5 L96.0 156.5 L49.0 190.5 Z M426.0 133.5 L394.5 125.0 L421.0 100.5 L442.0 92.5 L426.0 133.5 Z M374.0 213.5 L348.5 190.0 L362.5 159.0 L363.5 129.0 L444.0 145.5 L452.5 136.0 L465.0 96.5 L480.5 126.0 L479.5 148.0 L469.5 168.0 L457.0 179.5 L395.0 198.5 L374.0 213.5 Z M286.0 232.5 L225.5 232.0 L225.5 204.0 L240.5 198.0 L241.0 148.5 L270.5 149.0 L270.5 198.0 L285.5 204.0 L286.0 232.5 Z M399.5 185.0 L406.5 171.0 L393.0 156.5 L382.0 155.5 L377.5 169.0 L399.5 185.0 Z M188.0 232.5 L152.0 232.5 L119.5 182.0 L155.0 162.5 L188.0 232.5 Z M356.0 232.5 L302.5 232.0 L342.0 195.5 L366.5 220.0 L356.0 232.5 Z M431.0 282.5 L80.0 282.5 L64.5 270.0 L63.5 242.0 L447.0 241.5 L446.5 270.0 L431.0 282.5 Z M379.0 440.5 L132.0 440.5 L115.0 434.5 L94.5 406.0 L93.5 292.0 L126.5 292.0 L127.5 345.0 L138.0 358.5 L157.0 362.5 L177.5 343.0 L178.0 291.5 L333.0 291.5 L334.5 346.0 L345.0 358.5 L363.0 362.5 L383.5 345.0 L384.5 292.0 L417.0 291.5 L416.5 406.0 L400.0 431.5 L379.0 440.5 Z M156.0 353.5 L145.0 352.5 L135.5 341.0 L136.0 291.5 L168.5 292.0 L168.5 342.0 L156.0 353.5 Z M363.0 353.5 L350.0 351.5 L342.5 342.0 L343.0 291.5 L375.5 292.0 L375.5 341.0 L363.0 353.5 Z" fill="currentColor" fill-rule="evenodd"/>
                </svg>
                    <span id="toolbox-title">Gemini Toolbox</span>
                    <svg width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="dropdown-arrow" aria-hidden="true">
                        <path d="M6 9l6 6 6-6" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
                    </svg>
                </div>
                <div id="gemini-toolbox-dropdown" class="toolbox-dropdown" role="menu" aria-labelledby="gemini-toolbox-btn">
                    <div class="dropdown-group">
                        <div class="dropdown-group-label">Chat Management</div>
                        <div id="manage-folders-link" class="dropdown-item" role="menuitem" tabindex="-1">
                            <svg width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="dropdown-icon" aria-hidden="true">
                                <path d="M10 4H4C2.89543 4 2 4.89543 2 6V18C2 19.1046 2.89543 20 4 20H20C21.1046 20 22 19.1046 22 18V8C22 6.89543 21.1046 6 20 6H12L10 4Z" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
                            </svg>
                            <span>Manage Folders</span>
                        </div>
                        <div id="chat-tools-link" class="dropdown-item" role="menuitem" tabindex="-1">
                            <svg width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="dropdown-icon" aria-hidden="true">
                                <path d="M9 3H4C3.44772 3 3 3.44772 3 4V9C3 9.55228 3.44772 10 4 10H9C9.55228 10 10 9.55228 10 9V4C10 3.44772 9.55228 3 9 3Z" stroke="currentColor" stroke-width="2"/>
                                <path d="M20 3H15C14.4477 3 14 3.44772 14 4V9C14 9.55228 14.4477 10 15 10H20C20.5523 10 21 9.55228 21 9V4C21 3.44772 20.5523 3 20 3Z" stroke="currentColor" stroke-width="2"/>
                                <path d="M9 14H4C3.44772 14 3 14.4477 3 15V20C3 20.5523 3.44772 21 4 21H9C9.55228 21 10 20.5523 10 20V15C10 14.4477 9.55228 14 9 14Z" stroke="currentColor" stroke-width="2"/>
                                <path d="M20 14H15C14.4477 14 14 14.4477 14 15V20C14 20.5523 14.4477 21 15 21H20C20.5523 21 21 20.5523 21 20V15C21 14.4477 20.5523 14 20 14Z" stroke="currentColor" stroke-width="2"/>
                            </svg>
                            <span>Chat Tools</span>
                        </div>
                    </div>
                    <div class="dropdown-divider"></div>
                    <div class="dropdown-group">
                        <div class="dropdown-group-label">Utilities</div>
                        <div id="prompt-library-link" class="dropdown-item" role="menuitem" tabindex="-1">
                            <svg width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="dropdown-icon" aria-hidden="true">
                                <path d="M4 19.5A2.5 2.5 0 0 1 1.5 17V7A2.5 2.5 0 0 1 4 4.5h16A2.5 2.5 0 0 1 22.5 7v10a2.5 2.5 0 0 1-2.5 2.5H4z" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
                                <path d="M8 10h8M8 14h5" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
                            </svg>
                            <span>Prompt Management</span>
                        </div>
                        <!--
                        <div id="image-gallery-link" class="dropdown-item" role="menuitem" tabindex="-1">
                            <svg width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="dropdown-icon" aria-hidden="true">
                                <path d="M4 16L8.586 11.414C9.367 10.633 10.633 10.633 11.414 11.414L16 16M14 14L15.586 12.414C16.367 11.633 17.633 11.633 18.414 12.414L20 14M14 8H14.01M6 20H18C19.1046 20 20 19.1046 20 18V6C20 4.89543 19.1046 4 18 4H6C4.89543 4 4 4.89543 4 6V18C4 19.1046 4.89543 20 6 20Z" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
                            </svg>
                            <span>Image Gallery</span>
                            <span class="dropdown-badge" style="background-color: rgba(138, 180, 248, 0.2); color: var(--gf-accent-primary);">BETA</span>
                        </div>
                        -->
                        <div id="settings-link" class="dropdown-item" role="menuitem" tabindex="-1">
                            <svg width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="dropdown-icon" aria-hidden="true">
                                <path d="M12 15a3 3 0 100-6 3 3 0 000 6z" stroke="currentColor" stroke-width="2"/>
                                <path d="M19.4 15a1.65 1.65 0 00.33 1.82l.06.06a2 2 0 010 2.83 2 2 0 01-2.83 0l-.06-.06a1.65 1.65 0 00-1.82-.33 1.65 1.65 0 00-1 1.51V21a2 2 0 01-2 2 2 2 0 01-2-2v-.09A1.65 1.65 0 009 19.4a1.65 1.65 0 00-1.82.33l-.06.06a2 2 0 01-2.83 0 2 2 0 010-2.83l.06-.06a1.65 1.65 0 00.33-1.82 1.65 1.65 0 00-1.51-1H3a2 2 0 01-2-2 2 2 0 012-2h.09A1.65 1.65 0 004.6 9a1.65 1.65 0 00-.33-1.82l-.06-.06a2 2 0 010-2.83 2 2 0 012.83 0l.06.06a1.65 1.65 0 001.82.33H9a1.65 1.65 0 001-1.51V3a2 2 0 012-2 2 2 0 012 2v.09a1.65 1.65 0 001 1.51 1.65 1.65 0 001.82-.33l.06-.06a2 2 0 012.83 0 2 2 0 010 2.83l-.06.06a1.65 1.65 0 00-.33 1.82V9a1.65 1.65 0 001.51 1H21a2 2 0 012 2 2 2 0 01-2 2h-.09a1.65 1.65 0 00-1.51 1z" stroke="currentColor" stroke-width="2"/>
                            </svg>
                            <span>Settings</span>
                        </div>
                    </div>
                </div>
            </div>
        `}function wt(){const e=t(null,0);function t(n,o){let r="";return w.folders.filter(a=>a.parentId===n).forEach(a=>{const d=(a.chatIds?.length||0)===0?" is-empty":"";r+=`
                    <div class="premium-folder-item${d} ${o>0?"subfolder-level-"+o:""}" data-folder-id="${a.id}">
                        <div class="premium-folder-content">
                            ${o>0?'<span class="subfolder-spacer" style="width: '+o*20+'px; flex-shrink: 0;"></span>':""}
                            <svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="premium-folder-icon">
                                <path d="M10 4H4C2.89543 4 2 4.89543 2 6V18C2 19.1046 2.89543 20 4 20H20C21.1046 20 22 19.1046 22 18V8C22 6.89543 21.1046 6 20 6H12L10 4Z"/>
                            </svg>
                            <span class="premium-folder-name">${a.name}</span>
                            <span class="premium-folder-count">${a.chatIds?.length||0}</span>
                        </div>
                        <div class="premium-folder-actions">
                             <button class="premium-icon-btn add-chats-btn" data-folder-id="${a.id}" title="Add Chats">
                                <svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                                    <circle cx="12" cy="12" r="10"></circle>
                                    <line x1="12" y1="8" x2="12" y2="16"></line>
                                    <line x1="8" y1="12" x2="16" y2="12"></line>
                                </svg>
                             </button>
                             <button class="premium-icon-btn edit-folder-btn" data-folder-id="${a.id}" title="Edit Folder">
                                <svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                                    <path d="M11 4H4a2 2 0 0 0-2 2v14a2 2 0 0 0 2 2h14a2 2 0 0 0 2-2v-7"></path>
                                    <path d="M18.5 2.5a2.121 2.121 0 0 1 3 3L12 15l-4 1 1-4 9.5-9.5z"></path>
                                </svg>
                             </button>
                             <button class="premium-icon-btn add-subfolder-btn" data-parent-id="${a.id}" title="Add Subfolder" aria-label="Add subfolder to ${a.name}">
                                <svg xmlns="http://www.w3.org/2000/svg" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="feather feather-folder-plus"><path d="M22 19a2 2 0 0 1-2 2H4a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2h5l2 3h9a2 2 0 0 1 2 2z"></path><line x1="12" y1="11" x2="12" y2="17"></line><line x1="9" y1="14" x2="15" y2="14"></line></svg>
                            </button>
                             <button class="premium-icon-btn delete-folder-btn" data-folder-id="${a.id}" title="Delete Folder" aria-label="Delete ${a.name}">
                                <svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                                    <path d="M19 7l-.867 12.142A2 2 0 0116.138 21H7.862a2 2 0 01-1.995-1.858L5 7m5 4v6m4-6v6m1-10V4a1 1 0 00-1-1h-4a1 1 0 00-1 1v3M4 7h16"/>
                                </svg>
                            </button>
                        </div>
                    </div>
                `,r+=t(a.id,o+1)}),r}return`
            <div class="premium-modal-header">
                <h2 class="premium-modal-title">Manage Folders</h2>
                <button class="premium-modal-close" id="close-modal-btn" aria-label="Close">
                    <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                        <line x1="18" y1="6" x2="6" y2="18"></line>
                        <line x1="6" y1="6" x2="18" y2="18"></line>
                    </svg>
                </button>
            </div>
            <div class="premium-modal-actions">
                <button class="premium-button premium-button-primary" id="add-folder-btn">
                    <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                        <line x1="12" y1="5" x2="12" y2="19"></line>
                        <line x1="5" y1="12" x2="19" y2="12"></line>
                    </svg>
                    <span>New Folder</span>
                </button>
                <input type="search" id="search-folders-input" 
                       class="premium-search-input"
                       placeholder="Search folders..." 
                       aria-label="Search folders">
                <label class="premium-checkbox-label">
                    <input type="checkbox" 
                           id="hide-foldered-toggle" 
                           class="premium-checkbox"
                           ${w.settings.hideFolderedChats?"checked":""} />
                    <span>Hide foldered chats</span>
                </label>
                <span class="premium-shortcut-hint" aria-label="Keyboard shortcut to open Manage Folders" title="Press G then F to open Manage Folders" style="margin-left: auto; color: var(--gf-text-secondary); font-size: 12px;">
                    Shortcut: G \u2192 F
                </span>
            </div>
            <div class="premium-modal-body">
                <div id="folder-list-container" class="premium-folder-list">
                    ${e||'<div class="premium-empty-state">No folders yet. Click "New Folder" to get started.</div>'}
                </div>
            </div>
            <div class="premium-modal-footer">
                <button type="button" id="done-manage-folders-btn" class="premium-button premium-button-secondary">Done</button>
            </div>
        `}function oo(e){const t=w.selectedItems.includes(e.id);return`
            <div class="list-item folder-item" data-id="${e.id}">
                <input type="checkbox" class="item-checkbox" data-id="${e.id}" ${t?"checked":""}>
                <svg width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M10 4H4C2.89543 4 2 4.89543 2 6V18C2 19.1046 2.89543 20 4 20H20C21.1046 20 22 19.1046 22 18V8C22 6.89543 21.1046 6 20 6H12L10 4Z" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>
                <span class="item-title">${e.name}</span>
                <span class="item-count" style="margin-left: auto; color: var(--gf-text-secondary);">(${e.chatIds.length})</span>
                <button class="add-chats-btn icon-btn" data-folder-id="${e.id}" title="Add chats to folder">
                    <svg width="16" height="16" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M12 5V19M5 12H19" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>
                </button>
            </div>
        `}function no(e=!1,t=""){const n=e?"Edit Folder Name":"Add New Folder",o=e?"Save Changes":"Create Folder";return`
            <form id="add-folder-form" autocomplete="off">
                <div style="margin-bottom: 20px;">
                    <label for="folder-name-input" class="sr-only">Folder name</label>
                    <input type="text" 
                           id="folder-name-input" 
                           name="${`gemini-folder-${Date.now()}-${Math.random().toString(36).substr(2,9)}`}"
                           value="${t}" 
                           placeholder="Enter folder name" 
                           autocomplete="new-password"
                           required 
                           aria-required="true" 
                           style="width: 100%; padding: var(--input-padding); border: 1px solid var(--gf-border-color); border-radius: var(--space-2); background: var(--gf-bg-input); color: var(--gf-text-primary); font-size: 14px; font-weight: 400; transition: all var(--anim-normal) var(--ease-out);">
                </div>
                <div class="modal-footer footer-spread" style="margin-top: var(--space-4);">
                    <button type="button" class="button secondary cancel-action">Cancel</button>
                    <button type="button" id="save-folder-btn" class="button primary">${o}</button>
                </div>
            </form>
        `}function Jo(){return`
            <div style="margin-bottom: 24px;">
                <div style="display: flex; align-items: center; gap: var(--gap-medium); margin-bottom: var(--space-4);">
                    <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="var(--gf-accent-danger)" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                        <path d="M3 6h18"></path>
                        <path d="M19 6v14a2 2 0 01-2 2H7a2 2 0 01-2-2V6m3 0V4a2 2 0 012-2h4a2 2 0 012 2v2"></path>
                        <line x1="10" y1="11" x2="10" y2="17"></line>
                        <line x1="14" y1="11" x2="14" y2="17"></line>
                    </svg>
                    <p style="margin: 0; color: var(--gf-text-primary); font-size: 16px; font-weight: 500; line-height: 1.5;">
                        Are you sure you want to delete this folder and all its contents?
                    </p>
                </div>
                <p style="margin: 0 0 0 36px; color: var(--gf-text-secondary); font-size: 14px;">
                    This action cannot be undone.
                </p>
            </div>
            <div class="modal-footer">
                <button type="button" class="button secondary cancel-action">Cancel</button>
                    <button type="button" id="confirm-delete-btn" class="button danger" >
                        <svg width="16" height="16" viewBox="0 0 16 16" fill="currentColor" style="margin-right: 6px; vertical-align: middle;">
                            <path d="M2 4h12v9a1 1 0 01-1 1H3a1 1 0 01-1-1V4zm1.5-1.5h9V2a.5.5 0 00-.5-.5H4a.5.5 0 00-.5.5v.5zM6.5 6v5m3-5v5"/>
                        </svg>
                        Delete
                    </button>
            </div>
        `}function _e(e,t=null,n=!1,o=!1){return t||(t=new Set,w.folders.forEach(r=>{r.chatIds.forEach(i=>t.add(i))})),e.map((r,i)=>{const a=Ae(r,`Conversation ${i+1}`),d=K(r);if(!d)return"";const p=t.has(d),s=Jt(r)===!0,g=p&&!n||s&&!o;return`
                <div class="bulk-delete-item ${g?"foldered-protected":""}" data-is-foldered="${p}" data-is-pinned="${s}">
                    <input type="checkbox" id="del-check-${d}" class="bulk-delete-checkbox select-all-checkbox" data-type="chat" data-chat-id="${d}" ${g?"disabled":""}>
                    <span class="item-title" style="cursor: pointer; flex: 1;">${a}</span>
                    ${p&&!n?'<span class="protected-badge">Protected (Folder)</span>':""}
                    ${s&&!o?'<span class="protected-badge">Protected (Pinned)</span>':""}
                </div>
            `}).join("")}function ro(e,t){let n="";return arguments.length===2&&t.length===0?n=`
                <div style="text-align: center; padding: 40px;">
                    <div style="width: 40px; height: 40px; border: 3px solid var(--gf-border-color); border-top-color: var(--gf-accent-primary); border-radius: 50%; animation: spin 1s linear infinite; margin: 0 auto 16px;"></div>
                    <p style="color: var(--gf-text-secondary);">Loading all conversations...</p>
                </div>
            `:t&&t.length>0?n=t.map(o=>`
                <div class="list-item chat-item">
                    <input type="checkbox" class="chat-select-checkbox" data-chat-id="${o.id}">
                    <span class="item-title">${o.title}</span>
                </div>
            `).join(""):n='<p style="color: var(--gf-text-secondary); text-align: center; margin-top: 20px;">No available chats to add.</p>',`
            <div style="margin-bottom: 0px;">
                <p style="margin: 0 0 4px 0; color: var(--gf-text-secondary); font-size: 14px;">Select chats to add to this folder.</p>
                <div style="margin-top: 4px;">
                    <input type="text" id="add-chat-search" placeholder="Search chats..." class="search-input" style="width: 100%; padding: 8px 12px; border: 1px solid var(--gf-border-color); border-radius: 4px; background: var(--gf-bg-primary); color: var(--gf-text-primary);">
                </div>
                <div id="add-chats-search-loading" style="display: none; padding: 8px 12px; margin-top: 8px; background: var(--gf-bg-secondary); border-radius: 4px; color: var(--gf-accent-primary); font-size: 13px;">
                    <div style="display: flex; align-items: center; gap: 8px;">
                        <div style="width: 14px; height: 14px; border: 2px solid var(--gf-accent-primary); border-top: 2px solid transparent; border-radius: 50%; animation: spin 1s linear infinite;"></div>
                        <span id="add-chats-search-status">Searching all conversations...</span>
                    </div>
                </div>
            </div>
            <div id="add-chats-list-container" style="max-height: 650px; overflow-y: auto; margin-bottom: 8px; margin-top: 4px; padding: 0px 4px 4px 4px;">
                ${n}
            </div>
            <div style="margin-top: 8px; padding-top: 8px; border-top: 1px solid var(--gf-border-color);">
                <label style="display: flex; align-items: center; gap: 8px; cursor: pointer;">
                    <input type="checkbox" id="select-all-chats">
                    <span>Select All</span>
                </label>
            </div>
            <div class="modal-footer">
                <div class="modal-actions">
                    <button type="button" class="button secondary cancel-action">Cancel</button>
                    <button type="button" id="save-add-chats" class="button primary">Add Selected</button>
                </div>
            </div>
        `}let lt=!1;function ao(){if(lt)return;const e="gemini-toolbox-portal-styles";if(document.getElementById(e)){lt=!0;return}const t=document.createElement("style");t.id=e,t.textContent=`
            /* Portal Modal Styles - Injected to document head for modals outside shadow DOM */
            .infi-chatgpt-modal.modal-portal {
                position: fixed;
                top: 0;
                left: 0;
                width: 100vw;
                height: 100vh;
                background-color: rgba(0, 0, 0, 0.6);
                backdrop-filter: blur(4px);
                z-index: 99999;
                display: flex;
                align-items: center;
                justify-content: center;
                cursor: wait;
                opacity: 0;
                animation: portalModalFadeIn 140ms ease-out forwards;
            }
            
            @keyframes portalModalFadeIn {
                from { opacity: 0; }
                to { opacity: 1; }
            }
            
            .infi-chatgpt-modal.modal-portal.closing {
                animation: portalModalFadeOut 90ms ease-in forwards;
            }
            
            @keyframes portalModalFadeOut {
                from { opacity: 1; }
                to { opacity: 0; }
            }
            
            .infi-chatgpt-modal.modal-portal .modal-content {
                pointer-events: auto;
                background: #1a1c20;
                border-radius: 16px;
                box-shadow: 0 20px 60px rgba(0, 0, 0, 0.5);
                max-height: 90vh;
                overflow: hidden;
                display: flex;
                flex-direction: column;
            }
            
            .infi-chatgpt-modal.modal-portal .premium-modal-header {
                padding: 24px 28px;
                border-bottom: 1px solid #2d3139;
                display: flex;
                align-items: center;
                justify-content: space-between;
            }
            
            .infi-chatgpt-modal.modal-portal .premium-modal-title {
                font-size: 20px;
                font-weight: 600;
                color: #e3e3e3;
                margin: 0;
                font-family: 'Google Sans', -apple-system, BlinkMacSystemFont, sans-serif;
            }
            
            .infi-chatgpt-modal.modal-portal .premium-modal-body {
                padding: 40px;
                overflow-y: auto;
                flex: 1;
                color: #e3e3e3;
            }
            
            .infi-chatgpt-modal.modal-portal .premium-modal-footer {
                padding: 24px 28px;
                border-top: 1px solid #2d3139;
                display: flex;
                justify-content: flex-end;
                gap: 12px;
            }
            
            .infi-chatgpt-modal.modal-portal .premium-button {
                padding: 10px 20px;
                border-radius: 10px;
                font-size: 14px;
                font-weight: 500;
                border: none;
                cursor: pointer;
                transition: all 0.2s;
                font-family: 'Google Sans', -apple-system, BlinkMacSystemFont, sans-serif;
            }
            
            .infi-chatgpt-modal.modal-portal .premium-button-secondary {
                background: #2d3139;
                color: #e3e3e3;
            }
            
            .infi-chatgpt-modal.modal-portal .premium-button-secondary:hover {
                background: #383c45;
            }
            
            /* Progress modal specific styles */
            .infi-chatgpt-modal.modal-portal .spinner {
                animation: spin 1s linear infinite;
            }
            
            @keyframes spin {
                to { transform: rotate(360deg); }
            }
        `,document.head.appendChild(t),lt=!0}function le(e,t,n,o=480,r={}){const{blocking:i=!1,portal:a=!1}=r,d=a?document.body:u;if(!d){console.error("[Gemini Toolbox] Modal container not available");return}a&&ao();const p=d.querySelector(`#${e}`);if(p){try{d.appendChild(p)}catch{}const l=p.querySelector('button, [href], input, select, textarea, [tabindex]:not([tabindex="-1"])');return l&&l.focus&&setTimeout(()=>l.focus(),50),Se=!0,w.modalType=e,p}if(a){const l=document.body.querySelector(".infi-chatgpt-modal.modal-portal");if(l&&l.id!==e)return console.warn("[Gemini Toolbox] Portal modal already exists:",l.id),null}const s=document.createElement("div");s.className="infi-chatgpt-modal",s.setAttribute("data-gemini-toolbox-modal","true"),i&&s.classList.add("modal-blocking"),a&&s.classList.add("modal-portal"),s.id=e,s._isPortal=a;let g=n;n.includes("modal-header")||(g=`
                <div class="modal-header">
                    <h2 id="${`modal-title-${e}`}">${t}</h2>
                    <button class="modal-close" id="close-modal-btn" aria-label="Close ${t}">
                        <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" aria-hidden="true">
                            <line x1="18" y1="6" x2="6" y2="18"></line>
                            <line x1="6" y1="6" x2="18" y2="18"></line>
                        </svg>
                    </button>
                </div>
                <div class="modal-body">
                    ${n}
                </div>
            `),s.innerHTML=`
            <div class="modal-content modal-${e}" style="width: ${o}px;">
               ${g}
            </div>
        `;const c=document.activeElement;d.appendChild(s);const b=s.querySelector("#close-modal-btn");if(b)b.addEventListener("click",W);else{const l=s.querySelector(".close-button, .cancel-button");l&&l.addEventListener("click",W)}i&&s.addEventListener("click",l=>{l.target===s&&(l.stopPropagation(),l.preventDefault())});const C=l=>{if(l.key==="Escape"&&Se){const y=Array.from(u.querySelectorAll(".infi-chatgpt-modal"));y[y.length-1]===s&&W()}};document.addEventListener("keydown",C),s._escKeyHandler=C,s._previouslyFocusedElement=c;const T=s.querySelector(".modal-content");if(T){T.setAttribute("role","dialog"),T.setAttribute("aria-modal","true");const l=T.querySelector("h2[id]");l?T.setAttribute("aria-labelledby",l.id):T.setAttribute("aria-label",t);const y=T.querySelectorAll('button, [href], input, select, textarea, [tabindex]:not([tabindex="-1"])');let m=y[0];m&&m.classList.contains("modal-close")&&y.length>1&&(m=y[1]),m&&setTimeout(()=>m.focus(),100)}s.addEventListener("keydown",l=>{if(l.key==="Escape"){const y=Array.from(u.querySelectorAll(".infi-chatgpt-modal"));y[y.length-1]===s&&W()}}),s.addEventListener("click",l=>{l.target===s&&W()});const q=l=>{if(!l.target||l.target===document||l.target===window||!document.contains(l.target))return;const y=Array.from(u.querySelectorAll(".infi-chatgpt-modal"));if(!y.length)return;const m=y[y.length-1];m&&!m.contains(l.target)&&u.contains(m)&&setTimeout(()=>{if(u.contains(m)&&!document.activeElement?.matches('input[type="text"], input[type="search"]')){const h=m.querySelector('input, button, select, textarea, [tabindex]:not([tabindex="-1"])');if(h)try{h.focus()}catch{}}},50)};document.addEventListener("focusin",q),s._focusInHandler=q,Se=!0,w.modalType=e}function io(){if(!u)return;const e=Array.from(u.querySelectorAll(".infi-chatgpt-modal"));e.reverse().forEach(t=>{t._escKeyHandler&&document.removeEventListener("keydown",t._escKeyHandler),t._focusInHandler&&document.removeEventListener("focusin",t._focusInHandler),t.remove()}),e.length>0&&(Se=!1,w.modalType=null)}function W(){const e=u?Array.from(u.querySelectorAll(".infi-chatgpt-modal")):[],t=Array.from(document.body.querySelectorAll('.infi-chatgpt-modal[data-gemini-toolbox-modal="true"]')),n=[...e,...t];if(n.length===0){Se=!1,w.modalType=null;return}const o=n[n.length-1];o&&(o.classList.add("closing"),setTimeout(()=>{try{const i=o._isPortal?document.body:u;if(i&&i.contains(o)&&i.removeChild(o),o._escKeyHandler&&document.removeEventListener("keydown",o._escKeyHandler),o._focusInHandler&&document.removeEventListener("focusin",o._focusInHandler),o._previouslyFocusedElement&&o._previouslyFocusedElement.focus)try{o._previouslyFocusedElement.focus()}catch{}}catch(r){console.error("[Gemini Toolbox] Error closing modal:",r)}},100)),setTimeout(()=>{const r=u?Array.from(u.querySelectorAll(".infi-chatgpt-modal")):[],i=Array.from(document.body.querySelectorAll('.infi-chatgpt-modal[data-gemini-toolbox-modal="true"]')),a=[...r,...i].pop();if(a){const d=a._childOpener||a.querySelector('input, button, select, textarea, [tabindex]:not([tabindex="-1"])');try{d&&d.focus&&d.focus()}catch{}Se=!0,w.modalType=a.id||null}else Se=!1,w.modalType=null},120)}function dt(e,t,n="Confirm",o=!1){return new Promise(r=>{const i=`confirm-dialog-${Date.now()}`,d=`
                <div style="margin-bottom: 24px;">
                    <div style="display: flex; align-items: center; gap: 12px; margin-bottom: 16px;">
                        ${o?`<svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="var(--gf-accent-danger, #ea4335)" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                    <path d="M3 6h18"></path>
                    <path d="M19 6v14a2 2 0 01-2 2H7a2 2 0 01-2-2V6m3 0V4a2 2 0 012-2h4a2 2 0 012 2v2"></path>
                    <line x1="10" y1="11" x2="10" y2="17"></line>
                    <line x1="14" y1="11" x2="14" y2="17"></line>
                   </svg>`:`<svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="var(--gf-accent-warning, #fbbc04)" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                    <circle cx="12" cy="12" r="10"/>
                    <line x1="12" y1="8" x2="12" y2="12"/>
                    <line x1="12" y1="16" x2="12.01" y2="16"/>
                   </svg>`}
                        <p style="margin: 0; font-size: 15px; color: var(--gf-text-primary); line-height: 1.5;">
                            ${t}
                        </p>
                    </div>
                </div>
                <div style="display: flex; gap: 12px; justify-content: flex-end;">
                    <button id="confirm-cancel-btn" class="btn-secondary" style="padding: 10px 20px; border-radius: 8px; border: 1px solid var(--gf-border-color); background: var(--gf-bg-secondary); color: var(--gf-text-primary); cursor: pointer; font-size: 14px; font-weight: 500; transition: all 0.2s;">
                        Cancel
                    </button>
                    <button id="confirm-action-btn" class="btn-primary" style="padding: 10px 20px; border-radius: 8px; border: none; background: ${o?"var(--gf-accent-danger, #ea4335)":"var(--gf-accent-primary)"}; color: white; cursor: pointer; font-size: 14px; font-weight: 500; transition: all 0.2s;">
                        ${n}
                    </button>
                </div>
            `;le(i,e,d,480),setTimeout(()=>{const p=u.querySelector(`#${i}`);if(!p){r(!1);return}const s=p.querySelector("#confirm-action-btn"),g=p.querySelector("#confirm-cancel-btn"),c=()=>{W(),r(!0)},b=()=>{W(),r(!1)};s&&s.addEventListener("click",c),g&&g.addEventListener("click",b);const C=p.querySelector("#close-modal-btn");C&&C.addEventListener("click",b)},50)})}async function Qo(){const e=u.getElementById("folder-list-container");if(!e)return;e.innerHTML="";const t=w.folders;if(t.length===0){e.innerHTML='<p>No folders yet. Click "Add Folder" to create one.</p>';return}t.forEach(n=>{const o=oo(n);e.innerHTML+=o}),so()}function so(){u.querySelectorAll(".folder-item").forEach(e=>{e.addEventListener("click",lo)}),u.querySelectorAll(".item-checkbox").forEach(e=>{e.addEventListener("change",kt)}),u.querySelectorAll(".add-chats-btn").forEach(e=>{e.addEventListener("click",t=>{t.stopPropagation();const n=t.currentTarget.dataset.folderId;pt(n)})})}function lo(e){if(e.target.type==="checkbox")return;const t=e.currentTarget.dataset.id;Lt(t)}function kt(e){const t=e.target.dataset.folderId;e.target.checked?w.selectedItems.includes(t)||w.selectedItems.push(t):w.selectedItems=w.selectedItems.filter(n=>n!==t),Ct()}function Ct(){const e=u.querySelector("#remove-selected-btn");e&&(e.disabled=w.selectedItems.length===0)}async function Et(){const e=u.querySelector("#manage-folders-modal");if(!e)return;const t=e.querySelector(".modal-content");if(!t)return;t._clickHandler&&t.removeEventListener("click",t._clickHandler),t._clickHandler=r=>{const i=r.target;if(i.closest("#close-modal-btn")||i.closest("#close-manage-folders-btn")||i.closest("#done-manage-folders-btn"))W();else if(i.closest("#add-folder-btn"))ct();else if(i.closest(".add-subfolder-btn")){const a=i.closest(".add-subfolder-btn").dataset.parentId;ct(!1,null,a)}else if(i.closest(".add-chats-btn")){const a=i.closest(".add-chats-btn").dataset.folderId;pt(a)}else if(i.closest(".edit-folder-btn")){const a=i.closest(".edit-folder-btn").dataset.folderId;ct(!0,a)}else if(i.closest(".delete-folder-btn")){const a=i.closest(".delete-folder-btn").dataset.folderId,d=w.folders.find(p=>p.id===a);d&&go(a,d.name)}else if(i.closest("#remove-selected-btn")){const a=e.querySelectorAll(".folder-checkbox:checked");a.length>0&&uo(a)}else if(i.closest(".premium-folder-name")){const a=i.closest(".premium-folder-item").dataset.folderId;Lt(a)}},t.addEventListener("click",t._clickHandler),t._changeHandler&&t.removeEventListener("change",t._changeHandler),t._changeHandler=r=>{r.target.classList.contains("folder-checkbox")?kt(r):r.target.matches("#hide-foldered-toggle")&&(w.settings.hideFolderedChats=r.target.checked,Ne(),De(),window.geminiAPI&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.FEATURE_TOGGLED,{feature:"hideFolderedChats",enabled:r.target.checked}))},t.addEventListener("change",t._changeHandler);const n=e.querySelector("#search-folders-input"),o=e.querySelector("#folder-list-container");n&&o&&n.addEventListener("input",r=>{const i=r.target.value.toLowerCase(),a=e.querySelectorAll(".premium-folder-item");let d=0;a.forEach(s=>{const c=s.querySelector(".premium-folder-name").textContent.toLowerCase().includes(i);s.style.display=c?"flex":"none",c&&d++});const p=o.querySelector(".premium-empty-state");p&&p.remove(),d===0&&i&&o.insertAdjacentHTML("beforeend",`
                        <div class="premium-empty-state">
                            <svg width="48" height="48" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.5" style="margin: 0 auto 16px; opacity: 0.4;">
                                <circle cx="11" cy="11" r="8"></circle>
                                <path d="m21 21-4.35-4.35"></path>
                            </svg>
                            <p style="margin: 0; font-size: 14px;">No folders found matching "${i}"</p>
                        </div>
                    `)}),Ct()}function co(e=!1,t=null,n=null){const o=u.querySelector("#add-folder-modal");if(!o)return;const r=o.querySelector("#add-folder-form"),i=o.querySelector("#folder-name-input"),a=o.querySelector("#save-folder-btn"),d=o.querySelector(".cancel-action");if(!r||!i||!a)return;const p=()=>{o&&o.parentNode&&o.remove()},s=async g=>{g.preventDefault(),g.stopPropagation();const c=i.value.trim();if(!c)return;const b=window.geminiAPI;let C=null;if(e){const T=w.folders.find(q=>q.id===t);T&&(T.name=c)}else{if(n){let l=!1;try{b&&typeof b.getSubscriptionStatus=="function"&&(l=!!(await b.getSubscriptionStatus())?.isPremium)}catch{}if(!l){b&&CONFIG.ANALYTICS_EVENTS&&b.trackEvent(CONFIG.ANALYTICS_EVENTS.LIMIT_HIT,{feature:"subfolders",message:"Subfolders are a premium feature"}),p(),Ye("subfolders",{allowed:!1,limit:"Premium only",count:0,message:"Subfolders are a Premium feature"});return}}let T=null;try{b&&typeof b.checkFeatureLimit=="function"&&(T=await b.checkFeatureLimit("folders",!1))}catch{}if(!T){const l=typeof CONFIG<"u"&&CONFIG.FREE_LIMITS&&typeof CONFIG.FREE_LIMITS.folders=="number"?CONFIG.FREE_LIMITS.folders:2,y=Array.isArray(w.folders)?w.folders.length:0;T={allowed:y<l,limit:l,count:y,remaining:Math.max(0,l-y),unlimited:!1}}if(!T.allowed){b&&CONFIG.ANALYTICS_EVENTS&&b.trackEvent(CONFIG.ANALYTICS_EVENTS.LIMIT_HIT,{feature:"folders",currentCount:typeof T.count=="number"?T.count:w.folders.length,limit:typeof T.limit=="number"?T.limit:CONFIG.FREE_LIMITS?.folders??2}),p(),Ye("folders",T);return}window.geminiStorage||(window.geminiStorage=new GeminiToolboxStorage,await window.geminiStorage.initialize());const q=await window.geminiStorage.createFolder(c,n);C=q,w.folders.push({id:q.id,name:q.name,chatIds:q.chatIds||[],parentId:q.parentId});try{b&&CONFIG.ANALYTICS_EVENTS&&b.trackEvent(CONFIG.ANALYTICS_EVENTS.FOLDER_CREATED,{folderName:c,isSubfolder:!!n,totalFolders:w.folders.length})}catch{}}if(Ne(),p(),Ue(),!e&&C&&(!C.chatIds||C.chatIds.length===0))try{pt(C.id)}catch{}};r.addEventListener("submit",s),a.addEventListener("click",s),d&&d.addEventListener("click",g=>{g.preventDefault(),g.stopPropagation(),p()}),i.focus()}function po(e){const t=u.querySelector("#add-chats-modal");if(!t)return;const n=t.querySelector("#save-add-chats"),o=t.querySelector(".cancel-action"),r=t.querySelector("#add-chat-search"),i=t.querySelector("#select-all-chats"),a=t.querySelector("#add-chats-list-container"),d=t.querySelector("#add-chats-search-loading"),p=t.querySelector("#add-chats-search-status");let s=[],g=new Set,c=!1,b=null;t.querySelectorAll(".chat-item").forEach(m=>{const h=m.querySelector(".chat-select-checkbox")?.dataset.chatId,x=m.querySelector(".item-title")?.textContent||"";h&&(s.push({id:h,title:x}),g.add(h))});async function T(){const m=document.querySelector("conversations-list")||document.querySelector('[role="navigation"]')||q(document.querySelector('[data-test-id="conversation"]'));if(m){m.scrollTop=m.scrollHeight,m.dispatchEvent(new Event("scroll",{bubbles:!0})),await new Promise(x=>setTimeout(x,50));const h=Array.from(Z()).pop();if(h){h.scrollIntoView({block:"end"});const x=new WheelEvent("wheel",{deltaY:100,bubbles:!0,cancelable:!0});m.dispatchEvent(x)}await new Promise(x=>setTimeout(x,200))}}function q(m){if(!m)return null;let h=m.parentElement;for(;h&&h!==document.body;){if(h.scrollHeight>h.clientHeight)return h;h=h.parentElement}return null}async function l(){if(c)return;d&&(d.style.display="block"),p&&(p.textContent="Searching all conversations...");let m=0;const h=5;for(;m<h;){const x=s.length;await T(),await new Promise(E=>setTimeout(E,500));const f=me(),S=new Set;w.folders.forEach(E=>{E.chatIds.forEach(k=>S.add(k))});const P=f.filter(E=>E.id&&!S.has(E.id)&&!g.has(E.id));P.length>0?(P.forEach(E=>{g.add(E.id),s.push(E)}),m=0,p&&(p.textContent=`Searching... (${s.length} found)`)):m++,await new Promise(E=>setTimeout(E,100))}for(let x=0;x<2;x++){await T();const f=me(),S=new Set;w.folders.forEach(E=>{E.chatIds.forEach(k=>S.add(k))});const P=f.filter(E=>E.id&&!S.has(E.id)&&!g.has(E.id));P.length>0&&P.forEach(E=>{g.add(E.id),s.push(E)})}c=!0,d&&(d.style.display="none")}function y(m){const h=m.toLowerCase(),x=h?s.filter(f=>f.title.toLowerCase().includes(h)):s;if(x.length>0){const f=x.map(S=>`
                    <div class="list-item chat-item">
                        <input type="checkbox" class="chat-select-checkbox" data-chat-id="${S.id}">
                        <span class="item-title">${S.title}</span>
                    </div>
                `).join("");a.innerHTML=f}else a.innerHTML='<p style="color: var(--gf-text-secondary); text-align: center; margin-top: 20px;">No matching conversations found.</p>'}r&&r.addEventListener("input",async m=>{const h=m.target.value.trim();b&&clearTimeout(b),h&&!c?b=setTimeout(async()=>{await l(),y(h)},300):y(h)}),i&&i.addEventListener("change",async m=>{const h=m.target.checked;if(h&&!c){i.disabled=!0,await l();const f=r?r.value.trim():"";y(f),i.disabled=!1}t.querySelectorAll('.chat-item:not([style*="display: none"]) .chat-select-checkbox').forEach(f=>{f.checked=h})}),a&&a.addEventListener("click",m=>{if(m.target&&(m.target.matches('input[type="checkbox"]')||m.target.closest('input[type="checkbox"]')))return;const h=m.target&&m.target.closest?m.target.closest(".chat-item"):null;if(!h)return;const x=h.querySelector(".chat-select-checkbox");x&&(x.checked=!x.checked)}),n.addEventListener("click",async()=>{const m=t.querySelectorAll(".chat-select-checkbox:checked"),h=Array.from(m).map(x=>x.dataset.chatId);if(h.length>0){const x=w.folders.find(f=>f.id===e);if(x){const f={};Array.from(m).forEach(S=>{const P=S.dataset.chatId,E=Z().find(k=>K(k)===P);if(E){const k=Ae(E),H=(qe(E)||E.querySelector("a[href]"))?.getAttribute("href");if(k)if(f[P]={title:k},H)f[P].url=H.startsWith("http")?H:`https://gemini.google.com${H.startsWith("/")?"":"/"}${H}`;else{const R=P.startsWith("c_")?P.substring(2):P;f[P].url=`https://gemini.google.com/app/${R}`}}else{const k=S.closest(".chat-item"),O=k?k.querySelector(".item-title"):null;if(O){const H=P.startsWith("c_")?P.substring(2):P;f[P]={title:O.textContent.trim(),url:`https://gemini.google.com/app/${H}`}}}});for(const S of h)x.chatIds.includes(S)||(x.chatIds.push(S),window.geminiStorage&&await window.geminiStorage.addChatToFolder(S,e,f[S]),f[S]&&(w.chatMetadata[S]={...w.chatMetadata[S]||{},...f[S],lastSeen:Date.now()}));await Ne(),window.geminiAPI&&window.geminiAPI.trackEvent&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.CHAT_ADDED_TO_FOLDER,{folderId:e,chatCount:h.length,totalChatsInFolder:x.chatIds.length})}}W(),Ue()}),o&&o.addEventListener("click",()=>{W()})}async function en(){const t=Z().map(o=>({id:K(o),title:Ae(o)})),n=new Set;return w.folders.forEach(o=>{o.chatIds.forEach(r=>n.add(r))}),t.filter(o=>o.id&&!n.has(o.id))}async function tn(){const e=me(),t=new Set;return w.folders.forEach(o=>{o.chatIds.forEach(r=>t.add(r))}),e.filter(o=>o.id&&!t.has(o.id))}function on(e){const t=u.querySelector("#add-chats-modal");if(!t)return;const n=t.querySelector("#add-chats-list-container");if(n)if(e.length>0){const o=e.map(r=>`
                <div class="list-item chat-item">
                    <input type="checkbox" class="chat-select-checkbox" data-chat-id="${r.id}">
                    <span class="item-title">${r.title}</span>
                </div>
            `).join("");n.innerHTML=o}else n.innerHTML='<p style="color: var(--gf-text-secondary); text-align: center; margin-top: 20px;">No available chats to add.</p>'}function mo(e){const t=[],n=w.folders.find(r=>r.id===e);return n&&n.chatIds&&t.push(...n.chatIds),w.folders.filter(r=>r.parentId===e).forEach(r=>{t.push(...mo(r.id))}),t}function nn(e){const t=new Set(e);function n(o){w.folders.filter(i=>i.parentId===o).forEach(i=>{t.add(i.id),n(i.id)})}e.forEach(o=>{n(o)}),w.folders=w.folders.filter(o=>!t.has(o.id))}function uo(e){const t=e.length,n=`
            <div style="margin-bottom: 24px;">
                <div style="display: flex; align-items: center; gap: var(--gap-medium); margin-bottom: var(--space-4);">
                    <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="var(--gf-accent-danger)" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                        <path d="M3 6h18"></path>
                        <path d="M19 6v14a2 2 0 01-2 2H7a2 2 0 01-2-2V6m3 0V4a2 2 0 012-2h4a2 2 0 012 2v2"></path>
                        <line x1="10" y1="11" x2="10" y2="17"></line>
                        <line x1="14" y1="11" x2="14" y2="17"></line>
                    </svg>
                    <p style="margin: 0; color: var(--gf-text-primary); font-size: 16px; font-weight: 500; line-height: 1.5;">
                        Are you sure you want to delete ${t} folder${t>1?"s":""} and all ${t>1?"their":"its"} contents?
                    </p>
                </div>
                <p style="margin: 0 0 0 36px; color: var(--gf-text-secondary); font-size: 14px;">
                    This action cannot be undone.
                </p>
            </div>
            <div class="modal-footer">
                <button type="button" class="button secondary cancel-action">Cancel</button>
                    <button type="button" id="confirm-bulk-delete" class="button danger" >
                        <svg width="16" height="16" viewBox="0 0 16 16" fill="currentColor" style="margin-right: 6px; vertical-align: middle;">
                            <path d="M2 4h12v9a1 1 0 01-1 1H3a1 1 0 01-1-1V4zm1.5-1.5h9V2a.5.5 0 00-.5-.5H4a.5.5 0 00-.5.5v.5zM6.5 6v5m3-5v5"/>
                        </svg>
                        Delete
                    </button>
            </div>
        `;le("confirm-bulk-delete-modal","Confirm Deletion",n,480),setTimeout(()=>{const o=u.querySelector("#confirm-bulk-delete"),r=u.querySelector("#confirm-bulk-delete-modal .button.secondary.cancel-action");o&&(o.onclick=()=>{const i=new Set;e.forEach(d=>{const p=d.closest(".list-item");if(p&&p.dataset.folderId){let g=function(c){w.folders.filter(C=>C.parentId===c).forEach(C=>{i.add(C.id),g(C.id)})};const s=p.dataset.folderId;i.add(s),g(s)}});const a=w.folders.filter(d=>i.has(d.id));window.geminiAPI&&CONFIG.ANALYTICS_EVENTS&&a.forEach(d=>{window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.FOLDER_DELETED,{folderName:d.name,hadChildren:w.folders.some(p=>p.parentId===d.id),wasSubfolder:!!d.parentId})}),w.folders=w.folders.filter(d=>!i.has(d.id)),Ne(),W(),Ue()}),r&&(r.onclick=()=>{W()})},100)}function go(e,t){const n=`
            <div style="margin-bottom: 24px;">
                <div style="display: flex; align-items: center; gap: var(--gap-medium); margin-bottom: var(--space-4);">
                    <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="var(--gf-accent-danger)" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                        <path d="M3 6h18"></path>
                        <path d="M19 6v14a2 2 0 01-2 2H7a2 2 0 01-2-2V6m3 0V4a2 2 0 012-2h4a2 2 0 012 2v2"></path>
                        <line x1="10" y1="11" x2="10" y2="17"></line>
                        <line x1="14" y1="11" x2="14" y2="17"></line>
                    </svg>
                    <p style="margin: 0; color: var(--gf-text-primary); font-size: 16px; font-weight: 500; line-height: 1.5;">
                        Are you sure you want to delete this folder?
                    </p>
                </div>
                <p style="margin: 0 0 0 36px; color: var(--gf-text-secondary); font-size: 14px;">
                    "<strong>${t}</strong>" will be permanently deleted. Chats in this folder will not be deleted and will remain in your conversation list. This action cannot be undone.
                </p>
            </div>
            <div class="modal-footer">
                <button type="button" class="button secondary cancel-action">Cancel</button>
                    <button type="button" id="confirm-delete-single" class="button danger" >
                        <svg width="16" height="16" viewBox="0 0 16 16" fill="currentColor" style="margin-right: 6px; vertical-align: middle;">
                            <path d="M2 4h12v9a1 1 0 01-1 1H3a1 1 0 01-1-1V4zm1.5-1.5h9V2a.5.5 0 00-.5-.5H4a.5.5 0 00-.5.5v.5zM6.5 6v5m3-5v5"/>
                        </svg>
                        Delete
                    </button>
            </div>
        `;le("confirm-delete-modal","Confirm Deletion",n,480),setTimeout(()=>{const o=u.querySelector("#confirm-delete-single"),r=u.querySelector("#confirm-delete-modal .button.secondary.cancel-action");o&&(o.onclick=()=>{const i=new Set([e]);function a(p){w.folders.filter(g=>g.parentId===p).forEach(g=>{i.add(g.id),a(g.id)})}a(e);const d=w.folders.filter(p=>i.has(p.id));window.geminiAPI&&CONFIG.ANALYTICS_EVENTS&&d.forEach(p=>{window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.FOLDER_DELETED,{folderName:p.name,hadChildren:w.folders.some(s=>s.parentId===p.id),wasSubfolder:!!p.parentId})}),w.folders=w.folders.filter(p=>!i.has(p.id)),Ne(),W(),Ue()}),r&&(r.onclick=()=>{W()})},100)}function Ue(){const e=u.querySelector("#manage-folders-modal");if(!e)return;const t=e.querySelector(".modal-content");if(!t)return;const n=t.querySelector("#search-folders-input"),o=n?n.value:"",r=t.querySelector("#hide-foldered-toggle"),i=r?r.checked:w.settings.hideFolderedChats,a=wt(),d=document.createElement("div");d.innerHTML=a;const p=d.querySelector(".premium-modal-body"),s=t.querySelector(".premium-modal-body");if(p&&s){s.innerHTML=p.innerHTML;const g=t.querySelector("#search-folders-input");g&&o&&(g.value=o,g.dispatchEvent(new Event("input")));const c=t.querySelector("#hide-foldered-toggle");c&&(c.checked=i),Et()}}function St(){const e=u&&u.querySelector("#manage-folders-modal");if(e){try{u.appendChild(e)}catch{}try{Ue()}catch{}const t=e.querySelector('button, [href], input, select, textarea, [tabindex]:not([tabindex="-1"])');t&&t.focus&&setTimeout(()=>t.focus(),50),Se=!0,w.modalType="manage-folders-modal";return}le("manage-folders-modal","Manage Folders",wt(),800),Et()}function ct(e=!1,t=null,n=null){const o=e?w.folders.find(i=>i.id===t):null;le("add-folder-modal",e?"Edit Folder":n?"Add Subfolder":"Add Folder",no(e,o?o.name:""),480),co(e,t,n)}async function pt(e){const t=w.folders.find(i=>i.id===e);if(!t)return;const n=me(),o=new Set;w.folders.forEach(i=>{i.chatIds.forEach(a=>o.add(a))});const r=n.filter(i=>i.id&&!o.has(i.id));le("add-chats-modal",`Add Chats to "${t.name}"`,ro(t,r),720),setTimeout(()=>{const i=u.querySelector("#add-chats-modal");if(!i)return;const a=i.querySelector("#add-chats-list-container");if(!a)return;const d=new Set;r.forEach(x=>{x.id&&d.add(x.id)});let p=!1,s=0;const g=3;let c=null;async function b(){const x=document.querySelector("conversations-list")||document.querySelector('[role="navigation"]')||C(document.querySelector('[data-test-id="conversation"]'));if(x){x.scrollTop=x.scrollHeight,x.dispatchEvent(new Event("scroll",{bubbles:!0})),await new Promise(S=>setTimeout(S,50));const f=Array.from(Z()).pop();if(f){f.scrollIntoView({block:"end"});const S=new WheelEvent("wheel",{deltaY:100,bubbles:!0,cancelable:!0});x.dispatchEvent(S)}await new Promise(S=>setTimeout(S,200))}}function C(x){if(!x)return null;let f=x.parentElement;for(;f&&f!==document.body;){if(f.scrollHeight>f.clientHeight)return f;f=f.parentElement}return null}async function T(){if(p||s>=g)return;p=!0;const x=document.createElement("div");x.style.cssText="text-align: center; padding: 10px; color: var(--gf-text-secondary);",x.innerHTML='<div style="display: inline-block; width: 20px; height: 20px; border: 2px solid var(--gf-border-color); border-top-color: var(--gf-accent-primary); border-radius: 50%; animation: spin 1s linear infinite;"></div> Loading more...',a.appendChild(x);try{await b(),await new Promise(E=>setTimeout(E,500));const f=me(),S=new Set;w.folders.forEach(E=>{E.chatIds.forEach(k=>S.add(k))});const P=f.filter(E=>E.id&&!S.has(E.id)&&!d.has(E.id));if(P.length>0){s=0,P.forEach(k=>{d.add(k.id);const O=document.createElement("div");O.className="list-item chat-item",O.innerHTML=`
                                <input type="checkbox" class="chat-select-checkbox" data-chat-id="${k.id}">
                                <span class="item-title">${k.title}</span>
                            `,a.insertBefore(O,x)});const E=i.querySelector("#add-chat-search");if(E&&E.value){const k=E.value.toLowerCase();i.querySelectorAll(".chat-item").forEach(H=>{const R=H.querySelector(".item-title").textContent.toLowerCase();H.style.display=R.includes(k)?"":"none"})}}else s++}catch{s++}finally{x.parentNode&&x.remove(),p=!1}}a.addEventListener("scroll",()=>{if(s>=g||p)return;const{scrollTop:x,scrollHeight:f,clientHeight:S}=a;f-x-S<100&&T()});function q(){if(c)return;c=new MutationObserver(f=>{let S=!1;f.forEach(P=>{P.addedNodes.forEach(E=>{E.nodeType===Node.ELEMENT_NODE&&(E.matches('[data-test-id="conversation"]')?[E]:E.querySelectorAll('[data-test-id="conversation"]')).forEach(O=>{const H=K(O);H&&!d.has(H)&&(S=!0)})})}),S&&setTimeout(()=>l(),50)});const x=document.querySelector("conversations-list");x&&c.observe(x,{childList:!0,subtree:!0})}function l(){const x=me(),f=new Set;w.folders.forEach(P=>{P.chatIds.forEach(E=>f.add(E))});const S=x.filter(P=>P.id&&!f.has(P.id)&&!d.has(P.id));if(S.length>0){s=0,S.forEach(E=>{d.add(E.id);const k=document.createElement("div");k.className="list-item chat-item",k.innerHTML=`
                            <input type="checkbox" class="chat-select-checkbox" data-chat-id="${E.id}">
                            <span class="item-title">${E.title}</span>
                        `,a.appendChild(k)});const P=i.querySelector("#add-chat-search");if(P&&P.value){const E=P.value.toLowerCase();i.querySelectorAll(".chat-item").forEach(O=>{const H=O.querySelector(".item-title").textContent.toLowerCase();O.style.display=H.includes(E)?"":"none"})}}}q();const y=new MutationObserver(x=>{x.forEach(f=>{f.removedNodes.forEach(S=>{(S===i||S.contains&&S.contains(i))&&(c&&(c.disconnect(),c=null),y.disconnect())})})});y.observe(document.body,{childList:!0,subtree:!0});async function m(){const x=i.querySelector("#select-all-chats");if(!x)return;const f=x.parentElement;if(f.lastChild&&f.lastChild.nodeType===Node.TEXT_NODE)f.lastChild.textContent=" Loading all conversations...";else{const k=f.querySelector("span");k&&(k.textContent="Loading all conversations...")}x.disabled=!0;let S=0;const P=5;let E=0;for(;S<P;){const k=a.querySelectorAll(".chat-item").length;await b(),await new Promise(R=>setTimeout(R,300));const O=a.querySelectorAll(".chat-item").length,H=O-k;if(H>0)if(E+=H,S=0,f.lastChild&&f.lastChild.nodeType===Node.TEXT_NODE)f.lastChild.textContent=` Loading... (${O} conversations)`;else{const R=f.querySelector("span");R&&(R.textContent=`Loading... (${O} conversations)`)}else S++}for(let k=0;k<2;k++)await b(),await new Promise(O=>setTimeout(O,200));if(x.disabled=!1,f.lastChild&&f.lastChild.nodeType===Node.TEXT_NODE)f.lastChild.textContent=" Select All";else{const k=f.querySelector("span");k&&(k.textContent="Select All")}s=0}const h=i.querySelector("#select-all-chats");if(h){const x=h.onchange;h.onchange=null,h.addEventListener("change",async f=>{if(f.target.checked){await m();const P=new Set;w.settings.hideFolderedChats&&w.folders.forEach(k=>{k.chatIds.forEach(O=>P.add(O))}),i.querySelectorAll('.chat-item:not([style*="display: none"]) .chat-select-checkbox').forEach(k=>{const O=k.dataset.chatId;(!w.settings.hideFolderedChats||!P.has(O))&&(k.checked=!0)})}else i.querySelectorAll('.chat-item:not([style*="display: none"]) .chat-select-checkbox').forEach(E=>{E.checked=!1})})}po(e)},100)}function Lt(e){const t=w.folders.find(n=>n.id===e);t&&(le("manage-single-folder-modal",`Manage "${t.name}"`,It(t),640),At(e))}function ho(e){const n=new Date(e.pinnedAt).toLocaleDateString("en-US",{weekday:"long",year:"numeric",month:"long",day:"numeric",hour:"2-digit",minute:"2-digit"});let o=e.messageContent;o=o.replace(/Show thinking\s*/gi,""),o=o.replace(/^\s*Thinking\.\.\.\s*/gi,"");const r=`
            <div class="modal-header" style="
                padding: 16px 24px;
                border-bottom: 1px solid var(--gf-border-color);
                background: var(--gf-bg-secondary);
                display: flex;
                justify-content: space-between;
                align-items: flex-start;
            ">
                <div style="flex: 1;">
                    <div style="display: flex; align-items: center; gap: 8px; margin-bottom: 8px;">
                        <span style="font-size: 20px;">\u{1F4CC}</span>
                        <span style="font-weight: 600; font-size: 16px; color: var(--gf-text-primary);">Pinned Message</span>
                    </div>
                    <div style="font-size: 13px; color: var(--gf-text-secondary);">
                        ${n} \xB7 ${i(e.conversationTitle||"Untitled Chat")}
                    </div>
                </div>
                <button class="modal-close" id="close-modal-btn" aria-label="Close" style="
                    background: none;
                    border: none;
                    cursor: pointer;
                    padding: 4px;
                    display: flex;
                    align-items: center;
                    justify-content: center;
                    opacity: 0.7;
                    transition: opacity 0.2s;
                ">
                    <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" width="20" height="20" aria-hidden="true">
                        <line x1="18" y1="6" x2="6" y2="18"></line>
                        <line x1="6" y1="6" x2="18" y2="18"></line>
                    </svg>
                </button>
            </div>
            <div class="modal-body" style="display: flex; flex-direction: column; height: 100%; max-height: 70vh; padding: 0;">
                
                <div style="
                    flex: 1 1 auto;
                    overflow-y: auto;
                    padding: 24px;
                    background: var(--gf-bg-primary);
                    min-height: 0;
                ">
                    ${e.images&&e.images.length>0?`
                        <div style="
                            display: grid;
                            grid-template-columns: repeat(auto-fill, minmax(200px, 1fr));
                            gap: 12px;
                            margin-bottom: 20px;
                            padding: 12px;
                            background: var(--gf-bg-secondary);
                            border-radius: 8px;
                        ">
                            ${e.images.map(a=>`
                                <div style="
                                    position: relative;
                                    border-radius: 8px;
                                    overflow: hidden;
                                    border: 1px solid var(--gf-border-color);
                                    cursor: pointer;
                                    transition: transform 0.2s ease;
                                " class="pinned-image-card">
                                    <img src="${a.src}" alt="${i(a.alt)}" style="
                                        width: 100%;
                                        height: auto;
                                        display: block;
                                    " />
                                    ${a.type==="generated"?'<div style="position: absolute; top: 4px; right: 4px; background: rgba(0,0,0,0.7); color: white; padding: 2px 6px; border-radius: 4px; font-size: 10px;">AI Generated</div>':""}
                                </div>
                            `).join("")}
                        </div>
                    `:""}
                    <div style="
                        font-size: 14px;
                        line-height: 1.6;
                        color: var(--gf-text-primary);
                        white-space: pre-wrap;
                        word-break: break-word;
                    ">${i(o)}</div>
                </div>
                
                <div style="
                    flex-shrink: 0;
                    padding: 16px 24px;
                    border-top: 1px solid var(--gf-border-color);
                    background: var(--gf-bg-secondary);
                    display: flex;
                    justify-content: space-between;
                    align-items: center;
                    gap: 12px;
                ">
                    <button id="delete-this-pin-btn" class="premium-button" style="
                        background: var(--gf-accent-danger);
                        color: white;
                        border: none;
                        padding: 10px 20px;
                        border-radius: 6px;
                        cursor: pointer;
                        font-size: 14px;
                        font-weight: 500;
                        transition: all 0.2s ease;
                    ">
                        <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" style="vertical-align: middle; margin-right: 6px;">
                            <path d="M19 7l-.867 12.142A2 2 0 0116.138 21H7.862a2 2 0 01-1.995-1.858L5 7m5 4v6m4-6v6m1-10V4a1 1 0 00-1-1h-4a1 1 0 00-1 1v3M4 7h16"/>
                        </svg>
                        Delete Pin
                    </button>
                    <button id="show-in-chat-btn" class="premium-button premium-button-primary" style="
                        background: var(--gf-accent-primary);
                        color: white;
                        border: none;
                        padding: 10px 20px;
                        border-radius: 6px;
                        cursor: pointer;
                        font-size: 14px;
                        font-weight: 500;
                        transition: all 0.2s ease;
                    ">
                        <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" style="vertical-align: middle; margin-right: 6px;">
                            <path d="M10 6H6a2 2 0 00-2 2v10a2 2 0 002 2h10a2 2 0 002-2v-4M14 4h6m0 0v6m0-6L10 14"/>
                        </svg>
                        Show in Chat
                    </button>
                </div>
            </div>
        `;le("full-pinned-message-modal","",r,700),setTimeout(()=>{const a=u.querySelector("#full-pinned-message-modal");if(!a)return;const d=a.querySelector("#close-modal-btn");d&&(d.addEventListener("mouseenter",()=>{d.style.opacity="1"}),d.addEventListener("mouseleave",()=>{d.style.opacity="0.7"})),a.querySelectorAll(".pinned-image-card").forEach((c,b)=>{c.addEventListener("click",()=>{const C=c.querySelector("img");C&&C.src&&window.open(C.src,"_blank")}),c.addEventListener("mouseenter",()=>{c.style.transform="scale(1.02)",c.style.boxShadow="0 4px 8px rgba(0,0,0,0.2)"}),c.addEventListener("mouseleave",()=>{c.style.transform="scale(1)",c.style.boxShadow="none"})});const s=a.querySelector("#delete-this-pin-btn"),g=a.querySelector("#show-in-chat-btn");s&&(s.addEventListener("mouseenter",()=>{s.style.opacity="0.9"}),s.addEventListener("mouseleave",()=>{s.style.opacity="1"}),s.addEventListener("click",async()=>{if(await dt("Delete Pinned Message","Are you sure you want to delete this pinned message?","Delete",!0))try{const b=window.GeminiToolboxStorage?new window.GeminiToolboxStorage:null;b&&(await b.initialize(),await b.deletePinnedMessage(e.messageId),W(),u.querySelector("#pinned-messages-modal, #chat-tools-modal")&&(W(),je("pinned")),window.showToast&&window.showToast("Pinned message deleted","success"))}catch(b){console.error("[Pinned Messages] Delete error:",b),window.showToast&&window.showToast("Failed to delete message","error")}})),g&&(g.addEventListener("mouseenter",()=>{g.style.opacity="0.9"}),g.addEventListener("mouseleave",()=>{g.style.opacity="1"}),g.addEventListener("click",()=>{console.log("[Pinned Messages] Navigating to conversation ID:",e.conversationId),console.log("[Pinned Messages] Full message object:",e);const c=`https://gemini.google.com/app/${e.conversationId}`;console.log("[Pinned Messages] Target URL:",c),window.location.href=c}))},100);function i(a){const d=document.createElement("div");return d.textContent=a,d.innerHTML}}function fo(){const e=u.querySelector("#pinned-messages-modal")||u.querySelector("#chat-tools-modal");if(!e)return;const t=e.querySelector("#pinned-messages-list"),n=e.querySelector("#pinned-messages-loading"),o=e.querySelector("#pinned-messages-search"),r=e.querySelector("#pinned-messages-counter"),i=e.querySelector("#clear-all-pins-btn"),a=window.GeminiToolboxStorage?new window.GeminiToolboxStorage:null;if(!a){n.innerHTML='<p style="color: var(--gf-accent-danger);">Storage not available. Please refresh the page.</p>';return}function d(c){t.innerHTML="",c.forEach(b=>{const C=document.createElement("div");C.className="pinned-message-card",C.style.cssText=`
                    background: var(--gf-bg-secondary);
                    border: 1px solid var(--gf-border-color);
                    border-radius: 8px;
                    padding: 16px;
                    margin-bottom: 12px;
                    cursor: pointer;
                    transition: all 0.2s ease;
                `,C.addEventListener("mouseenter",()=>{C.style.background="var(--gf-bg-tertiary)",C.style.borderColor="var(--gf-accent-primary)"}),C.addEventListener("mouseleave",()=>{C.style.background="var(--gf-bg-secondary)",C.style.borderColor="var(--gf-border-color)"});const q=new Date(b.pinnedAt).toLocaleDateString("en-US",{month:"short",day:"numeric",year:"numeric"});let l=b.messageContent;l=l.replace(/Show thinking\s*/gi,""),l=l.replace(/^\s*Thinking\.\.\.\s*/gi,"");const y=l.length>300?l.substring(0,300)+"...":l;C.innerHTML=`
                    <div style="display: flex; justify-content: space-between; align-items: start; margin-bottom: 8px;">
                        <div style="flex: 1;">
                            <div style="font-size: 12px; color: var(--gf-text-tertiary); margin-bottom: 4px;">
                                \u{1F4CC} ${q}${b.images&&b.images.length>0?` \u2022 \u{1F5BC}\uFE0F ${b.images.length} image${b.images.length!==1?"s":""}`:""}
                            </div>
                            <div style="font-size: 12px; color: var(--gf-text-secondary); margin-bottom: 8px;">
                                From: <strong>${b.conversationTitle||"Untitled Chat"}</strong>
                            </div>
                        </div>
                        <button class="delete-pin-btn" data-message-id="${b.messageId}" style="
                            background: none;
                            border: none;
                            color: var(--gf-accent-danger);
                            cursor: pointer;
                            padding: 4px 8px;
                            border-radius: 4px;
                            transition: background 0.2s ease;
                        " title="Delete pinned message">
                            <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                <path d="M19 7l-.867 12.142A2 2 0 0116.138 21H7.862a2 2 0 01-1.995-1.858L5 7m5 4v6m4-6v6m1-10V4a1 1 0 00-1-1h-4a1 1 0 00-1 1v3M4 7h16"/>
                            </svg>
                        </button>
                    </div>
                    ${b.images&&b.images.length>0?`
                        <div style="
                            display: flex;
                            gap: 8px;
                            margin-bottom: 12px;
                            overflow-x: auto;
                            padding: 8px 0;
                        ">
                            ${b.images.slice(0,3).map(h=>`
                                <div style="
                                    flex-shrink: 0;
                                    width: 80px;
                                    height: 80px;
                                    border-radius: 6px;
                                    overflow: hidden;
                                    border: 1px solid var(--gf-border-color);
                                    position: relative;
                                ">
                                    <img src="${h.src}" alt="${g(h.alt)}" style="
                                        width: 100%;
                                        height: 100%;
                                        object-fit: cover;
                                    " />
                                    ${h.type==="generated"?'<div style="position: absolute; bottom: 2px; right: 2px; background: rgba(0,0,0,0.7); color: white; padding: 1px 4px; border-radius: 3px; font-size: 8px;">AI</div>':""}
                                </div>
                            `).join("")}
                            ${b.images.length>3?`<div style="width: 80px; height: 80px; border-radius: 6px; background: var(--gf-bg-tertiary); display: flex; align-items: center; justify-content: center; font-size: 12px; color: var(--gf-text-secondary);">+${b.images.length-3}</div>`:""}
                        </div>
                    `:""}
                    <div style="
                        font-size: 14px;
                        line-height: 1.5;
                        color: var(--gf-text-primary);
                        white-space: pre-wrap;
                        word-break: break-word;
                    ">${g(y)}</div>
                `,C.addEventListener("click",h=>{h.target.closest(".delete-pin-btn")||ho(b)});const m=C.querySelector(".delete-pin-btn");m.addEventListener("mouseenter",()=>{m.style.background="rgba(234, 67, 53, 0.1)"}),m.addEventListener("mouseleave",()=>{m.style.background="none"}),m.addEventListener("click",async h=>{if(h.stopPropagation(),await dt("Delete Pinned Message","Are you sure you want to delete this pinned message?","Delete",!0))try{await a.deletePinnedMessage(b.messageId),C.remove();const f=t.querySelectorAll(".pinned-message-card").length;r.textContent=`${f} pinned message${f!==1?"s":""}`,f===0&&(t.innerHTML='<div style="text-align: center; padding: 60px 20px; color: var(--gf-text-secondary);"><p>No pinned messages</p></div>'),window.showToast&&window.showToast("Pinned message deleted","success")}catch(f){console.error("[Pinned Messages] Delete error:",f),window.showToast&&window.showToast("Failed to delete message","error")}}),t.appendChild(C)})}a.initialize().then(()=>{const c=a.getAllPinnedMessages();if(n.style.display="none",c.length===0){t.innerHTML='<div style="text-align: center; padding: 60px 20px; color: var(--gf-text-secondary);"><p style="font-size: 16px; margin-bottom: 8px;">No pinned messages yet</p><p style="font-size: 14px;">Pin important messages by clicking the bookmark icon next to any AI response.</p></div>',r.textContent="0 pinned messages";return}if(r.textContent=`${c.length} pinned message${c.length!==1?"s":""}`,d(c),o){let b;const C=()=>{clearTimeout(b),b=setTimeout(()=>{const T=(o.value||"").trim();try{const q=T?a.searchPinnedMessages(T):a.getAllPinnedMessages();if(!q||q.length===0){t.innerHTML='<div style="text-align: center; padding: 60px 20px; color: var(--gf-text-secondary);"><p>No matching pinned messages</p></div>',r.textContent="0 pinned messages";return}d(q),r.textContent=`${q.length} pinned message${q.length!==1?"s":""}`}catch(q){console.error("[Pinned Messages] Search error:",q)}},300)};o.addEventListener("input",C),o.addEventListener("search",C)}}).catch(c=>{console.error("[Pinned Messages] Error loading:",c),n.innerHTML='<p style="color: var(--gf-accent-danger);">Failed to load pinned messages.</p>'}),i&&i.addEventListener("click",async()=>{if(await dt("Clear All Pinned Messages","Are you sure you want to delete ALL pinned messages? This action cannot be undone.","Delete All",!0))try{const b=a.getAllPinnedMessages();for(const C of b)await a.deletePinnedMessage(C.id);t.innerHTML='<div style="text-align: center; padding: 60px 20px; color: var(--gf-text-secondary);"><p style="font-size: 16px; margin-bottom: 8px;">No pinned messages yet</p><p style="font-size: 14px;">Pin important messages by clicking the bookmark icon next to any AI response.</p></div>',r.textContent="0 pinned messages",window.showToast&&window.showToast("All pinned messages cleared","success")}catch(b){console.error("[Pinned Messages] Clear all error:",b),window.showToast&&window.showToast("Failed to clear messages","error")}});const p=e.querySelector("#pinned-tab-panel"),s=p?p.querySelector(".cancel-action"):e.querySelector(".cancel-action");s&&s.addEventListener("click",()=>{W()});function g(c){const b=document.createElement("div");return b.textContent=c,b.innerHTML}}function bo(){return`
            <div class="premium-modal-actions">
                <input type="search" id="export-chat-search" class="premium-search-input" placeholder="Search conversations..." aria-label="Search chats to export">
                <div id="export-chat-search-loading" style="display: none; padding: 8px 12px; margin-top: 8px; background: var(--gf-bg-secondary); border-radius: 4px; color: var(--gf-accent-primary); font-size: 13px;">
                    <div style="display: flex; align-items: center; gap: 8px;">
                        <div style="width: 14px; height: 14px; border: 2px solid var(--gf-accent-primary); border-top: 2px solid transparent; border-radius: 50%; animation: spin 1s linear infinite;"></div>
                        <span id="export-chat-search-status">Searching all conversations...</span>
                    </div>
                </div>
                <label class="premium-checkbox-label">
                    <input type="checkbox" id="export-chat-select-all" class="premium-checkbox select-all-checkbox">
                    <span>Select all</span>
                </label>
                <div class="format-select" style="margin-left:auto;">
                    <label for="export-chat-format">Format</label>
                    <select id="export-chat-format">
                        <option value="pdf" selected>PDF</option>
                        <option value="html">HTML</option>
                        <option value="md">Markdown</option>
                        <option value="txt">Text</option>
                        <option value="csv">CSV</option>
                    </select>
                </div>
            </div>
            <div class="premium-modal-body">
                <div id="export-chat-list">
                    <div id="export-chat-loading" style="text-align: center; padding: 40px;" role="status" aria-live="polite">
                        <div style="width: 40px; height: 40px; border: 3px solid var(--gf-border-color); border-top-color: var(--gf-accent-primary); border-radius: 50%; animation: spin 1s linear infinite; margin: 0 auto 16px;" aria-hidden="true"></div>
                        <p style="color: var(--gf-text-secondary);">Loading conversations...</p>
                    </div>
                    <div id="export-chat-loading-more" style="display: none; text-align: center; padding: var(--space-4); color: var(--gf-text-secondary);" role="status" aria-live="polite">
                        Loading more conversations...
                    </div>
                </div>
            </div>
            <div class="premium-modal-footer" style="flex-direction: column; align-items: stretch;">
                <div id="export-chat-status" style="display: none; padding: 0 0 12px 0;">
                    <div id="export-error-message" style="color: var(--gf-accent-danger); font-size: 14px; padding: var(--space-3); background: rgba(234, 67, 53, 0.1); border-radius: var(--space-2); display: none; margin-bottom: 12px;"></div>
                    <div id="export-progress" style="display: none;">
                        <p style="color: var(--gf-text-secondary); font-size: 14px; margin-bottom: var(--space-2);">Exporting <span id="export-current-count">0</span> of <span id="export-total-count">0</span> conversations...</p>
                        <div style="height: 4px; background: var(--gf-border-color); border-radius: 2px; overflow: hidden;">
                            <div id="export-progress-bar" style="height: 100%; background: var(--gf-accent-primary); width: 0%; transition: width var(--anim-medium) var(--ease-out);"></div>
                        </div>
                    </div>
                </div>
                <div style="display: flex; justify-content: space-between; align-items: center; gap: 16px;">
                    <span id="export-chat-counter" class="select-all-counter">0 selected</span>
                    <div style="display: flex; gap: 12px;">
                        <button class="premium-button premium-button-secondary cancel-action">Close</button>
                        <button id="start-export-btn" class="premium-button premium-button-primary" disabled>Export</button>
                    </div>
                </div>
            </div>
        `}function xo(){return`
            <div class="premium-modal-actions">
                <input type="search" id="pinned-messages-search" class="premium-search-input" placeholder="Search pinned messages..." aria-label="Search pinned messages">
                <button id="clear-all-pins-btn" class="premium-button premium-button-danger" style="margin-left: auto;">
                    Clear All
                </button>
            </div>
            <div class="premium-modal-body" style="max-height: 600px; overflow-y: auto;">
                <div id="pinned-messages-list">
                    <div id="pinned-messages-loading" style="text-align: center; padding: 40px;" role="status" aria-live="polite">
                        <div style="width: 40px; height: 40px; border: 3px solid var(--gf-border-color); border-top-color: var(--gf-accent-primary); border-radius: 50%; animation: spin 1s linear infinite; margin: 0 auto 16px;" aria-hidden="true"></div>
                        <p style="color: var(--gf-text-secondary);">Loading pinned messages...</p>
                    </div>
                </div>
            </div>
            <div class="premium-modal-footer">
                <span id="pinned-messages-counter" class="select-all-counter">0 pinned messages</span>
                <button class="premium-button premium-button-secondary cancel-action">Close</button>
            </div>
        `}function yo(){return`
            <div class="premium-modal-actions">
                <input type="search" id="bulk-delete-search" class="premium-search-input" placeholder="Search loaded conversations..." aria-label="Search loaded conversations to delete">
                <div id="bulk-delete-search-loading" style="display: none; padding: 8px 12px; margin-top: 8px; background: var(--gf-bg-secondary); border-radius: 4px; color: var(--gf-accent-primary); font-size: 13px;">
                    <div style="display: flex; align-items: center; gap: 8px;">
                        <div style="width: 14px; height: 14px; border: 2px solid var(--gf-accent-primary); border-top: 2px solid transparent; border-radius: 50%; animation: spin 1s linear infinite;"></div>
                        <span id="bulk-delete-search-status">Searching loaded conversations...</span>
                    </div>
                </div>
                <label class="premium-checkbox-label">
                    <input type="checkbox" id="bulk-delete-select-all" class="premium-checkbox select-all-checkbox">
                    <span>Select latest 100</span>
                </label>
                <label class="premium-checkbox-label" style="margin-left: 16px;">
                    <input type="checkbox" id="include-foldered-chats" class="premium-checkbox">
                    <span>Include foldered chats</span>
                </label>
                <label class="premium-checkbox-label" style="margin-left: 16px;">
                    <input type="checkbox" id="include-pinned-chats" class="premium-checkbox">
                    <span>Include pinned chats</span>
                </label>
            </div>
            <div class="premium-modal-body">
                <div id="bulk-delete-list">
	                    <div id="bulk-delete-loading" style="text-align: center; padding: 40px;" role="status" aria-live="polite">
	                        <div style="width: 40px; height: 40px; border: 3px solid var(--gf-border-color); border-top-color: var(--gf-accent-primary); border-radius: 50%; animation: spin 1s linear infinite; margin: 0 auto 16px;" aria-hidden="true"></div>
	                        <p style="color: var(--gf-text-secondary);">Loading latest conversations...</p>
	                    </div>
	                    <!-- Chat items will be dynamically inserted here -->
	                    <div id="bulk-delete-loading-more" style="display: none; text-align: center; padding: var(--space-4); color: var(--gf-text-secondary);" role="status" aria-live="polite">
	                        <div style="width: 24px; height: 24px; border: 2px solid var(--gf-border-color); border-top-color: var(--gf-accent-primary); border-radius: 50%; animation: spin 0.8s linear infinite; margin: 0 auto 8px;" aria-hidden="true"></div>
	                        <span>Loading next 100 conversations...</span>
	                    </div>
	                    <div id="bulk-delete-load-more-actions" style="display: none; text-align: center; padding: var(--space-4); color: var(--gf-text-secondary);">
	                        <button type="button" id="bulk-delete-load-next-btn" class="premium-button premium-button-secondary">Load next 100</button>
	                        <div id="bulk-delete-load-more-status" style="font-size: 12px; margin-top: 8px;"></div>
	                    </div>
	                </div>
            </div>
            <div class="premium-modal-footer" id="bulk-delete-controls">
                <div style="display: flex; flex-direction: column; gap: 4px;">
                    <span id="bulk-delete-counter" class="select-all-counter">0 selected</span>
                    <span id="bulk-delete-scroll-status" style="font-size: 12px; color: var(--gf-text-tertiary);"></span>
                </div>
                <div style="display: flex; gap: 12px; align-items: center;">
                    <button class="premium-button premium-button-secondary cancel-action">Cancel</button>
                    <button id="start-bulk-delete-btn" class="premium-button premium-button-danger" disabled>
                        <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" style="margin-right: 6px;">
                            <path d="M19 7l-.867 12.142A2 2 0 0116.138 21H7.862a2 2 0 01-1.995-1.858L5 7m5 4v6m4-6v6m1-10V4a1 1 0 00-1-1h-4a1 1 0 00-1 1v3M4 7h16"/>
                        </svg>
                        Delete Selected
                    </button>
                </div>
            </div>
        `}function vo(e="export"){const t=window.geminiAPI?.isPremium?.()||!1;return`
            <div class="premium-modal-header">
                <h2 class="premium-modal-title">Chat Tools</h2>
                <button class="premium-modal-close" id="close-modal-btn" aria-label="Close">
                    <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                        <line x1="18" y1="6" x2="6" y2="18"></line>
                        <line x1="6" y1="6" x2="18" y2="18"></line>
                    </svg>
                </button>
            </div>
            
            <div class="chat-tools-tabs">
                <button class="chat-tools-tab ${e==="pinned"?"active":""}" data-tab="pinned" role="tab" aria-selected="${e==="pinned"}">
                    <svg width="16" height="16" viewBox="0 0 384 512" fill="currentColor">
                        <path d="M336 0h-288C21.49 0 0 21.49 0 48v431.9c0 24.7 26.79 40.08 48.12 27.64L192 423.6l143.9 83.93C357.2 519.1 384 504.6 384 479.9V48C384 21.49 362.5 0 336 0zM336 452L192 368l-144 84V54C48 50.63 50.63 48 53.1 48h276C333.4 48 336 50.63 336 54V452z"/>
                    </svg>
                    <span>Pinned</span>
                </button>
                
                <button class="chat-tools-tab ${e==="export"?"active":""}" data-tab="export" role="tab" aria-selected="${e==="export"}">
                    <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                        <path d="M14 2H6C4.89543 2 4 2.89543 4 4V20C4 21.1046 4.89543 22 6 22H18C19.1046 22 20 21.1046 20 20V8L14 2Z"/>
                        <path d="M14 2V8H20"/>
                        <path d="M12 10V16M12 16L9 13M12 16L15 13"/>
                    </svg>
                    <span>Export</span>
                </button>
                
                <button class="chat-tools-tab ${e==="bulk-delete"?"active":""}" data-tab="bulk-delete" role="tab" aria-selected="${e==="bulk-delete"}">
                    <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                        <path d="M19 7l-.867 12.142A2 2 0 0116.138 21H7.862a2 2 0 01-1.995-1.858L5 7m5 4v6m4-6v6m1-10V4a1 1 0 00-1-1h-4a1 1 0 00-1 1v3M4 7h16"/>
                    </svg>
                    <span>Bulk Delete</span>
                    ${t?"":'<span class="chat-tools-premium-badge">Premium</span>'}
                </button>
            </div>
            
            <div class="tab-panel ${e==="pinned"?"active":""}" id="pinned-tab-panel" role="tabpanel">
                ${xo()}
            </div>
            
            <div class="tab-panel ${e==="export"?"active":""}" id="export-tab-panel" role="tabpanel">
                ${bo()}
            </div>
            
            <div class="tab-panel ${e==="bulk-delete"?"active":""}" id="bulk-delete-tab-panel" role="tabpanel">
                ${yo()}
            </div>
        `}function je(e="pinned"){le("chat-tools-modal","Chat Tools",vo(e),900),wo(e)}async function wo(e="pinned"){const t=u.querySelector("#chat-tools-modal");if(!t)return;const n=t.querySelectorAll(".chat-tools-tab"),o=t.querySelectorAll(".tab-panel");let r=e;const i=new Set;await a(r),n.forEach(d=>{d.addEventListener("click",async p=>{const s=d.dataset.tab;if(s==="bulk-delete")try{const c=await window.geminiAPI.checkFeatureLimit("bulkDelete");if(!c.allowed){window.geminiAPI&&CONFIG?.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.LIMIT_HIT,{feature:"bulkDelete",context:"chat_tools_tab"}),W(),Ye("bulkDelete",{count:c.count??0,limit:c.limit??0});return}}catch(c){console.warn("[Chat Tools] Premium check failed:",c)}window.geminiAPI&&CONFIG?.ANALYTICS_EVENTS&&r!==s&&window.geminiAPI.trackEvent("chat_tools_tab_switched",{from_tab:r,to_tab:s,method:"click"}),n.forEach(c=>{c.classList.remove("active"),c.setAttribute("aria-selected","false")}),o.forEach(c=>c.classList.remove("active")),d.classList.add("active"),d.setAttribute("aria-selected","true");const g=t.querySelector(`#${s}-tab-panel`);g&&g.classList.add("active"),i.has(s)||await a(s),r=s})});async function a(d){if(!i.has(d)){switch(d){case"export":Io();break;case"pinned":fo();break;case"bulk-delete":try{(await window.geminiAPI.checkFeatureLimit("bulkDelete")).allowed&&Mt()}catch{Mt()}break}i.add(d)}}window.geminiAPI&&CONFIG?.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent("chat_tools_modal_opened",{initial_tab:e,source:"dropdown"})}function ko(){return`
            <div class="settings-modal-content">
                <style>
                    
                    .settings-modal-content {
                        padding: 0;
                        display: flex;
                        flex-direction: column;
                    }
                    
                    .settings-body {
                        padding: 12px 16px 16px 16px;
                    }
                    
                    .settings-section {
                        margin-bottom: 12px;
                        padding: var(--space-3);
                        background-color: var(--gf-bg-secondary);
                        border-radius: 12px;
                        border: 2px solid var(--gf-border-color);
                    }
                    
                    .settings-section:first-child {
                        margin-top: 0;
                    }
                    
                    .dark-theme .settings-section {
                        border-color: rgba(255, 255, 255, 0.15);
                    }
                    
                    .settings-section:last-child {
                        margin-bottom: 0;
                    }
                    
                    .section-title {
                        font-size: var(--font-size-tiny);
                        font-weight: var(--font-weight-semibold);
                        color: var(--gf-text-secondary);
                        margin-bottom: 10px;
                        display: flex;
                        align-items: center;
                        gap: 6px;
                        text-transform: uppercase;
                        letter-spacing: 0.5px;
                    }
                    
                    .section-title svg {
                        width: 18px;
                        height: 18px;
                        opacity: 0.7;
                    }
                    
                    .toggle-setting {
                        display: flex;
                        align-items: center;
                        justify-content: space-between;
                        padding: var(--space-3);
                        background-color: var(--background-primary);
                        border-radius: var(--space-2);
                        transition: all var(--anim-normal) var(--ease-out);
                        cursor: pointer;
                    }
                    
                    .toggle-setting:hover {
                        background-color: var(--background-hover);
                    }
                    
                    .toggle-content {
                        flex: 1;
                    }
                    
                    .toggle-label {
                        font-size: 15px;
                        font-weight: 500;
                        color: var(--text-primary);
                        margin-bottom: 4px;
                    }
                    
                    .toggle-description {
                        font-size: 13px;
                        color: var(--text-tertiary);
                    }
                    
                    .toggle-switch {
                        position: relative;
                        width: 48px;
                        height: 28px;
                        background-color: #dadce0;
                        border-radius: 28px;
                        cursor: pointer;
                        transition: all var(--anim-medium) var(--ease-out);
                        flex-shrink: 0;
                    }
                    
                    .dark-theme .toggle-switch {
                        background-color: #5f6368;
                    }
                    
                    .toggle-switch.active {
                        background-color: #1a73e8;
                    }
                    
                    .toggle-switch::after {
                        content: '';
                        position: absolute;
                        width: 22px;
                        height: 22px;
                        background-color: white;
                        border-radius: 50%;
                        top: 3px;
                        left: 3px;
                        transition: all var(--anim-medium) var(--ease-out);
                        box-shadow: 0 1px 3px 0 rgba(0, 0, 0, 0.4);
                    }
                    
                    .toggle-switch.active::after {
                        transform: translateX(20px);
                    }
                    
                    .toggle-switch:focus {
                        outline: none;
                        box-shadow: 0 0 0 3px rgba(26, 115, 232, 0.3);
                    }
                    
                    .toggle-switch:focus:not(:focus-visible) {
                        box-shadow: none;
                    }
                    
                    .shortcuts-link-container:hover {
                        background-color: var(--background-hover);
                        transform: translateX(2px);
                    }
                    
                    .feedback-container {
                        position: relative;
                        margin-bottom: 4px;
                    }
                    
                    .feedback-textarea {
                        width: 100%;
                        min-height: 80px;
                        max-height: 120px;
                        padding: var(--space-3);
                        border: 2px solid #dadce0;
                        border-radius: var(--space-2);
                        background-color: var(--background-primary);
                        color: var(--text-primary);
                        font-family: 'Google Sans', 'Roboto', sans-serif;
                        font-size: 14px;
                        resize: vertical;
                        transition: all var(--anim-normal) var(--ease-out);
                        box-sizing: border-box;
                    }
                    
                    .dark-theme .feedback-textarea {
                        border-color: #5f6368;
                    }
                    
                    .feedback-textarea:focus {
                        outline: none;
                        border-color: var(--gf-accent-primary);
                        border-width: 2px;
                        background-color: var(--gf-bg-primary);
                        box-shadow: 0 0 0 3px rgba(138, 180, 248, 0.3);
                    }
                    
                    .feedback-textarea:focus:not(:focus-visible) {
                        box-shadow: none;
                    }
                    
                    .feedback-textarea::placeholder {
                        color: var(--text-tertiary);
                    }
                    
                    .char-counter {
                        position: absolute;
                        bottom: -18px;
                        right: 0;
                        font-size: 11px;
                        color: var(--text-tertiary);
                        transition: color 0.2s ease;
                        background-color: var(--background-secondary);
                        padding: 0 4px;
                        border-radius: 4px;
                    }
                    
                    .char-counter.warning {
                        color: var(--gf-accent-warning, #F59E0B);
                    }
                    
                    .char-counter.error {
                        color: var(--gf-accent-danger);
                    }
                    
                    .settings-footer {
                        display: flex;
                        justify-content: space-between;
                        align-items: center;
                        gap: 16px;
                        padding: var(--input-padding);
                        background-color: var(--background-secondary);
                        border-top: 1px solid var(--border-color);
                        border-radius: 0 0 16px 16px;
                    }
                    
                    .footer-info {
                        font-size: 13px;
                        color: var(--text-tertiary);
                        display: flex;
                        align-items: center;
                        gap: 6px;
                    }
                    
                    .footer-info svg {
                        width: 16px;
                        height: 16px;
                        opacity: 0.6;
                    }
                    
                    /* Feedback buttons container */
                    .feedback-buttons {
                        display: grid;
                        grid-template-columns: 1fr 1fr;
                        gap: 12px;
                    }
                    
                    .feedback-buttons .button {
                        display: flex;
                        align-items: center;
                        justify-content: center;
                        gap: 8px;
                        min-height: 44px;
                        padding: 12px 24px;
                        font-weight: 600;
                        box-sizing: border-box;
                        width: 100%;
                    }
                    
                    .feedback-buttons .button svg {
                        width: 16px;
                        height: 16px;
                    }
                    
                    /* Email button specific styles */
                    .btn-send-email {
                        border: 2px solid #5f6368 !important;
                        color: var(--text-primary);
                        background-color: transparent;
                    }
                    
                    .btn-send-email:hover:not(:disabled) {
                        background-color: rgba(95, 99, 104, 0.1);
                        border-color: #202124 !important;
                    }
                    
                    .dark-theme .btn-send-email {
                        border-color: #dadce0 !important;
                    }
                    
                    .dark-theme .btn-send-email:hover:not(:disabled) {
                        background-color: rgba(218, 220, 224, 0.1);
                        border-color: #f8f9fa !important;
                    }
                    
                    /* Anonymous feedback button styles */
                    .btn-send-feedback {
                        border: 2px solid var(--gf-accent-primary) !important;
                    }
                    
                    .btn-send-feedback:disabled {
                        border-color: var(--gf-border-color) !important;
                        opacity: 0.5;
                    }
                    
                    .btn-send-feedback:hover:not(:disabled) {
                        background-color: var(--gf-accent-primary);
                        border-color: var(--gf-accent-primary) !important;
                        color: var(--gf-button-text, white);
                        opacity: 0.9;
                        box-shadow: 0 2px 8px rgba(26, 115, 232, 0.3);
                    }
                    
                    /* Shared disabled styles */
                    .feedback-buttons .button:disabled {
                        opacity: 0.5;
                        cursor: not-allowed;
                    }
                    
                    .btn-send-email:disabled {
                        border-color: #dadce0 !important;
                    }
                    
                    .dark-theme .btn-send-email:disabled {
                        border-color: #5f6368 !important;
                    }
                    
                    /* Success animation */
                    @keyframes successPulse {
                        0% { transform: scale(1); }
                        50% { transform: scale(1.1); }
                        100% { transform: scale(1); }
                    }
                    
                    .btn-send-feedback.success {
                        background-color: var(--gf-accent-success);
                        animation: successPulse var(--anim-slow) var(--ease-out);
                    }
                    
                    /* Loading spinner */
                    .spinner {
                        display: inline-block;
                        width: 14px;
                        height: 14px;
                        border: 2px solid rgba(255, 255, 255, 0.3);
                        border-radius: 50%;
                        border-top-color: white;
                        animation: spin 0.8s linear infinite;
                    }
                    
                    @keyframes spin {
                        to { transform: rotate(360deg); }
                    }
                </style>
                
                <div class="settings-body">
                    <!-- Word Counter Section (moved to top) -->
                    <div class="settings-section">
                        <h3 class="section-title">
                            <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                <circle cx="12" cy="12" r="3"/>
                                <path d="M12 1v6m0 6v6m11-7h-6m-6 0H1"/>
                            </svg>
                            Preferences
                        </h3>
                        <div class="toggle-setting" id="word-counter-setting">
                            <div class="toggle-content">
                                <div class="toggle-label">Word Counter</div>
                                <div class="toggle-description">Display character and word count below input field</div>
                            </div>
                            <div class="toggle-switch ${he?"active":""}" id="word-counter-toggle"></div>
                        </div>
                        <div class="toggle-setting" id="enhance-prompt-setting" style="margin-top: 16px;">
                            <div class="toggle-content">
                                <div class="toggle-label">Enhance Prompt</div>
                                <div class="toggle-description">Show AI-powered prompt enhancement button</div>
                            </div>
                            <div class="toggle-switch ${ye?"active":""}" id="enhance-prompt-toggle"></div>
                        </div>
                        <!-- TIMESTAMP FEATURE DISABLED -->
                        <!-- <div class="toggle-setting" id="message-timestamp-setting" style="margin-top: 16px;">
                            <div class="toggle-content">
                                <div class="toggle-label">Show Message Timestamps</div>
                                <div class="toggle-description">Show when each message was sent</div>
                            </div>
                            <div class="toggle-switch ${Ho?"active":""}" id="message-timestamp-toggle"></div>
                        </div> -->
                        <div class="toggle-setting" id="pinned-messages-setting" style="margin-top: 16px;">
                            <div class="toggle-content">
                                <div class="toggle-label">Pinned Messages</div>
                                <div class="toggle-description">Show bookmark icons to pin important messages</div>
                            </div>
                            <div class="toggle-switch ${fe?"active":""}" id="pinned-messages-toggle"></div>
                        </div>
                    </div>
                    
                    <!-- Feedback Section -->
                    <div class="settings-section">
                        <h3 class="section-title">
                            <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                <path d="M21 15a2 2 0 0 1-2 2H7l-4 4V5a2 2 0 0 1 2-2h14a2 2 0 0 1 2 2z"/>
                            </svg>
                            Send Feedback
                        </h3>
                        <div class="feedback-settings-container">
                            <div class="feedback-info" style="margin-bottom: 12px; padding: 10px; background-color: var(--background-primary); border-radius: 8px; font-size: 13px; color: var(--text-secondary); line-height: 1.4;">
                                Help improve Gemini Toolbox! Share your thoughts, report bugs, or suggest features.
                            </div>
                            <textarea 
                                class="settings-feedback-textarea" 
                                id="settings-feedback-textarea"
                                placeholder="Share your thoughts, report bugs, or suggest new features..."
                                maxlength="1000"
                                style="
                                    width: 100%;
                                    min-height: 100px;
                                    max-height: 200px;
                                    padding: 12px;
                                    background-color: var(--background-primary);
                                    color: var(--text-primary);
                                    border: 1px solid var(--border-color);
                                    border-radius: 8px;
                                    font-size: 14px;
                                    font-family: inherit;
                                    resize: vertical;
                                    box-sizing: border-box;
                                    transition: all var(--anim-fast) var(--ease-out);
                                "></textarea>
                            <div style="font-size: 11px; color: var(--text-tertiary); margin-top: 4px; text-align: right;" id="settings-char-counter">0 / 1000</div>
                            <div class="feedback-actions" style="display: grid; grid-template-columns: 1fr; gap: 12px; margin-top: 12px;">
                                <button class="button secondary" id="settings-email-btn" disabled style="display: flex; align-items: center; justify-content: center; gap: 8px;">
                                    <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                        <path d="M4 4h16c1.1 0 2 .9 2 2v12c0 1.1-.9 2-2 2H4c-1.1 0-2-.9-2-2V6c0-1.1.9-2 2-2z"/>
                                        <polyline points="22,6 12,13 2,6"/>
                                    </svg>
                                    Send via Email
                                </button>
                            </div>
                        </div>
                    </div>
                    
                    <!-- Community Section -->
                    <div class="settings-section">
                        <h3 class="section-title">
                            <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                <path d="M12 2a10 10 0 100 20 10 10 0 000-20z"/>
                                <path d="M8 10h8M8 14h5"/>
                            </svg>
                            Community
                        </h3>
                        <a href="https://chat.whatsapp.com/CF7i1mw1xrnHCalMsLxs8N" target="_blank" rel="noopener noreferrer" class="button secondary" style="width: 100%; display: flex; align-items: center; justify-content: center; gap: 8px;">
                            <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                <path d="M21 15a2 2 0 0 1-2 2H7l-4 4V5a2 2 0 0 1 2-2h14a2 2 0 0 1 2 2z"/>
                            </svg>
                            Join the Community
                        </a>
                    </div>
                    
                    <!-- Data Management Section -->
                    <div class="settings-section">
                        <h3 class="section-title">
                            <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                <path d="M21 8a2 2 0 0 0-1-1.73l-7-4a2 2 0 0 0-2 0l-7 4A2 2 0 0 0 3 8v8a2 2 0 0 0 1 1.73l7 4a2 2 0 0 0 2 0l7-4A2 2 0 0 0 21 16V8z"/>
                                <path d="M12 1v6m0 6v6"/>
                            </svg>
                            Data Management
                        </h3>
                        <div class="backup-restore-container">
                            <div class="backup-info" style="margin-bottom: 16px; padding: 12px; background-color: var(--background-primary); border-radius: 8px; border-left: 4px solid var(--gf-accent-primary);">
                                <div style="font-size: 13px; color: var(--text-secondary); line-height: 1.4;">
                                    <strong>Your data safety net:</strong> Export your folders and settings to a backup file, or restore from a previous backup. Keep your organization safe!
                                </div>
                            </div>
                            <div class="backup-actions" style="display: grid; grid-template-columns: 1fr 1fr; gap: 12px;">
                                <button class="button secondary" id="export-backup-btn" style="display: flex; align-items: center; justify-content: center; gap: 8px;">
                                    <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                        <path d="M21 15v4a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2v-4"/>
                                        <polyline points="7 10 12 15 17 10"/>
                                        <line x1="12" y1="15" x2="12" y2="3"/>
                                    </svg>
                                    Export Backup
                                </button>
                                <button class="button secondary" id="import-backup-btn" style="display: flex; align-items: center; justify-content: center; gap: 8px;">
                                    <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                        <path d="M21 15v4a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2v-4"/>
                                        <polyline points="17 8 12 3 7 8"/>
                                        <line x1="12" y1="3" x2="12" y2="15"/>
                                    </svg>
                                    Import Backup
                                </button>
                            </div>
                            <div class="storage-stats" style="margin-top: 16px; padding: 12px; background-color: var(--background-primary); border-radius: 8px;">
                                <div style="font-size: 12px; color: var(--text-tertiary); margin-bottom: 8px;">Storage Statistics</div>
                                <div id="storage-stats-content" style="font-size: 13px; color: var(--text-secondary);">
                                    Loading stats...
                                </div>
                            </div>
                        </div>
                    </div>
                    
                    <!-- Account Linking Section (only shown for premium_device users) -->
                    <div class="settings-section" id="account-linking-section" style="display: none;">
                        <h3 class="section-title">
                            <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                <path d="M10 13a5 5 0 0 0 7.54.54l3-3a5 5 0 0 0-7.07-7.07l-1.72 1.71"/>
                                <path d="M14 11a5 5 0 0 0-7.54-.54l-3 3a5 5 0 0 0 7.07 7.07l1.71-1.71"/>
                            </svg>
                            Link Your Purchase
                        </h3>
                        <div class="link-container">
                            <div class="link-info" style="margin-bottom: 16px; padding: 12px; background-color: var(--background-primary); border-radius: 8px; border-left: 4px solid #4285f4;">
                                <div style="font-size: 13px; color: var(--text-secondary); line-height: 1.4;">
                                    Link your purchase to use Premium on any device you sign in to.
                                </div>
                            </div>
                            <div class="link-input-container" style="margin-bottom: 12px;">
                                <input type="email" 
                                       id="link-email-input" 
                                       placeholder="Enter your email address"
                                       style="
                                           width: 100%;
                                           padding: 12px;
                                           background-color: var(--background-primary);
                                           color: var(--text-primary);
                                           border: 1px solid var(--border-color);
                                           border-radius: 8px;
                                           font-size: 14px;
                                           font-family: inherit;
                                           box-sizing: border-box;
                                       ">
                            </div>
                            <button class="button primary" id="link-email-btn" style="width: 100%; display: flex; align-items: center; justify-content: center; gap: 8px;">
                                <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                    <path d="M4 4h16c1.1 0 2 .9 2 2v12c0 1.1-.9 2-2 2H4c-1.1 0-2-.9-2-2V6c0-1.1.9-2 2-2z"/>
                                    <polyline points="22,6 12,13 2,6"/>
                                </svg>
                                Send Login Link
                            </button>
                        </div>
                    </div>
                    
                    <!-- Subscription Management Section (only shown for premium users) -->
                    <div class="settings-section" id="subscription-section" style="display: none;">
                        <h3 class="section-title">
                            <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                <path d="M12 2L2 7v10c0 5.55 3.84 10.74 9 12 5.16-1.26 9-6.45 9-12V7l-10-5z"/>
                                <path d="M9 12l2 2 4-4"/>
                            </svg>
                            Subscription
                        </h3>
                        <div class="subscription-container">
                            <div class="subscription-info" style="margin-bottom: 16px; padding: 12px; background-color: var(--background-primary); border-radius: 8px; border-left: 4px solid #4285f4;">
                                <div style="font-size: 13px; color: var(--text-secondary); line-height: 1.4;">
                                    <strong>Premium Member</strong> - Manage your subscription, billing, and payment methods.
                                </div>
                            </div>
                            <button class="button primary" id="manage-subscription-btn" style="width: 100%; display: flex; align-items: center; justify-content: center; gap: 8px;">
                                <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                    <rect x="3" y="11" width="18" height="11" rx="2" ry="2"/>
                                    <path d="M7 11V7a5 5 0 0 1 10 0v4"/>
                                </svg>
                                Manage Subscription
                            </button>
                        </div>
                    </div>
                    
                    <!-- Shortcuts Link Section -->
                    <div class="settings-section" style="padding: 0; background: transparent; border: none;">
                        <div class="shortcuts-link-container" id="shortcuts-link-container" style="
                            display: flex;
                            align-items: center;
                            justify-content: space-between;
                            padding: var(--space-4);
                            background-color: var(--background-secondary);
                            border: 1px solid var(--border-color);
                            border-radius: 12px;
                            cursor: pointer;
                            transition: all var(--anim-normal) var(--ease-out);
                        ">
                            <div style="display: flex; align-items: center; gap: var(--gap-medium);">
                                <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                    <rect x="2" y="4" width="20" height="16" rx="2"/>
                                    <path d="M6 8h12M6 12h8M6 16h10"/>
                                </svg>
                                <div>
                                    <div style="font-size: 15px; font-weight: 500; color: var(--text-primary);">Keyboard Shortcuts</div>
                                    <div style="font-size: 13px; color: var(--text-tertiary); margin-top: 2px;">View all available shortcuts</div>
                                </div>
                            </div>
                            <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                <polyline points="9 18 15 12 9 6"/>
                            </svg>
                        </div>
                    </div>
                </div>
            </div>
        `}function Co(){const e=u.querySelector("#settings-modal");if(!e)return;const t=e.querySelector("#word-counter-setting"),n=e.querySelector("#word-counter-toggle");t&&n&&t.addEventListener("click",async m=>{m.stopPropagation(),he=!he,he?n.classList.add("active"):n.classList.remove("active"),window.geminiAPI&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.FEATURE_TOGGLED,{feature:"wordCounter",enabled:he}),await _o(),await Nt()});const o=e.querySelector("#enhance-prompt-setting"),r=e.querySelector("#enhance-prompt-toggle");o&&r&&o.addEventListener("click",async m=>{m.stopPropagation(),ye=!ye,ye?r.classList.add("active"):r.classList.remove("active"),window.geminiAPI&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.FEATURE_TOGGLED,{feature:"enhancePrompt",enabled:ye}),await Do(),await _t()});const i=e.querySelector("#pinned-messages-setting"),a=e.querySelector("#pinned-messages-toggle");i&&a&&i.addEventListener("click",async m=>{m.stopPropagation(),fe=!fe,fe?a.classList.add("active"):a.classList.remove("active"),window.geminiAPI&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.FEATURE_TOGGLED,{feature:"pinnedMessages",enabled:fe}),await zo(),await $t(),Q(fe?"Pinned messages enabled":"Pinned messages disabled","success")});const d=e.querySelector("#link-email-btn"),p=e.querySelector("#link-email-input");if(d&&p){d.addEventListener("click",async()=>{const h=p.value.trim();if(!h||!h.includes("@")){Q("Please enter a valid email address","error");return}try{d.disabled=!0;const x=d.innerHTML;d.innerHTML='<span class="spinner"></span> Sending...';const f=await window.geminiAPI.requestMagicLink(h);if(f&&f.ok){if(Q("\u{1F4E7} Check your email for the 6-digit code","success"),p){p.placeholder="Enter 6-digit code from email",p.value="",p.type="text",p.maxLength=6,p.pattern="[0-9]{6}",d.innerHTML="Confirm Code",d.disabled=!1;const S=d.cloneNode(!0);d.parentNode.replaceChild(S,d),S.addEventListener("click",async()=>{const P=p.value.trim();if(P.length!==6){Q("Please enter the 6-digit code from your email","error");return}try{S.disabled=!0,S.innerHTML='<span class="spinner"></span> Confirming...';const E=await window.geminiAPI.confirmMagicCode(h,P);if(E&&E.ok){Q("\u2705 Account linked successfully!","success");const k=await window.geminiAPI.getMeStatus({force:!0});if(k.plan==="premium"||k.plan==="premium_device"){try{tt(!0)}catch{}const O=e.querySelector("#account-linking-section"),H=e.querySelector("#subscription-section");O&&(O.style.display="none"),H&&(H.style.display="block")}setTimeout(()=>{e.style.display="none"},2e3)}else Q("Invalid code. Please try again.","error"),S.innerHTML="Confirm Code",S.disabled=!1}catch{Q("Failed to confirm code. Please try again.","error"),S.innerHTML="Confirm Code",S.disabled=!1}})}}else Q("\u{1F4E7} Check your email for the login link","info"),d.innerHTML=x,d.disabled=!1}catch{Q("Failed to send login link. Please try again.","error"),d.innerHTML="Send Login Link",d.disabled=!1}});async function m(){let h=0;const x=20,f=setInterval(async()=>{h++;try{if((await window.geminiAPI.getMeStatus({force:!0})).plan==="premium"){clearInterval(f),Q("\u2705 Purchase linked successfully!","success");try{tt(!0)}catch{}const P=e.querySelector("#account-linking-section"),E=e.querySelector("#subscription-section");P&&(P.style.display="none"),E&&(E.style.display="block")}else h>=x&&clearInterval(f)}catch{}},3e3)}}const s=e.querySelector("#manage-subscription-btn");s&&s.addEventListener("click",async()=>{try{s.disabled=!0;const m=s.innerHTML;s.innerHTML='<span class="spinner"></span> Loading...';let x=(await chrome.storage.local.get("gt_install_id")).gt_install_id;x||(x="gt_"+Math.random().toString(36).substr(2)+Date.now().toString(36),await chrome.storage.local.set({gt_install_id:x}));const f=await chrome.runtime.sendMessage({type:"API_REQUEST",data:{method:"GET",endpoint:"/billing/portal",headers:{"X-Install-ID":x,"X-From":"GeminiToolbox"}}});if(!f||f.success!==!0)throw new Error(f&&f.error?f.error:"Failed to get portal URL");const S=f.result||{};if(S.portal_url)chrome&&chrome.tabs?chrome.tabs.create({url:S.portal_url}):window.open(S.portal_url,"_blank"),s.innerHTML=`
                            <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                <path d="M9 16.17L4.83 12l-1.42 1.41L9 19 21 7l-1.41-1.41L9 16.17z"/>
                            </svg>
                            Opening...
                        `;else throw new Error("No portal URL received");setTimeout(()=>{s.innerHTML=m,s.disabled=!1},2e3)}catch{X("Failed to open billing portal. Please try again."),s.innerHTML="Manage Subscription",s.disabled=!1}});const g=e.querySelector("#shortcuts-link-container");g&&g.addEventListener("click",()=>{e._childOpener=document.activeElement||g,Lo()});const c=e.querySelector("#export-backup-btn"),b=e.querySelector("#import-backup-btn"),C=e.querySelector("#storage-stats-content");window.geminiStorage||(window.geminiStorage=new GeminiToolboxStorage,window.geminiStorage.initialize().catch(m=>{}));const T=async()=>{try{if(window.geminiStorage&&window.geminiStorage.initialized){const m=window.geminiStorage.getStats();C&&(C.innerHTML=`
                            <div style="display: grid; grid-template-columns: repeat(2, 1fr); gap: 12px;">
                                <div><strong>${m.folders}</strong> folders</div>
                                <div><strong>${m.chats}</strong> chats</div>
                            </div>
                            <div style="margin-top: 8px; font-size: 11px; color: var(--text-tertiary);">
                                Last backup: ${m.lastBackup?new Date(m.lastBackup).toLocaleDateString():"Never"}
                            </div>
                        `)}else C&&(C.textContent="Storage system initializing...")}catch{C&&(C.textContent="Error loading stats")}};setTimeout(T,100),c&&c.addEventListener("click",async()=>{try{c.disabled=!0;const m=c.innerHTML;if(c.innerHTML='<span class="spinner"></span> Exporting...',window.geminiStorage)await window.geminiStorage.exportBackup(),c.innerHTML=`
                            <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                <path d="M9 16.17L4.83 12l-1.42 1.41L9 19 21 7l-1.41-1.41L9 16.17z"/>
                            </svg>
                            Exported!
                        `,setTimeout(()=>{c.innerHTML=m,c.disabled=!1,T()},3e3);else throw new Error("Storage system not initialized")}catch{c.innerHTML=`
                        <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                            <circle cx="12" cy="12" r="10"/>
                            <line x1="15" y1="9" x2="9" y2="15"/>
                            <line x1="9" y1="9" x2="15" y2="15"/>
                        </svg>
                        Failed
                    `,setTimeout(()=>{c.innerHTML=originalContent,c.disabled=!1},3e3),X("Failed to export backup. Please try again.")}}),b&&b.addEventListener("click",async()=>{try{const m=document.createElement("input");m.type="file",m.accept=".json",m.style.display="none",m.addEventListener("change",async h=>{const x=h.target.files[0];if(x)try{b.disabled=!0;const f=b.innerHTML;b.innerHTML='<span class="spinner"></span> Importing...';const S=await x.text(),P=JSON.parse(S),k=`
                                <div style="margin-bottom: 24px;">
                                    <div style="display: flex; align-items: center; gap: var(--gap-medium); margin-bottom: var(--space-4);">
                                        <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="var(--gf-accent-warning, #fbbc04)" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                                            <circle cx="12" cy="12" r="10"/>
                                            <line x1="12" y1="8" x2="12" y2="12"/>
                                            <line x1="12" y1="16" x2="12.01" y2="16"/>
                                        </svg>
                                        <p style="margin: 0; color: var(--gf-text-primary); font-size: 16px; font-weight: 500; line-height: 1.5;">
                                            Import backup from ${P.exportedAt?new Date(P.exportedAt).toLocaleDateString():"unknown date"}?
                                        </p>
                                    </div>
                                    <p style="margin: 0 0 0 36px; color: var(--gf-text-secondary); font-size: 14px;">
                                        This will replace all your current folders and settings. This action cannot be undone.
                                    </p>
                                </div>
                                <div class="modal-footer">
                                    <div style="display: flex; justify-content: space-between; align-items: center; width: 100%;">
                                        <button type="button" class="button secondary cancel-action">Cancel</button>
                                        <button type="button" class="button primary" id="confirm-import-backup">
                                            Import Backup
                                        </button>
                                    </div>
                                </div>
                            `;if(le("confirm-import-modal","Confirm Import",k,480),!await new Promise(H=>{setTimeout(()=>{const R=u.querySelector("#confirm-import-backup"),ie=u.querySelector("#confirm-import-modal .button.secondary.cancel-action");R&&(R.onclick=()=>{W(),H(!0)}),ie&&(ie.onclick=()=>{W(),H(!1)})},100)})){b.innerHTML=f,b.disabled=!1;return}if(window.geminiStorage)await window.geminiStorage.importBackup(P),b.innerHTML=`
                                    <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                        <path d="M9 16.17L4.83 12l-1.42 1.41L9 19 21 7l-1.41-1.41L9 16.17z"/>
                                    </svg>
                                    Imported!
                                `,setTimeout(async()=>{b.innerHTML=f,b.disabled=!1,T(),await vt(),De(),Q("Backup imported successfully! Your data has been restored.","success")},2e3);else throw new Error("Storage system not initialized")}catch{b.innerHTML=`
                                <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                    <circle cx="12" cy="12" r="10"/>
                                    <line x1="15" y1="9" x2="9" y2="15"/>
                                    <line x1="9" y1="9" x2="15" y2="15"/>
                                </svg>
                                Failed
                            `,setTimeout(()=>{b.innerHTML=originalContent,b.disabled=!1},3e3),X("Failed to import backup. Please check the file format and try again.")}finally{document.body.removeChild(m)}}),document.body.appendChild(m),m.click()}catch{X("Failed to set up file import. Please try again.")}});const q=e.querySelector("#settings-feedback-textarea"),l=e.querySelector("#settings-char-counter"),y=e.querySelector("#settings-email-btn");if(q&&l){const m=()=>{const h=q.value.length;l.textContent=`${h} / 1000`;const x=q.value.trim().length>0;y&&(y.disabled=!x)};q.addEventListener("input",m),y&&y.addEventListener("click",()=>{const h=q.value.trim();if(!h)return;const x=`Gemini Toolbox Feedback - Version ${CONFIG.VERSION}`,f=`Hi there!

Here's my feedback for Gemini Toolbox:

${h}

Extension Details:
- Version: ${chrome.runtime.getManifest().version}
- Browser: ${navigator.userAgent}
- Timestamp: ${new Date().toLocaleString()}
- User ID: ${window.geminiAPI?.userId||"Unknown"}

Best regards`,S=`mailto:${CONFIG.SUPPORT_EMAIL}?subject=${encodeURIComponent(x)}&body=${encodeURIComponent(f)}`;window.geminiAPI&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent("feedback_email_clicked",{source:"settings_modal",length:h.length}),window.open(S,"_blank")})}}async function rn(){window.geminiAPI&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent("feedback_modal_opened",{source:"dropdown_menu",timestamp:Date.now()}),le("feedback-modal","Send Feedback",`
            <style>
                #feedback-modal .infi-chatgpt-modal-content {
                    max-width: 400px !important;
                    width: 90vw !important;
                    overflow-x: hidden !important;
                }
                
                .feedback-container {
                    position: relative;
                    margin-bottom: 4px;
                    width: 100%;
                    box-sizing: border-box;
                }
                
                .feedback-textarea {
                    width: 100%;
                    min-height: 120px;
                    max-height: 300px;
                    padding: 12px;
                    background-color: var(--gf-bg-input);
                    color: var(--gf-text-primary);
                    border: 1px solid var(--gf-border-color);
                    border-radius: 8px;
                    font-size: 14px;
                    font-family: inherit;
                    resize: vertical;
                    transition: all var(--anim-fast) var(--ease-out);
                    box-sizing: border-box;
                }
                
                .dark-theme .feedback-textarea {
                    border-color: #5f6368;
                }
                
                .feedback-textarea:focus {
                    outline: none;
                    border-color: var(--gf-accent-primary);
                    box-shadow: 0 0 0 3px rgba(138, 180, 248, 0.1);
                    background-color: var(--gf-bg-secondary);
                }
                
                .feedback-textarea:focus:not(:focus-visible) {
                    box-shadow: none;
                }
                
                .feedback-textarea::placeholder {
                    color: var(--text-tertiary);
                }
                
                .char-counter {
                    position: absolute;
                    bottom: 8px;
                    right: 12px;
                    font-size: 11px;
                    color: var(--text-tertiary);
                    background-color: var(--gf-bg-primary);
                    padding: 2px 6px;
                    border-radius: 4px;
                    pointer-events: none;
                    transition: color var(--anim-fast) var(--ease-out);
                }
                
                .char-counter.warning {
                    color: var(--gf-accent-warning);
                }
                
                .char-counter.error {
                    color: var(--gf-accent-danger);
                }
                
                .feedback-buttons {
                    display: grid;
                    grid-template-columns: 1fr 1fr;
                    gap: 12px;
                    margin-top: 20px;
                }
                
                .feedback-buttons .button {
                    display: flex;
                    align-items: center;
                    justify-content: center;
                    gap: 8px;
                    padding: 10px 16px;
                    font-size: 14px;
                    font-weight: 500;
                    min-height: 40px;
                }
                
                .feedback-buttons .button svg {
                    width: 16px;
                    height: 16px;
                }
                
                .feedback-info {
                    display: flex;
                    align-items: center;
                    gap: 6px;
                    margin-top: 12px;
                    padding: 10px;
                    background-color: var(--background-primary);
                    border-radius: 6px;
                    font-size: 12px;
                    color: var(--text-tertiary);
                }
                
                .feedback-info svg {
                    width: 14px;
                    height: 14px;
                    opacity: 0.6;
                    flex-shrink: 0;
                }
                
                /* Button specific styles */
                .btn-send-feedback {
                    border: 2px solid var(--gf-accent-primary) !important;
                }
                
                .btn-send-feedback:disabled {
                    border-color: var(--gf-border-color) !important;
                    opacity: 0.5;
                }
                
                .btn-send-feedback:hover:not(:disabled) {
                    background-color: var(--gf-accent-primary);
                    border-color: var(--gf-accent-primary) !important;
                    color: var(--gf-button-text, white);
                    opacity: 0.9;
                }
                
                .btn-send-feedback.success {
                    background-color: var(--gf-accent-success);
                    animation: successPulse var(--anim-slow) var(--ease-out);
                }
                
                @keyframes successPulse {
                    0%, 100% { transform: scale(1); }
                    50% { transform: scale(1.05); }
                }
                
                /* Community section styles */
                .community-section {
                    margin-top: 24px;
                    padding-top: 20px;
                    border-top: 1px solid var(--gf-border-color);
                    width: 100%;
                    box-sizing: border-box;
                    overflow: hidden;
                }
                
                .community-title {
                    font-size: 14px;
                    font-weight: 600;
                    color: var(--gf-text-primary);
                    margin-bottom: 12px;
                    display: flex;
                    align-items: center;
                    gap: 6px;
                    flex-wrap: wrap;
                }
                
                .community-benefits {
                    font-size: 13px;
                    color: var(--text-secondary);
                    margin-bottom: 16px;
                    line-height: 1.6;
                }
                
                .community-benefits li {
                    margin: 6px 0;
                    padding-left: 20px;
                    position: relative;
                }
                
                .community-benefits li::before {
                    content: "\u2713";
                    position: absolute;
                    left: 0;
                    color: var(--gf-accent-success);
                    font-weight: bold;
                }
                
                .whatsapp-button {
                    display: flex;
                    align-items: center;
                    justify-content: center;
                    gap: 8px;
                    width: calc(100% - 4px);
                    padding: 10px 16px;
                    background-color: #25D366;
                    color: white;
                    border: none;
                    border-radius: 8px;
                    font-size: 13px;
                    font-weight: 600;
                    cursor: pointer;
                    transition: all var(--anim-fast) var(--ease-out);
                    text-decoration: none;
                    box-sizing: border-box;
                    margin: 0 2px;
                }
                
                .whatsapp-button:hover {
                    background-color: #20BA5C;
                    transform: translateY(-1px);
                    box-shadow: 0 4px 12px rgba(37, 211, 102, 0.3);
                }
                
                .whatsapp-button:active {
                    transform: translateY(0);
                }
                
                .limited-time-badge {
                    display: inline-block;
                    background: linear-gradient(135deg, #FF6B6B, #FF8E53);
                    color: white;
                    font-size: 10px;
                    font-weight: 600;
                    padding: 2px 6px;
                    border-radius: 4px;
                    animation: pulse 2s infinite;
                }
                
                @keyframes pulse {
                    0%, 100% { opacity: 1; }
                    50% { opacity: 0.8; }
                }
                
                .community-footer {
                    font-size: 12px;
                    color: var(--text-tertiary);
                    text-align: center;
                    margin-top: 12px;
                    font-style: italic;
                }
            </style>
            
            <div class="feedback-container">
                <textarea 
                    class="feedback-textarea" 
                    id="feedback-textarea"
                    placeholder="Share your thoughts, report bugs, or suggest new features..."
                    maxlength="1000"
                ></textarea>
                <div class="char-counter" id="char-counter">0 / 1000</div>
            </div>
            
            <div class="feedback-buttons">
                <button class="button secondary btn-send-email" id="send-email-btn" disabled>
                    <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                        <path d="M4 4h16c1.1 0 2 .9 2 2v12c0 1.1-.9 2-2 2H4c-1.1 0-2-.9-2-2V6c0-1.1.9-2 2-2z"/>
                        <polyline points="22,6 12,13 2,6"/>
                    </svg>
                    Send via Email
                </button>
                <button class="button primary btn-send-feedback" id="send-feedback-btn" disabled>
                    <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                        <path d="M21 15a2 2 0 0 1-2 2H7l-4 4V5a2 2 0 0 1 2-2h14a2 2 0 0 1 2 2z"/>
                    </svg>
                    Send Anonymous
                </button>
            </div>
            
            <div class="feedback-info">
                <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                    <circle cx="12" cy="12" r="10"/>
                    <path d="M12 16v-4M12 8h.01"/>
                </svg>
                <span>Email: You'll get a response \u2022 Anonymous: Completely private</span>
            </div>
        `,null);const e=u.querySelector("#feedback-modal"),t=e.querySelector("#feedback-textarea"),n=e.querySelector("#send-feedback-btn"),o=e.querySelector("#send-email-btn"),r=e.querySelector("#char-counter");if(t&&r){const i=()=>{const a=t.value.length;r.textContent=`${a} / 1000`,r.classList.remove("warning","error"),a>900?r.classList.add("error"):a>800&&r.classList.add("warning");const d=t.value.trim().length>0;n&&(n.disabled=!d),o&&(o.disabled=!d)};t.addEventListener("input",i),i()}n&&t&&n.addEventListener("click",async()=>{const i=t.value.trim();if(!i){t.focus();return}n.disabled=!0;const a=n.innerHTML;n.innerHTML='<span class="spinner"></span> Sending...';try{const d={content:i,timestamp:new Date().toISOString(),version:chrome.runtime.getManifest().version,userAgent:navigator.userAgent};window.geminiAPI&&typeof CONFIG<"u"&&CONFIG.ANALYTICS_EVENTS&&(await window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.FEEDBACK_SUBMITTED,{feedbackLength:i.length,feedbackType:"anonymous",version:d.version,timestamp:d.timestamp}),await window.geminiAPI.sendFeedback(i));const s=(await chrome.storage.local.get("userFeedback")||{}).userFeedback||[];s.push(d),await chrome.storage.local.set({userFeedback:s}),n.classList.add("success"),n.innerHTML=`
                        <svg viewBox="0 0 24 24" fill="currentColor">
                            <path d="M9 16.17L4.83 12l-1.42 1.41L9 19 21 7l-1.41-1.41L9 16.17z"/>
                        </svg>
                        <span>Sent Successfully!</span>
                    `,t.value="",r&&(r.textContent="0 / 1000",r.classList.remove("warning","error")),setTimeout(()=>{n.classList.remove("success"),n.innerHTML=a,n.disabled=!0},2e3)}catch{n.classList.remove("success"),n.innerHTML=`
                        <svg viewBox="0 0 24 24" fill="currentColor">
                            <path d="M19 6.41L17.59 5 12 10.59 6.41 5 5 6.41 10.59 12 5 17.59 6.41 19 12 13.41 17.59 19 19 17.59 13.41 12z"/>
                        </svg>
                        <span>Error - Try Email</span>
                    `,setTimeout(()=>{n.innerHTML=a,n.disabled=t.value.trim().length===0},3e3)}}),o&&t&&o.addEventListener("click",()=>{const i=t.value.trim();if(!i){t.focus();return}const a=`Gemini Toolbox Feedback - Version ${CONFIG.VERSION}`,d=`Hi there!

Here's my feedback for Gemini Toolbox:

${i}

Extension Details:
- Version: ${chrome.runtime.getManifest().version}
- Browser: ${navigator.userAgent}
- Timestamp: ${new Date().toLocaleString()}
- User ID: ${window.geminiAPI?.userId||"Unknown"} (for analytics correlation)

Please feel free to reply if you need more details!

Best regards`,p=`mailto:${CONFIG.SUPPORT_EMAIL}?subject=${encodeURIComponent(a)}&body=${encodeURIComponent(d)}`;window.geminiAPI&&typeof CONFIG<"u"&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.FEEDBACK_SUBMITTED,{feedbackLength:i.length,feedbackType:"email",version:CONFIG.VERSION,timestamp:new Date().toISOString()});try{window.open(p,"_blank"),o.innerHTML=`
                        <svg viewBox="0 0 24 24" fill="currentColor">
                            <path d="M9 16.17L4.83 12l-1.42 1.41L9 19 21 7l-1.41-1.41L9 16.17z"/>
                        </svg>
                        <span>Email Opened!</span>
                    `,t.value="",r&&(r.textContent="0 / 1000",r.classList.remove("warning","error")),setTimeout(()=>{o.innerHTML=`
                            <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                <path d="M4 4h16c1.1 0 2 .9 2 2v12c0 1.1-.9 2-2 2H4c-1.1 0-2-.9-2-2V6c0-1.1.9-2 2-2z"/>
                                <polyline points="22,6 12,13 2,6"/>
                            </svg>
                            Send via Email
                        `,o.disabled=!0},2e3)}catch{X("Unable to open email client. Please copy the feedback and email it manually to: "+CONFIG.SUPPORT_EMAIL)}})}async function Eo(e={}){await Pt(),await qt(),await Dt(),window.geminiAPI&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.SETTINGS_OPENED,{wordCounterEnabled:he,totalFolders:w.folders.length,hideFolderedChats:w.settings.hideFolderedChats}),le("settings-modal","Settings",ko(),800);try{const t=await window.geminiAPI.getMeStatus(),n=u.querySelector("#subscription-section"),o=u.querySelector("#account-linking-section"),r=CONFIG.FEATURES?.accountLinking!==!1;t.plan==="premium"?(n&&(n.style.display="block"),o&&(o.style.display="none")):(o&&r&&(o.style.display="block"),n&&(n.style.display=t.plan==="premium_device"?"block":"none"))}catch{const n=u.querySelector("#account-linking-section");n&&CONFIG.FEATURES?.accountLinking!==!1&&(n.style.display="block")}e&&e.focusSection==="linking"&&setTimeout(()=>{const t=u.querySelector("#account-linking-section"),n=u.querySelector("#link-email-input");if(t&&t.scrollIntoView({behavior:"smooth",block:"start"}),n)try{n.focus()}catch{}},150),Co()}function So(){return`
            <div class="shortcuts-modal-content">
                <style>
                    .shortcuts-modal-content {
                        padding: 20px;
                    }
                    
                    .shortcuts-intro {
                        font-size: 13px;
                        color: var(--gf-text-secondary);
                        margin-bottom: var(--space-4);
                        line-height: 1.5;
                    }
                    
                    .shortcuts-grid {
                        display: grid;
                        grid-template-columns: repeat(2, 1fr);
                        gap: 8px;
                    }
                    
                    .shortcut-item {
                        display: flex;
                        align-items: center;
                        gap: var(--gap-medium);
                        padding: var(--input-padding);
                        background-color: var(--gf-bg-secondary);
                        border-radius: 10px;
                        transition: all var(--anim-normal) var(--ease-out);
                        min-height: 48px;
                        box-sizing: border-box;
                    }
                    
                    .shortcut-item:hover {
                        background-color: var(--gf-hover-bg);
                        transform: translateX(2px);
                    }
                    
                    .shortcut-icon {
                        font-size: 20px;
                        width: 32px;
                        height: 32px;
                        display: flex;
                        align-items: center;
                        justify-content: center;
                        background-color: var(--gf-bg-primary);
                        border-radius: var(--space-2);
                        flex-shrink: 0;
                    }
                    
                    .shortcut-content {
                        flex: 1;
                        min-width: 0;
                    }
                    
                    .shortcut-key {
                        font-family: 'SF Mono', 'Monaco', 'Roboto Mono', monospace;
                        font-size: 12px;
                        font-weight: 600;
                        color: var(--gf-accent-primary);
                        background-color: var(--gf-bg-primary);
                        padding: 4px 8px;
                        border-radius: 4px;
                        border: 1px solid var(--gf-border-color);
                        display: inline-block;
                        letter-spacing: 0.3px;
                    }
                    
                    .shortcut-desc {
                        font-size: 13px;
                        color: var(--gf-text-secondary);
                        margin-top: 2px;
                        white-space: nowrap;
                        overflow: hidden;
                        text-overflow: ellipsis;
                    }
                    
                    .shortcuts-footer {
                        margin-top: var(--space-4);
                        padding-top: 16px;
                        border-top: 1px solid var(--gf-border-color);
                        font-size: 12px;
                        color: var(--gf-text-tertiary);
                        text-align: center;
                    }
                    
                    /* Responsive adjustments */
                    @media (max-width: 768px) {
                        .shortcuts-modal-content {
                            width: 95%;
                            max-width: none;
                            height: auto;
                            max-height: 90vh;
                        }
                        
                        .shortcuts-grid {
                            gap: var(--gap-medium);
                        }
                        
                        .shortcut-item {
                            padding: var(--space-3);
                        }
                    }
                    
                    @media (max-width: 540px) {
                        .shortcuts-grid {
                            grid-template-columns: 1fr;
                        }
                        
                        .shortcuts-intro {
                            padding: var(--space-3);
                            font-size: 13px;
                        }
                    }
                </style>
                
                <div class="shortcuts-intro">
                    Press <strong>G</strong> first, then the action key. Shortcuts work when not focused on input fields.
                </div>
                
                <div class="shortcuts-grid">
                    ${[{key:"G \u2192 F",description:"Manage Folders",icon:"\u{1F4C1}"},{key:"G \u2192 M",description:"Chat Tools (Pinned)",icon:"\u{1F527}"},{key:"G \u2192 E",description:"Chat Tools (Export)",icon:"\u{1F4C4}"},{key:"G \u2192 D",description:"Chat Tools (Bulk Delete)",icon:"\u{1F5D1}\uFE0F"},{key:"G \u2192 P",description:"Prompt Management",icon:"\u{1F4DD}"},{key:"Ctrl+Shift+P",description:"Enhance Prompt (AI)",icon:"\u2728"},{key:"G \u2192 S",description:"Settings",icon:"\u2699\uFE0F"},{key:"ESC",description:"Close any modal",icon:"\u274C"}].map(t=>`
                        <div class="shortcut-item">
                            <div class="shortcut-icon">${t.icon}</div>
                            <div class="shortcut-content">
                                <span class="shortcut-key">${t.key}</span>
                                <div class="shortcut-desc">${t.description}</div>
                            </div>
                        </div>
                    `).join("")}
                </div>
                
                <div class="shortcuts-footer">
                    <strong>Tip:</strong> Use ESC to close any open modal quickly.
                </div>
            </div>
        `}function Lo(){le("shortcuts-modal","Keyboard Shortcuts",So(),560)}function me(){const e=[];let t=Z();if(t.length===0){const n=Array.from(document.querySelectorAll('[role="navigation"] [role="listitem"], nav li, .conversation-item'));t=t.concat(n)}return t.forEach((n,o)=>{const r=K(n);if(!r)return;const i=Ae(n,`Conversation ${o+1}`);let a=n;const d=qe(n)||n.querySelector("a");d&&(a=d),i&&i!==""&&!i.toLowerCase().includes("new chat")&&e.push({id:r,title:i,lastUpdated:"Recently",element:a})}),t.length>0,e.length===0&&document.querySelectorAll('a[href*="/app/"]').forEach((o,r)=>{const i=K(o),a=Ae(o,`Conversation ${r+1}`);i&&a&&a.length>0&&a.length<100&&!a.includes("New chat")&&e.push({id:i,title:a,lastUpdated:"Recently",element:o})}),e}async function To(e=10){for(let t=0;t<e;t++){if(document.querySelectorAll('.conversation-container, [class*="conversation"], user-query').length>0)return!0;await new Promise(o=>setTimeout(o,500))}return!1}function Io(){const e=u.querySelector("#export-chat-modal")||u.querySelector("#chat-tools-modal");if(!e)return;const t=e.querySelector("#export-chat-select-all"),n=e.querySelector("#start-export-btn"),o=e.querySelector("#export-tab-panel"),r=o?o.querySelector(".cancel-action"):e.querySelector(".cancel-action"),i=e.querySelector("#export-chat-search"),a=e.querySelector("#export-chat-list"),d=e.querySelector("#export-chat-loading"),p=e.querySelector("#export-chat-counter"),s=e.querySelector("#export-error-message"),g=e.querySelector("#export-progress"),c=e.querySelector("#export-chat-status"),b=e.querySelector("#export-chat-loading-more"),C=e.querySelector("#export-chat-format");let T=[],q=[],l=new Set,y=new Set,m=!1,h=0;const x=3;let f=null,S=!1,P=null;const E=e.querySelector("#export-chat-search-loading"),k=e.querySelector("#export-chat-search-status");d.style.display="block",setTimeout(()=>{T=me(),q=[...T],T.forEach(D=>{D.id&&y.add(D.id)}),d.style.display="none",de(q),H()},500);async function O(){if(!m){m=!0,b.style.display="block",b.innerHTML=`
                <div style="display: flex; align-items: center; justify-content: center; gap: 8px; padding: var(--space-4); color: var(--gf-text-secondary);">
                    <div style="width: 16px; height: 16px; border: 2px solid var(--gf-accent-primary); border-top: 2px solid transparent; border-radius: 50%; animation: spin 1s linear infinite;"></div>
                    <span>Loading more conversations...</span>
                </div>
            `;try{const D=me().length,G=[document.querySelector("conversations-list"),document.querySelector('[role="navigation"]'),document.querySelector(".conversation-list"),document.querySelector('[data-testid="conversation-list"]')];let N=null;for(const _ of G)if(_&&(_.scrollHeight>_.clientHeight||_.querySelector('[data-test-id="conversation"]'))){N=_;break}if(!N){const _=document.querySelector('[data-test-id="conversation"]');if(_){let U=_.parentElement;for(;U&&U!==document.body;){if(U.scrollHeight>U.clientHeight){N=U;break}U=U.parentElement}}}if(N){const _=N.scrollTop;N.scrollTop=N.scrollHeight,N.dispatchEvent(new Event("scroll",{bubbles:!0,composed:!0}));const U=Z();if(U.length>0){const ne=U[U.length-1];ne.scrollIntoView({block:"end",inline:"nearest"});const He=new WheelEvent("wheel",{deltaY:300,bubbles:!0,cancelable:!0,view:window});ne.dispatchEvent(He),N.dispatchEvent(He)}let te=0;const J=3;for(;te<J&&(await new Promise(He=>setTimeout(He,100)),!(Z().length>D));)te++;if(!(Z().length>D)){const ne=N.querySelector('.loading-indicator, .spinner, [aria-label*="loading"]')}N.scrollTop=_}const Y=me().filter(_=>_.id&&!y.has(_.id));Y.length>0?(h=0,Y.forEach(_=>{y.add(_.id),T.push(_)}),q=i.value?T.filter(_=>_.title.toLowerCase().includes(i.value.toLowerCase())):[...T],de(q),b.innerHTML=`
                        <div style="text-align: center; color: var(--gf-accent-success); padding: var(--space-3); font-size: 14px;">
                            \u2713 Added ${Y.length} more conversation${Y.length===1?"":"s"}
                        </div>
                    `):(h++,b.style.display="none")}catch{b.innerHTML=`
                    <div style="text-align: center; color: var(--gf-accent-danger); padding: var(--space-3); font-size: 14px;">
                        Error loading conversations. Please try again.
                    </div>
                `}finally{m=!1,b.innerHTML.includes("\u2713 Added")?setTimeout(()=>{b.style.display="none"},400):b.innerHTML.includes("Error")&&setTimeout(()=>{b.style.display="none"},1e3)}}}function H(){if(f)return;f=new MutationObserver(G=>{let N=!1;G.forEach(V=>{V.addedNodes.forEach(Y=>{Y.nodeType===Node.ELEMENT_NODE&&(Y.matches?.('[data-test-id="conversation"]')?[Y]:Y.querySelectorAll?.('[data-test-id="conversation"]')||[]).forEach(U=>{const te=K(U);te&&!y.has(te)&&(N=!0)})})}),N&&setTimeout(()=>R(),50)});const D=document.querySelector("conversations-list");D&&f.observe(D,{childList:!0,subtree:!0})}function R(){const G=me().filter(N=>N.id&&!y.has(N.id));G.length>0&&(h=0,G.forEach(N=>{y.add(N.id),T.push(N)}),q=i.value?T.filter(N=>N.title.toLowerCase().includes(i.value.toLowerCase())):[...T],de(q))}function ie(){f&&(f.disconnect(),f=null)}a.addEventListener("scroll",()=>{if(h>=x||m)return;const{scrollTop:D,scrollHeight:G,clientHeight:N}=a;G-D-N<100&&O()}),C&&C.addEventListener("change",()=>ze());function de(D){a.querySelectorAll(".bulk-delete-item").forEach(Y=>Y.remove());const N=a.querySelector(".no-conversations-message");if(N&&N.remove(),D.length===0){const Y=document.createElement("div");Y.className="no-conversations-message empty-state";const _=i.value.trim();_&&T.length>0?Y.innerHTML=`
                        <div style="text-align: center; padding: 40px 20px; color: var(--gf-text-secondary);">
                            <svg width="48" height="48" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.5" style="margin: 0 auto 16px; opacity: 0.4;">
                                <circle cx="11" cy="11" r="8"></circle>
                                <path d="m21 21-4.35-4.35"></path>
                            </svg>
                            <p style="margin: 0; font-size: 14px;">No conversations found matching "${_}"</p>
                        </div>
                    `:T.length===0&&(Y.innerHTML=`
                        <div style="text-align: center; padding: 40px; color: var(--gf-text-secondary);">
                            <p style="font-size: 16px; margin-bottom: var(--space-2);">No conversations found</p>
                            <p style="font-size: 14px;">Make sure you have some conversations in your Gemini history.</p>
                            <p style="font-size: 12px; margin-top: var(--space-4);">If you have conversations but they're not showing, try refreshing the page.</p>
                        </div>
                    `),a.insertBefore(Y,b);return}const V=document.createDocumentFragment();D.forEach(Y=>{const _=document.createElement("div");_.className="bulk-delete-item";const U=l.has(Y.id);_.innerHTML=`
                    <input type="checkbox" class="bulk-delete-checkbox export-chat-checkbox" data-chat-id="${Y.id}" ${U?"checked":""}>
                    <span class="item-title" style="cursor: pointer; flex: 1; overflow: hidden; text-overflow: ellipsis; white-space: nowrap;">${Y.title}</span>
                `,_.style.cursor="pointer",_.addEventListener("click",te=>{if(te.target.type==="checkbox")return;const J=_.querySelector('input[type="checkbox"]');J&&(J.checked=!J.checked,J.dispatchEvent(new Event("change")))}),V.appendChild(_)}),b&&b.parentNode===a?a.insertBefore(V,b):a.appendChild(V),ge(),ze()}function ge(){e.querySelectorAll(".bulk-delete-checkbox").forEach(G=>{G.addEventListener("change",N=>{const V=N.target.getAttribute("data-chat-id");N.target.checked?l.add(V):(l.delete(V),t.checked=!1),ze()})})}function ze(){p&&(p.textContent=`${l.size} selected`),n.disabled=l.size===0,n.textContent=l.size>0?`Export ${l.size} Chat${l.size>1?"s":""}`:"Export";const D=e.querySelectorAll(".bulk-delete-checkbox"),G=e.querySelectorAll(".bulk-delete-checkbox:checked").length;t.checked=D.length>0&&G===D.length,t.indeterminate=G>0&&G<D.length}function gt(D){if(!D)return null;let G=D.parentElement;for(;G&&G!==document.body;){if(G.scrollHeight>G.clientHeight)return G;G=G.parentElement}return null}async function Be(){const D=document.querySelector("conversations-list")||document.querySelector('[role="navigation"]')||gt(document.querySelector('[data-test-id="conversation"]'));if(D){D.scrollTop=D.scrollHeight,D.dispatchEvent(new Event("scroll",{bubbles:!0})),await new Promise(N=>setTimeout(N,50));const G=Array.from(Z()).pop();if(G){G.scrollIntoView({block:"end"});const N=new WheelEvent("wheel",{deltaY:100,bubbles:!0,cancelable:!0});D.dispatchEvent(N)}await new Promise(N=>setTimeout(N,200))}}async function ht(){const D=t.parentElement,G=D.textContent.trim();if(D.lastChild&&D.lastChild.nodeType===Node.TEXT_NODE)D.lastChild.textContent="Loading all conversations...";else{const _=Array.from(D.childNodes).filter(U=>U.nodeType===Node.TEXT_NODE);_.length>0&&(_[_.length-1].textContent="Loading all conversations...")}t.disabled=!0,b.style.display="block",b.innerHTML=`
                <div style="display: flex; align-items: center; justify-content: center; gap: 8px; padding: var(--space-4); color: var(--gf-accent-primary);">
                    <div style="width: 16px; height: 16px; border: 2px solid var(--gf-accent-primary); border-top: 2px solid transparent; border-radius: 50%; animation: spin 1s linear infinite;"></div>
                    <span>Loading all conversations...</span>
                </div>
            `;let N=0;const V=5;let Y=0;for(;N<V;){const _=T.length;await Be();const te=me().filter(J=>J.id&&!y.has(J.id));te.length>0?(te.forEach(J=>{y.add(J.id),T.push(J)}),Y+=te.length,N=0,b.innerHTML=`
                        <div style="display: flex; align-items: center; justify-content: center; gap: 8px; padding: var(--space-4); color: var(--gf-accent-primary);">
                            <div style="width: 16px; height: 16px; border: 2px solid var(--gf-accent-primary); border-top: 2px solid transparent; border-radius: 50%; animation: spin 1s linear infinite;"></div>
                            <span>Loading conversations... (${T.length} found)</span>
                        </div>
                    `):N++,await new Promise(J=>setTimeout(J,100))}for(let _=0;_<2;_++){await Be();const U=me().filter(te=>te.id&&!y.has(te.id));U.length>0&&(U.forEach(te=>{y.add(te.id),T.push(te)}),Y+=U.length)}if(b.style.display="none",t.disabled=!1,D.lastChild&&D.lastChild.nodeType===Node.TEXT_NODE)D.lastChild.textContent="Select All";else{const _=Array.from(D.childNodes).filter(U=>U.nodeType===Node.TEXT_NODE);_.length>0&&(_[_.length-1].textContent="Select All")}}async function nt(){if(S)return;E&&(E.style.display="block"),k&&(k.textContent="Searching all conversations...");let D=0;const G=5;for(;D<G;){const N=T.length;await Be(),await new Promise(_=>setTimeout(_,500));const Y=me().filter(_=>_.id&&!y.has(_.id));Y.length>0?(Y.forEach(_=>{y.add(_.id),T.push(_)}),D=0,k&&(k.textContent=`Searching... (${T.length} found)`)):D++,await new Promise(_=>setTimeout(_,100))}for(let N=0;N<2;N++){await Be();const V=me().filter(Y=>Y.id&&!y.has(Y.id));V.length>0&&V.forEach(Y=>{y.add(Y.id),T.push(Y)})}S=!0,E&&(E.style.display="none")}t.addEventListener("change",async function(D){this.checked?(await ht(),q=i.value?T.filter(N=>N.title.toLowerCase().includes(i.value.toLowerCase())):[...T],q.forEach(N=>{l.add(N.id)}),de(q)):(l.clear(),e.querySelectorAll(".bulk-delete-checkbox").forEach(V=>{V.checked=!1}),ze())}),i.addEventListener("input",async D=>{const G=D.target.value.trim();if(P&&clearTimeout(P),G&&!S)P=setTimeout(async()=>{await nt();const N=G.toLowerCase();q=N?T.filter(V=>V.title.toLowerCase().includes(N)):[...T],de(q)},300);else{const N=G.toLowerCase();q=N?T.filter(V=>V.title.toLowerCase().includes(N)):[...T],de(q)}}),r.addEventListener("click",()=>{ie(),W()});const we=new MutationObserver(D=>{document.body.contains(e)||(ie(),we.disconnect())});we.observe(document.body,{childList:!0,subtree:!0}),n.addEventListener("click",async()=>{await Ht()});async function Ht(){const D=Array.from(l);if(D.length===0)return;const G=C&&C.value?C.value:"pdf";n.disabled=!0,n.innerHTML='<span style="display: inline-flex; align-items: center; gap: 8px;">Exporting... <svg width="16" height="16" viewBox="0 0 24 24" style="animation: spin 1s linear infinite;"><circle cx="12" cy="12" r="10" stroke="currentColor" stroke-width="3" fill="none" stroke-dasharray="31.4" stroke-dashoffset="10.5" stroke-linecap="round"></circle></svg></span>',c.style.display="block",g.style.display="block",s.style.display="none";const N=D.length,V=e.querySelector("#export-current-count"),Y=e.querySelector("#export-total-count"),_=e.querySelector("#export-progress-bar");Y.textContent=N;try{for(let U=0;U<D.length;U++){V.textContent=U+1,_.style.width=`${(U+1)/N*100}%`;const te=D[U],J=T.find(ke=>ke.id===te);try{if(J&&J.element){let ke=J.element;if(J.element.tagName!=="A"&&(ke=J.element.querySelector("a")||J.element),ke)if(ke.click(),await new Promise(ne=>setTimeout(ne,2e3)),await To(),typeof window.exportCurrentChat=="function")await window.exportCurrentChat(G,J.title),U<D.length-1&&await new Promise(ne=>setTimeout(ne,800));else if(G==="pdf"&&typeof window.exportCurrentChatToPDF=="function")await window.exportCurrentChatToPDF(J.title),U<D.length-1&&await new Promise(ne=>setTimeout(ne,800));else if(G==="pdf"&&typeof window.triggerGeminiToolboxExport=="function")window.triggerGeminiToolboxExport(),await new Promise(ne=>setTimeout(ne,1200));else throw new Error("Export function not available for format: "+G+". Please refresh the page.");else throw new Error(`Could not navigate to chat: ${J.title}`)}}catch{}}g.style.display="none",c.innerHTML=`
                    <div style="color: var(--gf-accent-success); font-size: 16px; text-align: center; padding: 20px;">
                        <svg width="24" height="24" viewBox="0 0 24 24" fill="currentColor" style="vertical-align: middle; margin-right: 8px;">
                            <path d="M9 16.17L4.83 12l-1.42 1.41L9 19 21 7l-1.41-1.41L9 16.17z"/>
                        </svg>
                        Successfully exported ${N} conversation${N>1?"s":""}
                    </div>
                `,setTimeout(()=>{W()},2e3)}catch(U){s.style.display="block",s.textContent=`Export failed: ${U.message}`,g.style.display="none",n.disabled=!1,n.textContent=l.size>0?`Export ${l.size} Chat${l.size>1?"s":""}`:"Export"}}}async function Ao(e,t){try{if(t?.aborted)throw new Error("Operation aborted by user.");try{e.scrollIntoView({block:"center",inline:"nearest"})}catch{}let n=Re(ft,e);const o=e.nextElementSibling;if(!n&&o&&(n=Re(ft,o)),n||(n=e.querySelector?.('button[aria-label*="More options"], button[aria-label*="menu" i], button')||o?.querySelector?.('button[aria-label*="More options"], button[aria-label*="menu" i], button')),!n)throw new Error("Three-dot button not found for conversation.");if(n.click(),await et(150),t?.aborted)throw new Error("Operation aborted by user.");const r=Re(Yt);if(!r)throw new Error("Overlay container for delete menu not found.");const i=await yt(Ut,r,7e3);if(!i)throw new Error("Delete button not found in menu");if(i.click(),await et(150),t?.aborted)throw new Error("Operation aborted by user.");const a=await yt(jt,r,7e3);if(!a)throw new Error("Confirm button not found in dialog");return a.click(),await Mo(e,15e3),{status:"success"}}catch(n){n.message.includes("aborted");const o=new KeyboardEvent("keydown",{key:"Escape",code:"Escape",keyCode:27,bubbles:!0,cancelable:!0});return document.body.dispatchEvent(o),await et(100),{status:"error",error:n.message}}}function Mo(e,t=15e3){return new Promise((n,o)=>{if(!e||!document.body.contains(e))return n();let r=0;const i=100,a=setInterval(()=>{r+=i,!document.body.contains(e)||e.offsetParent===null?(clearInterval(a),n()):r>=t&&(clearInterval(a),o(new Error("Element did not disappear within timeout.")))},i)})}function Tt(){const e=Z(),t={};let n=!1;e.forEach(o=>{const r=K(o);if(r){const i=Ae(o),d=(qe(o)||o.querySelector("a[href]"))?.getAttribute("href");let p;d?p=d.startsWith("http")?d:`https://gemini.google.com${d.startsWith("/")?"":"/"}${d}`:p=`https://gemini.google.com/app/${r.startsWith("c_")?r.substring(2):r}`;const s=w.chatMetadata?w.chatMetadata[r]:null;(!s||s.title!==i||s.url!==p)&&(t[r]={title:i,url:p},n=!0,w.chatMetadata||(w.chatMetadata={}),w.chatMetadata[r]={...w.chatMetadata[r]||{},title:i,url:p,lastSeen:Date.now()})}}),n&&window.geminiStorage&&Object.entries(t).forEach(([o,r])=>{window.geminiStorage.updateChatMetadata(o,r)})}let mt=null;function Fo(){if(mt)return;const e=document.querySelector("conversations-list");e&&(Tt(),w.settings.hideFolderedChats&&De(),mt=new MutationObserver(Kt(()=>{Tt(),w.settings.hideFolderedChats&&De()},200)),mt.observe(e,{childList:!0,subtree:!0,attributes:!0,attributeFilter:["href","class"]}))}function De(){const e=Z(),t=new Set;w.settings.hideFolderedChats&&w.folders.forEach(n=>{n.chatIds.forEach(o=>t.add(o))}),e.forEach(n=>{const o=K(n);o&&t.has(o)?n.style.display="none":n.style.display=""})}function It(e){const t=e.chatIds.map(n=>{const o=Z().find(i=>K(i)===n);let r=o?Ae(o,""):null;return!r&&w.chatMetadata&&w.chatMetadata[n]&&(r=w.chatMetadata[n].title),r||(r="Chat not found"),r=r.split(`
`)[0].trim(),`
                <div class="list-item chat-item" data-chat-id="${n}">
                    <span class="item-title">${r}</span>
                    <button class="icon-btn remove-from-folder-btn" data-chat-id="${n}" title="Remove from folder">
                        <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                            <line x1="18" y1="6" x2="6" y2="18"></line>
                            <line x1="6" y1="6" x2="18" y2="18"></line>
                        </svg>
                    </button>
                </div>
            `}).join("");return`
            <div class="modal-header" style="display: grid; grid-template-columns: auto 1fr auto; align-items: center; gap: 16px;">
                <button class="icon-btn" id="back-to-folders-btn" style="display: flex; align-items: center; gap: 4px; font-family: 'Google Sans', 'Roboto', sans-serif;">
                    <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                        <line x1="19" y1="12" x2="5" y2="12"></line>
                        <polyline points="12 19 5 12 12 5"></polyline>
                    </svg>
                    <span>Back</span>
                </button>
                <h2 style="text-align: center; margin: 0; font-family: 'Google Sans', 'Roboto', sans-serif;">${e.name}</h2>
                <button class="modal-close" id="close-modal-btn" aria-label="Close">
                    <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                        <line x1="18" y1="6" x2="6" y2="18"></line>
                        <line x1="6" y1="6" x2="18" y2="18"></line>
                    </svg>
                </button>
                </div>
            <div class="modal-body">
                ${t||"<p>No chats in this folder yet.</p>"}
            </div>
        `}function At(e){const t=u.querySelector("#manage-single-folder-modal");if(!t)return;const n=t.querySelector(".modal-content");n&&n.addEventListener("click",o=>{if(o.target.closest("#back-to-folders-btn"))W();else if(o.target.closest("#close-modal-btn"))W();else if(o.target.closest(".remove-from-folder-btn")){const r=o.target.closest(".remove-from-folder-btn").dataset.chatId,i=w.folders.find(a=>a.id===e);if(i){i.chatIds=i.chatIds.filter(d=>d!==r),Ne(),De();const a=u.querySelector("#manage-single-folder-modal");if(a){const d=a.querySelector(".modal-body");if(d){const p=It(i),s=document.createElement("div");s.innerHTML=p;const g=s.querySelector(".modal-body");g&&(d.innerHTML=g.innerHTML)}At(e)}}}else if(o.target.closest(".chat-item")){const r=o.target.closest(".chat-item").dataset.chatId,i=Z().find(d=>K(d)===r),a=Xt(r,i);a?(io(),window.location.href=a):X("Could not open this chat. Please refresh Gemini and try again.")}})}function Mt(){const t=u.getElementById("bulk-delete-modal")||u.getElementById("chat-tools-modal");if(!t)return;const n=t.querySelector("#bulk-delete-select-all");let o=t.querySelectorAll(".bulk-delete-checkbox");const r=t.querySelector("#start-bulk-delete-btn"),i=t.querySelector("#bulk-delete-status"),a=t.querySelector("#bulk-delete-search"),d=t.querySelector("#bulk-delete-counter"),p=t.querySelector("#bulk-delete-breakdown"),s=t.querySelector("#bulk-delete-list"),g=t.querySelector("#bulk-delete-loading");let c=t.querySelector("#bulk-delete-loading-more");const b=t.querySelector("#include-foldered-chats"),C=t.querySelector("#include-pinned-chats"),T=t.querySelector("#bulk-delete-search-loading"),q=t.querySelector("#bulk-delete-search-status"),l=t.querySelector("#bulk-delete-load-more-actions"),y=t.querySelector("#bulk-delete-load-next-btn"),m=t.querySelector("#bulk-delete-load-more-status");if(!s||!n||!r||!d||!a)return;let h=new Set,x=!1,f=0;const S=3;let P=!1,E=!1,k=!1,O=null;const H=new Set;w.folders.forEach(L=>{L.chatIds.forEach(v=>H.add(v))});function R(){let L=Z();return w.settings.hideFolderedChats&&(L=L.filter(v=>{const A=K(v);return A&&!H.has(A)})),L.filter(v=>{const A=K(v);return A&&!h.has(A)})}function ie(){o=t.querySelectorAll(".bulk-delete-checkbox"),o.forEach(L=>{L._bulkDeleteChangeHandlerAttached||(L.addEventListener("change",V),L._bulkDeleteChangeHandlerAttached=!0)})}function de(L=!0){if(l&&(l.style.display="block"),m){const v=t.querySelectorAll(".bulk-delete-item").length;m.textContent=L?`Showing ${v} loaded conversations. Load another 100 to go further back.`:`Showing ${v} loaded conversations. No more conversations found.`}y&&(y.disabled=!L||x,y.textContent=L?"Load next 100":"No more conversations")}function ge(L){const v=L.slice(0,100);if(v.length===0)return 0;const A=_e(v,H,P,E),F=document.createElement("div");for(F.innerHTML=A;F.firstChild;)c&&c.parentNode===s?s.insertBefore(F.firstChild,c):l&&l.parentNode===s?s.insertBefore(F.firstChild,l):s.appendChild(F.firstChild);return v.forEach(I=>{const M=K(I);M&&h.add(M)}),ie(),_(),V(),v.length}async function ze(L=4e3){const v=Date.now();for(;Date.now()-v<L;){const A=R();if(A.length>0)return A.slice(0,100);await new Promise(F=>setTimeout(F,250))}return[]}gt();async function gt(){try{g&&(g.style.display="none"),c=t.querySelector("#bulk-delete-loading-more"),s.querySelectorAll(".bulk-delete-item").forEach(F=>F.remove()),h.clear();const v=R(),A=ge(v);A===0&&s.insertAdjacentHTML("afterbegin",'<p style="text-align: center; color: var(--gf-text-secondary); padding: 40px 0;">No conversations found.</p>'),de(A>0),V()}catch{g&&(g.style.display="none"),s.innerHTML='<p style="text-align: center; color: var(--gf-text-secondary); padding: 40px 0;">Error loading conversations. Please refresh and try again.</p>'}}async function Be(L=100){const v=Math.max(1,Math.min(100,L)),A=R().slice(0,v);if(A.length>0)return f=0,ge(A);const F=Z().length,I=[document.querySelector("conversations-list"),document.querySelector('[role="navigation"]'),document.querySelector(".conversation-list"),document.querySelector('[data-testid="conversation-list"]')];let M=null;for(const B of I)if(B&&(B.scrollHeight>B.clientHeight||B.querySelector('[data-test-id="conversation"]'))){M=B;break}if(!M){const B=document.querySelector('[data-test-id="conversation"]');if(B){let j=B.parentElement;for(;j&&j!==document.body;){if(j.scrollHeight>j.clientHeight){M=j;break}j=j.parentElement}}}if(M){const B=M.scrollTop;M.scrollTop=M.scrollHeight,M.dispatchEvent(new Event("scroll",{bubbles:!0,composed:!0}));const j=Z();if(j.length>0){const Ce=j[j.length-1];Ce.scrollIntoView({block:"end",inline:"nearest"});const ue=new WheelEvent("wheel",{deltaY:300,bubbles:!0,cancelable:!0,view:window});Ce.dispatchEvent(ue),M.dispatchEvent(ue)}let oe=0;const re=3;for(;oe<re&&(await new Promise(ue=>setTimeout(ue,100)),!(Z().length>F));)oe++;if(!(Z().length>F)){const Ce=M.querySelector('.loading-indicator, .spinner, [aria-label*="loading"]')}M.scrollTop=B}const $=(await ze()).slice(0,v);return $.length>0?(f=0,ge($)):(f++,0)}function ht(L,v){const A=Array.from(t.querySelectorAll(".bulk-delete-item")).slice(L);let F=0;return A.forEach(I=>{if(F>=v)return;const M=I.querySelector(".bulk-delete-checkbox"),$=I.style.display!=="none",B=I.dataset.isFoldered==="true",j=I.dataset.isPinned==="true";M&&$&&!(B&&!P||j&&!E)&&!M.disabled&&(M.checked=!0,F++)}),F}async function nt(L=100,v={}){if(x)return 0;const A=v.selectNewlyLoaded===!0,F=t.querySelectorAll(".bulk-delete-item").length;x=!0;let I=0,M=0;const $=12;y&&(y.disabled=!0,y.textContent="Loading..."),c&&(c.style.display="block");try{for(;I<L&&M<$&&f<S;){if(y&&(y.textContent=I>0?`Loading ${Math.min(I,L)}/${L}...`:"Loading..."),c){const ae=c.querySelector("span");ae&&(ae.textContent=I>0?`Loading next 100 conversations... ${Math.min(I,L)}/${L} added`:"Loading next 100 conversations...")}const B=t.querySelectorAll(".bulk-delete-item").length,j=L-I,oe=await Be(j),re=t.querySelectorAll(".bulk-delete-item").length;if(M++,I+=oe,oe===0&&re<=B)break;I<L&&await new Promise(ae=>setTimeout(ae,150))}if(A&&I>0&&(ht(F,L),V()),I>0&&c){const B=c.querySelector("span");B&&(B.textContent=`Added ${I} more conversation${I===1?"":"s"}`)}return I}catch{return I}finally{if(x=!1,c){c.style.display="none";const B=c.querySelector("span");B&&(B.textContent="Loading next 100 conversations...")}de(f<S)}}let we=null;function Ht(){if(we)return;we=new MutationObserver(v=>{let A=!1;v.forEach(F=>{F.addedNodes.forEach(I=>{I.nodeType===Node.ELEMENT_NODE&&(I.matches?.('[data-test-id="conversation"]')?[I]:I.querySelectorAll?.('[data-test-id="conversation"]')||[]).forEach($=>{const B=K($);B&&!h.has(B)&&(A=!0)})})}),A&&setTimeout(()=>D(),50)});const L=document.querySelector("conversations-list");L&&we.observe(L,{childList:!0,subtree:!0})}function D(){let v=Z().filter(A=>{const F=K(A);return F&&!h.has(F)});if(w.settings.hideFolderedChats){const A=new Set;w.folders.forEach(F=>{F.chatIds.forEach(I=>A.add(I))}),v=v.filter(F=>{const I=K(F);return!A.has(I)})}if(v.length>0){f=0;const A=_e(v,H,P,E),F=document.createElement("div");for(F.innerHTML=A;F.firstChild;)c&&c.parentNode===s?s.insertBefore(F.firstChild,c):s.appendChild(F.firstChild);v.forEach(M=>{const $=K(M);$&&h.add($)}),o=t.querySelectorAll(".bulk-delete-checkbox"),Array.from(o).slice(-v.length).forEach(M=>{M.addEventListener("change",V)})}}function G(){we&&(we.disconnect(),we=null)}const N=new MutationObserver(L=>{L.forEach(v=>{v.type==="childList"&&v.removedNodes.forEach(A=>{(A===t||A.nodeType===Node.ELEMENT_NODE&&A.contains(t))&&(G(),N.disconnect())})})});N.observe(document.body,{childList:!0,subtree:!0}),y&&y.addEventListener("click",()=>{nt(100,{selectNewlyLoaded:n.checked})});function V(){if(!d||!r)return;const L=Array.from(o).filter(M=>{const $=M.closest(".bulk-delete-item");return $&&$.style.display!=="none"});let v=0,A=0,F=0;L.forEach(M=>{if(M.checked){const $=M.closest(".bulk-delete-item"),B=$&&$.dataset.isFoldered==="true",j=$&&$.dataset.isPinned==="true";B?v++:j?A++:F++}});const I=v+A+F;if(d.textContent=`${I} selected`,p)if(I>0){const M=[];F>0&&M.push(`Regular: ${F}`),v>0&&M.push(`Foldered: ${v}`),A>0&&M.push(`Pinned: ${A}`),M.length>1?(p.textContent=`(${M.join(", ")})`,p.style.display="block"):(p.textContent="",p.style.display="none")}else p.textContent="",p.style.display="none";I>0?(r.textContent=`Delete ${I} Chat${I===1?"":"s"}`,r.disabled=!1):(r.textContent="Delete 0 Chats",r.disabled=!0)}function Y(L){const v=t.querySelectorAll(".bulk-delete-item"),A=L.toLowerCase().trim();let F=0;v.forEach(M=>{const $=M.querySelector(".item-title"),B=$?$.textContent.toLowerCase():M.textContent.toLowerCase();A===""||B.includes(A)?(M.style.display="",F++):M.style.display="none"});const I=s.querySelector(".empty-state");I&&I.remove(),F===0&&A&&s.insertAdjacentHTML("beforeend",`
                    <div class="empty-state" style="text-align: center; padding: 40px 20px; color: var(--gf-text-secondary);">
                        <svg width="48" height="48" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.5" style="margin: 0 auto 16px; opacity: 0.4;">
                            <circle cx="11" cy="11" r="8"></circle>
                            <path d="m21 21-4.35-4.35"></path>
                        </svg>
                        <p style="margin: 0; font-size: 14px;">No conversations found matching "${A}"</p>
                    </div>
                `),V()}a.addEventListener("input",async L=>{const v=L.target.value.trim();O&&clearTimeout(O),O=setTimeout(()=>{Y(v)},150)}),a.addEventListener("focus",()=>{a.style.borderColor="var(--gf-accent-primary)",a.style.boxShadow="0 0 0 2px rgba(138, 180, 248, 0.2)"}),a.addEventListener("blur",()=>{a.style.borderColor="var(--gf-border-color)",a.style.boxShadow="none"}),b&&b.addEventListener("change",L=>{P=L.target.checked,_(),V(),window.geminiAPI&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.FEATURE_TOGGLED,{feature:"includeFolderedChats",enabled:P})}),C&&C.addEventListener("change",L=>{E=L.target.checked,_(),V(),window.geminiAPI&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.FEATURE_TOGGLED,{feature:"includePinnedChats",enabled:E})});function _(){t.querySelectorAll(".bulk-delete-item").forEach(v=>{const A=v.querySelector(".bulk-delete-checkbox"),F=v.dataset.isFoldered==="true",I=v.dataset.isPinned==="true";if(F&&!P||I&&!E){v.classList.add("foldered-protected"),A.disabled=!0,A.checked=!1;const $=v.querySelector(".protected-badge");$&&$.remove();const B=v.querySelector(".item-title");B&&(F&&!P?B.insertAdjacentHTML("afterend",'<span class="protected-badge">Protected (Folder)</span>'):I&&!E&&B.insertAdjacentHTML("afterend",'<span class="protected-badge">Protected (Pinned)</span>'))}else{v.classList.remove("foldered-protected"),A.disabled=!1;const $=v.querySelector(".protected-badge");$&&$.remove()}})}if(o.forEach(L=>{L.addEventListener("change",V)}),!n)return;function U(){return o=t.querySelectorAll(".bulk-delete-checkbox"),Array.from(o).filter(L=>{const v=L.closest(".bulk-delete-item"),A=v&&v.style.display!=="none",F=v&&v.dataset.isFoldered==="true",I=v&&v.dataset.isPinned==="true";return A&&!(F&&!P||I&&!E)&&!L.disabled})}async function te(L){let v=U(),A=0;const F=10;for(;v.length<L&&A<F&&!(!n.checked||f>=S);){const I=t.querySelectorAll(".bulk-delete-item").length,M=L-v.length,$=await nt(M),B=t.querySelectorAll(".bulk-delete-item").length;if(A++,v=U(),$===0&&B<=I)break}return v}n.addEventListener("change",async function(){const L=this.checked;if(o=t.querySelectorAll(".bulk-delete-checkbox"),o.forEach(v=>{v.checked=!1}),L){const v=n.closest("label")?.querySelector("span"),A=v?v.textContent:"Select latest 100";n.disabled=!0,v&&(v.textContent="Selecting latest 100...");try{(await te(100)).slice(0,100).forEach(I=>{I.checked=!0})}finally{v&&(v.textContent=A),n.disabled=!1}}V()});async function J(){const L=document.querySelector('[data-test-id="side-nav-menu-button"]'),v=document.querySelector("mat-sidenav");L&&v&&(v.classList.contains("mat-drawer-opened")||v.getAttribute("aria-hidden")==="false"||(console.log("[Bulk Delete] Opening sidebar..."),L.click(),await new Promise(se=>setTimeout(se,500))));const A=document.querySelector("infinite-scroller");if(!A){console.warn("[Bulk Delete] Could not find infinite-scroller, using fallback method"),await ke();return}const I=n.parentElement.querySelector("span"),M=I?I.textContent:"Select all";I&&(I.textContent="Loading all conversations..."),n.disabled=!0,g.style.display="block",g.innerHTML=`
                <div style="display: flex; align-items: center; justify-content: center; gap: 8px; padding: var(--space-4); color: var(--gf-accent-primary);">
                    <div style="width: 16px; height: 16px; border: 2px solid var(--gf-accent-primary); border-top: 2px solid transparent; border-radius: 50%; animation: spin 1s linear infinite;"></div>
                    <span>Loading all conversations...</span>
                </div>
            `;let $=0,B=0,j=0;const oe=300;let re=0,ae=0;for(console.log("[Bulk Delete] Starting aggressive conversation loading...");j<oe;){j++;const ce=Z().length,se=A.scrollHeight;A.scrollTop=se+1e5,I&&(I.textContent=`Loading... (${ce} conversations)`),await new Promise(be=>setTimeout(be,400));const Oe=document.querySelector('[data-test-id="loading-history-spinner"]');if(Oe&&Oe.offsetParent!==null){B=0,ae=0,await new Promise(be=>setTimeout(be,800));continue}const Ee=ce===$,ve=se===re;if(Ee&&ve){if(B++,ae++,B>=8){console.log(`[Bulk Delete] All conversations loaded! Total: ${ce}`);break}}else B=0,ae=0,$=ce,re=se;if(ae>=5&&ce>0){console.log(`[Bulk Delete] Early exit after ${j} attempts`);break}const rt=Ee&&ve?150:100;await new Promise(be=>setTimeout(be,rt))}const ue=Z().filter(ce=>{const se=K(ce);return se&&!h.has(se)});if(ue.length>0){const ce=_e(ue,H,P,E),se=document.createElement("div");for(se.innerHTML=ce;se.firstChild;)c&&c.parentNode===s?s.insertBefore(se.firstChild,c):s.appendChild(se.firstChild);ue.forEach(Ee=>{const ve=K(Ee);ve&&h.add(ve)}),o=t.querySelectorAll(".bulk-delete-checkbox"),Array.from(o).slice(-ue.length).forEach(Ee=>{Ee.addEventListener("change",V)})}I&&(I.textContent=M),n.disabled=!1,g.style.display="none",f=0,console.log(`[Bulk Delete] Finished! Total in list: ${t.querySelectorAll(".bulk-delete-item").length}`)}async function ke(){console.log("[Bulk Delete] Using fallback loading method...");let L=0;const v=5;for(;L<v;){await ne();const F=Z().filter(I=>{const M=K(I);return M&&!h.has(M)});if(F.length>0){const I=_e(F,H,P,E),M=document.createElement("div");for(M.innerHTML=I;M.firstChild;)c&&c.parentNode===s?s.insertBefore(M.firstChild,c):s.appendChild(M.firstChild);F.forEach(B=>{const j=K(B);j&&h.add(j)}),o=t.querySelectorAll(".bulk-delete-checkbox"),Array.from(o).slice(-F.length).forEach(B=>{B.addEventListener("change",V)}),L=0}else L++;await new Promise(I=>setTimeout(I,150))}}async function ne(){const L=document.querySelector("conversations-list")||document.querySelector('[role="navigation"]')||He(document.querySelector('[data-test-id="conversation"]'));if(L){L.scrollTop=L.scrollHeight,L.dispatchEvent(new Event("scroll",{bubbles:!0})),await new Promise(A=>setTimeout(A,50));const v=Array.from(Z()).pop();if(v){v.scrollIntoView({block:"end"});const A=new WheelEvent("wheel",{deltaY:100,bubbles:!0,cancelable:!0});L.dispatchEvent(A)}await new Promise(A=>setTimeout(A,200))}}function He(L){if(!L)return null;let v=L.parentElement;for(;v&&v!==document.body;){if(v.scrollHeight>v.clientHeight)return v;v=v.parentElement}return null}async function ln(){if(k)return;T&&(T.style.display="block"),q&&(q.textContent="Searching all conversations...");let L=0;const v=5;for(;L<v;){const A=h.size;await ne(),await new Promise(M=>setTimeout(M,500));const I=Z().filter(M=>{const $=K(M);return $&&!h.has($)});if(I.length>0){const M=_e(I,H,P,E),$=document.createElement("div");for($.innerHTML=M;$.firstChild;)c&&c.parentNode===s?s.insertBefore($.firstChild,c):s.appendChild($.firstChild);I.forEach(j=>{const oe=K(j);oe&&h.add(oe)}),o=t.querySelectorAll(".bulk-delete-checkbox"),Array.from(o).slice(-I.length).forEach(j=>{j.addEventListener("change",V)}),L=0,q&&(q.textContent=`Searching... (${h.size} found)`)}else L++;await new Promise(M=>setTimeout(M,100))}for(let A=0;A<2;A++){await ne();const I=Z().filter(M=>{const $=K(M);return $&&!h.has($)});if(I.length>0){const M=_e(I,H,P,E),$=document.createElement("div");for($.innerHTML=M;$.firstChild;)c&&c.parentNode===s?s.insertBefore($.firstChild,c):s.appendChild($.firstChild);I.forEach(j=>{const oe=K(j);oe&&h.add(oe)}),o=t.querySelectorAll(".bulk-delete-checkbox"),Array.from(o).slice(-I.length).forEach(j=>{j.addEventListener("change",V)})}}k=!0,T&&(T.style.display="none")}V();const Ot=t.querySelector("#bulk-delete-tab-panel"),Gt=Ot?Ot.querySelector(".cancel-action"):t.querySelector(".cancel-action");Gt&&Gt.addEventListener("click",()=>{W()}),r.addEventListener("click",async()=>{const L=Array.from(o).filter(ee=>ee.checked);if(L.length===0){i.textContent="No items selected.";return}const v=[];L.forEach(ee=>{ee.dataset.chatId&&v.push(ee.dataset.chatId)});const A=new Set(v),F=A.size;if(F===0){i.textContent="No chats to delete.";return}const M=`
                <div style="margin-bottom: 24px;">
                    <div style="display: flex; align-items: center; gap: var(--gap-medium); margin-bottom: var(--space-4);">
                        <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="var(--gf-accent-danger)" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                            <path d="M3 6h18"></path>
                            <path d="M19 6v14a2 2 0 01-2 2H7a2 2 0 01-2-2V6m3 0V4a2 2 0 012-2h4a2 2 0 012 2v2"></path>
                            <line x1="10" y1="11" x2="10" y2="17"></line>
                            <line x1="14" y1="11" x2="14" y2="17"></line>
                        </svg>
                        <p style="margin: 0; color: var(--gf-text-primary); font-size: 16px; font-weight: 500; line-height: 1.5;">
                            ${`Are you sure you want to delete ${F} conversation${F>1?"s":""}? This action cannot be undone.`}
                        </p>
                    </div>
                    <p style="margin: 0 0 0 36px; color: var(--gf-text-secondary); font-size: 14px;">
                        All selected conversations will be permanently deleted.
                    </p>
                </div>
                <div class="modal-footer">
                    <div style="display: flex; justify-content: space-between; align-items: center; width: 100%;">
                        <button type="button" class="button secondary" id="cancel-bulk-delete-confirm" >Cancel</button>
                        <button type="button" class="button danger" id="confirm-bulk-delete-action" >
                            <svg width="16" height="16" viewBox="0 0 16 16" fill="currentColor" style="margin-right: 6px; vertical-align: middle;">
                                <path d="M2 4h12v9a1 1 0 01-1 1H3a1 1 0 01-1-1V4zm1.5-1.5h9V2a.5.5 0 00-.5-.5H4a.5.5 0 00-.5.5v.5zM6.5 6v5m3-5v5"/>
                            </svg>
                            Delete
                        </button>
                    </div>
                </div>
            `;if(le("bulk-delete-confirm-modal","Confirm Bulk Deletion",M,480),!await new Promise(ee=>{setTimeout(()=>{const xe=u.querySelector("#confirm-bulk-delete-action"),Fe=u.querySelector("#cancel-bulk-delete-confirm");xe&&(xe.onclick=()=>{W(),ee(!0)}),Fe&&(Fe.onclick=()=>{W(),ee(!1)})},100)}))return;const B=Z();A.forEach(ee=>{const xe=B.find(Fe=>K(Fe)===ee);xe&&xe.style.display==="none"&&(xe.style.display="")}),W(),No();const j=document.createElement("style");j.id="bulk-delete-hide-dialogs",j.textContent=`
                .cdk-overlay-container,
                [role="dialog"],
                .modal-container,
                .overlay-container {
                    visibility: hidden !important;
                    opacity: 0 !important;
                    pointer-events: none !important;
                }
            `,document.head.appendChild(j);const oe=document.createElement("div");oe.innerHTML=Po(),u.appendChild(oe);const re=u.getElementById("gemini-delete-all-overlay");if(!re)return;const ae=re.querySelector(".message"),Ce=re.querySelector("#progress-status"),ue=re.querySelector("#progress-counter"),ce=re.querySelector(".progress-bar-inner"),se=re.querySelector(".cancel-button"),Oe=re.querySelector(".spinner"),Ee=re.querySelector(".completion-tick");let ve=!1;const rt=new AbortController;se&&se.addEventListener("click",()=>{ve=!0,rt.abort(),ae&&(ae.textContent="Cancelling..."),setTimeout(()=>{const ee=document.getElementById("bulk-delete-hide-dialogs");ee&&ee.remove()},1e3)});let be=0,Ge=0;const Rt=Array.from(A);try{for(let ee=0;ee<Rt.length&&!ve;ee++){const xe=Rt[ee];Ce&&(Ce.textContent=`Deleting chat ${ee+1} of ${F}...`),ue&&(ue.textContent=`${ee+1} / ${F}`),ce&&(ce.style.width=`${(ee+1)/F*100}%`);const Fe=B.find(Vt=>K(Vt)===xe);Fe&&(await Ao(Fe,rt.signal)).status==="success"?be++:Ge++,await et(250)}}catch{Ge++}Oe&&(Oe.style.display="none"),Ee&&(Ee.style.display="block"),ce&&(ce.style.width="100%"),ue&&(ue.textContent=`${be} / ${F}`),ae&&(ve?ae.textContent="Deletion cancelled.":Ge>0?ae.textContent=`Finished. Deleted ${be}, failed ${Ge}.`:ae.textContent="All selected items deleted!"),!ve&&window.geminiAPI&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.BULK_DELETE_USED,{action:"completed",deletedCount:be,errorCount:Ge,totalSelected:F,successRate:F>0?(be/F*100).toFixed(1):0}),setTimeout(()=>{re.classList.add("hidden");const ee=()=>{oe&&oe.parentNode&&oe.remove();const xe=document.getElementById("bulk-delete-hide-dialogs");xe&&xe.remove(),W()};re.addEventListener("transitionend",ee,{once:!0}),setTimeout(ee,500)},3e3)})}function Po(){return`
            <div id="gemini-delete-all-overlay" class="visible">
                <div class="spinner"></div>
                <svg class="completion-tick" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 52 52">
                    <circle class="tick-circle" cx="26" cy="26" r="25" fill="none"/>
                    <path class="tick-path" fill="none" d="M14.1 27.2l7.1 7.2 16.7-16.8"/>
                </svg>
                <div class="message">Deleting...</div>
                <div class="progress-container">
                    <div class="progress-text">
                        <span id="progress-status">Starting...</span>
                        <span id="progress-counter">0 / 0</span>
                    </div>
                    <div class="progress-bar">
                        <div class="progress-bar-inner"></div>
                    </div>
                </div>
                <button class="cancel-button">Cancel</button>
            </div>
        `}function No(){if(u.getElementById("gemini-delete-all-overlay-styles"))return;const e={isDark:document.body.classList.contains("dark-theme"),backgroundColor:"var(--gf-bg-primary)",textColor:"var(--gf-text-primary)",secondaryTextColor:"var(--gf-text-secondary)",accentColor:"var(--gf-accent-primary)",progressTrackColor:"rgba(128, 128, 128, 0.2)",successColor:"#34a853"},t=`
          #gemini-delete-all-overlay {
            position: fixed; top: 0; left: 0; width: 100vw; height: 100vh;
            background-color: var(--gf-bg-primary);
            z-index: 2147483647; display: flex; flex-direction: column;
            justify-content: center; align-items: center;
            font-family: 'Google Sans', Roboto, Arial, sans-serif; color: ${e.textColor}; text-align: center;
            opacity: 1; transition: opacity 0.3s ease-in-out;
          }
          #gemini-delete-all-overlay.hidden { opacity: 0; pointer-events: none; }
          #gemini-delete-all-overlay .spinner {
            display: block;
            border: 3px solid ${e.progressTrackColor}; border-top: 3px solid ${e.accentColor};
            border-radius: 50%; width: 50px; height: 50px;
            animation: spin 0.8s linear infinite; margin-bottom: 25px;
          }
          @keyframes spin { 0% { transform: rotate(0deg); } 100% { transform: rotate(360deg); } }
          
          #gemini-delete-all-overlay .completion-tick {
            display: none; width: 60px; height: 60px;
            border-radius: 50%;
            stroke-width: 5; stroke: ${e.successColor};
            stroke-miterlimit: 10;
            animation: draw-tick-container 0.5s ease-out forwards;
            margin-bottom: 20px;
          }
          #gemini-delete-all-overlay .completion-tick .tick-path {
            stroke-dasharray: 100;
            stroke-dashoffset: 100;
            animation: draw-tick-path 0.5s 0.2s ease-out forwards;
          }
          @keyframes draw-tick-container {
            0% { opacity: 0; transform: scale(0.5); }
            100% { opacity: 1; transform: scale(1); }
          }
          @keyframes draw-tick-path {
            to { stroke-dashoffset: 0; }
          }
          #gemini-delete-all-overlay .message { font-size: 20px; font-weight: 500; margin-bottom: var(--space-2); }
          
          #gemini-delete-all-overlay .progress-container {
            display: flex; flex-direction: column; align-items: center;
            width: 300px; margin: 10px 0;
          }
          #gemini-delete-all-overlay .progress-text { 
            font-size: 14px; color: ${e.secondaryTextColor}; 
            margin-bottom: var(--space-2); width: 100%;
            display: flex; justify-content: space-between;
          }
          
          #gemini-delete-all-overlay .progress-bar {
            width: 100%; height: 4px; background-color: ${e.progressTrackColor};
            border-radius: 4px; overflow: hidden;
          }
          #gemini-delete-all-overlay .progress-bar-inner {
            height: 100%; width: 0%;
            background-color: ${e.accentColor};
            transition: width var(--anim-normal) var(--ease-out);
            border-radius: 4px;
          }
          
          #gemini-delete-all-overlay .cancel-button {
            margin-top: var(--space-4); color: ${e.secondaryTextColor};
            font-size: 14px; background: none; border: 1px solid ${e.secondaryTextColor};
            padding: 8px 16px; cursor: pointer;
            font-family: 'Google Sans', Roboto, Arial, sans-serif;
            border-radius: 4px; transition: background-color 0.15s;
          }
          #gemini-delete-all-overlay .cancel-button:hover {
            background-color: rgba(128, 128, 128, 0.2);
          }
        `,n=document.createElement("style");n.id="gemini-delete-all-overlay-styles",n.textContent=t,u.appendChild(n)}async function Ft(e){try{if(!chrome.runtime||!chrome.runtime.getURL)throw new Error("Extension context invalidated - please refresh the page");const t=chrome.runtime.getURL(e);console.log(`[Prompt Library] Fetching resource: ${e} from ${t}`);const n=await fetch(t);if(!n.ok)throw new Error(`Failed to fetch ${e}: HTTP ${n.status} ${n.statusText}`);const o=await n.text();return console.log(`[Prompt Library] Successfully loaded ${e} (${o.length} bytes)`),o}catch(t){throw console.error(`[Prompt Library] Error fetching ${e}:`,t),t.message&&t.message.includes("Extension context invalidated")?X("Extension was updated or reloaded. Please refresh the page to continue."):X(`Failed to load ${e}. Please refresh the page and try again.`),t}}async function qo(){if(!u.getElementById("prompt-library-modal"))try{if(!chrome.runtime||!chrome.runtime.getURL)throw new Error("Extension context invalidated - please refresh the page");const[e,t]=await Promise.all([Ft("prompt_library.html"),Ft("prompt_library.css")]),n=document.createElement("div");n.innerHTML=e;const o=n.firstElementChild;if(u.appendChild(o),t&&!u.querySelector("#prompt-library-styles")){const i=document.createElement("style");i.id="prompt-library-styles",i.textContent=t,u.appendChild(i);const a=document.createElement("style");a.id="modal-size-overrides",a.textContent=`
                        /* Override ALL modal heights except prompt library with higher specificity */
                        #gemini-folders-injector-host .infi-chatgpt-modal:not(#prompt-library-modal) .modal-content {
                            min-height: auto !important;
                            height: auto !important;
                        }
                        
                        /* Even more specific for manage folders */
                        #gemini-folders-injector-host #manage-folders-modal .modal-content {
                            min-height: auto !important;
                            height: auto !important;
                        }
                    `,u.appendChild(a)}}catch(e){throw console.error("[Prompt Library] Resource injection failed:",e),e}}function $e(){try{return chrome&&chrome.storage&&chrome.storage.local&&typeof chrome.storage.local.get=="function"}catch{return!1}}let ot=null,he=!0,Te=null,ye=!0;async function Pt(){try{if(!$e()){he=CONFIG.FEATURES.wordCounterDefault||!0;return}const e=await chrome.storage.local.get("wordCounterEnabled");he=e.wordCounterEnabled!==void 0?e.wordCounterEnabled:CONFIG.FEATURES.wordCounterDefault||!0}catch(e){!e.message||e.message.includes("Extension context invalidated"),he=CONFIG.FEATURES.wordCounterDefault||!0}}async function _o(){try{if(!$e()){X("Extension was updated. Please refresh the page to save settings.");return}await chrome.storage.local.set({wordCounterEnabled:he})}catch(e){e.message&&e.message.includes("Extension context invalidated")?X("Extension was updated. Please refresh the page to save settings."):X("Failed to save word counter settings.")}}async function Nt(){if(await Pt(),ot&&(ot.destroy(),ot=null),he)try{typeof WordCounter<"u"&&(ot=new WordCounter)}catch{X("Failed to initialize word counter. Please refresh the page.")}}async function qt(){try{if(!$e()){ye=CONFIG.FEATURES?.enhancePrompt!==!1;return}const e=await chrome.storage.sync.get("enhancePromptEnabled");ye=e.enhancePromptEnabled!==void 0?e.enhancePromptEnabled:CONFIG.FEATURES?.enhancePrompt!==!1}catch(e){!e.message||e.message.includes("Extension context invalidated"),ye=CONFIG.FEATURES?.enhancePrompt!==!1}}async function Do(){try{if(!$e()){X("Extension was updated. Please refresh the page to save settings.");return}await chrome.storage.sync.set({enhancePromptEnabled:ye})}catch(e){e.message&&e.message.includes("Extension context invalidated")?X("Extension was updated. Please refresh the page to save settings."):X("Failed to save enhance prompt settings.")}}async function _t(){if(await qt(),Te&&Te.destroy&&(Te.destroy(),Te=null),!!ye&&!(typeof window.EnhancePromptModule>"u"))try{const t=(await window.geminiAPI.getSubscriptionStatus())?.isPremium||!1;window.EnhancePromptModule.initialize(u,{isPremium:t}),Te=window.EnhancePromptModule}catch{}}async function $o(){if(Te&&Te.updatePremiumStatus)try{const e=await window.geminiAPI.getSubscriptionStatus();Te.updatePremiumStatus(e?.isPremium||!1)}catch{}}let fe=!0;async function Dt(){try{if(!$e()){fe=!0;return}const e=await chrome.storage.sync.get("pinnedMessagesEnabled");fe=e.pinnedMessagesEnabled!==void 0?e.pinnedMessagesEnabled:!0}catch(e){!e.message||e.message.includes("Extension context invalidated"),fe=!0}}async function zo(){try{if(!$e()){X("Extension was updated. Please refresh the page to save settings.");return}await chrome.storage.sync.set({pinnedMessagesEnabled:fe})}catch(e){e.message&&e.message.includes("Extension context invalidated")?X("Extension was updated. Please refresh the page to save settings."):X("Failed to save pinned messages settings.")}}async function $t(){if(await Dt(),!fe){window.PinnedMessages&&window.PinnedMessages.removePinButtons&&window.PinnedMessages.removePinButtons();return}if(window.PinnedMessages&&window.PinnedMessages.initialize)try{window.PinnedMessages.initialize()}catch{}}function Ye(e,t,n){const o=n||(typeof crypto<"u"&&crypto.randomUUID?crypto.randomUUID():"corr_"+Math.random().toString(36).slice(2));if(t&&Number.isFinite(t.count)&&Number.isFinite(t.limit))try{pe.track(CONFIG.ANALYTICS_EVENTS.LIMIT_HIT,{feature:e,count:t.count,limit:t.limit,correlationId:o})}catch{}try{if(u&&u.querySelector("#upgrade-modal"))return}catch{}const r=Number.isFinite(t?.count)?t.count:0,i={folders:CONFIG.FREE_LIMITS?.folders??2,customPrompts:CONFIG.FREE_LIMITS?.customPrompts??2,pinnedMessages:CONFIG.FREE_LIMITS?.pinnedMessages??2,promptChains:CONFIG.FREE_LIMITS?.promptChains??1},a=typeof t?.limit=="number"&&e==="folders"?t.limit:i.folders,d=typeof t?.limit=="number"&&e==="customPrompts"?t.limit:i.customPrompts,p=typeof t?.limit=="number"&&e==="pinnedMessages"?t.limit:i.pinnedMessages,s=typeof t?.limit=="number"&&e==="promptChains"?t.limit:i.promptChains;try{const k=e==="folders"?a:e==="customPrompts"?d:e==="pinnedMessages"?p:e==="promptChains"?s:Number.isFinite(t?.limit)?t.limit:0;pe.track(CONFIG.ANALYTICS_EVENTS.PAYWALL_SHOWN,{feature:e,currentUsage:r,limit:k,correlationId:o})}catch{}const g={folders:`You've used ${r}/${a} folders. Upgrade for unlimited.`,customPrompts:`You've used ${r}/${d} custom prompts. Upgrade for unlimited.`,bulkDelete:"Bulk Delete lets you select and remove multiple conversations at once \u2014 perfect for quickly cleaning up your chat history.",subfolders:"Subfolders are a Premium feature. Upgrade to organize your chats with nested folders.",enhancePrompt:`You've used ${r}/${CONFIG.FREE_LIMITS?.dailyEnhancePrompts||3} daily enhancements. Upgrade for unlimited.`,pinnedMessages:`You've pinned ${r}/${p} messages. Upgrade for unlimited.`,promptChains:`You've created ${r}/${s} prompt chain. Upgrade for unlimited.`},c=typeof CONFIG<"u"&&CONFIG.FREE_LIMITS?CONFIG.FREE_LIMITS:{folders:2,customPrompts:2},b=[{key:"folders",label:"Folders",free:`${c.folders}`,premium:"Unlimited"},{key:"customPrompts",label:"Custom prompts",free:`${c.customPrompts}`,premium:"Unlimited"},{key:"pinnedMessages",label:"Pinned messages",free:`${c.pinnedMessages||2}`,premium:"Unlimited"},{key:"promptChains",label:"Prompt chains",free:`${c.promptChains||1}`,premium:"Unlimited"},{key:"enhancePrompt",label:"AI Prompt Enhancement",free:`${c.dailyEnhancePrompts||3} per day`,premium:"Unlimited daily"},{key:"bulkDelete",label:"Bulk delete chats",free:"Not available",premium:"\u2713 Included"}],C=["folders","customPrompts","bulkDelete","enhancePrompt","pinnedMessages","promptChains"].includes(e)?e:null,T=b.slice().sort((k,O)=>k.key===C&&O.key!==C?-1:O.key===C&&k.key!==C?1:0),q=!!(CONFIG?.PREMIUM?.INCLUDES_FUTURE_FEATURES||CONFIG?.PRICING?.INCLUDES_FUTURE_FEATURES||CONFIG?.BILLING?.INCLUDES_FUTURE_FEATURES),l=q?"All future features included*":"Early access to new features",y=T.map(k=>{const O=k.key===C;let H=k.label,R="";return k.key==="folders"?t&&typeof t.count<"u"&&typeof t.limit<"u"&&t.count>=t.limit?(H="Folders \u2014 Limit reached",R="(Premium: Unlimited)"):R=`(Free: ${k.free} \u2192 Premium: ${k.premium})`:k.key==="customPrompts"?R=`(Free: ${k.free} \u2192 Premium: ${k.premium})`:k.key==="pinnedMessages"?t&&e==="pinnedMessages"&&typeof t.count<"u"&&typeof t.limit<"u"&&t.count>=t.limit?(H="Pinned messages \u2014 Limit reached",R="(Premium: Unlimited)"):R=`(Free: ${k.free} \u2192 Premium: ${k.premium})`:k.key==="promptChains"?t&&e==="promptChains"&&typeof t.count<"u"&&typeof t.limit<"u"&&t.count>=t.limit?(H="Prompt chains \u2014 Limit reached",R="(Premium: Unlimited)"):R=`(Free: ${k.free} \u2192 Premium: ${k.premium})`:k.key==="enhancePrompt"?R=`(Free: ${k.free} \u2192 Premium: ${k.premium})`:k.key==="bulkDelete"?(H="Bulk delete conversations",R="(Select & delete multiple chats at once)"):k.key==="prioritySupport"?(H="Priority support",R="(Skip the line)"):k.key==="export"?(H="Export chats (PDF)",R="(Included in Free)"):k.key==="futureFeatures"&&(H=k.label,R=""),`
                <div style="display: flex; align-items: center; gap: 8px; padding: 6px; border-radius: 6px; ${O?"background: rgba(138, 180, 248, 0.08); outline: 1px solid var(--gf-border-color);":""}">
                    <svg width="14" height="14" fill="var(--gf-accent-success)" viewBox="0 0 20 20" style="flex-shrink: 0;" aria-hidden="true">
                        <path fill-rule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z"></path>
                    </svg>
                    <div style="min-width: 0;">
                        <span style="font-size: 12px; color: var(--gf-text-primary); font-weight: 500;">${H}</span>
                        ${R?`<span style="font-size: 12px; color: var(--gf-text-secondary);"> ${R}</span>`:""}
                    </div>
                </div>
            `}).join(""),m=parseFloat((CONFIG?.PRICING?.monthly?.price||"$0").replace("$","")),h=parseFloat((CONFIG?.PRICING?.yearly?.price||"$0").replace("$","")),x=m*12,f=h,S=Math.round((x-f)/x*100),P=(f/365).toFixed(2),E=`
            <div style="padding: 16px;">
                <!-- Limit Reached Notice -->
                <div style="background: var(--gf-bg-secondary); border: 1px solid var(--gf-border-color); border-radius: 6px; padding: 8px; margin-bottom: 12px; text-align: center;">
                    <p style="font-size: 13px; color: var(--gf-text-primary); margin: 0; font-weight: 500;">
                        ${g[e]||"You've reached a free tier limit"}
                    </p>
                </div>

                <!-- Title -->
                <div style="text-align: center; margin-bottom: 10px;">
                    <h3 style="font-size: 18px; margin-bottom: 2px; color: var(--gf-text-primary); font-weight: 600;">Upgrade to Premium</h3>
                    <p style="font-size: 12px; color: var(--gf-text-secondary); margin: 0;">Remove all limits and unlock advanced features</p>
                </div>

                <!-- Premium Features -->
                <div style="background: var(--gf-bg-secondary); border-radius: 6px; padding: 8px; margin-bottom: 8px; border: 1px solid var(--gf-border-color);">
                    <div style="display: grid; grid-template-columns: 1fr 1fr; gap: 6px;">
                        ${y}
                    </div>
                </div>

                <!-- Pricing Options -->
                <div style="display: flex; gap: 10px; margin-bottom: 12px; padding-top: 8px;">
                    <div style="flex: 1; position: relative;">
                        ${S>0?`<div style="position: absolute; top: -8px; left: 50%; transform: translateX(-50%); background: var(--gf-accent-danger); color: white; padding: 2px 10px; border-radius: 10px; font-size: 9px; font-weight: 600; text-transform: uppercase; white-space: nowrap; z-index: 10;">Save ${S}%</div>`:""}
<button id="upgrade-yearly-btn" class="button primary" aria-label="Choose annual plan \u2014 ${CONFIG?.PRICING?.yearly?.price||"$0"} per year, billed annually" style="width: 100%; min-height: 80px; padding: 12px; border: none; display: flex; flex-direction: column; align-items: center; justify-content: center; cursor: pointer; transition: all 0.2s;">
                            <div style="font-size: 10px; text-transform: uppercase; opacity: 0.9; letter-spacing: 0.3px;">Best Value</div>
<div style="font-size: 20px; font-weight: 700; line-height: 1.2;">${CONFIG?.PRICING?.yearly?.display||(CONFIG?.PRICING?.yearly?.price||"$0")+"/year"}</div>
                            <div style="font-size: 11px; opacity: 0.9;">Billed annually \u2022 \u2248 $${(f/12).toFixed(2)}/mo</div>
<div style="background: rgba(255, 255, 255, 0.2); padding: 4px 12px; border-radius: 4px; font-size: 11px; font-weight: 600; text-transform: uppercase; letter-spacing: 0.3px; margin-top: 4px; white-space: normal;">Choose Annual \u2014 ${CONFIG?.PRICING?.yearly?.display||(CONFIG?.PRICING?.yearly?.price||"$0")+"/year"}</div>
                        </button>
                    </div>

                    <div style="flex: 1; position: relative;">
<button id="upgrade-monthly-btn" class="button secondary" aria-label="Choose monthly plan \u2014 ${CONFIG?.PRICING?.monthly?.price||"$0"} per month, billed monthly" style="width: 100%; min-height: 80px; padding: 12px; border: 1px solid var(--gf-border-color); display: flex; flex-direction: column; align-items: center; justify-content: center; cursor: pointer; transition: all 0.2s;">
                            <div style="font-size: 10px; text-transform: uppercase; opacity: 0.7; letter-spacing: 0.3px;">Monthly</div>
<div style="font-size: 20px; font-weight: 700; color: var(--gf-text-primary); line-height: 1.2;">${CONFIG?.PRICING?.monthly?.display||(CONFIG?.PRICING?.monthly?.price||"$0")+"/mo"}</div>
                            <div style="font-size: 11px; opacity: 0.7;">Billed monthly</div>
<div style="background: var(--gf-bg-primary); border: 1px solid var(--gf-border-color); padding: 4px 12px; border-radius: 4px; font-size: 11px; font-weight: 600; text-transform: uppercase; letter-spacing: 0.3px; color: var(--gf-text-primary); margin-top: 4px; white-space: normal;">Choose Monthly \u2014 ${CONFIG?.PRICING?.monthly?.display||(CONFIG?.PRICING?.monthly?.price||"$0")+"/mo"}</div>
                        </button>
                    </div>
                </div>

                <!-- Trust & Legal -->
                <div style="text-align: center; margin-bottom: 10px; padding: 8px 0; border-top: 1px solid var(--gf-border-color);">
                    <p style="font-size: 11px; color: var(--gf-text-secondary); margin: 0 0 6px 0;">Secure checkout via Lemon Squeezy \u2022 30-day money-back \u2022 Cancel anytime</p>
                    <div style="display: flex; justify-content: center; gap: 6px; opacity: 0.6; align-items: center;" aria-label="Accepted payment methods">
                        <svg width="28" height="16" viewBox="0 0 32 20" fill="var(--gf-text-secondary)" role="img" aria-label="Visa"><title>Visa</title><rect width="32" height="20" rx="2" fill="white" opacity="0.1"/><text x="16" y="13" font-size="7" text-anchor="middle" fill="currentColor">VISA</text></svg>
                        <svg width="28" height="16" viewBox="0 0 32 20" fill="var(--gf-text-secondary)" role="img" aria-label="Mastercard"><title>Mastercard</title><rect width="32" height="20" rx="2" fill="white" opacity="0.1"/><circle cx="12" cy="10" r="4" fill="currentColor" opacity="0.5"/><circle cx="20" cy="10" r="4" fill="currentColor" opacity="0.3"/></svg>
                        <svg width="28" height="16" viewBox="0 0 32 20" fill="var(--gf-text-secondary)" role="img" aria-label="American Express"><title>American Express</title><rect width="32" height="20" rx="2" fill="white" opacity="0.1"/><text x="16" y="13" font-size="7" text-anchor="middle" fill="currentColor">AMEX</text></svg>
                        <svg width="28" height="16" viewBox="0 0 32 20" fill="var(--gf-text-secondary)" role="img" aria-label="PayPal"><title>PayPal</title><rect width="32" height="20" rx="2" fill="white" opacity="0.1"/><text x="16" y="13" font-size="7" text-anchor="middle" fill="currentColor">PayPal</text></svg>
                    </div>
                    ${CONFIG?.LEGAL_URLS?.terms||CONFIG?.LEGAL_URLS?.privacy||CONFIG?.LEGAL_URLS?.refund?`
                    <div style="margin-top: 6px; font-size: 11px;">
                        ${CONFIG?.LEGAL_URLS?.terms?`<a href="${CONFIG.LEGAL_URLS.terms}" target="_blank" rel="noopener noreferrer" style="color: var(--gf-text-secondary); text-decoration: underline; margin: 0 6px;">Terms</a>`:""}
                        ${CONFIG?.LEGAL_URLS?.privacy?`<a href="${CONFIG.LEGAL_URLS.privacy}" target="_blank" rel="noopener noreferrer" style="color: var(--gf-text-secondary); text-decoration: underline; margin: 0 6px;">Privacy</a>`:""}
                        ${CONFIG?.LEGAL_URLS?.refund?`<a href="${CONFIG.LEGAL_URLS.refund}" target="_blank" rel="noopener noreferrer" style="color: var(--gf-text-secondary); text-decoration: underline; margin: 0 6px;">Refund Policy</a>`:""}
                    </div>
                    `:""}
                </div>

                ${q?'<div style="font-size: 10px; color: var(--gf-text-secondary); text-align: center; margin: -4px 0 8px 0;">\u201CAll future features\u201D = features released into the Premium plan; excludes third-party services and usage-based fees.</div>':""}

                <button id="cancel-upgrade-btn" class="button secondary" style="width: 100%; padding: 10px; font-size: 13px;">Continue on Free Plan</button>
            </div>
        `;le("upgrade-modal","Upgrade to Premium",E,640),setTimeout(()=>{const k=u.querySelector("#upgrade-monthly-btn"),O=u.querySelector("#upgrade-yearly-btn"),H=u.querySelector("#cancel-upgrade-btn");k&&k.addEventListener("click",async()=>{try{Qe(k,!0);try{pe.track(CONFIG.ANALYTICS_EVENTS.PAYWALL_CTA_CLICK_MONTHLY,{plan:"monthly",feature:e,correlationId:o})}catch{}Q("Opening checkout...","info");const R=Date.now(),ie=window.geminiAPI.startUpgrade("monthly");try{pe.track(CONFIG.ANALYTICS_EVENTS.CHECKOUT_OPENED,{plan:"monthly",correlationId:o})}catch{}setTimeout(()=>{bt()},2e3);const de=await ie;if(xt(),de.success){try{pe.track(CONFIG.ANALYTICS_EVENTS.PREMIUM_ACTIVATION_SUCCESS,{plan:"monthly",activationTimeMs:Math.max(0,Date.now()-R),correlationId:o})}catch{}Q("\u{1F389} Premium activated!","success"),W(),window.location.reload()}else if(de.timeout){try{pe.track(CONFIG.ANALYTICS_EVENTS.PREMIUM_ACTIVATION_TIMEOUT,{plan:"monthly",timeoutMs:Math.max(0,Date.now()-R),correlationId:o})}catch{}Q("Still processing... Premium will activate shortly.","info"),W()}}catch{try{pe.track(CONFIG.ANALYTICS_EVENTS.PREMIUM_ACTIVATION_FAILED,{plan:"monthly",reason:"unknown",correlationId:o})}catch{}Q("Failed to start upgrade. Please try again.","error"),Qe(k,!1)}}),O&&O.addEventListener("click",async()=>{try{Qe(O,!0);try{pe.track(CONFIG.ANALYTICS_EVENTS.PAYWALL_CTA_CLICK_ANNUAL,{plan:"yearly",feature:e,correlationId:o})}catch{}Q("Opening checkout...","info");const R=Date.now(),ie=window.geminiAPI.startUpgrade("yearly");try{pe.track(CONFIG.ANALYTICS_EVENTS.CHECKOUT_OPENED,{plan:"yearly",correlationId:o})}catch{}setTimeout(()=>{bt()},2e3);const de=await ie;if(xt(),de.success){try{pe.track(CONFIG.ANALYTICS_EVENTS.PREMIUM_ACTIVATION_SUCCESS,{plan:"yearly",activationTimeMs:Math.max(0,Date.now()-R),correlationId:o})}catch{}Q("\u{1F389} Premium activated!","success"),W(),window.location.reload()}else if(de.timeout){try{pe.track(CONFIG.ANALYTICS_EVENTS.PREMIUM_ACTIVATION_TIMEOUT,{plan:"yearly",timeoutMs:Math.max(0,Date.now()-R),correlationId:o})}catch{}Q("Still processing... Premium will activate shortly.","info"),W()}}catch{try{pe.track(CONFIG.ANALYTICS_EVENTS.PREMIUM_ACTIVATION_FAILED,{plan:"yearly",reason:"unknown",correlationId:o})}catch{}Q("Failed to start upgrade. Please try again.","error"),Qe(O,!1)}}),H&&H.addEventListener("click",()=>{W()})},100)}async function Bo(){console.log("[Gemini Toolbox] Attempting to open sidebar...");const e=document.querySelector('[data-test-id="side-nav-menu-button"]')||document.querySelector('button[aria-label*="menu" i]')||document.querySelector('button[aria-label*="navigation" i]'),t=document.querySelector("mat-sidenav")||document.querySelector('[role="navigation"]');if(console.log("[Gemini Toolbox] Found menuButton:",!!e),console.log("[Gemini Toolbox] Found sideNav:",!!t),!e){console.warn("[Gemini Toolbox] Menu button not found - cannot open sidebar");return}if(!t){console.warn("[Gemini Toolbox] Sidebar element not found");return}const n=t.classList.contains("mat-drawer-closed"),o=t.getAttribute("aria-hidden")==="true",r=t.offsetWidth>100,i=n||o||!r;console.log("[Gemini Toolbox] Detection details:",{hasClosedClass:n,isHidden:o,hasWidth:r,offsetWidth:t.offsetWidth,isClosed:i}),i?(console.log("[Gemini Toolbox] Sidebar is closed, clicking menu button to open..."),e.click(),await new Promise(a=>setTimeout(a,600)),console.log("[Gemini Toolbox] Sidebar should be open now")):console.log("[Gemini Toolbox] Sidebar is already open, no action needed")}let Ho=!1,an=null,sn=null;async function Oo(){try{await window.geminiAPI.initialize();try{await pe.track(CONFIG.ANALYTICS_EVENTS.APP_INITIALIZED)}catch{}try{const o=(await chrome.storage?.local?.get("gt_last_version"))?.gt_last_version||null,r=CONFIG?.VERSION||null;r&&o!==r&&(o&&await pe.track(CONFIG.ANALYTICS_EVENTS.VERSION_UPDATED,{fromVersion:o,toVersion:r}),await chrome.storage?.local?.set({gt_last_version:r}))}catch{}const e=window.geminiAPI.getUserInfo(),t=await window.geminiAPI.getSubscriptionStatus()}catch{}}async function zt(){if(document.getElementById(Ze))return;await Wt(500),at();try{try{await Oo()}catch{}}catch{}const e=document.querySelector("conversations-list");if(e&&!document.getElementById(Ze)){let s=function(){if(o.classList.contains("show"))try{const l=n.getBoundingClientRect();o.style.position="fixed",o.style.right="auto",o.style.visibility="hidden",o.style.opacity="0",o.style.transform="none";const y=Math.max(220,Math.ceil(l.width));o.style.minWidth=y+"px";const m=o.getBoundingClientRect(),h=Math.max(y,Math.ceil(m.width||y)),x=Math.ceil(m.height||240),f=Math.max(8,Math.min(window.innerWidth-h-8,Math.floor(l.left)));o.style.left=f+"px";let S=Math.floor(l.bottom)+8;S+x>window.innerHeight-8&&(S=Math.max(8,Math.floor(l.top)-x-8)),o.style.top=S+"px",o.style.visibility="",o.style.opacity="",o.style.transform=""}catch{}},g=function(){let l=!1;const y=()=>{l||(l=!0,requestAnimationFrame(()=>{l=!1,s()}))};o._repositionHandler=y,window.addEventListener("resize",y,{passive:!0}),window.addEventListener("scroll",y,{passive:!0,capture:!0})},c=function(){o.style.position="",o.style.top="",o.style.left="",o.style.right="",o.style.minWidth="",o._repositionHandler&&(window.removeEventListener("resize",o._repositionHandler),window.removeEventListener("scroll",o._repositionHandler,{capture:!0}),delete o._repositionHandler)},b=function(){try{o.classList.remove("show"),p.classList.remove("rotated"),n.setAttribute("aria-expanded","false"),c();try{n.blur&&n.blur()}catch{}}catch{}},C=function(){try{const l=u&&u.activeElement?u.activeElement:null;if(l&&l===n){const y=n.getAttribute("tabindex");n.setAttribute("tabindex","-1");try{n.blur&&n.blur()}catch{}setTimeout(()=>{y!==null?n.setAttribute("tabindex",y):n.removeAttribute("tabindex")},0)}}catch{}};z=document.createElement("div"),z.id=Ze,u=z.attachShadow({mode:"open"}),Qt();const t=to();u.innerHTML+=t,e.prepend(z),Fo();const n=u.getElementById("gemini-toolbox-btn"),o=u.getElementById("gemini-toolbox-dropdown"),r=u.getElementById("manage-folders-link"),i=u.getElementById("chat-tools-link"),a=u.getElementById("prompt-library-link"),d=u.getElementById("settings-link"),p=u.querySelector(".dropdown-arrow");n.addEventListener("click",l=>{l.stopPropagation();const y=o.classList.contains("show");o.classList.toggle("show",!y),p.classList.toggle("rotated",!y),n.setAttribute("aria-expanded",!y),y?c():(requestAnimationFrame(()=>s()),g(),setTimeout(()=>{const m=o.querySelector('.dropdown-item[role="menuitem"]');m&&m.focus()},50))}),n.addEventListener("keydown",l=>{(l.key==="Enter"||l.key===" ")&&(l.preventDefault(),n.click())});let T=0;document.addEventListener("keydown",l=>{if(l.target.tagName==="INPUT"||l.target.tagName==="TEXTAREA"||l.target.isContentEditable)return;try{const h=!!(u&&u.querySelector(".infi-chatgpt-modal")),x=document.querySelector(".cdk-overlay-container"),f=!!(x&&x.children&&x.children.length>0),S=!!document.querySelector('[aria-modal="true"], [role="dialog"]');if(h||f||S)return}catch{}const y=Date.now(),m=y-T;if(l.key.toLowerCase()==="g"&&!l.ctrlKey&&!l.metaKey&&!l.altKey)T=y;else if(m<500&&!l.ctrlKey&&!l.metaKey&&!l.altKey){let h=null;switch(l.key.toLowerCase()){case"f":l.preventDefault(),C(),St(),h="manage_folders";break;case"m":l.preventDefault(),C(),je("pinned"),h="chat_tools";break;case"d":l.preventDefault(),C(),je("bulk-delete"),h="chat_tools_bulk_delete";break;case"e":l.preventDefault(),C(),je("export"),h="chat_tools_export";break;case"p":l.preventDefault(),C(),a.click(),h="prompt_library";break;case"s":l.preventDefault(),C(),d.click(),h="settings";break}h&&window.geminiAPI&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent("keyboard_shortcut_used",{shortcut:`g+${l.key.toLowerCase()}`,feature:h}),T=0}}),r.addEventListener("click",l=>{l.stopPropagation(),b(),St()}),i.addEventListener("click",l=>{l.stopPropagation(),b(),je("pinned")}),a.addEventListener("click",async l=>{l.stopPropagation(),b();try{if(typeof PromptLibrary>"u"&&typeof window.PromptLibrary>"u")throw new Error("PromptLibrary class not found. The extension may not have loaded properly. Please refresh the page.");if(await qo(),!u.getElementById("prompt-library-modal"))throw new Error("Prompt library HTML failed to load. Please refresh the page.");if(!Je){const y=typeof PromptLibrary<"u"?PromptLibrary:window.PromptLibrary;Je=new y(u),Je.initializeEventListeners()}Je.show()}catch(y){X(`Failed to open Prompt Library: ${y.message}`)}}),d.addEventListener("click",l=>{l.stopPropagation(),b(),Eo()}),o.addEventListener("mousedown",l=>{const y=l.target&&l.target.closest?l.target.closest('.dropdown-item[role="menuitem"]'):null;if(y&&y.focus)try{y.focus({preventScroll:!0})}catch{}});const q=o.querySelectorAll('.dropdown-item[role="menuitem"]');q.forEach((l,y)=>{l.addEventListener("keydown",m=>{switch(m.key){case"ArrowDown":m.preventDefault();const h=(y+1)%q.length;q[h].focus();break;case"ArrowUp":m.preventDefault();const x=(y-1+q.length)%q.length;q[x].focus();break;case"Enter":case" ":m.preventDefault(),C(),l.click();break;case"Escape":m.preventDefault(),o.classList.remove("show"),p.classList.remove("rotated"),n.setAttribute("aria-expanded","false"),c(),n.focus();break;case"Tab":o.classList.remove("show"),p.classList.remove("rotated"),n.setAttribute("aria-expanded","false"),c();break}})}),u.addEventListener("click",l=>{o.contains(l.target)||n.contains(l.target)||u.querySelector(".infi-chatgpt-modal")||l.target.closest(".infi-chatgpt-modal")||(o.classList.remove("show"),p.classList.remove("rotated"),c())}),document.addEventListener("click",l=>{const y=u.host;if(y&&!y.contains(l.target)){if(u.querySelector(".infi-chatgpt-modal"))return;o.classList.remove("show"),p.classList.remove("rotated"),c()}}),await vt(),w.settings.hideFolderedChats&&De(),Nt(),_t(),$t(),window.addEventListener("message",async l=>{if(!(l.source!==window||!l.data||l.data.from!=="GeminiToolbox")&&l.data.type==="enhancePromptRequest"&&l.data.prompt){const y=l.data.id;try{const m=await fetch(`${CONFIG.API_URL}/api/prompt/enhance`,{method:"POST",headers:{"Content-Type":"application/json","X-From":"GeminiToolbox"},body:JSON.stringify({prompt:l.data.prompt})});if(!m.ok){const x=await m.text().catch(()=>"");throw new Error(`API error ${m.status}: ${x}`)}const h=await m.json();window.postMessage({type:"enhancePromptResponse",id:y,success:!0,data:h},"*")}catch(m){window.postMessage({type:"enhancePromptResponse",id:y,success:!1,error:m.message||"Failed to enhance prompt"},"*")}}});try{const l=await window.geminiAPI.getSubscriptionStatus();tt(!!l?.isPremium),$o()}catch{tt(!1)}window.showUpgradeModal=Ye,window.ensureSidebarOpen=Bo,window.addEventListener("showUpgradeModal",l=>{l.detail&&l.detail.feature&&l.detail.limitInfo&&Ye(l.detail.feature,l.detail.limitInfo)})}}let We=null,Ke=null;We=new MutationObserver(e=>{for(const t of e)t.type==="childList"&&document.querySelector("conversations-list")&&!document.getElementById(Ze)&&zt(),Me()!==Pe&&Ve()}),We.observe(document.body,{childList:!0,subtree:!0,attributes:!0,attributeFilter:["class"]}),Ke=new MutationObserver(()=>{Me()!==Pe&&Ve()}),Ke.observe(document.documentElement,{attributes:!0,attributeFilter:["data-theme","class"]});function ut(){We&&(We.disconnect(),We=null),Ke&&(Ke.disconnect(),Ke=null),window.wordCounterInstance&&typeof window.wordCounterInstance.destroy=="function"&&window.wordCounterInstance.destroy(),window.EnhancePromptModule&&typeof window.EnhancePromptModule.destroy=="function"&&window.EnhancePromptModule.destroy()}window.addEventListener("beforeunload",ut),window.addEventListener("pagehide",ut),chrome.runtime&&chrome.runtime.onSuspend&&chrome.runtime.onSuspend.addListener(ut),setInterval(()=>{Me()!==Pe&&Ve()},3e3),window.addEventListener("error",e=>{e.error&&e.error.message&&(e.error.message.includes("Extension context invalidated")||e.error.message.includes("Cannot access a chrome:// URL"))&&(window._geminiToolboxInvalidatedErrorShown||(window._geminiToolboxInvalidatedErrorShown=!0,X("Extension was updated. Please refresh the page to continue using Gemini Toolbox.")),e.preventDefault())}),zt();function Go(e,t=50,n=20){let o=0;const r=setInterval(()=>{o++,(document.querySelector('rich-textarea, .ql-editor[contenteditable="true"], [contenteditable="true"][role="textbox"]')||o>=n)&&(clearInterval(r),e())},t)}chrome.runtime.onMessage.addListener((e,t,n)=>{if(e.action==="insertText"){const o=e.text,r=document.querySelector('button[aria-label="New chat"]');return r?(r.click(),Go(()=>{Bt(o)},50,20)):Bt(o),n({success:!0}),!0}});function Bt(e){const t=document.querySelector('rich-textarea[placeholder*="Enter"], rich-textarea, .ql-editor[contenteditable="true"], [contenteditable="true"][role="textbox"], textarea[placeholder*="Enter"]');if(t&&console.log("[Context Menu] Found input element:",t.tagName),!t){console.error("[Context Menu] Could not find input element"),typeof X=="function"?X("Could not find Gemini input field"):window.showToast&&window.showToast("Could not find Gemini input field","error");return}try{if(t.tagName==="RICH-TEXTAREA"){const n=t.querySelector('.ql-editor[contenteditable="true"]');if(n){console.log("[Context Menu] Found editable div inside rich-textarea"),n.textContent=e,n.focus(),n.dispatchEvent(new Event("input",{bubbles:!0})),n.dispatchEvent(new Event("change",{bubbles:!0}));const o=document.createRange(),r=window.getSelection();o.selectNodeContents(n),o.collapse(!1),r.removeAllRanges(),r.addRange(o)}else console.log("[Context Menu] Setting value on rich-textarea"),t.value=e,t.dispatchEvent(new Event("input",{bubbles:!0})),t.focus()}else if(t.isContentEditable||t.contentEditable==="true"){console.log("[Context Menu] Setting textContent on contenteditable"),t.textContent=e,t.focus(),t.dispatchEvent(new Event("input",{bubbles:!0})),t.dispatchEvent(new Event("change",{bubbles:!0}));const n=document.createRange(),o=window.getSelection();n.selectNodeContents(t),n.collapse(!1),o.removeAllRanges(),o.addRange(n)}else(t.tagName==="TEXTAREA"||t.tagName==="INPUT")&&(console.log("[Context Menu] Setting value on input/textarea"),t.value=e,t.focus(),t.dispatchEvent(new Event("input",{bubbles:!0})),t.dispatchEvent(new Event("change",{bubbles:!0})));console.log("[Context Menu] Text inserted successfully"),window.geminiAPI&&window.geminiAPI.trackEvent&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.CONTEXT_MENU_USED,{textLength:e.length,source:"context_menu"}),typeof showSuccess=="function"?showSuccess("Text sent to Gemini!"):window.showToast&&window.showToast("Text sent to Gemini!","success")}catch(n){console.error("[Context Menu] Error inserting text:",n),typeof X=="function"?X("Failed to insert text"):window.showToast&&window.showToast("Failed to insert text","error")}}})();
