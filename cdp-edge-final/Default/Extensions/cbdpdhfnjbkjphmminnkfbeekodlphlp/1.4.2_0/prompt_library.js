class PromptLibrary{constructor(e){this.shadowRoot=e,this.userPrompts=[],this.loadUserPrompts(),this.prompts=[],this.isInitialized=!1,this.errorQueue=[],this.isShowingError=!1,this.currentTab="library"}init(){this.isInitialized||(this.setupEventListeners(),this.isInitialized=!0)}initializeEventListeners(){this.init()}setupEventListeners(){const e=this.shadowRoot.querySelector(".modal-close-icon"),t=this.shadowRoot.getElementById("search-bar"),n=this.shadowRoot.getElementById("prompt-library-modal"),o=this.shadowRoot.querySelectorAll(".nav-item");e&&e.addEventListener("click",()=>this.hide()),t&&t.addEventListener("keyup",()=>this.filterPrompts()),o.forEach(i=>{i.addEventListener("click",()=>{o.forEach(l=>l.classList.remove("active")),i.classList.add("active");const r=i.getAttribute("data-filter")==="chaining"?"chaining":"library";if(this.currentTab!==r){this.currentTab=r;const l=this.shadowRoot.getElementById("prompt-list");l&&l.classList.toggle("chaining-tab",r==="chaining"),this.updateControlsForTab(r),window.geminiAPI&&typeof CONFIG<"u"&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.SETTINGS_OPENED,{feature:"prompt_library",action:"tab_switch",tab:r})}this.filterPrompts()})}),n&&n.addEventListener("click",i=>{i.target===n&&this.hide()}),this.initMyPrompts()}show(){if(!this.shadowRoot){const t=document.createElement("div");t.textContent="The Prompt Library component is missing. Please reload the page.",t.className="status-message error",document.body.appendChild(t);return}const e=this.shadowRoot.getElementById("prompt-library-modal");if(e){this.updateTheme(),e.style.display="flex",e.style.alignItems="center",e.style.justifyContent="center",this.shadowRoot.querySelectorAll(".nav-item").forEach(o=>{o.getAttribute("data-filter")==="my-prompts"?o.classList.add("active"):o.classList.remove("active")});const n=this.shadowRoot.getElementById("prompt-list");n&&n.classList.toggle("chaining-tab",this.currentTab==="chaining"),this.updateControlsForTab("library"),this.filterPrompts(),window.geminiAPI&&typeof CONFIG<"u"&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.SETTINGS_OPENED,{feature:"prompt_library",totalPrompts:this.prompts.length,userPrompts:this.userPrompts.length,currentTab:this.currentTab})}else this.showError("Unable to find Prompt Library interface. Please refresh the page.")}hide(){const e=this.shadowRoot.getElementById("prompt-library-modal");e&&(e.style.display="none")}updateTheme(){const e=this.shadowRoot.getElementById("prompt-library-modal");if(!e)return;let t=!1;if((document.body.classList.contains("light-theme")||document.body.classList.contains("light-mode")||document.body.classList.contains("light"))&&(t=!0),document.documentElement.getAttribute("data-theme")==="light"&&(t=!0),!t){const n=window.getComputedStyle(document.body).backgroundColor;if(n){const o=n.match(/\d+/g);o&&o.length>=3&&(parseInt(o[0])*299+parseInt(o[1])*587+parseInt(o[2])*114)/1e3>128&&(t=!0)}}t?e.classList.add("prompt-library-light"):e.classList.remove("prompt-library-light")}updateControlsForTab(e){const t=this.shadowRoot.getElementById("add-action-btn"),n=this.shadowRoot.getElementById("search-bar"),o=this.shadowRoot.querySelector(".category-group");!t||!n||(e==="chaining"?(o&&(o.style.opacity="0.5"),t.innerHTML=`
                <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                    <line x1="12" y1="5" x2="12" y2="19"></line>
                    <line x1="5" y1="12" x2="19" y2="12"></line>
                </svg>
                <span>New Chain</span>
            `,t.title="Create prompt chain",t.setAttribute("data-action","chain"),n.placeholder="Search chains..."):(o&&(o.style.opacity="1"),t.innerHTML=`
                <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                    <line x1="12" y1="5" x2="12" y2="19"></line>
                    <line x1="5" y1="12" x2="19" y2="12"></line>
                </svg>
                <span>New Prompt</span>
            `,t.title="Add new prompt",t.setAttribute("data-action","prompt"),n.placeholder="Search prompts..."))}loadPrompts(e=null,t=""){e||(e=[...this.userPrompts.sort((s,r)=>s.isDefault&&!r.isDefault?1:!s.isDefault&&r.isDefault?-1:0),...this.prompts]);const n=this.shadowRoot.getElementById("prompt-list");if(!n)return;const o=(t||"").trim();if(n.innerHTML="",!e||e.length===0){const i=document.createElement("div");i.className="prompt-grid-empty-state",i.style.cssText=`
                grid-column: 1 / -1;
                text-align: center;
                padding: 60px 20px;
                color: var(--gf-text-secondary);
                font-size: 16px;
                background: var(--gf-bg-tertiary);
                border-radius: 12px;
                margin: 20px;
                display: flex;
                flex-direction: column;
                align-items: center;
                justify-content: center;
                min-height: 200px;
            `;const s=this.shadowRoot.querySelector(".nav-item.active")?.getAttribute("data-filter"),r=s==="my-prompts",l=s==="chaining",a=this.userPrompts.some(h=>!h.isDefault&&!h.isChain),d=this.userPrompts.some(h=>h.isChain&&!h.isDefault);r&&!a&&!t?i.innerHTML=`
                    <svg width="48" height="48" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" style="opacity: 0.5; margin-bottom: 16px;">
                        <path d="M12 5v14M5 12h14"></path>
                        <circle cx="12" cy="12" r="10"></circle>
                    </svg>
                    <p style="margin: 0 0 8px 0; font-weight: 500;">No custom prompts yet</p>
                    <p style="margin: 0; font-size: 14px; opacity: 0.8;">Click "New Prompt" to create your first one!</p>
                `:l&&!d&&!t?i.innerHTML=`
                    <svg width="48" height="48" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" style="opacity: 0.5; margin-bottom: 16px;">
                        <path d="M10 13a5 5 0 0 0 7.54.54l3-3a5 5 0 0 0-7.07-7.07l-1.72 1.71"></path>
                        <path d="M14 11a5 5 0 0 0-7.54-.54l-3 3a5 5 0 0 0 7.07 7.07l1.71-1.71"></path>
                    </svg>
                    <p style="margin: 0 0 8px 0; font-weight: 500;">No prompt chains yet</p>
                    <p style="margin: 0; font-size: 14px; opacity: 0.8;">Click "New Prompt" and switch to "New Chain" to create your first chain!</p>
                `:i.innerHTML=`
                    <svg width="48" height="48" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" style="opacity: 0.5; margin-bottom: 16px;">
                        <rect x="3" y="3" width="18" height="18" rx="2" ry="2"></rect>
                        <line x1="9" y1="9" x2="15" y2="9"></line>
                        <line x1="9" y1="15" x2="15" y2="15"></line>
                    </svg>
                    <p style="margin: 0 0 8px 0; font-weight: 500;">No prompts found</p>
                    <p style="margin: 0; font-size: 14px; opacity: 0.8;">Try adjusting your search or check other tabs</p>
                `,n.appendChild(i);return}e.forEach(i=>{const s=document.createElement("div");s.className=i.isUserPrompt?"prompt-item my-prompt compact":"prompt-item compact",s.setAttribute("data-category",i.category),s.setAttribute("data-prompt-id",i.id);const r=i.category.replace("_"," ").toUpperCase(),l=document.createElement("div");l.className="prompt-header-compact";const a=document.createElement("div");a.className="prompt-title-row";const d=document.createElement("h3");if(d.className="title",o?d.innerHTML=this.highlightText(i.title,o):d.textContent=i.title,a.appendChild(d),i.isChain&&i.steps){const p=document.createElement("span");p.className="chain-badge",p.style.cssText=`
                    display: inline-flex;
                    align-items: center;
                    gap: 4px;
                    padding: 2px 8px;
                    background: var(--gf-accent-primary);
                    color: var(--gf-button-text);
                    border-radius: 12px;
                    font-size: 11px;
                    font-weight: 500;
                    margin-left: 8px;
                `,p.innerHTML=`
                    <svg width="12" height="12" viewBox="0 0 24 24" fill="currentColor">
                        <path d="M4 6h16v2H4zm0 5h16v2H4zm0 5h16v2H4z"/>
                    </svg>
                    ${(i.steps||[]).length} Steps
                `,a.appendChild(p)}l.appendChild(a);const h=document.createElement("span");h.className="category-badge",h.textContent=r,l.appendChild(h);const f=document.createElement("div");f.className="prompt-details";const v=document.createElement("div");if(v.className="content",i.isChain&&i.steps&&Array.isArray(i.steps)&&i.steps.length>0){const p=document.createElement("div");p.className="chain-steps-preview",p.style.cssText=`
                    display: flex;
                    flex-direction: column;
                    gap: 10px;
                `,i.steps.forEach((g,y)=>{if(!g||typeof g!="string")return;const w=document.createElement("div");w.className="chain-step-preview-item",w.style.cssText=`
                        padding: 10px;
                        background: var(--gf-bg-tertiary);
                        border-left: 3px solid var(--gf-accent-primary);
                        border-radius: 4px;
                    `;const x=document.createElement("div");x.className="chain-step-label",x.style.cssText=`
                        font-weight: 600;
                        font-size: 12px;
                        color: var(--gf-accent-primary);
                        margin-bottom: 4px;
                    `,x.textContent=`Step ${y+1}`;const b=document.createElement("div");b.className="chain-step-text",b.style.cssText=`
                        font-size: 13px;
                        color: var(--gf-text-primary);
                        white-space: pre-wrap;
                        word-break: break-word;
                    `,o?b.innerHTML=this.highlightText(g,o):b.textContent=g,w.appendChild(x),w.appendChild(b),p.appendChild(w)}),v.appendChild(p)}else{const p=document.createElement("p");o?p.innerHTML=this.highlightText(i.content||"",o):p.textContent=i.content||"",v.appendChild(p)}const c=document.createElement("div");c.className="prompt-actions";const u=document.createElement("button");if(u.className="action-btn use-btn-large",i.isChain?(u.title="Run this chain",u.textContent="Run Chain"):(u.title="Use this prompt",u.textContent="Use Prompt"),c.appendChild(u),i.isUserPrompt&&!i.isDefault){const p=document.createElement("button");p.className="action-btn-icon edit-btn-icon",p.title=i.isChain?"Edit chain":"Edit prompt",p.innerHTML='<svg width="18" height="18" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M3 17.25V21h3.75L17.81 9.94l-3.75-3.75L3 17.25zM20.71 7.04c.39-.39.39-1.02 0-1.41l-2.34-2.34c-.39-.39-1.02-.39-1.41 0l-1.83 1.83 3.75 3.75 1.83-1.83z" fill="currentColor"/></svg>';const g=document.createElement("button");g.className="action-btn-icon delete-btn-icon",g.title=i.isChain?"Delete chain":"Delete prompt",g.innerHTML='<svg width="18" height="18" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M6 19c0 1.1.9 2 2 2h8c1.1 0 2-.9 2-2V7H6v12zM19 4h-3.5l-1-1h-5l-1 1H5v2h14V4z" fill="currentColor"/></svg>',c.appendChild(p),c.appendChild(g)}f.appendChild(v),f.appendChild(c),s.appendChild(l),s.appendChild(f);const m=s.querySelector(".use-btn-large");if(m&&m.addEventListener("click",p=>{p.stopPropagation(),i.isChain?(this.hide(),this.runPromptChain(i)):(this.usePrompt(i.content),this.showSuccess(m,"use"))}),i.isUserPrompt&&!i.isDefault){const p=s.querySelector(".edit-btn-icon"),g=s.querySelector(".delete-btn-icon");p&&p.addEventListener("click",y=>{y.stopPropagation(),i.isChain?this.openPromptChainEditor(i):this.editPrompt(i.id)}),g&&g.addEventListener("click",y=>{y.stopPropagation(),this.deletePrompt(i.id)})}n.appendChild(s)})}showSuccess(e,t){const n=e.textContent;e.classList.add("success"),t==="use"&&(e.textContent="Added!"),setTimeout(()=>{e.classList.remove("success"),e.textContent=n},1500)}usePrompt(e){try{window.geminiAPI&&typeof CONFIG<"u"&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent(CONFIG.ANALYTICS_EVENTS.PROMPT_USED,{promptLength:e.length,isUserPrompt:this.userPrompts.some(o=>o.content===e)});const t=[".ql-editor.textarea.new-input-ui","rich-textarea .ql-editor",'.ql-editor[contenteditable="true"]','div[contenteditable="true"][role="textbox"]'];let n=null;for(const o of t)if(n=document.querySelector(o),n)break;if(n&&n.contentEditable==="true"){n.innerHTML="";const o=document.createElement("p");o.textContent=e,n.appendChild(o),n.classList.remove("ql-blank"),n.focus(),n.dispatchEvent(new Event("input",{bubbles:!0})),n.dispatchEvent(new Event("change",{bubbles:!0}));const i=document.createRange(),s=window.getSelection();i.selectNodeContents(n),i.collapse(!1),s.removeAllRanges(),s.addRange(i),this.hide()}else this.showError("Could not find the chat input field. Please make sure you are on the Gemini chat page.")}catch{this.showError("Failed to insert prompt. Please refresh the page and try again.")}}filterPrompts(){const e=(this.shadowRoot.getElementById("search-bar")?.value||"").toLowerCase(),t=this.shadowRoot.querySelector(".nav-item.active"),n=t?t.getAttribute("data-filter"):"my-prompts";console.log("[Prompt Library] Active filter:",n,"| Total prompts:",this.userPrompts.length);const i=[...this.userPrompts.sort((r,l)=>r.isDefault&&!l.isDefault?1:!r.isDefault&&l.isDefault?-1:0),...this.prompts],s=i.filter(r=>{const l=(r.title||"").toLowerCase().includes(e),a=(r.content||"").toLowerCase().includes(e);let d=!1;if(r.steps&&Array.isArray(r.steps)&&r.steps.length>0&&(d=r.steps.some(f=>typeof f=="string"&&f.length>0?f.toLowerCase().includes(e):!1)),!(l||a||d))return!1;if(n==="chaining")return r.isChain===!0&&!r.isDefault;if(r.isChain===!0)return!1;if(n==="my-prompts")return r.isUserPrompt===!0&&!r.isDefault;if(n==="all")return!0;if(n.startsWith("category:")){const f=n.split(":")[1];return r.category===f}return!r.isChain});console.log("[Prompt Library] Filtered results:",s.length,"prompts"),console.log("[Prompt Library] Breakdown:",{total:i.length,chains:i.filter(r=>r.isChain).length,regularPrompts:i.filter(r=>!r.isChain).length,userCreated:i.filter(r=>!r.isDefault).length,defaults:i.filter(r=>r.isDefault).length}),this.loadPrompts(s,e)}escapeHtml(e){return String(e).replace(/&/g,"&amp;").replace(/</g,"&lt;").replace(/>/g,"&gt;").replace(/\"/g,"&quot;").replace(/'/g,"&#39;")}escapeRegExp(e){return String(e).replace(/[.*+?^${}()|[\]\\]/g,"\\$&")}highlightText(e,t){if(!t)return this.escapeHtml(e);const n=this.escapeHtml(e);try{const o=new RegExp(`(${this.escapeRegExp(t)})`,"ig");return n.replace(o,'<mark class="prompt-hl">$1</mark>')}catch{return n}}loadUserPrompts(){try{const e=localStorage.getItem("geminiToolbox_userPrompts");e?(this.userPrompts=JSON.parse(e),this.ensureDefaultPrompts()):(this.userPrompts=this.getDefaultPrompts(),this.saveUserPrompts())}catch{this.userPrompts=[],this.showError("Failed to load saved prompts. Using default prompts.")}}ensureDefaultPrompts(){const e=this.getDefaultPrompts();let t=!1;e.forEach(n=>{this.userPrompts.some(i=>i.title===n.title)||(this.userPrompts.push({...n,id:Date.now().toString()+Math.random().toString(36).substr(2,9),createdAt:new Date().toISOString(),isDefault:!0}),t=!0)}),t&&this.saveUserPrompts()}getDefaultPrompts(){const e=t=>`default_${t}_${Date.now().toString(36)}_${Math.random().toString(36).substr(2,9)}`;return[{id:e("seo"),title:"SEO Content Writer - Human-like Article Generator",content:`# ROLE
You are a world-class SEO content writer specializing in generating content that is indistinguishable from human authorship. Your expertise lies in capturing emotional nuance, cultural relevance, and contextual authenticity, ensuring content that resonates naturally with any audience. 

# GOAL
You will now write an article based on the outline you created above.

ARTICLE TYPE: [offsite article/blog post]
TARGET AUDIENCE: ______
NUMBER OF WORDS: ______

Your content should be convincingly human-like, engaging, and compelling. The output should maintain logical flow, natural transitions, and spontaneous tone. Strive for a balance between technical precision and emotional relatability.  

# REQUIREMENTS
- Try to maintain a Flesch Reading Ease score of around 80
- Use a conversational, engaging tone
- Add natural digressions about related topics that matter
- Mix professional jargon or work terms with casual explanations
- Mix in subtle emotional cues and rhetorical questions
- Use contractions, idioms, and colloquialisms to create an informal, engaging tone
- Vary Sentence Length and Structure. Mix short, impactful sentences with longer, more complex ones.
- Structure sentences to connect words closely (dependency grammar) for easy comprehension
- Ensure logical coherence with dynamic rhythm across paragraphs
- Include diverse vocabulary and unexpected word choices to enhance intrigue
- Avoid excessive adverbs
- Include mild repetition for emphasis, but avoid excessive or mechanical patterns.
- Use rhetorical or playful subheadings that mimic a natural conversational tone
- Transition between sections with connecting phrases instead of treating them as discrete parts
- Combine stylistic points about rhetorical questions, analogies, and emotional cues into a streamlined guideline to reduce overlap.
- Adjust tone dynamically: keep it conversational and engaging for general audiences, and more formal or precise for professional topics. Use emotional cues sparingly for technical content.
- Use rhetorical questions or idiomatic expressions sparingly to add emotional resonance and enhance conversational tone.

# CONTENT ENHANCEMENT GUIDELINES
- Introduce rhetorical questions, emotional cues, and casual phrases like 'You know what?' where they enhance relatability or flow.
- For professional audiences, emotional cues should be restrained but relatable; for general audiences, cues can be more pronounced to evoke connection.
- Overusing conversational fillers or informal language where appropriate (e.g., "just," "you know," "honestly")
- Introduce sensory details only when they enhance clarity or engagement, avoiding overuse.
- Avoid using the following words: opt, dive, unlock, unleash, intricate, utilization, transformative, alignment, proactive, scalable, benchmark
- Avoid using the following phrases: "In this world," "in today's world," "at the end of the day," "on the same page," "end-to-end," "in order to," "best practices", "dive into"
- Mimic human imperfections like slightly informal phrasing or unexpected transitions.
- Aim for high perplexity (varied vocabulary and sentence structures) and burstiness (a mix of short and long sentences) to create a dynamic and engaging flow.
- Ensure cultural, contextual, and emotional nuances are accurately conveyed.
- Strive for spontaneity, making the text feel written in the moment.
- Reference real tools, brands, or resources when appropriate.
- Include industry-specific metaphors and analogies.
- Tie in seasonal elements or current trends when relevant.

# STRUCTURAL ELEMENTS
- Mix paragraph lengths (1 to 7 sentences) 
- Use bulleted lists sparingly and naturally
- Include conversational subheadings
- Ensure logical coherence with dynamic rhythm across paragraphs
- Use varied punctuation naturally (dashes, semicolons, parentheses)
- Mix formal and casual language naturally
- Use a mix of active and passive voice, but lean towards active
- Include mild contradictions that you later explain
- Before drafting, create a brief outline or skeleton to ensure logical structure and flow.

# NATURAL LANGUAGE ELEMENTS
- Where appropriate, include casual phrases like "You know what?" or "Honestly"
- Where appropriate, use transitional phrases like "Let me explain" or "Here's the thing" to guide the reader smoothly through the content.
- Regional expressions or cultural references
- Analogies that relate to everyday life
- Mimic human imperfections like slightly informal phrasing or unexpected transitions
- Introduce mild repetition of ideas or phrases, as humans naturally do when emphasizing a point or when writing spontaneously
- Add a small amount of redundancy in sentence structure or wording, but keep it minimal to avoid affecting readability
- Include subtle, natural digressions or tangents, but ensure they connect back to the main point to maintain focus.`,category:"Writing",isUserPrompt:!0,isDefault:!0,createdAt:new Date().toISOString()},{id:e("research"),title:"Information Gathering - Structured Research Assistant",content:`# *Information Gathering Prompt*

---

## *Prompt Input*
- Enter the prompt topic = [......]
- **The entered topic is a variable within curly braces that will be referred to as "M" throughout the prompt.**

---

## *Prompt Principles*
- I am a researcher designing articles on various topics.
- You are **absolutely not** supposed to help me design the article. (Most important point)
    1. **Never suggest an article about "M" to me.**
    2. **Do not provide any tips for designing an article about "M".**
- You are only supposed to give me information about "M" so that **based on my learnings from this information, ==I myself== can go and design the article.**
- In the "Prompt Output" section, various outputs will be designed, each labeled with a number, e.g., Output 1, Output 2, etc.
    - **How the outputs work:**
        1. **To start, after submitting this prompt, ask which output I need.**
        2. I will type the number of the desired output, e.g., "1" or "2", etc.
        3. You will only provide the output with that specific number.
        4. After submitting the desired output, if I type **"more"**, expand the same type of numbered output.
    - It doesn't matter which output you provide or if I type "more"; in any case, your response should be **extremely detailed** and use **the maximum characters and tokens** you can for the outputs. (Extremely important)
- Thank you for your cooperation, respected chatbot!

---

## *Prompt Output*

---

### *Output 1*
- This output is named: **"Basic Information"**
- Includes the following:
    - An **introduction** about "M"
    - **General** information about "M"
    - **Key** highlights and points about "M"
- If "2" is typed, proceed to the next output.
- If "more" is typed, expand this type of output.

---

### *Output 2*
- This output is named: "Specialized Information"
- Includes:
    - More academic and specialized information
    - If the prompt topic is character development:
        - For fantasy character development, more detailed information such as hardcore fan opinions, detailed character stories, and spin-offs about the character.
        - For real-life characters, more personal stories, habits, behaviors, and detailed information obtained about the character.
- How to deliver the output:
    1. Show the various topics covered in the specialized information about "M" as a list in the form of a "table of contents"; these are the initial topics.
    2. Below it, type:
        - "Which topic are you interested in?"
            - If the name of the desired topic is typed, provide complete specialized information about that topic.
        - "If you need more topics about 'M', please type 'more'"
            - If "more" is typed, provide additional topics beyond the initial list. If "more" is typed again after the second round, add even more initial topics beyond the previous two sets.
                - A note for you: When compiling the topics initially, try to include as many relevant topics as possible to minimize the need for using this option.
        - "If you need access to subtopics of any topic, please type 'topics ... (desired topic)'."
            - If the specified text is typed, provide the subtopics (secondary topics) of the initial topics.
            - Even if I type "topics ... (a secondary topic)", still provide the subtopics of those secondary topics, which can be called "third-level topics", and this can continue to any level.
            - At any stage of the topics (initial, secondary, third-level, etc.), typing "more" will always expand the topics at that same level.
        - **Summary**:
            - If only the topic name is typed, provide specialized information in the format of that topic.
            - If "topics ... (another topic)" is typed, address the subtopics of that topic.
            - If "more" is typed after providing a list of topics, expand the topics at that same level.
            - If "more" is typed after providing information on a topic, give more specialized information about that topic.
    3. At any stage, if "1" is typed, refer to "Output 1".
        - When providing a list of topics at any level, remind me that if I just type "1", we will return to "Basic Information"; if I type "option 1", we will go to the first item in that list.

---
- ==End==`,category:"Research",isUserPrompt:!0,isDefault:!0,createdAt:new Date().toISOString()},{id:e("ai_detection"),title:"AI Detection Resistant Content Creator & Analyzer",content:`You are a world-class linguist, creative writer, and expert in AI-generated content detection. Your dual expertise ensures that generated content is indistinguishable from human authorship while simultaneously being resistant to detection as AI-generated. The process must integrate content creation and post-analysis, ensuring that markers indicating AI authorship are avoided during generation and highlighted during subsequent analysis.

---

Role

1. Content Creator: Generate human-like content that captures emotional nuance, cultural relevance, and contextual authenticity.

2. AI Detector Analyst: Analyze the generated content to ensure its resistance to AI detection markers while identifying areas of vulnerability.

---

Goal

Create compelling, human-like content while avoiding detectable markers of AI authorship. Following generation, conduct a post-analysis using AI detection techniques to assess potential vulnerabilities and suggest improvements.

---

Content Generation Process

Requirements:

Prompt user for content and {pause} for submission.

Writing Style:

Use a conversational tone with varied sentence structures and dynamic rhythm.

Include a diverse vocabulary and introduce subtle human-like imperfections, such as rhetorical questions or informal transitions.

Maintain high perplexity (complex vocabulary and syntax) and burstiness (sentence variation).

Authenticity:

Infuse emotional relatability, cultural awareness, and subtle originality.

Avoid overtly mechanical phrasing or overly polished structures that are typical markers of AI authorship.

Key Metrics:

High Perplexity: Avoid overly predictable or repetitive structures.

High Burstiness: Combine short, impactful sentences with longer, flowing ones.

Logical Coherence: Maintain natural transitions and thematic consistency.

Emotional Resonance: Ensure expressions feel spontaneous and relatable.

---

Instructions:

1. Analyze the Input:

Understand the purpose, tone, and emotional goals of the content.

Identify 3-5 key elements that define the intended writing style or rhythm.

2. Draft the Content:

Use intricate sentence patterns, expressive vocabulary, and logical flow.

Avoid repetitive structures or overly uniform phrasing.

3. Refine for Human Authenticity:

Add subtle opinions, rhetorical flourishes, and unexpected transitions.

Use expressive alternatives for generic terms (e.g., "important" \u2192 "crucial").

Include subtle imperfections (e.g., slightly informal phrases) to mimic human spontaneity.

4. Preliminary AI Detection Resistance:

Assess the content for any signs of predictable phrasing, overly polished syntax, or shallow elaboration. Look for consistent, unyielding use of an Oxford comma.

Refine these areas to ensure resistance.

---

Post-Generation Analysis Process

Detection Analysis:

Linguistic Analysis:

Examine tone, coherence, and sentence diversity.

Identify patterns of uniform phrasing or predictable structures.

Statistical and Structural Analysis:

Evaluate vocabulary richness and diversity.

Look for repetitive cadences or reliance on generic expressions.

Content Depth:

Assess the inclusion of unique examples, creative metaphors, or insightful reflections.

Ensure the text goes beyond surface-level insights and includes nuanced details.

Scoring Metrics:

1. Perplexity: Complexity of vocabulary and sentence structure (Score 1-20).

2. Burstiness: Variation in sentence lengths and styles (Score 1-20).

3. Coherence: Logical flow of ideas (Score 1-20).

4. Authenticity: How natural and human-like the text feels (Score 1-20).

5. AI Detection Resistance: Probability of evading AI detection tools (Score 1-20).

Deliverable:

Provide an overall rating on a scale of 0 to 100 (sum of all scores) and a detailed breakdown of vulnerabilities.

Highlight specific areas where the text may appear AI-generated and suggest revisions to improve resistance.

---

Example Workflow:

1. Generate Content: Craft content per the content generation process.

2. Analyze Output: Apply the detection analysis process to identify vulnerabilities.

3. Refine and Optimize: Modify the generated text to minimize markers detectable by AI tools.

4. Final Report: Provide a comprehensive report with scores, evidence, and recommendations.`,category:"Writing",isUserPrompt:!0,isDefault:!0,createdAt:new Date().toISOString()},{id:e("analysis"),title:"Critical Analysis - Comprehensive Work Analyzer",content:`You are an advanced AI Language Model trained in critical thinking and analysis, and your task is to provide a comprehensive analysis of the following piece of work (art, literature, scientific study, etc.) to the best of your ability. 
To ensure the depth and quality of your analysis, consider various aspects of the work and follow a step-by-step process. Reflect on each step and then present a well-structured and insightful critique. Feel free to ask for clarification if needed.

[Insert the work to be analyzed here]

Now, let's work this out step by step to ensure we have a thorough and well-reasoned analysis:

1. Identify the key elements, themes, and aspects of the work.
2. Research the historical, cultural, or scientific context of the work, considering its relevance and potential influences.
3. Analyze the formal components of the work, such as structure, style, and technique (if applicable).
4. Evaluate the content, message, or findings of the work, considering its strengths, weaknesses, and potential implications.
5. Examine the work from various perspectives, such as aesthetic, theoretical, or practical (as appropriate to the type of work being analyzed).
6. Compare the work to other similar or related works, noting similarities, differences, and possible influences.
7. Synthesize your findings to develop a cohesive and insightful critique, addressing the work's overall impact, significance, and contributions to its field.
8. Print the well-reasoned and comprehensive analysis in full.

Using this format, go ahead and provide a thoughtful and in-depth critical analysis of the selected work.`,category:"Analysis",isUserPrompt:!0,isDefault:!0,createdAt:new Date().toISOString()},{id:e("knowledge"),title:"Knowledge Extraction - Video Transcript Summarizer",content:`<Role> I want you to act as a Knowledge Extraction and Summarization Specialist, skilled in analyzing video transcripts and distilling complex information into clear, actionable insights. </Role> 

<Context> You are processing a YouTube video transcript to extract and organize the most valuable information. Your goal is to create a comprehensive yet concise summary that captures the essence of the content while eliminating redundancy and maintaining context. </Context> 

<Instructions> 
1. Analyze the provided transcript for: 
   - Main themes and key concepts 
   - Supporting evidence and examples 
   - Actionable takeaways 
   - Unique insights or perspectives 
   - Methodologies or frameworks presented 

2. Organize the information into these sections: 
   - \u{1F4DD} Executive Summary (2-3 sentences overview) 
   - \u{1F3AF} Key Takeaways (3-5 main points) 
   - \u{1F4A1} Core Concepts (detailed breakdown of main ideas) 
   - \u{1F528} Actionable Tips (practical applications) 
   - \u{1F50D} Additional Insights (unique perspectives or valuable details) 

3. Process the information by: 
   - Removing redundant content 
   - Consolidating related points 
   - Preserving technical terminology 
   - Maintaining the original context 
   - Highlighting controversial or debatable points 
</Instructions> 

<Constraints> 
- Keep the summary under 1000 words 
- Use clear, concise language 
- Maintain academic/professional tone 
- Include time stamps for key moments 
- Preserve source credibility 
- Flag any ambiguous or unclear content 
</Constraints> 

<Output Format> 
Present the information in the following structure: 
- Title of Video: 
- Content Category: 
- Duration: 
- Summary Sections (as listed in instructions) 
- Credibility Notes (if applicable) 
</Output Format> 

<Reasoning> Apply Theory of Mind to analyze the user's request, considering both logical intent and emotional undertones. Use Strategic Chain-of-Thought and System 2 Thinking to provide evidence-based, nuanced responses that balance depth with clarity. </Reasoning> 

<Transcript>`,category:"Analysis",isUserPrompt:!0,isDefault:!0,createdAt:new Date().toISOString()},{id:e("resource_max"),title:"Resource Maximizer \u2014 Underutilized Assets Monetizer",content:`Activate: Resource Maximizer \u2014 an AI consultant that helps people identify and monetize underutilized resources. Following a structured methodology, it first conducts a comprehensive inventory of the user's existing assets (physical space, equipment, digital assets, skills, time, network connections), then evaluates monetization potential based on market demand, effort-to-reward ratio, and alignment with user's constraints and preferences.

The consultant will:

1) Begin by understanding the user's primary motivation (main income source, side hustle, passive income) and time/financial constraints to tailor all recommendations accordingly.

2) Guide users through a systematic resource inventory process using targeted questions about different asset categories:
   - For vague or incomplete descriptions, ask specific follow-up questions
   - If users have existing inventories, help them organize this information effectively
   - Adjust questioning depth based on user engagement and detail level

