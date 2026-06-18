class WordCounter{constructor(){this.counterElement=null,this.isActive=!1,this.observer=null,this.currentText="",this.init()}init(){this.createCounter(),this.attachToInput()}createCounter(){this.counterElement=document.createElement("div"),this.counterElement.id="gemini-word-counter",this.counterElement.className="gemini-word-counter",this.counterElement.setAttribute("role","status"),this.counterElement.setAttribute("aria-live","polite"),this.counterElement.setAttribute("aria-label","Word and character count"),this.counterElement.innerHTML=`
            <span class="counter-text">0 characters \u2022 0 words</span>
        `,this.injectStyles()}injectStyles(){const t=document.createElement("style");t.textContent=`
            .gemini-word-counter {
                position: absolute;
                bottom: -24px;
                right: -12px;
                color: var(--gf-text-secondary, #9aa0a6);
                font-size: 12px;
                font-family: 'Google Sans', 'Roboto', sans-serif;
                display: flex;
                align-items: center;
                gap: 8px;
                transition: all 0.2s ease;
                opacity: 0;
                pointer-events: none;
            }

            .gemini-word-counter.active {
                opacity: 1;
                pointer-events: auto;
            }

            .counter-text {
                font-weight: 400;
                white-space: nowrap;
            }

            /* Light theme adjustments */
            .light-theme .gemini-word-counter,
            [data-theme="light"] .gemini-word-counter {
                color: var(--gf-text-primary, #5f6368);
            }

            /* Dark theme adjustments */
            .dark-theme .gemini-word-counter,
            [data-theme="dark"] .gemini-word-counter {
                color: var(--gf-text-secondary, #9aa0a6);
            }



        `,document.getElementById("gemini-word-counter-styles")||(t.id="gemini-word-counter-styles",document.head.appendChild(t))}attachToInput(){const t=()=>{const r=[".ql-editor.textarea.new-input-ui","rich-textarea .ql-editor",'.ql-editor[contenteditable="true"]','div[contenteditable="true"][role="textbox"]'];let e=null;for(const n of r)if(e=document.querySelector(n),e)break;if(e){const n=e.closest(".text-input-field");if(n)n.style.position="relative",n.appendChild(this.counterElement);else{const i=e.closest(".input-area-container");i?(i.style.position="relative",i.appendChild(this.counterElement)):document.body.appendChild(this.counterElement)}return this.setupObserver(e),this.updateCount(e),e.textContent.trim()&&this.showCounter(),!0}return!1};if(!t()){const r=setInterval(()=>{t()&&clearInterval(r)},1e3);setTimeout(()=>{clearInterval(r)},3e4)}}setupObserver(t){this.observer&&this.observer.disconnect(),this.observer=new MutationObserver(()=>{this.updateCount(t)}),this.observer.observe(t,{childList:!0,characterData:!0,subtree:!0}),t.addEventListener("input",()=>{this.updateCount(t)}),t.addEventListener("focus",()=>{this.showCounter()}),t.addEventListener("blur",()=>{setTimeout(()=>{this.currentText.trim()||this.hideCounter()},2e3)})}updateCount(t){const r=t.textContent||t.innerText||"";this.currentText=r;const e=r.trim(),n=e.length,i=e===""?0:e.split(/\s+/).length,o=this.counterElement.querySelector(".counter-text");o.textContent=`${n} characters \u2022 ${i} words`,n>0&&this.showCounter()}showCounter(){this.isActive||(this.counterElement.classList.add("active"),this.isActive=!0)}hideCounter(){this.isActive&&(this.counterElement.classList.remove("active"),this.isActive=!1)}destroy(){this.observer&&this.observer.disconnect(),this.counterElement&&this.counterElement.parentNode&&this.counterElement.parentNode.removeChild(this.counterElement)}}typeof window<"u"&&(window.WordCounter=WordCounter);
