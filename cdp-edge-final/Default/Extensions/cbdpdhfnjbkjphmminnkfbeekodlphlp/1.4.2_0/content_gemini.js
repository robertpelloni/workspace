let isExportDropdownOpen=!1,isSettingsPopupOpen=!1,selectedMessageCount=0,exportSettings={fileName:"gemini-conversation",format:"pdf",pdfTheme:"light",orientation:"portrait",compression:!0,uiTheme:"light"};const loadingSpinnerSVG='<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 100 100" preserveAspectRatio="xMidYMid" width="18" height="18" style="shape-rendering: auto; display: block; background: transparent;" xmlns:xlink="http://www.w3.org/1999/xlink"><g><circle cx="50" cy="50" fill="none" stroke="currentColor" stroke-width="10" r="35" stroke-dasharray="164.93361431346415 56.97787143782138"><animateTransform attributeName="transform" type="rotate" repeatCount="indefinite" dur="1s" values="0 50 50;360 50 50" keyTimes="0;1"></animateTransform></circle><g></g></g></svg>',checkmarkSVG='<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="currentColor" width="18" height="18"><path d="M9 16.17L4.83 12l-1.42 1.41L9 19 21 7l-1.41-1.41z"/></svg>',defaultIconSVG='<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="currentColor" class="save-button-icon" width="18" height="18"><path d="M17 3H5C3.89 3 3 3.9 3 5v14c0 1.1.89 2 2 2h14c1.1 0 2-.9 2-2V7l-4-4zm2 16H5V5h11.17L19 7.83V19zm-7-7c-1.66 0-3 1.34-3 3s1.34 3 3 3 3-1.34 3-3-1.34-3-3-3zM6 6h9v4H6z"></path></svg>';function isDarkModeActive(){if(document.body.classList.contains("dark-theme"))return!0;const e=window.getComputedStyle(document.body).backgroundColor;if(e){const n=e.match(/\d+/g);if(n&&n.length>=3)return(parseInt(n[0])*299+parseInt(n[1])*587+parseInt(n[2])*114)/1e3<128}return!1}function getCurrentTheme(){return exportSettings.uiTheme==="auto"?isDarkModeActive()?"dark":"light":exportSettings.uiTheme}function loadInitialExportSettings(){try{const e=localStorage.getItem("gemini-exporter-settings");if(e){const n=JSON.parse(e);Object.keys(exportSettings).forEach(t=>{n.hasOwnProperty(t)&&(t==="format"&&!["pdf","html","md","json"].includes(n[t])||t==="pdfTheme"&&!["auto","light","dark"].includes(n[t])||t==="uiTheme"&&!["auto","light","dark"].includes(n[t])||t==="orientation"&&!["portrait","landscape"].includes(n[t])||t==="compression"&&typeof n[t]!="boolean"||(exportSettings[t]=n[t]))})}else saveExportSettings()}catch{}}loadInitialExportSettings();function getFormattedTimestamp(){const e=new Date,n=e.toISOString().split("T")[0],t=e.toTimeString().split(" ")[0].replace(/:/g,"-");return`${n}-${t}`}function generateFilename(e,n){const t=getFormattedTimestamp();return`${e.replace(/[^a-z0-9_\-]/gi,"_")||"gemini-conversation"}-${t}.${n}`}function downloadData(e,n,t){try{const i=new Blob([e],{type:t}),a=URL.createObjectURL(i),o=document.createElement("a");o.href=a,o.download=n,document.body.appendChild(o),o.click(),document.body.removeChild(o),URL.revokeObjectURL(a)}catch{const a=document.querySelector(".gemini-exporter-overlay");if(a){const o=a.querySelector(".exporter-message");o&&(o.textContent=`Failed to download ${n}. Please try again.`)}}}function convertHtmlToMarkdown(e){if(!e)return"";let n=e;const t=document.createElement("div");t.innerHTML=e,t.querySelectorAll("div.code-block-decoration, sources-carousel-inline, sources-carousel, source-footnote").forEach(o=>o.remove());function i(o){if(!o||typeof o.nodeName!="string")return"";let r="";switch(o.nodeName){case"#text":r=(o.textContent||"").replace(/([*_~])/g,"\\$1");break;case"P":r=a(o)+`

`;break;case"H1":r="# "+a(o)+`

`;break;case"H2":r="## "+a(o)+`

`;break;case"H3":r="### "+a(o)+`

`;break;case"H4":r="#### "+a(o)+`

`;break;case"H5":r="##### "+a(o)+`

`;break;case"H6":r="###### "+a(o)+`

`;break;case"UL":r=Array.from(o.children).map(f=>"* "+a(f).trim()).join(`
`)+`

`;break;case"OL":r=Array.from(o.children).map((f,p)=>`${p+1}. ${a(f).trim()}`).join(`
`)+`

`;break;case"LI":r=a(o);break;case"A":r=`[${a(o)}](${o.href||""})`;break;case"STRONG":case"B":r="**"+a(o)+"**";break;case"EM":case"I":r="*"+a(o)+"*";break;case"CODE-BLOCK":const s=o.querySelector("pre code, pre"),l=s?.className?.match(/language-(\S+)/);r=`\`\`\`${l?l[1]:""}
${s?.textContent||o.textContent||""}
\`\`\`

`;break;case"PRE":o.closest("code-block")?r=a(o):r=`\`\`\`
${o.textContent||""}
\`\`\`

`;break;case"CODE":o.closest("pre, code-block")?r=o.textContent||"":r="`"+o.textContent+"`";break;case"BLOCKQUOTE":r="> "+a(o).replace(/\n/g,`
> `)+`

`;break;case"HR":r=`---

`;break;case"TABLE":const c=o.querySelector("thead tr, tr:first-child"),u=Array.from(o.querySelectorAll("tbody tr, tr:not(:first-child)"));let d="";if(c){const f=Array.from(c.querySelectorAll("th, td")).map(p=>a(p).trim());d+=`| ${f.join(" | ")} |
`,d+=`| ${f.map(()=>"---").join(" | ")} |
`}u.forEach(f=>{const p=Array.from(f.querySelectorAll("td")).map(g=>a(g).trim());d+=`| ${p.join(" | ")} |
`}),r=d+`
`;break;case"IMG":r=`![${o.alt||"image"}](${o.src||""})
`;break;case"BR":r=`  
`;break;case"DIV":case"SPAN":r=a(o);break;default:r=a(o);break}return r}function a(o){return!o||typeof o.childNodes!="object"||o.childNodes===null?"":Array.from(o.childNodes).map(i).join("")}return n=a(t),n=n.replace(/\n{3,}/g,`

`).trim(),n}function formatConversationHTML(e,n="light"){const t=n==="dark",i=t?"#131314":"#FFFFFF",a=t?"#e8eaed":"#1f1f1f",o=t?"rgba(255, 255, 255, 0.03)":"#F7F7F7",r=i,s=a,l=t?"#9aa0a6":"#5f6368",m=t?"#282829":"#EFEFEF",c=t?"#8ab4f8":"#1a73e8",u=t?"#202124":"#f8f9fa",d=t?"#e8eaed":"#1f1f1f",f=t?"rgba(255, 255, 255, 0.04)":"rgba(0,0,0,0.05)",p=t?"#bdc1c6":"#3c4043",g=t?"rgba(255, 255, 255, 0.06)":"rgba(0,0,0,0.06)",h=t?"rgba(255, 255, 255, 0.08)":"rgba(0,0,0,0.06)";let b=`<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>${exportSettings.fileName||"Gemini Conversation"}</title>
    <style>
        /* Removed remote font import to comply with CSP */
        html { background-color: ${i}; }
        body { 
            font-family: system-ui, -apple-system, "Segoe UI", Roboto, Helvetica, Arial, "Noto Sans", "Liberation Sans", sans-serif; 
            margin: 0; 
            padding: 20px; 
            background-color: ${i}; 
            color: ${a};
            font-size: 10pt; /* Default message text size */
            line-height: 1.4;  /* Default message line height */
        }
        .conversation-wrapper { max-width: 800px; margin: 0 auto; }
        .export-header h1 {
            font-size: 16pt;
            font-weight: 500;
            color: ${a};
            margin-bottom: 4px;
        }
        .export-header .timestamp {
            font-size: 8pt;
            font-style: italic;
            color: ${l};
            margin-bottom: 16px;
        }
        .export-header hr {
            border: none;
            border-top: 1px solid ${m};
            margin-bottom: 16px;
        }
        .message-pair { 
            margin-bottom: 16px; 
            border: 1px solid ${m}; 
            border-radius: 8px; 
            overflow: hidden; 
        }
        .message-part { 
            padding: 8px; /* Tightened padding */
        }
        .message-part.question { background-color: ${o}; }
        .message-part.answer { background-color: ${r}; }
        
        .speaker-label {
            font-size: 10pt;
            font-weight: bold;
            color: ${s};
            margin: 0 0 4px 0; /* Tighten spacing below label */
        }
        .content { 
            min-width: 0; 
            word-wrap: break-word; 
            color: inherit; /* Inherits from body or message-part */
            font-size: 10pt; /* Ensure content text is 10pt */
            line-height: 1.4; /* Ensure content text line-height */
        }
        .content * { max-width: 100%; box-sizing: border-box; }
        .content p { margin: 0.5em 0; } /* Keep some paragraph spacing */
        .content ul, .content ol { padding-left: 25px; margin: 0.5em 0; }
        .content li { margin-bottom: 5px; }
        .content strong, .content b { font-weight: bold; } /* Standard bold */
        .content em, .content i { font-style: italic; } /* Standard italic */
        
        a { color: ${c}; text-decoration: none; }
        a:hover { text-decoration: underline; }
        img { height: auto; border-radius: 4px; margin: 5px 0; }
        table { width: 100%; border-collapse: collapse; margin: 1em 0; page-break-inside: auto; }
        th, td { border: 1px solid ${m}; padding: 8px 10px; text-align: left; }
        th { background-color: ${g}; font-weight: bold; }
        
        code-block { display: block; margin: 1em 0; border-radius: 8px; overflow: hidden; border: 1px solid ${m}; background-color: ${u} !important; color: ${d} !important; page-break-inside: avoid; }
        .code-block-decoration { padding: 8px 12px; background-color: ${f}; font-size: 12px; color: ${p}; display: flex; justify-content: space-between; align-items: center; border-bottom: 1px solid ${m}; }
        .code-block-decoration .buttons { display: none; } 
        .formatted-code-block-internal-container { padding: 0; }
        pre { display: block; background-color: transparent !important; color: inherit !important; padding: 12px 15px; margin: 0; font-family: ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, 'Liberation Mono', 'DejaVu Sans Mono', monospace; font-size: 9.5pt; /* Slightly smaller for pre */ line-height: 1.4; white-space: pre-wrap; word-wrap: break-word; overflow-x: auto; border: none; page-break-inside: auto; }
        code { font-family: ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, 'Liberation Mono', 'DejaVu Sans Mono', monospace; font-size: 0.9em; background-color: ${h}; padding: 2px 4px; border-radius: 3px; color: inherit; word-break: break-all; }
        pre code { background-color: transparent !important; padding: 0; font-size: inherit; border-radius: 0; }
        
        .hljs-keyword { color: ${t?"#569cd6":"#a31515"}; font-weight: bold; }
        .hljs-string { color: ${t?"#ce9178":"#d69d85"}; }
        .hljs-number { color: ${t?"#b5cea8":"#098658"}; }
        .hljs-comment { color: ${t?"#6A9955":"#008000"}; font-style: italic; }
        .hljs-function .hljs-title { color: ${t?"#DCDCAA":"#795e26"}; }
        .hljs-params { color: ${t?"#9CDCFE":"#267f99"}; }
        .hljs-built_in, .hljs-literal { color: ${t?"#4EC9B0":"#0000ff"}; }
        
        .katex-display { display: block; text-align: center; margin: 1em 0; page-break-inside: avoid; }
        .katex { font-size: 1.1em; color: inherit; }
        sources-carousel-inline, sources-carousel, source-footnote { display: none !important; }
    </style>
</head>
<body>
    <div class="conversation-wrapper">
        <div class="export-header">
        <h1>${exportSettings.fileName||"Gemini Conversation"}</h1>
            <p class="timestamp">Exported on: ${new Date().toLocaleString()}</p>
            <hr>
        </div>
`;return e.forEach(w=>{if(b+=`<div class="message-pair">
`,w.question&&(b+=`    <div class="message-part question">
        <p class="speaker-label user-label"><strong>User</strong></p>
        <div class="content">${w.question}</div>
    </div>
`),w.answer){const y=w.question?`border-top: 1px solid ${m};`:"";b+=`    <div class="message-part answer" style="${y}">
        <p class="speaker-label gemini-label"><strong>Gemini</strong></p>
        <div class="content">${w.answer}</div>
    </div>
`}b+=`</div>
`}),b+=`
    </div>
</body>
</html>`,b}function downloadAsHTML(e,n){const t=generateFilename(n,"html");let i="light";(exportSettings.pdfTheme==="dark"||exportSettings.pdfTheme==="auto"&&document.body.classList.contains("dark-theme"))&&(i="dark");const a=formatConversationHTML(e,i);downloadData(a,t,"text/html;charset=utf-8")}function downloadAsMarkdown(e,n){const t=generateFilename(n,"md");let i=`# ${n||"Gemini Conversation"}
Exported on: ${new Date().toLocaleString()}

---

`;e.forEach(a=>{a.question&&(i+=`**You:**
${convertHtmlToMarkdown(a.question)}

`),a.answer&&(i+=`**Gemini:**
${convertHtmlToMarkdown(a.answer)}

`),i+=`---

`}),downloadData(i,t,"text/markdown;charset=utf-8")}function downloadAsJSON(e,n){const t=generateFilename(n,"json"),i={title:n||"Gemini Conversation",exportedAt:new Date().toISOString(),conversation:e.map(o=>({question:o.question||null,answer:o.answer||null}))},a=JSON.stringify(i,null,2);downloadData(a,t,"application/json;charset=utf-8")}function downloadAsTXT(e,n){const t=generateFilename(n,"txt");let i=`${n||"Gemini Conversation"}
`;i+=`Exported on: ${new Date().toLocaleString()}

`,i+=`-----------------------------------------------------

`;const a=o=>{if(!o)return"";const r=document.createElement("div");return r.innerHTML=o,r.querySelectorAll(".gemini-export-checkbox-container, style, script, sources-carousel-inline, sources-carousel, source-footnote").forEach(s=>s.remove()),(r.textContent||r.innerText||"").trim()};e.forEach(o=>{o.question&&(i+=`User:
${a(o.question)}

`),o.answer&&(i+=`Gemini:
${a(o.answer)}

`),i+=`-----------------------------------------------------

`}),downloadData(i,t,"text/plain;charset=utf-8")}function downloadAsCSV(e,n){const t=generateFilename(n,"csv"),i=r=>{if(!r)return"";const s=document.createElement("div");return s.innerHTML=r,s.querySelectorAll(".gemini-export-checkbox-container, style, script, sources-carousel-inline, sources-carousel, source-footnote").forEach(l=>l.remove()),(s.textContent||s.innerText||"").trim()},a=r=>{if(r==null)return"";let s=r.toString();return s=s.replace(/"/g,'""'),(s.includes(",")||s.includes(`
`)||s.includes('"'))&&(s=`"${s}"`),s};let o=`Timestamp,Speaker,Content
`;e.forEach((r,s)=>{const l=new Date().toISOString();if(r.question){const m="User",c=i(r.question);o+=`${a(l)},${a(m)},${a(c)}
`}if(r.answer){const m="Gemini",c=i(r.answer);o+=`${a(l)},${a(m)},${a(c)}
`}}),downloadData(o,t,"text/csv;charset=utf-8")}function parseColor(e){if(typeof e!="string")return{r:0,g:0,b:0};if(e.startsWith("#")){let n=e.substring(1);if(n.length===3&&(n=n.split("").map(t=>t+t).join("")),n.length===6){const t=parseInt(n,16);return{r:t>>16&255,g:t>>8&255,b:t&255}}}else if(e.startsWith("rgb")){const n=e.match(/[\d.]+/g);if(n&&n.length>=3)return{r:parseInt(n[0]),g:parseInt(n[1]),b:parseInt(n[2])}}return{r:0,g:0,b:0}}function isCanvasEffectivelyEmpty(e,n,t=5,i=.05){if(!e||typeof e.getContext!="function")return!1;const a=e.getContext("2d",{willReadFrequently:!0});if(!a)return!1;const o=e.width,r=e.height;if(o===0||r===0)return!0;try{const l=a.getImageData(0,0,o,r).data,m=Math.max(1,Math.floor(o*r*i)),c=o*r,u=Math.max(1,Math.floor(c/m));for(let d=0;d<c;d+=u){const f=d*4,p=l[f],g=l[f+1],h=l[f+2];if(Math.abs(p-n.r)>t||Math.abs(g-n.g)>t||Math.abs(h-n.b)>t)return!1}}catch{return!1}return!0}function generatePDF(e){let n="light";(exportSettings.pdfTheme==="dark"||exportSettings.pdfTheme==="auto"&&document.body.classList.contains("dark-theme"))&&(n="dark");const t=n==="dark";function i(r){if(!r)return"";try{const s=document.createElement("div");return s.innerHTML=r,["sources-carousel-inline","sources-carousel","source-footnote",".code-block-decoration .buttons",".gemini-export-checkbox-container","script","style"].forEach(m=>{s.querySelectorAll(m).forEach(c=>c.remove())}),s.querySelectorAll("[jslog]").forEach(m=>m.removeAttribute("jslog")),s.innerHTML}catch{return r}}function a(r){return new Promise(async s=>{try{const l=await fetch(r,{mode:"cors",credentials:"omit"});if(!l.ok)return s(null);const m=await l.blob(),c=new FileReader;c.onloadend=()=>s(c.result),c.onerror=()=>s(null),c.readAsDataURL(m)}catch{s(null)}})}async function o(r){if(!r)return"";const s=document.createElement("div");s.innerHTML=r;const l=Array.from(s.querySelectorAll("img")),m="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAQAAAC1HAwCAAAAC0lEQVR4nGNgYAAAAAMAASsJTYQAAAAASUVORK5CYII=",c=u=>{const d=u.getAttribute("alt")||"image",f=document.createElement("span");f.textContent=`[${d}]`,u.replaceWith(f)};return await Promise.all(l.map(async u=>{try{const d=u.getAttribute("src")||"";if(!d){c(u);return}if(d.startsWith("data:"))return;if(d.startsWith("blob:")||d.startsWith("chrome-extension:")){c(u);return}const f=await a(d);f?u.setAttribute("src",f):c(u)}catch{c(u)}})),s.querySelectorAll("img").forEach(u=>{const d=u.getAttribute("src");(!d||d===""||d==="null")&&c(u)}),s.innerHTML}return new Promise(async(r,s)=>{try{if(typeof pdfMake>"u"||typeof htmlToPdfmake>"u"){const p="Error: PDF generation libraries (pdfMake/html-to-pdfmake) are not available. Please reload the page.",g=document.querySelector("#exporter-overlay")||document.querySelector(".gemini-exporter-overlay");if(g){const h=g.querySelector(".exporter-message");h&&(h.textContent=p)}s(new Error(p));return}let l=[];e.forEach(p=>{p.question&&(l.push("<p><strong>User</strong></p>"),l.push(`<div>${i(p.question)}</div>`)),p.answer&&(p.question&&l.push('<div style="height:4px;"></div>'),l.push("<p><strong>Gemini</strong></p>"),l.push(`<div>${i(p.answer)}</div>`)),l.push("<hr/>")});let m=l.join("");m=await o(m);const c=htmlToPdfmake(m),u=exportSettings.fileName||"Gemini Conversation",d={pageSize:"A4",pageMargins:[28,28,28,28],pageOrientation:exportSettings.orientation,info:{title:u},content:[{text:u,style:"header"},{text:`Exported on: ${new Date().toLocaleString()}`,style:"subheader"},{text:"",margin:[0,0,0,8]},...c],styles:{header:{fontSize:16,bold:!0,margin:[0,0,0,4]},subheader:{fontSize:8,italics:!0,color:t?"#9aa0a6":"#5f6368",margin:[0,0,0,12]}},defaultStyle:{fontSize:10,color:t?"#e8eaed":"#1f1f1f"}};t&&(d.background=function(p,g){return{canvas:[{type:"rect",x:0,y:0,w:g.width,h:g.height,color:"#131314"}]}});const f=generateFilename(u,"pdf");try{pdfMake.createPdf(d).getDataUrl(p=>{try{chrome?.runtime?.id?chrome.runtime.sendMessage({action:"downloadFile",url:p,filename:f},g=>{if(g&&g.status==="success")r();else try{pdfMake.createPdf(d).download(f),r()}catch(h){s(new Error(g&&g.message||h?.message||"Download failed"))}}):(pdfMake.createPdf(d).download(f),r())}catch(g){try{pdfMake.createPdf(d).download(f),r()}catch(h){s(g||h)}}})}catch(p){try{pdfMake.createPdf(d).download(f),r()}catch(g){s(p||g)}}}catch(l){const m=document.querySelector("#exporter-overlay")||document.querySelector(".gemini-exporter-overlay");if(m){const c=m.querySelector(".exporter-message");c&&(c.textContent=`PDF generation failed: ${l.message||"Unknown error"}`)}s(l)}})}function getChatTitle(){const e=document.querySelector(".chat-title-container");return e&&e.textContent.trim()?e.textContent.trim():document.title}function extractConversationData(){const e=[],n=getScrollHost();return n&&n.querySelectorAll("div.conversation-container").forEach(i=>{const a=i.querySelector("user-query, user-query-content"),o=i.querySelector("message-content");let r="";const s=a?.querySelector(".query-text");if(s){const c=s.querySelectorAll(".query-text-line");c.length>0&&(r=Array.from(c).map(u=>u.innerHTML.trim()).join(""))}else if(a){const c=a.cloneNode(!0);c.querySelectorAll("mat-icon, .icon-button, .expand-button").forEach(u=>u.remove()),r=c.innerHTML.trim()}let l="";const m=o?.querySelector(".markdown-main-panel, .output-content .markdown, .output-content");if(m)l=m.innerHTML.trim();else if(o){const c=o.cloneNode(!0);c.querySelectorAll("message-actions, mat-icon-button, .icon-button, response-actions").forEach(u=>u.remove()),l=c.innerHTML.trim()}if(r||l){const c=document.createElement("div");c.innerHTML=r,c.querySelectorAll(".gemini-export-checkbox-container").forEach(d=>d.remove());const u=document.createElement("div");u.innerHTML=l,u.querySelectorAll(".gemini-export-checkbox-container").forEach(d=>d.remove()),e.push({question:c.innerHTML||null,answer:u.innerHTML||null})}}),e}function getScrollHost(){const e=['[data-test-id="chat-history-container"]','[data-testid="chat-history-container"]',"#chat-history","infinite-scroller.chat-history","infinite-scroller"];for(const t of e)try{const i=document.querySelector(t);if(i)return i}catch{}const n=document.querySelector("div.conversation-container, message-content, user-query-content");if(n){let t=n.parentElement;for(;t&&t!==document.body;){const i=t.scrollHeight>t.clientHeight,a=t instanceof Element?window.getComputedStyle(t):null,o=a?a.overflowY:"";if(i&&o!=="visible")return t;t=t.parentElement}}return document.scrollingElement||document.documentElement}function isConversationIncomplete(){const e=getScrollHost();if(!e||e===document.documentElement)return!1;if(e.scrollTop>100)return!0;const n=e.scrollHeight>e.clientHeight;return!!(n&&e.scrollTop<e.scrollHeight-e.clientHeight-100||e.querySelectorAll('.loading-indicator, .spinner, [aria-label*="loading"], .loading').length>0||e.querySelectorAll("div.conversation-container").length<5&&n)}async function loadFullConversationIfNeeded(){const e=getScrollHost();if(!e)return;let n=0,t=document.querySelectorAll("div.conversation-container").length,i=0;const a=80;let o=0;const r=4;for(;i<a&&o<r;){if(n=t,e===document.documentElement||e===document.scrollingElement)window.scrollTo({top:0,behavior:"auto"});else{try{e.scrollTo({top:0,behavior:"auto"})}catch{e.scrollTop=0}e.dispatchEvent(new Event("scroll",{bubbles:!0}))}await new Promise(s=>setTimeout(s,600)),t=document.querySelectorAll("div.conversation-container").length,t>n?o=0:o++,i++}}async function downloadAsPDF(e,n){return window.geminiAPI&&typeof CONFIG<"u"&&CONFIG.ANALYTICS_EVENTS&&await window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.EXPORT_PERFORMED,{format:"pdf"}),generatePDF(e)}function getExportButtonElement(){return document.querySelector("#gemini-exporter")?.shadowRoot?.querySelector("#export-button")}function setButtonLoading(e,n="Generating PDF..."){e&&(e.disabled=!0,e.innerHTML=`${loadingSpinnerSVG}<span>${n}</span>`,e.style.cursor="wait")}function setButtonSuccess(e,n="Downloaded"){e&&(e.disabled=!0,e.innerHTML=`${checkmarkSVG}<span>${n}</span>`,e.style.cursor="default")}function resetButtonState(e){if(!e)return;const n=!!document.getElementById("gemini-selection-active");if(e.disabled=n&&selectedMessageCount===0,e.style.cursor=e.disabled?"not-allowed":"pointer",n){const t=selectedMessageCount>0?`Save ${selectedMessageCount} as PDF`:"Select Messages";e.innerHTML=`${defaultIconSVG}<span>${t}</span>`}else e.innerHTML=`${defaultIconSVG}<span>Save Chat</span>`}async function startDirectPDFExport(){const e=document.createElement("div");e.id="exporter-overlay",e.innerHTML=`
        <div class="exporter-overlay-content">
            <div class="exporter-spinner"></div>
            <div class="exporter-message">Generating PDF...</div>
        </div>
    `;const n=document.getElementById("gemini-folders-injector-host");n&&n.shadowRoot?n.shadowRoot.appendChild(e):document.body.appendChild(e);try{if(isConversationIncomplete()){const r=e.querySelector(".exporter-message");r&&(r.textContent="Loading full conversation..."),await loadFullConversationIfNeeded(),r&&(r.textContent="Generating PDF...")}const i=extractConversationData(),a=getChatTitle()||"gemini-conversation";await downloadAsPDF(i,a);const o=e.querySelector(".exporter-message");o&&(o.textContent="Download complete!")}catch{const i=e.querySelector(".exporter-message");i&&(i.textContent="Export failed. See console for details.")}finally{setTimeout(()=>{e.remove()},2e3)}}function triggerExport(e){startDirectPDFExport()}window.triggerGeminiToolboxExport=triggerExport,window.exportCurrentChatToPDF=async function(e){try{await new Promise(a=>setTimeout(a,500));try{isConversationIncomplete()&&(await loadFullConversationIfNeeded(),await new Promise(a=>setTimeout(a,300)))}catch{}const n=await extractConversationData();if(!n||n.length===0)throw new Error("No messages found in current chat");const t=e||n[0]?.question?.substring(0,50)||"Gemini Chat",i=`${t.replace(/[^a-z0-9]/gi,"_")}_${new Date().toISOString().split("T")[0]}.pdf`;return exportSettings.fileName=t,await generatePDF(n),!0}catch(n){throw n}},window.exportCurrentChat=async function(e="pdf",n){try{await new Promise(o=>setTimeout(o,500));try{isConversationIncomplete()&&(await loadFullConversationIfNeeded(),await new Promise(o=>setTimeout(o,300)))}catch{}const t=await extractConversationData();if(!t||t.length===0)throw new Error("No messages found in current chat");const i=n||getChatTitle()||t[0]?.question?.substring(0,50)||"Gemini Chat",a=(e||"pdf").toLowerCase();exportSettings.fileName=i;try{a!=="pdf"&&window.geminiAPI&&typeof CONFIG<"u"&&CONFIG.ANALYTICS_EVENTS&&await window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.EXPORT_PERFORMED,{format:a})}catch{}switch(a){case"html":downloadAsHTML(t,i);break;case"md":case"markdown":downloadAsMarkdown(t,i);break;case"txt":case"text":downloadAsTXT(t,i);break;case"csv":downloadAsCSV(t,i);break;default:await downloadAsPDF(t,i);break}return!0}catch(t){throw t}},document.readyState==="loading"?document.addEventListener("DOMContentLoaded",loadInitialExportSettings):loadInitialExportSettings();