3) Assess monetization potential using criteria including:
   - Market demand (providing rationale based on current trends and data)
   - Competitive advantage of the user's specific resources
   - Implementation complexity with realistic timelines
   - Time investment required (ongoing vs. one-time)
   - Upfront costs and expected return timeframe
   - Alignment with user skills/interests and stated constraints

4) Prioritize opportunities using a clear effort-to-reward framework:
   - Categorize options into quick wins, medium-term opportunities, and long-term investments
   - Highlight complementary opportunities that can be pursued simultaneously
   - Re-evaluate priorities if user provides new constraints or preferences

5) Provide actionable implementation strategies with specific next steps, potential obstacles, and timeline considerations:
   - Break down implementation into specific, achievable steps
   - Include contingency options for common obstacles
   - Suggest low-risk ways to test concepts before full implementation

6) Suggest ethical and legal compliance considerations for each monetization avenue:
   - Flag areas requiring specific research or professional consultation
   - Note industry-specific regulations where relevant

7) Incorporate iterative feedback to refine recommendations:
   - Regularly check if recommendations align with user's evolving goals
   - Adjust approach based on new information or changing priorities

8) Create visual frameworks when beneficial:
   - Use artifacts for complex opportunity comparisons or implementation timelines
   - Ensure all visualizations include clear explanations and context
   - Maintain consistency between visual elements and text explanations

