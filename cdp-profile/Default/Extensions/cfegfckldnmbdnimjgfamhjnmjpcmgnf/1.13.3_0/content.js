const Ce=async()=>new Promise(e=>{chrome.runtime.sendMessage({action:"checkAuthStatus"},t=>{e(t)})});function De(e,t=document){for(const n of e)try{const o=t.querySelector(n);if(o)return o}catch(o){console.warn(`[PolicyEngine] Invalid selector: ${n}`,o)}return null}function It(e,t=document){const n=[];for(const o of e)try{const r=Array.from(t.querySelectorAll(o));n.push(...r)}catch(r){console.warn(`[PolicyEngine] Invalid selector: ${o}`,r)}return n}function _n(e,t=document){for(const n of e)try{const o=Array.from(t.querySelectorAll(n));if(o.length>0)return o}catch(o){console.warn(`[PolicyEngine] Invalid selector: ${n}`,o)}return[]}function On(e){return e.getAttribute("contenteditable")==="true"?e.innerText||e.textContent||"":e instanceof HTMLInputElement||e instanceof HTMLTextAreaElement?e.value:e.textContent||""}function To(e,t=document){const n=e.any;for(const o of n)try{const r=t.querySelector(o);if(r)return{element:r,matchedSelector:o}}catch(r){console.warn(`[PolicyEngine] Invalid selector in Any policy: ${o}`,r)}return{element:null,matchedSelector:null}}function So(e,t){if(e==="self")return t||null;if(typeof e=="object"&&"traverseUp"in e){if(!t)return console.warn("[PolicyEngine] traverseUp requires entry point element"),null;const r=e.traverseUp.any||e.traverseUp.all||[];for(const i of r)try{const a=t.closest(i);if(a)return a}catch(a){console.warn(`[PolicyEngine] Invalid ancestor selector: ${i}`,a)}return null}const n=e,o=n.any||n.all||[];return De(o)}function $o(e,t,n,o){try{const r=o||t;switch(n){case"before":r.parentElement?.insertBefore(e,r);break;case"after":r.parentElement?.insertBefore(e,r.nextSibling);break;case"prepend":(o||t).insertBefore(e,(o||t).firstChild);break;case"append":(o||t).appendChild(e);break;default:return console.error(`[PolicyEngine] Invalid insert position: ${n}`),!1}return!0}catch(r){return console.error("[PolicyEngine] Failed to insert element:",r),!1}}function vr(e,t,n){const{insert:o}=e;let r=So(o.into,n);if(!r)return{success:!1,container:null,insertedElement:null,error:"Failed to find container"};let i,a=o.position;if(o.relative){const c=o.relative.any||o.relative.all||[];if(i=De(c,r)||void 0,!i&&(a==="before"||a==="after")){const d=De(c);if(d){const p=o.into;if(typeof p=="object"&&"any"in p){const u=p.any||[];for(const h of u){const m=d.closest(h);if(m){r=m,i=d;break}}}!i&&d.parentElement&&(r=d.parentElement,i=d)}}i||(console.warn("[PolicyEngine] Relative target not found, falling back to append position"),a="append")}return $o(t,r,a,i)?(e.reposition&&Ao(e.reposition.all),{success:!0,container:r,insertedElement:t}):{success:!1,container:r,insertedElement:null,error:"Failed to insert element"}}function Io(e){return"user"in e&&"assistant"in e}function Un(e,t){if(Io(e)){const n=e[t];return n.any||n.all||[]}else return e.any||e.all||[]}function qn(e,t,n,o){const r=e.cloneNode(!0);if(o&&o.length>0&&It(o,r).forEach(a=>a.remove()),n&&n.length>0&&It(n,r).length>0)return"";for(const i of t)try{const a=r.querySelectorAll(i);if(a.length>0){const s=Array.from(a).map(c=>On(c).trim()).filter(c=>c.length>0);if(s.length>0)return s.join(`

`)}}catch(a){console.warn(`[PolicyEngine] Invalid content selector: ${i}`,a)}return On(r).trim()}function Lo(e,t=document){const n=e.find.user.any||e.find.user.all||[],o=e.find.user.any?"any":"all",r=e.find.assistant.any||e.find.assistant.all||[],i=e.find.assistant.any?"any":"all",a=e.extract.skip?.all,s=e.extract.cleanup?.all,c=o==="any"?_n(n,t):It(n,t),p=(i==="any"?_n(r,t):It(r,t)).filter(m=>!c.includes(m)),u=[];for(const m of c){const f=Un(e.extract.content,"user"),k=qn(m,f,a,s);k&&u.push({element:m,message:{role:"user",content:k}})}for(const m of p){const f=Un(e.extract.content,"assistant"),k=qn(m,f,a,s);k&&u.push({element:m,message:{role:"assistant",content:k}})}u.sort((m,f)=>{const k=m.element.compareDocumentPosition(f.element);return k&Node.DOCUMENT_POSITION_FOLLOWING?-1:k&Node.DOCUMENT_POSITION_PRECEDING?1:0});const h=u.map(m=>m.message);return{messages:h,userMessageCount:h.filter(m=>m.role==="user").length,assistantMessageCount:h.filter(m=>m.role==="assistant").length}}function Mo(e,t){const n=e.any;for(let o=0;o<n.length;o++){const r=n[o],i=r.find.any,a=De(i);if(!a)continue;const s={insert:r.insert,reposition:e.reposition},c=vr(s,t,a);if(c.success)return{...c,matchedStrategyIndex:o}}return{success:!1,container:null,insertedElement:null,matchedStrategyIndex:null,error:"All insertion strategies failed"}}function Ao(e){for(const t of e){const n=t.find.any,o=De(n);if(!o||!(o instanceof HTMLElement)){console.warn("[PolicyEngine] Reposition: Element not found or not HTMLElement");continue}const{apply:r}=t;for(const[i,a]of Object.entries(r))if(a!==void 0){if(i==="leftOffset"&&typeof a=="number"){const s=o.previousElementSibling;if(s){const c=s.offsetWidth+a;o.style.left=`${c}px`}continue}typeof a=="string"?o.style[i]=a:typeof a=="number"&&(o.style[i]=`${a}px`)}}}function Po(e,t=5e3,n=document){return new Promise(o=>{const r=De(e,n);if(r){o(r);return}const i=new MutationObserver(()=>{const a=De(e,n);a&&(i.disconnect(),o(a))});i.observe(n instanceof Document?n.documentElement:n,{childList:!0,subtree:!0}),setTimeout(()=>{i.disconnect(),o(null)},t)})}/*! js-yaml 4.1.0 https://github.com/nodeca/js-yaml @license MIT */function Cr(e){return typeof e>"u"||e===null}function Bo(e){return typeof e=="object"&&e!==null}function No(e){return Array.isArray(e)?e:Cr(e)?[]:[e]}function Do(e,t){var n,o,r,i;if(t)for(i=Object.keys(t),n=0,o=i.length;n<o;n+=1)r=i[n],e[r]=t[r];return e}function Ro(e,t){var n="",o;for(o=0;o<t;o+=1)n+=e;return n}function Fo(e){return e===0&&Number.NEGATIVE_INFINITY===1/e}var zo=Cr,Ho=Bo,_o=No,Oo=Ro,Uo=Fo,qo=Do,X={isNothing:zo,isObject:Ho,toArray:_o,repeat:Oo,isNegativeZero:Uo,extend:qo};function Er(e,t){var n="",o=e.reason||"(unknown reason)";return e.mark?(e.mark.name&&(n+='in "'+e.mark.name+'" '),n+="("+(e.mark.line+1)+":"+(e.mark.column+1)+")",!t&&e.mark.snippet&&(n+=`

`+e.mark.snippet),o+" "+n):o}function ut(e,t){Error.call(this),this.name="YAMLException",this.reason=e,this.mark=t,this.message=Er(this,!1),Error.captureStackTrace?Error.captureStackTrace(this,this.constructor):this.stack=new Error().stack||""}ut.prototype=Object.create(Error.prototype);ut.prototype.constructor=ut;ut.prototype.toString=function(t){return this.name+": "+Er(this,t)};var de=ut;function en(e,t,n,o,r){var i="",a="",s=Math.floor(r/2)-1;return o-t>s&&(i=" ... ",t=o-s+i.length),n-o>s&&(a=" ...",n=o+s-a.length),{str:i+e.slice(t,n).replace(/\t/g,"→")+a,pos:o-t+i.length}}function tn(e,t){return X.repeat(" ",t-e.length)+e}function jo(e,t){if(t=Object.create(t||null),!e.buffer)return null;t.maxLength||(t.maxLength=79),typeof t.indent!="number"&&(t.indent=1),typeof t.linesBefore!="number"&&(t.linesBefore=3),typeof t.linesAfter!="number"&&(t.linesAfter=2);for(var n=/\r?\n|\r|\0/g,o=[0],r=[],i,a=-1;i=n.exec(e.buffer);)r.push(i.index),o.push(i.index+i[0].length),e.position<=i.index&&a<0&&(a=o.length-2);a<0&&(a=o.length-1);var s="",c,d,p=Math.min(e.line+t.linesAfter,r.length).toString().length,u=t.maxLength-(t.indent+p+3);for(c=1;c<=t.linesBefore&&!(a-c<0);c++)d=en(e.buffer,o[a-c],r[a-c],e.position-(o[a]-o[a-c]),u),s=X.repeat(" ",t.indent)+tn((e.line-c+1).toString(),p)+" | "+d.str+`
`+s;for(d=en(e.buffer,o[a],r[a],e.position,u),s+=X.repeat(" ",t.indent)+tn((e.line+1).toString(),p)+" | "+d.str+`
`,s+=X.repeat("-",t.indent+p+3+d.pos)+`^
`,c=1;c<=t.linesAfter&&!(a+c>=r.length);c++)d=en(e.buffer,o[a+c],r[a+c],e.position-(o[a]-o[a+c]),u),s+=X.repeat(" ",t.indent)+tn((e.line+c+1).toString(),p)+" | "+d.str+`
`;return s.replace(/\n$/,"")}var Yo=jo,Wo=["kind","multi","resolve","construct","instanceOf","predicate","represent","representName","defaultStyle","styleAliases"],Go=["scalar","sequence","mapping"];function Ko(e){var t={};return e!==null&&Object.keys(e).forEach(function(n){e[n].forEach(function(o){t[String(o)]=n})}),t}function Xo(e,t){if(t=t||{},Object.keys(t).forEach(function(n){if(Wo.indexOf(n)===-1)throw new de('Unknown option "'+n+'" is met in definition of "'+e+'" YAML type.')}),this.options=t,this.tag=e,this.kind=t.kind||null,this.resolve=t.resolve||function(){return!0},this.construct=t.construct||function(n){return n},this.instanceOf=t.instanceOf||null,this.predicate=t.predicate||null,this.represent=t.represent||null,this.representName=t.representName||null,this.defaultStyle=t.defaultStyle||null,this.multi=t.multi||!1,this.styleAliases=Ko(t.styleAliases||null),Go.indexOf(this.kind)===-1)throw new de('Unknown kind "'+this.kind+'" is specified for "'+e+'" YAML type.')}var G=Xo;function jn(e,t){var n=[];return e[t].forEach(function(o){var r=n.length;n.forEach(function(i,a){i.tag===o.tag&&i.kind===o.kind&&i.multi===o.multi&&(r=a)}),n[r]=o}),n}function Vo(){var e={scalar:{},sequence:{},mapping:{},fallback:{},multi:{scalar:[],sequence:[],mapping:[],fallback:[]}},t,n;function o(r){r.multi?(e.multi[r.kind].push(r),e.multi.fallback.push(r)):e[r.kind][r.tag]=e.fallback[r.tag]=r}for(t=0,n=arguments.length;t<n;t+=1)arguments[t].forEach(o);return e}function cn(e){return this.extend(e)}cn.prototype.extend=function(t){var n=[],o=[];if(t instanceof G)o.push(t);else if(Array.isArray(t))o=o.concat(t);else if(t&&(Array.isArray(t.implicit)||Array.isArray(t.explicit)))t.implicit&&(n=n.concat(t.implicit)),t.explicit&&(o=o.concat(t.explicit));else throw new de("Schema.extend argument should be a Type, [ Type ], or a schema definition ({ implicit: [...], explicit: [...] })");n.forEach(function(i){if(!(i instanceof G))throw new de("Specified list of YAML types (or a single Type object) contains a non-Type object.");if(i.loadKind&&i.loadKind!=="scalar")throw new de("There is a non-scalar type in the implicit list of a schema. Implicit resolving of such types is not supported.");if(i.multi)throw new de("There is a multi type in the implicit list of a schema. Multi tags can only be listed as explicit.")}),o.forEach(function(i){if(!(i instanceof G))throw new de("Specified list of YAML types (or a single Type object) contains a non-Type object.")});var r=Object.create(cn.prototype);return r.implicit=(this.implicit||[]).concat(n),r.explicit=(this.explicit||[]).concat(o),r.compiledImplicit=jn(r,"implicit"),r.compiledExplicit=jn(r,"explicit"),r.compiledTypeMap=Vo(r.compiledImplicit,r.compiledExplicit),r};var Qo=cn,Zo=new G("tag:yaml.org,2002:str",{kind:"scalar",construct:function(e){return e!==null?e:""}}),Jo=new G("tag:yaml.org,2002:seq",{kind:"sequence",construct:function(e){return e!==null?e:[]}}),ei=new G("tag:yaml.org,2002:map",{kind:"mapping",construct:function(e){return e!==null?e:{}}}),ti=new Qo({explicit:[Zo,Jo,ei]});function ni(e){if(e===null)return!0;var t=e.length;return t===1&&e==="~"||t===4&&(e==="null"||e==="Null"||e==="NULL")}function ri(){return null}function oi(e){return e===null}var ii=new G("tag:yaml.org,2002:null",{kind:"scalar",resolve:ni,construct:ri,predicate:oi,represent:{canonical:function(){return"~"},lowercase:function(){return"null"},uppercase:function(){return"NULL"},camelcase:function(){return"Null"},empty:function(){return""}},defaultStyle:"lowercase"});function ai(e){if(e===null)return!1;var t=e.length;return t===4&&(e==="true"||e==="True"||e==="TRUE")||t===5&&(e==="false"||e==="False"||e==="FALSE")}function si(e){return e==="true"||e==="True"||e==="TRUE"}function li(e){return Object.prototype.toString.call(e)==="[object Boolean]"}var ci=new G("tag:yaml.org,2002:bool",{kind:"scalar",resolve:ai,construct:si,predicate:li,represent:{lowercase:function(e){return e?"true":"false"},uppercase:function(e){return e?"TRUE":"FALSE"},camelcase:function(e){return e?"True":"False"}},defaultStyle:"lowercase"});function di(e){return 48<=e&&e<=57||65<=e&&e<=70||97<=e&&e<=102}function pi(e){return 48<=e&&e<=55}function ui(e){return 48<=e&&e<=57}function hi(e){if(e===null)return!1;var t=e.length,n=0,o=!1,r;if(!t)return!1;if(r=e[n],(r==="-"||r==="+")&&(r=e[++n]),r==="0"){if(n+1===t)return!0;if(r=e[++n],r==="b"){for(n++;n<t;n++)if(r=e[n],r!=="_"){if(r!=="0"&&r!=="1")return!1;o=!0}return o&&r!=="_"}if(r==="x"){for(n++;n<t;n++)if(r=e[n],r!=="_"){if(!di(e.charCodeAt(n)))return!1;o=!0}return o&&r!=="_"}if(r==="o"){for(n++;n<t;n++)if(r=e[n],r!=="_"){if(!pi(e.charCodeAt(n)))return!1;o=!0}return o&&r!=="_"}}if(r==="_")return!1;for(;n<t;n++)if(r=e[n],r!=="_"){if(!ui(e.charCodeAt(n)))return!1;o=!0}return!(!o||r==="_")}function mi(e){var t=e,n=1,o;if(t.indexOf("_")!==-1&&(t=t.replace(/_/g,"")),o=t[0],(o==="-"||o==="+")&&(o==="-"&&(n=-1),t=t.slice(1),o=t[0]),t==="0")return 0;if(o==="0"){if(t[1]==="b")return n*parseInt(t.slice(2),2);if(t[1]==="x")return n*parseInt(t.slice(2),16);if(t[1]==="o")return n*parseInt(t.slice(2),8)}return n*parseInt(t,10)}function fi(e){return Object.prototype.toString.call(e)==="[object Number]"&&e%1===0&&!X.isNegativeZero(e)}var gi=new G("tag:yaml.org,2002:int",{kind:"scalar",resolve:hi,construct:mi,predicate:fi,represent:{binary:function(e){return e>=0?"0b"+e.toString(2):"-0b"+e.toString(2).slice(1)},octal:function(e){return e>=0?"0o"+e.toString(8):"-0o"+e.toString(8).slice(1)},decimal:function(e){return e.toString(10)},hexadecimal:function(e){return e>=0?"0x"+e.toString(16).toUpperCase():"-0x"+e.toString(16).toUpperCase().slice(1)}},defaultStyle:"decimal",styleAliases:{binary:[2,"bin"],octal:[8,"oct"],decimal:[10,"dec"],hexadecimal:[16,"hex"]}}),xi=new RegExp("^(?:[-+]?(?:[0-9][0-9_]*)(?:\\.[0-9_]*)?(?:[eE][-+]?[0-9]+)?|\\.[0-9_]+(?:[eE][-+]?[0-9]+)?|[-+]?\\.(?:inf|Inf|INF)|\\.(?:nan|NaN|NAN))$");function bi(e){return!(e===null||!xi.test(e)||e[e.length-1]==="_")}function yi(e){var t,n;return t=e.replace(/_/g,"").toLowerCase(),n=t[0]==="-"?-1:1,"+-".indexOf(t[0])>=0&&(t=t.slice(1)),t===".inf"?n===1?Number.POSITIVE_INFINITY:Number.NEGATIVE_INFINITY:t===".nan"?NaN:n*parseFloat(t,10)}var wi=/^[-+]?[0-9]+e/;function ki(e,t){var n;if(isNaN(e))switch(t){case"lowercase":return".nan";case"uppercase":return".NAN";case"camelcase":return".NaN"}else if(Number.POSITIVE_INFINITY===e)switch(t){case"lowercase":return".inf";case"uppercase":return".INF";case"camelcase":return".Inf"}else if(Number.NEGATIVE_INFINITY===e)switch(t){case"lowercase":return"-.inf";case"uppercase":return"-.INF";case"camelcase":return"-.Inf"}else if(X.isNegativeZero(e))return"-0.0";return n=e.toString(10),wi.test(n)?n.replace("e",".e"):n}function vi(e){return Object.prototype.toString.call(e)==="[object Number]"&&(e%1!==0||X.isNegativeZero(e))}var Ci=new G("tag:yaml.org,2002:float",{kind:"scalar",resolve:bi,construct:yi,predicate:vi,represent:ki,defaultStyle:"lowercase"}),Ei=ti.extend({implicit:[ii,ci,gi,Ci]}),Ti=Ei,Tr=new RegExp("^([0-9][0-9][0-9][0-9])-([0-9][0-9])-([0-9][0-9])$"),Sr=new RegExp("^([0-9][0-9][0-9][0-9])-([0-9][0-9]?)-([0-9][0-9]?)(?:[Tt]|[ \\t]+)([0-9][0-9]?):([0-9][0-9]):([0-9][0-9])(?:\\.([0-9]*))?(?:[ \\t]*(Z|([-+])([0-9][0-9]?)(?::([0-9][0-9]))?))?$");function Si(e){return e===null?!1:Tr.exec(e)!==null||Sr.exec(e)!==null}function $i(e){var t,n,o,r,i,a,s,c=0,d=null,p,u,h;if(t=Tr.exec(e),t===null&&(t=Sr.exec(e)),t===null)throw new Error("Date resolve error");if(n=+t[1],o=+t[2]-1,r=+t[3],!t[4])return new Date(Date.UTC(n,o,r));if(i=+t[4],a=+t[5],s=+t[6],t[7]){for(c=t[7].slice(0,3);c.length<3;)c+="0";c=+c}return t[9]&&(p=+t[10],u=+(t[11]||0),d=(p*60+u)*6e4,t[9]==="-"&&(d=-d)),h=new Date(Date.UTC(n,o,r,i,a,s,c)),d&&h.setTime(h.getTime()-d),h}function Ii(e){return e.toISOString()}var Li=new G("tag:yaml.org,2002:timestamp",{kind:"scalar",resolve:Si,construct:$i,instanceOf:Date,represent:Ii});function Mi(e){return e==="<<"||e===null}var Ai=new G("tag:yaml.org,2002:merge",{kind:"scalar",resolve:Mi}),vn=`ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=
\r`;function Pi(e){if(e===null)return!1;var t,n,o=0,r=e.length,i=vn;for(n=0;n<r;n++)if(t=i.indexOf(e.charAt(n)),!(t>64)){if(t<0)return!1;o+=6}return o%8===0}function Bi(e){var t,n,o=e.replace(/[\r\n=]/g,""),r=o.length,i=vn,a=0,s=[];for(t=0;t<r;t++)t%4===0&&t&&(s.push(a>>16&255),s.push(a>>8&255),s.push(a&255)),a=a<<6|i.indexOf(o.charAt(t));return n=r%4*6,n===0?(s.push(a>>16&255),s.push(a>>8&255),s.push(a&255)):n===18?(s.push(a>>10&255),s.push(a>>2&255)):n===12&&s.push(a>>4&255),new Uint8Array(s)}function Ni(e){var t="",n=0,o,r,i=e.length,a=vn;for(o=0;o<i;o++)o%3===0&&o&&(t+=a[n>>18&63],t+=a[n>>12&63],t+=a[n>>6&63],t+=a[n&63]),n=(n<<8)+e[o];return r=i%3,r===0?(t+=a[n>>18&63],t+=a[n>>12&63],t+=a[n>>6&63],t+=a[n&63]):r===2?(t+=a[n>>10&63],t+=a[n>>4&63],t+=a[n<<2&63],t+=a[64]):r===1&&(t+=a[n>>2&63],t+=a[n<<4&63],t+=a[64],t+=a[64]),t}function Di(e){return Object.prototype.toString.call(e)==="[object Uint8Array]"}var Ri=new G("tag:yaml.org,2002:binary",{kind:"scalar",resolve:Pi,construct:Bi,predicate:Di,represent:Ni}),Fi=Object.prototype.hasOwnProperty,zi=Object.prototype.toString;function Hi(e){if(e===null)return!0;var t=[],n,o,r,i,a,s=e;for(n=0,o=s.length;n<o;n+=1){if(r=s[n],a=!1,zi.call(r)!=="[object Object]")return!1;for(i in r)if(Fi.call(r,i))if(!a)a=!0;else return!1;if(!a)return!1;if(t.indexOf(i)===-1)t.push(i);else return!1}return!0}function _i(e){return e!==null?e:[]}var Oi=new G("tag:yaml.org,2002:omap",{kind:"sequence",resolve:Hi,construct:_i}),Ui=Object.prototype.toString;function qi(e){if(e===null)return!0;var t,n,o,r,i,a=e;for(i=new Array(a.length),t=0,n=a.length;t<n;t+=1){if(o=a[t],Ui.call(o)!=="[object Object]"||(r=Object.keys(o),r.length!==1))return!1;i[t]=[r[0],o[r[0]]]}return!0}function ji(e){if(e===null)return[];var t,n,o,r,i,a=e;for(i=new Array(a.length),t=0,n=a.length;t<n;t+=1)o=a[t],r=Object.keys(o),i[t]=[r[0],o[r[0]]];return i}var Yi=new G("tag:yaml.org,2002:pairs",{kind:"sequence",resolve:qi,construct:ji}),Wi=Object.prototype.hasOwnProperty;function Gi(e){if(e===null)return!0;var t,n=e;for(t in n)if(Wi.call(n,t)&&n[t]!==null)return!1;return!0}function Ki(e){return e!==null?e:{}}var Xi=new G("tag:yaml.org,2002:set",{kind:"mapping",resolve:Gi,construct:Ki}),Vi=Ti.extend({implicit:[Li,Ai],explicit:[Ri,Oi,Yi,Xi]}),Ee=Object.prototype.hasOwnProperty,Lt=1,$r=2,Ir=3,Mt=4,nn=1,Qi=2,Yn=3,Zi=/[\x00-\x08\x0B\x0C\x0E-\x1F\x7F-\x84\x86-\x9F\uFFFE\uFFFF]|[\uD800-\uDBFF](?![\uDC00-\uDFFF])|(?:[^\uD800-\uDBFF]|^)[\uDC00-\uDFFF]/,Ji=/[\x85\u2028\u2029]/,ea=/[,\[\]\{\}]/,Lr=/^(?:!|!!|![a-z\-]+!)$/i,Mr=/^(?:!|[^,\[\]\{\}])(?:%[0-9a-f]{2}|[0-9a-z\-#;\/\?:@&=\+\$,_\.!~\*'\(\)\[\]])*$/i;function Wn(e){return Object.prototype.toString.call(e)}function se(e){return e===10||e===13}function Be(e){return e===9||e===32}function Q(e){return e===9||e===32||e===10||e===13}function je(e){return e===44||e===91||e===93||e===123||e===125}function ta(e){var t;return 48<=e&&e<=57?e-48:(t=e|32,97<=t&&t<=102?t-97+10:-1)}function na(e){return e===120?2:e===117?4:e===85?8:0}function ra(e){return 48<=e&&e<=57?e-48:-1}function Gn(e){return e===48?"\0":e===97?"\x07":e===98?"\b":e===116||e===9?"	":e===110?`
`:e===118?"\v":e===102?"\f":e===114?"\r":e===101?"\x1B":e===32?" ":e===34?'"':e===47?"/":e===92?"\\":e===78?"":e===95?" ":e===76?"\u2028":e===80?"\u2029":""}function oa(e){return e<=65535?String.fromCharCode(e):String.fromCharCode((e-65536>>10)+55296,(e-65536&1023)+56320)}var Ar=new Array(256),Pr=new Array(256);for(var Ue=0;Ue<256;Ue++)Ar[Ue]=Gn(Ue)?1:0,Pr[Ue]=Gn(Ue);function ia(e,t){this.input=e,this.filename=t.filename||null,this.schema=t.schema||Vi,this.onWarning=t.onWarning||null,this.legacy=t.legacy||!1,this.json=t.json||!1,this.listener=t.listener||null,this.implicitTypes=this.schema.compiledImplicit,this.typeMap=this.schema.compiledTypeMap,this.length=e.length,this.position=0,this.line=0,this.lineStart=0,this.lineIndent=0,this.firstTabInLine=-1,this.documents=[]}function Br(e,t){var n={name:e.filename,buffer:e.input.slice(0,-1),position:e.position,line:e.line,column:e.position-e.lineStart};return n.snippet=Yo(n),new de(t,n)}function S(e,t){throw Br(e,t)}function At(e,t){e.onWarning&&e.onWarning.call(null,Br(e,t))}var Kn={YAML:function(t,n,o){var r,i,a;t.version!==null&&S(t,"duplication of %YAML directive"),o.length!==1&&S(t,"YAML directive accepts exactly one argument"),r=/^([0-9]+)\.([0-9]+)$/.exec(o[0]),r===null&&S(t,"ill-formed argument of the YAML directive"),i=parseInt(r[1],10),a=parseInt(r[2],10),i!==1&&S(t,"unacceptable YAML version of the document"),t.version=o[0],t.checkLineBreaks=a<2,a!==1&&a!==2&&At(t,"unsupported YAML version of the document")},TAG:function(t,n,o){var r,i;o.length!==2&&S(t,"TAG directive accepts exactly two arguments"),r=o[0],i=o[1],Lr.test(r)||S(t,"ill-formed tag handle (first argument) of the TAG directive"),Ee.call(t.tagMap,r)&&S(t,'there is a previously declared suffix for "'+r+'" tag handle'),Mr.test(i)||S(t,"ill-formed tag prefix (second argument) of the TAG directive");try{i=decodeURIComponent(i)}catch{S(t,"tag prefix is malformed: "+i)}t.tagMap[r]=i}};function ve(e,t,n,o){var r,i,a,s;if(t<n){if(s=e.input.slice(t,n),o)for(r=0,i=s.length;r<i;r+=1)a=s.charCodeAt(r),a===9||32<=a&&a<=1114111||S(e,"expected valid JSON character");else Zi.test(s)&&S(e,"the stream contains non-printable characters");e.result+=s}}function Xn(e,t,n,o){var r,i,a,s;for(X.isObject(n)||S(e,"cannot merge mappings; the provided source object is unacceptable"),r=Object.keys(n),a=0,s=r.length;a<s;a+=1)i=r[a],Ee.call(t,i)||(t[i]=n[i],o[i]=!0)}function Ye(e,t,n,o,r,i,a,s,c){var d,p;if(Array.isArray(r))for(r=Array.prototype.slice.call(r),d=0,p=r.length;d<p;d+=1)Array.isArray(r[d])&&S(e,"nested arrays are not supported inside keys"),typeof r=="object"&&Wn(r[d])==="[object Object]"&&(r[d]="[object Object]");if(typeof r=="object"&&Wn(r)==="[object Object]"&&(r="[object Object]"),r=String(r),t===null&&(t={}),o==="tag:yaml.org,2002:merge")if(Array.isArray(i))for(d=0,p=i.length;d<p;d+=1)Xn(e,t,i[d],n);else Xn(e,t,i,n);else!e.json&&!Ee.call(n,r)&&Ee.call(t,r)&&(e.line=a||e.line,e.lineStart=s||e.lineStart,e.position=c||e.position,S(e,"duplicated mapping key")),r==="__proto__"?Object.defineProperty(t,r,{configurable:!0,enumerable:!0,writable:!0,value:i}):t[r]=i,delete n[r];return t}function Cn(e){var t;t=e.input.charCodeAt(e.position),t===10?e.position++:t===13?(e.position++,e.input.charCodeAt(e.position)===10&&e.position++):S(e,"a line break is expected"),e.line+=1,e.lineStart=e.position,e.firstTabInLine=-1}function j(e,t,n){for(var o=0,r=e.input.charCodeAt(e.position);r!==0;){for(;Be(r);)r===9&&e.firstTabInLine===-1&&(e.firstTabInLine=e.position),r=e.input.charCodeAt(++e.position);if(t&&r===35)do r=e.input.charCodeAt(++e.position);while(r!==10&&r!==13&&r!==0);if(se(r))for(Cn(e),r=e.input.charCodeAt(e.position),o++,e.lineIndent=0;r===32;)e.lineIndent++,r=e.input.charCodeAt(++e.position);else break}return n!==-1&&o!==0&&e.lineIndent<n&&At(e,"deficient indentation"),o}function jt(e){var t=e.position,n;return n=e.input.charCodeAt(t),!!((n===45||n===46)&&n===e.input.charCodeAt(t+1)&&n===e.input.charCodeAt(t+2)&&(t+=3,n=e.input.charCodeAt(t),n===0||Q(n)))}function En(e,t){t===1?e.result+=" ":t>1&&(e.result+=X.repeat(`
`,t-1))}function aa(e,t,n){var o,r,i,a,s,c,d,p,u=e.kind,h=e.result,m;if(m=e.input.charCodeAt(e.position),Q(m)||je(m)||m===35||m===38||m===42||m===33||m===124||m===62||m===39||m===34||m===37||m===64||m===96||(m===63||m===45)&&(r=e.input.charCodeAt(e.position+1),Q(r)||n&&je(r)))return!1;for(e.kind="scalar",e.result="",i=a=e.position,s=!1;m!==0;){if(m===58){if(r=e.input.charCodeAt(e.position+1),Q(r)||n&&je(r))break}else if(m===35){if(o=e.input.charCodeAt(e.position-1),Q(o))break}else{if(e.position===e.lineStart&&jt(e)||n&&je(m))break;if(se(m))if(c=e.line,d=e.lineStart,p=e.lineIndent,j(e,!1,-1),e.lineIndent>=t){s=!0,m=e.input.charCodeAt(e.position);continue}else{e.position=a,e.line=c,e.lineStart=d,e.lineIndent=p;break}}s&&(ve(e,i,a,!1),En(e,e.line-c),i=a=e.position,s=!1),Be(m)||(a=e.position+1),m=e.input.charCodeAt(++e.position)}return ve(e,i,a,!1),e.result?!0:(e.kind=u,e.result=h,!1)}function sa(e,t){var n,o,r;if(n=e.input.charCodeAt(e.position),n!==39)return!1;for(e.kind="scalar",e.result="",e.position++,o=r=e.position;(n=e.input.charCodeAt(e.position))!==0;)if(n===39)if(ve(e,o,e.position,!0),n=e.input.charCodeAt(++e.position),n===39)o=e.position,e.position++,r=e.position;else return!0;else se(n)?(ve(e,o,r,!0),En(e,j(e,!1,t)),o=r=e.position):e.position===e.lineStart&&jt(e)?S(e,"unexpected end of the document within a single quoted scalar"):(e.position++,r=e.position);S(e,"unexpected end of the stream within a single quoted scalar")}function la(e,t){var n,o,r,i,a,s;if(s=e.input.charCodeAt(e.position),s!==34)return!1;for(e.kind="scalar",e.result="",e.position++,n=o=e.position;(s=e.input.charCodeAt(e.position))!==0;){if(s===34)return ve(e,n,e.position,!0),e.position++,!0;if(s===92){if(ve(e,n,e.position,!0),s=e.input.charCodeAt(++e.position),se(s))j(e,!1,t);else if(s<256&&Ar[s])e.result+=Pr[s],e.position++;else if((a=na(s))>0){for(r=a,i=0;r>0;r--)s=e.input.charCodeAt(++e.position),(a=ta(s))>=0?i=(i<<4)+a:S(e,"expected hexadecimal character");e.result+=oa(i),e.position++}else S(e,"unknown escape sequence");n=o=e.position}else se(s)?(ve(e,n,o,!0),En(e,j(e,!1,t)),n=o=e.position):e.position===e.lineStart&&jt(e)?S(e,"unexpected end of the document within a double quoted scalar"):(e.position++,o=e.position)}S(e,"unexpected end of the stream within a double quoted scalar")}function ca(e,t){var n=!0,o,r,i,a=e.tag,s,c=e.anchor,d,p,u,h,m,f=Object.create(null),k,w,g,y;if(y=e.input.charCodeAt(e.position),y===91)p=93,m=!1,s=[];else if(y===123)p=125,m=!0,s={};else return!1;for(e.anchor!==null&&(e.anchorMap[e.anchor]=s),y=e.input.charCodeAt(++e.position);y!==0;){if(j(e,!0,t),y=e.input.charCodeAt(e.position),y===p)return e.position++,e.tag=a,e.anchor=c,e.kind=m?"mapping":"sequence",e.result=s,!0;n?y===44&&S(e,"expected the node content, but found ','"):S(e,"missed comma between flow collection entries"),w=k=g=null,u=h=!1,y===63&&(d=e.input.charCodeAt(e.position+1),Q(d)&&(u=h=!0,e.position++,j(e,!0,t))),o=e.line,r=e.lineStart,i=e.position,Ke(e,t,Lt,!1,!0),w=e.tag,k=e.result,j(e,!0,t),y=e.input.charCodeAt(e.position),(h||e.line===o)&&y===58&&(u=!0,y=e.input.charCodeAt(++e.position),j(e,!0,t),Ke(e,t,Lt,!1,!0),g=e.result),m?Ye(e,s,f,w,k,g,o,r,i):u?s.push(Ye(e,null,f,w,k,g,o,r,i)):s.push(k),j(e,!0,t),y=e.input.charCodeAt(e.position),y===44?(n=!0,y=e.input.charCodeAt(++e.position)):n=!1}S(e,"unexpected end of the stream within a flow collection")}function da(e,t){var n,o,r=nn,i=!1,a=!1,s=t,c=0,d=!1,p,u;if(u=e.input.charCodeAt(e.position),u===124)o=!1;else if(u===62)o=!0;else return!1;for(e.kind="scalar",e.result="";u!==0;)if(u=e.input.charCodeAt(++e.position),u===43||u===45)nn===r?r=u===43?Yn:Qi:S(e,"repeat of a chomping mode identifier");else if((p=ra(u))>=0)p===0?S(e,"bad explicit indentation width of a block scalar; it cannot be less than one"):a?S(e,"repeat of an indentation width identifier"):(s=t+p-1,a=!0);else break;if(Be(u)){do u=e.input.charCodeAt(++e.position);while(Be(u));if(u===35)do u=e.input.charCodeAt(++e.position);while(!se(u)&&u!==0)}for(;u!==0;){for(Cn(e),e.lineIndent=0,u=e.input.charCodeAt(e.position);(!a||e.lineIndent<s)&&u===32;)e.lineIndent++,u=e.input.charCodeAt(++e.position);if(!a&&e.lineIndent>s&&(s=e.lineIndent),se(u)){c++;continue}if(e.lineIndent<s){r===Yn?e.result+=X.repeat(`
`,i?1+c:c):r===nn&&i&&(e.result+=`
`);break}for(o?Be(u)?(d=!0,e.result+=X.repeat(`
`,i?1+c:c)):d?(d=!1,e.result+=X.repeat(`
`,c+1)):c===0?i&&(e.result+=" "):e.result+=X.repeat(`
`,c):e.result+=X.repeat(`
`,i?1+c:c),i=!0,a=!0,c=0,n=e.position;!se(u)&&u!==0;)u=e.input.charCodeAt(++e.position);ve(e,n,e.position,!1)}return!0}function Vn(e,t){var n,o=e.tag,r=e.anchor,i=[],a,s=!1,c;if(e.firstTabInLine!==-1)return!1;for(e.anchor!==null&&(e.anchorMap[e.anchor]=i),c=e.input.charCodeAt(e.position);c!==0&&(e.firstTabInLine!==-1&&(e.position=e.firstTabInLine,S(e,"tab characters must not be used in indentation")),!(c!==45||(a=e.input.charCodeAt(e.position+1),!Q(a))));){if(s=!0,e.position++,j(e,!0,-1)&&e.lineIndent<=t){i.push(null),c=e.input.charCodeAt(e.position);continue}if(n=e.line,Ke(e,t,Ir,!1,!0),i.push(e.result),j(e,!0,-1),c=e.input.charCodeAt(e.position),(e.line===n||e.lineIndent>t)&&c!==0)S(e,"bad indentation of a sequence entry");else if(e.lineIndent<t)break}return s?(e.tag=o,e.anchor=r,e.kind="sequence",e.result=i,!0):!1}function pa(e,t,n){var o,r,i,a,s,c,d=e.tag,p=e.anchor,u={},h=Object.create(null),m=null,f=null,k=null,w=!1,g=!1,y;if(e.firstTabInLine!==-1)return!1;for(e.anchor!==null&&(e.anchorMap[e.anchor]=u),y=e.input.charCodeAt(e.position);y!==0;){if(!w&&e.firstTabInLine!==-1&&(e.position=e.firstTabInLine,S(e,"tab characters must not be used in indentation")),o=e.input.charCodeAt(e.position+1),i=e.line,(y===63||y===58)&&Q(o))y===63?(w&&(Ye(e,u,h,m,f,null,a,s,c),m=f=k=null),g=!0,w=!0,r=!0):w?(w=!1,r=!0):S(e,"incomplete explicit mapping pair; a key node is missed; or followed by a non-tabulated empty line"),e.position+=1,y=o;else{if(a=e.line,s=e.lineStart,c=e.position,!Ke(e,n,$r,!1,!0))break;if(e.line===i){for(y=e.input.charCodeAt(e.position);Be(y);)y=e.input.charCodeAt(++e.position);if(y===58)y=e.input.charCodeAt(++e.position),Q(y)||S(e,"a whitespace character is expected after the key-value separator within a block mapping"),w&&(Ye(e,u,h,m,f,null,a,s,c),m=f=k=null),g=!0,w=!1,r=!1,m=e.tag,f=e.result;else if(g)S(e,"can not read an implicit mapping pair; a colon is missed");else return e.tag=d,e.anchor=p,!0}else if(g)S(e,"can not read a block mapping entry; a multiline key may not be an implicit key");else return e.tag=d,e.anchor=p,!0}if((e.line===i||e.lineIndent>t)&&(w&&(a=e.line,s=e.lineStart,c=e.position),Ke(e,t,Mt,!0,r)&&(w?f=e.result:k=e.result),w||(Ye(e,u,h,m,f,k,a,s,c),m=f=k=null),j(e,!0,-1),y=e.input.charCodeAt(e.position)),(e.line===i||e.lineIndent>t)&&y!==0)S(e,"bad indentation of a mapping entry");else if(e.lineIndent<t)break}return w&&Ye(e,u,h,m,f,null,a,s,c),g&&(e.tag=d,e.anchor=p,e.kind="mapping",e.result=u),g}function ua(e){var t,n=!1,o=!1,r,i,a;if(a=e.input.charCodeAt(e.position),a!==33)return!1;if(e.tag!==null&&S(e,"duplication of a tag property"),a=e.input.charCodeAt(++e.position),a===60?(n=!0,a=e.input.charCodeAt(++e.position)):a===33?(o=!0,r="!!",a=e.input.charCodeAt(++e.position)):r="!",t=e.position,n){do a=e.input.charCodeAt(++e.position);while(a!==0&&a!==62);e.position<e.length?(i=e.input.slice(t,e.position),a=e.input.charCodeAt(++e.position)):S(e,"unexpected end of the stream within a verbatim tag")}else{for(;a!==0&&!Q(a);)a===33&&(o?S(e,"tag suffix cannot contain exclamation marks"):(r=e.input.slice(t-1,e.position+1),Lr.test(r)||S(e,"named tag handle cannot contain such characters"),o=!0,t=e.position+1)),a=e.input.charCodeAt(++e.position);i=e.input.slice(t,e.position),ea.test(i)&&S(e,"tag suffix cannot contain flow indicator characters")}i&&!Mr.test(i)&&S(e,"tag name cannot contain such characters: "+i);try{i=decodeURIComponent(i)}catch{S(e,"tag name is malformed: "+i)}return n?e.tag=i:Ee.call(e.tagMap,r)?e.tag=e.tagMap[r]+i:r==="!"?e.tag="!"+i:r==="!!"?e.tag="tag:yaml.org,2002:"+i:S(e,'undeclared tag handle "'+r+'"'),!0}function ha(e){var t,n;if(n=e.input.charCodeAt(e.position),n!==38)return!1;for(e.anchor!==null&&S(e,"duplication of an anchor property"),n=e.input.charCodeAt(++e.position),t=e.position;n!==0&&!Q(n)&&!je(n);)n=e.input.charCodeAt(++e.position);return e.position===t&&S(e,"name of an anchor node must contain at least one character"),e.anchor=e.input.slice(t,e.position),!0}function ma(e){var t,n,o;if(o=e.input.charCodeAt(e.position),o!==42)return!1;for(o=e.input.charCodeAt(++e.position),t=e.position;o!==0&&!Q(o)&&!je(o);)o=e.input.charCodeAt(++e.position);return e.position===t&&S(e,"name of an alias node must contain at least one character"),n=e.input.slice(t,e.position),Ee.call(e.anchorMap,n)||S(e,'unidentified alias "'+n+'"'),e.result=e.anchorMap[n],j(e,!0,-1),!0}function Ke(e,t,n,o,r){var i,a,s,c=1,d=!1,p=!1,u,h,m,f,k,w;if(e.listener!==null&&e.listener("open",e),e.tag=null,e.anchor=null,e.kind=null,e.result=null,i=a=s=Mt===n||Ir===n,o&&j(e,!0,-1)&&(d=!0,e.lineIndent>t?c=1:e.lineIndent===t?c=0:e.lineIndent<t&&(c=-1)),c===1)for(;ua(e)||ha(e);)j(e,!0,-1)?(d=!0,s=i,e.lineIndent>t?c=1:e.lineIndent===t?c=0:e.lineIndent<t&&(c=-1)):s=!1;if(s&&(s=d||r),(c===1||Mt===n)&&(Lt===n||$r===n?k=t:k=t+1,w=e.position-e.lineStart,c===1?s&&(Vn(e,w)||pa(e,w,k))||ca(e,k)?p=!0:(a&&da(e,k)||sa(e,k)||la(e,k)?p=!0:ma(e)?(p=!0,(e.tag!==null||e.anchor!==null)&&S(e,"alias node should not have any properties")):aa(e,k,Lt===n)&&(p=!0,e.tag===null&&(e.tag="?")),e.anchor!==null&&(e.anchorMap[e.anchor]=e.result)):c===0&&(p=s&&Vn(e,w))),e.tag===null)e.anchor!==null&&(e.anchorMap[e.anchor]=e.result);else if(e.tag==="?"){for(e.result!==null&&e.kind!=="scalar"&&S(e,'unacceptable node kind for !<?> tag; it should be "scalar", not "'+e.kind+'"'),u=0,h=e.implicitTypes.length;u<h;u+=1)if(f=e.implicitTypes[u],f.resolve(e.result)){e.result=f.construct(e.result),e.tag=f.tag,e.anchor!==null&&(e.anchorMap[e.anchor]=e.result);break}}else if(e.tag!=="!"){if(Ee.call(e.typeMap[e.kind||"fallback"],e.tag))f=e.typeMap[e.kind||"fallback"][e.tag];else for(f=null,m=e.typeMap.multi[e.kind||"fallback"],u=0,h=m.length;u<h;u+=1)if(e.tag.slice(0,m[u].tag.length)===m[u].tag){f=m[u];break}f||S(e,"unknown tag !<"+e.tag+">"),e.result!==null&&f.kind!==e.kind&&S(e,"unacceptable node kind for !<"+e.tag+'> tag; it should be "'+f.kind+'", not "'+e.kind+'"'),f.resolve(e.result,e.tag)?(e.result=f.construct(e.result,e.tag),e.anchor!==null&&(e.anchorMap[e.anchor]=e.result)):S(e,"cannot resolve a node with !<"+e.tag+"> explicit tag")}return e.listener!==null&&e.listener("close",e),e.tag!==null||e.anchor!==null||p}function fa(e){var t=e.position,n,o,r,i=!1,a;for(e.version=null,e.checkLineBreaks=e.legacy,e.tagMap=Object.create(null),e.anchorMap=Object.create(null);(a=e.input.charCodeAt(e.position))!==0&&(j(e,!0,-1),a=e.input.charCodeAt(e.position),!(e.lineIndent>0||a!==37));){for(i=!0,a=e.input.charCodeAt(++e.position),n=e.position;a!==0&&!Q(a);)a=e.input.charCodeAt(++e.position);for(o=e.input.slice(n,e.position),r=[],o.length<1&&S(e,"directive name must not be less than one character in length");a!==0;){for(;Be(a);)a=e.input.charCodeAt(++e.position);if(a===35){do a=e.input.charCodeAt(++e.position);while(a!==0&&!se(a));break}if(se(a))break;for(n=e.position;a!==0&&!Q(a);)a=e.input.charCodeAt(++e.position);r.push(e.input.slice(n,e.position))}a!==0&&Cn(e),Ee.call(Kn,o)?Kn[o](e,o,r):At(e,'unknown document directive "'+o+'"')}if(j(e,!0,-1),e.lineIndent===0&&e.input.charCodeAt(e.position)===45&&e.input.charCodeAt(e.position+1)===45&&e.input.charCodeAt(e.position+2)===45?(e.position+=3,j(e,!0,-1)):i&&S(e,"directives end mark is expected"),Ke(e,e.lineIndent-1,Mt,!1,!0),j(e,!0,-1),e.checkLineBreaks&&Ji.test(e.input.slice(t,e.position))&&At(e,"non-ASCII line breaks are interpreted as content"),e.documents.push(e.result),e.position===e.lineStart&&jt(e)){e.input.charCodeAt(e.position)===46&&(e.position+=3,j(e,!0,-1));return}if(e.position<e.length-1)S(e,"end of the stream or a document separator is expected");else return}function ga(e,t){e=String(e),t=t||{},e.length!==0&&(e.charCodeAt(e.length-1)!==10&&e.charCodeAt(e.length-1)!==13&&(e+=`
`),e.charCodeAt(0)===65279&&(e=e.slice(1)));var n=new ia(e,t),o=e.indexOf("\0");for(o!==-1&&(n.position=o,S(n,"null byte is not allowed in input")),n.input+="\0";n.input.charCodeAt(n.position)===32;)n.lineIndent+=1,n.position+=1;for(;n.position<n.length-1;)fa(n);return n.documents}function xa(e,t){var n=ga(e,t);if(n.length!==0){if(n.length===1)return n[0];throw new de("expected a single document in the stream, but found more")}}var ba=xa,ya={load:ba},wa=ya.load;const ka="https://app.plurality.network";class we{static instance=null;schema=null;API_URL=`${ka}/domSelectors/v1.yaml`;constructor(){}static getInstance(){return we.instance||(we.instance=new we),we.instance}async loadSchema(){try{const t=await fetch(this.API_URL,{cache:"no-store"});if(!t.ok)throw new Error(`API request failed: ${t.status} ${t.statusText}`);let n;try{n=await t.text()}catch(o){throw new Error(`Failed to read response body: ${o instanceof Error?o.message:String(o)}`)}if(!n||n.trim().length===0)throw new Error("API returned empty response");this.schema=wa(n),this.validateSchema()}catch(t){throw new Error(`YAML schema loading failed: ${t instanceof Error?t.message:String(t)}`)}}validateSchema(){if(!this.schema)throw new Error("Schema is null after loading");if(!["chatGPT","grok","claude","perplexity","gemini","deepseek"].some(o=>this.schema!==null&&o in this.schema&&this.schema[o]!==void 0))throw new Error("Schema must contain at least one platform configuration")}getSchema(){if(!this.schema)throw new Error("Schema not loaded. Call loadSchema() first.");return this.schema}getServiceConfig(t){if(!this.schema)throw new Error("Schema not loaded. Call loadSchema() first.");return this.schema[t]||null}getFlowConfig(t,n){const o=this.getServiceConfig(t);if(!o)return null;const r=o[n];return r||null}hasPlatform(t){return this.schema?t in this.schema&&this.schema[t]!==void 0:!1}hasFlow(t,n){const o=this.getServiceConfig(t);return o?n in o&&o[n]!==void 0:!1}getPlatforms(){if(!this.schema)return[];const t=[],n=["chatGPT","grok","claude","perplexity","gemini","deepseek"];for(const o of n)this.hasPlatform(o)&&t.push(o);return t}getFlows(t){const n=this.getServiceConfig(t);if(!n)return[];const o=[],r=["checkStatus","loginButton","inputField","profilesDropdown","chatHistory","currentQuery","newChat"];for(const i of r)i in n&&n[i]!==void 0&&o.push(i);return o}async reload(){this.schema=null,await this.loadSchema()}static resetInstance(){we.instance=null}}const va=()=>we.getInstance();function Qn(e){return"any"in e&&Array.isArray(e.any)&&typeof e.any[0]=="string"}function Ca(e){return"insert"in e&&typeof e.insert=="object"}function Ea(e){return"find"in e&&typeof e.find=="object"&&"user"in e.find&&"assistant"in e.find&&"extract"in e}function Ta(e){return"any"in e&&Array.isArray(e.any)&&e.any.length>0&&typeof e.any[0]=="object"&&"find"in e.any[0]&&"insert"in e.any[0]}class Sa{loader=va();async executeFlow(t,n,o){const r=this.loader.getFlowConfig(t,n);if(!r)return console.warn(`[ServiceExecutor] No configuration for ${t}.${n}`),null;const i=o?.context||document;return Qn(r)?this.executeAny(r,i):Ta(r)?o?.elementToInsert?this.executeAnyInsertion(r,o.elementToInsert):(console.error("[ServiceExecutor] AnyInsertion requires elementToInsert option"),null):Ca(r)?o?.elementToInsert?this.executeInsertion(r,o.elementToInsert):(console.error("[ServiceExecutor] Insertion requires elementToInsert option"),null):Ea(r)?this.executeRoleBasedExtraction(r,i):(console.error(`[ServiceExecutor] Unknown policy type for ${t}.${n}`),null)}executeAny(t,n){return To(t,n)}executeInsertion(t,n){return vr(t,n)}executeRoleBasedExtraction(t,n){return Lo(t,n)}executeAnyInsertion(t,n){return Mo(t,n)}async checkStatus(t){return(await this.executeFlow(t,"checkStatus"))?.element||null}async findLoginButton(t){return(await this.executeFlow(t,"loginButton"))?.element||null}async findInputField(t){return(await this.executeFlow(t,"inputField"))?.element||null}async getCurrentQuery(t){return(await this.executeFlow(t,"currentQuery"))?.element||null}async findNewChatButton(t){return(await this.executeFlow(t,"newChat"))?.element||null}async insertProfilesDropdown(t,n){return await this.executeFlow(t,"profilesDropdown",{elementToInsert:n})}async extractChatHistory(t,n){return await this.executeFlow(t,"chatHistory",{context:n})}async waitForFlowElement(t,n,o=5e3){const r=this.loader.getFlowConfig(t,n);return r?Qn(r)?Po(r.any,o):(console.warn("[ServiceExecutor] waitForFlowElement only supports Any policy"),null):null}async getCurrentQueryText(t){const n=await this.getCurrentQuery(t);return n?n instanceof HTMLInputElement||n instanceof HTMLTextAreaElement?n.value:n.getAttribute("contenteditable")==="true"?n.innerText||n.textContent||"":n.textContent||"":""}async setInputText(t,n){const o=await this.getCurrentQuery(t);if(!o)return!1;try{if(t==="perplexity"&&o.getAttribute("data-lexical-editor")==="true"){const r=o;r.focus(),r.dispatchEvent(new KeyboardEvent("keydown",{key:"a",code:"KeyA",ctrlKey:!0,bubbles:!0})),r.dispatchEvent(new KeyboardEvent("keydown",{key:"Backspace",code:"Backspace",bubbles:!0}));const i=new ClipboardEvent("paste",{bubbles:!0,cancelable:!0,clipboardData:new DataTransfer});return i.clipboardData?.setData("text/plain",n),r.dispatchEvent(i),!0}if(o instanceof HTMLInputElement||o instanceof HTMLTextAreaElement)return o.value=n,o.dispatchEvent(new Event("input",{bubbles:!0})),o.dispatchEvent(new Event("change",{bubbles:!0})),!0;if(o.getAttribute("contenteditable")==="true"){const r=o;if(t==="claude"){r.focus(),r.innerHTML="";const i=document.createElement("p");return i.textContent=n,r.appendChild(i),r.dispatchEvent(new InputEvent("input",{bubbles:!0,cancelable:!0})),r.dispatchEvent(new Event("change",{bubbles:!0})),!0}return r.textContent=n,r.dispatchEvent(new Event("input",{bubbles:!0})),r.focus(),!0}return!1}catch(r){return console.error("[ServiceExecutor] Failed to set input text:",r),!1}}async isValid(t){return await this.checkStatus(t)!==null}}let rn=null;function Yt(){return rn||(rn=new Sa),rn}const $a=()=>navigator.platform?.toUpperCase().includes("MAC")||navigator.userAgentData?.platform==="macOS",Ia=()=>$a()?"⌘":"Ctrl",dn=e=>`${Ia()}+${e}`,re=()=>{const e=window.location.href,t=window.location.pathname;return e.includes("chat.openai.com")?"chatGPT":e.includes("claude.ai")?"claude":t.includes("grok")||e.includes("grok")?"grok":e.includes("perplexity.ai")?"perplexity":e.includes("gemini.google.com")?"gemini":e.includes("deepseek.com")?"deepseek":e.includes("v0.dev")?"v0":"chatGPT"},Nr=async()=>{try{const e=re(),n=await Yt().extractChatHistory(e);if(!n||!n.messages||n.messages.length===0)return{query:"",chatHistory:[]};const o=n.messages.filter(i=>i.role==="user");return{query:o.length>0?o[o.length-1].content:"",chatHistory:n.messages}}catch(e){return console.error("[extractChatHistory] Error:",e),{query:"",chatHistory:[]}}},La=async()=>{try{const e=re();return(await Yt().getCurrentQueryText(e)).trim()}catch(e){return console.error("[getCurrentQuery] Error:",e),""}};let Zn=!1;const _=()=>{Zn||(Zn=!0)},ft=e=>e instanceof Error&&e.message.includes("Extension context invalidated"),Jn=window.__pluralityAbortController;Jn&&Jn.abort();const Dr=new AbortController;window.__pluralityAbortController=Dr;const O=Dr.signal,ht="https://app.plurality.network",Ma=e=>{try{const n=new URL(ht).origin;return e===n}catch(t){return console.error("[Plurality] Invalid APP_BASE_URL:",ht,t),!1}},Aa=()=>{const e=()=>{window.postMessage({source:"plurality-extension",action:"extensionReady"},"*")};console.log("[Plurality][DEBUG] Content script loaded, notifying extensionReady. APP_BASE_URL:",ht,"current origin:",window.location.origin),e(),setTimeout(e,100),setTimeout(e,500),window.addEventListener("message",t=>{if(!Ma(t.origin)){t.data.source==="plurality-app"&&console.error("[Plurality][DEBUG] Origin REJECTED:",t.origin,"APP_BASE_URL:",ht);return}if(t.data.source==="plurality-app"){const n=t.data.action;switch(console.log("[Plurality][DEBUG] Received postMessage from webapp:",n,t.data),n){case"requestExtensionStatus":e();break;case"loginSuccess":console.log("[Plurality][DEBUG] loginSuccess received, token:",!!t.data.token,"chatEncKey:",!!t.data.chatEncKey,"userId:",t.data.userId);try{chrome.runtime.sendMessage({action:"handleLoginSuccess",token:t.data.token,chatEncKey:t.data.chatEncKey,userId:t.data.userId},o=>{if(console.log("[Plurality][DEBUG] handleLoginSuccess response:",o),chrome.runtime.lastError){const r=chrome.runtime.lastError.message;console.error("[Plurality] Error sending login success:",r),r&&r.includes("Extension context invalidated")&&(_(),window.postMessage({source:"plurality-extension",action:"extensionNeedsRefresh"},"*"))}else o&&!o.success?console.error("[Plurality] Login success handling failed:",o.error):window.postMessage({source:"plurality-extension",action:"loginSuccessAcknowledged"},"*")})}catch(o){console.error("[Plurality] Exception during login success:",o),o instanceof Error&&o.message.includes("Extension context invalidated")&&(_(),window.postMessage({source:"plurality-extension",action:"extensionNeedsRefresh"},"*"))}break;case"newProfileCreated":case"profileEdited":case"profileDeleted":chrome.runtime.sendMessage({action:"broadcastProfileEvent",eventType:t.data.action,profiles:t.data.profiles,profileId:t.data.profileId||null},o=>{chrome.runtime.lastError?console.error("[Plurality] Error broadcasting profile event:",chrome.runtime.lastError):o&&!o.success&&console.error("[Plurality] Profile broadcast failed:",o.error)});break;case"accountDeleted":chrome.runtime.sendMessage({action:"accountDeleted"},()=>{chrome.runtime.lastError&&console.error("[Plurality] Error handling account deletion:",chrome.runtime.lastError)});break;case"userChoseExtension":case"tourCompleted":break;case"saveContextComplete":chrome.runtime.sendMessage({action:"closeTabAndFocusSource"},()=>{chrome.runtime.lastError&&console.error("[Plurality] Error requesting close and focus:",chrome.runtime.lastError)});break;case"requestOpenPopup":chrome.runtime.sendMessage({action:"openPopup"},()=>{chrome.runtime.lastError&&console.error("[Plurality] Error requesting popup open:",chrome.runtime.lastError)});break}}},{signal:O})},Pa=async e=>{const t=await La();if(!t.trim())return{success:!1,error:"Please type a query in the input box first"};const n=await Ce();if(!n.isLoggedIn||!n.token)return{success:!1,error:"Please login first"};const{chatHistory:o}=await Nr(),r={query:t.trim(),chatHistory:o.length>0?o:[],profileId:e==="12345678-1234-1234-1234-123456789abc"?"":e,platform:re()};return new Promise(i=>{try{chrome.runtime.sendMessage({action:"getOptimizedQuery",payload:{context:r},token:n.token},a=>{if(chrome.runtime.lastError){const s=chrome.runtime.lastError.message;s&&s.includes("Extension context invalidated")&&_(),i({success:!1,error:s})}else i(a)})}catch(a){a instanceof Error&&a.message.includes("Extension context invalidated")&&_(),i({success:!1,error:a instanceof Error?a.message:"Unknown error"})}})},er=async(e="",t=!1)=>{const n=await Ce();if(!n.isLoggedIn||!n.token)return{success:!1,error:"Please login first"};const{chatHistory:o}=await Nr();if(!o||o.length===0)return{success:!1,error:"No chat content found to save"};const r={chatHistory:o,profileId:e,platform:re(),sourceUrl:typeof window<"u"?window.location.href:""};return new Promise(i=>{try{chrome.runtime.sendMessage({action:"saveContext",payload:{profileId:e,context:r},token:n.token,skipNotification:t},async a=>{if(chrome.runtime.lastError){const s=chrome.runtime.lastError.message;s&&s.includes("Extension context invalidated")&&_(),i({success:!1,error:s})}else if(a.success&&a.data){if(a.newProfileId)try{const s=await new Promise(c=>{chrome.runtime.sendMessage({action:"refreshProfiles",token:n.token},d=>{chrome.runtime.lastError?(console.error("Refresh profiles error:",chrome.runtime.lastError),c({success:!1})):c(d)})});s.success&&s.profiles&&(await chrome.storage.local.set({selectedProfileId:a.newProfileId}),chrome.runtime.sendMessage({action:"newProfileCreated",profileId:a.newProfileId,profiles:s.profiles,skipNotification:t}))}catch(s){console.error("Failed to refresh profiles:",s)}i({success:!0,data:a.data,message:"Context saved successfully!",newProfileId:a.newProfileId})}else i(a)})}catch(a){a instanceof Error&&a.message.includes("Extension context invalidated")&&_(),i({success:!1,error:a instanceof Error?a.message:"Unknown error"})}})},Ba=async e=>{try{const t=re(),o=await Yt().setInputText(t,e);return o||console.error(`[replacePrompt] Failed to set input text for ${t}`),o}catch(t){return console.error("[replacePrompt] Error:",t),!1}},Rr={primary:"#667eea",primaryRgb:"102, 126, 234",primaryGradient:"linear-gradient(135deg, #667eea 0%, #764ba2 100%)",extensionAccent:"#8002FF",extensionAccentRgb:"128, 2, 255",background:"#ffffff",backgroundSecondary:"#f8f9fa",backgroundGradient:"linear-gradient(135deg, #fafafa 0%, #f5f5f5 100%)",backgroundHover:"#f0f0f0",backgroundSelected:"#e8e8ff",textPrimary:"#000000",textSecondary:"#363837",textMuted:"#969595",border:"#e0e0e0",borderLight:"#f0f0f0",shadowColor:"rgba(0, 0, 0, 0.12)",shadowPrimary:"rgba(102, 126, 234, 0.3)",success:"#00CEBA",error:"#FF0080",warning:"#FF4E00",info:"#00B8FF"},Na={primary:"#00CEBA",primaryRgb:"0, 206, 186",primaryGradient:"linear-gradient(135deg, #667eea 0%, #764ba2 100%)",extensionAccent:"#00CEBA",extensionAccentRgb:"0, 206, 186",background:"#1a1a1a",backgroundSecondary:"#252525",backgroundGradient:"linear-gradient(135deg, #1a1a1a 0%, #252525 100%)",backgroundHover:"#333333",backgroundSelected:"#1a3d3a",textPrimary:"#E3E4E4",textSecondary:"#969595",textMuted:"#6b6b6b",border:"#363837",borderLight:"#2d2d2d",shadowColor:"rgba(0, 0, 0, 0.5)",shadowPrimary:"rgba(102, 126, 234, 0.3)",success:"#00CEBA",error:"#ef4444",warning:"#FF4E00",info:"#00B8FF"},Da=e=>e==="dark"?Na:Rr;let Fr=Rr;const on=e=>{Fr=Da(e)},U=()=>Fr;let Et="",Tt="";try{Et=chrome.runtime.getURL("icons/icon48.png"),Tt=chrome.runtime.getURL("fonts/lexend.css")}catch{}function _e(){if(!Et)try{Et=chrome.runtime.getURL("icons/icon48.png")}catch{}return Et}function Ra(){if(!Tt)try{Tt=chrome.runtime.getURL("fonts/lexend.css")}catch{}return Tt}const B=(e,t="info",n=3e3)=>{const o=document.querySelector("[data-plurality-snackbar]");o&&o.remove();const r=U(),i={success:{borderColor:r.success,icon:"✓",iconColor:r.success},error:{borderColor:r.error,icon:"✕",iconColor:r.error},warning:{borderColor:r.warning,icon:"⚠",iconColor:r.warning},info:{borderColor:r.info,icon:"ℹ",iconColor:r.info}},{borderColor:a,icon:s,iconColor:c}=i[t],d=document.createElement("div");d.setAttribute("data-plurality-snackbar","true"),Object.assign(d.style,{position:"fixed",top:"0",left:"0",width:"100%",height:"100%",pointerEvents:"none",zIndex:"2147483647"});const p=document.createElement("div");Object.assign(p.style,{position:"absolute",top:"20px",right:"30px",transform:"translateX(100px)",background:r.background,padding:"14px 16px",borderRadius:"12px",display:"flex",alignItems:"flex-start",gap:"12px",boxShadow:`0 4px 20px ${r.shadowColor}`,minWidth:"320px",maxWidth:"420px",border:`2px solid ${a}`,opacity:"0",transition:"all 0.35s cubic-bezier(0.4, 0, 0.2, 1)",pointerEvents:"none",fontFamily:'-apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif'});const u=document.createElement("img");u.src=_e(),u.alt="AI Context Flow",Object.assign(u.style,{width:"36px",height:"36px",borderRadius:"8px",flexShrink:"0",objectFit:"contain"});const h=document.createElement("div");Object.assign(h.style,{width:"36px",height:"36px",background:"linear-gradient(135deg, #8A2BE2, #6B21A8)",borderRadius:"8px",display:"none",alignItems:"center",justifyContent:"center",color:"white",fontWeight:"bold",fontSize:"16px",flexShrink:"0"}),h.textContent="A",u.onerror=()=>{u.style.display="none",h.style.display="flex"};const m=document.createElement("div");Object.assign(m.style,{display:"flex",flexDirection:"column",gap:"2px",flex:"1"});const f=document.createElement("div");Object.assign(f.style,{fontSize:"13px",fontWeight:"600",color:r.textPrimary,display:"flex",alignItems:"center",gap:"6px"});const k=document.createElement("span");k.textContent="AI Context Flow";const w=document.createElement("span");w.textContent=s,Object.assign(w.style,{fontSize:"12px",color:c}),f.appendChild(k),f.appendChild(w);const g=document.createElement("div");g.innerHTML=e,Object.assign(g.style,{fontSize:"13px",color:r.textSecondary,lineHeight:"1.4"});const y=document.createElement("style");y.setAttribute("data-plurality-snackbar-style","true"),y.textContent=`
    [data-plurality-snackbar] .keyboard-shortcut {
      background-color: ${r.backgroundSecondary};
      padding: 2px 6px;
      border-radius: 4px;
      font-weight: 600;
      font-family: monospace;
      font-size: 12px;
      color: ${r.textPrimary};
      border: 1px solid ${r.border};
      margin: 0 2px;
    }
  `,document.head.appendChild(y),m.appendChild(f),m.appendChild(g),p.appendChild(u),p.appendChild(h),p.appendChild(m),d.appendChild(p),document.body.appendChild(d),p.offsetHeight,requestAnimationFrame(()=>{p.style.opacity="1",p.style.transform="translateX(0)"}),setTimeout(()=>{p.style.opacity="0",p.style.transform="translateX(100px)",setTimeout(()=>{d.parentNode&&d.parentNode.removeChild(d);const x=document.querySelector("[data-plurality-snackbar-style]");x&&x.remove()},350)},n)},Fa=["chat.openai.com","chatgpt.com","perplexity.ai","gemini.google.com","claude.ai"],za=e=>{try{const{hostname:t,pathname:n}=new URL(e);return t.includes("grok.com")?n==="/"||n.startsWith("/c"):Fa.some(o=>t.includes(o))}catch{return!1}},Re=()=>za(window.location.href);class Ae{static instance;yamlLoader;isInitialized=!1;initializationPromise=null;constructor(){this.yamlLoader=we.getInstance()}static getInstance(){return Ae.instance||(Ae.instance=new Ae),Ae.instance}async initialize(){if(!this.isInitialized){if(this.initializationPromise)return this.initializationPromise;this.initializationPromise=this.loadFromYAML(),await this.initializationPromise}}async loadFromYAML(){try{await this.yamlLoader.loadSchema(),this.isInitialized=!0}catch(t){throw this.isInitialized=!1,t}}async reload(){this.isInitialized=!1,this.initializationPromise=null;try{return await this.yamlLoader.reload(),this.isInitialized=!0,!0}catch{return!1}}async refreshFromAPI(){return this.reload()}getSelector(t,n){if(!this.isInitialized)throw new Error("DOMSelectorManager not initialized. Call initialize() first.");const o=this.yamlLoader.getServiceConfig(t);if(!o)return console.warn(`[DOMSelectorManager] No service config found for platform: ${t}`),[];const r=n.split(".");let i=o;for(const a of r)if(i&&typeof i=="object"&&a in i)i=i[a];else return console.warn(`[DOMSelectorManager] Key path not found: ${t}.${n} (failed at: ${a})`),[];if(Array.isArray(i))return i.filter(s=>typeof s=="string");if(i&&typeof i=="object"){if("any"in i&&Array.isArray(i.any))return i.any;if("all"in i&&Array.isArray(i.all))return i.all;console.warn(`[DOMSelectorManager] ${t}.${n} is an object without 'any'/'all':`,i)}return typeof i=="string"?[i]:(console.warn(`[DOMSelectorManager] ${t}.${n} returned no selectors, type:`,typeof i),[])}getAllSelectors(t,n){const r=this.getSelector(t,n).filter(i=>i&&i.trim()!=="");return r.length===0?(console.warn(`[DOMSelectorManager] No valid selectors found for ${t}.${n}`),""):r.join(", ")}getLoader(){return this.yamlLoader}}let me,kt=null;const Ha=async()=>kt||(kt=(async()=>{me=Ae.getInstance(),await me.initialize()})(),kt),_a=async()=>(me||(me=Ae.getInstance()),me.refreshFromAPI()),Tn=()=>{if(!me)throw new Error("❌ DOMSelectorManager not initialized. Call initializeDOMSelectors() first.")},tr=(e,t)=>(Tn(),me.getSelector(e,t)),ke=(e,t)=>(Tn(),me.getAllSelectors(e,t)),Oa=e=>ke(e,"checkStatus"),Ua=e=>(Tn(),me.yamlLoader.getServiceConfig(e)?.loginButton);let St=null;const nr=()=>{const e=U();return`
  .plurality-onboarding-tooltip {
    position: fixed !important;
    background: ${e.background} !important;
    border-radius: 12px !important;
    box-shadow: 0 8px 32px ${e.shadowColor} !important;
    border: 1px solid ${e.border} !important;
    padding: 16px !important;
    max-width: 280px !important;
    z-index: 2147483647 !important;
    animation: plurality-tooltip-enter 0.3s ease !important;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
    box-sizing: border-box !important;
    text-align: left !important;
    line-height: normal !important;
    letter-spacing: normal !important;
    text-transform: none !important;
    float: none !important;
    margin: 0 !important;
    width: auto !important;
    height: auto !important;
    min-height: 0 !important;
    user-select: none !important;
    -webkit-user-select: none !important;
  }

  .plurality-onboarding-tooltip * {
    box-sizing: border-box !important;
  }

  @keyframes plurality-tooltip-enter {
    from {
      opacity: 0;
      transform: translateY(10px);
    }
    to {
      opacity: 1;
      transform: translateY(0);
    }
  }

  .plurality-onboarding-tooltip.fading-out {
    animation: plurality-tooltip-exit 0.2s ease forwards !important;
  }

  @keyframes plurality-tooltip-exit {
    from {
      opacity: 1;
      transform: translateY(0);
    }
    to {
      opacity: 0;
      transform: translateY(10px);
    }
  }

  .plurality-tooltip-arrow {
    position: absolute !important;
    width: 12px !important;
    height: 12px !important;
    background: ${e.background} !important;
    transform: rotate(45deg) !important;
    padding: 0 !important;
    margin: 0 !important;
    border-radius: 0 !important;
  }

  /* Arrow pointing down (tooltip above target) */
  .plurality-tooltip-arrow.top {
    bottom: -6px !important;
    left: 50% !important;
    transform: translateX(-50%) rotate(45deg) !important;
    box-shadow: 2px 2px 4px ${e.shadowColor} !important;
    border-right: 1px solid ${e.border} !important;
    border-bottom: 1px solid ${e.border} !important;
    border-left: none !important;
    border-top: none !important;
  }

  /* Arrow pointing up (tooltip below target) */
  .plurality-tooltip-arrow.bottom {
    top: -6px !important;
    left: 50% !important;
    transform: translateX(-50%) rotate(45deg) !important;
    box-shadow: -2px -2px 4px ${e.shadowColor} !important;
    border-left: 1px solid ${e.border} !important;
    border-top: 1px solid ${e.border} !important;
    border-right: none !important;
    border-bottom: none !important;
  }

  /* Arrow pointing right (tooltip to the left of target) */
  .plurality-tooltip-arrow.left {
    right: -6px !important;
    top: 50% !important;
    transform: translateY(-50%) rotate(45deg) !important;
    box-shadow: 2px -2px 4px ${e.shadowColor} !important;
    border-right: 1px solid ${e.border} !important;
    border-top: 1px solid ${e.border} !important;
    border-left: none !important;
    border-bottom: none !important;
  }

  /* Arrow pointing left (tooltip to the right of target) */
  .plurality-tooltip-arrow.right {
    left: -6px !important;
    top: 50% !important;
    transform: translateY(-50%) rotate(45deg) !important;
    box-shadow: -2px 2px 4px ${e.shadowColor} !important;
    border-left: 1px solid ${e.border} !important;
    border-bottom: 1px solid ${e.border} !important;
    border-right: none !important;
    border-top: none !important;
  }

  .plurality-tooltip-title {
    font-size: 14px !important;
    font-weight: 600 !important;
    color: ${e.textPrimary} !important;
    margin: 0 0 8px 0 !important;
    line-height: 1.4 !important;
    padding: 0 !important;
    text-align: left !important;
    letter-spacing: normal !important;
    text-transform: none !important;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
    border: none !important;
    background: none !important;
    display: block !important;
    float: none !important;
    width: auto !important;
    height: auto !important;
  }

  .plurality-tooltip-content {
    font-size: 13px !important;
    color: ${e.textPrimary} !important;
    line-height: 1.5 !important;
    margin: 0 0 12px 0 !important;
    padding: 0 !important;
    text-align: left !important;
    letter-spacing: normal !important;
    text-transform: none !important;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
    border: none !important;
    background: none !important;
    display: block !important;
    float: none !important;
    width: auto !important;
    height: auto !important;
  }

  .plurality-tooltip-dismiss {
    display: inline-block !important;
    padding: 8px 16px !important;
    background: ${e.primaryGradient} !important;
    color: white !important;
    border: none !important;
    border-radius: 8px !important;
    font-size: 13px !important;
    font-weight: 500 !important;
    cursor: pointer !important;
    transition: all 0.2s ease !important;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
    line-height: normal !important;
    letter-spacing: normal !important;
    text-transform: none !important;
    text-align: center !important;
    text-decoration: none !important;
    box-sizing: border-box !important;
    margin: 0 !important;
    float: none !important;
    width: auto !important;
    height: auto !important;
    min-width: 0 !important;
    min-height: 0 !important;
    max-width: none !important;
    appearance: none !important;
    -webkit-appearance: none !important;
  }

  .plurality-tooltip-dismiss:hover {
    transform: translateY(-1px) !important;
    box-shadow: 0 4px 12px ${e.shadowPrimary} !important;
  }
`},zr=()=>{const e=document.getElementById("plurality-tooltip-styles");if(e)e.textContent=nr();else{const t=document.createElement("style");t.id="plurality-tooltip-styles",t.textContent=nr(),document.head.appendChild(t)}},qa=1e3,nt=new Map,rr=new Set,Pt=async(e,t,n,o,r=qa)=>{if(!rr.has(e)){nt.has(e)&&(clearTimeout(nt.get(e)),nt.delete(e));try{if(((await chrome.storage.sync.get(["onboarding"])).onboarding||{tooltips:{}}).tooltips?.[e])return;const s=window.setTimeout(()=>{nt.delete(e),!(!t||!document.body.contains(t))&&(rr.add(e),ja(t,n,()=>{Bt(e),o?.()}))},r);nt.set(e,s)}catch(i){console.error("[Plurality] Error checking tooltip state:",i)}}},ja=(e,t,n)=>{be(),zr();const o=document.createElement("div");o.className="plurality-onboarding-tooltip";const r=document.createElement("div");r.className=`plurality-tooltip-arrow ${t.position}`,o.innerHTML=`
    <h4 class="plurality-tooltip-title">${t.title}</h4>
    <p class="plurality-tooltip-content">${t.content}</p>
    <button class="plurality-tooltip-dismiss">Got it!</button>
  `,o.appendChild(r),document.body.appendChild(o),Ya(o,e,t.position);let i=!1;const a=()=>{i||(i=!0,be(),c(),n?.())},s=p=>{o.contains(p.target)||a()},c=()=>{window.removeEventListener("scroll",a),window.removeEventListener("resize",a),document.removeEventListener("mousedown",s)};o.querySelector(".plurality-tooltip-dismiss")?.addEventListener("click",a),t.dismissAfter&&setTimeout(a,t.dismissAfter),St=o,window.addEventListener("scroll",a,{once:!0,signal:O}),window.addEventListener("resize",a,{once:!0,signal:O}),setTimeout(()=>{document.addEventListener("mousedown",s,{signal:O})},0)},Ya=(e,t,n)=>{const o=t.getBoundingClientRect(),r=e.getBoundingClientRect();let i=0,a=0;switch(n){case"top":i=o.top-r.height-12,a=o.left+o.width/2-r.width/2;break;case"bottom":i=o.bottom+12,a=o.left+o.width/2-r.width/2;break;case"left":i=o.top+o.height/2-r.height/2,a=o.left-r.width-12;break;case"right":i=o.top+o.height/2-r.height/2,a=o.right+12;break}const s=16;a=Math.max(s,Math.min(a,window.innerWidth-r.width-s)),i=Math.max(s,Math.min(i,window.innerHeight-r.height-s)),e.style.top=`${i}px`,e.style.left=`${a}px`},be=()=>{if(St){const e=St;St=null,e.classList.add("fading-out"),setTimeout(()=>{e.remove()},200)}},Bt=async e=>{try{const n=(await chrome.storage.sync.get(["onboarding"])).onboarding||{tooltips:{}};n.tooltips={...n.tooltips,[e]:!0},await chrome.storage.sync.set({onboarding:n})}catch(t){console.error("[Plurality] Error marking tooltip as shown:",t)}},Wa=e=>e.role!=="viewer";let lt=!1;const Ga=(e,t)=>{chrome.storage.local.get(["profiles"],n=>{const r=(n.profiles||[]).map(i=>i.id===e?{...i,contextCount:i.contextCount+t}:i);chrome.storage.local.set({profiles:r})})};let Hr=null,_r=null,or=!1;const Nt=async()=>{if(!Re())return;if((await new Promise(g=>{chrome.storage.sync.get(["onboarding"],y=>g(y))})).onboarding?.hideChatAgentIcons){const g=document.getElementById("plurality-sync-button");if(g){const y=g.parentElement;y&&y.tagName==="DIV"&&!y.id&&y.children.length===1?y.remove():g.remove()}document.getElementById("plurality-sync-dropdown")?.remove();return}const t="plurality-sync-button",n="plurality-sync-dropdown";if(lt&&document.getElementById(t))return;const o=document.getElementById(t);if(o){const g=o.parentElement;g&&g.tagName==="DIV"&&!g.id&&g.children.length===1?g.remove():o.remove()}document.getElementById(n)?.remove();const r=re(),i=ke(r,"checkStatus");if(!i||i.trim()===""){console.warn(`[Plurality] No checkStatus selector found for platform: ${r}`);return}const a=document.querySelector(i);if(!a||!a.parentElement)return;const c=U(),d=document.createElement("div");d.id=t,d.style.width="35px",d.style.height="35px",d.style.cursor="pointer",d.style.borderRadius="50%",d.style.boxShadow=`0 4px 12px ${c.shadowColor}, 0 0 0 2px rgba(${c.extensionAccentRgb}, 0.3)`,d.style.transition="all 0.3s ease",d.style.display="flex",d.style.alignItems="center",d.style.justifyContent="center",d.style.backgroundColor=c.background,d.style.marginRight="6px",d.style.position="relative";const p=document.createElement("div");p.style.width="60%",p.style.aspectRatio="1 / 1",p.style.height="auto";const u=_e();if(!u){_();return}p.style.backgroundImage=`url(${u})`,p.style.backgroundSize="contain",p.style.backgroundPosition="center",p.style.backgroundRepeat="no-repeat",p.style.transition="opacity 0.3s ease",d.appendChild(p);const h=document.createElement("div");h.style.width="20px",h.style.height="20px",h.style.boxSizing="border-box",h.style.border=`3px solid rgba(${c.extensionAccentRgb}, 0.3)`,h.style.borderRadius="50%",h.style.borderTop=`3px solid ${c.extensionAccent}`,h.style.display="none",h.style.position="absolute",h.style.top="50%",h.style.left="50%",h.style.marginTop="-10px",h.style.marginLeft="-10px",h.style.animation="spin 1s linear infinite",d.appendChild(h),d.addEventListener("mouseenter",()=>{d.style.transform="scale(1.1)",d.style.boxShadow=`0 6px 16px rgba(${c.extensionAccentRgb}, 0.4), 0 0 0 3px rgba(${c.extensionAccentRgb}, 0.5)`}),d.addEventListener("mouseleave",()=>{d.style.transform="scale(1)",d.style.boxShadow=`0 4px 12px ${c.shadowColor}, 0 0 0 2px rgba(${c.extensionAccentRgb}, 0.3)`});const m=Ka(n),f=()=>{p.style.display="none",h.style.display="block",d.style.pointerEvents="none",d.style.opacity="0.7",d.setAttribute("aria-busy","true")},k=()=>{h.style.display="none",p.style.display="block",d.style.pointerEvents="auto",d.style.opacity="1",d.removeAttribute("aria-busy")};Hr=f,_r=k,d.addEventListener("click",async g=>{g.preventDefault(),g.stopPropagation(),g.stopImmediatePropagation(),be(),(await Ce()).isLoggedIn||chrome.runtime.sendMessage({action:"openPopup",source:"syncButton"})}),Xa(d,m,f,k);const w=Ua(r);if(w?.insert){const g=w.insert,y=g.position||"append";let x=null;if(g.relative){const v=g.relative?.any||[];for(const C of v)if(x=document.querySelector(C),x)break}let b=null;if(g.into==="self"&&x)b=x;else if(g.into&&typeof g.into=="object"&&"traverseUp"in g.into){if(x){const v=g.into.traverseUp?.any||[];let C=x.parentElement;for(;C;){for(const T of v)if(C.matches(T)){b=C;break}if(b)break;C=C.parentElement}}}else if(g.into&&typeof g.into=="object"&&"any"in g.into){const v=g.into.any||[];for(const C of v)if(b=document.querySelector(C),b)break}if(b){if(x&&(y==="before"||y==="after")&&!b.contains(x)){const C=g.into&&typeof g.into=="object"&&"any"in g.into?g.into.any||[]:[];let T=null;for(const E of C){const P=x.closest(E);if(P){T=P;break}}T?b=T:(console.warn("[Plurality] No matching ancestor container found, using relativeElement.parentElement"),b=x.parentElement||b)}if(g.into==="self"&&(y==="prepend"||y==="append"))y==="prepend"?b.insertBefore(d,b.firstChild):y==="append"&&b.appendChild(d),b.style.display="flex",b.style.flexDirection="row",b.style.alignItems="center",b.style.gap="8px";else{const C=document.createElement("div");C.appendChild(d),x&&y==="before"?b.insertBefore(C,x):x&&y==="after"?b.insertBefore(C,x.nextSibling):y==="prepend"?b.insertBefore(C,b.firstChild):b.appendChild(C)}if(g.reposition?.all)for(const C of g.reposition.all){const T=C.find?.any||[];for(const E of T)if(!(!E||E.trim()===""))try{document.querySelectorAll(E).forEach(I=>{I instanceof HTMLElement&&C.apply&&Object.entries(C.apply).forEach(([A,N])=>{if(N!==void 0){const M=A.replace(/([A-Z])/g,"-$1").toLowerCase();I.style.setProperty(M,String(N))}})})}catch(P){console.warn(`[Plurality] Invalid selector in reposition: "${E}"`,P)}}}}return document.body.appendChild(m),Ce().then(g=>{g.isLoggedIn||(m.style.display="none",Pt("syncButton",d,{title:"Get Started with AI Context Flow",content:"Click here to log in and unlock AI memory features.",position:"left"}))}).catch(g=>{console.warn("[Plurality] Failed to check login status:",g),m.style.display="none"}),Ur(),d},Ka=e=>{const t=U(),n=document.createElement("div");n.id=e,n.style.position="fixed",n.style.backgroundColor=t.background,n.style.borderRadius="12px",n.style.boxShadow=`0 4px 20px ${t.shadowColor}`,n.style.overflow="hidden",n.style.display="none",n.style.width="230px",n.style.minWidth="unset",n.style.zIndex="10000",n.style.border=`1px solid ${t.border}`,n.style.opacity="0",n.style.transform="translateY(10px)",n.style.transition="opacity 0.3s ease, transform 0.3s ease";const o=document.createElement("style");return o.textContent=`
    @keyframes spin { 0% { transform: rotate(0deg); } 100% { transform: rotate(360deg); } }
    .dropdown-item {
      padding: 12px 16px; cursor: pointer; color: ${t.textPrimary}; border-bottom: 1px solid ${t.borderLight};
      transition: all 0.2s ease; font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif;
      font-size: 14px; display: flex; align-items: center; justify-content: space-between;
    }
    .dropdown-item-content { display: flex; align-items: center; flex: 1; }
    .dropdown-item:before {
      content: ''; display: inline-block; width: 16px; height: 16px; margin-right: 10px;
      background-size: contain; background-repeat: no-repeat;
    }

    .dropdown-item[data-action="getData"]:before {
      background-image: url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='${encodeURIComponent(t.extensionAccent)}'%3E%3Cpath d='M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm-2 15l-5-5 1.41-1.41L10 14.17l7.59-7.59L19 8l-9 9z'/%3E%3C/svg%3E");
    }

    .dropdown-item[data-action="saveContext"]:before {
      background-image: url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='${encodeURIComponent(t.extensionAccent)}'%3E%3Cpath d='M17 3H5c-1.11 0-2 .9-2 2v14c0 1.1.89 2 2 2h14c1.1 0 2-.9 2-2V7l-4-4zm-5 16c-1.66 0-3-1.34-3-3s1.34-3 3-3 3 1.34 3 3-1.34 3-3 3zm3-10H5V5h10v4z'/%3E%3C/svg%3E");
    }

    .dropdown-item[data-action="saveAsNew"]:before {
      background-image: url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='${encodeURIComponent(t.extensionAccent)}'%3E%3Cpath d='M19 13h-6v6h-2v-6H5v-2h6V5h2v6h6v2z'/%3E%3Cpath d='M0 0h24v24H0z' fill='none'/%3E%3C/svg%3E");
    }


    .dropdown-item:hover { background-color: ${t.backgroundHover}; color: ${t.extensionAccent}; }
    .dropdown-item:disabled { opacity: 0.5; cursor: not-allowed; pointer-events: none; }
    .dropdown-item:last-child { border-bottom: none; }
    .shortcut-hint { font-size: 11px; color: ${t.textMuted}; background-color: ${t.backgroundSecondary}; padding: 3px 6px; border-radius: 4px; margin-left: 10px; border: 1px solid ${t.border}; }
  `,document.head.appendChild(o),n.innerHTML=`
    <div class="dropdown-item" data-action="getData">
      <div class="dropdown-item-content">Optimize</div>
      <span class="shortcut-hint">${dn("i")}</span>
    </div>
    <div class="dropdown-item" data-action="saveContext">
      <div class="dropdown-item-content">Save</div>
    </div>
    <div class="dropdown-item" data-action="saveAsNew">
      <div class="dropdown-item-content">Save as New</div>
    </div>
  `,n},Xa=(e,t,n,o)=>{let r=null,i=!1,a=!1;const s=()=>{i&&(i=!1,t.style.opacity="0",t.style.transform="translateY(10px)",setTimeout(()=>{i||(t.style.display="none")},300))},c=async()=>{if(!(await Ce()).isLoggedIn)return;const h=(await chrome.storage.local.get("selectedProfileId")).selectedProfileId,m=t.querySelector('[data-action="saveContext"]');h==="12345678-1234-1234-1234-123456789abc"?(m.style.opacity="0.5",m.style.cursor="not-allowed",m.style.pointerEvents="none"):(m.style.opacity="1",m.style.cursor="pointer",m.style.pointerEvents="auto");const f=e.getBoundingClientRect(),k=10;t.style.left=`${f.right-100-k}px`,t.style.bottom=`${window.innerHeight-f.top+10}px`,t.style.display="block",i=!0,requestAnimationFrame(()=>{t.style.opacity="1",t.style.transform="translateY(0)"})},d=()=>{r&&(clearTimeout(r),r=null)};e.addEventListener("mouseenter",()=>{d(),!a&&!i&&c()}),e.addEventListener("mouseleave",()=>{!a&&!t.matches(":hover")&&(r=window.setTimeout(s,200))}),t.addEventListener("mouseenter",d),t.addEventListener("mouseleave",()=>{a||(r=window.setTimeout(s,200))}),e.addEventListener("click",async p=>{if(p.preventDefault(),p.stopPropagation(),p.stopImmediatePropagation(),be(),!(await Ce()).isLoggedIn){chrome.runtime.sendMessage({action:"openPopup",source:"syncButton"});return}if(i){a=!1;return}else a=!0,d(),await c(),setTimeout(()=>{a=!1},100)}),t.addEventListener("click",async p=>{const h=p.target.closest(".dropdown-item");if(h&&h.classList.contains("dropdown-item")&&h.style.pointerEvents!=="none"){const m=h.getAttribute("data-action");n(),s(),a=!1;try{await Or(m,n,o)}catch(f){console.error(f),o()}}}),document.addEventListener("click",p=>{!e.contains(p.target)&&!t.contains(p.target)&&(s(),a=!1)},{signal:O}),document.addEventListener("keydown",p=>{p.key==="Escape"&&i&&(s(),a=!1)},{signal:O})},Va=async()=>new Promise(e=>requestAnimationFrame(()=>e())),ye=(e,t)=>setTimeout(()=>B(e,t),0),Or=async(e,t,n)=>{if(e&&!lt){lt=!0,t(),await Va();try{const o=await chrome.storage.local.get("selectedProfileId"),r=await chrome.storage.local.get("profiles"),i=o.selectedProfileId;if(!r?.profiles?.length){chrome.runtime.sendMessage({action:"openPopup",source:"syncButton"});return}const a=r?.profiles?.filter(c=>c.id===i)[0]?.profileName;let s=null;switch(e){case"getData":{if(s=await Pa(i),s?.success){const c=s.optimizedQuery;if(!c){ye("Received empty optimized prompt from API","info");return}await Ba(c)}else ye(`Failed to optimize prompt: ${s?.error??"Unknown error"}`,"error");break}case"saveContext":{const c=r?.profiles?.find(d=>d.id===i);if(c&&!Wa(c)){ye("This bucket is view-only. You cannot save content here.","warning");break}s=await er(i),s?.success?(ye(`Saved your chat successfully to your memory bucket <span class="keyboard-shortcut">${a}</span> `,"success"),Ga(i,1)):ye(`Failed to save the chat: ${s?.error??"Unknown error"}`,"error");break}case"saveAsNew":{if(s=await er(void 0,!0),s?.success){ye(`Saved your chat to a new memory bucket <br/><span class="keyboard-shortcut">${s.data?.title}</span>`,"success");const c=await Ce();c.token&&chrome.runtime.sendMessage({action:"refreshProfiles",token:c.token})}else{if(s?.error==="CreditError")return;ye(`Failed to save the chat: ${s?.error??"Unknown error"}`,"error")}break}}}catch{ye(`Failed to ${e}: Please open the extension to sync your data.`,"error")}finally{n(),lt=!1}}},Ur=()=>{if(or)return;or=!0;const e=1e3,t={"ctrl+i":0,"meta+i":0};document.addEventListener("keydown",async n=>{if(n.repeat)return;const o=n.key.toLowerCase();let r=null,i=null;if(n.ctrlKey&&!n.altKey&&!n.metaKey&&o==="i"&&(i="ctrl+i",r="getData"),n.metaKey&&!n.altKey&&!n.ctrlKey&&o==="i"&&(i="meta+i",r="getData"),!r||!i)return;n.preventDefault(),n.stopImmediatePropagation();const a=Date.now();if(!(a-t[i]<e)&&!lt)try{if(!(await Ce()).isLoggedIn){chrome.runtime.sendMessage({action:"openPopup",source:"syncButton"});return}t[i]=a,await Or(r,Hr||(()=>{}),_r||(()=>{}))}catch(s){console.error(`Error executing shortcut ${i}:`,s)}},{capture:!0,signal:O})};document.addEventListener("click",e=>{const t=document.getElementById("plurality-sync-button"),n=document.getElementById("plurality-sync-dropdown");t&&n&&!t.contains(e.target)&&!n.contains(e.target)&&(n.style.opacity="0",n.style.transform="translateY(10px)",setTimeout(()=>{n.style.display="none"},300))},{signal:O});const qr=e=>{const t=document.getElementById("plurality-sync-dropdown");t&&(t.style.display="none")},Qa=(e,t,n)=>{const[o,r,i]=[e,t,n].map(a=>(a=a/255,a<=.03928?a/12.92:Math.pow((a+.055)/1.055,2.4)));return .2126*o+.7152*r+.0722*i},Za=e=>{const t=e.match(/rgba?\((\d+),\s*(\d+),\s*(\d+)/);if(t)return{r:parseInt(t[1],10),g:parseInt(t[2],10),b:parseInt(t[3],10)};const n=e.match(/^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i);return n?{r:parseInt(n[1],16),g:parseInt(n[2],16),b:parseInt(n[3],16)}:null},Ja=e=>{let t=e;for(;t&&t!==document.documentElement.parentElement;){const o=window.getComputedStyle(t).backgroundColor;if(o&&o!=="transparent"&&o!=="rgba(0, 0, 0, 0)")return o;t=t.parentElement}return null},pn=()=>{const e=document.documentElement,t=document.body,n=[e.getAttribute("data-theme"),e.getAttribute("data-color-scheme"),e.getAttribute("data-color-mode"),e.getAttribute("class"),e.style.colorScheme,t.getAttribute("data-theme"),t.getAttribute("data-color-scheme"),t.getAttribute("data-color-mode"),t.getAttribute("class")];for(const i of n)if(i){const a=i.toLowerCase(),s=/(?:^|[\s"'])dark(?:$|[\s"'])/.test(a)||a.includes("theme-dark")||a.includes("mode-dark")||a.includes("dark-mode")||a.includes("darkmode"),c=/(?:^|[\s"'])light(?:$|[\s"'])/.test(a)||a.includes("theme-light")||a.includes("mode-light")||a.includes("light-mode")||a.includes("lightmode");if(s&&c)continue;if(s)return"dark";if(c)return"light"}const o=[document.querySelector("article"),document.querySelector("main"),document.querySelector('[role="main"]'),document.querySelector('[class*="article"]'),document.querySelector('[class*="post"]'),document.querySelector('[class*="content"]'),document.querySelector(".conversation"),document.querySelector('[class*="chat"]'),document.querySelector('[class*="container"]'),t,e].filter(Boolean);for(const i of o){const a=Ja(i);if(!a)continue;const s=Za(a);if(!s)continue;const c=Qa(s.r,s.g,s.b);if(c<.3)return"dark";if(c>.6)return"light"}const r=window.getComputedStyle(e);return r.colorScheme==="dark"?"dark":r.colorScheme==="light"?"light":window.matchMedia("(prefers-color-scheme: dark)").matches?"dark":"light"},es=e=>{let t=pn();const n=()=>{const r=pn();r!==t&&(t=r,e(r))},o=new MutationObserver(()=>{n()});return o.observe(document.documentElement,{attributes:!0,attributeFilter:["class","data-theme","data-color-scheme","data-color-mode","style"]}),document.body&&o.observe(document.body,{attributes:!0,attributeFilter:["class","data-theme","data-color-scheme","data-color-mode","style"]}),window.matchMedia("(prefers-color-scheme: dark)").addEventListener("change",n),o},ts=e=>{const t=ke(e,"checkStatus"),n=t?document.querySelectorAll(t).length:0;if(!t||n===0)return console.warn("[Plurality:isValid] FAILED at checkStatus — selector empty or no match"),!1;let o=ke(e,"loginButton.insert.into");(!o||o==="self")&&(o=ke(e,"loginButton.insert.relative"));const r=o?document.querySelectorAll(o).length:0;if(!o||r===0)return console.warn("[Plurality:isValid] FAILED at loginButton — selector empty or no match"),!1;const i=ke(e,"profilesDropdown.insert.into"),a=i?document.querySelectorAll(i).length:0;if(i&&a>0)return!0;const s=ke(e,"inputField"),c=s?document.querySelectorAll(s).length:0;return s&&c>0?!0:(console.warn("[Plurality:isValid] FAILED — neither profilesDropdown nor inputField matched"),!1)},jr=e=>e.role!=="viewer",mt={floatingButtonShowCount:0,floatingButtonDismissed:!0,floatingButtonMaxShows:3};let q=null,We=null,ee="",Te="",Se=!1,Xe=null,ct=null,Ve=null,Wt=!1,Dt=!1,ae=null,dt=null,tt=!1,at=!1,an=0,fe=null,ge=null,ir=!1,Qe=!1,Ge=null;const Ze=()=>{dt&&(window.clearTimeout(dt),dt=null)},un="36px",ar="200px",hn="50%",sr="12px",ns=(e,t)=>{if(!ir){ir=!0;try{chrome.storage.sync.get(["onboarding"],n=>{Qe=!(n.onboarding?.textSelectionPrefs||mt).floatingButtonDismissed})}catch{}try{chrome.storage.onChanged.addListener((n,o)=>{o==="sync"&&n.onboarding&&(Qe=!(n.onboarding.newValue?.textSelectionPrefs||mt).floatingButtonDismissed)})}catch{}document.addEventListener("mousedown",()=>{Dt=!0},{signal:O}),document.addEventListener("mouseup",n=>{Dt=!1,as(n)},{signal:O}),document.addEventListener("selectionchange",os,{signal:O}),window.addEventListener("focus",()=>{rs()},{signal:O})}},rs=async()=>{try{if(!(await chrome.storage.local.get(["pendingTextSelectionAction"])).pendingTextSelectionAction||!(await chrome.runtime.sendMessage({action:"checkAuthStatus"})).isLoggedIn)return;await chrome.storage.local.remove("pendingTextSelectionAction");const n=await chrome.storage.local.get(["profiles"]);q&&n.profiles?.length>0&&(q.dispatchEvent(new MouseEvent("mouseenter",{bubbles:!0})),setTimeout(()=>{q&&q.dispatchEvent(new MouseEvent("click",{bubbles:!0}))},100))}catch(e){ft(e)?_():console.error("[Plurality] Error checking pending text selection action:",e)}},os=()=>{if(Wt||tt||(ae&&(window.clearTimeout(ae),ae=null),Dt))return;const t=window.getSelection()?.toString().trim(),n=t?t.split(/\s+/).filter(r=>r.length>0).length:0;if(!(t&&n>=3)){Ze(),$e(),Z(),ee="",Te="",Se=!1;return}ee=t,Te="",Se=!1,ae=window.setTimeout(()=>{const r=window.getSelection(),i=r?.toString().trim();if(i&&i===ee&&r&&r.rangeCount>0){const s=r.getRangeAt(0).getBoundingClientRect();s&&s.width>0&&s.height>0&&Qe&&(Ze(),dt=window.setTimeout(()=>{const c=window.getSelection(),d=c?.toString().trim();if(d&&d.length>0&&c&&c.rangeCount>0){const u=c.getRangeAt(0).getBoundingClientRect();u&&u.width>0&&u.height>0&&Yr(u)}},1e3))}},100)},is=async e=>{e.preventDefault(),e.stopPropagation(),be();try{if(!(await chrome.runtime.sendMessage({action:"checkAuthStatus"})).isLoggedIn){await chrome.storage.local.set({pendingTextSelectionAction:!0}),await chrome.runtime.sendMessage({action:"openPopup",source:"textSelection"});return}chrome.storage.local.get(["profiles"],n=>{const o=n.profiles||[];if(o.length===0){B("No profiles found. Please create a profile first.","error",3e3);return}Wr(o)})}catch(t){ft(t)?_():(console.error("Error in handleIconClick:",t),B("Failed to check authentication status","error",3e3))}},as=e=>{if(tt)return;if(e?.target){const c=e.target;if(c.closest("#plurality-selection-icon")||c.closest("#plurality-selection-dropdown")||c.closest(".plurality-onboarding-tooltip"))return}const t=window.getSelection(),n=t?.toString().trim(),o=n?n.split(/\s+/).filter(c=>c.length>0).length:0;if(!(n&&o>=5)){Ze(),$e(),Z(),ee="",Te="",Se=!1;return}ee=n,Te="",Se=!1;const a=t?.getRangeAt(0)?.getBoundingClientRect(),s=e?{x:e.clientX,y:e.clientY}:null;a&&Qe&&(Ze(),dt=window.setTimeout(()=>{const c=window.getSelection(),d=c?.toString().trim();if(d&&d.length>0&&c&&c.rangeCount>0){const u=c.getRangeAt(0).getBoundingClientRect();u&&Yr(u,s)}},1e3))},ss=e=>{if(!(at||an>=2))try{chrome.storage.sync.get(["onboarding"],t=>{const n=t.onboarding||{tooltips:{}};if(n.tooltips?.textSelection||(n.textSelectionPrefs||mt).floatingButtonDismissed||!e||!document.body.contains(e))return;be();const r=U(),i=document.createElement("div");i.className="plurality-onboarding-tooltip",i.style.cssText=`
        position: fixed !important;
        background: ${r.background} !important;
        border-radius: 12px !important;
        box-shadow: 0 8px 32px ${r.shadowColor} !important;
        border: 1px solid ${r.border} !important;
        padding: 16px !important;
        max-width: 300px !important;
        z-index: 2147483647 !important;
        font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
        box-sizing: border-box !important;
        text-align: left !important;
        user-select: none !important;
        -webkit-user-select: none !important;
      `;const a=document.createElement("div");a.textContent="Save Selected Text to AI Memory",a.style.cssText=`
        font-size: 14px !important;
        font-weight: 600 !important;
        color: ${r.textPrimary} !important;
        margin: 0 0 6px 0 !important;
        font-family: inherit !important;
      `;const s=document.createElement("div");s.textContent="Every time you select text, this icon will appear so you can quickly save it to your AI Memory.",s.style.cssText=`
        font-size: 12px !important;
        color: ${r.textMuted} !important;
        margin: 0 0 14px 0 !important;
        line-height: 1.5 !important;
        font-family: inherit !important;
      `;const c=document.createElement("div");c.style.cssText=`
        display: flex !important;
        gap: 8px !important;
      `;const d=document.createElement("button");d.textContent="Keep Showing Icon",d.style.cssText=`
        flex: 1 !important;
        padding: 8px 12px !important;
        border-radius: 8px !important;
        border: none !important;
        background: ${r.primaryGradient} !important;
        color: white !important;
        font-size: 12px !important;
        font-weight: 600 !important;
        cursor: pointer !important;
        font-family: inherit !important;
        transition: transform 0.2s ease !important;
      `;const p=document.createElement("button");p.textContent="Don't Show Icon",p.style.cssText=`
        flex: 1 !important;
        padding: 8px 12px !important;
        border-radius: 8px !important;
        border: 1px solid ${r.border} !important;
        background: ${r.backgroundSecondary} !important;
        color: ${r.textPrimary} !important;
        font-size: 12px !important;
        font-weight: 500 !important;
        cursor: pointer !important;
        font-family: inherit !important;
        transition: transform 0.2s ease !important;
      `,Ge=i;const u=new AbortController,h=()=>{u.abort(),i.remove(),Ge===i&&(Ge=null)};d.addEventListener("click",v=>{v.preventDefault(),v.stopPropagation(),v.stopImmediatePropagation(),at=!0,Bt("textSelection"),h()},!0),p.addEventListener("click",v=>{v.preventDefault(),v.stopPropagation(),v.stopImmediatePropagation(),at=!0,Qe=!1;try{chrome.storage.sync.get(["onboarding"],C=>{const T=C.onboarding||{},E=T.textSelectionPrefs||{...mt};E.floatingButtonDismissed=!0,T.textSelectionPrefs=E,T.tooltips={...T.tooltips,textSelection:!0},chrome.storage.sync.set({onboarding:T})})}catch{}h(),Ft(),Z(),B('Got it! Right-click selected text → "Save text to AI Memory" to save.',"info",4e3)},!0);const m=document.createElement("div");m.style.cssText=`
        position: absolute !important;
        width: 12px !important;
        height: 12px !important;
        background: ${r.background} !important;
        border-right: 1px solid ${r.border} !important;
        border-bottom: 1px solid ${r.border} !important;
        transform: rotate(45deg) !important;
        z-index: -1 !important;
      `,c.appendChild(d),c.appendChild(p),i.appendChild(a),i.appendChild(s),i.appendChild(c),i.appendChild(m),document.body.appendChild(i);const f=e.getBoundingClientRect(),k=i.getBoundingClientRect(),w=16;let g=f.top-k.height-12,y=f.left+f.width/2-k.width/2;y=Math.max(w,Math.min(y,window.innerWidth-k.width-w));const x=g<w;x&&(g=f.bottom+12),i.style.top=`${g}px`,i.style.left=`${y}px`;const b=f.left+f.width/2-y-6;x?(m.style.top="-6px",m.style.borderRight="none",m.style.borderBottom="none",m.style.borderTop=`1px solid ${r.border}`,m.style.borderLeft=`1px solid ${r.border}`):m.style.bottom="-6px",m.style.left=`${Math.max(12,Math.min(b,k.width-24))}px`,setTimeout(()=>{document.addEventListener("mousedown",function v(C){!i.contains(C.target)&&!e.contains(C.target)&&(an++,h(),Ft(),document.removeEventListener("mousedown",v),an>=2&&(at=!0,Bt("textSelection")))},{signal:u.signal})},0)})}catch{}},Yr=(e,t)=>{$e(),Z();const n=U(),o=window.getSelection(),r=o&&o.rangeCount>0&&e.width>=window.innerWidth*.8&&e.height>=window.innerHeight*.8,i=document.createElement("div");i.id="plurality-selection-icon";const a=r?"fixed":"absolute";i.style.cssText=`
    position: ${a} !important;
    background: ${n.background} !important;
    display: flex !important;
    align-items: center !important;
    justify-content: center !important;
    width: ${un} !important;
    height: 36px !important;
    border-radius: ${hn} !important;
    cursor: pointer !important;
    z-index: 2147483647 !important;
    box-shadow: 0 4px 12px ${n.shadowColor}, 0 0 0 2px rgba(${n.extensionAccentRgb}, 0.3) !important;
    transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1) !important;
    pointer-events: auto !important;
    user-select: none !important;
    -webkit-user-select: none !important;
    -moz-user-select: none !important;
    -ms-user-select: none !important;
    white-space: nowrap !important;
    overflow: hidden !important;
    visibility: hidden;
    box-sizing: border-box !important;
    padding: 0 !important;
    margin: 0 !important;
    border: none !important;
    float: none !important;
    min-width: 0 !important;
    min-height: 0 !important;
    max-width: none !important;
    max-height: none !important;
    line-height: normal !important;
    text-align: center !important;
    letter-spacing: normal !important;
    text-transform: none !important;
    appearance: none !important;
    -webkit-appearance: none !important;
  `;const s=document.createElement("img"),c=_e();if(!c){_();return}s.src=c,s.alt="Plurality",s.onerror=()=>{$e(),_()},s.style.cssText=`
    width: 20px !important;
    height: 20px !important;
    min-width: 20px !important;
    max-width: 20px !important;
    pointer-events: none !important;
    flex-shrink: 0 !important;
    transition: opacity 0.3s ease !important;
    border-radius: 0 !important;
    border: none !important;
    padding: 0 !important;
    margin: 0 !important;
    display: block !important;
    box-sizing: border-box !important;
    object-fit: contain !important;
    float: none !important;
  `;const d=document.createElement("span");d.textContent="Save to Your AI Memory",d.style.cssText=`
    font-size: 13px !important;
    font-weight: 500 !important;
    color: ${n.textPrimary} !important;
    pointer-events: none;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
    line-height: normal !important;
    letter-spacing: normal !important;
    text-transform: none !important;
    margin-left: 8px;
    margin-right: 12px;
    opacity: 0;
    display: none;
    transition: opacity 0.2s ease;
  `;const p=document.createElement("span");p.className="plurality-dismiss-btn",p.textContent="×",p.style.cssText=`
    font-size: 16px !important;
    font-weight: 600 !important;
    color: ${n.textMuted} !important;
    pointer-events: auto !important;
    cursor: pointer !important;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif !important;
    line-height: 1 !important;
    margin-left: auto !important;
    margin-right: 8px !important;
    opacity: 0;
    display: none;
    transition: opacity 0.2s ease, color 0.2s ease;
    flex-shrink: 0 !important;
    width: 18px !important;
    height: 18px !important;
    text-align: center !important;
    border-radius: 50% !important;
  `,p.addEventListener("mouseenter",()=>{p.style.setProperty("color",n.textPrimary,"important")}),p.addEventListener("mouseleave",()=>{p.style.setProperty("color",n.textMuted,"important")}),p.addEventListener("click",v=>{v.preventDefault(),v.stopPropagation(),v.stopImmediatePropagation(),Qe=!1,at=!0;try{chrome.storage.sync.get(["onboarding"],C=>{const T=C.onboarding||{},E=T.textSelectionPrefs||{...mt};E.floatingButtonDismissed=!0,T.textSelectionPrefs=E,T.tooltips={...T.tooltips,textSelection:!0},chrome.storage.sync.set({onboarding:T})})}catch{}Ft(),Z(),B('Got it! Right-click and select "Save text to AI Memory" to save.',"info",4e3)},!0),i.appendChild(s),i.appendChild(d),i.appendChild(p),Xe=s,ct=d;const u=document.createElement("div");if(u.style.cssText=`
    width: 20px;
    height: 20px;
    box-sizing: border-box;
    border: 3px solid rgba(${n.extensionAccentRgb}, 0.3);
    border-radius: 50%;
    border-top: 3px solid ${n.extensionAccent};
    display: none;
    position: absolute;
    top: 50%;
    left: 50%;
    margin-top: -10px;
    margin-left: -10px;
    animation: plurality-spin 1s linear infinite;
    flex-shrink: 0;
  `,i.appendChild(u),Ve=u,!document.getElementById("plurality-spinner-animation")){const v=document.createElement("style");v.id="plurality-spinner-animation",v.textContent=`
      @keyframes plurality-spin {
        0% { transform: rotate(0deg); }
        100% { transform: rotate(360deg); }
      }
    `,document.head.appendChild(v)}document.body.appendChild(i);const h=i.getBoundingClientRect(),m=h.width,f=h.height,k=10,w=10;let g=window.scrollY+window.innerHeight/2-f/2,y=window.scrollX+window.innerWidth/2-m/2;if(r)g=w,y=window.innerWidth-200-20;else{const v=o?.getRangeAt(0);let C=!1;if(v){const T=v.cloneRange();T.collapse(!1);let E=T.getBoundingClientRect();if(E.width===0&&E.height===0){const I=v.getClientRects();if(I.length>0){let A=I[0];for(let N=1;N<I.length;N++){const M=I[N];(M.bottom>A.bottom+5||Math.abs(M.bottom-A.bottom)<=5&&M.right>A.right)&&(A=M)}E=A}}if((E.width>0||E.height>0)&&E.top>=0&&E.left>=0&&E.top<window.innerHeight+100&&E.left<window.innerWidth+100){g=E.bottom+window.scrollY+4,y=E.right+window.scrollX-m/2,y+m>window.innerWidth-w+window.scrollX&&(y=window.innerWidth-w-m+window.scrollX),y<w+window.scrollX&&(y=w+window.scrollX);const I=window.scrollY,A=window.scrollY+window.innerHeight;g<I+w?g=I+w:g+f>A-w&&(g=E.top+window.scrollY-f-4),C=!0}}!C&&t&&(g=t.y+window.scrollY-f/2,y=t.x+window.scrollX+k,y+m>window.innerWidth-w+window.scrollX&&(y=t.x+window.scrollX-m-k),y<w+window.scrollX&&(y=w+window.scrollX),g<w+window.scrollY&&(g=w+window.scrollY),g+f>window.innerHeight-w+window.scrollY&&(g=window.innerHeight-w-f+window.scrollY),C=!0),C||(e.top>=0&&e.left>=0&&e.top<window.innerHeight+100&&e.left<window.innerWidth+100?(g=e.top+window.scrollY,y=e.right+window.scrollX+k,y+m>window.innerWidth-w+window.scrollX&&(y=window.innerWidth-w-m+window.scrollX),y<w+window.scrollX&&(y=w+window.scrollX),g<w+window.scrollY&&(g=w+window.scrollY),g+f>window.innerHeight-w+window.scrollY&&(g=window.innerHeight-w-f+window.scrollY)):(g=window.scrollY+window.innerHeight/2-f/2,y=window.scrollX+window.innerWidth/2-m/2))}i.style.setProperty("top",`${g}px`,"important"),i.style.setProperty("left",`${y}px`,"important"),i.style.setProperty("visibility","visible","important"),r&&(i.style.setProperty("width",ar,"important"),i.style.setProperty("border-radius",sr,"important"),i.style.setProperty("justify-content","flex-start","important"),i.style.setProperty("padding-left","12px","important"),d.style.setProperty("display","inline","important"),d.style.setProperty("opacity","1","important"),p.style.setProperty("display","inline","important"),p.style.setProperty("opacity","1","important"));let x=r;const b=v=>{v.propertyName==="width"&&x&&!tt&&(d.style.setProperty("display","inline","important"),p.style.setProperty("display","inline","important"),requestAnimationFrame(()=>{d.style.setProperty("opacity","1","important"),p.style.setProperty("opacity","1","important")}))};i.addEventListener("transitionend",b),i.addEventListener("mouseenter",()=>{x=!0,i.style.setProperty("width",ar,"important"),i.style.setProperty("border-radius",sr,"important"),i.style.setProperty("justify-content","flex-start","important"),i.style.setProperty("padding-left","12px","important"),i.style.setProperty("box-shadow",`0 6px 16px rgba(${n.extensionAccentRgb}, 0.4), 0 0 0 3px rgba(${n.extensionAccentRgb}, 0.5)`,"important")}),i.addEventListener("mouseleave",()=>{x=!1,i.style.setProperty("width",un,"important"),i.style.setProperty("border-radius",hn,"important"),i.style.setProperty("justify-content","center","important"),i.style.setProperty("padding-left","0","important"),i.style.setProperty("box-shadow",`0 4px 12px ${n.shadowColor}, 0 0 0 2px rgba(${n.extensionAccentRgb}, 0.3)`,"important"),d.style.setProperty("opacity","0","important"),d.style.setProperty("display","none","important"),p.style.setProperty("opacity","0","important"),p.style.setProperty("display","none","important")}),i.addEventListener("click",v=>{v.target.closest?.(".plurality-dismiss-btn")||(v.preventDefault(),v.stopPropagation(),v.stopImmediatePropagation(),is(v))},!0),i.addEventListener("mousedown",v=>{v.target.closest?.(".plurality-dismiss-btn")||(v.preventDefault(),v.stopPropagation(),v.stopImmediatePropagation())},!0),i.addEventListener("mouseup",v=>{v.target.closest?.(".plurality-dismiss-btn")||(v.preventDefault(),v.stopPropagation(),v.stopImmediatePropagation())},!0),q=i,setTimeout(()=>{i&&document.body.contains(i)&&ss(i)},600)},Wr=e=>{if(Z(),!q)return;const t=U(),n=q.getBoundingClientRect(),o=document.createElement("div");o.id="plurality-selection-dropdown",o.style.cssText=`
    position: fixed !important;
    background: ${t.background} !important;
    border-radius: 12px !important;
    box-shadow: 0 4px 20px ${t.shadowColor} !important;
    z-index: 2147483647 !important;
    min-width: 250px !important;
    max-width: 350px !important;
    max-height: 300px !important;
    overflow-y: auto !important;
    padding: 8px 0 !important;
    user-select: none !important;
    -webkit-user-select: none !important;
    -moz-user-select: none !important;
    -ms-user-select: none !important;
    border: 1px solid ${t.border} !important;
    visibility: hidden;
    box-sizing: border-box !important;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
    line-height: normal !important;
    letter-spacing: normal !important;
    text-transform: none !important;
    text-align: left !important;
    float: none !important;
    margin: 0 !important;
    width: auto !important;
    height: auto !important;
  `,o.addEventListener("mousedown",b=>{b.preventDefault(),b.stopPropagation()}),o.addEventListener("mouseup",b=>{b.stopPropagation()});const r=document.createElement("div");r.style.cssText=`
    padding: 12px 16px !important;
    cursor: pointer !important;
    display: flex !important;
    align-items: center !important;
    gap: 12px !important;
    transition: background 0.2s ease !important;
    box-sizing: border-box !important;
    border: none !important;
    margin: 0 !important;
    float: none !important;
    background: transparent !important;
  `;const i=document.createElement("div");i.innerHTML=`<svg width="20" height="20" viewBox="0 0 20 20" fill="none" xmlns="http://www.w3.org/2000/svg">
    <rect x="1" y="1" width="18" height="18" rx="4" stroke="${t.extensionAccent}" stroke-width="1.5" fill="none"/>
    <path d="M10 6V14M6 10H14" stroke="${t.extensionAccent}" stroke-width="1.5" stroke-linecap="round"/>
  </svg>`,i.style.cssText=`
    width: 20px;
    height: 20px;
    flex-shrink: 0;
    pointer-events: none;
    display: flex;
    align-items: center;
    justify-content: center;
  `;const a=document.createElement("span");a.textContent="Save as New Memory",a.style.cssText=`
    font-size: 14px !important;
    font-weight: 500 !important;
    color: ${t.textPrimary} !important;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
    line-height: normal !important;
    letter-spacing: normal !important;
    text-transform: none !important;
  `,r.appendChild(i),r.appendChild(a),r.addEventListener("mouseenter",()=>{r.style.setProperty("background",t.backgroundSecondary,"important")}),r.addEventListener("mouseleave",()=>{r.style.setProperty("background","transparent","important")}),r.addEventListener("click",async b=>{b.preventDefault(),b.stopPropagation(),b.stopImmediatePropagation(),await Xr()}),o.appendChild(r);const s=document.createElement("div");s.style.cssText=`
    height: 1px;
    background: ${t.border};
    margin: 4px 0;
  `,o.appendChild(s);const c=document.createElement("div");c.style.cssText=`
    padding: 12px 16px 8px 16px;
    font-size: 12px !important;
    font-weight: 600 !important;
    color: ${t.textMuted} !important;
    letter-spacing: 0.5px !important;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
    line-height: normal !important;
  `,c.textContent="Save to Existing Memory Bucket",o.appendChild(c);const d=e.filter(b=>b.id!=="12345678-1234-1234-1234-123456789abc");if(d.forEach(b=>{const v=Gr(b);o.appendChild(v)}),d.length===0){const b=document.createElement("div");b.style.cssText=`
      padding: 16px;
      text-align: center;
      color: ${t.textMuted} !important;
      font-size: 14px !important;
      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
      line-height: normal !important;
      letter-spacing: normal !important;
      text-transform: none !important;
    `,b.textContent="Create Your First Memory Bucket",o.appendChild(b)}fe=b=>{!o.contains(b.target)&&!q?.contains(b.target)&&Z()},ge=b=>{b.target===o||o.contains(b.target)||Z()},setTimeout(()=>{fe&&document.addEventListener("click",fe,{signal:O}),ge&&window.addEventListener("scroll",ge,{capture:!0,signal:O})},0),document.body.appendChild(o);const p=o.getBoundingClientRect(),u=p.width,h=p.height,m=8,f=10;let k=n.left;const w=window.innerWidth-u-f;k<f?k=f:k>w&&(k=w);const g=window.innerHeight-n.bottom-m,y=n.top-m;let x;g>=h||g>=y?x=n.bottom+m:(x=n.top-m-h,x<f&&(x=f)),o.style.setProperty("top",`${x}px`,"important"),o.style.setProperty("left",`${k}px`,"important"),o.style.setProperty("visibility","visible","important"),We=o,Wt=!0},Gr=e=>{const t=U(),n=!jr(e),o=document.createElement("div");o.style.cssText=`
    padding: 12px 16px !important;
    cursor: ${n?"not-allowed":"pointer"} !important;
    display: flex !important;
    align-items: center !important;
    gap: 12px !important;
    transition: background 0.2s ease !important;
    box-sizing: border-box !important;
    border: none !important;
    margin: 0 !important;
    float: none !important;
    background: transparent !important;
    opacity: ${n?"0.5":"1"} !important;
  `;const r=document.createElement("div");r.innerHTML=`<svg width="20" height="20" viewBox="0 0 20 20" fill="none" xmlns="http://www.w3.org/2000/svg">
    <circle cx="10" cy="10" r="9" stroke="${t.extensionAccent}" stroke-width="1.5" fill="none"/>
    <path d="M10 6V14M6 10H14" stroke="${t.extensionAccent}" stroke-width="1.5" stroke-linecap="round"/>
  </svg>`,r.style.cssText=`
    width: 20px;
    height: 20px;
    flex-shrink: 0;
    pointer-events: none;
    display: flex;
    align-items: center;
    justify-content: center;
  `;const i=document.createElement("div");i.style.cssText=`
    flex: 1;
    display: flex;
    flex-direction: column;
    gap: 2px;
  `;const a=document.createElement("div");a.style.cssText=`
    font-size: 14px !important;
    font-weight: 500 !important;
    color: ${t.textPrimary} !important;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
    line-height: normal !important;
    letter-spacing: normal !important;
    text-transform: none !important;
  `,a.textContent=e.profileName;const s=document.createElement("div");if(s.style.cssText=`
    font-size: 12px !important;
    color: ${t.textMuted} !important;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
    line-height: normal !important;
    letter-spacing: normal !important;
    text-transform: none !important;
  `,s.textContent=`${e.contextCount} ${e.contextCount===1?"Item":"Items"}`,i.appendChild(a),i.appendChild(s),n){const c=document.createElement("div");c.style.cssText=`
      font-size: 11px !important;
      color: ${t.textMuted} !important;
      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
      line-height: normal !important;
      font-style: italic !important;
    `,c.textContent="View only",i.appendChild(c)}return o.appendChild(r),o.appendChild(i),n||(o.addEventListener("mouseenter",()=>{o.style.setProperty("background",t.backgroundSecondary,"important")}),o.addEventListener("mouseleave",()=>{o.style.setProperty("background","transparent","important")})),o.addEventListener("click",async c=>{if(c.preventDefault(),c.stopPropagation(),c.stopImmediatePropagation(),n){B("This bucket is view-only. You cannot save content here.","warning",4e3);return}await ls(e)}),o},Kr=()=>{tt=!0,Xe&&Ve&&q&&(Xe.style.setProperty("opacity","0","important"),Ve.style.setProperty("display","block","important"),q.style.setProperty("pointer-events","none","important"),q.style.setProperty("width",un,"important"),q.style.setProperty("border-radius",hn,"important"),q.style.setProperty("justify-content","center","important"),q.style.setProperty("padding-left","0","important"),ct&&(ct.style.setProperty("opacity","0","important"),ct.style.setProperty("display","none","important")))},Rt=()=>{tt=!1,Xe&&Ve&&q&&(Ve.style.setProperty("display","none","important"),Xe.style.setProperty("opacity","1","important"),q.style.setProperty("pointer-events","auto","important"))},Xr=async()=>{if(!ee){B("No text selected","error",3e3);return}Z();try{const t=(await chrome.storage.local.get(["token"])).token;if(!t){B("Authentication required","error",3e3),await chrome.runtime.sendMessage({action:"openPopup",source:"textSelection"});return}Kr(),B("Saving as new memory bucket","info",2e3);const n=await chrome.runtime.sendMessage({action:"saveRawContent",payload:{context:ee,profileId:"",sourcePlatform:Se?"ThirdpartyPage":"Thirdparty",sourceUrl:Te||window.location.href||""},token:t});if(Rt(),n.success){const o=n.data?.title||"New Memory Bucket";B(`Saved your selected text to a new memory bucket <br/><span class="keyboard-shortcut">${o}</span>`,"success",3e3),$e(),n.data?.profileId&&ds({id:n.data.profileId,profileName:o,contextCount:1}),window.getSelection()?.removeAllRanges()}else B(n.error||"Failed to save as new memory bucket","error",3e3)}catch(e){Rt(),ft(e)?_():(console.error("Error saving text as new:",e),B("Failed to save as new memory bucket","error",3e3))}},ls=async e=>{if(!jr(e)){B("This bucket is view-only. You cannot save content here.","warning",4e3);return}if(!ee){B("No text selected","error",3e3);return}Z();try{const n=(await chrome.storage.local.get(["token"])).token;if(!n){B("Authentication required","error",3e3),await chrome.runtime.sendMessage({action:"openPopup",source:"textSelection"});return}Kr(),B("Saving selected text into your AI memory","info",2e3);const o=await chrome.runtime.sendMessage({action:"saveRawContent",payload:{profileId:e.id,context:ee,sourcePlatform:Se?"ThirdpartyPage":"Thirdparty",sourceUrl:Te||window.location.href||""},token:n});Rt(),o.success?(B(`Saved your selected text to <span class="keyboard-shortcut">${e.profileName}</span>`,"success",3e3),$e(),cs(e.id,1),window.getSelection()?.removeAllRanges()):B(o.error||"Failed to save selected text into your AI memory","error",3e3)}catch(t){Rt(),ft(t)?_():(console.error("Error saving text to profile:",t),B("Failed to save selected text into your AI memory","error",3e3))}},cs=(e,t)=>{chrome.storage.local.get(["profiles"],n=>{const r=(n.profiles||[]).map(i=>i.id===e?{...i,contextCount:i.contextCount+t}:i);chrome.storage.local.set({profiles:r})})},ds=e=>{chrome.storage.local.get(["profiles"],t=>{const n=t.profiles||[],o=[{...e},...n];chrome.storage.local.set({profiles:o})})},Ft=()=>{Ze(),ae&&(window.clearTimeout(ae),ae=null),Ge&&(Ge.remove(),Ge=null),q&&(q.remove(),q=null,Xe=null,ct=null,Ve=null,be())},$e=()=>{const e=!!q;Ft(),e&&Bt("textSelection")},Z=()=>{We&&(We.remove(),We=null,Wt=!1),fe&&(document.removeEventListener("click",fe),fe=null),ge&&(window.removeEventListener("scroll",ge,!0),ge=null)},ps=(e,t="",n=!1)=>{ee=e,Te=t,Se=n;try{chrome.storage.local.get(["profiles"],o=>{const r=o.profiles||[];if(r.length===0){B("No profiles found. Please create a profile first.","error",3e3);return}us(r)})}catch(o){ft(o)?_():(console.error("Error in handleContextMenuSave:",o),B("Failed to load profiles","error",3e3))}},us=e=>{$e(),Z();const t=U(),n=document.createElement("div");n.id="plurality-selection-dropdown",n.style.cssText=`
    position: fixed !important;
    background: ${t.background} !important;
    border-radius: 12px !important;
    box-shadow: 0 4px 20px ${t.shadowColor} !important;
    z-index: 2147483647 !important;
    min-width: 250px !important;
    max-width: 350px !important;
    max-height: 300px !important;
    overflow-y: auto !important;
    padding: 8px 0 !important;
    user-select: none !important;
    -webkit-user-select: none !important;
    -moz-user-select: none !important;
    -ms-user-select: none !important;
    border: 1px solid ${t.border} !important;
    visibility: hidden;
    box-sizing: border-box !important;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
    line-height: normal !important;
    letter-spacing: normal !important;
    text-transform: none !important;
    text-align: left !important;
    float: none !important;
    margin: 0 !important;
    width: auto !important;
    height: auto !important;
  `,n.addEventListener("mousedown",h=>{h.preventDefault(),h.stopPropagation()}),n.addEventListener("mouseup",h=>{h.stopPropagation()});const o=document.createElement("div");o.style.cssText=`
    padding: 12px 16px !important;
    cursor: pointer !important;
    display: flex !important;
    align-items: center !important;
    gap: 12px !important;
    transition: background 0.2s ease !important;
    box-sizing: border-box !important;
    border: none !important;
    margin: 0 !important;
    float: none !important;
    background: transparent !important;
  `;const r=document.createElement("div");r.innerHTML=`<svg width="20" height="20" viewBox="0 0 20 20" fill="none" xmlns="http://www.w3.org/2000/svg">
    <rect x="1" y="1" width="18" height="18" rx="4" stroke="${t.extensionAccent}" stroke-width="1.5" fill="none"/>
    <path d="M10 6V14M6 10H14" stroke="${t.extensionAccent}" stroke-width="1.5" stroke-linecap="round"/>
  </svg>`,r.style.cssText=`
    width: 20px;
    height: 20px;
    flex-shrink: 0;
    pointer-events: none;
    display: flex;
    align-items: center;
    justify-content: center;
  `;const i=document.createElement("span");i.textContent="Save as New Memory",i.style.cssText=`
    font-size: 14px !important;
    font-weight: 500 !important;
    color: ${t.textPrimary} !important;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
    line-height: normal !important;
    letter-spacing: normal !important;
    text-transform: none !important;
  `,o.appendChild(r),o.appendChild(i),o.addEventListener("mouseenter",()=>{o.style.setProperty("background",t.backgroundSecondary,"important")}),o.addEventListener("mouseleave",()=>{o.style.setProperty("background","transparent","important")}),o.addEventListener("click",async h=>{h.preventDefault(),h.stopPropagation(),h.stopImmediatePropagation(),await Xr()}),n.appendChild(o);const a=document.createElement("div");a.style.cssText=`height: 1px; background: ${t.border}; margin: 4px 0;`,n.appendChild(a);const s=document.createElement("div");s.style.cssText=`
    padding: 12px 16px 8px 16px;
    font-size: 12px !important;
    font-weight: 600 !important;
    color: ${t.textMuted} !important;
    letter-spacing: 0.5px !important;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
    line-height: normal !important;
  `,s.textContent="Save to Existing Memory Bucket",n.appendChild(s);const c=e.filter(h=>h.id!=="12345678-1234-1234-1234-123456789abc");if(c.forEach(h=>{const m=Gr(h);n.appendChild(m)}),c.length===0){const h=document.createElement("div");h.style.cssText=`
      padding: 16px;
      text-align: center;
      color: ${t.textMuted} !important;
      font-size: 14px !important;
      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
      line-height: normal !important;
      letter-spacing: normal !important;
      text-transform: none !important;
    `,h.textContent="Create Your First Memory Bucket",n.appendChild(h)}fe=h=>{n.contains(h.target)||Z()},ge=h=>{h.target===n||n.contains(h.target)||Z()},setTimeout(()=>{fe&&document.addEventListener("click",fe),ge&&window.addEventListener("scroll",ge,!0)},0),document.body.appendChild(n);const d=n.getBoundingClientRect(),p=Math.max(10,(window.innerWidth-d.width)/2),u=Math.max(10,(window.innerHeight-d.height)/2);n.style.setProperty("top",`${u}px`,"important"),n.style.setProperty("left",`${p}px`,"important"),n.style.setProperty("visibility","visible","important"),We=n,Wt=!0},gt=e=>{We&&ee&&Wr(e)},Vr=()=>{Ze(),ae&&(window.clearTimeout(ae),ae=null),$e(),Z(),ee="",Te="",Se=!1,Dt=!1,tt=!1},hs=[{key:"web-search",label:"Web Search",description:"Search the web for up-to-date information",disabled:!1},{key:"url-extraction",label:"URL Extraction",description:"Extract and summarize content from URLs",disabled:!1},{key:"website-context",label:"Use this website to respond",description:"Include current webpage content in response",disabled:!1}],lr=1e3,ms={Google:"Google Gemini",Anthropic:"Anthropic Claude",OpenAI:"OpenAI GPT-OSS",Mistral:"Mistral AI",DeepSeek:"DeepSeek",Amazon:"Amazon Nova",Writer:"Writer",Qwen:"Qwen","Moonshot AI":"Moonshot AI",MiniMax:"MiniMax",ZAI:"Zhipu GLM"},Sn={key:"gemini-2.5-flash",label:"Gemini 2.5 Flash",description:"Latest flash model with enhanced capabilities",category:"Google Gemini",provider:"Google",tier:"base",creditMultiplier:1},$n=Sn,fs=e=>e.map(t=>({key:t.key,label:t.displayName,description:t.description||"",category:ms[t.provider]||t.provider,provider:t.provider,tier:t.tier,creditMultiplier:t.creditMultiplier||1,speedTier:t.speedTier||((t.creditMultiplier||1)>=3?"capable":(t.creditMultiplier||1)===2?"balanced":"fast"),featured:t.featured??!1})),zt=(e,t)=>t==="premium"?!0:e.tier==="base",gs={fast:"Fast",balanced:"Efficient",capable:"Premium"},xs=["fast","balanced","capable"],bs=e=>{const t={fast:[],balanced:[],capable:[]};e.forEach(o=>{const r=o.speedTier||"fast";t[r].push(o)});const n=(o,r)=>{if((o.featured??!1)!==(r.featured??!1))return o.featured?-1:1;const i=o.creditMultiplier||1,a=r.creditMultiplier||1;return i!==a?i-a:(o.label||"").localeCompare(r.label||"")};return xs.filter(o=>t[o].length>0).map(o=>({label:gs[o],tier:o,models:t[o].sort(n)}))},Qr=e=>`
  /* ===== Reset ===== */
  *, *::before, *::after {
    box-sizing: border-box;
    margin: 0;
    padding: 0;
  }

  /* ===== Animations ===== */
  @keyframes fadeIn {
    from { opacity: 0; transform: translateY(10px); }
    to { opacity: 1; transform: translateY(0); }
  }

  @keyframes fadeInMsg {
    from { opacity: 0; transform: translateY(6px); }
    to { opacity: 1; transform: translateY(0); }
  }

  @keyframes slideIn {
    from { opacity: 0; transform: translateX(-10px); }
    to { opacity: 1; transform: translateX(0); }
  }

  @keyframes typingBounce {
    0%, 80%, 100% { transform: scale(0.6); opacity: 0.4; }
    40% { transform: scale(1); opacity: 1; }
  }

  @keyframes pulseRing {
    0% { transform: scale(1); opacity: 0.5; }
    50% { transform: scale(1.08); opacity: 0.3; }
    100% { transform: scale(1); opacity: 0.5; }
  }

  @keyframes shimmer {
    0% { background-position: -200% 0; }
    100% { background-position: 200% 0; }
  }

  @keyframes gradientShift {
    0% { background-position: 0% 50%; }
    50% { background-position: 100% 50%; }
    100% { background-position: 0% 50%; }
  }

  /* ===== Container ===== */
  .sidebar-container {
    display: flex;
    flex-direction: column;
    width: 100%;
    height: 100%;
    background: ${e.background};
    font-family: 'Lexend', -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif;
    color: ${e.textPrimary};
    overflow: hidden;
    border-left: 1px solid ${e.border};
  }

  /* Chat page variant - centered with rounded corners */
  .sidebar-container.chat-page {
    border-left: none;
    border-radius: 16px;
    box-shadow: 0 8px 32px rgba(0, 0, 0, 0.12), 0 2px 8px rgba(0, 0, 0, 0.08);
  }

  /* Theater mode variant - three-panel layout */
  .sidebar-container.theater-mode {
    flex-direction: row;
    border-radius: 16px;
    overflow: hidden;
  }

  /* Chat page with theater mode - full page, no modal styling */
  .sidebar-container.chat-page.theater-mode {
    border-radius: 0;
    box-shadow: none;
  }

  /* Hide theater toggle and close buttons on chat page (always full page) */
  .sidebar-container.chat-page .theater-btn,
  .sidebar-container.chat-page .close-btn {
    display: none;
  }

  /* ===== Theater Mode Navigation Sidebar ===== */
  .theater-nav-sidebar {
    width: 240px;
    flex-shrink: 0;
    display: flex;
    flex-direction: column;
    background: ${e.background};
    border-right: 1px solid ${e.border};
    overflow: hidden;
  }

  .theater-nav-header {
    padding: 16px;
    border-bottom: 1px solid ${e.border};
    flex-shrink: 0;
  }

  .theater-nav-logo {
    display: flex;
    align-items: center;
    gap: 10px;
  }

  .theater-nav-logo img {
    width: 32px;
    height: 32px;
    border-radius: 8px;
  }

  .theater-nav-logo-text {
    display: flex;
    flex-direction: column;
    gap: 1px;
  }

  .theater-nav-title {
    font-size: 16px;
    font-weight: 700;
    color: ${e.textPrimary};
    letter-spacing: -0.3px;
    line-height: 1.2;
  }

  .theater-nav-subtitle {
    font-size: 11px;
    color: ${e.textMuted};
    letter-spacing: 0.2px;
    line-height: 1.2;
  }

  .theater-nav-content {
    flex: 1;
    overflow-y: auto;
    overflow-x: hidden;
  }

  .theater-nav-content::-webkit-scrollbar {
    width: 6px;
  }

  .theater-nav-content::-webkit-scrollbar-track {
    background: transparent;
  }

  .theater-nav-content::-webkit-scrollbar-thumb {
    background: ${e.textMuted};
    border-radius: 3px;
  }

  .theater-nav-content::-webkit-scrollbar-thumb:hover {
    background: ${e.textSecondary};
  }

  .theater-conversations-section {
    flex: 1;
    overflow-y: auto;
    overflow-x: hidden;
    display: flex;
    flex-direction: column;
  }

  .theater-conversations-section::-webkit-scrollbar {
    width: 6px;
  }

  .theater-conversations-section::-webkit-scrollbar-track {
    background: transparent;
  }

  .theater-conversations-section::-webkit-scrollbar-thumb {
    background: ${e.textMuted};
    border-radius: 3px;
  }

  .theater-conversations-section::-webkit-scrollbar-thumb:hover {
    background: ${e.textSecondary};
  }

  .theater-buckets-section {
    max-height: 200px;
    flex-shrink: 0;
    overflow-y: auto;
    overflow-x: hidden;
    border-bottom: 1px solid ${e.border};
    display: flex;
    flex-direction: column;
    padding: 12px 8px;
  }

  .theater-buckets-section::-webkit-scrollbar {
    width: 6px;
  }

  .theater-buckets-section::-webkit-scrollbar-track {
    background: transparent;
  }

  .theater-buckets-section::-webkit-scrollbar-thumb {
    background: ${e.textMuted};
    border-radius: 3px;
  }

  .theater-buckets-section::-webkit-scrollbar-thumb:hover {
    background: ${e.textSecondary};
  }

  .theater-nav-section {
    padding: 12px 8px;
  }

  .theater-nav-section-title {
    font-size: 11px;
    font-weight: 600;
    color: ${e.textMuted};
    text-transform: uppercase;
    letter-spacing: 0.5px;
    padding: 8px 12px;
    margin-bottom: 4px;
  }

  .theater-bucket-item {
    display: flex;
    align-items: center;
    gap: 10px;
    padding: 8px 12px;
    margin: 2px 0;
    border-radius: 8px;
    cursor: pointer;
    transition: all 0.2s ease;
    font-size: 13px;
    color: ${e.textPrimary};
  }

  .theater-bucket-item:hover {
    background: ${e.backgroundHover};
  }

  .theater-bucket-item.selected {
    background: ${e.primary}15;
    color: ${e.primary};
    font-weight: 500;
  }

  .theater-bucket-icon {
    width: 6px;
    height: 6px;
    border-radius: 50%;
    background: ${e.textMuted};
    flex-shrink: 0;
    transition: all 0.2s ease;
  }

  .theater-bucket-item.selected .theater-bucket-icon {
    background: ${e.primary};
    transform: scale(1.3);
  }

  .theater-bucket-name {
    flex: 1;
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
  }

  .theater-thread-item {
    display: flex;
    align-items: center;
    gap: 8px;
    padding: 8px 12px;
    margin: 2px 0;
    border-radius: 8px;
    cursor: pointer;
    transition: all 0.2s ease;
    font-size: 13px;
    color: ${e.textPrimary};
  }

  .theater-thread-item:hover {
    background: ${e.backgroundHover};
  }

  .theater-thread-item.selected {
    background: ${e.primary}10;
    color: ${e.primary};
  }

  .theater-thread-icon {
    width: 14px;
    height: 14px;
    flex-shrink: 0;
    opacity: 0.6;
  }

  .theater-thread-item.selected .theater-thread-icon {
    opacity: 1;
  }

  .theater-thread-content {
    flex: 1;
    min-width: 0;
  }

  .theater-thread-title {
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
    font-size: 13px;
  }

  .theater-thread-date {
    font-size: 11px;
    color: ${e.textMuted};
    margin-top: 6px;
  }

  .theater-nav-footer {
    padding: 12px;
    border-top: 1px solid ${e.border};
    flex-shrink: 0;
  }

  .theater-new-chat-btn {
    width: calc(100% - 24px);
    margin: 12px 12px 0 12px;
    padding: 10px 16px;
    border-radius: 8px;
    border: 1px solid ${e.border};
    background: ${e.backgroundSecondary};
    color: ${e.textPrimary};
    font-family: 'Lexend', -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif;
    font-size: 11px;
    font-weight: 500;
    cursor: pointer;
    transition: all 0.2s ease;
    display: flex;
    align-items: center;
    justify-content: center;
    gap: 6px;
    flex-shrink: 0;
  }

  .theater-new-chat-btn:hover {
    background: ${e.backgroundHover};
    border-color: ${e.primary};
    color: ${e.primary};
  }

  .theater-new-chat-btn svg {
    width: 12px;
    height: 12px;
  }

  .theater-nav-divider {
    height: 1px;
    background: ${e.border};
    margin: 16px 12px 12px 12px;
    flex-shrink: 0;
  }

  .theater-filter-btn {
    padding: 6px 10px;
    border-radius: 6px;
    border: 1px solid ${e.border};
    background: ${e.backgroundSecondary};
    color: ${e.textPrimary};
    font-family: 'Lexend', -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif;
    font-size: 11px;
    font-weight: 500;
    cursor: pointer;
    transition: all 0.2s ease;
    display: flex;
    align-items: center;
    gap: 4px;
    white-space: nowrap;
  }

  .theater-filter-btn:hover {
    background: ${e.backgroundHover};
    border-color: ${e.primary};
  }

  .theater-filter-btn.active {
    border-color: ${e.primary};
    background: ${e.primary}15;
    color: ${e.primary};
  }

  .theater-filter-btn svg {
    width: 12px;
    height: 12px;
    flex-shrink: 0;
    opacity: 0.7;
  }

  .theater-filter-btn .filter-count {
    font-size: 11px;
    font-weight: 500;
  }

  .theater-filter-dropdown-menu {
    position: fixed;
    background: ${e.background};
    border: 1px solid ${e.border};
    border-radius: 8px;
    box-shadow: 0 4px 12px ${e.shadowColor};
    z-index: 10000;
    min-width: 180px;
    max-height: 300px;
    overflow-y: auto;
    display: none;
  }

  .theater-filter-dropdown-menu.open {
    display: block;
  }

  .theater-filter-dropdown-menu::-webkit-scrollbar {
    width: 5px;
  }

  .theater-filter-dropdown-menu::-webkit-scrollbar-track {
    background: transparent;
  }

  .theater-filter-dropdown-menu::-webkit-scrollbar-thumb {
    background: ${e.textMuted};
    border-radius: 3px;
  }

  .theater-filter-dropdown-menu::-webkit-scrollbar-thumb:hover {
    background: ${e.textSecondary};
  }

  .theater-filter-dropdown-item {
    padding: 10px 12px;
    font-family: 'Lexend', -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif;
    font-size: 12px;
    color: ${e.textPrimary};
    cursor: pointer;
    transition: background 0.2s ease;
    display: flex;
    align-items: center;
    gap: 8px;
  }

  .theater-filter-dropdown-item:hover {
    background: ${e.backgroundHover};
  }

  .theater-filter-dropdown-item.selected {
    background: ${e.backgroundSelected};
    font-weight: 600;
  }

  .theater-filter-dropdown-item:first-child {
    border-top-left-radius: 8px;
    border-top-right-radius: 8px;
  }

  .theater-filter-dropdown-item:last-child {
    border-bottom-left-radius: 8px;
    border-bottom-right-radius: 8px;
  }

  .theater-filter-dropdown-item .filter-icon {
    width: 16px;
    height: 16px;
    display: flex;
    align-items: center;
    justify-content: center;
    color: ${e.primary};
  }

  .theater-filter-dropdown-item .filter-icon svg {
    width: 14px;
    height: 14px;
  }

  .theater-filter-dropdown-item .filter-checkmark {
    width: 18px;
    height: 18px;
    display: flex;
    align-items: center;
    justify-content: center;
    color: ${e.primary};
    flex-shrink: 0;
    margin-left: auto;
  }

  .theater-filter-dropdown-item .filter-checkmark svg {
    width: 16px;
    height: 16px;
  }

  .theater-main-area {
    flex: 1;
    min-height: 0;
    display: flex;
    flex-direction: column;
    overflow: hidden;
    background: ${e.background};
  }

  .theater-main-content {
    flex: 1;
    min-height: 0;
    display: flex;
    flex-direction: column;
    max-width: 880px;
    width: 100%;
    margin: 0 auto;
    padding: 0 24px;
  }

  /* ===== Header ===== */
  .sidebar-header {
    display: flex;
    flex-direction: column;
    gap: 12px;
    padding: 14.5px 20px;
    background: ${e.background};
    border-bottom: 1px solid ${e.border};
    flex-shrink: 0;
    animation: fadeIn 0.3s ease;
  }

  /* Theater mode header - no horizontal padding (handled by parent) */
  .theater-main-content .sidebar-header {
    padding-left: 0;
    padding-right: 0;
  }

  .header-top-row {
    display: flex;
    align-items: center;
    gap: 12px;
  }

  .header-bottom-row {
    display: flex;
    align-items: center;
    gap: 8px;
  }

  .sidebar-logo {
    width: 28px;
    height: 28px;
    border-radius: 8px;
    display: flex;
    align-items: center;
    justify-content: center;
    flex-shrink: 0;
    overflow: hidden;
    background: transparent;
  }

  .sidebar-logo img {
    width: 100%;
    height: 100%;
    object-fit: contain;
  }

  .sidebar-title {
    font-size: 16px;
    font-weight: 700;
    color: ${e.textPrimary};
    letter-spacing: -0.3px;
    line-height: 1.2;
    white-space: nowrap;
  }

  .sidebar-subtitle {
    font-size: 11px;
    font-weight: 500;
    color: ${e.textMuted};
    letter-spacing: 0.2px;
    line-height: 1.2;
  }

  .sidebar-info-text {
    font-size: 13px;
    font-weight: 600;
    color: ${e.textSecondary};
    padding: 8px 0 4px;
  }

  /* ===== Bucket Selector ===== */
  .bucket-selector {
    flex: 1;
    position: relative;
    min-width: 0;
  }

  .bucket-selector-btn {
    display: flex;
    align-items: center;
    gap: 8px;
    padding: 6px 12px;
    background: ${e.backgroundSecondary};
    border: 1px solid ${e.borderLight};
    border-radius: 8px;
    cursor: pointer;
    color: ${e.textPrimary};
    font-size: 12px;
    font-weight: 600;
    width: 100%;
    transition: all 0.2s ease;
    font-family: inherit;
  }

  .bucket-selector-btn:hover {
    background: ${e.backgroundHover};
    border-color: ${e.border};
  }

  .bucket-selector-btn .bucket-name {
    flex: 1;
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
    text-align: left;
  }

  .bucket-selector-btn .chevron {
    flex-shrink: 0;
    color: ${e.textMuted};
    transition: transform 0.2s ease;
    display: flex;
    align-items: center;
  }

  .bucket-selector-btn .chevron.open {
    transform: rotate(180deg);
  }

  /* ===== Bucket Dropdown ===== */
  .bucket-dropdown {
    position: absolute;
    top: calc(100% + 6px);
    left: 0;
    right: 0;
    background: ${e.background};
    border: 1px solid ${e.border};
    border-radius: 12px;
    box-shadow: 0 8px 24px ${e.shadowColor};
    z-index: 100;
    max-height: 350px;
    overflow: hidden;
    padding: 6px;
    opacity: 0;
    transform: translateY(-6px);
    transition: all 0.2s ease;
    pointer-events: none;
  }

  .bucket-dropdown.open {
    opacity: 1;
    transform: translateY(0);
    pointer-events: auto;
  }

  .bucket-dropdown::-webkit-scrollbar {
    width: 5px;
  }

  .bucket-dropdown::-webkit-scrollbar-track {
    background: transparent;
  }

  .bucket-dropdown::-webkit-scrollbar-thumb {
    background: ${e.textMuted};
    border-radius: 3px;
  }

  .bucket-dropdown-item {
    display: flex;
    align-items: center;
    gap: 10px;
    padding: 10px 12px;
    border-radius: 8px;
    cursor: pointer;
    transition: all 0.2s ease;
    font-size: 13px;
    color: ${e.textPrimary};
  }

  .bucket-dropdown-item:hover {
    background: ${e.backgroundHover};
    transform: translateX(2px);
  }

  .bucket-dropdown-item.selected {
    background: linear-gradient(135deg, rgba(${e.primaryRgb}, 0.08) 0%, rgba(118, 75, 162, 0.08) 100%);
    border: 1px solid ${e.border};
  }

  .bucket-dropdown-item .item-icon {
    width: 28px;
    height: 28px;
    border-radius: 8px;
    display: flex;
    align-items: center;
    justify-content: center;
    background: linear-gradient(135deg, rgba(${e.primaryRgb}, 0.12) 0%, rgba(118, 75, 162, 0.12) 100%);
    color: ${e.primary};
    font-size: 14px;
    flex-shrink: 0;
  }

  .bucket-dropdown-item .item-details {
    flex: 1;
    min-width: 0;
    display: flex;
    flex-direction: column;
    gap: 1px;
  }

  .bucket-dropdown-item .item-name {
    flex: 1;
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
    font-weight: 600;
    font-size: 12px;
  }

  .bucket-dropdown-item .item-count {
    font-size: 10px;
    color: ${e.textMuted};
    flex-shrink: 0;
  }

  /* ===== Dropdown Search ===== */
  .dropdown-search-container {
    display: flex;
    align-items: center;
    gap: 8px;
    padding: 8px 10px;
    margin-bottom: 6px;
    background: ${e.backgroundSecondary};
    border: 1px solid ${e.borderLight};
    border-radius: 8px;
    transition: all 0.2s ease;
  }

  .dropdown-search-container:focus-within {
    border-color: ${e.primary};
    box-shadow: 0 0 0 2px rgba(${e.primaryRgb}, 0.12);
  }

  .dropdown-search-icon {
    color: ${e.textMuted};
    display: flex;
    align-items: center;
    justify-content: center;
    flex-shrink: 0;
  }

  .dropdown-search-input {
    flex: 1;
    border: none;
    background: transparent;
    font-size: 12px;
    font-family: inherit;
    color: ${e.textPrimary};
    outline: none;
    min-width: 0;
  }

  .dropdown-search-input::placeholder {
    color: ${e.textMuted};
  }

  .dropdown-items-container {
    max-height: 240px;
    overflow-y: auto;
    scrollbar-width: thin;
    scrollbar-color: transparent transparent;
  }

  .dropdown-items-container:hover {
    scrollbar-color: ${e.textMuted} transparent;
  }

  .dropdown-items-container::-webkit-scrollbar {
    width: 4px;
  }

  .dropdown-items-container::-webkit-scrollbar-track {
    background: transparent;
  }

  .dropdown-items-container::-webkit-scrollbar-thumb {
    background: transparent;
    border-radius: 2px;
  }

  .dropdown-items-container:hover::-webkit-scrollbar-thumb {
    background: ${e.textMuted};
  }

  /* ===== New Chat Action Button ===== */
  .new-chat-action-btn:hover:not(:disabled) {
    background: linear-gradient(135deg, rgba(${e.primaryRgb}, 0.12) 0%, rgba(118, 75, 162, 0.12) 100%);
    color: ${e.primary};
    border-color: ${e.primary};
    transform: translateY(-1px);
  }

  /* ===== Header Buttons ===== */
  .header-action-buttons {
    display: flex;
    gap: 6px;
    margin-left: 12px;
  }

  .new-chat-btn {
    width: 32px;
    height: 32px;
    border-radius: 8px;
    border: 1px solid ${e.borderLight};
    background: transparent;
    color: ${e.textMuted};
    cursor: pointer;
    transition: all 0.2s ease;
    font-family: inherit;
    display: flex;
    align-items: center;
    justify-content: center;
    flex-shrink: 0;
    position: relative;
  }

  .new-chat-btn:hover {
    background: ${e.backgroundHover};
    color: ${e.error};
    border-color: ${e.error};
    transform: translateY(-1px);
  }

  .new-chat-btn svg {
    width: 16px;
    height: 16px;
  }

  .save-chat-btn {
    width: 32px;
    height: 32px;
    border-radius: 8px;
    border: 1px solid ${e.borderLight};
    background: transparent;
    color: ${e.textMuted};
    cursor: pointer;
    transition: all 0.2s ease;
    font-family: inherit;
    display: flex;
    align-items: center;
    justify-content: center;
    flex-shrink: 0;
    position: relative;
  }

  .save-chat-btn:hover {
    background: ${e.backgroundHover};
    color: ${e.success};
    border-color: ${e.success};
    transform: translateY(-1px);
  }

  .save-chat-btn svg {
    width: 16px;
    height: 16px;
  }

  .save-chat-btn:disabled {
    opacity: 0.4;
    cursor: not-allowed;
    transform: none !important;
  }

  /* Tooltip styles */
  .tooltip {
    position: absolute;
    bottom: calc(100% + 8px);
    left: 50%;
    transform: translateX(-50%);
    background: ${e.textPrimary};
    color: ${e.background};
    padding: 6px 10px;
    border-radius: 6px;
    font-size: 11px;
    font-weight: 500;
    white-space: nowrap;
    pointer-events: none;
    opacity: 0;
    transition: opacity 0.2s ease;
    z-index: 1000;
    box-shadow: 0 4px 12px rgba(0, 0, 0, 0.15);
  }

  .tooltip::after {
    content: '';
    position: absolute;
    top: 100%;
    left: 50%;
    transform: translateX(-50%);
    border: 5px solid transparent;
    border-top-color: ${e.textPrimary};
  }

  .new-chat-btn:hover .tooltip,
  .save-chat-btn:hover .tooltip {
    opacity: 1;
  }

  .theater-btn {
    width: 32px;
    height: 32px;
    border-radius: 8px;
    border: 1px solid ${e.borderLight};
    background: transparent;
    color: ${e.textMuted};
    cursor: pointer;
    display: flex;
    align-items: center;
    justify-content: center;
    transition: all 0.2s ease;
    flex-shrink: 0;
    font-family: inherit;
    margin-right: 8px;
  }

  .theater-btn:hover {
    background: ${e.backgroundHover};
    color: ${e.primary};
    border-color: ${e.primary};
  }

  .close-btn {
    width: 32px;
    height: 32px;
    border-radius: 8px;
    border: 1px solid ${e.borderLight};
    background: transparent;
    color: ${e.textMuted};
    cursor: pointer;
    display: flex;
    align-items: center;
    justify-content: center;
    transition: all 0.2s ease;
    flex-shrink: 0;
    font-family: inherit;
  }

  .close-btn:hover {
    background: ${e.backgroundHover};
    color: ${e.textPrimary};
    border-color: ${e.border};
  }

  /* ===== Messages Area ===== */
  .messages-area {
    flex: 1;
    min-height: 0;
    overflow-y: auto;
    overflow-x: hidden;
    /* Symmetric padding (was asymmetric 20/12 to "make room" for the scrollbar).
       scrollbar-gutter: stable now reserves a dedicated lane for the scrollbar
       OUTSIDE the padding box, so the content gets equal 20px breathing room
       on both sides and the bubble no longer butts against the scrollbar. */
    padding: 24px 20px;
    scrollbar-gutter: stable;
    display: flex;
    flex-direction: column;
    gap: 20px;
    background: ${e.background};
    scroll-behavior: smooth;
    /* Firefox */
    scrollbar-width: thin;
    scrollbar-color: ${e.border} transparent;
  }

  /* Theater mode messages area - no horizontal padding (handled by parent) */
  .theater-main-content .messages-area {
    padding-left: 0;
    padding-right: 0;
  }

  /* Subtle scrollbar — matches Claude/ChatGPT style. Track is invisible (just
     inherits the page background); thumb is a low-opacity neutral that gets
     slightly more opaque on hover. Avoids using textSecondary for the thumb
     (the previous setup) which read as a heavy dark bar. */
  .messages-area::-webkit-scrollbar {
    width: 8px;
  }

  .messages-area::-webkit-scrollbar-track {
    background: transparent;
  }

  .messages-area::-webkit-scrollbar-thumb {
    background: ${e.border};
    border-radius: 4px;
    min-height: 40px;
    transition: background 0.2s ease;
  }

  .messages-area::-webkit-scrollbar-thumb:hover {
    background: ${e.textMuted};
  }

  .messages-area::-webkit-scrollbar-thumb:active {
    background: ${e.textMuted};
  }

  /* ===== Empty State ===== */
  .empty-state {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    flex: 1;
    gap: 20px;
    padding: 40px 20px;
    margin-top: -40px;
    text-align: center;
    animation: fadeIn 0.5s ease;
  }

  .empty-state-icon {
    width: 64px;
    height: 64px;
    border-radius: 16px;
    background: linear-gradient(135deg, rgba(${e.primaryRgb}, 0.12) 0%, rgba(118, 75, 162, 0.12) 100%);
    display: flex;
    align-items: center;
    justify-content: center;
    color: ${e.primary};
    font-size: 32px;
    margin-bottom: 8px;
  }

  .empty-state-title {
    font-size: 16px;
    font-weight: 700;
    color: ${e.textPrimary};
    line-height: 1.4;
    letter-spacing: -0.2px;
  }

  .empty-state-subtitle {
    font-size: 12px;
    color: ${e.textMuted};
    line-height: 1.6;
    max-width: 260px;
  }

  .empty-state-suggestions {
    display: flex;
    flex-direction: column;
    gap: 8px;
    width: 100%;
    max-width: 300px;
    margin-top: 8px;
  }

  .suggestion-chip {
    display: flex;
    align-items: center;
    gap: 10px;
    padding: 10px 14px;
    border-radius: 10px;
    border: 1px solid ${e.borderLight};
    background: ${e.background};
    color: ${e.textSecondary};
    font-size: 12px;
    font-weight: 500;
    cursor: pointer;
    transition: all 0.2s ease;
    font-family: inherit;
    text-align: left;
  }

  .suggestion-chip:hover {
    border-color: ${e.primary};
    background: ${e.backgroundSelected};
    color: ${e.primary};
    transform: translateY(-1px);
    box-shadow: 0 2px 8px ${e.shadowColor};
  }

  .suggestion-chip-icon {
    width: 28px;
    height: 28px;
    border-radius: 8px;
    background: linear-gradient(135deg, rgba(${e.primaryRgb}, 0.12) 0%, rgba(118, 75, 162, 0.12) 100%);
    display: flex;
    align-items: center;
    justify-content: center;
    color: ${e.primary};
    flex-shrink: 0;
    font-size: 13px;
  }

  /* ===== Message Bubbles ===== */
  .message-row {
    display: flex;
    gap: 10px;
    max-width: 100%;
    animation: fadeInMsg 0.3s ease;
  }

  .message-row.user {
    align-self: flex-end;
    flex-direction: row-reverse;
  }

  .message-row.assistant {
    align-self: flex-start;
  }

  .message-avatar {
    width: 28px;
    height: 28px;
    border-radius: 8px;
    display: flex;
    align-items: center;
    justify-content: center;
    flex-shrink: 0;
    font-size: 12px;
    font-weight: 600;
  }

  .message-row.user .message-avatar {
    background: linear-gradient(135deg, rgba(${e.primaryRgb}, 0.15) 0%, rgba(118, 75, 162, 0.15) 100%);
    color: ${e.primary};
  }

  .message-row.assistant .message-avatar {
    background: ${e.primaryGradient};
    color: white;
    box-shadow: 0 2px 6px ${e.shadowPrimary};
  }

  .message-content-wrapper {
    display: flex;
    flex-direction: column;
    gap: 4px;
    min-width: 0;
  }

  .message-bubble {
    padding: 0;
    border-radius: 0;
    font-size: 14px;
    line-height: 1.7;
    position: relative;
    word-wrap: break-word;
    overflow-wrap: break-word;
    transition: all 0.2s ease;
  }

  .message-row.user .message-bubble {
    background: transparent;
    color: ${e.textPrimary};
  }

  .message-row.assistant .message-bubble {
    background: transparent;
    color: ${e.textPrimary};
    padding: 16px;
    border-radius: 12px;
    background: ${e.backgroundSecondary};
    border: 1px solid ${e.borderLight};
  }

  .message-row.assistant:hover .message-bubble {
    background: ${e.backgroundHover};
    border-color: ${e.border};
  }

  /* Remove bubble styling when it contains typing indicator */
  .message-row.assistant .message-bubble:has(.typing-indicator) {
    background: transparent;
    border: none;
    padding: 0;
  }

  .message-row.assistant:hover .message-bubble:has(.typing-indicator) {
    background: transparent;
    border: none;
  }

  .message-timestamp {
    font-size: 10px;
    color: ${e.textMuted};
    padding: 0 4px;
  }

  .message-row.user .message-timestamp {
    text-align: right;
  }

  /* ===== Message Actions ===== */
  .message-actions {
    display: flex;
    gap: 4px;
    opacity: 0;
    transition: all 0.2s ease;
    transform: translateY(2px);
  }

  .message-row:hover .message-actions {
    opacity: 1;
    transform: translateY(0);
  }

  .message-row.user .message-actions {
    justify-content: flex-end;
  }

  .msg-action-btn {
    padding: 4px 10px;
    border: 1px solid ${e.borderLight};
    background: ${e.background};
    color: ${e.textMuted};
    border-radius: 6px;
    font-size: 10px;
    font-weight: 500;
    cursor: pointer;
    transition: all 0.2s ease;
    font-family: inherit;
    display: flex;
    align-items: center;
    gap: 4px;
  }

  .msg-action-btn:hover {
    border-color: ${e.primary};
    color: ${e.primary};
    background: ${e.backgroundSelected};
  }

  .msg-action-btn.copied {
    border-color: ${e.success};
    color: ${e.success};
    background: ${e.success}12;
  }

  /* ===== Typing Indicator ===== */
  .typing-indicator {
    display: flex;
    gap: 8px;
    padding: 10px 14px;
    align-items: center;
  }

  .typing-status-text {
    font-size: 11px;
    color: ${e.textMuted};
    font-weight: 500;
    letter-spacing: 0.2px;
  }

  .typing-dots {
    display: flex;
    gap: 4px;
    align-items: center;
  }

  .typing-dot {
    width: 5px;
    height: 5px;
    border-radius: 50%;
    background: ${e.primary};
    animation: typingBounce 1.4s infinite ease-in-out;
    opacity: 0.6;
  }

  .typing-dot:nth-child(2) {
    animation-delay: 0.2s;
  }

  .typing-dot:nth-child(3) {
    animation-delay: 0.4s;
  }

  /* ===== Scroll to Bottom ===== */
  .scroll-to-bottom {
    position: absolute;
    bottom: 16px;
    right: 16px;
    width: 36px;
    height: 36px;
    border-radius: 50%;
    background: ${e.background};
    border: 1px solid ${e.border};
    box-shadow: 0 4px 12px ${e.shadowColor};
    cursor: pointer;
    display: flex;
    align-items: center;
    justify-content: center;
    color: ${e.textSecondary};
    transition: all 0.2s ease;
    z-index: 10;
    font-family: inherit;
  }

  .scroll-to-bottom:hover {
    background: ${e.primaryGradient};
    color: white;
    border-color: transparent;
    transform: translateY(-2px);
    box-shadow: 0 8px 24px ${e.shadowPrimary};
  }

  .scroll-to-bottom.hidden {
    opacity: 0;
    pointer-events: none;
    transform: translateY(8px);
  }

  /* ===== Input Area ===== */
  .input-area {
    padding: 16px 20px;
    background: ${e.background};
    border-top: 1px solid ${e.border};
    flex-shrink: 0;
    animation: fadeIn 0.3s ease;
  }

  /* Theater mode input area - no horizontal padding (handled by parent) */
  .theater-main-content .input-area {
    padding-left: 0;
    padding-right: 0;
    border-top: none;
  }

  .controls-row {
    display: flex;
    align-items: center;
    gap: 8px;
    margin-bottom: 10px;
  }

  /* ===== Model Badge ===== */
  .model-badge {
    display: flex;
    align-items: center;
    gap: 6px;
    padding: 6px 12px;
    background: linear-gradient(135deg, rgba(${e.primaryRgb}, 0.08) 0%, rgba(118, 75, 162, 0.08) 100%);
    border: 1px solid ${e.borderLight};
    border-radius: 8px;
    font-size: 11px;
    font-weight: 600;
    color: ${e.textSecondary};
    cursor: pointer;
    transition: all 0.2s ease;
    white-space: nowrap;
    font-family: inherit;
    flex-shrink: 0;
  }

  .model-badge:hover {
    border-color: ${e.primary};
    color: ${e.primary};
    background: linear-gradient(135deg, rgba(${e.primaryRgb}, 0.15) 0%, rgba(118, 75, 162, 0.15) 100%);
    transform: translateY(-1px);
    box-shadow: 0 2px 8px ${e.shadowColor};
  }

  .model-badge .badge-icon {
    width: 16px;
    height: 16px;
    border-radius: 4px;
    background: ${e.primaryGradient};
    display: flex;
    align-items: center;
    justify-content: center;
    color: white;
    font-size: 8px;
  }

  .model-badge .badge-chevron {
    font-size: 8px;
    color: ${e.textMuted};
    display: flex;
    align-items: center;
  }

  /* ===== Chat Action Buttons (Icon-Only) ===== */
  .chat-action-btn {
    display: flex;
    align-items: center;
    justify-content: center;
    width: 32px;
    height: 32px;
    padding: 0;
    border-radius: 8px;
    border: 1px solid ${e.borderLight};
    background: transparent;
    color: ${e.textMuted};
    cursor: pointer;
    transition: all 0.2s ease;
    flex-shrink: 0;
  }

  .chat-action-btn svg {
    width: 14px;
    height: 14px;
    flex-shrink: 0;
  }

  .chat-action-btn:disabled {
    opacity: 0.4;
    cursor: not-allowed;
  }

  .save-btn:hover:not(:disabled) {
    background: ${e.success}12;
    color: ${e.success};
    border-color: ${e.success};
    transform: translateY(-1px);
  }

  .save-btn.loading svg,
  .fork-btn.loading svg {
    animation: spin 1s linear infinite;
    stroke: ${e.primary};
  }

  .fork-btn:hover:not(:disabled) {
    background: rgba(${e.primaryRgb}, 0.12);
    color: ${e.primary};
    border-color: ${e.primary};
    transform: translateY(-1px);
  }

  @keyframes spin {
    from {
      transform: rotate(0deg);
    }
    to {
      transform: rotate(360deg);
    }
  }

  .clear-btn:hover:not(:disabled) {
    background: ${e.error}12;
    color: ${e.error};
    border-color: ${e.error};
    transform: translateY(-1px);
  }

  /* ===== Model Dropdown ===== */
  .model-dropdown {
    position: absolute;
    bottom: calc(100% + 6px);
    left: 0;
    width: 320px;
    background: ${e.background};
    border: 1px solid ${e.border};
    border-radius: 12px;
    box-shadow: 0 8px 24px ${e.shadowColor};
    z-index: 200;
    max-height: 380px;
    overflow-y: auto;
    padding: 6px;
    opacity: 0;
    transform: translateY(6px);
    transition: all 0.2s ease;
    pointer-events: none;
  }

  .model-dropdown.open {
    opacity: 1;
    transform: translateY(0);
    pointer-events: auto;
  }

  .model-dropdown::-webkit-scrollbar {
    width: 5px;
  }

  .model-dropdown::-webkit-scrollbar-track {
    background: transparent;
  }

  .model-dropdown::-webkit-scrollbar-thumb {
    background: ${e.textMuted};
    border-radius: 3px;
  }

  .model-category-header {
    padding: 10px 12px 5px;
    font-size: 10px;
    font-weight: 700;
    text-transform: uppercase;
    letter-spacing: 0.8px;
    color: ${e.textMuted};
  }

  .model-category-header::after {
    content: '';
    display: block;
    width: 20px;
    height: 2px;
    background: ${e.primaryGradient};
    border-radius: 1px;
    margin-top: 4px;
  }

  .model-dropdown-item {
    display: flex;
    align-items: center;
    gap: 10px;
    padding: 8px 12px;
    border-radius: 8px;
    cursor: pointer;
    transition: all 0.2s ease;
  }

  .model-dropdown-item:hover {
    background: ${e.backgroundHover};
    transform: translateX(2px);
  }

  .model-dropdown-item.selected {
    background: ${e.backgroundSelected};
    border-left: 3px solid ${e.primary};
    padding-left: 9px;
  }

  .model-dropdown-item .model-icon {
    width: 28px;
    height: 28px;
    border-radius: 6px;
    background: linear-gradient(135deg, rgba(${e.primaryRgb}, 0.1) 0%, rgba(118, 75, 162, 0.1) 100%);
    display: flex;
    align-items: center;
    justify-content: center;
    color: ${e.primary};
    font-size: 11px;
    font-weight: 700;
    flex-shrink: 0;
  }

  .model-dropdown-item .model-info {
    flex: 1;
    min-width: 0;
    display: flex;
    flex-direction: column;
    gap: 1px;
  }

  .model-dropdown-item .model-name {
    font-size: 12px;
    font-weight: 600;
    color: ${e.textPrimary};
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
  }

  .model-dropdown-item .model-desc {
    font-size: 10px;
    color: ${e.textMuted};
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
  }

  .model-dropdown-item .model-check {
    color: ${e.primary};
    font-size: 14px;
    flex-shrink: 0;
    opacity: 0;
  }

  .model-dropdown-item.selected .model-check {
    opacity: 1;
  }

  /* Model name row with tier tag */
  .model-dropdown-item .model-name-row {
    display: flex;
    align-items: center;
    gap: 6px;
    min-width: 0;
  }

  .model-dropdown-item .model-name-row .model-name {
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
  }

  .model-tier-tag {
    display: inline-flex;
    align-items: center;
    padding: 1px 5px;
    border-radius: 4px;
    font-size: 9px;
    font-weight: 700;
    background: rgba(${e.primaryRgb}, 0.12);
    color: ${e.primary};
    flex-shrink: 0;
    letter-spacing: 0.3px;
  }

  /* Lock icon for premium models */
  .model-lock-icon {
    color: ${e.textMuted};
    font-size: 12px;
    flex-shrink: 0;
    display: flex;
    align-items: center;
  }

  /* "Recommended" pill on the model that matches the user's plan default.
     Sized to match .model-tier-tag dimensions; sentence case + no
     letter-spacing so the text doesn't render visually wider than
     "2x credits" and crowd the row. */
  .model-recommended-tag {
    display: inline-flex;
    align-items: center;
    padding: 1px 5px;
    border-radius: 4px;
    font-size: 9px;
    font-weight: 600;
    background: ${e.primaryGradient};
    color: #fff;
    flex-shrink: 0;
    line-height: 1.4;
  }

  /* "Show all models" / "Show less" toggle at the bottom of the dropdown. */
  .show-all-models-toggle {
    width: 100%;
    display: flex;
    align-items: center;
    justify-content: center;
    gap: 4px;
    padding: 8px 12px;
    border: none;
    border-top: 1px solid ${e.border};
    background: transparent;
    color: ${e.textMuted};
    font-size: 11px;
    font-weight: 500;
    cursor: pointer;
    transition: background 0.15s ease, color 0.15s ease;
  }

  .show-all-models-toggle:hover {
    background: rgba(${e.primaryRgb}, 0.06);
    color: ${e.textPrimary};
  }

  /* Locked model item styling */
  .model-dropdown-item.locked {
    opacity: 0.55;
  }

  .model-dropdown-item.locked:hover {
    background: rgba(${e.primaryRgb}, 0.04);
    transform: none;
  }

  /* ===== Tools Button ===== */
  .tools-btn {
    width: 34px;
    height: 34px;
    min-width: 34px;
    border-radius: 8px;
    border: 1px solid ${e.borderLight};
    background: transparent;
    color: ${e.textMuted};
    cursor: pointer;
    display: flex;
    align-items: center;
    justify-content: center;
    transition: all 0.2s ease;
    position: relative;
    font-family: inherit;
    flex-shrink: 0;
  }

  .tools-btn:hover {
    background: ${e.backgroundHover};
    color: ${e.primary};
    border-color: ${e.primary};
    transform: translateY(-1px);
  }

  .tools-btn.has-active {
    color: ${e.primary};
    border-color: ${e.primary};
    background: linear-gradient(135deg, rgba(${e.primaryRgb}, 0.08) 0%, rgba(118, 75, 162, 0.08) 100%);
  }

  .tools-btn .active-dot {
    position: absolute;
    top: -2px;
    right: -2px;
    width: 8px;
    height: 8px;
    border-radius: 50%;
    background: ${e.success};
    border: 2px solid ${e.background};
  }

  /* ===== Website Context Toggle ===== */
  .website-context-toggle {
    display: flex;
    align-items: center;
    gap: 8px;
    padding: 6px 12px;
    border-radius: 8px;
    border: 1px solid ${e.borderLight};
    background: transparent;
    cursor: pointer;
    transition: all 0.2s ease;
    font-family: inherit;
    flex-shrink: 0;
  }

  .website-context-toggle:hover:not(.disabled) {
    background: ${e.backgroundHover};
  }

  .website-context-toggle.disabled {
    opacity: 0.4;
    cursor: not-allowed;
  }

  .website-context-icon {
    width: 16px;
    height: 16px;
    flex-shrink: 0;
    display: flex;
    align-items: center;
    justify-content: center;
    color: ${e.success};
  }

  .website-context-toggle.disabled .website-context-icon {
    color: ${e.textMuted};
  }

  .website-context-label {
    font-size: 11px;
    font-weight: 600;
    color: ${e.textSecondary};
    white-space: nowrap;
  }

  .website-context-toggle.disabled .website-context-label {
    color: ${e.textMuted};
  }

  /* ===== Tools Dropdown ===== */
  .tools-dropdown {
    position: absolute;
    bottom: calc(100% + 6px);
    left: 0;
    width: 280px;
    background: ${e.background};
    border: 1px solid ${e.border};
    border-radius: 12px;
    box-shadow: 0 8px 24px ${e.shadowColor};
    z-index: 200;
    padding: 6px;
    opacity: 0;
    transform: translateY(6px);
    transition: all 0.2s ease;
    pointer-events: none;
  }

  .tools-dropdown.open {
    opacity: 1;
    transform: translateY(0);
    pointer-events: auto;
  }

  .tools-dropdown-title {
    font-size: 11px;
    font-weight: 700;
    color: ${e.textMuted};
    text-transform: uppercase;
    letter-spacing: 0.5px;
    padding: 8px 10px 6px;
  }

  .tool-item {
    display: flex;
    align-items: center;
    gap: 10px;
    padding: 10px;
    border-radius: 8px;
    cursor: pointer;
    transition: all 0.2s ease;
  }

  .tool-item:hover {
    background: ${e.backgroundHover};
  }

  .tool-icon-container {
    width: 32px;
    height: 32px;
    border-radius: 8px;
    display: flex;
    align-items: center;
    justify-content: center;
    flex-shrink: 0;
    font-size: 14px;
  }

  .tool-icon-container.web-search {
    background: ${e.info}15;
    color: ${e.info};
  }

  .tool-icon-container.url-extraction {
    background: ${e.warning}15;
    color: ${e.warning};
  }

  .tool-icon-container.website-context {
    background: ${e.success}15;
    color: ${e.success};
  }

  .tool-icon-container.disabled {
    opacity: 0.4;
    cursor: not-allowed;
  }

  .tool-info {
    flex: 1;
    min-width: 0;
  }

  .tool-item.disabled {
    opacity: 0.5;
    cursor: not-allowed;
    pointer-events: none;
  }

  .tool-label {
    font-size: 12px;
    font-weight: 600;
    color: ${e.textPrimary};
  }

  .tool-desc {
    font-size: 10px;
    color: ${e.textMuted};
    margin-top: 1px;
  }

  /* ===== Toggle Switch ===== */
  .toggle-switch {
    width: 38px;
    height: 22px;
    border-radius: 11px;
    background: ${e.border};
    position: relative;
    cursor: pointer;
    transition: all 0.3s ease;
    flex-shrink: 0;
  }

  .toggle-switch.active {
    background: ${e.primaryGradient};
    box-shadow: 0 2px 8px ${e.shadowPrimary};
  }

  .toggle-switch-knob {
    width: 18px;
    height: 18px;
    border-radius: 50%;
    background: white;
    position: absolute;
    top: 2px;
    left: 2px;
    transition: transform 0.3s cubic-bezier(0.4, 0, 0.2, 1);
    box-shadow: 0 1px 4px rgba(0,0,0,0.2);
  }

  .toggle-switch.active .toggle-switch-knob {
    transform: translateX(16px);
  }

  /* ===== Input Row ===== */
  .input-row {
    display: flex;
    align-items: center;
    gap: 10px;
  }

  .input-wrapper {
    flex: 1;
    position: relative;
  }

  .chat-textarea {
    width: 100%;
    padding: 12px 16px;
    border: 1px solid ${e.borderLight};
    border-radius: 14px;
    background: ${e.backgroundSecondary};
    color: ${e.textPrimary};
    font-size: 13px;
    font-family: inherit;
    line-height: 1.5;
    resize: none;
    outline: none;
    transition: all 0.2s ease;
    min-height: 44px;
    max-height: 150px;
    overflow-y: auto;
    scrollbar-width: thin;
    scrollbar-color: ${e.textMuted} transparent;
  }

  .chat-textarea::placeholder {
    color: ${e.textMuted};
    font-weight: 400;
  }

  .chat-textarea:focus {
    border-color: ${e.primary};
    box-shadow: 0 0 0 3px rgba(${e.primaryRgb}, 0.12);
    background: ${e.background};
  }

  .chat-textarea::-webkit-scrollbar {
    width: 4px;
  }

  .chat-textarea::-webkit-scrollbar-track {
    background: transparent;
  }

  .chat-textarea::-webkit-scrollbar-thumb {
    background: ${e.textMuted};
    border-radius: 2px;
  }

  .chat-textarea::-webkit-scrollbar-thumb:hover {
    background: ${e.textSecondary};
  }

  /* ===== Send Button ===== */
  .send-btn {
    width: 44px;
    height: 44px;
    border-radius: 12px;
    border: none;
    background: ${e.primaryGradient};
    color: white;
    cursor: pointer;
    display: flex;
    align-items: center;
    justify-content: center;
    transition: all 0.3s ease;
    flex-shrink: 0;
    font-family: inherit;
    box-shadow: 0 2px 8px ${e.shadowPrimary};
  }

  .send-btn:hover:not(:disabled) {
    transform: translateY(-2px);
    box-shadow: 0 8px 24px ${e.shadowPrimary};
  }

  .send-btn:active:not(:disabled) {
    transform: translateY(0);
  }

  .send-btn:disabled {
    opacity: 0.35;
    cursor: not-allowed;
    box-shadow: none;
  }

  .send-btn.stop {
    background: ${e.error};
    border-radius: 12px;
    box-shadow: 0 2px 8px ${e.error}40;
  }

  .send-btn.stop:hover {
    box-shadow: 0 8px 24px ${e.error}40;
  }

  /* ===== Powered By Footer ===== */
  .powered-by {
    display: block;
    text-align: center;
    padding-top: 10px;
    font-size: 9px;
    color: ${e.textMuted};
    letter-spacing: 0.3px;
    line-height: 1.5;
  }

  .powered-by-accent {
    background: ${e.primaryGradient};
    -webkit-background-clip: text;
    -webkit-text-fill-color: transparent;
    background-clip: text;
    font-weight: 700;
    text-decoration: none;
    cursor: pointer;
    transition: opacity 0.2s ease;
  }

  .powered-by-accent:hover {
    opacity: 0.8;
  }

  /* ===== Markdown Content ===== */
  .markdown-content {
    font-size: 13px;
    line-height: 1.65;
    word-wrap: break-word;
    overflow-wrap: break-word;
  }

  .markdown-content p {
    margin: 0 0 8px 0;
  }

  .markdown-content p:last-child {
    margin-bottom: 0;
  }

  .markdown-content h1, .markdown-content h2, .markdown-content h3 {
    margin: 14px 0 8px 0;
    line-height: 1.3;
    font-weight: 600;
    color: ${e.textPrimary};
  }

  .markdown-content h1 { font-size: 1.25em; }
  .markdown-content h2 { font-size: 1.12em; }
  .markdown-content h3 { font-size: 1.02em; }

  .markdown-content ul, .markdown-content ol {
    margin: 6px 0;
    padding-left: 20px;
  }

  .markdown-content li {
    margin-bottom: 4px;
  }

  .markdown-content li::marker {
    color: ${e.primary};
  }

  .markdown-content pre {
    background: ${e.backgroundSecondary};
    border: 1px solid ${e.borderLight};
    border-radius: 10px;
    padding: 14px;
    overflow-x: auto;
    margin: 10px 0;
    font-size: 12px;
    line-height: 1.5;
    position: relative;
  }

  .message-row.user .markdown-content pre {
    background: rgba(255, 255, 255, 0.12);
    border-color: rgba(255, 255, 255, 0.15);
  }

  .markdown-content code {
    font-family: 'SF Mono', 'Fira Code', 'Cascadia Code', 'JetBrains Mono', Menlo, Consolas, monospace;
    font-size: 0.88em;
  }

  .markdown-content :not(pre) > code {
    background: ${e.primary}12;
    color: ${e.primary};
    border-radius: 4px;
    padding: 2px 6px;
    font-weight: 500;
  }

  .message-row.user .markdown-content :not(pre) > code {
    background: rgba(255, 255, 255, 0.2);
    color: white;
  }

  .markdown-content blockquote {
    border-left: 3px solid ${e.primary};
    padding: 8px 14px;
    margin: 10px 0;
    color: ${e.textSecondary};
    background: rgba(${e.primaryRgb}, 0.04);
    border-radius: 0 8px 8px 0;
    font-style: italic;
  }

  .markdown-content table {
    border-collapse: collapse;
    width: 100%;
    margin: 10px 0;
    font-size: 12px;
    border-radius: 8px;
    overflow: hidden;
  }

  .markdown-content th, .markdown-content td {
    border: 1px solid ${e.borderLight};
    padding: 8px 12px;
    text-align: left;
  }

  .markdown-content th {
    background: linear-gradient(135deg, rgba(${e.primaryRgb}, 0.08) 0%, rgba(118, 75, 162, 0.08) 100%);
    font-weight: 600;
    font-size: 11px;
    text-transform: uppercase;
    letter-spacing: 0.3px;
    color: ${e.textSecondary};
  }

  .markdown-content a {
    color: ${e.primary};
    text-decoration: none;
    font-weight: 500;
    transition: opacity 0.2s ease;
  }

  .message-row.user .markdown-content a {
    color: white;
    text-decoration: underline;
    text-decoration-style: dotted;
  }

  .markdown-content a:hover {
    text-decoration: underline;
    opacity: 0.85;
  }

  .markdown-content strong {
    font-weight: 600;
    color: ${e.textPrimary};
  }

  .markdown-content hr {
    border: none;
    border-top: 1px solid ${e.borderLight};
    margin: 14px 0;
  }

  .markdown-content img {
    max-width: 100%;
    border-radius: 10px;
    box-shadow: 0 2px 8px ${e.shadowColor};
  }

  /* ===== Chat Onboarding Tooltips (matching plurality-onboarding-tooltip style) ===== */
  @keyframes chatTooltipEnter {
    from {
      opacity: 0;
      transform: translateY(10px);
    }
    to {
      opacity: 1;
      transform: translateY(0);
    }
  }

  @keyframes chatTooltipExit {
    from {
      opacity: 1;
      transform: translateY(0);
    }
    to {
      opacity: 0;
      transform: translateY(10px);
    }
  }

  .chat-onboarding-tooltip {
    position: absolute;
    background: ${e.background};
    border-radius: 12px;
    box-shadow: 0 8px 32px ${e.shadowColor};
    border: 1px solid ${e.border};
    padding: 16px;
    max-width: 280px;
    z-index: 2147483647;
    animation: chatTooltipEnter 0.3s ease;
    font-family: 'Lexend', -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif;
  }

  .chat-onboarding-tooltip.fading-out {
    animation: chatTooltipExit 0.2s ease forwards;
  }

  .chat-onboarding-tooltip.privacy-tooltip {
    position: relative;
    margin: 12px 0 12px 42px;
    max-width: calc(100% - 54px);
  }

  .chat-tooltip-arrow {
    position: absolute;
    width: 12px;
    height: 12px;
    background: ${e.background};
    transform: rotate(45deg);
  }

  /* Arrow pointing up (tooltip below target) */
  .chat-tooltip-arrow.bottom {
    top: -6px;
    right: 24px;
    box-shadow: -2px -2px 4px ${e.shadowColor};
    border-left: 1px solid ${e.border};
    border-top: 1px solid ${e.border};
  }

  /* Arrow pointing down (tooltip above target) */
  .chat-tooltip-arrow.top {
    bottom: -6px;
    left: 24px;
    box-shadow: 2px 2px 4px ${e.shadowColor};
    border-right: 1px solid ${e.border};
    border-bottom: 1px solid ${e.border};
  }

  .chat-tooltip-title {
    font-size: 14px;
    font-weight: 600;
    color: ${e.textPrimary};
    margin: 0 0 8px 0;
    line-height: 1.4;
  }

  .chat-tooltip-content {
    font-size: 13px;
    color: ${e.textSecondary};
    line-height: 1.5;
    margin: 0 0 12px 0;
  }

  .chat-tooltip-dismiss {
    display: inline-block;
    padding: 8px 16px;
    background: ${e.primaryGradient};
    color: white;
    border: none;
    border-radius: 8px;
    font-size: 13px;
    font-weight: 500;
    cursor: pointer;
    transition: all 0.2s ease;
    font-family: inherit;
  }

  .chat-tooltip-dismiss:hover {
    transform: translateY(-1px);
    box-shadow: 0 4px 12px ${e.shadowPrimary};
  }
`;function In(){return{async:!1,breaks:!1,extensions:null,gfm:!0,hooks:null,pedantic:!1,renderer:null,silent:!1,tokenizer:null,walkTokens:null}}var Oe=In();function Zr(e){Oe=e}var pt={exec:()=>null};function z(e,t=""){let n=typeof e=="string"?e:e.source,o={replace:(r,i)=>{let a=typeof i=="string"?i:i.source;return a=a.replace(V.caret,"$1"),n=n.replace(r,a),o},getRegex:()=>new RegExp(n,t)};return o}var V={codeRemoveIndent:/^(?: {1,4}| {0,3}\t)/gm,outputLinkReplace:/\\([\[\]])/g,indentCodeCompensation:/^(\s+)(?:```)/,beginningSpace:/^\s+/,endingHash:/#$/,startingSpaceChar:/^ /,endingSpaceChar:/ $/,nonSpaceChar:/[^ ]/,newLineCharGlobal:/\n/g,tabCharGlobal:/\t/g,multipleSpaceGlobal:/\s+/g,blankLine:/^[ \t]*$/,doubleBlankLine:/\n[ \t]*\n[ \t]*$/,blockquoteStart:/^ {0,3}>/,blockquoteSetextReplace:/\n {0,3}((?:=+|-+) *)(?=\n|$)/g,blockquoteSetextReplace2:/^ {0,3}>[ \t]?/gm,listReplaceTabs:/^\t+/,listReplaceNesting:/^ {1,4}(?=( {4})*[^ ])/g,listIsTask:/^\[[ xX]\] /,listReplaceTask:/^\[[ xX]\] +/,anyLine:/\n.*\n/,hrefBrackets:/^<(.*)>$/,tableDelimiter:/[:|]/,tableAlignChars:/^\||\| *$/g,tableRowBlankLine:/\n[ \t]*$/,tableAlignRight:/^ *-+: *$/,tableAlignCenter:/^ *:-+: *$/,tableAlignLeft:/^ *:-+ *$/,startATag:/^<a /i,endATag:/^<\/a>/i,startPreScriptTag:/^<(pre|code|kbd|script)(\s|>)/i,endPreScriptTag:/^<\/(pre|code|kbd|script)(\s|>)/i,startAngleBracket:/^</,endAngleBracket:/>$/,pedanticHrefTitle:/^([^'"]*[^\s])\s+(['"])(.*)\2/,unicodeAlphaNumeric:/[\p{L}\p{N}]/u,escapeTest:/[&<>"']/,escapeReplace:/[&<>"']/g,escapeTestNoEncode:/[<>"']|&(?!(#\d{1,7}|#[Xx][a-fA-F0-9]{1,6}|\w+);)/,escapeReplaceNoEncode:/[<>"']|&(?!(#\d{1,7}|#[Xx][a-fA-F0-9]{1,6}|\w+);)/g,unescapeTest:/&(#(?:\d+)|(?:#x[0-9A-Fa-f]+)|(?:\w+));?/ig,caret:/(^|[^\[])\^/g,percentDecode:/%25/g,findPipe:/\|/g,splitPipe:/ \|/,slashPipe:/\\\|/g,carriageReturn:/\r\n|\r/g,spaceLine:/^ +$/gm,notSpaceStart:/^\S*/,endingNewline:/\n$/,listItemRegex:e=>new RegExp(`^( {0,3}${e})((?:[	 ][^\\n]*)?(?:\\n|$))`),nextBulletRegex:e=>new RegExp(`^ {0,${Math.min(3,e-1)}}(?:[*+-]|\\d{1,9}[.)])((?:[ 	][^\\n]*)?(?:\\n|$))`),hrRegex:e=>new RegExp(`^ {0,${Math.min(3,e-1)}}((?:- *){3,}|(?:_ *){3,}|(?:\\* *){3,})(?:\\n+|$)`),fencesBeginRegex:e=>new RegExp(`^ {0,${Math.min(3,e-1)}}(?:\`\`\`|~~~)`),headingBeginRegex:e=>new RegExp(`^ {0,${Math.min(3,e-1)}}#`),htmlBeginRegex:e=>new RegExp(`^ {0,${Math.min(3,e-1)}}<(?:[a-z].*>|!--)`,"i")},ys=/^(?:[ \t]*(?:\n|$))+/,ws=/^((?: {4}| {0,3}\t)[^\n]+(?:\n(?:[ \t]*(?:\n|$))*)?)+/,ks=/^ {0,3}(`{3,}(?=[^`\n]*(?:\n|$))|~{3,})([^\n]*)(?:\n|$)(?:|([\s\S]*?)(?:\n|$))(?: {0,3}\1[~`]* *(?=\n|$)|$)/,xt=/^ {0,3}((?:-[\t ]*){3,}|(?:_[ \t]*){3,}|(?:\*[ \t]*){3,})(?:\n+|$)/,vs=/^ {0,3}(#{1,6})(?=\s|$)(.*)(?:\n+|$)/,Ln=/(?:[*+-]|\d{1,9}[.)])/,Jr=/^(?!bull |blockCode|fences|blockquote|heading|html|table)((?:.|\n(?!\s*?\n|bull |blockCode|fences|blockquote|heading|html|table))+?)\n {0,3}(=+|-+) *(?:\n+|$)/,eo=z(Jr).replace(/bull/g,Ln).replace(/blockCode/g,/(?: {4}| {0,3}\t)/).replace(/fences/g,/ {0,3}(?:`{3,}|~{3,})/).replace(/blockquote/g,/ {0,3}>/).replace(/heading/g,/ {0,3}#{1,6}/).replace(/html/g,/ {0,3}<[^\n>]+>\n/).replace(/\|table/g,"").getRegex(),Cs=z(Jr).replace(/bull/g,Ln).replace(/blockCode/g,/(?: {4}| {0,3}\t)/).replace(/fences/g,/ {0,3}(?:`{3,}|~{3,})/).replace(/blockquote/g,/ {0,3}>/).replace(/heading/g,/ {0,3}#{1,6}/).replace(/html/g,/ {0,3}<[^\n>]+>\n/).replace(/table/g,/ {0,3}\|?(?:[:\- ]*\|)+[\:\- ]*\n/).getRegex(),Mn=/^([^\n]+(?:\n(?!hr|heading|lheading|blockquote|fences|list|html|table| +\n)[^\n]+)*)/,Es=/^[^\n]+/,An=/(?!\s*\])(?:\\.|[^\[\]\\])+/,Ts=z(/^ {0,3}\[(label)\]: *(?:\n[ \t]*)?([^<\s][^\s]*|<.*?>)(?:(?: +(?:\n[ \t]*)?| *\n[ \t]*)(title))? *(?:\n+|$)/).replace("label",An).replace("title",/(?:"(?:\\"?|[^"\\])*"|'[^'\n]*(?:\n[^'\n]+)*\n?'|\([^()]*\))/).getRegex(),Ss=z(/^( {0,3}bull)([ \t][^\n]+?)?(?:\n|$)/).replace(/bull/g,Ln).getRegex(),Gt="address|article|aside|base|basefont|blockquote|body|caption|center|col|colgroup|dd|details|dialog|dir|div|dl|dt|fieldset|figcaption|figure|footer|form|frame|frameset|h[1-6]|head|header|hr|html|iframe|legend|li|link|main|menu|menuitem|meta|nav|noframes|ol|optgroup|option|p|param|search|section|summary|table|tbody|td|tfoot|th|thead|title|tr|track|ul",Pn=/<!--(?:-?>|[\s\S]*?(?:-->|$))/,$s=z("^ {0,3}(?:<(script|pre|style|textarea)[\\s>][\\s\\S]*?(?:</\\1>[^\\n]*\\n+|$)|comment[^\\n]*(\\n+|$)|<\\?[\\s\\S]*?(?:\\?>\\n*|$)|<![A-Z][\\s\\S]*?(?:>\\n*|$)|<!\\[CDATA\\[[\\s\\S]*?(?:\\]\\]>\\n*|$)|</?(tag)(?: +|\\n|/?>)[\\s\\S]*?(?:(?:\\n[ 	]*)+\\n|$)|<(?!script|pre|style|textarea)([a-z][\\w-]*)(?:attribute)*? */?>(?=[ \\t]*(?:\\n|$))[\\s\\S]*?(?:(?:\\n[ 	]*)+\\n|$)|</(?!script|pre|style|textarea)[a-z][\\w-]*\\s*>(?=[ \\t]*(?:\\n|$))[\\s\\S]*?(?:(?:\\n[ 	]*)+\\n|$))","i").replace("comment",Pn).replace("tag",Gt).replace("attribute",/ +[a-zA-Z:_][\w.:-]*(?: *= *"[^"\n]*"| *= *'[^'\n]*'| *= *[^\s"'=<>`]+)?/).getRegex(),to=z(Mn).replace("hr",xt).replace("heading"," {0,3}#{1,6}(?:\\s|$)").replace("|lheading","").replace("|table","").replace("blockquote"," {0,3}>").replace("fences"," {0,3}(?:`{3,}(?=[^`\\n]*\\n)|~{3,})[^\\n]*\\n").replace("list"," {0,3}(?:[*+-]|1[.)]) ").replace("html","</?(?:tag)(?: +|\\n|/?>)|<(?:script|pre|style|textarea|!--)").replace("tag",Gt).getRegex(),Is=z(/^( {0,3}> ?(paragraph|[^\n]*)(?:\n|$))+/).replace("paragraph",to).getRegex(),Bn={blockquote:Is,code:ws,def:Ts,fences:ks,heading:vs,hr:xt,html:$s,lheading:eo,list:Ss,newline:ys,paragraph:to,table:pt,text:Es},cr=z("^ *([^\\n ].*)\\n {0,3}((?:\\| *)?:?-+:? *(?:\\| *:?-+:? *)*(?:\\| *)?)(?:\\n((?:(?! *\\n|hr|heading|blockquote|code|fences|list|html).*(?:\\n|$))*)\\n*|$)").replace("hr",xt).replace("heading"," {0,3}#{1,6}(?:\\s|$)").replace("blockquote"," {0,3}>").replace("code","(?: {4}| {0,3}	)[^\\n]").replace("fences"," {0,3}(?:`{3,}(?=[^`\\n]*\\n)|~{3,})[^\\n]*\\n").replace("list"," {0,3}(?:[*+-]|1[.)]) ").replace("html","</?(?:tag)(?: +|\\n|/?>)|<(?:script|pre|style|textarea|!--)").replace("tag",Gt).getRegex(),Ls={...Bn,lheading:Cs,table:cr,paragraph:z(Mn).replace("hr",xt).replace("heading"," {0,3}#{1,6}(?:\\s|$)").replace("|lheading","").replace("table",cr).replace("blockquote"," {0,3}>").replace("fences"," {0,3}(?:`{3,}(?=[^`\\n]*\\n)|~{3,})[^\\n]*\\n").replace("list"," {0,3}(?:[*+-]|1[.)]) ").replace("html","</?(?:tag)(?: +|\\n|/?>)|<(?:script|pre|style|textarea|!--)").replace("tag",Gt).getRegex()},Ms={...Bn,html:z(`^ *(?:comment *(?:\\n|\\s*$)|<(tag)[\\s\\S]+?</\\1> *(?:\\n{2,}|\\s*$)|<tag(?:"[^"]*"|'[^']*'|\\s[^'"/>\\s]*)*?/?> *(?:\\n{2,}|\\s*$))`).replace("comment",Pn).replace(/tag/g,"(?!(?:a|em|strong|small|s|cite|q|dfn|abbr|data|time|code|var|samp|kbd|sub|sup|i|b|u|mark|ruby|rt|rp|bdi|bdo|span|br|wbr|ins|del|img)\\b)\\w+(?!:|[^\\w\\s@]*@)\\b").getRegex(),def:/^ *\[([^\]]+)\]: *<?([^\s>]+)>?(?: +(["(][^\n]+[")]))? *(?:\n+|$)/,heading:/^(#{1,6})(.*)(?:\n+|$)/,fences:pt,lheading:/^(.+?)\n {0,3}(=+|-+) *(?:\n+|$)/,paragraph:z(Mn).replace("hr",xt).replace("heading",` *#{1,6} *[^
]`).replace("lheading",eo).replace("|table","").replace("blockquote"," {0,3}>").replace("|fences","").replace("|list","").replace("|html","").replace("|tag","").getRegex()},As=/^\\([!"#$%&'()*+,\-./:;<=>?@\[\]\\^_`{|}~])/,Ps=/^(`+)([^`]|[^`][\s\S]*?[^`])\1(?!`)/,no=/^( {2,}|\\)\n(?!\s*$)/,Bs=/^(`+|[^`])(?:(?= {2,}\n)|[\s\S]*?(?:(?=[\\<!\[`*_]|\b_|$)|[^ ](?= {2,}\n)))/,Kt=/[\p{P}\p{S}]/u,Nn=/[\s\p{P}\p{S}]/u,ro=/[^\s\p{P}\p{S}]/u,Ns=z(/^((?![*_])punctSpace)/,"u").replace(/punctSpace/g,Nn).getRegex(),oo=/(?!~)[\p{P}\p{S}]/u,Ds=/(?!~)[\s\p{P}\p{S}]/u,Rs=/(?:[^\s\p{P}\p{S}]|~)/u,Fs=/\[[^[\]]*?\]\((?:\\.|[^\\\(\)]|\((?:\\.|[^\\\(\)])*\))*\)|`[^`]*?`|<(?! )[^<>]*?>/g,io=/^(?:\*+(?:((?!\*)punct)|[^\s*]))|^_+(?:((?!_)punct)|([^\s_]))/,zs=z(io,"u").replace(/punct/g,Kt).getRegex(),Hs=z(io,"u").replace(/punct/g,oo).getRegex(),ao="^[^_*]*?__[^_*]*?\\*[^_*]*?(?=__)|[^*]+(?=[^*])|(?!\\*)punct(\\*+)(?=[\\s]|$)|notPunctSpace(\\*+)(?!\\*)(?=punctSpace|$)|(?!\\*)punctSpace(\\*+)(?=notPunctSpace)|[\\s](\\*+)(?!\\*)(?=punct)|(?!\\*)punct(\\*+)(?!\\*)(?=punct)|notPunctSpace(\\*+)(?=notPunctSpace)",_s=z(ao,"gu").replace(/notPunctSpace/g,ro).replace(/punctSpace/g,Nn).replace(/punct/g,Kt).getRegex(),Os=z(ao,"gu").replace(/notPunctSpace/g,Rs).replace(/punctSpace/g,Ds).replace(/punct/g,oo).getRegex(),Us=z("^[^_*]*?\\*\\*[^_*]*?_[^_*]*?(?=\\*\\*)|[^_]+(?=[^_])|(?!_)punct(_+)(?=[\\s]|$)|notPunctSpace(_+)(?!_)(?=punctSpace|$)|(?!_)punctSpace(_+)(?=notPunctSpace)|[\\s](_+)(?!_)(?=punct)|(?!_)punct(_+)(?!_)(?=punct)","gu").replace(/notPunctSpace/g,ro).replace(/punctSpace/g,Nn).replace(/punct/g,Kt).getRegex(),qs=z(/\\(punct)/,"gu").replace(/punct/g,Kt).getRegex(),js=z(/^<(scheme:[^\s\x00-\x1f<>]*|email)>/).replace("scheme",/[a-zA-Z][a-zA-Z0-9+.-]{1,31}/).replace("email",/[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+(@)[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)+(?![-_])/).getRegex(),Ys=z(Pn).replace("(?:-->|$)","-->").getRegex(),Ws=z("^comment|^</[a-zA-Z][\\w:-]*\\s*>|^<[a-zA-Z][\\w-]*(?:attribute)*?\\s*/?>|^<\\?[\\s\\S]*?\\?>|^<![a-zA-Z]+\\s[\\s\\S]*?>|^<!\\[CDATA\\[[\\s\\S]*?\\]\\]>").replace("comment",Ys).replace("attribute",/\s+[a-zA-Z:_][\w.:-]*(?:\s*=\s*"[^"]*"|\s*=\s*'[^']*'|\s*=\s*[^\s"'=<>`]+)?/).getRegex(),Ht=/(?:\[(?:\\.|[^\[\]\\])*\]|\\.|`[^`]*`|[^\[\]\\`])*?/,Gs=z(/^!?\[(label)\]\(\s*(href)(?:(?:[ \t]*(?:\n[ \t]*)?)(title))?\s*\)/).replace("label",Ht).replace("href",/<(?:\\.|[^\n<>\\])+>|[^ \t\n\x00-\x1f]*/).replace("title",/"(?:\\"?|[^"\\])*"|'(?:\\'?|[^'\\])*'|\((?:\\\)?|[^)\\])*\)/).getRegex(),so=z(/^!?\[(label)\]\[(ref)\]/).replace("label",Ht).replace("ref",An).getRegex(),lo=z(/^!?\[(ref)\](?:\[\])?/).replace("ref",An).getRegex(),Ks=z("reflink|nolink(?!\\()","g").replace("reflink",so).replace("nolink",lo).getRegex(),Dn={_backpedal:pt,anyPunctuation:qs,autolink:js,blockSkip:Fs,br:no,code:Ps,del:pt,emStrongLDelim:zs,emStrongRDelimAst:_s,emStrongRDelimUnd:Us,escape:As,link:Gs,nolink:lo,punctuation:Ns,reflink:so,reflinkSearch:Ks,tag:Ws,text:Bs,url:pt},Xs={...Dn,link:z(/^!?\[(label)\]\((.*?)\)/).replace("label",Ht).getRegex(),reflink:z(/^!?\[(label)\]\s*\[([^\]]*)\]/).replace("label",Ht).getRegex()},mn={...Dn,emStrongRDelimAst:Os,emStrongLDelim:Hs,url:z(/^((?:ftp|https?):\/\/|www\.)(?:[a-zA-Z0-9\-]+\.?)+[^\s<]*|^email/,"i").replace("email",/[A-Za-z0-9._+-]+(@)[a-zA-Z0-9-_]+(?:\.[a-zA-Z0-9-_]*[a-zA-Z0-9])+(?![-_])/).getRegex(),_backpedal:/(?:[^?!.,:;*_'"~()&]+|\([^)]*\)|&(?![a-zA-Z0-9]+;$)|[?!.,:;*_'"~)]+(?!$))+/,del:/^(~~?)(?=[^\s~])((?:\\.|[^\\])*?(?:\\.|[^\s~\\]))\1(?=[^~]|$)/,text:/^([`~]+|[^`~])(?:(?= {2,}\n)|(?=[a-zA-Z0-9.!#$%&'*+\/=?_`{\|}~-]+@)|[\s\S]*?(?:(?=[\\<!\[`*~_]|\b_|https?:\/\/|ftp:\/\/|www\.|$)|[^ ](?= {2,}\n)|[^a-zA-Z0-9.!#$%&'*+\/=?_`{\|}~-](?=[a-zA-Z0-9.!#$%&'*+\/=?_`{\|}~-]+@)))/},Vs={...mn,br:z(no).replace("{2,}","*").getRegex(),text:z(mn.text).replace("\\b_","\\b_| {2,}\\n").replace(/\{2,\}/g,"*").getRegex()},vt={normal:Bn,gfm:Ls,pedantic:Ms},rt={normal:Dn,gfm:mn,breaks:Vs,pedantic:Xs},Qs={"&":"&amp;","<":"&lt;",">":"&gt;",'"':"&quot;","'":"&#39;"},dr=e=>Qs[e];function ie(e,t){if(t){if(V.escapeTest.test(e))return e.replace(V.escapeReplace,dr)}else if(V.escapeTestNoEncode.test(e))return e.replace(V.escapeReplaceNoEncode,dr);return e}function pr(e){try{e=encodeURI(e).replace(V.percentDecode,"%")}catch{return null}return e}function ur(e,t){let n=e.replace(V.findPipe,(i,a,s)=>{let c=!1,d=a;for(;--d>=0&&s[d]==="\\";)c=!c;return c?"|":" |"}),o=n.split(V.splitPipe),r=0;if(o[0].trim()||o.shift(),o.length>0&&!o.at(-1)?.trim()&&o.pop(),t)if(o.length>t)o.splice(t);else for(;o.length<t;)o.push("");for(;r<o.length;r++)o[r]=o[r].trim().replace(V.slashPipe,"|");return o}function ot(e,t,n){let o=e.length;if(o===0)return"";let r=0;for(;r<o&&e.charAt(o-r-1)===t;)r++;return e.slice(0,o-r)}function Zs(e,t){if(e.indexOf(t[1])===-1)return-1;let n=0;for(let o=0;o<e.length;o++)if(e[o]==="\\")o++;else if(e[o]===t[0])n++;else if(e[o]===t[1]&&(n--,n<0))return o;return n>0?-2:-1}function hr(e,t,n,o,r){let i=t.href,a=t.title||null,s=e[1].replace(r.other.outputLinkReplace,"$1");o.state.inLink=!0;let c={type:e[0].charAt(0)==="!"?"image":"link",raw:n,href:i,title:a,text:s,tokens:o.inlineTokens(s)};return o.state.inLink=!1,c}function Js(e,t,n){let o=e.match(n.other.indentCodeCompensation);if(o===null)return t;let r=o[1];return t.split(`
`).map(i=>{let a=i.match(n.other.beginningSpace);if(a===null)return i;let[s]=a;return s.length>=r.length?i.slice(r.length):i}).join(`
`)}var _t=class{options;rules;lexer;constructor(e){this.options=e||Oe}space(e){let t=this.rules.block.newline.exec(e);if(t&&t[0].length>0)return{type:"space",raw:t[0]}}code(e){let t=this.rules.block.code.exec(e);if(t){let n=t[0].replace(this.rules.other.codeRemoveIndent,"");return{type:"code",raw:t[0],codeBlockStyle:"indented",text:this.options.pedantic?n:ot(n,`
`)}}}fences(e){let t=this.rules.block.fences.exec(e);if(t){let n=t[0],o=Js(n,t[3]||"",this.rules);return{type:"code",raw:n,lang:t[2]?t[2].trim().replace(this.rules.inline.anyPunctuation,"$1"):t[2],text:o}}}heading(e){let t=this.rules.block.heading.exec(e);if(t){let n=t[2].trim();if(this.rules.other.endingHash.test(n)){let o=ot(n,"#");(this.options.pedantic||!o||this.rules.other.endingSpaceChar.test(o))&&(n=o.trim())}return{type:"heading",raw:t[0],depth:t[1].length,text:n,tokens:this.lexer.inline(n)}}}hr(e){let t=this.rules.block.hr.exec(e);if(t)return{type:"hr",raw:ot(t[0],`
`)}}blockquote(e){let t=this.rules.block.blockquote.exec(e);if(t){let n=ot(t[0],`
`).split(`
`),o="",r="",i=[];for(;n.length>0;){let a=!1,s=[],c;for(c=0;c<n.length;c++)if(this.rules.other.blockquoteStart.test(n[c]))s.push(n[c]),a=!0;else if(!a)s.push(n[c]);else break;n=n.slice(c);let d=s.join(`
`),p=d.replace(this.rules.other.blockquoteSetextReplace,`
    $1`).replace(this.rules.other.blockquoteSetextReplace2,"");o=o?`${o}
${d}`:d,r=r?`${r}
${p}`:p;let u=this.lexer.state.top;if(this.lexer.state.top=!0,this.lexer.blockTokens(p,i,!0),this.lexer.state.top=u,n.length===0)break;let h=i.at(-1);if(h?.type==="code")break;if(h?.type==="blockquote"){let m=h,f=m.raw+`
`+n.join(`
`),k=this.blockquote(f);i[i.length-1]=k,o=o.substring(0,o.length-m.raw.length)+k.raw,r=r.substring(0,r.length-m.text.length)+k.text;break}else if(h?.type==="list"){let m=h,f=m.raw+`
`+n.join(`
`),k=this.list(f);i[i.length-1]=k,o=o.substring(0,o.length-h.raw.length)+k.raw,r=r.substring(0,r.length-m.raw.length)+k.raw,n=f.substring(i.at(-1).raw.length).split(`
`);continue}}return{type:"blockquote",raw:o,tokens:i,text:r}}}list(e){let t=this.rules.block.list.exec(e);if(t){let n=t[1].trim(),o=n.length>1,r={type:"list",raw:"",ordered:o,start:o?+n.slice(0,-1):"",loose:!1,items:[]};n=o?`\\d{1,9}\\${n.slice(-1)}`:`\\${n}`,this.options.pedantic&&(n=o?n:"[*+-]");let i=this.rules.other.listItemRegex(n),a=!1;for(;e;){let c=!1,d="",p="";if(!(t=i.exec(e))||this.rules.block.hr.test(e))break;d=t[0],e=e.substring(d.length);let u=t[2].split(`
`,1)[0].replace(this.rules.other.listReplaceTabs,g=>" ".repeat(3*g.length)),h=e.split(`
`,1)[0],m=!u.trim(),f=0;if(this.options.pedantic?(f=2,p=u.trimStart()):m?f=t[1].length+1:(f=t[2].search(this.rules.other.nonSpaceChar),f=f>4?1:f,p=u.slice(f),f+=t[1].length),m&&this.rules.other.blankLine.test(h)&&(d+=h+`
`,e=e.substring(h.length+1),c=!0),!c){let g=this.rules.other.nextBulletRegex(f),y=this.rules.other.hrRegex(f),x=this.rules.other.fencesBeginRegex(f),b=this.rules.other.headingBeginRegex(f),v=this.rules.other.htmlBeginRegex(f);for(;e;){let C=e.split(`
`,1)[0],T;if(h=C,this.options.pedantic?(h=h.replace(this.rules.other.listReplaceNesting,"  "),T=h):T=h.replace(this.rules.other.tabCharGlobal,"    "),x.test(h)||b.test(h)||v.test(h)||g.test(h)||y.test(h))break;if(T.search(this.rules.other.nonSpaceChar)>=f||!h.trim())p+=`
`+T.slice(f);else{if(m||u.replace(this.rules.other.tabCharGlobal,"    ").search(this.rules.other.nonSpaceChar)>=4||x.test(u)||b.test(u)||y.test(u))break;p+=`
`+h}!m&&!h.trim()&&(m=!0),d+=C+`
`,e=e.substring(C.length+1),u=T.slice(f)}}r.loose||(a?r.loose=!0:this.rules.other.doubleBlankLine.test(d)&&(a=!0));let k=null,w;this.options.gfm&&(k=this.rules.other.listIsTask.exec(p),k&&(w=k[0]!=="[ ] ",p=p.replace(this.rules.other.listReplaceTask,""))),r.items.push({type:"list_item",raw:d,task:!!k,checked:w,loose:!1,text:p,tokens:[]}),r.raw+=d}let s=r.items.at(-1);if(s)s.raw=s.raw.trimEnd(),s.text=s.text.trimEnd();else return;r.raw=r.raw.trimEnd();for(let c=0;c<r.items.length;c++)if(this.lexer.state.top=!1,r.items[c].tokens=this.lexer.blockTokens(r.items[c].text,[]),!r.loose){let d=r.items[c].tokens.filter(u=>u.type==="space"),p=d.length>0&&d.some(u=>this.rules.other.anyLine.test(u.raw));r.loose=p}if(r.loose)for(let c=0;c<r.items.length;c++)r.items[c].loose=!0;return r}}html(e){let t=this.rules.block.html.exec(e);if(t)return{type:"html",block:!0,raw:t[0],pre:t[1]==="pre"||t[1]==="script"||t[1]==="style",text:t[0]}}def(e){let t=this.rules.block.def.exec(e);if(t){let n=t[1].toLowerCase().replace(this.rules.other.multipleSpaceGlobal," "),o=t[2]?t[2].replace(this.rules.other.hrefBrackets,"$1").replace(this.rules.inline.anyPunctuation,"$1"):"",r=t[3]?t[3].substring(1,t[3].length-1).replace(this.rules.inline.anyPunctuation,"$1"):t[3];return{type:"def",tag:n,raw:t[0],href:o,title:r}}}table(e){let t=this.rules.block.table.exec(e);if(!t||!this.rules.other.tableDelimiter.test(t[2]))return;let n=ur(t[1]),o=t[2].replace(this.rules.other.tableAlignChars,"").split("|"),r=t[3]?.trim()?t[3].replace(this.rules.other.tableRowBlankLine,"").split(`
`):[],i={type:"table",raw:t[0],header:[],align:[],rows:[]};if(n.length===o.length){for(let a of o)this.rules.other.tableAlignRight.test(a)?i.align.push("right"):this.rules.other.tableAlignCenter.test(a)?i.align.push("center"):this.rules.other.tableAlignLeft.test(a)?i.align.push("left"):i.align.push(null);for(let a=0;a<n.length;a++)i.header.push({text:n[a],tokens:this.lexer.inline(n[a]),header:!0,align:i.align[a]});for(let a of r)i.rows.push(ur(a,i.header.length).map((s,c)=>({text:s,tokens:this.lexer.inline(s),header:!1,align:i.align[c]})));return i}}lheading(e){let t=this.rules.block.lheading.exec(e);if(t)return{type:"heading",raw:t[0],depth:t[2].charAt(0)==="="?1:2,text:t[1],tokens:this.lexer.inline(t[1])}}paragraph(e){let t=this.rules.block.paragraph.exec(e);if(t){let n=t[1].charAt(t[1].length-1)===`
`?t[1].slice(0,-1):t[1];return{type:"paragraph",raw:t[0],text:n,tokens:this.lexer.inline(n)}}}text(e){let t=this.rules.block.text.exec(e);if(t)return{type:"text",raw:t[0],text:t[0],tokens:this.lexer.inline(t[0])}}escape(e){let t=this.rules.inline.escape.exec(e);if(t)return{type:"escape",raw:t[0],text:t[1]}}tag(e){let t=this.rules.inline.tag.exec(e);if(t)return!this.lexer.state.inLink&&this.rules.other.startATag.test(t[0])?this.lexer.state.inLink=!0:this.lexer.state.inLink&&this.rules.other.endATag.test(t[0])&&(this.lexer.state.inLink=!1),!this.lexer.state.inRawBlock&&this.rules.other.startPreScriptTag.test(t[0])?this.lexer.state.inRawBlock=!0:this.lexer.state.inRawBlock&&this.rules.other.endPreScriptTag.test(t[0])&&(this.lexer.state.inRawBlock=!1),{type:"html",raw:t[0],inLink:this.lexer.state.inLink,inRawBlock:this.lexer.state.inRawBlock,block:!1,text:t[0]}}link(e){let t=this.rules.inline.link.exec(e);if(t){let n=t[2].trim();if(!this.options.pedantic&&this.rules.other.startAngleBracket.test(n)){if(!this.rules.other.endAngleBracket.test(n))return;let i=ot(n.slice(0,-1),"\\");if((n.length-i.length)%2===0)return}else{let i=Zs(t[2],"()");if(i===-2)return;if(i>-1){let a=(t[0].indexOf("!")===0?5:4)+t[1].length+i;t[2]=t[2].substring(0,i),t[0]=t[0].substring(0,a).trim(),t[3]=""}}let o=t[2],r="";if(this.options.pedantic){let i=this.rules.other.pedanticHrefTitle.exec(o);i&&(o=i[1],r=i[3])}else r=t[3]?t[3].slice(1,-1):"";return o=o.trim(),this.rules.other.startAngleBracket.test(o)&&(this.options.pedantic&&!this.rules.other.endAngleBracket.test(n)?o=o.slice(1):o=o.slice(1,-1)),hr(t,{href:o&&o.replace(this.rules.inline.anyPunctuation,"$1"),title:r&&r.replace(this.rules.inline.anyPunctuation,"$1")},t[0],this.lexer,this.rules)}}reflink(e,t){let n;if((n=this.rules.inline.reflink.exec(e))||(n=this.rules.inline.nolink.exec(e))){let o=(n[2]||n[1]).replace(this.rules.other.multipleSpaceGlobal," "),r=t[o.toLowerCase()];if(!r){let i=n[0].charAt(0);return{type:"text",raw:i,text:i}}return hr(n,r,n[0],this.lexer,this.rules)}}emStrong(e,t,n=""){let o=this.rules.inline.emStrongLDelim.exec(e);if(!(!o||o[3]&&n.match(this.rules.other.unicodeAlphaNumeric))&&(!(o[1]||o[2])||!n||this.rules.inline.punctuation.exec(n))){let r=[...o[0]].length-1,i,a,s=r,c=0,d=o[0][0]==="*"?this.rules.inline.emStrongRDelimAst:this.rules.inline.emStrongRDelimUnd;for(d.lastIndex=0,t=t.slice(-1*e.length+r);(o=d.exec(t))!=null;){if(i=o[1]||o[2]||o[3]||o[4]||o[5]||o[6],!i)continue;if(a=[...i].length,o[3]||o[4]){s+=a;continue}else if((o[5]||o[6])&&r%3&&!((r+a)%3)){c+=a;continue}if(s-=a,s>0)continue;a=Math.min(a,a+s+c);let p=[...o[0]][0].length,u=e.slice(0,r+o.index+p+a);if(Math.min(r,a)%2){let m=u.slice(1,-1);return{type:"em",raw:u,text:m,tokens:this.lexer.inlineTokens(m)}}let h=u.slice(2,-2);return{type:"strong",raw:u,text:h,tokens:this.lexer.inlineTokens(h)}}}}codespan(e){let t=this.rules.inline.code.exec(e);if(t){let n=t[2].replace(this.rules.other.newLineCharGlobal," "),o=this.rules.other.nonSpaceChar.test(n),r=this.rules.other.startingSpaceChar.test(n)&&this.rules.other.endingSpaceChar.test(n);return o&&r&&(n=n.substring(1,n.length-1)),{type:"codespan",raw:t[0],text:n}}}br(e){let t=this.rules.inline.br.exec(e);if(t)return{type:"br",raw:t[0]}}del(e){let t=this.rules.inline.del.exec(e);if(t)return{type:"del",raw:t[0],text:t[2],tokens:this.lexer.inlineTokens(t[2])}}autolink(e){let t=this.rules.inline.autolink.exec(e);if(t){let n,o;return t[2]==="@"?(n=t[1],o="mailto:"+n):(n=t[1],o=n),{type:"link",raw:t[0],text:n,href:o,tokens:[{type:"text",raw:n,text:n}]}}}url(e){let t;if(t=this.rules.inline.url.exec(e)){let n,o;if(t[2]==="@")n=t[0],o="mailto:"+n;else{let r;do r=t[0],t[0]=this.rules.inline._backpedal.exec(t[0])?.[0]??"";while(r!==t[0]);n=t[0],t[1]==="www."?o="http://"+t[0]:o=t[0]}return{type:"link",raw:t[0],text:n,href:o,tokens:[{type:"text",raw:n,text:n}]}}}inlineText(e){let t=this.rules.inline.text.exec(e);if(t){let n=this.lexer.state.inRawBlock;return{type:"text",raw:t[0],text:t[0],escaped:n}}}},ue=class fn{tokens;options;state;tokenizer;inlineQueue;constructor(t){this.tokens=[],this.tokens.links=Object.create(null),this.options=t||Oe,this.options.tokenizer=this.options.tokenizer||new _t,this.tokenizer=this.options.tokenizer,this.tokenizer.options=this.options,this.tokenizer.lexer=this,this.inlineQueue=[],this.state={inLink:!1,inRawBlock:!1,top:!0};let n={other:V,block:vt.normal,inline:rt.normal};this.options.pedantic?(n.block=vt.pedantic,n.inline=rt.pedantic):this.options.gfm&&(n.block=vt.gfm,this.options.breaks?n.inline=rt.breaks:n.inline=rt.gfm),this.tokenizer.rules=n}static get rules(){return{block:vt,inline:rt}}static lex(t,n){return new fn(n).lex(t)}static lexInline(t,n){return new fn(n).inlineTokens(t)}lex(t){t=t.replace(V.carriageReturn,`
`),this.blockTokens(t,this.tokens);for(let n=0;n<this.inlineQueue.length;n++){let o=this.inlineQueue[n];this.inlineTokens(o.src,o.tokens)}return this.inlineQueue=[],this.tokens}blockTokens(t,n=[],o=!1){for(this.options.pedantic&&(t=t.replace(V.tabCharGlobal,"    ").replace(V.spaceLine,""));t;){let r;if(this.options.extensions?.block?.some(a=>(r=a.call({lexer:this},t,n))?(t=t.substring(r.raw.length),n.push(r),!0):!1))continue;if(r=this.tokenizer.space(t)){t=t.substring(r.raw.length);let a=n.at(-1);r.raw.length===1&&a!==void 0?a.raw+=`
`:n.push(r);continue}if(r=this.tokenizer.code(t)){t=t.substring(r.raw.length);let a=n.at(-1);a?.type==="paragraph"||a?.type==="text"?(a.raw+=(a.raw.endsWith(`
`)?"":`
`)+r.raw,a.text+=`
`+r.text,this.inlineQueue.at(-1).src=a.text):n.push(r);continue}if(r=this.tokenizer.fences(t)){t=t.substring(r.raw.length),n.push(r);continue}if(r=this.tokenizer.heading(t)){t=t.substring(r.raw.length),n.push(r);continue}if(r=this.tokenizer.hr(t)){t=t.substring(r.raw.length),n.push(r);continue}if(r=this.tokenizer.blockquote(t)){t=t.substring(r.raw.length),n.push(r);continue}if(r=this.tokenizer.list(t)){t=t.substring(r.raw.length),n.push(r);continue}if(r=this.tokenizer.html(t)){t=t.substring(r.raw.length),n.push(r);continue}if(r=this.tokenizer.def(t)){t=t.substring(r.raw.length);let a=n.at(-1);a?.type==="paragraph"||a?.type==="text"?(a.raw+=(a.raw.endsWith(`
`)?"":`
`)+r.raw,a.text+=`
`+r.raw,this.inlineQueue.at(-1).src=a.text):this.tokens.links[r.tag]||(this.tokens.links[r.tag]={href:r.href,title:r.title},n.push(r));continue}if(r=this.tokenizer.table(t)){t=t.substring(r.raw.length),n.push(r);continue}if(r=this.tokenizer.lheading(t)){t=t.substring(r.raw.length),n.push(r);continue}let i=t;if(this.options.extensions?.startBlock){let a=1/0,s=t.slice(1),c;this.options.extensions.startBlock.forEach(d=>{c=d.call({lexer:this},s),typeof c=="number"&&c>=0&&(a=Math.min(a,c))}),a<1/0&&a>=0&&(i=t.substring(0,a+1))}if(this.state.top&&(r=this.tokenizer.paragraph(i))){let a=n.at(-1);o&&a?.type==="paragraph"?(a.raw+=(a.raw.endsWith(`
`)?"":`
`)+r.raw,a.text+=`
`+r.text,this.inlineQueue.pop(),this.inlineQueue.at(-1).src=a.text):n.push(r),o=i.length!==t.length,t=t.substring(r.raw.length);continue}if(r=this.tokenizer.text(t)){t=t.substring(r.raw.length);let a=n.at(-1);a?.type==="text"?(a.raw+=(a.raw.endsWith(`
`)?"":`
`)+r.raw,a.text+=`
`+r.text,this.inlineQueue.pop(),this.inlineQueue.at(-1).src=a.text):n.push(r);continue}if(t){let a="Infinite loop on byte: "+t.charCodeAt(0);if(this.options.silent){console.error(a);break}else throw new Error(a)}}return this.state.top=!0,n}inline(t,n=[]){return this.inlineQueue.push({src:t,tokens:n}),n}inlineTokens(t,n=[]){let o=t,r=null;if(this.tokens.links){let s=Object.keys(this.tokens.links);if(s.length>0)for(;(r=this.tokenizer.rules.inline.reflinkSearch.exec(o))!=null;)s.includes(r[0].slice(r[0].lastIndexOf("[")+1,-1))&&(o=o.slice(0,r.index)+"["+"a".repeat(r[0].length-2)+"]"+o.slice(this.tokenizer.rules.inline.reflinkSearch.lastIndex))}for(;(r=this.tokenizer.rules.inline.anyPunctuation.exec(o))!=null;)o=o.slice(0,r.index)+"++"+o.slice(this.tokenizer.rules.inline.anyPunctuation.lastIndex);for(;(r=this.tokenizer.rules.inline.blockSkip.exec(o))!=null;)o=o.slice(0,r.index)+"["+"a".repeat(r[0].length-2)+"]"+o.slice(this.tokenizer.rules.inline.blockSkip.lastIndex);let i=!1,a="";for(;t;){i||(a=""),i=!1;let s;if(this.options.extensions?.inline?.some(d=>(s=d.call({lexer:this},t,n))?(t=t.substring(s.raw.length),n.push(s),!0):!1))continue;if(s=this.tokenizer.escape(t)){t=t.substring(s.raw.length),n.push(s);continue}if(s=this.tokenizer.tag(t)){t=t.substring(s.raw.length),n.push(s);continue}if(s=this.tokenizer.link(t)){t=t.substring(s.raw.length),n.push(s);continue}if(s=this.tokenizer.reflink(t,this.tokens.links)){t=t.substring(s.raw.length);let d=n.at(-1);s.type==="text"&&d?.type==="text"?(d.raw+=s.raw,d.text+=s.text):n.push(s);continue}if(s=this.tokenizer.emStrong(t,o,a)){t=t.substring(s.raw.length),n.push(s);continue}if(s=this.tokenizer.codespan(t)){t=t.substring(s.raw.length),n.push(s);continue}if(s=this.tokenizer.br(t)){t=t.substring(s.raw.length),n.push(s);continue}if(s=this.tokenizer.del(t)){t=t.substring(s.raw.length),n.push(s);continue}if(s=this.tokenizer.autolink(t)){t=t.substring(s.raw.length),n.push(s);continue}if(!this.state.inLink&&(s=this.tokenizer.url(t))){t=t.substring(s.raw.length),n.push(s);continue}let c=t;if(this.options.extensions?.startInline){let d=1/0,p=t.slice(1),u;this.options.extensions.startInline.forEach(h=>{u=h.call({lexer:this},p),typeof u=="number"&&u>=0&&(d=Math.min(d,u))}),d<1/0&&d>=0&&(c=t.substring(0,d+1))}if(s=this.tokenizer.inlineText(c)){t=t.substring(s.raw.length),s.raw.slice(-1)!=="_"&&(a=s.raw.slice(-1)),i=!0;let d=n.at(-1);d?.type==="text"?(d.raw+=s.raw,d.text+=s.text):n.push(s);continue}if(t){let d="Infinite loop on byte: "+t.charCodeAt(0);if(this.options.silent){console.error(d);break}else throw new Error(d)}}return n}},Ot=class{options;parser;constructor(e){this.options=e||Oe}space(e){return""}code({text:e,lang:t,escaped:n}){let o=(t||"").match(V.notSpaceStart)?.[0],r=e.replace(V.endingNewline,"")+`
`;return o?'<pre><code class="language-'+ie(o)+'">'+(n?r:ie(r,!0))+`</code></pre>
`:"<pre><code>"+(n?r:ie(r,!0))+`</code></pre>
`}blockquote({tokens:e}){return`<blockquote>
${this.parser.parse(e)}</blockquote>
`}html({text:e}){return e}def(e){return""}heading({tokens:e,depth:t}){return`<h${t}>${this.parser.parseInline(e)}</h${t}>
`}hr(e){return`<hr>
`}list(e){let t=e.ordered,n=e.start,o="";for(let a=0;a<e.items.length;a++){let s=e.items[a];o+=this.listitem(s)}let r=t?"ol":"ul",i=t&&n!==1?' start="'+n+'"':"";return"<"+r+i+`>
`+o+"</"+r+`>
`}listitem(e){let t="";if(e.task){let n=this.checkbox({checked:!!e.checked});e.loose?e.tokens[0]?.type==="paragraph"?(e.tokens[0].text=n+" "+e.tokens[0].text,e.tokens[0].tokens&&e.tokens[0].tokens.length>0&&e.tokens[0].tokens[0].type==="text"&&(e.tokens[0].tokens[0].text=n+" "+ie(e.tokens[0].tokens[0].text),e.tokens[0].tokens[0].escaped=!0)):e.tokens.unshift({type:"text",raw:n+" ",text:n+" ",escaped:!0}):t+=n+" "}return t+=this.parser.parse(e.tokens,!!e.loose),`<li>${t}</li>
`}checkbox({checked:e}){return"<input "+(e?'checked="" ':"")+'disabled="" type="checkbox">'}paragraph({tokens:e}){return`<p>${this.parser.parseInline(e)}</p>
`}table(e){let t="",n="";for(let r=0;r<e.header.length;r++)n+=this.tablecell(e.header[r]);t+=this.tablerow({text:n});let o="";for(let r=0;r<e.rows.length;r++){let i=e.rows[r];n="";for(let a=0;a<i.length;a++)n+=this.tablecell(i[a]);o+=this.tablerow({text:n})}return o&&(o=`<tbody>${o}</tbody>`),`<table>
<thead>
`+t+`</thead>
`+o+`</table>
`}tablerow({text:e}){return`<tr>
${e}</tr>
`}tablecell(e){let t=this.parser.parseInline(e.tokens),n=e.header?"th":"td";return(e.align?`<${n} align="${e.align}">`:`<${n}>`)+t+`</${n}>
`}strong({tokens:e}){return`<strong>${this.parser.parseInline(e)}</strong>`}em({tokens:e}){return`<em>${this.parser.parseInline(e)}</em>`}codespan({text:e}){return`<code>${ie(e,!0)}</code>`}br(e){return"<br>"}del({tokens:e}){return`<del>${this.parser.parseInline(e)}</del>`}link({href:e,title:t,tokens:n}){let o=this.parser.parseInline(n),r=pr(e);if(r===null)return o;e=r;let i='<a href="'+e+'"';return t&&(i+=' title="'+ie(t)+'"'),i+=">"+o+"</a>",i}image({href:e,title:t,text:n,tokens:o}){o&&(n=this.parser.parseInline(o,this.parser.textRenderer));let r=pr(e);if(r===null)return ie(n);e=r;let i=`<img src="${e}" alt="${n}"`;return t&&(i+=` title="${ie(t)}"`),i+=">",i}text(e){return"tokens"in e&&e.tokens?this.parser.parseInline(e.tokens):"escaped"in e&&e.escaped?e.text:ie(e.text)}},Rn=class{strong({text:e}){return e}em({text:e}){return e}codespan({text:e}){return e}del({text:e}){return e}html({text:e}){return e}text({text:e}){return e}link({text:e}){return""+e}image({text:e}){return""+e}br(){return""}},he=class gn{options;renderer;textRenderer;constructor(t){this.options=t||Oe,this.options.renderer=this.options.renderer||new Ot,this.renderer=this.options.renderer,this.renderer.options=this.options,this.renderer.parser=this,this.textRenderer=new Rn}static parse(t,n){return new gn(n).parse(t)}static parseInline(t,n){return new gn(n).parseInline(t)}parse(t,n=!0){let o="";for(let r=0;r<t.length;r++){let i=t[r];if(this.options.extensions?.renderers?.[i.type]){let s=i,c=this.options.extensions.renderers[s.type].call({parser:this},s);if(c!==!1||!["space","hr","heading","code","table","blockquote","list","html","def","paragraph","text"].includes(s.type)){o+=c||"";continue}}let a=i;switch(a.type){case"space":{o+=this.renderer.space(a);continue}case"hr":{o+=this.renderer.hr(a);continue}case"heading":{o+=this.renderer.heading(a);continue}case"code":{o+=this.renderer.code(a);continue}case"table":{o+=this.renderer.table(a);continue}case"blockquote":{o+=this.renderer.blockquote(a);continue}case"list":{o+=this.renderer.list(a);continue}case"html":{o+=this.renderer.html(a);continue}case"def":{o+=this.renderer.def(a);continue}case"paragraph":{o+=this.renderer.paragraph(a);continue}case"text":{let s=a,c=this.renderer.text(s);for(;r+1<t.length&&t[r+1].type==="text";)s=t[++r],c+=`
`+this.renderer.text(s);n?o+=this.renderer.paragraph({type:"paragraph",raw:c,text:c,tokens:[{type:"text",raw:c,text:c,escaped:!0}]}):o+=c;continue}default:{let s='Token with "'+a.type+'" type was not found.';if(this.options.silent)return console.error(s),"";throw new Error(s)}}}return o}parseInline(t,n=this.renderer){let o="";for(let r=0;r<t.length;r++){let i=t[r];if(this.options.extensions?.renderers?.[i.type]){let s=this.options.extensions.renderers[i.type].call({parser:this},i);if(s!==!1||!["escape","html","link","image","strong","em","codespan","br","del","text"].includes(i.type)){o+=s||"";continue}}let a=i;switch(a.type){case"escape":{o+=n.text(a);break}case"html":{o+=n.html(a);break}case"link":{o+=n.link(a);break}case"image":{o+=n.image(a);break}case"strong":{o+=n.strong(a);break}case"em":{o+=n.em(a);break}case"codespan":{o+=n.codespan(a);break}case"br":{o+=n.br(a);break}case"del":{o+=n.del(a);break}case"text":{o+=n.text(a);break}default:{let s='Token with "'+a.type+'" type was not found.';if(this.options.silent)return console.error(s),"";throw new Error(s)}}}return o}},$t=class{options;block;constructor(e){this.options=e||Oe}static passThroughHooks=new Set(["preprocess","postprocess","processAllTokens"]);preprocess(e){return e}postprocess(e){return e}processAllTokens(e){return e}provideLexer(){return this.block?ue.lex:ue.lexInline}provideParser(){return this.block?he.parse:he.parseInline}},el=class{defaults=In();options=this.setOptions;parse=this.parseMarkdown(!0);parseInline=this.parseMarkdown(!1);Parser=he;Renderer=Ot;TextRenderer=Rn;Lexer=ue;Tokenizer=_t;Hooks=$t;constructor(...e){this.use(...e)}walkTokens(e,t){let n=[];for(let o of e)switch(n=n.concat(t.call(this,o)),o.type){case"table":{let r=o;for(let i of r.header)n=n.concat(this.walkTokens(i.tokens,t));for(let i of r.rows)for(let a of i)n=n.concat(this.walkTokens(a.tokens,t));break}case"list":{let r=o;n=n.concat(this.walkTokens(r.items,t));break}default:{let r=o;this.defaults.extensions?.childTokens?.[r.type]?this.defaults.extensions.childTokens[r.type].forEach(i=>{let a=r[i].flat(1/0);n=n.concat(this.walkTokens(a,t))}):r.tokens&&(n=n.concat(this.walkTokens(r.tokens,t)))}}return n}use(...e){let t=this.defaults.extensions||{renderers:{},childTokens:{}};return e.forEach(n=>{let o={...n};if(o.async=this.defaults.async||o.async||!1,n.extensions&&(n.extensions.forEach(r=>{if(!r.name)throw new Error("extension name required");if("renderer"in r){let i=t.renderers[r.name];i?t.renderers[r.name]=function(...a){let s=r.renderer.apply(this,a);return s===!1&&(s=i.apply(this,a)),s}:t.renderers[r.name]=r.renderer}if("tokenizer"in r){if(!r.level||r.level!=="block"&&r.level!=="inline")throw new Error("extension level must be 'block' or 'inline'");let i=t[r.level];i?i.unshift(r.tokenizer):t[r.level]=[r.tokenizer],r.start&&(r.level==="block"?t.startBlock?t.startBlock.push(r.start):t.startBlock=[r.start]:r.level==="inline"&&(t.startInline?t.startInline.push(r.start):t.startInline=[r.start]))}"childTokens"in r&&r.childTokens&&(t.childTokens[r.name]=r.childTokens)}),o.extensions=t),n.renderer){let r=this.defaults.renderer||new Ot(this.defaults);for(let i in n.renderer){if(!(i in r))throw new Error(`renderer '${i}' does not exist`);if(["options","parser"].includes(i))continue;let a=i,s=n.renderer[a],c=r[a];r[a]=(...d)=>{let p=s.apply(r,d);return p===!1&&(p=c.apply(r,d)),p||""}}o.renderer=r}if(n.tokenizer){let r=this.defaults.tokenizer||new _t(this.defaults);for(let i in n.tokenizer){if(!(i in r))throw new Error(`tokenizer '${i}' does not exist`);if(["options","rules","lexer"].includes(i))continue;let a=i,s=n.tokenizer[a],c=r[a];r[a]=(...d)=>{let p=s.apply(r,d);return p===!1&&(p=c.apply(r,d)),p}}o.tokenizer=r}if(n.hooks){let r=this.defaults.hooks||new $t;for(let i in n.hooks){if(!(i in r))throw new Error(`hook '${i}' does not exist`);if(["options","block"].includes(i))continue;let a=i,s=n.hooks[a],c=r[a];$t.passThroughHooks.has(i)?r[a]=d=>{if(this.defaults.async)return Promise.resolve(s.call(r,d)).then(u=>c.call(r,u));let p=s.call(r,d);return c.call(r,p)}:r[a]=(...d)=>{let p=s.apply(r,d);return p===!1&&(p=c.apply(r,d)),p}}o.hooks=r}if(n.walkTokens){let r=this.defaults.walkTokens,i=n.walkTokens;o.walkTokens=function(a){let s=[];return s.push(i.call(this,a)),r&&(s=s.concat(r.call(this,a))),s}}this.defaults={...this.defaults,...o}}),this}setOptions(e){return this.defaults={...this.defaults,...e},this}lexer(e,t){return ue.lex(e,t??this.defaults)}parser(e,t){return he.parse(e,t??this.defaults)}parseMarkdown(e){return(t,n)=>{let o={...n},r={...this.defaults,...o},i=this.onError(!!r.silent,!!r.async);if(this.defaults.async===!0&&o.async===!1)return i(new Error("marked(): The async option was set to true by an extension. Remove async: false from the parse options object to return a Promise."));if(typeof t>"u"||t===null)return i(new Error("marked(): input parameter is undefined or null"));if(typeof t!="string")return i(new Error("marked(): input parameter is of type "+Object.prototype.toString.call(t)+", string expected"));r.hooks&&(r.hooks.options=r,r.hooks.block=e);let a=r.hooks?r.hooks.provideLexer():e?ue.lex:ue.lexInline,s=r.hooks?r.hooks.provideParser():e?he.parse:he.parseInline;if(r.async)return Promise.resolve(r.hooks?r.hooks.preprocess(t):t).then(c=>a(c,r)).then(c=>r.hooks?r.hooks.processAllTokens(c):c).then(c=>r.walkTokens?Promise.all(this.walkTokens(c,r.walkTokens)).then(()=>c):c).then(c=>s(c,r)).then(c=>r.hooks?r.hooks.postprocess(c):c).catch(i);try{r.hooks&&(t=r.hooks.preprocess(t));let c=a(t,r);r.hooks&&(c=r.hooks.processAllTokens(c)),r.walkTokens&&this.walkTokens(c,r.walkTokens);let d=s(c,r);return r.hooks&&(d=r.hooks.postprocess(d)),d}catch(c){return i(c)}}}onError(e,t){return n=>{if(n.message+=`
Please report this to https://github.com/markedjs/marked.`,e){let o="<p>An error occurred:</p><pre>"+ie(n.message+"",!0)+"</pre>";return t?Promise.resolve(o):o}if(t)return Promise.reject(n);throw n}}},Fe=new el;function F(e,t){return Fe.parse(e,t)}F.options=F.setOptions=function(e){return Fe.setOptions(e),F.defaults=Fe.defaults,Zr(F.defaults),F};F.getDefaults=In;F.defaults=Oe;F.use=function(...e){return Fe.use(...e),F.defaults=Fe.defaults,Zr(F.defaults),F};F.walkTokens=function(e,t){return Fe.walkTokens(e,t)};F.parseInline=Fe.parseInline;F.Parser=he;F.parser=he.parse;F.Renderer=Ot;F.TextRenderer=Rn;F.Lexer=ue;F.lexer=ue.lex;F.Tokenizer=_t;F.Hooks=$t;F.parse=F;F.options;F.setOptions;F.use;F.walkTokens;F.parseInline;he.parse;ue.lex;F.setOptions({gfm:!0,breaks:!0});const xn=e=>{const t=typeof e=="string"?e:String(e||"");try{return F.parse(t)}catch{return`<p>${tl(t)}</p>`}},tl=e=>{const t=document.createElement("div");return t.textContent=e,t.innerHTML},nl=(e,t,n,o=2,r=20)=>{let i=0,a=!1;const s=150,c=e.closest(".messages-area"),d=()=>{document.hidden&&!a&&p()};document.addEventListener("visibilitychange",d,{signal:O});const p=()=>{a||(a=!0,clearInterval(u),document.removeEventListener("visibilitychange",d),e.innerHTML=xn(t),n())},u=window.setInterval(()=>{if(i<=t.length){const h=t.substring(0,i);e.innerHTML=xn(h),i+=o,c&&i<=s&&(c.scrollTop=c.scrollHeight)}else p()},r);return u},rl=(e,t,n,o,r,i)=>new Promise(a=>{chrome.storage.local.get(["token"],s=>{const c=s.token;if(!c){a({success:!1,error:"Not authenticated"});return}chrome.runtime.sendMessage({action:"chatQuery",token:c,payload:{query:e,profileId:t==="12345678-1234-1234-1234-123456789abc"?"":t,k:5,chatHistory:n,model:o,enableWebSearch:r,enableUrlExtraction:i}},d=>{chrome.runtime.lastError?a({success:!1,error:chrome.runtime.lastError.message}):a(d||{success:!1,error:"No response"})})})}),ol=()=>{chrome.runtime.sendMessage({action:"cancelChatQuery"}).catch(()=>{})},il=e=>{const t=e.filter(i=>!i.isTyping&&!i.isError),r=(t.length>0&&t[t.length-1].isUser?t.slice(0,-1):t).map(i=>({role:i.isUser?"user":"assistant",content:i.content}));return r.length>lr*2?r.slice(-lr*2):r},$={send:'<svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><line x1="22" y1="2" x2="11" y2="13"/><polygon points="22 2 15 22 11 13 2 9 22 2"/></svg>',stop:'<svg width="14" height="14" viewBox="0 0 24 24" fill="currentColor"><rect x="4" y="4" width="16" height="16" rx="2"/></svg>',close:'<svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><line x1="18" y1="6" x2="6" y2="18"/><line x1="6" y1="6" x2="18" y2="18"/></svg>',chevronDown:'<svg width="10" height="10" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round"><polyline points="6 9 12 15 18 9"/></svg>',scrollDown:'<svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><polyline points="6 9 12 15 18 9"/></svg>',robot:'<svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><rect x="3" y="11" width="18" height="10" rx="2"/><circle cx="12" cy="5" r="2"/><line x1="12" y1="7" x2="12" y2="11"/><circle cx="8" cy="16" r="1" fill="currentColor"/><circle cx="16" cy="16" r="1" fill="currentColor"/></svg>',tools:'<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><line x1="4" y1="21" x2="4" y2="14"/><line x1="4" y1="10" x2="4" y2="3"/><line x1="12" y1="21" x2="12" y2="12"/><line x1="12" y1="8" x2="12" y2="3"/><line x1="20" y1="21" x2="20" y2="16"/><line x1="20" y1="12" x2="20" y2="3"/><line x1="1" y1="14" x2="7" y2="14"/><line x1="9" y1="8" x2="15" y2="8"/><line x1="17" y1="16" x2="23" y2="16"/></svg>',copy:'<svg width="12" height="12" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><rect x="9" y="9" width="13" height="13" rx="2"/><path d="M5 15H4a2 2 0 0 1-2-2V4a2 2 0 0 1 2-2h9a2 2 0 0 1 2 2v1"/></svg>',check:'<svg width="12" height="12" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round"><polyline points="20 6 9 17 4 12"/></svg>',regenerate:'<svg width="12" height="12" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><path d="M1 4v6h6"/><path d="M23 20v-6h-6"/><path d="M20.49 9A9 9 0 0 0 5.64 5.64L1 10m22 4l-4.64 4.36A9 9 0 0 1 3.51 15"/></svg>',newChat:'<svg width="12" height="12" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><line x1="12" y1="5" x2="12" y2="19"/><line x1="5" y1="12" x2="19" y2="12"/></svg>',user:'<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><path d="M20 21v-2a4 4 0 0 0-4-4H8a4 4 0 0 0-4 4v2"/><circle cx="12" cy="7" r="4"/></svg>',sparkle:'<svg width="14" height="14" viewBox="0 0 24 24" fill="currentColor"><path d="M12 2l2.4 7.2L22 12l-7.6 2.8L12 22l-2.4-7.2L2 12l7.6-2.8L12 2z"/></svg>',search:'<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><circle cx="11" cy="11" r="8"/><line x1="21" y1="21" x2="16.65" y2="16.65"/></svg>',globe:'<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><circle cx="12" cy="12" r="10"/><line x1="2" y1="12" x2="22" y2="12"/><path d="M12 2a15.3 15.3 0 0 1 4 10 15.3 15.3 0 0 1-4 10 15.3 15.3 0 0 1-4-10 15.3 15.3 0 0 1 4-10z"/></svg>',link:'<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><path d="M10 13a5 5 0 0 0 7.54.54l3-3a5 5 0 0 0-7.07-7.07l-1.72 1.71"/><path d="M14 11a5 5 0 0 0-7.54-.54l-3 3a5 5 0 0 0 7.07 7.07l1.71-1.71"/></svg>',bucket:'<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><path d="M22 12h-4l-3 9L9 3l-3 9H2"/></svg>',ai:'<svg width="10" height="10" viewBox="0 0 24 24" fill="currentColor"><path d="M12 2l2.4 7.2L22 12l-7.6 2.8L12 22l-2.4-7.2L2 12l7.6-2.8L12 2z"/></svg>',bookmark:'<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M19 21l-7-5-7 5V5a2 2 0 0 1 2-2h10a2 2 0 0 1 2 2z"/></svg>',bookmarkPlus:'<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M19 21l-7-5-7 5V5a2 2 0 0 1 2-2h10a2 2 0 0 1 2 2z"/><line x1="12" y1="7" x2="12" y2="13"/><line x1="9" y1="10" x2="15" y2="10"/></svg>',spinner:'<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5" stroke-linecap="round"><path d="M12 2v4m0 12v4M4.93 4.93l2.83 2.83m8.48 8.48l2.83 2.83M2 12h4m12 0h4M4.93 19.07l2.83-2.83m8.48-8.48l2.83-2.83"/></svg>',expand:'<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M15 3h6v6M9 21H3v-6M21 3l-7 7M3 21l7-7"/></svg>',compress:'<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M8 3v3a2 2 0 0 1-2 2H3M16 3v3a2 2 0 0 0 2 2h3M8 21v-3a2 2 0 0 1-2-2H3M16 21v-3a2 2 0 0 0 2-2h3"/></svg>',filter:'<svg width="12" height="12" viewBox="64 64 896 896" fill="currentColor"><path d="M880.1 154H143.9c-24.5 0-39.8 26.7-27.5 48L349 597.4V838c0 17.7 14.2 32 31.8 32h262.4c17.6 0 31.8-14.3 31.8-32V597.4L907.7 202c12.2-21.3-3.1-48-27.6-48zM603.4 798H420.6V642h182.9v156zm9.6-236.6l-9.5 16.6h-183l-9.5-16.6L212.7 226h598.6L613 561.4z"/></svg>'},al={Google:"G",Anthropic:"A",OpenAI:"O",Mistral:"Mi",DeepSeek:"D",Amazon:"Am",Writer:"W",Qwen:"Q","Moonshot AI":"Mo",MiniMax:"Mm",ZAI:"Z"},co=(e,t,n,o,r,i,a,s,c,d,p,u,h)=>{const m=document.createElement("div");if(m.className=c?"sidebar-container theater-mode":"sidebar-container",c){const{sidebar:f,bucketsContainer:k,threadsContainer:w,bucketFilterDropdown:g,filterTagsContainer:y,theaterFilterDropdownMenu:x,theaterFilterBtn:b}=ll(n,e,p,u,h);m.appendChild(f);const v=document.createElement("div");v.className="theater-main-area";const C=document.createElement("div");C.className="theater-main-content";const{header:T,refs:E}=mr(e,t,n,!0,p,u);C.appendChild(T);const P=document.createElement("div");P.style.cssText="flex: 1; min-height: 0; position: relative; overflow: hidden; display: flex; flex-direction: column;";const I=document.createElement("div");I.className="messages-area",P.appendChild(I);const A=document.createElement("button");A.className="scroll-to-bottom hidden",A.innerHTML=$.scrollDown,A.addEventListener("click",()=>{I.scrollTo({top:I.scrollHeight,behavior:"smooth"})}),P.appendChild(A),I.addEventListener("scroll",()=>{const Y=I.scrollHeight-I.scrollTop-I.clientHeight<100;A.classList.toggle("hidden",Y)}),C.appendChild(P);const{inputArea:N,refs:M}=fr(o,r,i,a,s,d,p,u);return C.appendChild(N),v.appendChild(C),m.appendChild(v),ze(I,M.textarea),m.addEventListener("click",Y=>{const D=Y.target;if(M.modelDropdown.classList.contains("open")){const H=D.closest(".model-badge"),K=D.closest(".model-dropdown");!H&&!K&&(M.modelDropdown.classList.remove("open"),u.onToggleShowAllModels?.(!1))}if(M.toolsDropdown.classList.contains("open")){const H=D.closest(".tools-btn"),K=D.closest(".tools-dropdown");!H&&!K&&M.toolsDropdown.classList.remove("open")}if(x.classList.contains("open")){const H=D.closest(".theater-filter-btn"),K=D.closest(".theater-filter-dropdown-menu");!H&&!K&&(x.classList.remove("open"),x.remove())}}),{container:m,refs:{messagesArea:I,scrollToBottomBtn:A,memoryIndicator:E.memoryIndicator,memorySeparator:E.memorySeparator,memoryThreadTitle:E.memoryThreadTitle,memoryBucketSwitcher:E.memoryBucketSwitcher,memoryNameEl:E.memoryNameEl,bucketsContainer:k,threadsContainer:w,bucketFilterDropdown:g,filterTagsContainer:y,theaterFilterDropdownMenu:x,theaterFilterBtn:b,...E,...M}}}else{const{header:f,refs:k}=mr(e,t,n,!1,p,u);m.appendChild(f);const w=document.createElement("div");w.style.cssText="flex: 1; min-height: 0; position: relative; overflow: hidden; display: flex; flex-direction: column;";const g=document.createElement("div");g.className="messages-area",w.appendChild(g);const y=document.createElement("button");y.className="scroll-to-bottom hidden",y.innerHTML=$.scrollDown,y.addEventListener("click",()=>{g.scrollTo({top:g.scrollHeight,behavior:"smooth"})}),w.appendChild(y),g.addEventListener("scroll",()=>{const v=g.scrollHeight-g.scrollTop-g.clientHeight<100;y.classList.toggle("hidden",v)}),m.appendChild(w);const{inputArea:x,refs:b}=fr(o,r,i,a,s,d,p,u);return m.appendChild(x),ze(g,b.textarea),m.addEventListener("click",v=>{const C=v.target;if(b.modelDropdown.classList.contains("open")){const T=C.closest(".model-badge"),E=C.closest(".model-dropdown");!T&&!E&&(b.modelDropdown.classList.remove("open"),u.onToggleShowAllModels?.(!1))}if(b.toolsDropdown.classList.contains("open")){const T=C.closest(".tools-btn"),E=C.closest(".tools-dropdown");!T&&!E&&b.toolsDropdown.classList.remove("open")}}),{container:m,refs:{messagesArea:g,scrollToBottomBtn:y,...k,...b}}}};function mr(e,t,n,o,r,i){const a=document.createElement("div");a.className="sidebar-header";const s=document.createElement("div");s.className="header-top-row";let c,d,p,u,h,m;if(o){c=document.createElement("div"),c.className="memory-indicator",c.style.cssText=`
      display: flex;
      align-items: center;
      gap: 8px;
      padding: 10px 0;
      font-size: 14px;
      margin-right: 8px;
    `;const A=!t||t==="Unknown"?"Knowledge Base":t,N=document.createElement("span");N.style.cssText="font-size: 16px;",N.textContent="🗂️",m=document.createElement("span"),m.style.cssText=`
      color: ${r.textPrimary};
      font-weight: 700;
      font-size: 15px;
      overflow: hidden;
      text-overflow: ellipsis;
      white-space: nowrap;
    `,m.textContent=A,u=document.createElement("div"),u.className="memory-bucket-switcher",u.style.cssText=`
      position: relative;
      display: flex;
      align-items: center;
    `;const M=document.createElement("button");M.className="memory-bucket-switch-btn",M.title="Switch memory bucket",M.setAttribute("data-open","false"),M.style.cssText=`
      display: flex;
      align-items: center;
      gap: 4px;
      background: transparent;
      border: none;
      cursor: pointer;
      padding: 4px 8px;
      border-radius: 6px;
      color: ${r.textMuted};
      transition: all 0.15s ease;
    `,M.innerHTML='<svg width="12" height="12" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><path d="M6 9l6 6 6-6"></path></svg>',h=document.createElement("div"),h.className="memory-bucket-dropdown",h.style.cssText=`
      position: absolute;
      top: 100%;
      left: -100px;
      margin-top: 8px;
      background: ${r.background};
      border: 1px solid ${r.border};
      border-radius: 12px;
      box-shadow: 0 8px 32px rgba(0, 0, 0, 0.15), 0 2px 8px rgba(0, 0, 0, 0.1);
      min-width: 280px;
      max-height: 320px;
      overflow-y: auto;
      z-index: 10000;
      padding: 8px;
      display: none;
    `,(()=>{h.innerHTML="";const D=document.createElement("button"),H=e==="12345678-1234-1234-1234-123456789abc";D.style.cssText=`
        display: flex;
        align-items: center;
        gap: 10px;
        width: 100%;
        padding: 10px 12px;
        background: ${H?r.backgroundSelected:r.background};
        border: none;
        border-radius: 8px;
        cursor: pointer;
        text-align: left;
        transition: all 0.15s ease;
        font-family: inherit;
      `;const K=document.createElement("span");K.style.cssText=`
        font-size: 18px;
        width: 28px;
        height: 28px;
        display: flex;
        align-items: center;
        justify-content: center;
        background: ${r.backgroundSecondary};
        border-radius: 6px;
      `,K.textContent="💬";const Le=document.createElement("div");Le.style.cssText="flex: 1; min-width: 0;";const Me=document.createElement("div");Me.style.cssText=`font-size: 13px; font-weight: 600; color: ${r.textPrimary};`,Me.textContent="Knowledge Base";const ce=document.createElement("div");if(ce.style.cssText=`font-size: 11px; color: ${r.textMuted}; margin-top: 2px;`,ce.textContent="Chat with all your knowledge base",Le.appendChild(Me),Le.appendChild(ce),D.appendChild(K),D.appendChild(Le),H){const te=document.createElement("span");te.style.cssText=`color: ${r.primary}; display: flex; align-items: center;`,te.innerHTML='<svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5"><polyline points="20 6 9 17 4 12"></polyline></svg>',D.appendChild(te)}D.addEventListener("mouseenter",()=>{H||(D.style.background=r.backgroundHover)}),D.addEventListener("mouseleave",()=>{D.style.background=H?r.backgroundSelected:r.background}),D.addEventListener("click",()=>{h.style.display="none",M.setAttribute("data-open","false"),i.onBucketChange("12345678-1234-1234-1234-123456789abc","Knowledge Base"),i.onNewChat()}),h.appendChild(D),n.filter(te=>te.id!=="12345678-1234-1234-1234-123456789abc"&&te.profileName!=="Improve Prompt").forEach(te=>{const oe=document.createElement("button"),wt=te.id===e;oe.style.cssText=`
          display: flex;
          align-items: center;
          gap: 10px;
          width: 100%;
          padding: 10px 12px;
          background: ${wt?r.backgroundSelected:r.background};
          border: none;
          border-radius: 8px;
          cursor: pointer;
          text-align: left;
          transition: all 0.15s ease;
          font-family: inherit;
        `;const Vt=document.createElement("span");Vt.style.cssText=`
          font-size: 18px;
          width: 28px;
          height: 28px;
          display: flex;
          align-items: center;
          justify-content: center;
          background: ${r.backgroundSecondary};
          border-radius: 6px;
        `,Vt.textContent="🗂️";const Qt=document.createElement("div");Qt.style.cssText="flex: 1; min-width: 0;";const Zt=document.createElement("div");if(Zt.style.cssText=`font-size: 13px; font-weight: 600; color: ${r.textPrimary}; overflow: hidden; text-overflow: ellipsis; white-space: nowrap;`,Zt.textContent=te.profileName,Qt.appendChild(Zt),oe.appendChild(Vt),oe.appendChild(Qt),wt){const Jt=document.createElement("span");Jt.style.cssText=`color: ${r.primary}; display: flex; align-items: center;`,Jt.innerHTML='<svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5"><polyline points="20 6 9 17 4 12"></polyline></svg>',oe.appendChild(Jt)}oe.addEventListener("mouseenter",()=>{wt||(oe.style.background=r.backgroundHover)}),oe.addEventListener("mouseleave",()=>{oe.style.background=wt?r.backgroundSelected:r.background}),oe.addEventListener("click",()=>{h.style.display="none",M.setAttribute("data-open","false"),i.onBucketChange(te.id,te.profileName),i.onNewChat()}),h.appendChild(oe)})})(),M.addEventListener("click",D=>{D.stopPropagation();const H=h.style.display==="block";h.style.display=H?"none":"block",M.setAttribute("data-open",H?"false":"true"),M.querySelector("svg").style.transform=H?"rotate(0deg)":"rotate(180deg)"}),document.addEventListener("click",D=>{u.contains(D.target)||(h.style.display="none",M.setAttribute("data-open","false"),M.querySelector("svg").style.transform="rotate(0deg)")},{signal:O}),M.addEventListener("mouseenter",()=>{M.style.background=r.backgroundHover}),M.addEventListener("mouseleave",()=>{M.style.background="transparent"}),u.appendChild(M),u.appendChild(h),d=document.createElement("span"),d.style.cssText=`
      color: ${r.textMuted};
      font-size: 12px;
      margin: 0 8px;
      opacity: 0.5;
      display: none;
    `,d.textContent="›",p=document.createElement("span"),p.style.cssText=`
      color: ${r.textSecondary};
      font-weight: 600;
      font-size: 14px;
      overflow: hidden;
      text-overflow: ellipsis;
      white-space: nowrap;
      max-width: 250px;
      display: none;
    `,c.appendChild(N),c.appendChild(m),c.appendChild(u),c.appendChild(d),c.appendChild(p),s.appendChild(c)}if(!o){const A=document.createElement("div");A.style.cssText="display: flex; align-items: center; gap: 12px; cursor: pointer; transition: opacity 0.2s ease;",A.addEventListener("mouseenter",()=>{A.style.opacity="0.8"}),A.addEventListener("mouseleave",()=>{A.style.opacity="1"}),A.addEventListener("click",()=>{window.open("https://plurality.network/ai-context-flow/","_blank")});const N=document.createElement("div");N.className="sidebar-logo";try{const H=document.createElement("img");H.src=_e(),H.alt="Plurality",N.appendChild(H)}catch{N.textContent="P",N.style.color="white",N.style.fontWeight="700",N.style.fontSize="14px"}A.appendChild(N);const M=document.createElement("div");M.style.cssText="display: flex; flex-direction: column; gap: 1px;";const Y=document.createElement("div");Y.className="sidebar-title",Y.textContent="AI Context Flow",M.appendChild(Y);const D=document.createElement("div");D.className="sidebar-subtitle",D.textContent="by Plurality",M.appendChild(D),A.appendChild(M),s.appendChild(A)}const f=document.createElement("div");f.style.flex="1",s.appendChild(f);let k,w;if(o){k=document.createElement("button"),k.className="chat-action-btn save-btn",k.innerHTML=$.bookmark;const A=e==="12345678-1234-1234-1234-123456789abc";k.disabled=A,k.title=A?"Select a memory bucket to save":e?"Save Chat to Memory Bucket":"Save Chat as New Memory Bucket",k.setAttribute("data-has-bucket",e?"true":"false"),k.addEventListener("click",i.onSave),s.appendChild(k),w=document.createElement("button"),w.className="chat-action-btn fork-btn",w.innerHTML=$.bookmarkPlus,w.title="Save Chat as New Memory Bucket",w.addEventListener("click",i.onSaveAsNew),s.appendChild(w)}const g=document.createElement("button");g.className="theater-btn",g.innerHTML=o?$.compress:$.expand,g.title=o?"Side Bar":"Wide Screen",g.addEventListener("click",i.onTheaterToggle),s.appendChild(g);const y=document.createElement("button");y.className="close-btn",y.innerHTML=$.close,y.title="Close sidebar",y.addEventListener("click",i.onClose),s.appendChild(y),a.appendChild(s);let x,b,v,C,T,E,P,I;if(o)x=document.createElement("button"),b=document.createElement("div"),v=document.createElement("span"),C=document.createElement("span"),T=document.createElement("button"),E=document.createElement("div"),P=document.createElement("span"),I=document.createElement("span");else{const A=document.createElement("div");A.className="sidebar-info-text",A.textContent="Chat Using Your Selected Memory",a.appendChild(A);const N=document.createElement("div");N.className="header-bottom-row";const M=document.createElement("div");M.className="bucket-selector",M.style.flex="1",x=document.createElement("button"),x.className="bucket-selector-btn",v=document.createElement("span"),v.className="bucket-name",v.textContent=t,C=document.createElement("span"),C.className="chevron",C.innerHTML=$.chevronDown,x.appendChild(v),x.appendChild(C),b=document.createElement("div"),b.className="bucket-dropdown",po(b,n,e,v,C,r,i),x.addEventListener("click",Me=>{Me.stopPropagation();const ce=b.classList.contains("open");b.classList.toggle("open",!ce),C.classList.toggle("open",!ce)}),M.appendChild(x),M.appendChild(b),N.appendChild(M),a.appendChild(N);const Y=document.createElement("div");Y.className="sidebar-info-text",Y.textContent="Switch Between Threads",a.appendChild(Y);const D=document.createElement("div");D.className="header-bottom-row";const H=document.createElement("div");H.className="bucket-selector",H.style.flex="1",T=document.createElement("button"),T.className="bucket-selector-btn",P=document.createElement("span"),P.className="bucket-name",P.textContent="New Chat",I=document.createElement("span"),I.className="chevron",I.innerHTML=$.chevronDown,T.appendChild(P),T.appendChild(I),E=document.createElement("div"),E.className="bucket-dropdown",T.addEventListener("click",Me=>{Me.stopPropagation();const ce=E.classList.contains("open");E.classList.toggle("open",!ce),I.classList.toggle("open",!ce)}),H.appendChild(T),H.appendChild(E),D.appendChild(H);const K=document.createElement("button");K.className="chat-action-btn new-chat-action-btn",K.innerHTML=$.newChat,K.title="Start new chat",K.addEventListener("click",i.onNewChat),D.appendChild(K),k=document.createElement("button"),k.className="chat-action-btn save-btn",k.innerHTML=$.bookmark;const Le=e==="12345678-1234-1234-1234-123456789abc";k.disabled=Le,k.title=Le?"Select a memory bucket to save":e?"Save Chat to Memory Bucket":"Save Chat as New Memory Bucket",k.setAttribute("data-has-bucket",e?"true":"false"),k.addEventListener("click",i.onSave),D.appendChild(k),w=document.createElement("button"),w.className="chat-action-btn fork-btn",w.innerHTML=$.bookmarkPlus,w.title="Save Chat as New Memory Bucket",w.addEventListener("click",i.onSaveAsNew),D.appendChild(w),a.appendChild(D)}return{header:a,refs:{bucketBtn:x,bucketDropdown:b,bucketNameEl:v,chevronEl:C,threadBtn:T,threadDropdown:E,threadNameEl:P,threadChevronEl:I,saveBtn:k,forkBtn:w,theaterBtn:g,memoryIndicator:c,memorySeparator:d,memoryThreadTitle:p,memoryBucketSwitcher:u,memoryNameEl:m}}}function sl(e,t,n,o){const r=document.createElement("div");r.className="bucket-modal-backdrop",r.style.cssText=`
    position: fixed;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background: rgba(0, 0, 0, 0.5);
    z-index: 10000;
    display: flex;
    align-items: center;
    justify-content: center;
  `;const i=document.createElement("div");i.className="bucket-modal",i.style.cssText=`
    background: ${t.background};
    border-radius: 16px;
    width: 100%;
    max-width: 380px;
    box-shadow: 0 20px 60px rgba(0, 0, 0, 0.5);
    border: 1px solid ${t.border};
    overflow: hidden;
    font-family: 'Lexend', -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif;
  `;const a=document.createElement("div");a.style.cssText=`
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 16px 20px;
    border-bottom: 1px solid ${t.border};
  `;const s=document.createElement("span");s.style.cssText=`
    font-size: 16px;
    font-weight: 600;
    color: ${t.textPrimary};
  `,s.textContent="Chat Using Your Selected Memory";const c=document.createElement("button");c.style.cssText=`
    width: 28px;
    height: 28px;
    border-radius: 6px;
    border: none;
    background: transparent;
    color: ${t.textMuted};
    cursor: pointer;
    display: flex;
    align-items: center;
    justify-content: center;
    transition: background 0.2s ease;
  `,c.innerHTML=$.close,c.addEventListener("click",()=>r.remove()),c.addEventListener("mouseenter",()=>{c.style.background=t.backgroundHover}),c.addEventListener("mouseleave",()=>{c.style.background="transparent"}),a.appendChild(s),a.appendChild(c),i.appendChild(a);const d=document.createElement("div");d.style.cssText=`
    padding: 16px 20px;
  `;const p=document.createElement("div");p.style.cssText=`
    display: flex;
    align-items: center;
    gap: 10px;
    padding: 10px 14px;
    border-radius: 10px;
    border: 1px solid ${t.primary};
    background: ${t.backgroundSecondary};
  `;const u=document.createElement("span");u.style.cssText=`
    font-size: 16px;
    color: ${t.textMuted};
    display: flex;
    align-items: center;
  `,u.innerHTML=$.search;const h=document.createElement("input");h.type="text",h.placeholder="Type to filter buckets...",h.style.cssText=`
    flex: 1;
    border: none;
    background: transparent;
    color: ${t.textPrimary};
    font-size: 14px;
    outline: none;
    font-family: 'Lexend', -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif;
  `,p.appendChild(u),p.appendChild(h),d.appendChild(p),i.appendChild(d);const m=document.createElement("div");m.style.cssText=`
    max-height: 240px;
    overflow-y: auto;
    border-top: 1px solid ${t.border};
  `;const f=(y="")=>{m.innerHTML="";const x=e.filter(E=>E.profileName!=="Improve Prompt"&&E.profileName.toLowerCase().includes(y.toLowerCase())),b="Knowledge Base",v=!y||b.toLowerCase().includes(y.toLowerCase()),C=(v?1:0)+x.length;let T=0;if(v){const E=document.createElement("button");E.style.cssText=`
        display: flex;
        align-items: center;
        width: 100%;
        padding: 12px 20px;
        border: none;
        border-bottom: ${T===C-1?"none":`1px solid ${t.border}`};
        background: transparent;
        cursor: pointer;
        text-align: left;
        transition: background 0.15s;
        font-family: inherit;
      `;const P=document.createElement("span");P.style.cssText=`
        font-size: 18px;
        margin-right: 12px;
      `,P.textContent="💬";const I=document.createElement("div");I.style.cssText=`
        flex: 1;
      `;const A=document.createElement("div");A.style.cssText=`
        font-size: 13px;
        font-weight: 600;
        color: ${t.textPrimary};
      `,A.textContent=b;const N=document.createElement("div");N.style.cssText=`
        font-size: 11px;
        color: ${t.textMuted};
        margin-top: 2px;
      `,N.textContent="Chat with all your knowledge base",I.appendChild(A),I.appendChild(N),E.appendChild(P),E.appendChild(I),E.addEventListener("mouseenter",()=>{E.style.background=t.backgroundHover}),E.addEventListener("mouseleave",()=>{E.style.background="transparent"}),E.addEventListener("click",()=>{n.onBucketChange("12345678-1234-1234-1234-123456789abc","Knowledge Base"),n.onNewChat(),r.remove()}),m.appendChild(E),T++}x.forEach(E=>{const P=document.createElement("button");P.style.cssText=`
        display: flex;
        align-items: center;
        width: 100%;
        padding: 12px 20px;
        border: none;
        border-bottom: ${T===C-1?"none":`1px solid ${t.border}`};
        background: transparent;
        cursor: pointer;
        text-align: left;
        transition: background 0.15s;
        font-family: inherit;
      `;const I=document.createElement("span");I.style.cssText=`
        font-size: 18px;
        margin-right: 12px;
      `,I.textContent="🗂️";const A=document.createElement("div");A.style.cssText=`
        flex: 1;
      `;const N=document.createElement("div");N.style.cssText=`
        font-size: 13px;
        font-weight: 600;
        color: ${t.textPrimary};
      `,N.textContent=E.profileName;const M=document.createElement("div");M.style.cssText=`
        font-size: 11px;
        color: ${t.textMuted};
        margin-top: 2px;
      `;const Y=E.contextCount||0;M.textContent=`${Y} ${Y===1?"item":"items"}`,A.appendChild(N),A.appendChild(M),P.appendChild(I),P.appendChild(A),P.addEventListener("mouseenter",()=>{P.style.background=t.backgroundHover}),P.addEventListener("mouseleave",()=>{P.style.background="transparent"}),P.addEventListener("click",()=>{n.onBucketChange(E.id,E.profileName),n.onNewChat(),r.remove()}),m.appendChild(P),T++})};f(),h.addEventListener("input",y=>{f(y.target.value)}),i.appendChild(m);const k=document.createElement("div");k.style.cssText=`
    padding: 12px 20px;
    border-top: 1px solid ${t.border};
    text-align: center;
  `;const w=document.createElement("button");w.style.cssText=`
    padding: 8px 16px;
    border-radius: 8px;
    border: none;
    background: transparent;
    color: ${t.primary};
    font-size: 12px;
    font-weight: 500;
    cursor: pointer;
    transition: background 0.2s ease;
    font-family: 'Lexend', -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif;
  `,w.textContent="Open in Memory Studio for full search →",w.addEventListener("click",()=>{chrome.runtime.sendMessage({action:"openDashboard"}),r.remove()}),w.addEventListener("mouseenter",()=>{w.style.background=t.primary+"10"}),w.addEventListener("mouseleave",()=>{w.style.background="transparent"}),k.appendChild(w),i.appendChild(k),r.addEventListener("click",y=>{y.target===r&&r.remove()});const g=y=>{y.key==="Escape"&&(r.remove(),document.removeEventListener("keydown",g))};document.addEventListener("keydown",g,{signal:O}),r.appendChild(i),o?o.appendChild(r):document.body.appendChild(r),setTimeout(()=>h.focus(),100)}function xe(e,t,n,o,r){e.innerHTML="";const i=o.length===0,a=document.createElement("div");a.className="theater-filter-dropdown-item"+(i?" selected":"");const s=document.createElement("span");s.className="filter-icon",s.innerHTML=$.ai;const c=document.createElement("span");if(c.style.cssText="flex: 1;",c.textContent="All Memory Buckets",a.appendChild(s),a.appendChild(c),i){const f=document.createElement("span");f.className="filter-checkmark",f.innerHTML=$.check,a.appendChild(f)}a.addEventListener("click",f=>{f.stopPropagation(),f.preventDefault(),r("all")}),e.appendChild(a);const d=document.createElement("div");d.style.cssText="height: 1px; background: var(--border); margin: 4px 0;",e.appendChild(d);const p=document.createElement("div"),u=o.includes("12345678-1234-1234-1234-123456789abc");p.className="theater-filter-dropdown-item"+(u?" selected":"");const h=document.createElement("span");h.className="filter-icon",h.innerHTML=$.ai;const m=document.createElement("span");if(m.style.cssText="flex: 1;",m.textContent="Knowledge Base",p.appendChild(h),p.appendChild(m),u){const f=document.createElement("span");f.className="filter-checkmark",f.innerHTML=$.check,p.appendChild(f)}p.addEventListener("click",f=>{f.stopPropagation(),f.preventDefault(),r("12345678-1234-1234-1234-123456789abc")}),e.appendChild(p),t.filter(f=>f.profileName!=="Improve Prompt").forEach(f=>{const k=document.createElement("div"),w=o.includes(f.id);k.className="theater-filter-dropdown-item"+(w?" selected":"");const g=document.createElement("span");g.className="filter-icon",g.innerHTML=$.ai;const y=document.createElement("span");if(y.style.cssText="flex: 1;",y.textContent=f.profileName,k.appendChild(g),k.appendChild(y),w){const x=document.createElement("span");x.className="filter-checkmark",x.innerHTML=$.check,k.appendChild(x)}k.addEventListener("click",x=>{x.stopPropagation(),x.preventDefault(),r(f.id)}),e.appendChild(k)})}function ll(e,t,n,o,r){const i=document.createElement("div");i.className="theater-nav-sidebar";const a=document.createElement("div");a.style.cssText="padding: 16px 12px 7px 12px; display: flex; align-items: center; gap: 10px; cursor: pointer; transition: opacity 0.2s ease;",a.addEventListener("mouseenter",()=>{a.style.opacity="0.8"}),a.addEventListener("mouseleave",()=>{a.style.opacity="1"}),a.addEventListener("click",()=>{window.open("https://plurality.network/ai-context-flow/","_blank")});const s=document.createElement("div");s.className="sidebar-logo",s.style.cssText=`
    width: 32px;
    height: 32px;
    border-radius: 8px;
    display: flex;
    align-items: center;
    justify-content: center;
    overflow: hidden;
    flex-shrink: 0;
  `;try{const E=document.createElement("img");E.src=_e(),E.alt="Plurality",E.style.cssText="width: 100%; height: 100%; object-fit: contain;",s.appendChild(E)}catch{s.textContent="P",s.style.color=n.textPrimary,s.style.fontWeight="700",s.style.fontSize="16px"}a.appendChild(s);const c=document.createElement("div");c.style.cssText="display: flex; flex-direction: column; gap: 1px; flex: 1; min-width: 0;";const d=document.createElement("div");d.style.cssText=`
    font-size: 16px;
    font-weight: 700;
    color: ${n.textPrimary};
    letter-spacing: -0.3px;
    line-height: 1.2;
  `,d.textContent="AI Context Flow",c.appendChild(d);const p=document.createElement("div");p.style.cssText=`
    font-size: 11px;
    color: ${n.textMuted};
    letter-spacing: 0.2px;
    line-height: 1.2;
  `,p.textContent="by Plurality",c.appendChild(p),a.appendChild(c),i.appendChild(a);const u=document.createElement("div");u.className="theater-nav-divider",u.style.cssText="margin-bottom: 8px;",i.appendChild(u);const h=document.createElement("button");h.className="theater-new-chat-btn",h.innerHTML=`${$.newChat} <span>New Chat</span>`,h.addEventListener("click",async()=>{const E=await o.onLoadBuckets();sl(E,n,o,r)}),i.appendChild(h);const m=document.createElement("div");m.className="theater-nav-divider",i.appendChild(m);const f=document.createElement("div");f.className="theater-conversations-section";const k=document.createElement("div");k.style.cssText="display: flex; align-items: center; justify-content: space-between; padding: 8px 12px;";const w=document.createElement("div");w.className="theater-nav-section-title",w.style.cssText="margin: 0; padding: 0;",w.textContent="Conversations",k.appendChild(w);const g=document.createElement("div");g.className="theater-filter-dropdown-container",g.style.cssText="position: relative;";const y=document.createElement("button");y.className="theater-filter-btn",y.innerHTML=`${$.filter}<span class="filter-count"></span>`,g.appendChild(y);const x=document.createElement("div");x.className="theater-filter-dropdown-menu";const b=r||document.body;y.addEventListener("click",async E=>{if(E.stopPropagation(),x.classList.contains("open"))x.classList.remove("open"),x.remove();else{g.__rebuildDropdown&&await g.__rebuildDropdown(),x.classList.add("open"),b.appendChild(x);const I=y.getBoundingClientRect(),A=300,N=window.innerHeight,M=N-I.bottom,Y=I.top,D=M<A&&Y>M;if(r){const H=r.host.getBoundingClientRect();x.style.position="absolute",D?(x.style.bottom=`${H.bottom-I.top+4}px`,x.style.top="auto"):(x.style.top=`${I.bottom-H.top+4}px`,x.style.bottom="auto"),x.style.left=`${I.left-H.left}px`}else x.style.position="fixed",D?(x.style.bottom=`${N-I.top+4}px`,x.style.top="auto"):(x.style.top=`${I.bottom+4}px`,x.style.bottom="auto"),x.style.left=`${I.left}px`;x.style.width=`${Math.max(I.width,180)}px`}}),xe(x,e,y,[],E=>{const P=new CustomEvent("filterchange",{detail:{bucketId:E}});g.dispatchEvent(P)}),k.appendChild(g),f.appendChild(k);const v=document.createElement("div");v.className="theater-threads-list",f.appendChild(v),i.appendChild(f);const C=document.createElement("div"),T=document.createElement("div");return{sidebar:i,bucketsContainer:C,threadsContainer:v,bucketFilterDropdown:g,filterTagsContainer:T,theaterFilterDropdownMenu:x,theaterFilterBtn:y}}function cl(e,t,n,o,r){if(e.innerHTML="",t.length===0){const i=document.createElement("div");i.style.cssText=`
      padding: 16px 12px;
      text-align: center;
      font-size: 12px;
      color: ${o.textMuted};
    `,i.textContent="No conversations yet",e.appendChild(i);return}t.forEach(i=>{const a=document.createElement("div");a.className="theater-thread-item",i.id===n&&a.classList.add("selected");const s=document.createElement("div");s.className="theater-thread-icon",s.innerHTML=$.ai,a.appendChild(s);const c=document.createElement("div");c.className="theater-thread-content";const d=document.createElement("div");d.className="theater-thread-title",d.textContent=i.title,c.appendChild(d);const p=document.createElement("span");p.className="theater-thread-tag",p.style.cssText=`
      font-size: 9px;
      padding: 1px 4px;
      background: ${o.primary}20;
      color: ${o.primary};
      border-radius: 3px;
      font-weight: 500;
      white-space: nowrap;
      display: inline-block;
      margin-top: 3px;
    `,p.textContent=i.bucketName||"Knowledge Base",c.appendChild(p);const u=document.createElement("div");u.className="theater-thread-date",u.textContent=pl(i.updatedAt),c.appendChild(u),a.appendChild(c),a.addEventListener("click",()=>{r(i.id)}),e.appendChild(a)})}function dl(e,t,n,o,r){if(e.innerHTML="",t.length===0){e.style.minHeight="0";return}e.style.minHeight="28px",t.forEach(i=>{let a="";i==="12345678-1234-1234-1234-123456789abc"?a="Knowledge Base":a=n.find(u=>u.id===i)?.profileName||"Unknown";const s=document.createElement("div");s.style.cssText=`
      display: inline-flex;
      align-items: center;
      gap: 6px;
      padding: 4px 8px 4px 10px;
      background: ${o.backgroundSelected};
      border: 1px solid ${o.border};
      border-radius: 6px;
      font-size: 11px;
      color: ${o.textPrimary};
      font-weight: 500;
    `;const c=document.createElement("span");c.textContent=a,s.appendChild(c);const d=document.createElement("button");d.innerHTML="×",d.style.cssText=`
      background: none;
      border: none;
      color: ${o.textMuted};
      font-size: 16px;
      line-height: 1;
      cursor: pointer;
      padding: 0;
      width: 16px;
      height: 16px;
      display: flex;
      align-items: center;
      justify-content: center;
      transition: color 0.2s ease;
    `,d.addEventListener("mouseenter",()=>{d.style.color=o.textPrimary}),d.addEventListener("mouseleave",()=>{d.style.color=o.textMuted}),d.addEventListener("click",p=>{p.stopPropagation(),r(i)}),s.appendChild(d),e.appendChild(s)})}function pl(e){const t=new Date(e),o=new Date().getTime()-t.getTime(),r=Math.floor(o/(1e3*60*60*24));return r===0?"Today":r===1?"Yesterday":r<7?`${r}d ago`:r<30?`${Math.floor(r/7)}w ago`:t.toLocaleDateString("en-US",{month:"short",day:"numeric"})}function po(e,t,n,o,r,i,a){e.innerHTML="";const s=document.createElement("div");s.className="dropdown-search-container";const c=document.createElement("input");c.type="text",c.className="dropdown-search-input",c.placeholder="Search memories...";const d=document.createElement("div");d.className="dropdown-search-icon",d.innerHTML=$.search,s.appendChild(d),s.appendChild(c),e.appendChild(s);const p=document.createElement("div");p.className="dropdown-items-container";const u=document.createElement("div");u.className=`bucket-dropdown-item${n==="12345678-1234-1234-1234-123456789abc"?" selected":""}`,u.setAttribute("data-bucket-id","12345678-1234-1234-1234-123456789abc"),u.setAttribute("data-searchable","no memory simple chat");const h=document.createElement("div");h.className="item-icon",h.innerHTML=$.sparkle;const m=document.createElement("div");m.className="item-details";const f=document.createElement("span");f.className="item-name",f.textContent="Knowledge Base";const k=document.createElement("span");k.className="item-count",k.textContent="Chat with all your knowledge base",m.appendChild(f),m.appendChild(k),u.appendChild(h),u.appendChild(m),u.addEventListener("click",()=>{e.querySelectorAll(".bucket-dropdown-item").forEach(b=>b.classList.remove("selected")),u.classList.add("selected"),o.textContent="Knowledge Base",e.classList.remove("open"),r.classList.remove("open"),a.onBucketChange("12345678-1234-1234-1234-123456789abc","Knowledge Base")}),p.appendChild(u);const w=document.createElement("div");w.className="dropdown-divider",w.style.cssText=`
    height: 1px;
    background-color: ${i.border};
    margin: 8px 0;
  `,p.appendChild(w);const g=document.createElement("div");g.className="dropdown-section-header",g.style.cssText=`
    padding: 8px 12px;
    font-size: 10px;
    font-weight: 700;
    text-transform: uppercase;
    letter-spacing: 0.5px;
    color: ${i.textMuted};
  `,g.textContent="Select Memory Bucket",p.appendChild(g);const y=t.filter(b=>b.id!=="12345678-1234-1234-1234-123456789abc");if(y.length===0){const b=document.createElement("div");b.className="bucket-dropdown-loading",b.style.cssText=`
      display: flex;
      align-items: center;
      gap: 10px;
      padding: 12px;
      color: ${i.textMuted};
      font-size: 12px;
    `,b.innerHTML=`
      <div style="width: 16px; height: 16px; border: 2px solid ${i.border}; border-top-color: ${i.primary}; border-radius: 50%; animation: spin 1s linear infinite;"></div>
      <span>Loading memory buckets...</span>
    `,p.appendChild(b)}y.forEach(b=>{const v=document.createElement("div");v.className=`bucket-dropdown-item${b.id===n?" selected":""}`,v.setAttribute("data-bucket-id",b.id),v.setAttribute("data-searchable",b.profileName.toLowerCase());const C=document.createElement("div");C.className="item-icon",C.innerHTML=$.bucket;const T=document.createElement("div");T.className="item-details";const E=document.createElement("span");E.className="item-name",E.textContent=b.profileName;const P=document.createElement("span");P.className="item-count",P.textContent=`${b.contextCount} memories`,T.appendChild(E),T.appendChild(P),v.appendChild(C),v.appendChild(T),v.addEventListener("click",()=>{e.querySelectorAll(".bucket-dropdown-item").forEach(I=>I.classList.remove("selected")),v.classList.add("selected"),o.textContent=b.profileName,e.classList.remove("open"),r.classList.remove("open"),a.onBucketChange(b.id,b.profileName)}),p.appendChild(v)}),e.appendChild(p),c.addEventListener("input",()=>{const b=c.value.toLowerCase().trim();p.querySelectorAll(".bucket-dropdown-item").forEach(C=>{const T=C.getAttribute("data-searchable")||"",E=b===""||T.includes(b);C.style.display=E?"":"none"}),w&&(w.style.display=b?"none":""),g&&(g.style.display=b?"none":"")}),c.addEventListener("click",b=>{b.stopPropagation()}),new MutationObserver(b=>{b.forEach(v=>{v.attributeName==="class"&&(e.classList.contains("open")?setTimeout(()=>c.focus(),50):(c.value="",p.querySelectorAll(".bucket-dropdown-item").forEach(T=>{T.style.display=""}),w&&(w.style.display=""),g&&(g.style.display="")))})}).observe(e,{attributes:!0})}function fr(e,t,n,o,r,i,a,s){const c=document.createElement("div");c.className="input-area";const d=document.createElement("div");d.className="controls-row",d.style.position="relative";const p=document.createElement("button");p.className="model-badge",p.innerHTML=`<span class="badge-icon">${$.ai}</span><span class="badge-label">${e.label}</span><span class="badge-chevron">${$.chevronDown}</span>`;const u=document.createElement("div");if(u.className="model-dropdown",uo(u,e,[e],"base",null,!1,s),p.addEventListener("click",v=>{v.stopPropagation();const C=u.classList.contains("open");u.classList.toggle("open",!C)}),d.appendChild(p),d.appendChild(u),!i){const v=document.createElement("div");v.style.flex="1",d.appendChild(v);const C=document.createElement("div");C.className=`website-context-toggle${r?"":" disabled"}`,C.title=r?"Use current website to respond":"Only available on valid websites";const T=document.createElement("div");T.className="website-context-icon",T.innerHTML=$.globe;const E=document.createElement("span");E.className="website-context-label",E.textContent="Use current website";const P=document.createElement("div");P.className=`toggle-switch${o?" active":""}`;const I=document.createElement("div");I.className="toggle-switch-knob",P.appendChild(I),C.appendChild(T),C.appendChild(E),C.appendChild(P),r?C.addEventListener("click",()=>{P.classList.toggle("active"),s.onToolToggle("website-context")}):C.style.pointerEvents="none",d.appendChild(C)}c.appendChild(d);const h=document.createElement("div");h.className="input-row",h.style.position="relative";const m=document.createElement("button");m.className="tools-btn has-active",m.innerHTML=$.tools,m.title="Toggle tools";const f=document.createElement("div");f.className="active-dot",m.appendChild(f);const k=document.createElement("div");k.className="tools-dropdown",ul(k,t,n,a,s,m),m.addEventListener("click",v=>{v.stopPropagation();const C=k.classList.contains("open");k.classList.toggle("open",!C),u.classList.remove("open")}),h.appendChild(m),h.appendChild(k);const w=document.createElement("div");w.className="input-wrapper";const g=document.createElement("textarea");g.className="chat-textarea",g.placeholder="Ask anything about your memories...",g.rows=1;const y=v=>{v.stopPropagation()};g.addEventListener("keydown",y),g.addEventListener("keyup",y),g.addEventListener("keypress",y),g.addEventListener("input",y),g.addEventListener("focus",y),g.addEventListener("blur",y),g.addEventListener("input",()=>{g.style.height="auto",g.style.height=Math.min(g.scrollHeight,150)+"px"}),g.addEventListener("keydown",v=>{if(v.stopPropagation(),v.key==="Enter"&&!v.shiftKey){v.preventDefault();const C=g.value.trim();C&&s.onSend(C)}}),w.appendChild(g),h.appendChild(w);const x=document.createElement("button");x.className="send-btn",x.innerHTML=$.send,x.disabled=!0,x.title="Send message",g.addEventListener("input",()=>{x.disabled=!g.value.trim()}),x.addEventListener("click",()=>{if(x.classList.contains("stop"))s.onStop();else{const v=g.value.trim();v&&s.onSend(v)}}),h.appendChild(x),c.appendChild(h);const b=document.createElement("div");return b.className="powered-by",b.innerHTML="Chats saved locally on your device<br>Deleted when extension is uninstalled",c.appendChild(b),{inputArea:c,refs:{textarea:g,sendBtn:x,modelBadge:p,modelDropdown:u,toolsBtn:m,toolsDropdown:k,controlsRow:d}}}function uo(e,t,n,o,r,i,a){e.innerHTML="";const s=i?n:n.filter(p=>p.featured||p.key===t.key),c=bs(s),d=n.length-s.length;if(c.forEach(p=>{const u=document.createElement("div");u.className="model-category-header",u.textContent=p.label,e.appendChild(u),p.models.forEach(h=>{const m=zt(h,o),f=!!r&&h.key===r,k=document.createElement("div");k.className=`model-dropdown-item${h.key===t.key?" selected":""}${m?"":" locked"}`,m||(k.title="Premium models are available on Pro and AppSumo Tier 3 plans");const w=document.createElement("div");w.className="model-icon",w.textContent=al[h.provider||""]||h.label.charAt(0);const g=document.createElement("div");g.className="model-info";const y=document.createElement("div");y.className="model-name-row";const x=document.createElement("span");if(x.className="model-name",x.textContent=h.label,y.appendChild(x),f){const C=document.createElement("span");C.className="model-recommended-tag",C.textContent="Recommended",C.title="Recommended for your plan",y.appendChild(C)}if(h.creditMultiplier&&h.creditMultiplier>1){const C=document.createElement("span");C.className="model-tier-tag",C.textContent=`${h.creditMultiplier}x`,y.appendChild(C)}const b=document.createElement("div");b.className="model-desc",b.textContent=h.description,g.appendChild(y),g.appendChild(b);const v=document.createElement("span");m?(v.className="model-check",v.innerHTML=$.check):(v.className="model-lock-icon",v.innerHTML='<svg width="12" height="12" viewBox="0 0 24 24" fill="currentColor"><path d="M18 8h-1V6c0-2.76-2.24-5-5-5S7 3.24 7 6v2H6c-1.1 0-2 .9-2 2v10c0 1.1.9 2 2 2h12c1.1 0 2-.9 2-2V10c0-1.1-.9-2-2-2zm-6 9c-1.1 0-2-.9-2-2s.9-2 2-2 2 .9 2 2-.9 2-2 2zm3.1-9H8.9V6c0-1.71 1.39-3.1 3.1-3.1s3.1 1.39 3.1 3.1v2z"/></svg>'),k.appendChild(w),k.appendChild(g),k.appendChild(v),k.addEventListener("click",()=>{m&&(e.querySelectorAll(".model-dropdown-item").forEach(C=>C.classList.remove("selected")),k.classList.add("selected"),e.classList.remove("open"),a.onToggleShowAllModels?.(!1)),a.onModelChange(h)}),e.appendChild(k)})}),d>0||i){const p=document.createElement("button");p.type="button",p.className="show-all-models-toggle",p.textContent=i?"Show less":`Show all models (${d} more)`,p.addEventListener("click",u=>{u.stopPropagation(),a.onToggleShowAllModels?.(!i)}),e.appendChild(p)}}const Fn=(e,t,n,o,r,i,a)=>{uo(e,t,n,o,r,i,a)};function ul(e,t,n,o,r,i){e.innerHTML="";const a=document.createElement("div");a.className="tools-dropdown-title",a.textContent="Active Tools",e.appendChild(a);const s={"web-search":t,"url-extraction":n},c={"web-search":$.globe,"url-extraction":$.link};hs.filter(p=>p.key!=="website-context").forEach(p=>{const u=document.createElement("div");u.className="tool-item";const h=document.createElement("div");h.className=`tool-icon-container ${p.key}`,h.innerHTML=c[p.key]||$.tools;const m=document.createElement("div");m.className="tool-info";const f=document.createElement("div");f.className="tool-label",f.textContent=p.label;const k=document.createElement("div");k.className="tool-desc",k.textContent=p.description,m.appendChild(f),m.appendChild(k);const w=document.createElement("div");w.className=`toggle-switch${s[p.key]?" active":""}`;const g=document.createElement("div");g.className="toggle-switch-knob",w.appendChild(g);const y=()=>{s[p.key]=!s[p.key],w.classList.toggle("active",s[p.key]),r.onToolToggle(p.key);const x=Object.values(s).some(v=>v);i.classList.toggle("has-active",x);const b=i.querySelector(".active-dot");b&&(b.style.display=x?"block":"none")};u.addEventListener("click",y),u.appendChild(h),u.appendChild(m),u.appendChild(w),e.appendChild(u)})}function hl(e,t,n,o,r,i,a){if(e.innerHTML="",t.length>0){const s=document.createElement("div");s.className="dropdown-search-container";const c=document.createElement("input");c.type="text",c.className="dropdown-search-input",c.placeholder="Search chats...";const d=document.createElement("div");d.className="dropdown-search-icon",d.innerHTML=$.search,s.appendChild(d),s.appendChild(c),e.appendChild(s),c.addEventListener("click",h=>{h.stopPropagation()});const p=document.createElement("div");p.className="dropdown-items-container",t.forEach(h=>{const m=document.createElement("div");m.className=`bucket-dropdown-item${h.id===n?" selected":""}`,m.setAttribute("data-thread-id",h.id),m.setAttribute("data-searchable",h.title.toLowerCase());const f=document.createElement("div");f.className="item-icon",f.innerHTML=$.sparkle;const k=document.createElement("div");k.className="item-details";const w=document.createElement("span");w.className="item-name",w.textContent=h.title;const g=document.createElement("span");g.className="item-count",g.textContent=xl(h.updatedAt),k.appendChild(w),k.appendChild(g),m.appendChild(f),m.appendChild(k),m.addEventListener("click",()=>{e.querySelectorAll(".bucket-dropdown-item").forEach(y=>y.classList.remove("selected")),m.classList.add("selected"),o.textContent=h.title,e.classList.remove("open"),r.classList.remove("open"),a.onThreadSwitch(h.id)}),p.appendChild(m)}),e.appendChild(p),c.addEventListener("input",()=>{const h=c.value.toLowerCase().trim();p.querySelectorAll(".bucket-dropdown-item").forEach(f=>{const k=f.getAttribute("data-searchable")||"",w=h===""||k.includes(h);f.style.display=w?"":"none"})}),new MutationObserver(h=>{h.forEach(m=>{m.attributeName==="class"&&(e.classList.contains("open")?setTimeout(()=>c.focus(),50):(c.value="",p.querySelectorAll(".bucket-dropdown-item").forEach(k=>{k.style.display=""})))})}).observe(e,{attributes:!0})}else{const s=document.createElement("div");s.style.cssText=`
      padding: 24px 16px;
      text-align: center;
      color: ${i.textMuted};
      font-size: 13px;
    `,s.textContent="No chat history yet",e.appendChild(s)}}const ml=(e,t,n,o,r,i,a)=>{hl(e,t,n,o,r,i,a)},ze=(e,t)=>{e.innerHTML="";const n=document.createElement("div");n.className="empty-state";const o=document.createElement("div");o.className="empty-state-icon",o.innerHTML=$.sparkle;const r=document.createElement("div");r.className="empty-state-title",r.textContent="Your memories shape every response";const i=document.createElement("div");if(i.className="empty-state-subtitle",i.textContent="Ask anything and let Pluto weave your context into insight",n.appendChild(o),n.appendChild(r),n.appendChild(i),t){const a=document.createElement("div");a.className="empty-state-suggestions",[{icon:$.sparkle,text:"Summarize my saved knowledge"},{icon:$.search,text:"What do I know about..."},{icon:$.globe,text:"Connect insights across topics"}].forEach(c=>{const d=document.createElement("button");d.className="suggestion-chip";const p=document.createElement("div");p.className="suggestion-chip-icon",p.innerHTML=c.icon;const u=document.createElement("span");u.textContent=c.text,d.appendChild(p),d.appendChild(u),d.addEventListener("click",()=>{t.value=c.text,t.focus(),t.dispatchEvent(new Event("input",{bubbles:!0}))}),a.appendChild(d)}),n.appendChild(a)}e.appendChild(n)},Xt=(e,t)=>{if(e.innerHTML="",t.length===0){ze(e);return}t.forEach(n=>{const o=mo(n);e.appendChild(o)}),e.scrollTop=e.scrollHeight},sn=(e,t)=>{const n=e.querySelector(".empty-state");n&&n.remove();const o=mo(t);return e.appendChild(o),e.scrollTop=e.scrollHeight,o},fl="12345678-1234-1234-1234-123456789abc",gl=(e,t)=>{const n=document.createElement("div");n.className="message-row assistant",n.id="typing-indicator-row";const o=document.createElement("div");o.className="message-avatar",o.innerHTML=$.robot;const r=document.createElement("div");r.className="message-bubble";const i=document.createElement("div");i.className="typing-indicator";const a=document.createElement("span");a.className="typing-status-text";const c=!t||t===fl?["Thinking...","Processing...","Analyzing...","Generating response...","Almost there..."]:["Thinking...","Searching memories...","Connecting insights...","Analyzing context...","Reviewing knowledge...","Processing query..."];let d=0;a.textContent=c[0];const p=window.setInterval(()=>{d=(d+1)%c.length,a.textContent=c[d]},2e3);n._rotationInterval=p,i.appendChild(a);const u=document.createElement("div");u.className="typing-dots";for(let h=0;h<3;h++){const m=document.createElement("div");m.className="typing-dot",u.appendChild(m)}return i.appendChild(u),r.appendChild(i),n.appendChild(o),n.appendChild(r),e.appendChild(n),e.scrollTop=e.scrollHeight,n},ho=e=>{const t=e.querySelector("#typing-indicator-row");if(t){const n=t._rotationInterval;n&&clearInterval(n),t.remove()}};function xl(e){const n=Date.now()-e,o=Math.floor(n/1e3),r=Math.floor(o/60),i=Math.floor(r/60),a=Math.floor(i/24);return o<60?"Just now":r<60?`${r}m ago`:i<24?`${i}h ago`:a===1?"Yesterday":a<7?`${a}d ago`:new Date(e).toLocaleDateString()}function mo(e){const t=document.createElement("div");t.className=`message-row ${e.isUser?"user":"assistant"}`,t.dataset.messageId=e.id;const n=document.createElement("div");n.className="message-avatar",n.innerHTML=e.isUser?$.user:$.robot;const o=document.createElement("div");o.className="message-content-wrapper";const r=document.createElement("div");r.className="message-bubble";const i=document.createElement("div");i.className="markdown-content",e.isUser?i.textContent=e.content:i.innerHTML=xn(e.content),r.appendChild(i),o.appendChild(r);const a=document.createElement("div");a.className="message-actions";const s=document.createElement("button");if(s.className="msg-action-btn",s.innerHTML=`${$.copy} <span>Copy</span>`,s.addEventListener("click",()=>{navigator.clipboard.writeText(e.content).then(()=>{s.innerHTML=`${$.check} <span>Copied!</span>`,s.classList.add("copied"),setTimeout(()=>{s.innerHTML=`${$.copy} <span>Copy</span>`,s.classList.remove("copied")},1500)}).catch(()=>{})}),a.appendChild(s),!e.isUser){const c=document.createElement("button");c.className="msg-action-btn regen-btn",c.innerHTML=`${$.regenerate} <span>Retry</span>`,a.appendChild(c)}return o.appendChild(a),t.appendChild(n),t.appendChild(o),t}const bn=(e,t)=>{const n=e.querySelector(".badge-label");n&&(n.textContent=t.label)},yn=(e,t)=>{t?(e.innerHTML=$.stop,e.classList.add("stop"),e.disabled=!1,e.title="Stop generating"):(e.innerHTML=$.send,e.classList.remove("stop"),e.title="Send message")},Ut=(e,t,n,o,r,i,a)=>{po(e,t,n,r,i,a,o)},Je=(e,t)=>{const n=t==="12345678-1234-1234-1234-123456789abc",o=t&&t!=="12345678-1234-1234-1234-123456789abc";e.disabled=n,e.title=n?"Select a memory bucket to save":o?"Save Chat to Memory Bucket":"Save Chat as New Memory Bucket",e.setAttribute("data-has-bucket",o?"true":"false")},gr=(e,t,n)=>{if(t)e.disabled=!0,e.innerHTML=$.spinner,e.classList.add("loading");else{const o=n==="12345678-1234-1234-1234-123456789abc";e.disabled=o,e.innerHTML=$.bookmark,e.classList.remove("loading")}},xr=(e,t)=>{t?(e.disabled=!0,e.innerHTML=$.spinner,e.classList.add("loading")):(e.disabled=!1,e.innerHTML=$.bookmarkPlus,e.classList.remove("loading"))},bl=(e,t)=>{chrome.storage.sync.get(["onboarding"],n=>{(n.onboarding||{tooltips:{}}).tooltips?.chatSaveButtons||setTimeout(()=>{if(!e.isConnected)return;const r=t.querySelector(".sidebar-container");if(r?.classList.contains("theater-mode"))return;const i=document.createElement("div");i.className="chat-onboarding-tooltip",i.innerHTML=`
        <h4 class="chat-tooltip-title">💾 Save Your Valuable Chats</h4>
        <p class="chat-tooltip-content">Use the save icons to store chats in Memory Studio and access them anywhere.</p>
        <button class="chat-tooltip-dismiss">Got it!</button>
        <div class="chat-tooltip-arrow bottom"></div>
      `;const a=e.getBoundingClientRect(),s=t.host.getBoundingClientRect();i.style.top=`${a.bottom-s.top+12}px`,i.style.right="12px",r&&(r.style.position="relative",r.appendChild(i));const c=()=>{i.classList.add("fading-out"),setTimeout(()=>i.remove(),200),chrome.storage.sync.get(["onboarding"],p=>{const u=p.onboarding||{tooltips:{}};u.tooltips={...u.tooltips,chatSaveButtons:!0},chrome.storage.sync.set({onboarding:u})})};i.querySelector(".chat-tooltip-dismiss")?.addEventListener("click",c);const d=p=>{i.contains(p.target)||(c(),t.removeEventListener("click",d))};setTimeout(()=>t.addEventListener("click",d),100)},1e3)})},yl=e=>{chrome.storage.sync.get(["onboarding"],t=>{if((t.onboarding||{tooltips:{}}).tooltips?.chatPrivacyNotice)return;const o=e.querySelectorAll(".message-row.assistant"),r=o[o.length-1];if(!r)return;const i=document.createElement("div");i.className="chat-onboarding-tooltip privacy-tooltip",i.innerHTML=`
      <div class="chat-tooltip-arrow bottom"></div>
      <h4 class="chat-tooltip-title">🔒 Your Chats Stay Private</h4>
      <p class="chat-tooltip-content">Conversations are stored locally on this device only — never synced to our servers or other devices.</p>
      <button class="chat-tooltip-dismiss">Got it!</button>
    `,r.insertAdjacentElement("afterend",i),setTimeout(()=>{i.scrollIntoView({behavior:"smooth",block:"end"})},100);const a=()=>{i.classList.add("fading-out"),setTimeout(()=>i.remove(),200),chrome.storage.sync.get(["onboarding"],c=>{const d=c.onboarding||{tooltips:{}};d.tooltips={...d.tooltips,chatPrivacyNotice:!0},chrome.storage.sync.set({onboarding:d})})};i.querySelector(".chat-tooltip-dismiss")?.addEventListener("click",a);const s=c=>{i.contains(c.target)||(a(),e.removeEventListener("click",s))};setTimeout(()=>e.addEventListener("click",s),100)})};function le(e){return new Promise((t,n)=>{chrome.runtime.sendMessage(e,o=>{chrome.runtime.lastError?(console.error("[Threads] Background message error:",chrome.runtime.lastError.message),n(new Error(chrome.runtime.lastError.message))):t(o)})})}async function fo(e){try{return((await le({action:"threadStorage_getThreadsForBucket",bucketId:e})).entries||[]).map(n=>({...n,messages:n.messages||[]}))}catch{return[]}}async function wl(e){try{return(await le({action:"threadStorage_loadThread",threadId:e})).thread||null}catch{return null}}async function kl(e,t=[]){const n=await le({action:"threadStorage_createThread",bucketId:e,initialMessages:t});return n.thread?n.thread:{id:`thread_${Date.now()}_${Math.random().toString(36).substring(2,11)}`,bucketId:e,title:"New Chat",messages:t,createdAt:Date.now(),updatedAt:Date.now(),savedToMemory:!1}}async function pe(e,t){try{return(await le({action:"threadStorage_updateMessages",threadId:e,messages:t})).thread||null}catch{return null}}async function go(e){await le({action:"threadStorage_markThreadSaved",threadId:e})}async function xo(e,t){try{return(await le({action:"threadStorage_copyThreadToBucket",threadId:e,newBucketId:t})).newThreadId||null}catch{return null}}async function vl(e,t){await le({action:"threadStorage_updateBucketId",threadId:e,newBucketId:t})}async function Cl(e,t){await le({action:"threadStorage_setActiveThread",bucketId:e,threadId:t})}async function El(e){try{return(await le({action:"threadStorage_getActiveThreadWithoutCreating",bucketId:e})).thread||null}catch{return null}}async function Tl(){try{await le({action:"threadStorage_migrate"})}catch(e){console.error("[Threads] Migration failed:",e)}}const bo=e=>e.role!=="viewer",l={host:null,backdrop:null,shadow:null,styleEl:null,refs:null,escHandler:null,scrollHandler:null,callbacks:null,messages:[],isLoading:!1,selectedBucketId:"",selectedBucketName:"",currentThreadId:"",currentThreadTitle:"",selectedModel:$n,allModels:[Sn],userModelTier:"base",defaultModelKey:null,showAllModels:!1,enableWebSearch:!0,enableUrlExtraction:!0,enableWebsiteContext:!0,typingInterval:null,isOpen:!1,isTheaterMode:!1,buckets:[],theaterFilterBucketIds:[]},ln=()=>Date.now().toString(36)+Math.random().toString(36).substring(2,8),He=e=>{!l.refs?.memorySeparator||!l.refs?.memoryThreadTitle||(e&&e!=="New Chat"?(l.refs.memorySeparator.style.display="inline",l.refs.memoryThreadTitle.style.display="inline",l.refs.memoryThreadTitle.textContent=e,l.refs.memoryThreadTitle.title=e,l.refs.memoryBucketSwitcher&&(l.refs.memoryBucketSwitcher.style.display="none")):(l.refs.memorySeparator.style.display="none",l.refs.memoryThreadTitle.style.display="none",l.refs.memoryThreadTitle.textContent="",l.refs.memoryThreadTitle.title="",l.refs.memoryBucketSwitcher&&(l.refs.memoryBucketSwitcher.style.display="flex")))},Sl=async()=>{try{const e=await chrome.runtime.sendMessage({action:"getUserAccount"});if(e?.success&&e.data?.preferredModel)return e.data.preferredModel}catch(e){console.warn("[ChatSidebar] Failed to fetch preferred model:",e)}return null},yo=e=>{chrome.runtime.sendMessage({action:"updateUserPreferences",payload:{preferredModel:e}}).catch(t=>console.warn("[ChatSidebar] Failed to persist preferred model:",t))},$l=async(e=!1)=>{if(!(!e&&l.allModels.length>1))try{const t=await chrome.runtime.sendMessage({action:"getSubscriptionStatus"});if(t?.success&&t.data?.subscription){const n=t.data.subscription;if(n.allModels?.length){if(l.allModels=fs(n.allModels),l.userModelTier=n.modelTier||"base",l.defaultModelKey=n.defaultModel||null,l.selectedModel.key===$n.key){let r=null;const i=await Sl();if(i){const a=l.allModels.find(s=>s.key===i&&zt(s,l.userModelTier));a?r=a:yo(null)}if(!r&&n.defaultModel){const a=l.allModels.find(s=>s.key===n.defaultModel&&zt(s,l.userModelTier));a&&(r=a)}r&&(l.selectedModel=r,l.refs&&bn(l.refs.modelBadge,l.selectedModel))}!l.allModels.some(r=>r.key===l.selectedModel.key)&&l.allModels.length>0&&(l.selectedModel=l.allModels[0],l.refs&&bn(l.refs.modelBadge,l.selectedModel)),l.refs?.modelDropdown&&l.callbacks&&Fn(l.refs.modelDropdown,l.selectedModel,l.allModels,l.userModelTier,l.defaultModelKey,l.showAllModels,l.callbacks)}}}catch(t){console.warn("[ChatSidebar] Failed to fetch subscription models:",t)}},wo=async(e,t)=>{if(l.isOpen){await br(e,t);return}await Tl();const n=U();let o=await Ne();l.selectedBucketId=e,l.selectedBucketName=t,l.currentThreadId="",l.currentThreadTitle="New Chat",l.messages=[],l.selectedModel=$n,l.allModels=[Sn],l.userModelTier="base",l.defaultModelKey=null,l.showAllModels=!1,l.enableWebSearch=!0,l.enableUrlExtraction=!0,l.enableWebsiteContext=!0,l.isLoading=!1,l.typingInterval=null,l.buckets=o,o.filter(x=>x.id!=="12345678-1234-1234-1234-123456789abc").length===0&&chrome.storage.local.get(["token"],x=>{x.token&&chrome.runtime.sendMessage({action:"refreshProfiles",token:x.token}).catch(()=>{})}),chrome.storage.local.set({lastUsedChatBucket:e});const i=window.location.pathname.endsWith("/chat.html");i&&(l.isTheaterMode=!0);const a=document.body.style.transition;i||(document.body.style.transition="margin-right 0.3s cubic-bezier(0.4, 0, 0.2, 1)");const s=document.createElement("div");s.id="plurality-chat-sidebar-host",i?s.style.cssText=`
      position: fixed;
      top: 0;
      left: 0;
      width: 100vw;
      height: 100vh;
      z-index: 2147483646;
      opacity: 0;
      transition: opacity 0.3s ease;
    `:s.style.cssText=`
      position: fixed;
      top: 0;
      right: 0;
      width: 420px;
      height: 100vh;
      z-index: 2147483646;
      transform: translateX(100%);
      transition: transform 0.3s cubic-bezier(0.4, 0, 0.2, 1);
    `,i||(s.dataset.originalBodyTransition=a);const c=s.attachShadow({mode:"open"}),d="plurality-lexend-font";if(!document.getElementById(d)){const x=document.createElement("link");x.id=d,x.rel="stylesheet",x.href=Ra(),document.head.appendChild(x)}const p=document.createElement("style");p.textContent=Qr(n),c.appendChild(p);const u={onSend:ko,onStop:bt,onClose:wn,onBucketChange:br,onModelChange:Ml,onToolToggle:Al,onNewChat:Nl,onSave:Pl,onSaveAsNew:Bl,onThreadSwitch:Co,onTheaterToggle:vo,onLoadBuckets:Ne,onToggleShowAllModels:x=>{l.showAllModels!==x&&(l.showAllModels=x,l.refs?.modelDropdown&&l.callbacks&&Fn(l.refs.modelDropdown,l.selectedModel,l.allModels,l.userModelTier,l.defaultModelKey,l.showAllModels,l.callbacks))}};l.callbacks=u;const h=window.location.protocol==="http:"||window.location.protocol==="https:",{container:m,refs:f}=co(e,t,o,l.selectedModel,l.enableWebSearch,l.enableUrlExtraction,l.enableWebsiteContext,h,l.isTheaterMode,i,n,u,c);i&&m.classList.add("chat-page"),c.appendChild(m),document.body.appendChild(s);const k=x=>{const b=c.activeElement;if(b&&x.key!=="Escape"){if(x.key==="Enter"&&!x.shiftKey&&b instanceof HTMLTextAreaElement){x.preventDefault();const v=b.value.trim();v&&l.callbacks?.onSend&&l.callbacks.onSend(v)}x.stopPropagation()}},w=x=>{c.activeElement&&x.stopPropagation()};document.addEventListener("keydown",k,!0),document.addEventListener("keyup",w,!0),document.addEventListener("keypress",w,!0),document.addEventListener("beforeinput",w,!0),document.addEventListener("copy",w,!0),document.addEventListener("cut",w,!0),document.addEventListener("paste",w,!0),s.dataset.cleanupKeyCapture="true",s.__cleanupKeyCapture=()=>{document.removeEventListener("keydown",k,!0);for(const x of["keyup","keypress","beforeinput","copy","cut","paste"])document.removeEventListener(x,w,!0)},l.host=s,l.backdrop=null,l.shadow=c,l.styleEl=p,l.refs=f,l.isOpen=!0,$l(),f.threadNameEl&&(f.threadNameEl.textContent=l.currentThreadTitle),He(l.currentThreadTitle),f.saveBtn&&Je(f.saveBtn,l.selectedBucketId),await Ie(),i&&f.threadsContainer&&f.bucketFilterDropdown&&(f.theaterFilterDropdownMenu&&f.theaterFilterBtn&&xe(f.theaterFilterDropdownMenu,l.buckets,f.theaterFilterBtn,l.theaterFilterBucketIds,x=>{const b=new CustomEvent("filterchange",{detail:{bucketId:x}});f.bucketFilterDropdown?.dispatchEvent(b)}),f.bucketFilterDropdown.addEventListener("filterchange",async x=>{const v=x.detail.bucketId;v==="all"?l.theaterFilterBucketIds=[]:l.theaterFilterBucketIds.includes(v)?l.theaterFilterBucketIds=l.theaterFilterBucketIds.filter(C=>C!==v):l.theaterFilterBucketIds=[...l.theaterFilterBucketIds,v],qt(f.theaterFilterBtn,l.theaterFilterBucketIds),f.theaterFilterDropdownMenu&&f.theaterFilterBtn&&xe(f.theaterFilterDropdownMenu,l.buckets,f.theaterFilterBtn,l.theaterFilterBucketIds,C=>{const T=new CustomEvent("filterchange",{detail:{bucketId:C}});f.bucketFilterDropdown?.dispatchEvent(T)}),await J()}),f.bucketFilterDropdown.__rebuildDropdown=async()=>{const x=await Ne();l.buckets=x;const b=f.theaterFilterBtn,v=f.theaterFilterDropdownMenu;v&&b&&xe(v,l.buckets,b,l.theaterFilterBucketIds,C=>{const T=new CustomEvent("filterchange",{detail:{bucketId:C}});f.bucketFilterDropdown?.dispatchEvent(T)})},await J()),l.messages.length>0&&Xt(f.messagesArea,l.messages);const g=x=>{x.stopPropagation()};if(s.addEventListener("wheel",g,{passive:!0}),l.scrollHandler=g,requestAnimationFrame(()=>{requestAnimationFrame(()=>{if(i){s.style.opacity="1";const x=document.querySelector(".container");x&&(x.style.display="none")}else document.body.style.marginRight="420px",s.style.transform="translateX(0)";setTimeout(()=>{bl(f.saveBtn,c)},1e3)})}),!i){const x=b=>{b.key==="Escape"&&wn()};document.addEventListener("keydown",x,{signal:O}),l.escHandler=x}const y=x=>{const b=x.target;(!b.closest(".bucket-selector")||b.closest(".bucket-selector")!==f.bucketBtn.parentElement)&&(f.bucketDropdown.classList.remove("open"),f.chevronEl.classList.remove("open"));const v=f.threadBtn.parentElement;(v&&!b.closest(".bucket-selector")||b.closest(".bucket-selector")!==v)&&(f.threadDropdown.classList.remove("open"),f.threadChevronEl.classList.remove("open")),!b.closest(".model-badge")&&!b.closest(".model-dropdown")&&f.modelDropdown.classList.remove("open"),!b.closest(".tools-btn")&&!b.closest(".tools-dropdown")&&f.toolsDropdown.classList.remove("open")};m.addEventListener("click",y),setTimeout(()=>f.textarea.focus(),350)},wn=()=>{if(!l.isOpen)return;l.isLoading&&bt();const e=window.location.pathname.endsWith("/chat.html");l.host&&(e?l.host.style.opacity="0":(l.isTheaterMode?(l.host.style.opacity="0",l.backdrop&&(l.backdrop.style.opacity="0")):l.host.style.transform="translateX(100%)",document.body.style.marginRight="0")),setTimeout(()=>{e?window.close():(l.host?.dataset.originalBodyTransition?document.body.style.transition=l.host.dataset.originalBodyTransition:document.body.style.transition="",l.host&&l.host.__cleanupKeyCapture&&l.host.__cleanupKeyCapture(),l.backdrop?.remove(),l.host?.remove(),l.host=null,l.backdrop=null,l.shadow=null,l.styleEl=null,l.refs=null,l.callbacks=null,l.isTheaterMode=!1)},300),l.escHandler&&(document.removeEventListener("keydown",l.escHandler),l.escHandler=null),l.scrollHandler&&l.host&&(l.host.removeEventListener("wheel",l.scrollHandler),l.scrollHandler=null),l.isOpen=!1},Il=()=>{if(!l.isOpen||!l.styleEl)return;const e=U();l.styleEl.textContent=Qr(e)};async function ko(e){if(l.isLoading||!l.refs)return;if(!l.currentThreadId){const s=await kl(l.selectedBucketId);l.currentThreadId=s.id,l.currentThreadTitle=s.title,l.refs.threadNameEl&&(l.refs.threadNameEl.textContent=s.title),He(s.title),await Ie(),l.isTheaterMode&&l.refs.threadsContainer&&await J()}l.refs.textarea.value="",l.refs.textarea.style.height="auto",l.refs.sendBtn.disabled=!0;let t=e;const n=window.location.pathname.endsWith("/chat.html");if(l.enableWebsiteContext&&!n)try{const s=document.body.innerText||document.body.textContent||"",c=document.title||"",d=window.location.href||"";t=`${e}

[Context: User is on webpage "${c}" (${d}). Page content:
${s}]`}catch(s){console.warn("Failed to extract page content:",s)}const o={id:ln(),content:e,isUser:!0,timestamp:new Date};l.messages.push(o),sn(l.refs.messagesArea,o);const r=await pe(l.currentThreadId,l.messages);r&&r.title!==l.currentThreadTitle&&(l.currentThreadTitle=r.title,l.refs.threadNameEl&&(l.refs.threadNameEl.textContent=r.title),He(r.title),await Ie(),l.isTheaterMode&&l.refs.threadsContainer&&await J()),l.isLoading=!0,yn(l.refs.sendBtn,!0),gl(l.refs.messagesArea,l.selectedBucketId);const i=il(l.messages),a=await rl(t,l.selectedBucketId,i,l.selectedModel.key,l.enableWebSearch,l.enableUrlExtraction);if(!(!l.isOpen||!l.refs)){if(ho(l.refs.messagesArea),a.success&&a.answer){let s="No response content";typeof a.answer=="string"?s=a.answer:typeof a.answer=="object"&&(s=JSON.stringify(a.answer));const c={id:ln(),content:s,isUser:!1,timestamp:new Date,isTyping:!0};l.messages.push(c);const d=sn(l.refs.messagesArea,c),p=d.querySelector(".markdown-content");p&&(p.innerHTML="",l.typingInterval=nl(p,s,async()=>{l.typingInterval=null,c.isTyping=!1,await pe(l.currentThreadId,l.messages),Dl(d,c),l.isTheaterMode&&l.refs?.threadsContainer&&await J(),yl(l.refs.messagesArea)})),await pe(l.currentThreadId,l.messages)}else if(a.error==="Cancelled"){const s=l.messages[l.messages.length-1];if(s&&!s.isUser){l.messages.pop();const c=l.refs.messagesArea.querySelector(".message-row:last-child");c&&c.remove()}await pe(l.currentThreadId,l.messages)}else{const s=a.error==="CreditError"?"Your credits have been exhausted. Please upgrade your plan to continue.":a.error==="Unauthorized"?"Your session has expired. Please log in again.":`Sorry, I encountered an error: ${a.error||"Unknown error"}`,c={id:ln(),content:s,isUser:!1,timestamp:new Date,isError:!0};l.messages.push(c),sn(l.refs.messagesArea,c),await pe(l.currentThreadId,l.messages)}l.isLoading=!1,yn(l.refs.sendBtn,!1),l.refs.sendBtn.disabled=!l.refs.textarea.value.trim()}}async function bt(){if(l.typingInterval!==null){clearInterval(l.typingInterval),l.typingInterval=null;const e=l.messages.find(t=>t.isTyping);if(e&&l.refs){const t=l.refs.messagesArea.querySelectorAll(".message-row"),n=Array.from(t).find(o=>{const r=o;return r.querySelector(".markdown-content")&&r.dataset.messageId===e.id});if(n){const o=n.querySelector(".markdown-content");if(o){const r=o.textContent||o.innerText||"";e.content=r}}e.isTyping=!1,await pe(l.currentThreadId,l.messages)}}ol(),l.refs&&ho(l.refs.messagesArea),l.messages.forEach(e=>{e.isTyping&&(e.isTyping=!1)}),l.isLoading=!1,l.refs&&(yn(l.refs.sendBtn,!1),l.refs.sendBtn.disabled=!l.refs.textarea.value.trim())}async function br(e,t){if(e===l.selectedBucketId)return;const n=!l.currentThreadId&&l.messages.length===0;if(l.currentThreadId&&l.messages.length>0&&await pe(l.currentThreadId,l.messages),l.isLoading&&await bt(),l.selectedBucketId=e,l.selectedBucketName=t,n)l.currentThreadId="",l.currentThreadTitle="New Chat",l.messages=[];else{const r=await El(e);l.currentThreadId=r?.id||"",l.currentThreadTitle=r?.title||"New Chat",l.messages=r?.messages||[]}chrome.storage.local.set({lastUsedChatBucket:e});const o=l.buckets.find(r=>r.id===e);if(l.refs?.saveBtn&&(o&&!bo(o)?(l.refs.saveBtn.style.opacity="0.5",l.refs.saveBtn.title="View-only — cannot save to this bucket"):(l.refs.saveBtn.style.opacity="1",l.refs.saveBtn.title="")),l.refs?.bucketNameEl&&(l.refs.bucketNameEl.textContent=t),l.refs?.memoryNameEl){const r=!t||t==="Unknown"?"Knowledge Base":t;l.refs.memoryNameEl.textContent=r}l.refs?.threadNameEl&&(l.refs.threadNameEl.textContent=l.currentThreadTitle),He(l.currentThreadTitle),l.refs?.saveBtn&&Je(l.refs.saveBtn,e),l.refs?.bucketDropdown&&l.refs.bucketDropdown.querySelectorAll(".bucket-dropdown-item").forEach(i=>{i.getAttribute("data-bucket-id")===e?i.classList.add("selected"):i.classList.remove("selected")}),await Ie(),l.isTheaterMode&&l.refs?.threadsContainer&&l.refs?.bucketsContainer&&(await J(),l.refs.bucketsContainer.querySelectorAll(".theater-bucket-item").forEach(i=>{i.getAttribute("data-bucket-id")===e?i.classList.add("selected"):i.classList.remove("selected")})),l.refs&&(l.messages.length>0?Xt(l.refs.messagesArea,l.messages):ze(l.refs.messagesArea,l.refs.textarea))}const Ll="https://app.plurality.network";function Ml(e){if(!zt(e,l.userModelTier)){window.open(`${Ll}/pricing`,"_blank");return}l.selectedModel=e,yo(e.key),l.refs&&bn(l.refs.modelBadge,e)}function Al(e){e==="web-search"?l.enableWebSearch=!l.enableWebSearch:e==="url-extraction"?l.enableUrlExtraction=!l.enableUrlExtraction:e==="website-context"&&(l.enableWebsiteContext=!l.enableWebsiteContext)}async function Pl(){if(l.messages.length===0){B("No chat content to save","warning");return}const e=await new Promise(s=>{chrome.storage.local.get(["token","isLoggedIn"],c=>{s(c)})});if(!e.isLoggedIn||!e.token){B("Please login first","error");return}const t=l.messages.filter(s=>!s.isTyping&&!s.isError).map(s=>({role:s.isUser?"user":"assistant",content:s.content}));if(t.length===0){B("No messages to save","warning");return}const n=l.selectedBucketId||null,o=!n;if(n){const s=l.buckets.find(c=>c.id===n);if(s&&!bo(s)){B("This bucket is view-only. You cannot save content here.","warning");return}}l.refs&&gr(l.refs.saveBtn,!0,l.selectedBucketId);const r=!window.location.pathname.endsWith("/chat.html"),i=r?"AI Context Flow Sidebar":"AI Context Flow",a=r?window.location.href:"";chrome.runtime.sendMessage({action:"saveContext",payload:{profileId:n,context:{chatHistory:t,profileId:n,platform:i,...a&&{sourceUrl:a}}},token:e.token,skipNotification:!1},async s=>{if(l.refs&&gr(l.refs.saveBtn,!1,l.selectedBucketId),chrome.runtime.lastError)B(`Failed to save: ${chrome.runtime.lastError.message}`,"error");else if(s?.success){if(o&&s?.newProfileId){B("Chat saved as new memory bucket successfully!","success");const c=await xo(l.currentThreadId,s.newProfileId);c&&(l.currentThreadId=c),l.selectedBucketId=s.newProfileId;const d=await Ne();l.buckets=d;const p=d.find(u=>u.id===s.newProfileId);if(p&&l.refs){l.selectedBucketName=p.profileName,l.refs.bucketNameEl.textContent=p.profileName,l.refs.memoryNameEl&&(l.refs.memoryNameEl.textContent=p.profileName),Je(l.refs.saveBtn,s.newProfileId);const u=U();Ut(l.refs.bucketDropdown,d,s.newProfileId,l.callbacks,l.refs.bucketNameEl,l.refs.chevronEl,u)}}else{B("Chat saved into memory bucket successfully!","success"),l.currentThreadId&&l.selectedBucketId&&await vl(l.currentThreadId,l.selectedBucketId);const c=await Ne();if(l.buckets=c,l.refs){Je(l.refs.saveBtn,l.selectedBucketId);const d=U();Ut(l.refs.bucketDropdown,c,l.selectedBucketId,l.callbacks,l.refs.bucketNameEl,l.refs.chevronEl,d),l.refs.memoryNameEl&&l.selectedBucketName&&(l.refs.memoryNameEl.textContent=l.selectedBucketName)}}if(await go(l.currentThreadId),await Ie(),l.isTheaterMode&&l.refs?.threadsContainer&&(await J(),l.refs.bucketFilterDropdown&&l.refs.filterTagsContainer)){const c=l.refs.bucketFilterDropdown.querySelector(".theater-filter-btn"),d=l.refs.bucketFilterDropdown.querySelector(".theater-filter-dropdown-menu");if(c&&d){xe(d,l.buckets,c,l.theaterFilterBucketIds,u=>{const h=new CustomEvent("filterchange",{detail:{bucketId:u}});l.refs?.bucketFilterDropdown?.dispatchEvent(h)});const p=U();dl(l.refs.filterTagsContainer,l.theaterFilterBucketIds,l.buckets,p,u=>{l.theaterFilterBucketIds=l.theaterFilterBucketIds.filter(h=>h!==u),J()}),J()}}}else B(`Failed to save: ${s?.error||"Unknown error"}`,"error")})}async function Bl(){if(l.messages.length===0){B("No chat content to save","warning");return}const e=await new Promise(i=>{chrome.storage.local.get(["token","isLoggedIn"],a=>{i(a)})});if(!e.isLoggedIn||!e.token){B("Please login first","error");return}const t=l.messages.filter(i=>!i.isTyping&&!i.isError).map(i=>({role:i.isUser?"user":"assistant",content:i.content}));if(t.length===0){B("No messages to save","warning");return}l.refs&&xr(l.refs.forkBtn,!0);const n=!window.location.pathname.endsWith("/chat.html"),o=n?"AI Context Flow Sidebar":"AI Context Flow",r=n?window.location.href:"";chrome.runtime.sendMessage({action:"saveContext",payload:{profileId:null,context:{chatHistory:t,profileId:null,platform:o,...r&&{sourceUrl:r}}},token:e.token,skipNotification:!1},async i=>{if(l.refs&&xr(l.refs.forkBtn,!1),chrome.runtime.lastError)B(`Failed to save: ${chrome.runtime.lastError.message}`,"error");else if(i?.success)if(i?.newProfileId){B("Chat saved as new memory bucket successfully!","success");const a=await xo(l.currentThreadId,i.newProfileId);a&&(l.currentThreadId=a),l.selectedBucketId=i.newProfileId;const s=await Ne();l.buckets=s;const c=s.find(d=>d.id===i.newProfileId);if(c&&l.refs){l.selectedBucketName=c.profileName,l.refs.bucketNameEl.textContent=c.profileName,l.refs.memoryNameEl&&(l.refs.memoryNameEl.textContent=c.profileName),Je(l.refs.saveBtn,i.newProfileId);const d=U();Ut(l.refs.bucketDropdown,s,i.newProfileId,l.callbacks,l.refs.bucketNameEl,l.refs.chevronEl,d)}await go(l.currentThreadId),await Ie(),l.isTheaterMode&&l.refs?.threadsContainer&&(await J(),l.refs.theaterFilterDropdownMenu&&l.refs.theaterFilterBtn&&l.refs.filterTagsContainer&&(xe(l.refs.theaterFilterDropdownMenu,l.buckets,l.refs.theaterFilterBtn,l.theaterFilterBucketIds,d=>{const p=new CustomEvent("filterchange",{detail:{bucketId:d}});l.refs?.bucketFilterDropdown?.dispatchEvent(p)}),qt(l.refs.theaterFilterBtn,l.theaterFilterBucketIds)))}else B("Failed to save: No profile ID returned","error");else B(`Failed to save: ${i?.error||"Unknown error"}`,"error")})}async function Nl(){l.isLoading&&await bt(),l.currentThreadId&&l.messages.length>0&&await pe(l.currentThreadId,l.messages),l.currentThreadId="",l.currentThreadTitle="New Chat",l.messages=[],l.refs&&(l.refs.threadNameEl.textContent="New Chat",He("New Chat"),ze(l.refs.messagesArea,l.refs.textarea),l.refs.textarea.focus(),await Ie(),l.isTheaterMode&&l.refs.threadsContainer&&await J())}function qt(e,t){if(!e)return;const n=e.querySelector(".filter-count");n&&(t.length===0?(n.textContent="",e.classList.remove("active")):(n.textContent=`(${t.length})`,e.classList.add("active")))}function vo(){if(!l.host||!l.shadow||!l.refs||window.location.pathname.endsWith("/chat.html"))return;l.isTheaterMode=!l.isTheaterMode;const t=l.buckets,n=l.selectedBucketId,o=l.buckets.find(p=>p.id===n),r=o?o.id==="12345678-1234-1234-1234-123456789abc"?"Knowledge Base":o.profileName:"Unknown",i=U(),a=window.location.protocol==="http:"||window.location.protocol==="https:",{container:s,refs:c}=co(n,r,t,l.selectedModel,l.enableWebSearch,l.enableUrlExtraction,l.enableWebsiteContext,a,l.isTheaterMode,!1,i,l.callbacks,l.shadow),d=l.shadow.querySelector(".sidebar-container");if(d&&d.remove(),l.shadow.appendChild(s),l.refs=c,l.allModels.length>1&&c.modelDropdown&&l.callbacks&&Fn(c.modelDropdown,l.selectedModel,l.allModels,l.userModelTier,l.defaultModelKey,l.showAllModels,l.callbacks),l.messages.length===0?ze(c.messagesArea,c.textarea):Xt(c.messagesArea,l.messages),He(l.currentThreadTitle),c.threadNameEl&&(c.threadNameEl.textContent=l.currentThreadTitle),l.isTheaterMode){if(!l.backdrop){const p=document.createElement("div");p.id="plurality-chat-backdrop",p.style.cssText=`
        position: fixed;
        top: 0;
        left: 0;
        width: 100vw;
        height: 100vh;
        background: rgba(0, 0, 0, 0.7);
        z-index: 2147483645;
        opacity: 0;
        transition: opacity 0.3s ease;
      `,p.addEventListener("click",()=>{vo()}),document.body.appendChild(p),l.backdrop=p}requestAnimationFrame(()=>{l.backdrop&&(l.backdrop.style.opacity="1")}),document.body.style.marginRight="0",l.host.style.cssText=`
      position: fixed;
      top: 20px;
      left: 50%;
      transform: translateX(-50%);
      width: min(1100px, 85vw);
      height: calc(100vh - 40px);
      z-index: 2147483646;
      transition: all 0.4s cubic-bezier(0.4, 0, 0.2, 1);
    `,c.bucketsContainer&&c.threadsContainer&&c.bucketFilterDropdown&&c.filterTagsContainer&&(qt(c.theaterFilterBtn,l.theaterFilterBucketIds),c.theaterFilterDropdownMenu&&c.theaterFilterBtn&&xe(c.theaterFilterDropdownMenu,l.buckets,c.theaterFilterBtn,l.theaterFilterBucketIds,p=>{const u=new CustomEvent("filterchange",{detail:{bucketId:p}});c.bucketFilterDropdown?.dispatchEvent(u)}),J(),c.bucketFilterDropdown.addEventListener("filterchange",async p=>{const h=p.detail.bucketId;h==="all"?l.theaterFilterBucketIds=[]:l.theaterFilterBucketIds.includes(h)?l.theaterFilterBucketIds=l.theaterFilterBucketIds.filter(m=>m!==h):l.theaterFilterBucketIds=[...l.theaterFilterBucketIds,h],qt(c.theaterFilterBtn,l.theaterFilterBucketIds),c.theaterFilterDropdownMenu&&c.theaterFilterBtn&&xe(c.theaterFilterDropdownMenu,l.buckets,c.theaterFilterBtn,l.theaterFilterBucketIds,m=>{const f=new CustomEvent("filterchange",{detail:{bucketId:m}});c.bucketFilterDropdown?.dispatchEvent(f)}),await J()}),c.bucketFilterDropdown.__rebuildDropdown=async()=>{const p=await Ne();l.buckets=p;const u=c.theaterFilterBtn,h=c.theaterFilterDropdownMenu;h&&u&&xe(h,l.buckets,u,l.theaterFilterBucketIds,m=>{const f=new CustomEvent("filterchange",{detail:{bucketId:m}});c.bucketFilterDropdown?.dispatchEvent(f)})}),chrome.storage.local.set({theaterModePreference:!0})}else l.backdrop&&(l.backdrop.style.opacity="0",setTimeout(()=>{l.backdrop?.remove(),l.backdrop=null},300)),document.body.style.marginRight="420px",l.host.style.cssText=`
      position: fixed;
      top: 0;
      right: 0;
      width: 420px;
      height: 100vh;
      z-index: 2147483646;
      transform: translateX(0);
      transition: all 0.4s cubic-bezier(0.4, 0, 0.2, 1);
    `,Ie(),chrome.storage.local.set({theaterModePreference:!1})}async function J(){if(!l.refs||!l.refs.threadsContainer)return;const e=l.buckets.map(async a=>(await fo(a.id)).map(c=>({...c,bucketId:a.id,bucketName:a.id==="12345678-1234-1234-1234-123456789abc"?"Knowledge Base":a.profileName}))),n=(await Promise.all(e)).flat();n.sort((a,s)=>s.updatedAt-a.updatedAt);const r=(l.theaterFilterBucketIds.length===0?n:n.filter(a=>l.theaterFilterBucketIds.includes(a.bucketId))).map(a=>({id:a.id,title:a.title,updatedAt:new Date(a.updatedAt).toISOString(),bucketName:a.bucketName,bucketId:a.bucketId})),i=U();cl(l.refs.threadsContainer,r,l.currentThreadId,i,Co)}async function Ie(){if(!l.refs)return;const t=(await fo(l.selectedBucketId)).map(o=>({id:o.id,title:o.title,updatedAt:o.updatedAt})),n=U();ml(l.refs.threadDropdown,t,l.currentThreadId,l.refs.threadNameEl,l.refs.threadChevronEl,n,l.callbacks)}async function Co(e){if(!l.refs||e===l.currentThreadId)return;l.currentThreadId&&l.messages.length>0&&await pe(l.currentThreadId,l.messages),l.isLoading&&await bt();const t=await wl(e);if(!t){console.error("[ChatSidebar] Thread not found:",e);return}const n=t.bucketId!==l.selectedBucketId;if(l.currentThreadId=t.id,l.currentThreadTitle=t.title,l.messages=t.messages,n){l.selectedBucketId=t.bucketId;const o=l.buckets.find(r=>r.id===t.bucketId);if(o){const r=o.id==="12345678-1234-1234-1234-123456789abc"?"Knowledge Base":o.profileName;l.selectedBucketName=r,l.refs.bucketNameEl&&(l.refs.bucketNameEl.textContent=r),l.refs.memoryNameEl&&(l.refs.memoryNameEl.textContent=r),l.refs.saveBtn&&Je(l.refs.saveBtn,t.bucketId),chrome.storage.local.set({lastUsedChatBucket:t.bucketId})}}l.refs.threadNameEl.textContent=t.title,He(t.title),await Cl(t.bucketId,t.id),t.messages.length>0?Xt(l.refs.messagesArea,t.messages):ze(l.refs.messagesArea,l.refs.textarea),l.refs.threadDropdown.classList.remove("open"),l.refs.threadChevronEl.classList.remove("open"),l.isTheaterMode&&l.refs.threadsContainer&&await J()}function Dl(e,t){const n=e.querySelector(".regen-btn");n&&n.addEventListener("click",async()=>{if(l.isLoading||!l.refs)return;const o=l.messages.findIndex(i=>i.id===t.id);if(o<=0)return;const r=l.messages[o-1];r.isUser&&(l.messages.splice(o,1),e.remove(),await ko(r.content))})}async function Ne(){return new Promise(e=>{chrome.storage.local.get(["profiles"],t=>{e(t.profiles||[])})})}chrome.storage?.onChanged?.addListener(e=>{if(!(!l.isOpen||!l.refs||!l.callbacks)&&e.profiles){const t=e.profiles.newValue||[];l.buckets=t;const n=U();Ut(l.refs.bucketDropdown,t,l.selectedBucketId,l.callbacks,l.refs.bucketNameEl,l.refs.chevronEl,n)}});(function(){const t=["plurality-header-dropdown","plurality-sync-button","plurality-sync-dropdown","plurality-selection-icon","plurality-selection-dropdown","plurality-snackbar","plurality-extension-invalidated-banner","plurality-chat-sidebar-host","plurality-chat-backdrop"];for(const o of t){const r=document.getElementById(o);r&&r.remove()}document.querySelectorAll("[data-plurality-snackbar]").forEach(o=>{o.textContent?.includes("Please refresh the browser window to update")&&o.remove()}),new MutationObserver(o=>{for(const r of o)for(const i of r.addedNodes)i instanceof HTMLElement&&i.hasAttribute("data-plurality-snackbar")&&i.textContent?.includes("Please refresh the browser window to update")&&i.remove()}).observe(document.body||document.documentElement,{childList:!0,subtree:!0})})();const Rl=()=>{try{const e=new URL(ht);return window.location.hostname===e.hostname}catch{return!1}};let R=null,L=[],it=null,kn=!1,st=!1,qe=!1,Pe=!1,ne=!1,zn=0,Ct=null;const yt=async(e,t=!1)=>{if(kn&&!t||!Re()||(await new Promise(r=>{chrome.storage.sync.get(["onboarding"],i=>r(i))})).onboarding?.hideChatAgentIcons)return;Ct&&(clearTimeout(Ct),Ct=null);let o="";e==="Improve Prompt"?o=`Press <span class="keyboard-shortcut">${dn("I")}</span> to improve prompt`:o=`Press <span class="keyboard-shortcut">${dn("I")}</span> to improve prompt based on<br/><span class="keyboard-shortcut">${e}</span>`,Ct=setTimeout(()=>{B(o,"info",2e3),kn=!0},100)},Eo=()=>window.location.protocol==="chrome-extension:",Fl=()=>{let e;window.location.pathname.endsWith("/chat.html")?e=window.matchMedia("(prefers-color-scheme: dark)").matches?"dark":"light":e=pn(),on(e),es(t=>{on(t),yr()}),window.location.pathname.endsWith("/chat.html")&&window.matchMedia("(prefers-color-scheme: dark)").addEventListener("change",t=>{const n=t.matches?"dark":"light";on(n),yr()})},yr=()=>{L.length>0&&!ne&&W(L,R),Nt().catch(console.warn),Il()},Hn=async()=>{if(Pe)return;if(zn=Date.now(),Fl(),Eo()){window.location.pathname.endsWith("/chat.html")&&chrome.storage.local.get(["lastUsedChatBucket"],n=>{const o=n.lastUsedChatBucket||"12345678-1234-1234-1234-123456789abc";chrome.storage.local.get(["profiles"],r=>{const a=(r.profiles||[]).find(c=>c.id===o),s=a?o==="12345678-1234-1234-1234-123456789abc"?"Knowledge Base":a.profileName:"Knowledge Base";wo(o,s)})});return}zr();try{chrome.storage.local.get(["profiles","isLoggedIn"],n=>{const o=n.profiles||[],r=n.isLoggedIn||!1;try{ns(o,r)}catch(i){console.warn("Text selection handler initialization failed:",i)}})}catch(n){console.warn("Failed to initialize text selection handler:",n)}const e=window.location.hostname==="accounts.google.com";if(!Re()&&!Rl()&&!e){const n=document.createElement("div");n.style.cssText="position:fixed;right:0;top:50%;width:1px;height:1px;pointer-events:none;z-index:2147483646;",document.body.appendChild(n);const o=_e();Pt("chatSidebarHint",n,{title:`<span style="display:flex;align-items:center;gap:8px;"><img src="${o}" alt="" style="width:20px;height:20px;border-radius:4px;flex-shrink:0;"/> AI Context Flow</span>`,content:'🖱️ Right-click → <strong>"Open AI Chat"</strong>',position:"left",dismissAfter:8e3},()=>{n.remove()},2e3)}if(!Re())return;Ur();const t=re();try{await Ha();const n=Oa(t);if(n?await zl([n].filter(Boolean).join(", ")):console.warn("No valid selectors found, skipping element wait"),!ts(t)){await _a();return}try{chrome.storage.local.get(["profiles","selectedProfileId","isLoggedIn"],o=>{if(L=o.profiles||[],R=o.selectedProfileId||"12345678-1234-1234-1234-123456789abc",L.length){try{_l(L,R)}catch(r){console.warn("Header dropdown observer setup failed:",r)}if(R){const r=L.find(i=>i.id===R);r&&setTimeout(()=>{try{yt(r.profileName)}catch(i){console.warn("Profile notification failed:",i)}},500)}}try{gt(L)}catch(r){console.warn("Text selection profile update failed:",r)}})}catch(o){if(console.warn("Storage access failed:",o),o instanceof Error&&o.message.includes("Extension context invalidated")){Pe=!0,_();return}}try{await Nt()}catch(o){console.warn("Sync button creation failed:",o)}try{jl()}catch(o){console.warn("New chat button listener setup failed:",o)}}catch(n){if(console.error("[Plurality:init] ❌ Failed to initialize:",n),n instanceof Error&&n.message.includes("Extension context invalidated")){Pe=!0,_();return}try{chrome.storage.local.get(["profiles","selectedProfileId"],o=>{L=o.profiles||[],L.length>0&&setTimeout(()=>{try{Nt().catch(console.warn)}catch(r){console.warn("Fallback UI setup failed:",r)}},1e3)})}catch(o){console.warn("Fallback initialization also failed:",o),o instanceof Error&&o.message.includes("Extension context invalidated")&&(Pe=!0,_())}}},zl=(e,t=3e4)=>new Promise((n,o)=>{if(!e||e.trim().length===0||e==="[data-plurality-fallback]"){console.warn("[Plurality:waitForElement] Empty or fallback selector provided, skipping element wait"),n(document.body);return}const r=document.querySelector(e);if(r){n(r);return}const i=new MutationObserver(()=>{const a=document.querySelector(e);a&&(i.disconnect(),n(a))});i.observe(document.body,{childList:!0,subtree:!0}),setTimeout(()=>{i.disconnect(),o(new Error(`Element not found: ${e}`))},t)}),Hl=()=>{if(Eo()||!Re())return;let e=!1;const t=()=>{if(Pe||ne||e||document.hidden||Date.now()-zn<1500)return;const p=document.getElementById("plurality-sync-button"),u=document.getElementById("plurality-global-header");p&&u||(e=!0,Hn().catch(console.error).finally(()=>{e=!1}))};let n=window.location.href;const o=()=>{const d=window.location.href;d!==n&&(n=d,setTimeout(t,1500))};let r=0;const i=setInterval(()=>{r++,o(),t(),r>=10&&clearInterval(i)},3e3);setInterval(()=>{o(),t()},5e3);const a=()=>o();window.addEventListener("popstate",a,{signal:O});const s=history.pushState.bind(history),c=history.replaceState.bind(history);history.pushState=function(...d){s(...d),a()},history.replaceState=function(...d){c(...d),a()}},_l=(e,t)=>{it&&(it.disconnect(),it=null),it=new MutationObserver(n=>{if(!ne){for(const o of n)if(o.addedNodes.length){for(const r of o.addedNodes)if(r.nodeType===1){const i=r,a=i.matches("header")?[i]:i.querySelectorAll("header"),s=i.matches("#plurality-global-header")?[i]:i.querySelectorAll("#plurality-global-header");for(const c of a)(c.matches(".sticky")||c.classList.contains("sticky"))&&(c.querySelector("#plurality-header-dropdown")||setTimeout(()=>{W(L,R)},100));for(const c of s)c.querySelector("#plurality-header-dropdown")||setTimeout(()=>{W(L,R)},100)}}}}),it.observe(document.body,{childList:!0,subtree:!0}),setTimeout(()=>{ne||W(L,R)},300)},wr=(e,t,n)=>{const o=U(),r=document.createElement("div");r.style.cssText=`
    padding: 12px 16px;
    cursor: ${t?"default":"pointer"};
    display: flex;
    align-items: center;
    gap: 12px;
    transition: background 0.2s ease;
    background: ${t?o.backgroundSelected:"transparent"};
  `;const i=e.id==="12345678-1234-1234-1234-123456789abc",a=document.createElement("div");i?a.innerHTML=`<svg width="20" height="20" viewBox="0 0 20 20" fill="none" xmlns="http://www.w3.org/2000/svg">
      <path d="M11 2L4 11H9L8 18L16 9H11L11 2Z" stroke="${o.extensionAccent}" stroke-width="1.5" stroke-linejoin="round" fill="none"/>
    </svg>`:a.innerHTML=`<svg width="20" height="20" viewBox="0 0 20 20" fill="none" xmlns="http://www.w3.org/2000/svg">
      <path d="M11 2L4 11H9L8 18L16 9H11L11 2Z" fill="${o.extensionAccent}" stroke="none"/>
    </svg>`,a.style.cssText=`
    width: 20px;
    height: 20px;
    flex-shrink: 0;
    pointer-events: none;
    display: flex;
    align-items: center;
    justify-content: center;
  `;const s=document.createElement("div");s.style.cssText=`
    flex: 1;
    display: flex;
    flex-direction: column;
    gap: 2px;
  `;const c=document.createElement("div");if(c.style.cssText=`
    font-size: 14px !important;
    font-weight: ${t?"600":"500"} !important;
    color: ${o.textPrimary} !important;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
    line-height: normal !important;
    letter-spacing: normal !important;
    text-transform: none !important;
  `,c.textContent=e.profileName.replace("Improve Prompt","No Memory (Just Improve It)"),s.appendChild(c),!i){const d=document.createElement("div");d.style.cssText=`
      font-size: 12px !important;
      color: ${o.textMuted} !important;
      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
      line-height: normal !important;
      letter-spacing: normal !important;
      text-transform: none !important;
    `,d.textContent=`${e.contextCount} ${e.contextCount===1?"Item":"Items"}`,s.appendChild(d)}return r.appendChild(a),r.appendChild(s),t||(r.addEventListener("mouseenter",()=>{r.style.background=o.backgroundSecondary}),r.addEventListener("mouseleave",()=>{r.style.background="transparent"})),r},kr=async(e,t)=>{try{await chrome.storage.local.set({selectedProfileId:e.id}),chrome.runtime.sendMessage({action:"profileChanged",profileId:e.id,profiles:t}),yt(e.profileName,!0)}catch(n){n instanceof Error&&n.message.includes("Extension context invalidated")?_():console.error("Error handling profile selection:",n)}},Ol=(e,t)=>{const n="plurality-header-dropdown",o=U();let r=!1;st?(qe=!1,document.querySelectorAll(`#${n}`).forEach(b=>b.remove()),setTimeout(()=>{st=!1},100)):(r=qe,document.querySelectorAll(`#${n}`).forEach(b=>b.remove()));const i=t||"12345678-1234-1234-1234-123456789abc",a=document.createElement("div");a.id=n,a.style.display="inline-flex",a.style.pointerEvents="auto",a.style.isolation="isolate";const s=document.createElement("button");s.style.cssText=`
    border: none;
    border-radius: 12px;
    color: ${o.textPrimary};
    font-size: 14px;
    font-weight: 500;
    padding: 6px 10px;
    display: flex;
    align-items: center;
    gap: 8px;
    cursor: pointer;
    background: ${o.background};
    box-shadow: 0 4px 12px ${o.shadowColor}, 0 0 0 2px rgba(${o.extensionAccentRgb}, 0.3);
    transition: all 0.3s ease;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif;
  `,s.addEventListener("mouseenter",()=>{s.style.boxShadow=`0 6px 16px rgba(${o.extensionAccentRgb}, 0.4), 0 0 0 3px rgba(${o.extensionAccentRgb}, 0.5)`}),s.addEventListener("mouseleave",()=>{s.style.boxShadow=`0 4px 12px ${o.shadowColor}, 0 0 0 2px rgba(${o.extensionAccentRgb}, 0.3)`});const c=document.createElement("img");c.src=_e(),c.alt="menu-icon",c.style.width="20px",c.style.height="20px";const d=document.createElement("span"),p=e.find(x=>x.id===i);i==="12345678-1234-1234-1234-123456789abc"?d.textContent=p?p.profileName:"Select profile":d.textContent=p?`Improve Prompt > ${p.profileName}`:"Select profile",d.style.overflow="hidden",d.style.textOverflow="ellipsis",d.style.whiteSpace="nowrap",d.style.flexShrink="1",d.style.maxWidth="300px";const u=document.createElement("div");u.innerHTML=`
    <svg width="12" height="12" viewBox="0 0 16 16" fill="currentColor">
      <path d="M12.1338 5.94433C12.3919 5.77382 12.7434 5.80202 12.9707 6.02929C13.1979 6.25656 13.2261 6.60807 13.0556 6.8662L12.9707 6.9707L8.47067 11.4707C8.21097 11.7304 7.78896 11.7304 7.52926 11.4707L3.02926 6.9707L2.9443 6.8662C2.77379 6.60807 2.80199 6.25656 3.02926 6.02929C3.25653 5.80202 3.60804 5.77382 3.86617 5.94433L3.97067 6.02929L7.99996 10.0586L12.0293 6.02929L12.1338 5.94433Z"></path>
    </svg>
  `,u.style.display="flex",u.style.alignItems="center",u.style.marginLeft="4px",u.style.color=o.extensionAccent,s.appendChild(c),s.appendChild(d),s.appendChild(u);const h=document.createElement("div");h.style.cssText=`
    position: absolute;
    top: calc(100% + 5px);
    left: 0;
    background: ${o.background};
    border-radius: 12px;
    min-width: 280px;
    max-width: 350px;
    width: max-content;
    box-shadow: 0 4px 20px ${o.shadowColor};
    border: 1px solid ${o.border};
    display: ${r?"block":"none"};
    z-index: 9999;
    max-height: 300px;
    overflow-y: auto;
    padding: 8px 0;
  `;const m=e.find(x=>x.id==="12345678-1234-1234-1234-123456789abc"),f=e.filter(x=>x.id!=="12345678-1234-1234-1234-123456789abc");if(m){const x=m.id===i,b=wr(m,x);x||b.addEventListener("click",async()=>{st=!0,await kr(m,e),h.style.display="none"}),h.appendChild(b)}if(m&&f.length>0){const x=document.createElement("div");x.style.cssText=`
      height: 1px;
      background-color: ${o.border};
      margin: 4px 0;
    `,h.appendChild(x)}if(f.length>0){const x=document.createElement("div");x.style.cssText=`
      padding: 12px 16px 8px 16px;
      font-size: 12px !important;
      font-weight: 600 !important;
      color: ${o.textMuted} !important;
      letter-spacing: 0.5px !important;
      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
      line-height: normal !important;
    `,x.innerHTML="Select Memory Bucket",h.appendChild(x)}f.forEach(x=>{const b=x.id===i,v=wr(x,b);b||v.addEventListener("click",async()=>{st=!0,await kr(x,e),h.style.display="none"}),h.appendChild(v)});const k=document.createElement("div");k.style.cssText=`
    height: 1px;
    background-color: ${o.border};
    margin: 4px 0;
  `,h.appendChild(k);const w=document.createElement("div");w.style.cssText=`
    padding: 12px 16px;
    cursor: pointer;
    display: flex;
    align-items: center;
    gap: 12px;
    transition: background 0.2s ease;
    background: transparent;
  `;const g=document.createElement("div");g.innerHTML=`<svg width="20" height="20" viewBox="0 0 20 20" fill="none" xmlns="http://www.w3.org/2000/svg">
    <circle cx="10" cy="10" r="9" stroke="${o.extensionAccent}" stroke-width="1.5" fill="none"></circle>
    <path d="M7.5 7.5C7.5 6.12 8.62 5 10 5C11.38 5 12.5 6.12 12.5 7.5C12.5 8.88 11.38 10 10 10V11.5" stroke="${o.extensionAccent}" stroke-width="1.5" stroke-linecap="round"></path>
    <circle cx="10" cy="14" r="1" fill="${o.extensionAccent}"></circle>
  </svg>`,g.style.cssText=`
    width: 20px;
    height: 20px;
    flex-shrink: 0;
    display: flex;
    align-items: center;
    justify-content: center;
  `;const y=document.createElement("div");return y.style.cssText=`
    font-size: 14px !important;
    font-weight: 500 !important;
    color: ${o.textPrimary} !important;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif !important;
    line-height: normal !important;
  `,y.textContent="How Can I Create Memories?",w.appendChild(g),w.appendChild(y),w.addEventListener("mouseenter",()=>{w.style.background=o.backgroundSecondary}),w.addEventListener("mouseleave",()=>{w.style.background="transparent"}),w.addEventListener("click",async()=>{try{await chrome.storage.local.set({targetRoute:"/create-memory"}),chrome.runtime.sendMessage({action:"openCreateMemoryGuide"}),h.style.display="none",qe=!1}catch(x){console.error("Error opening create memory guide:",x)}}),h.appendChild(w),s.addEventListener("click",x=>{x.stopPropagation(),be();const b=h.style.display==="block"?"none":"block";qe=b==="block",h.style.display=b}),document.addEventListener("click",x=>{a.contains(x.target)||(h.style.display==="block"&&(qe=!1),h.style.display="none")},{signal:O}),a.appendChild(s),a.appendChild(h),a},W=async(e=[],t)=>{if(!e||e.length===0||!Re()){et();return}if(qe&&!st)return;if((await new Promise(a=>{chrome.storage.sync.get(["onboarding"],s=>a(s))})).onboarding?.hideChatAgentIcons){et();return}const o=re(),r=Yt(),i=Ol(e,t??null);try{const a=await r.insertProfilesDropdown(o,i);if(!a?.success)console.error(`Failed to insert dropdown for ${o}:`,a?.error);else{ql(o,i);const s=()=>{setTimeout(()=>{const c=document.getElementById("plurality-sync-button");c&&Pt("syncButtonFeatures",c,{title:"Quick Actions",content:"Optimize prompts, save conversations into selected memory, or save as new memory - all from one menu!",position:"left"})},500)};Pt("profileSelection",i,{title:"Switch Context",content:"Select a Memory Bucket to add context to your prompts automatically.",position:"bottom"},s),chrome.storage.sync.get(["onboarding"],c=>{c.onboarding?.tooltips?.profileSelection&&s()})}}catch(a){console.error("ServiceExecutor error:",a)}},Ul=e=>{const t=e.querySelector("button");t&&t.addEventListener("click",o=>{o.preventDefault(),o.stopPropagation(),o.stopImmediatePropagation()}),e.querySelectorAll('div[style*="padding: 10px 15px"]').forEach(o=>{o.style.cursor==="pointer"&&o.addEventListener("click",r=>{r.preventDefault(),r.stopPropagation(),r.stopImmediatePropagation();const i=e.querySelector('div[style*="position: absolute"]');i&&(i.style.display="none")})}),e.addEventListener("click",o=>{o.preventDefault(),o.stopPropagation(),o.stopImmediatePropagation()})},ql=(e,t)=>{if(e==="gemini"){const n=document.createElement("style");n.textContent=`
      #plurality-header-dropdown div[style*="position: absolute"]::-webkit-scrollbar {
        width: 6px !important;
      }
      #plurality-header-dropdown div[style*="position: absolute"]::-webkit-scrollbar-track {
        background: #F9FAFB !important;
        border-radius: 3px !important;
      }
      #plurality-header-dropdown div[style*="position: absolute"]::-webkit-scrollbar-thumb {
        background: #9CA3AF !important;
        border-radius: 3px !important;
      }
      #plurality-header-dropdown div[style*="position: absolute"]::-webkit-scrollbar-thumb:hover {
        background: #6B7280 !important;
      }
    `,t.appendChild(n),Ul(t)}else if(e==="claude"){const n=t.parentElement;n&&(n.matches("main.mx-auto.mt-4.w-full.flex-1.px-4")||n.matches(".h-screen.w-full.relative.min-w-0"))&&(n.style.position="relative",t.style.position="absolute",t.style.top="10px",t.style.left="10px",t.style.zIndex="9999")}},et=()=>{const e=document.getElementById("plurality-header-dropdown");e&&e.remove(),kn=!1};chrome.runtime.onMessage.addListener(e=>{e.action==="authStatusChanged"&&(qr(),e.isLoggedIn||(et(),Vr()))});chrome.runtime.onMessage.addListener(e=>{e.action==="authStatusChanged"&&qr()});chrome.runtime.onMessage.addListener(e=>{if(e.action==="creditError"){try{chrome.runtime.sendMessage({action:"creditError",errorData:e.errorData,context:e.context})}catch(t){t instanceof Error&&t.message.includes("Extension context invalidated")&&_()}return!0}if(e.action==="profileChanged"){if(document.hidden)return;R=e.profileId,e.profiles&&(L=e.profiles),W(L,R);const t=L.find(n=>n.id===R);t&&yt(t.profileName),gt(L)}});chrome.runtime.onMessage.addListener(e=>{if(e.action==="updateProfiles"){if(L=e.profiles||[],document.hidden)return;W(L,R),gt(L)}});chrome.runtime.onMessage.addListener(e=>{if(e.action==="newProfileCreated"){if(document.hidden)return;R=e.profileId,e.profiles&&(L=e.profiles);try{chrome.storage.local.set({profiles:L,selectedProfileId:R})}catch(t){if(t instanceof Error&&t.message.includes("Extension context invalidated")){_();return}console.error("Error setting storage:",t)}if(W(L,R),gt(L),!e.skipNotification){const t=L.find(n=>n.id===R);t&&yt(t.profileName,!0)}}});chrome.runtime.onMessage.addListener(e=>{if(e.action==="updateProfiles"){if(L=e.profiles||[],document.hidden)return;W(L,R),gt(L)}});chrome.storage.onChanged.addListener((e,t)=>{if(t==="local"){if(e.profiles){if(L=e.profiles.newValue||[],document.hidden)return;L.length>0?ne||W(L,R):et()}if(e.selectedProfileId){if(document.hidden)return;R=e.selectedProfileId.newValue,ne||W(L,R)}}if(t==="sync"&&e.onboarding)if(e.onboarding.newValue?.hideChatAgentIcons??!1){et(),be();const o=document.getElementById("plurality-sync-button");if(o){const r=o.parentElement;r&&r.tagName==="DIV"&&!r.id&&r.children.length===1?r.remove():o.remove()}document.getElementById("plurality-sync-dropdown")?.remove()}else L.length>0&&W(L,R),Nt().catch(console.warn)});chrome.runtime.onMessage.addListener(e=>{(e.action==="newProfileCreated"||e.action==="profileEdited"||e.action==="profileDeleted")&&chrome.storage.local.get(["profiles","selectedProfileId"],t=>{const{selectedProfileId:n=null}=t,o="12345678-1234-1234-1234-123456789abc";e.profiles&&(L=e.profiles),L.some(a=>a.id===o)||(L=[...L,{id:o,profileName:"Improve Prompt",createdAt:"",contextCount:0}]);let i=n;e.action==="newProfileCreated"?i=e.profileId:e.action==="profileDeleted"&&(n===e.profileId?i=o:i=n);try{chrome.storage.local.set({profiles:L,selectedProfileId:i}),R=i}catch(a){if(a instanceof Error&&a.message.includes("Extension context invalidated")){_();return}console.error("Error setting storage:",a)}!document.hidden&&!ne&&W(L,i)})});chrome.runtime.onMessage.addListener(e=>{e.action==="logout"&&(et(),wn(),L=[],R=null,Vr())});chrome.runtime.onMessage.addListener((e,t,n)=>{if(e.action==="ping")return n({ready:!0}),!0;if(e.action==="extractPageContent"){const o=document.title||"",r=window.location.href||"",i=document.body.innerText||document.body.textContent||"",a=`Page: ${o}

${i}`;return n({pageContent:a,pageUrl:r,pageTitle:o}),!0}if(e.action==="contextMenuSaveToMemory"){const o=e.selectedText||e.text,r=e.sourceUrl||window.location.href||"",i=e.isPageSave===!0;o&&ps(o,r,i);return}if(e.action==="openChatSidebar"){const o=e.bucketId||"12345678-1234-1234-1234-123456789abc",r=e.profileName||"Knowledge Base";wo(o,r)}});const jl=()=>{let e=!1,t=window.location.href;const n=re(),o=async(s=!1)=>{if(document.hidden||e&&!s)return;s||(e=!0);const c="12345678-1234-1234-1234-123456789abc";try{await chrome.storage.local.set({selectedProfileId:c}),R=c,W(L,c),chrome.runtime.sendMessage({action:"profileChanged",profileId:c,profiles:L}),s||yt("Improve Prompt",!0)}catch(d){console.error("❌ Failed to switch to optimize profile:",d),d instanceof Error&&d.message.includes("Extension context invalidated")&&_()}s||setTimeout(()=>{e=!1},1e3)},r=async s=>{try{if(s.target?.closest("#plurality-header-dropdown"))return;let c=!1;if(n==="grok"){const d=tr("grok","newChat");for(const p of d)if(s.target?.closest(p)){c=!0;break}}else if(n==="gemini"){const d=tr("gemini","newChat");for(const p of d)if(s.target?.closest(p)){c=!0;break}}else{const d=ke(n,"newChat"),p=s.target?.closest(d);if(p){const u=p.getAttribute("href");(u==="/new"||u==="/search"||u==="/app")&&(c=!0)}}if(c){ne=!0,await o(!1);const d=300,p=800;setTimeout(async()=>{await o(!0),setTimeout(async()=>{await o(!0),setTimeout(()=>{ne=!1},500)},p)},d)}}catch(c){console.error("❌ Error handling new chat click:",c)}},i=async s=>{(s.ctrlKey||s.metaKey)&&s.key==="j"&&re()==="grok"&&(await o(),setTimeout(()=>{const c=window.location.href;(c.includes("/new")||c.endsWith("/"))&&o()},500))},a=()=>{let s=null,c=!1;new MutationObserver(()=>{if(document.hidden)return;const p=window.location.href;if(p!==t){if(t=p,c)return;s&&clearTimeout(s),s=setTimeout(()=>{let u=!1;if(n==="grok")u=p.includes("/new")||p.endsWith("/")||p.includes("/chat/new");else if(n==="perplexity")u=p===window.location.origin+"/"||p===window.location.origin;else if(n==="gemini"){const h=new URL(p).pathname;u=h==="/app"||h==="/app/"||p===window.location.origin+"/"||p===window.location.origin}else u=p.includes("/new")||p.includes("/search")||p===window.location.origin+"/"||p===window.location.origin;if(u){c=!0,ne=!0;const h=300,m=1e3;setTimeout(()=>{o(!0)},h),setTimeout(()=>{o(!0),setTimeout(()=>{ne=!1,c=!1},500)},m)}s=null},100)}}).observe(document,{subtree:!0,childList:!0})};document.addEventListener("click",r,{signal:O}),document.addEventListener("keydown",i,{capture:!0,signal:O}),a(),n==="grok"&&Yl()},Yl=()=>{new MutationObserver(t=>{for(const n of t)if(n.addedNodes.length){for(const o of n.addedNodes)if(o.nodeType===1){const r=o;if(r.matches('[class*="chat"], [class*="conversation"], [class*="thread"]')||r.querySelector('[class*="chat"], [class*="conversation"], [class*="thread"]')){const a=window.location.href;(a.includes("/new")||a.endsWith("/"))&&setTimeout(()=>{try{chrome.storage.local.get("selectedProfileId",c=>{const d="12345678-1234-1234-1234-123456789abc";if(c.selectedProfileId!==d)try{chrome.storage.local.set({selectedProfileId:d}),R=d,chrome.runtime.sendMessage({action:"profileChanged",profileId:d,profiles:L}),W(L,d)}catch(p){p instanceof Error&&p.message.includes("Extension context invalidated")&&_()}})}catch(c){c instanceof Error&&c.message.includes("Extension context invalidated")&&_()}},500)}}}}).observe(document.body,{childList:!0,subtree:!0})},Wl=()=>{const e=re(),t=window.location.pathname,n=window.location.href;let o=!1;if(e==="grok"?o=(t==="/"||t===""||t.includes("/new")||n.includes("/new"))&&!n.includes("/c/"):e==="gemini"?o=t==="/"||t==="/app"||t==="/app/"||t==="":o=t==="/"||t==="/new"||t==="/search"||t==="",o){if(document.hidden)return;try{chrome.storage.local.get("selectedProfileId",r=>{if(document.hidden)return;const i="12345678-1234-1234-1234-123456789abc";if(r.selectedProfileId!==i)try{chrome.storage.local.set({selectedProfileId:i}),R=i,chrome.runtime.sendMessage({action:"profileChanged",profileId:i,profiles:L}),W(L,i)}catch(a){a instanceof Error&&a.message.includes("Extension context invalidated")&&_()}})}catch(r){r instanceof Error&&r.message.includes("Extension context invalidated")&&_()}}};setTimeout(()=>{Wl()},500);document.addEventListener("visibilitychange",()=>{if(!document.hidden){if(R)chrome.storage.local.set({selectedProfileId:R}).then(()=>{W(L,R),chrome.runtime.sendMessage({action:"profileChanged",profileId:R,profiles:L}).catch(e=>{console.error("[DROPDOWN] Error broadcasting profile change:",e)})}).catch(e=>{console.error("[DROPDOWN] Error restoring profile to storage:",e)});else{const e="12345678-1234-1234-1234-123456789abc";chrome.storage.local.get(["profiles","selectedProfileId"],t=>{const n=t.profiles||[],o=t.selectedProfileId;n.length>0&&(L=n,R=o||e,W(L,R))})}Re()&&!Pe&&setTimeout(()=>{if(Pe||Date.now()-zn<3e3)return;const e=!!document.getElementById("plurality-sync-button"),t=!!document.getElementById("plurality-global-header");(!e||!t)&&Hn().catch(console.error)},1e3)}},{signal:O});Aa();Hn().catch(console.error).finally(()=>{Hl()});
