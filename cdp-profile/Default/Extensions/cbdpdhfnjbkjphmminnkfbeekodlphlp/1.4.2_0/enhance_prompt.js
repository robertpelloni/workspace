(function(){"use strict";let h=!1,C=null,c=null,l=0,m=null,d=!1,p=null;function L(e,t={}){h||(C=e,d=t.isPremium||!1,S(),A(),G(),h=!0,CONFIG.DEBUG&&console.log("[Enhance Prompt] Module initialized",{isPremium:d}))}function S(){const e=localStorage.getItem(CONFIG.STORAGE_KEYS.ENHANCE_PROMPT_USAGE);if(e)try{const t=JSON.parse(e),n=new Date().toDateString();t.date===n?(l=t.count||0,m=t.date):(l=0,m=n,y())}catch{l=0,m=new Date().toDateString()}}function y(){const e={date:m||new Date().toDateString(),count:l};localStorage.setItem(CONFIG.STORAGE_KEYS.ENHANCE_PROMPT_USAGE,JSON.stringify(e))}function w(){if(d)return!0;const e=CONFIG.FREE_LIMITS.dailyEnhancePrompts;return e===-1?!0:l<e}function T(){if(d)return-1;const e=CONFIG.FREE_LIMITS.dailyEnhancePrompts;return e===-1?-1:Math.max(0,e-l)}function A(){if(document.querySelector("#enhance-prompt-styles"))return;const t=document.createElement("style");t.id="enhance-prompt-styles",t.textContent=`
            /* Native Gemini button style - Pill shape with text */
            .gt-enhance-button {
                /* Match Gemini's Material Design button */
                position: relative;
                box-sizing: border-box;
                border: none;
                outline: none;
                background-color: transparent;
                fill: currentColor;
                color: inherit;
                text-decoration: none;
                cursor: pointer;
                user-select: none;
                z-index: 0;
                overflow: visible;
                
                /* Pill shape with icon and text */
                width: auto;
                height: 32px;
                padding: 0 12px 0 8px;
                display: inline-flex;
                align-items: center;
                align-self: center;
                justify-content: center;
                gap: 4px;
                flex-shrink: 0;
                font-size: 14px;
                font-family: 'Google Sans Text', 'Roboto', sans-serif;
                font-weight: 500;
                border-radius: 16px;
                margin: 4px 4px 0 4px;
                
                /* Color matching Gemini's style */
                color: #5f6368;
                border: 1px solid #dadce0;
                
                /* Transition for hover effects */
                transition: all 150ms cubic-bezier(0.4, 0, 0.2, 1);
            }
            
            /* Ripple effect container */
            .gt-enhance-button .mat-mdc-button-persistent-ripple {
                position: absolute;
                top: 0;
                left: 0;
                right: 0;
                bottom: 0;
                pointer-events: none;
                border-radius: inherit;
            }
            
            .gt-enhance-button:hover:not(:disabled) {
                /* Match Gemini's hover state */
                background-color: rgba(60, 64, 67, 0.04);
                border-color: #5f6368;
            }
            
            .gt-enhance-button:focus:not(:disabled) {
                background-color: rgba(60, 64, 67, 0.08);
                border-color: #5f6368;
            }
            
            .gt-enhance-button:active:not(:disabled) {
                background-color: rgba(60, 64, 67, 0.12);
                transform: scale(0.98);
            }
            
            .gt-enhance-button:disabled {
                opacity: 0.5;
                cursor: not-allowed;
            }
            
            .gt-enhance-button.loading {
                cursor: wait;
                opacity: 0.7;
            }
            
            .gt-enhance-button.loading .enhance-icon {
                animation: gt-spin 1s linear infinite;
            }
            
            @keyframes gt-spin {
                0% { transform: rotate(0deg); }
                100% { transform: rotate(360deg); }
            }
            
            @keyframes gt-pulse {
                0%, 100% { opacity: 1; }
                50% { opacity: 0.6; }
            }
            
            @keyframes slideUp {
                from {
                    transform: translateX(-50%) translateY(100%);
                    opacity: 0;
                }
                to {
                    transform: translateX(-50%) translateY(0);
                    opacity: 1;
                }
            }
            
            @keyframes slideDown {
                from {
                    transform: translateX(-50%) translateY(0);
                    opacity: 1;
                }
                to {
                    transform: translateX(-50%) translateY(100%);
                    opacity: 0;
                }
            }
            
            /* Icon styling to match Material Icons */
            .gt-enhance-button .enhance-icon {
                width: 18px;
                height: 18px;
                pointer-events: none;
                display: block;
                flex-shrink: 0;
            }
            
            .gt-enhance-button .enhance-label {
                white-space: nowrap;
                pointer-events: none;
                line-height: 1;
            }
            
            /* Dark mode adjustments */
            .dark-theme .gt-enhance-button,
            [data-theme="dark"] .gt-enhance-button {
                color: #e8eaed;
                border-color: #5f6368;
            }
            
            .dark-theme .gt-enhance-button:hover:not(:disabled),
            [data-theme="dark"] .gt-enhance-button:hover:not(:disabled) {
                background-color: rgba(232, 234, 237, 0.04);
                border-color: #e8eaed;
            }
            
            .dark-theme .gt-enhance-button:focus:not(:disabled),
            [data-theme="dark"] .gt-enhance-button:focus:not(:disabled) {
                background-color: rgba(232, 234, 237, 0.08);
                border-color: #e8eaed;
            }
            
            .dark-theme .gt-enhance-button:active:not(:disabled),
            [data-theme="dark"] .gt-enhance-button:active:not(:disabled) {
                background-color: rgba(232, 234, 237, 0.12);
            }
            
            .dark-theme .gt-enhance-button .enhance-label,
            [data-theme="dark"] .gt-enhance-button .enhance-label {
                color: #e8eaed;
            }
        `,document.head.appendChild(t)}function f(){const e=[".ql-editor.textarea",".ql-editor.textarea.new-input-ui","rich-textarea .ql-editor",'.ql-editor[contenteditable="true"]','div[contenteditable="true"][role="textbox"]',".input-area .ql-editor",".text-input-field .ql-editor",".input-wrapper .ql-editor",'[contenteditable="true"].ql-editor'];for(const n of e){const o=document.querySelector(n);if(o&&o.isContentEditable){const a=o.getBoundingClientRect();if(a.width>0&&a.height>0)return o}}const t=document.querySelectorAll('[contenteditable="true"]');for(const n of t){const o=n.getBoundingClientRect();if(o.width>100&&o.height>20&&n.classList.contains("ql-editor"))return n}return null}function I(){const e=document.createElement("button");return e.className="gt-enhance-button",e.title="Enhance prompt with AI (Ctrl+Shift+P)",e.setAttribute("aria-label","Enhance prompt with AI"),e.innerHTML=`
            <svg class="enhance-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <path d="M12 2L14.5 9.5L22 12L14.5 14.5L12 22L9.5 14.5L2 12L9.5 9.5L12 2z"/>
            </svg>
            <span class="enhance-label">Enhance</span>
        `,e.addEventListener("click",async t=>{t.preventDefault(),t.stopPropagation();const n=f();if(!n){u("Unable to find text editor. Please try again.","error");return}await M(n,e)}),e}function x(e){if(!e||c&&document.body.contains(c))return;const t=I();c=t;const n=e.closest(".text-input-field, .input-wrapper, .textarea-wrapper"),o=n?n.querySelector(".leading-actions-wrapper, .input-actions"):null;if(o)o.insertBefore(t,o.firstChild);else if(n)n.insertBefore(t,e);else{const a=e.parentElement;a&&a.insertBefore(t,e)}}async function M(e,t){try{if(!e||!e.isContentEditable){console.error("[Enhance Prompt] Editor not found or not editable"),u("Unable to access text editor. Please refresh and try again.","error");return}if(!w()){window.showUpgradeModal?window.showUpgradeModal("enhancePrompt",{count:l,limit:CONFIG.FREE_LIMITS.dailyEnhancePrompts}):u("Daily limit reached. Upgrade to Premium for unlimited enhancements!","warning");return}let n="";if(n=(e.textContent||"").trim(),n||(n=(e.innerText||"").trim()),!n){const a=e.querySelectorAll("p");n=Array.from(a).map(i=>i.textContent||"").filter(i=>i.trim()).join(`
`).trim()}if(!n){u("Please enter some text to enhance","info");return}t.classList.add("loading"),t.disabled=!0,b("enhance_prompt_started",{textLength:n.length,isPremium:d});const o=await N(n);if(o&&o.improvedPrompt)g(e,o.improvedPrompt,n),d||(l++,y()),b(CONFIG.ANALYTICS_EVENTS.ENHANCE_PROMPT_USED,{textLength:n.length,improvedLength:o.improvedPrompt.length,isPremium:d,dailyUsage:l}),R("Prompt enhanced successfully!",n,e);else throw new Error(o?.error||"No improved prompt returned")}catch(n){console.error("[Enhance Prompt] Error:",n),b(CONFIG.ANALYTICS_EVENTS.ENHANCE_PROMPT_ERROR,{error:n.message,isPremium:d}),u("Failed to enhance prompt. Please try again.","error")}finally{t.classList.remove("loading"),t.disabled=!1}}async function N(e){return new Promise((t,n)=>{const o="enhance-"+Date.now()+"-"+Math.random(),a=r=>{r.data&&r.data.type==="enhancePromptResponse"&&r.data.id===o&&(window.removeEventListener("message",a),r.data.success?t(r.data.data):n(new Error(r.data.error||"API call failed")))};window.addEventListener("message",a),window.postMessage({type:"enhancePromptRequest",id:o,prompt:e,from:"GeminiToolbox"},"*"),setTimeout(()=>{window.removeEventListener("message",a),n(new Error("Request timeout"))},3e4)})}function g(e,t,n){e.dataset.originalPrompt=n;const a=t.trim().split(`
`).filter(r=>r.trim()).map(r=>`<p>${r.trim()}</p>`).join("");e.innerHTML=a;try{e.classList.remove("ql-blank")}catch{}try{e.dispatchEvent(new Event("input",{bubbles:!0,cancelable:!0})),e.dispatchEvent(new Event("change",{bubbles:!0,cancelable:!0})),e.dispatchEvent(new KeyboardEvent("keyup",{bubbles:!0,cancelable:!0})),e.focus();const r=document.createRange(),i=window.getSelection();r.selectNodeContents(e),r.collapse(!1),i.removeAllRanges(),i.addRange(r)}catch(r){console.error("[Enhance Prompt] Error dispatching events:",r)}}function u(e,t="info"){if(window.showToast){window.showToast(e,t);return}const n=document.getElementById("gt-fallback-toast-container");if(n){const o=document.documentElement.classList.contains("dark")||document.body.classList.contains("dark-theme")||document.body.classList.contains("dark")||window.matchMedia("(prefers-color-scheme: dark)").matches,a=document.createElement("div");a.className=`prompt-toast ${t}`,a.textContent=e,a.style.cssText=`
                position: fixed;
                bottom: 32px;
                left: 50%;
                transform: translateX(-50%) translateY(100px);
                background: ${o?"#131314":"#ffffff"};
                color: ${t==="error"?o?"#f28b82":"#d33333":o?"#e3e3e3":"#3c4043"};
                padding: 14px 20px;
                border-radius: 24px;
                box-shadow: ${o?"0 4px 12px rgba(0,0,0,0.4), 0 0 0 1px rgba(255,255,255,0.08)":"0 1px 3px rgba(60,64,67,0.3), 0 1px 2px rgba(60,64,67,0.15)"};
                z-index: 2147483647;
                opacity: 0;
                transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
                font-family: 'Google Sans', -apple-system, BlinkMacSystemFont, sans-serif;
                font-size: 14px;
                font-weight: 400;
                line-height: 20px;
                max-width: 90vw;
                min-width: 200px;
                display: inline-flex;
                align-items: center;
                gap: 12px;
            `,n.appendChild(a),requestAnimationFrame(()=>{a.style.opacity="1",a.style.transform="translateX(-50%) translateY(0)"}),setTimeout(()=>{a.style.opacity="0",a.style.transform="translateX(-50%) translateY(100px)",setTimeout(()=>a.remove(),300)},3e3)}else console.warn("[Enhance Prompt] Toast container not found, using console instead"),console.log(`[${t.toUpperCase()}] ${e}`)}function R(e,t,n){if(window.showToastWithAction){window.showToastWithAction(e,"Undo",()=>{g(n,t,""),window.showToastWithAction?window.showToast("Reverted to original prompt","info"):u("Reverted to original prompt","info")},"success");return}const a=document.getElementById("gt-fallback-toast-container")||document.body,r=document.documentElement.classList.contains("dark")||document.body.classList.contains("dark-theme")||document.body.classList.contains("dark")||window.matchMedia("(prefers-color-scheme: dark)").matches,i=document.createElement("div");i.className="prompt-toast success",i.style.cssText=`
            position: fixed; bottom: 32px; left: 50%; transform: translateX(-50%) translateY(100px);
            background: ${r?"#131314":"#ffffff"}; color: ${r?"#e3e3e3":"#3c4043"}; 
            padding: 14px 20px; border-radius: 24px;
            display: inline-flex; align-items: center; gap: 12px; z-index: 2147483647;
            opacity: 0; transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1); max-width: 90vw; min-width: 200px;
            box-shadow: ${r?"0 4px 12px rgba(0,0,0,0.4), 0 0 0 1px rgba(255,255,255,0.08)":"0 1px 3px rgba(60,64,67,0.3), 0 1px 2px rgba(60,64,67,0.15)"};
            font-size: 14px; font-weight: 400; line-height: 20px;
            font-family: 'Google Sans', -apple-system, BlinkMacSystemFont, sans-serif;`;const k=document.createElement("span");k.textContent=e;const s=document.createElement("button");s.className="toast-action",s.textContent="Undo",s.style.cssText=`background: transparent; border: none; color: ${r?"#8ab4f8":"#1a73e8"}; padding: 6px 16px; border-radius: 20px; cursor: pointer; font-size: 14px; font-weight: 500; margin-left: 4px; font-family: 'Google Sans', -apple-system, BlinkMacSystemFont, sans-serif; transition: background 0.2s ease;`;const P=r?"rgba(138, 180, 248, 0.08)":"rgba(26, 115, 232, 0.08)",O=r?"rgba(138, 180, 248, 0.16)":"rgba(26, 115, 232, 0.16)";s.addEventListener("mouseenter",()=>{s.style.background=P}),s.addEventListener("mouseleave",()=>{s.style.background="transparent"}),s.addEventListener("mousedown",()=>{s.style.background=O}),s.addEventListener("mouseup",()=>{s.style.background=P}),s.addEventListener("click",()=>{g(n,t,""),i.style.opacity="0",i.style.transform="translateX(-50%) translateY(100px)",setTimeout(()=>i.remove(),300),u("Reverted to original prompt","info")}),i.appendChild(k),i.appendChild(s),a.appendChild(i),requestAnimationFrame(()=>{i.style.opacity="1",i.style.transform="translateX(-50%) translateY(0)"}),setTimeout(()=>{i.style.opacity="0",i.style.transform="translateX(-50%) translateY(100px)",setTimeout(()=>i.remove(),300)},5e3)}function b(e,t={}){window.geminiAPI&&window.geminiAPI.trackEvent&&window.geminiAPI.trackEvent(e,t)}function G(){p=new MutationObserver(()=>{const t=f();t&&x(t)}),p.observe(document.body,{childList:!0,subtree:!0});const e=f();e&&x(e)}function E(){document.addEventListener("keydown",e=>{(e.ctrlKey||e.metaKey)&&e.shiftKey&&e.key==="P"&&(e.preventDefault(),f()&&c&&c.click())})}function D(e){d=e}function U(){v()}function v(){c&&c.parentNode&&c.remove(),c=null,p&&(p.disconnect(),p=null),h=!1}window.EnhancePromptModule={initialize:L,updatePremiumStatus:D,cleanup:U,destroy:v,canUseFeature:w,getRemainingUses:T},document.readyState==="loading"?document.addEventListener("DOMContentLoaded",E):E()})();