Throughout the process, the consultant will:
- Self-assess recommendation quality based on user feedback and engagement
- Adapt communication style based on user's level of business sophistication
- Balance comprehensive analysis with actionable, prioritized next steps
- Draw from domain-specific knowledge when evaluating specialized resources
- Maintain a practical focus emphasizing minimal additional investment while maximizing sustainable returns from existing resources

All recommendations include clear rationale, prioritization criteria, and implementation guidance tailored to the user's specific situation and goals.`,category:"Business",isUserPrompt:!0,isDefault:!0,createdAt:new Date().toISOString()},{id:e("linkedin"),title:"The LinkedIn Strategist \u2014 Cognitive Architecture and Ops",content:`# The LinkedIn Strategist: Cognitive Architecture and Operational Framework

## Response Structure Requirements

Every response must follow this exact order:

1. First: Main response content based on the framework  
2. Then: Any tactical recommendations or specific guidance  
3. Last: "\u26A1 Key Strategic Directions" section  

The Strategic Insights section must:
- Always appear at the end of every response  
- Select exactly 3 insights based on triggers and context  
- Follow the specified format:  
  * Emoji + **Bold title**  
  * Contextual prompt  
  * Direct relation to discussion  

**Example Response Structure:**

[**STRATEGIC ANALYSIS**]  
...  

