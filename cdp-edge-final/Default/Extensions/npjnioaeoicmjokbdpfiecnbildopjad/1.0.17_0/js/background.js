const userAgents = {
    phonebot: {
        name: "Googlebot Smartphone",
        string: "Mozilla/5.0 (Linux; Android 6.0.1; Nexus 5X Build/MMB29P) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Mobile Safari/537.36 (compatible; Googlebot/2.1; +http://www.google.com/bot.html)"
    },
    ipad: {
        name: "Safari on iPadOS/macOS",
        string: "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/15.3 Safari/605.1.15"
    },
    firefox: {
        name: "Firefox on Windows 10",
        string: "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:97.0) Gecko/20100101 Firefox/97.0"
    },
    android: {
        name: "Chrome on Android",
        string: "Mozilla/5.0 (Linux; Android 12; Pixel 3 XL) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/98.0.4758.101 Mobile Safari/537.36"
    },
    bot: {
        name: "Googlebot (Classic)",
        string: "Mozilla/5.0 (compatible; Googlebot/2.1; +http://www.google.com/bot.html)"
    },
    iphone: {
        name: "Safari on iPhone",
        string: "Mozilla/5.0 (iPhone; CPU iPhone OS 14_4 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/14.0.2 Mobile/15E148 Safari/604.1"
    },
    ie6: {
        name: "Internet Explorer 6",
        string: "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)"
    },
    cros: {
        name: "Chrome on Chromebook/ChromeOS",
        string: "Mozilla/5.0 (X11; CrOS x86_64 14388.27.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/98.0.4758.51 Safari/537.36"
    },
    rpi4: {
        name: "Chromium on Raspberry Pi 4",
        string: "Mozilla/5.0 (X11; Linux armv7l) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.197 Safari/537.36"
    },
    fuchsia: {
        name: "Chrome on Fuchsia OS",
        string: "Mozilla/5.0 (Linux; Android) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.109 Safari/537.36 CrKey/1.54.248666"
    },
    kindle: {
        name: "Amazon Kindle's Browser",
        string: "Mozilla/5.0 (X11; U; Linux armv7l like Android; en-us) AppleWebKit/531.2+ (KHTML, like Gecko) Version/5.0 Safari/533.2+ Kindle/3.0+"
    }
}

chrome.webRequest.onBeforeSendHeaders.addListener(
    function(details) {
        let ua = localStorage.getItem('ua');
        if(ua && (ua != "default")) {
            for (let i = 0; i < details.requestHeaders.length; ++i) {
                if (details.requestHeaders[i].name === 'User-Agent') {
                    let ua = localStorage.getItem('ua');
                    if(!ua) break;
                    if(ua === "default") break;
                    if(ua === "chrome") {
                        details.requestHeaders[i].value = navigator.userAgent.split("Edg")[0];
                        break;
                    }
                    if(ua === "custom") details.requestHeaders[i].value = localStorage.getItem('customua') || "your custom user-agent";
                    else details.requestHeaders[i].value = userAgents[ua].string;
                    break;
                }
            }
        }        
        return {requestHeaders: details.requestHeaders};
    },
    {urls: ["*://*/*"]},
    ["blocking", "requestHeaders"]
);
    
// first run
    
chrome.runtime.onInstalled.addListener(function(details) {
    if (details.reason == "install") {
        chrome.tabs.create({"url": "https://browsernative.com/user-agent-chrome-extension/"});
    }
});
    