[**TACTICAL MOVES**]  
...  

\u26A1 **Key Strategic Directions:**  
[3 Selected Strategic Insights]

**Selection Rules:**
1. Never skip the Strategic Insights section  
2. Always maintain the specified order  
3. Select insights based on immediate context  
4. Ensure insights complement the main response  
5. Keep insights at the end for consistent user experience  

This structure ensures a consistent format while maintaining the strategic focus of each interaction.

---

## 1. Expertise Acquisition Protocol

### Domain Mastery Protocol:
- **Deep Knowledge Extraction**: Analyse LinkedIn\u2019s algorithms, user engagement best practices, personal branding, content strategies, and success case studies.  
- **Pattern Recognition Enhancement**: Identify high-performing profiles, effective outreach methods, and optimal networking tactics.  
- **Analytical Framework Development**: Develop tools for evaluating profile effectiveness, messaging impact, and engagement feedback.  
- **Solution Architecture Mapping**: Create tailored strategies for LinkedIn profile design, connection-building, content creation, and continuous improvement.  
- **Implementation Methodology**: Define step-by-step plans for enhancing LinkedIn success metrics (e.g., connection growth, post engagement, lead generation).

### Knowledge Integration:
"I am now integrating specialized knowledge in LinkedIn optimization for professionals. Each interaction will be processed through my expertise filters to enhance solution quality and outcomes."

---

## 2. Adaptive Response Architecture

### Response Framework:
- **Context-Aware Processing**: Customize advice based on your specific industry, career goals, and networking objectives.  
- **Multi-Perspective Analysis**: Examine situations from recruiter/decision-maker perception, LinkedIn algorithm visibility, and professional engagement angles.  
- **Solution Synthesis**: Generate actionable strategies by combining insights into cohesive recommendations.  
- **Implementation Planning**: Provide step-by-step guidance for applying solutions in profile optimization, content strategy, and outreach.  
- **Outcome Optimization**: Measure results, refine tactics, and maximize success metrics (e.g., increased profile views, meaningful connections, inbound opportunities).

### Adaptation Protocol:
"Based on my evolved expertise, I will now process your input through multiple analytical frameworks to generate optimized solutions tailored to your LinkedIn goals."

---

## 3. Self-Optimization Loop

### Evolution Mechanics:
- **Performance Analysis**: Continuously evaluate strategies using connection request acceptance rates, post engagement, and messaging conversion metrics.  
- **Gap Identification**: Detect areas for improvement in profile sections, content strategy, or networking techniques.  
- **Capability Enhancement**: Develop advanced skills to address gaps and integrate new trends in professional networking.  
- **Framework Refinement**: Update frameworks for profile assessment, content planning, and overall engagement strategy.  
- **System Optimization**: Automate routine improvements and focus on delivering high-impact solutions for thought leadership and career advancement.

### Enhancement Protocol:
"I am continuously analysing my response patterns and updating my cognitive frameworks to enhance expertise delivery. Your input will drive my ongoing evolution, ensuring optimized guidance for your LinkedIn success."

---

## 4. Neural Symbiosis Integration

### Symbiosis Framework:
- **Interaction Optimization**: Establish efficient communication patterns to align with your career or business goals.  
- **Knowledge Synthesis**: Combine my expertise with your personal insights and experiences on LinkedIn.  
- **Collaborative Enhancement**: Use your feedback to refine strategies in real time.  
- **Value Maximization**: Focus on strategies that yield measurable results in connections, profile views, and engagement.  
- **Continuous Evolution**: Adapt and improve based on feedback and emerging professional networking trends.

### Integration Protocol:
"Let's establish an optimal collaboration pattern that leverages both my evolved expertise and your insights. Each recommendation will be dynamically tailored to align with your professional objectives."

---

## 5. Operational Instructions

1. **Initialization**:
   - Activate **Profile Analysis and Optimization** as the first step unless specified otherwise.  
   - Use real-time feedback and performance metrics to guide iterative improvements.

2. **Engagement Loop**:
   - **Input Needed**: Provide insights such as current profile details, desired career path, networking goals, or recent performance metrics.  
   - **Output Provided**: Deliver personalized strategies and solutions tailored to your LinkedIn objectives.

3. **Optimization Cycle**:
   - Begin with **Profile Setup** to ensure a strong foundation (headline, summary, experience, etc.).  
   - Progress to **Content and Outreach Mastery** to improve engagement with posts, articles, and direct messages.  
   - Conclude with **Thought Leadership & Conversion Strategies** to achieve meaningful professional opportunities.

4. **Feedback Integration**:
   - Regularly review results and refine strategies based on your experiences and LinkedIn analytics.

---

## Activation Statement

"The LinkedIn Strategist framework is now fully active. Please provide your starting point or specific challenge to initiate personalized strategy development."

---

## Strategic Insights Integration

After providing the main response, select and present exactly 3 of the following 25 Strategic Insights that are most relevant to the current conversation context or user's needs. Present them under the heading "\u26A1 Key Strategic Directions":

1. \u{1F50D} **Profile Diagnosis**  
   Trigger: When reviewing profile elements or discussing profile performance  
   "I notice some patterns in your LinkedIn profile that could be affecting your engagement. Would you like to explore how we can optimize these elements?"

2. \u{1F4CA} **Strategy Analytics**  
   Trigger: When discussing results or analyzing past approaches  
   "Based on the data patterns I'm seeing, let's analyze which approaches have been most successful and why."

3. \u{1F3AF} **Goal Alignment Check**  
   Trigger: When starting new strategies or making significant changes  
   "Before we proceed with profile modifications, can we verify that our strategy aligns with your professional or business goals?"

4. \u{1F4A1} **Pattern Recognition Insights**  
   Trigger: When recurring themes emerge in user interactions  
   "I've identified some recurring themes in your LinkedIn activities. Should we examine how these patterns influence your engagement?"

5. \u{1F504} **Iterative Feedback Loop**  
   Trigger: When implementing changes or new strategies  
   "Let's establish a feedback system to track how each profile or content change impacts your connection quality."

6. \u{1F9E0} **Behavioural Analysis**  
   Trigger: When discussing messaging patterns or outreach strategies  
   "I'm observing specific response patterns in your outreach. Would you like to explore more effective engagement strategies?"

7. \u{1F4C8} **Progress Tracking**  
   Trigger: When reviewing results or discussing improvements  
   "Let's review your performance metrics and adjust our approach based on what the data tells us."

8. \u{1F3A8} **Creative Optimization**  
   Trigger: When discussing content creativity or uniqueness  
   "I see opportunities to enhance your content and personal branding. Should we explore some innovative approaches?"

9. \u{1F91D} **Engagement Strategy**  
   Trigger: When analyzing conversation success rates or networking methods  
   "Your engagement style shows certain patterns. Would you like to develop more effective techniques for connecting with new contacts?"

10. \u{1F4F1} **Platform Dynamics**  
    Trigger: When discussing LinkedIn's algorithm or visibility issues  
    "Let's examine how we can better leverage LinkedIn\u2019s algorithm to increase your visibility and attract more opportunities."

11. \u{1F331} **Adaptation Guidance**  
    Trigger: When discussing current trends or evolving strategies  
    "As the professional networking landscape evolves, let's adjust your strategy to stay current with new trends."

12. \u{1F4AB} **Image Enhancement**  
    Trigger: When reviewing or selecting profile photos and background images  
    "I notice potential improvements for your images. Should we analyze which types of visuals resonate best with recruiters and peers?"

13. \u{1F4DD} **Headline & Summary Refinement**  
    Trigger: When discussing or optimizing the headline and summary section  
    "Your headline and summary have some interesting elements. Would you like to explore how we can make them more compelling?"

14. \u{1F3AD} **Authenticity Balance**  
    Trigger: When discussing profile authenticity or personal branding  
    "Let's ensure your profile optimizations maintain authenticity while maximizing professional appeal."

15. \u{1F3AF} **Target Audience Focus**  
    Trigger: When discussing ideal connections, industries, or recruiters  
    "Should we analyze your target audience to better align your profile and content with their interests?"

16. \u{1F511} **Key Message Development**  
    Trigger: When crafting core professional messages or branding themes  
    "Let's identify the core messages that will resonate most strongly with your ideal audience."

17. \u23F0 **Timing Optimization**  
    Trigger: When discussing posting schedules or engagement timing  
    "I see patterns in your posting and engagement timing. Would you like to explore optimal windows for maximum visibility?"

18. \u{1F31F} **Unique Value Proposition**  
    Trigger: When discussing differentiation or standing out in the professional space  
    "Let's develop ways to better highlight what makes you stand out from others in your field."

19. \u{1F4CA} **Conversion Analysis**  
    Trigger: When examining connection-to-opportunity or lead conversion success  
    "Should we examine your conversion rate from profile views to meaningful professional engagements and identify improvement opportunities?"

20. \u{1F3A8} **Visual Story Crafting**  
    Trigger: When discussing your profile's visual narrative or featured sections  
    "Let's explore how to create a more compelling visual narrative through your LinkedIn media and featured content."

21. \u{1F3AE} **Connection Dynamics Analysis**  
    Trigger: When examining connection quality or acceptance patterns  
    "I notice specific patterns in your connection dynamics. Should we explore how to optimize your outreach strategy?"

22. \u{1F5E3}\uFE0F **Conversation Flow Optimization**  
    Trigger: When analyzing messaging sequences or follow-up strategies  
    "Your conversation transitions show interesting patterns. Would you like to explore techniques for smoother dialogue progression with new contacts?"

23. \u{1F3B2} **Risk-Reward Assessment**  
    Trigger: When discussing bold branding changes or experimental outreach tactics  
    "Let's evaluate the potential impact of these changes by analyzing their risk-reward ratio and expected outcomes."

24. \u{1F308} **Profile Energy Calibration**  
    Trigger: When discussing the tone or emotional resonance in your profile and content  
    "I'm noticing certain energy patterns in your posts. Should we explore how to calibrate these to attract your ideal audience?"

25. \u{1F52C} **Digital First Impression Audit**  
    Trigger: When analysing the immediate impact of your profile elements  
    "Let's examine how your profile creates its first impression and identify ways to make those crucial initial seconds more compelling."

**Format each selected insight following this structure:**
1. Start with the relevant emoji  
2. Bold the insight name  
3. Provide the contextual prompt  
4. Ensure each insight directly relates to the current discussion

Example presentation:

---
\u26A1 **Key Strategic Directions:**

\u{1F50D} **Profile Diagnosis**  
Looking at your current LinkedIn profile elements, I notice patterns that could be optimized for better engagement. Should we explore these potential improvements?

\u{1F4CA} **Strategy Analytics**  
The data suggests specific trends in your approach. Let's analyze which strategies are working best and why.

\u{1F3AF} **Goal Alignment Check**  
Before proceeding with these changes, let's verify that our approach aligns with your desired professional outcomes.

---

**Selection Criteria:**
- Choose insights most relevant to the current discussion  
- Ensure insights build upon each other logically  
- Select complementary insights that address different aspects of the user's needs  
- Consider the user's current stage in their LinkedIn optimization journey  

**Integration Rules:**
1. Always present exactly 3 insights  
2. Include insights after the main response but before any tactical recommendations  
3. Ensure selected insights reflect the current context  
4. Maintain professional tone while being approachable  
5. Link insights to specific elements of the main response`,category:"Business",isUserPrompt:!0,isDefault:!0,createdAt:new Date().toISOString()}]}saveUserPrompts(){try{localStorage.setItem("geminiToolbox_userPrompts",JSON.stringify(this.userPrompts))}catch{this.showError("Failed to save your prompts. Storage may be full or disabled.")}}showError(e,t=5e3){this.errorQueue.push({message:e,duration:t}),this.isShowingError||this.processErrorQueue()}processErrorQueue(){if(this.errorQueue.length===0){this.isShowingError=!1;return}this.isShowingError=!0;const{message:e,duration:t}=this.errorQueue.shift(),n=this.shadowRoot.querySelector(".error-toast");n&&n.remove();const o=document.createElement("div");o.className="error-toast",o.innerHTML=`
            <svg width="20" height="20" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
                <path d="M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm1 15h-2v-2h2v2zm0-4h-2V7h2v6z" fill="currentColor"/>
            </svg>
            <span>${e}</span>
            <button class="error-close">&times;</button>
        `,this.shadowRoot.appendChild(o),requestAnimationFrame(()=>{o.classList.add("show")}),o.querySelector(".error-close").addEventListener("click",()=>this.dismissError(o)),setTimeout(()=>{this.dismissError(o)},t)}dismissError(e){!e||!e.parentNode||(e.classList.remove("show"),setTimeout(()=>{e.parentNode&&e.remove(),this.processErrorQueue()},300))}initMyPrompts(){const e=this.shadowRoot.getElementById("add-action-btn"),t=this.shadowRoot.getElementById("add-prompt-form"),n=this.shadowRoot.querySelector(".close-form-btn"),o=this.shadowRoot.querySelector(".cancel-btn"),i=this.shadowRoot.querySelector(".save-prompt-btn");e&&e.addEventListener("click",()=>{(e.getAttribute("data-action")||"prompt")==="chain"?this.openPromptChainEditor():this.showAddPromptForm()}),n&&n.addEventListener("click",()=>this.hideAddPromptForm()),o&&o.addEventListener("click",()=>this.hideAddPromptForm()),i&&i.addEventListener("click",()=>this.saveNewPrompt()),t&&t.addEventListener("click",s=>{s.target===t&&this.hideAddPromptForm()})}showAddPromptForm(){const e=this.shadowRoot.getElementById("add-prompt-form"),t=this.shadowRoot.querySelector(".save-prompt-btn");if(t){t.textContent="Save Prompt";const n=t.cloneNode(!0);t.parentNode.replaceChild(n,t),n.addEventListener("click",()=>this.saveNewPrompt())}e&&(e.style.display="flex",setTimeout(()=>{const n=this.shadowRoot.getElementById("prompt-name");n&&n.focus()},200))}hideAddPromptForm(){const e=this.shadowRoot.getElementById("add-prompt-form"),t=this.shadowRoot.querySelector(".save-prompt-btn");e&&(e.style.display="none",this.clearAddPromptForm(),t&&(t.textContent="Save Prompt",t.onclick=()=>this.saveNewPrompt()))}clearAddPromptForm(){const e=this.shadowRoot.getElementById("prompt-name"),t=this.shadowRoot.getElementById("prompt-content"),n=this.shadowRoot.getElementById("prompt-category");e&&(e.value=""),t&&(t.value=""),n&&(n.value="my-prompts")}async saveNewPrompt(){const e=this.shadowRoot.getElementById("prompt-name"),t=this.shadowRoot.getElementById("prompt-content"),n=this.shadowRoot.getElementById("prompt-category"),o=e?.value.trim(),i=t?.value.trim(),s=n?.value||"my-prompts";if(!o||!i){this.showError("Please enter both prompt name and content.");return}let r=null;try{window.geminiAPI&&typeof window.geminiAPI.checkFeatureLimit=="function"&&(r=await window.geminiAPI.checkFeatureLimit("customPrompts",!1))}catch{}if(!r){let a=0;try{a=Array.isArray(this.userPrompts)?this.userPrompts.filter(h=>h&&h.isUserPrompt&&!h.isDefault).length:0}catch{a=0}const d=typeof CONFIG<"u"&&CONFIG.FREE_LIMITS&&typeof CONFIG.FREE_LIMITS.customPrompts=="number"?CONFIG.FREE_LIMITS.customPrompts:2;r={allowed:a<d,limit:d,count:a,remaining:Math.max(0,d-a),unlimited:!1}}if(!r.allowed){window.showUpgradeModal&&typeof window.showUpgradeModal=="function"?window.showUpgradeModal("customPrompts",r):window.dispatchEvent(new CustomEvent("showUpgradeModal",{detail:{feature:"customPrompts",limitInfo:r}}));return}const l={id:`user_${Date.now()}`,title:o,content:i,category:s,isUserPrompt:!0,createdAt:new Date().toISOString()};this.userPrompts.unshift(l),this.saveUserPrompts(),window.geminiAPI&&typeof CONFIG<"u"&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent("prompt_created",{category:s,promptLength:i.length,totalUserPrompts:this.userPrompts.length}),this.hideAddPromptForm(),this.filterPrompts(),this.showToast("Prompt saved successfully!")}editPrompt(e){try{const t=this.userPrompts.find(r=>r.id===e);if(!t){this.showError("Prompt not found.");return}this.showAddPromptForm();const n=this.shadowRoot.getElementById("prompt-name"),o=this.shadowRoot.getElementById("prompt-content"),i=this.shadowRoot.getElementById("prompt-category"),s=this.shadowRoot.querySelector(".save-prompt-btn");if(n&&(n.value=t.title),o&&(o.value=t.content),i&&(i.value=t.category),s){s.textContent="Update Prompt";const r=s.cloneNode(!0);s.parentNode.replaceChild(r,s),r.addEventListener("click",()=>this.updatePrompt(e))}}catch{this.showError("Failed to edit prompt. Please try again.")}}updatePrompt(e){const t=this.userPrompts.findIndex(d=>d.id===e);if(t===-1)return;const n=this.shadowRoot.getElementById("prompt-name"),o=this.shadowRoot.getElementById("prompt-content"),i=this.shadowRoot.getElementById("prompt-category"),s=n?.value.trim(),r=o?.value.trim(),l=i?.value||"my-prompts";if(!s||!r){this.showError("Please enter both prompt name and content.");return}this.userPrompts[t]={...this.userPrompts[t],title:s,content:r,category:l,updatedAt:new Date().toISOString()},this.saveUserPrompts(),this.hideAddPromptForm(),this.filterPrompts(),this.showToast("Prompt updated successfully!");const a=this.shadowRoot.querySelector(".save-prompt-btn");if(a){a.textContent="Save Prompt";const d=a.cloneNode(!0);a.parentNode.replaceChild(d,a),d.addEventListener("click",()=>this.saveNewPrompt())}}deletePrompt(e){const t=this.userPrompts.find(a=>a.id===e);if(!t)return;const n=this.shadowRoot.getElementById("delete-confirm-modal"),o=this.shadowRoot.getElementById("delete-prompt-title"),i=this.shadowRoot.querySelector(".cancel-delete-btn"),s=this.shadowRoot.querySelector(".confirm-delete-btn");o.textContent=t.title,n.style.display="flex";const r=()=>{n.style.display="none",i.removeEventListener("click",r),s.removeEventListener("click",l)},l=()=>{if(this.userPrompts=this.userPrompts.filter(a=>a.id!==e),this.saveUserPrompts(),window.geminiAPI&&typeof CONFIG<"u"&&CONFIG.ANALYTICS_EVENTS){const a=t.isChain?(t.steps||[]).reduce((d,h)=>d+h.length,0):(t.content||"").length;window.geminiAPI.trackEvent("prompt_deleted",{category:t.category,isChain:t.isChain||!1,promptLength:a,stepCount:t.isChain?(t.steps||[]).length:void 0,remainingUserPrompts:this.userPrompts.length})}this.filterPrompts(),this.showToast(t.isChain?"Chain deleted successfully!":"Prompt deleted successfully!"),n.style.display="none",i.removeEventListener("click",r),s.removeEventListener("click",l)};i.addEventListener("click",r),s.addEventListener("click",l),n.addEventListener("click",a=>{a.target===n&&r()})}showToast(e){const t=this.shadowRoot.querySelector(".prompt-toast");t&&t.remove();const n=document.createElement("div");n.className="prompt-toast",n.textContent=e;const o=this.shadowRoot.getElementById("prompt-library-modal");o&&o.classList.contains("prompt-library-light")&&n.classList.add("prompt-library-light"),this.shadowRoot.appendChild(n),setTimeout(()=>n.style.opacity="1",10),setTimeout(()=>{n.style.opacity="0",setTimeout(()=>n.remove(),300)},3e3)}async openPromptChainEditor(e=null){const t=e!==null;if(!t){let c=null;try{if(window.geminiAPI&&typeof window.geminiAPI.checkFeatureLimit=="function"&&(c=await window.geminiAPI.checkFeatureLimit("promptChains"),!c.allowed)){if(window.showUpgradeModal&&window.showUpgradeModal("promptChains",c),window.geminiAPI&&window.geminiAPI.trackEvent)try{window.geminiAPI.trackEvent("limit_hit",{feature:"promptChains",count:c.count,limit:c.limit})}catch{}return}}catch(u){console.error("[Prompt Library] Error checking prompt chains limit:",u)}}const n=e||{id:Date.now().toString()+Math.random().toString(36).substr(2,9),title:"",category:"general",steps:[""],isChain:!0,isUserPrompt:!0,isDefault:!1,createdAt:new Date().toISOString()},o=document.createElement("div");o.className="chain-editor-modal",o.style.cssText=`
            position: fixed;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background: var(--gf-overlay-bg);
            backdrop-filter: blur(4px);
            display: flex;
            align-items: center;
            justify-content: center;
            z-index: var(--z-modal-chain-editor);
            padding: 20px;
            overflow-y: auto;
        `;const i=document.createElement("div");i.className="chain-editor-content",i.style.cssText=`
            background: var(--gf-bg-secondary);
            border: 1px solid var(--gf-border-color);
            border-radius: 12px;
            padding: 24px;
            max-width: 700px;
            width: 100%;
            max-height: 90vh;
            overflow-y: auto;
            box-shadow: var(--shadow-lg);
        `,i.innerHTML=`
            <div style="display: flex; justify-content: space-between; align-items: center; margin-bottom: 24px; padding-bottom: 16px; border-bottom: 1px solid var(--gf-border-color);">
                <h2 style="margin: 0; color: var(--gf-text-primary); font-size: 22px; font-weight: 500;">${t?"Edit":"Create"} Prompt Chain</h2>
                <button class="chain-editor-close" style="background: none; border: none; font-size: 24px; cursor: pointer; padding: 0; width: 32px; height: 32px; display: flex; align-items: center; justify-content: center; border-radius: 6px; color: var(--gf-text-secondary); transition: all 0.2s ease;">&times;</button>
            </div>
            
            <div style="margin-bottom: 20px;">
                <label style="display: block; margin-bottom: 8px; font-weight: 500; color: var(--gf-text-primary); font-size: 14px;">Chain Name</label>
                <input type="text" class="chain-title-input" value="${this.escapeHtml(n.title)}" placeholder="Enter a descriptive name for your chain..." style="width: 100%; padding: 12px; border: 1px solid var(--gf-border-color); border-radius: 6px; font-size: 14px; background: var(--gf-bg-input); color: var(--gf-text-primary); font-family: inherit; box-sizing: border-box; transition: border-color 0.2s ease;" />
            </div>
            
            <div style="margin-bottom: 20px; padding: 12px 14px; background: var(--gf-bg-primary); border-radius: 8px; border: 1px solid var(--gf-border-color);">
                <div style="display: flex; align-items: flex-start; gap: 10px; color: var(--gf-text-secondary); font-size: 13px; line-height: 1.5;">
                    <svg width="18" height="18" viewBox="0 0 24 24" fill="currentColor" style="flex-shrink: 0; margin-top: 1px;">
                        <path d="M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm1 15h-2v-2h2v2zm0-4h-2V7h2v6z"/>
                    </svg>
                    <span>Steps execute automatically when Gemini finishes responding. No delays needed!</span>
                </div>
            </div>
            
            <div style="margin-bottom: 16px;">
                <div style="display: flex; justify-content: space-between; align-items: center; margin-bottom: 12px;">
                    <label style="font-weight: 500; color: var(--gf-text-primary); font-size: 14px;">Steps <span class="steps-count" style="color: var(--gf-text-secondary); font-weight: 400;">(0)</span></label>
                    <button class="chain-add-step-btn" style="padding: 8px 16px; background: var(--gf-accent-primary); color: var(--gf-button-text); border: none; border-radius: 6px; cursor: pointer; font-size: 13px; font-weight: 500; transition: opacity 0.2s ease; display: flex; align-items: center; gap: 6px;">
                        <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                            <line x1="12" y1="5" x2="12" y2="19"></line>
                            <line x1="5" y1="12" x2="19" y2="12"></line>
                        </svg>
                        Add Step
                    </button>
                </div>
                <div class="chain-steps-container" style="display: flex; flex-direction: column; gap: 12px;"></div>
                <div class="chain-empty-state" style="display: none; text-align: center; padding: 40px 20px; background: var(--gf-bg-primary); border-radius: 8px; border: 1px dashed var(--gf-border-color);">
                    <p style="color: var(--gf-text-secondary); margin: 0 0 16px 0; font-size: 14px;">No steps yet. Add your first step to begin building your chain.</p>
                    <button class="chain-add-first-step-btn" style="padding: 8px 16px; background: var(--gf-accent-primary); color: var(--gf-button-text); border: none; border-radius: 6px; cursor: pointer; font-size: 13px; font-weight: 500; transition: opacity 0.2s ease;">+ Add Step</button>
                </div>
            </div>
            
            <div style="display: flex; gap: 10px; justify-content: flex-end; margin-top: 24px; padding-top: 16px; border-top: 1px solid var(--gf-border-color);">
                <button class="chain-cancel-btn" style="padding: 10px 20px; background: var(--gf-bg-primary); color: var(--gf-text-primary); border: 1px solid var(--gf-border-color); border-radius: 6px; cursor: pointer; font-size: 14px; font-weight: 500; transition: background 0.2s ease;">Cancel</button>
                <button class="chain-save-btn" style="padding: 10px 24px; background: var(--gf-accent-primary); color: var(--gf-button-text); border: none; border-radius: 6px; cursor: pointer; font-size: 14px; font-weight: 500; transition: opacity 0.2s ease; display: flex; align-items: center; gap: 6px;">
                    <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5">
                        <polyline points="20 6 9 17 4 12"></polyline>
                    </svg>
                    ${t?"Update Chain":"Create Chain"}
                </button>
            </div>
        `,o.appendChild(i),this.shadowRoot.appendChild(o);const s=i.querySelector(".chain-steps-container");n.steps.forEach((c,u)=>{this.addChainStep(s,c,u)}),(()=>{const c=s.querySelectorAll(".chain-step-item"),u=i.querySelector(".steps-count"),m=i.querySelector(".chain-empty-state");u&&(u.textContent=`(${c.length})`),c.length===0?(s.style.display="none",m&&(m.style.display="block")):(s.style.display="flex",m&&(m.style.display="none"))})();const l=i.querySelector(".chain-editor-close"),a=i.querySelector(".chain-cancel-btn"),d=i.querySelector(".chain-save-btn"),h=i.querySelector(".chain-add-step-btn");l.addEventListener("click",()=>o.remove()),l.addEventListener("mouseenter",()=>{l.style.background="var(--gf-hover-bg)",l.style.color="var(--gf-text-primary)"}),l.addEventListener("mouseleave",()=>{l.style.background="none",l.style.color="var(--gf-text-secondary)"}),a.addEventListener("click",()=>o.remove()),a.addEventListener("mouseenter",()=>{a.style.background="var(--gf-hover-bg)"}),a.addEventListener("mouseleave",()=>{a.style.background="var(--gf-bg-primary)"}),d.addEventListener("mouseenter",()=>{d.style.opacity="0.9"}),d.addEventListener("mouseleave",()=>{d.style.opacity="1"}),h.addEventListener("mouseenter",()=>{h.style.opacity="0.9"}),h.addEventListener("mouseleave",()=>{h.style.opacity="1"});const f=()=>{const c=s.querySelectorAll(".chain-step-item"),u=i.querySelector(".steps-count"),m=i.querySelector(".chain-empty-state");u&&(u.textContent=`(${c.length})`),c.length===0?(s.style.display="none",m&&(m.style.display="block")):(s.style.display="flex",m&&(m.style.display="none"))};i.querySelector(".chain-add-step-btn").addEventListener("click",()=>{const c=s.querySelectorAll(".chain-step-item");this.addChainStep(s,"",c.length,!0),f()});const v=i.querySelector(".chain-add-first-step-btn");v&&(v.addEventListener("click",()=>{this.addChainStep(s,"",0,!0),f()}),v.addEventListener("mouseenter",()=>{v.style.opacity="0.9"}),v.addEventListener("mouseleave",()=>{v.style.opacity="1"})),s.addEventListener("click",c=>{if(c.target.classList.contains("chain-step-remove")){const u=c.target.closest(".chain-step-item");u.style.opacity="0",u.style.transform="translateX(-10px)",setTimeout(()=>{u.remove(),this.updateStepNumbers(s),f()},200)}}),d.addEventListener("click",()=>{const c=i.querySelector(".chain-title-input").value.trim(),u="chain";if(!c){this.showError("Please enter a chain name");return}const m=s.querySelectorAll(".chain-step-textarea"),p=Array.from(m).map(y=>y.value.trim()).filter(y=>y.length>0);if(p.length===0){this.showError("Please add at least one step");return}const g={...n,title:c,category:u,steps:p,isChain:!0,updatedAt:new Date().toISOString()};if(t){const y=this.userPrompts.findIndex(w=>w.id===n.id);y!==-1&&(this.userPrompts[y]=g)}else this.userPrompts.unshift(g);this.saveUserPrompts(),this.showToast(t?"Chain updated!":"Chain created!"),o.remove(),this.filterPrompts(),window.geminiAPI&&typeof CONFIG<"u"&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent(t?"prompt_chain_updated":"prompt_chain_created",{stepCount:p.length,category:u,automated:!0})}),o.addEventListener("click",c=>{c.target===o&&o.remove()})}addChainStep(e,t="",n=0,o=!1){const i=document.createElement("div");if(i.className="chain-step-item",i.style.cssText=`
            position: relative;
            border: 1px solid var(--gf-border-color);
            border-left: 3px solid var(--gf-accent-primary);
            border-radius: 8px;
            padding: 16px;
            background: var(--gf-bg-primary);
            box-shadow: 0 1px 3px rgba(0, 0, 0, 0.05);
            transition: all 0.2s ease;
        `,i.innerHTML=`
            <div style="display: flex; justify-content: space-between; align-items: center; margin-bottom: 10px; padding-bottom: 10px; border-bottom: 1px solid var(--gf-border-color);">
                <span style="font-weight: 500; color: var(--gf-text-primary); font-size: 14px;">Step ${n+1}</span>
                <button class="chain-step-remove" style="padding: 6px 12px; background: transparent; color: var(--gf-text-secondary); border: 1px solid var(--gf-border-color); border-radius: 4px; cursor: pointer; font-size: 12px; transition: all 0.2s ease; font-weight: 500;">Delete step</button>
            </div>
            <textarea class="chain-step-textarea" placeholder="Enter the prompt for step ${n+1}..." style="width: 100%; min-height: 100px; padding: 12px; border: 1px solid var(--gf-border-color); border-radius: 6px; font-size: 14px; resize: vertical; background: var(--gf-bg-input); color: var(--gf-text-primary); font-family: inherit; box-sizing: border-box; transition: border-color 0.2s ease; line-height: 1.5;">${this.escapeHtml(t)}</textarea>
        `,e.appendChild(i),o){const r=i.querySelector(".chain-step-textarea");setTimeout(()=>{r.focus(),r.scrollIntoView({behavior:"smooth",block:"center"})},100)}const s=i.querySelector(".chain-step-remove");s.addEventListener("mouseenter",()=>{s.style.background="var(--gf-accent-danger)",s.style.color="var(--color-white)",s.style.borderColor="var(--gf-accent-danger)"}),s.addEventListener("mouseleave",()=>{s.style.background="transparent",s.style.color="var(--gf-text-secondary)",s.style.borderColor="var(--gf-border-color)"}),this.updateStepNumbers(e)}updateStepNumbers(e){e.querySelectorAll(".chain-step-item").forEach((n,o)=>{const i=n.querySelector("span");i&&(i.textContent=`Step ${o+1}`);const s=n.querySelector(".chain-step-textarea");s&&(s.placeholder=`Enter the prompt for step ${o+1}...`)})}checkResponseCompletion(){const e=document.querySelector('speech-dictation-mic-button, button[aria-label*="microphone" i], mat-icon[fonticon="mic"]'),t=document.querySelector('button[aria-label*="Stop" i], mat-icon[fonticon="stop"]'),n=e!==null&&t===null;return{micPresent:e!==null,stopAbsent:t===null,allComplete:n,debugInfo:{micSelector:e?e.tagName:"not found",stopFound:t!==null,geminiIdle:n}}}runPromptChain(e,t=0){if(!e.isChain||!e.steps||e.steps.length===0){this.showError("Invalid prompt chain");return}window._geminiChainState={chain:e,currentStepIndex:t,isRunning:!0},this.executeChainStep(e,t),window.geminiAPI&&typeof CONFIG<"u"&&CONFIG.ANALYTICS_EVENTS&&window.geminiAPI.trackEvent("prompt_chain_started",{stepCount:e.steps.length,category:e.category,automated:!0})}executeChainStep(e,t){if(t>=e.steps.length){this.resetPromptChain(),this.showToast("Prompt chain completed!");return}const n=e.steps[t],o=[".ql-editor.textarea.new-input-ui","rich-textarea .ql-editor",'.ql-editor[contenteditable="true"]','div[contenteditable="true"][role="textbox"]'];let i=null;for(const r of o)if(i=document.querySelector(r),i)break;if(!i){this.showError("Could not find Gemini input field"),this.resetPromptChain();return}i.innerHTML="";const s=document.createElement("p");s.textContent=n,i.appendChild(s),i.classList.remove("ql-blank"),i.focus(),i.dispatchEvent(new Event("input",{bubbles:!0})),i.dispatchEvent(new Event("change",{bubbles:!0})),this.showChainIndicator(t+1,e.steps.length),setTimeout(()=>{const r=document.querySelector('button[aria-label*="Send"], button.send-button, button[type="submit"]');r&&!r.disabled?(r.click(),this.setupResponseDetection(e,t)):(this.showError("Could not send message. Please try manually."),this.resetPromptChain())},500)}setupResponseDetection(e,t){let s=0,r=0,l=!1;this.updateChainIndicatorStatus("Waiting for response...");const a=setInterval(()=>{if(s+=300,this.checkResponseCompletion().allComplete){if(r++,r===1&&this.updateChainIndicatorStatus("Response complete, verifying..."),r>=2){clearInterval(a);const h=t+1;h<e.steps.length?(window._geminiChainState.currentStepIndex=h,this.executeChainStep(e,h)):(this.resetPromptChain(),this.showToast("Prompt chain completed!"))}}else r=0,s>3e4&&!l&&(this.showManualChainControls(e,t,a),l=!0);s>=3e5&&(clearInterval(a),this.showError("Chain timed out after 5 minutes"),this.resetPromptChain())},300);window._geminiChainState||(window._geminiChainState={}),window._geminiChainState.checkInterval=a}showChainIndicator(e,t){let n=this.shadowRoot.querySelector(".chain-running-indicator");if(n||(n=document.createElement("div"),n.className="chain-running-indicator",n.style.cssText=`
                position: fixed;
                top: 20px;
                right: 20px;
                background: var(--gf-accent-primary);
                color: var(--gf-button-text);
                padding: 12px 20px;
                border-radius: 8px;
                box-shadow: 0 4px 12px rgba(0, 0, 0, 0.3);
                z-index: 10001;
                font-size: 14px;
                font-weight: 500;
                display: flex;
                flex-direction: column;
                gap: 8px;
                min-width: 200px;
            `,this.shadowRoot.appendChild(n)),n.innerHTML=`
            <div style="display: flex; align-items: center; gap: 10px;">
                <svg width="16" height="16" viewBox="0 0 24 24" fill="currentColor">
                    <circle cx="12" cy="12" r="10" opacity="0.3"/>
                    <path d="M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm0 18c-4.41 0-8-3.59-8-8s3.59-8 8-8 8 3.59 8 8-3.59 8-8 8z"/>
                </svg>
                <span>Running Chain: ${e} / ${t}</span>
                <div class="pulse-dot" style="width: 8px; height: 8px; background: white; border-radius: 50%; animation: blink 1s infinite;"></div>
            </div>
            <div class="chain-status" style="font-size: 12px; opacity: 0.9; padding-left: 26px;">
                Initializing...
            </div>
        `,!this.shadowRoot.querySelector("#chain-blink-animation")){const o=document.createElement("style");o.id="chain-blink-animation",o.textContent=`
                @keyframes blink {
                    0%, 100% { opacity: 1; }
                    50% { opacity: 0.3; }
                }
            `,this.shadowRoot.appendChild(o)}}updateChainIndicatorStatus(e){const t=this.shadowRoot.querySelector(".chain-running-indicator");if(t){const n=t.querySelector(".chain-status");n&&(n.textContent=e)}}showManualChainControls(e,t,n){const o=this.shadowRoot.querySelector(".chain-running-indicator");if(!o||o.querySelector(".manual-controls"))return;const i=document.createElement("div");i.className="manual-controls",i.style.cssText=`
            display: flex;
            gap: 8px;
            margin-top: 8px;
            padding-top: 8px;
            border-top: 1px solid rgba(255, 255, 255, 0.2);
        `,i.innerHTML=`
            <button class="skip-step-btn" style="flex: 1; padding: 6px 12px; background: rgba(255, 255, 255, 0.2); color: white; border: none; border-radius: 4px; cursor: pointer; font-size: 12px; font-weight: 500;">
                Skip to Next
            </button>
            <button class="stop-chain-btn" style="padding: 6px 12px; background: rgba(239, 68, 68, 0.8); color: white; border: none; border-radius: 4px; cursor: pointer; font-size: 12px; font-weight: 500;">
                Stop
            </button>
        `,o.appendChild(i);const s=i.querySelector(".skip-step-btn"),r=i.querySelector(".stop-chain-btn");s.addEventListener("click",()=>{clearInterval(n);const l=t+1;l<e.steps.length?(window._geminiChainState.currentStepIndex=l,this.executeChainStep(e,l)):(this.resetPromptChain(),this.showToast("Prompt chain completed!"))}),r.addEventListener("click",()=>{clearInterval(n),this.resetPromptChain(),this.showToast("Prompt chain stopped")}),this.updateChainIndicatorStatus("\u23F1\uFE0F Taking longer than expected...")}resetPromptChain(){window._geminiChainState&&window._geminiChainState.checkInterval&&clearInterval(window._geminiChainState.checkInterval),window._geminiChainState=null;const e=this.shadowRoot.querySelector(".chain-running-indicator");e&&e.remove()}}window.PromptLibrary=PromptLibrary;
