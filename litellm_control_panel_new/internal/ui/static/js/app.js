let stabilityChart = null;
let lastRanked = [];

async function compareModels() {
    const prompt = document.getElementById('prompt').value;
    if (!prompt || lastRanked.length === 0) return;

    for (let i = 0; i < 3 && i < lastRanked.length; i++) {
        const m = lastRanked[i];
        const outDiv = document.getElementById('m' + (i+1) + '-output');
        document.getElementById('m' + (i+1) + '-name').innerText = m.id;
        outDiv.innerText = 'Streaming...';

        fetch('/api/proxy/v1/chat/completions', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({
                model: m.id,
                messages: [{ role: 'user', content: prompt }],
                stream: true
            })
        }).then(async resp => {
            const reader = resp.body.getReader();
            outDiv.innerText = '';
            while (true) {
                const { done, value } = await reader.read();
                if (done) break;
                const chunk = new TextDecoder().decode(value);
                const lines = chunk.split('\n');
                for (const line of lines) {
                    if (line.startsWith('data: ')) {
                        try {
                            const data = JSON.parse(line.slice(6));
                            const content = data.choices[0].delta.content;
                            if (content) outDiv.innerText += content;
                        } catch (e) {}
                    }
                }
            }
        });
    }
}

function showTab(id) {
    document.querySelectorAll('.tab-content').forEach(t => t.classList.remove('active'));
    document.querySelectorAll('.tab-btn').forEach(b => b.classList.remove('active'));
    document.getElementById(id).classList.add('active');
    event.target.classList.add('active');
}

async function doAction(url) {
    if (!confirm('Are you sure?')) return;
    try {
        const resp = await fetch(url, { method: 'POST' });
        if (resp.ok) alert('Action successful');
        else alert('Action failed: ' + await resp.text());
    } catch (e) {
        alert('Error: ' + e);
    }
}

async function loadConfig() {
    try {
        const resp = await fetch('/api/config');
        const data = await resp.text();
        document.getElementById('config-editor').value = data;
    } catch (e) {
        console.error('Error loading config:', e);
    }
}

async function saveConfig() {
    const data = document.getElementById('config-editor').value;
    try {
        const resp = await fetch('/api/config', {
            method: 'POST',
            body: data
        });
        if (resp.ok) alert('Config saved and reloaded');
        else alert('Failed to save config: ' + await resp.text());
    } catch (e) {
        alert('Error saving config: ' + e);
    }
}

async function sendQuickQuery() {
    const input = document.getElementById('chat-input');
    const out = document.getElementById('chat-output');
    const prompt = input.value;
    if (!prompt) return;

    input.value = '';
    out.innerText += "\nUser: " + prompt + "\nAssistant: ";

    try {
        const resp = await fetch('/api/proxy/v1/chat/completions', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({
                model: 'free-llm',
                messages: [{ role: 'user', content: prompt }],
                stream: true
            })
        });

        const reader = resp.body.getReader();
        while (true) {
            const { done, value } = await reader.read();
            if (done) break;
            const chunk = new TextDecoder().decode(value);
            const lines = chunk.split('\n');
            for (const line of lines) {
                if (line.startsWith('data: ')) {
                    try {
                        const data = JSON.parse(line.slice(6));
                        const content = data.choices[0].delta.content;
                        if (content) {
                            out.innerText += content;
                            out.scrollTop = out.scrollHeight;
                        }
                    } catch (e) {}
                }
            }
        }
        out.innerText += "\n";
    } catch (e) {
        out.innerText += "\n[Error: " + e + "]\n";
    }
}

function filterRankings() {
    const q = document.getElementById('ranking-search').value.toLowerCase();
    const rows = document.querySelectorAll('#rankings tbody tr');
    rows.forEach(row => {
        row.style.display = row.innerText.toLowerCase().includes(q) ? '' : 'none';
    });
}

function filterLogs() {
    const q = document.getElementById('log-search').value.toLowerCase();
    const logs = document.querySelectorAll('#logs div');
    logs.forEach(log => {
        log.style.display = log.innerText.toLowerCase().includes(q) ? '' : 'none';
    });
}

async function toggleProvider(name, enabled) {
    try {
        const resp = await fetch('/api/providers/toggle?name=' + encodeURIComponent(name) + '&enabled=' + enabled, { method: 'POST' });
        if (resp.ok) refresh();
    } catch (e) { console.error(e); }
}

async function refresh() {
    try {
        const presp = await fetch('/api/providers/health');
        const pdata = await presp.json();
        const ptbody = document.querySelector('#providers tbody');
        ptbody.innerHTML = '';
        if (pdata && pdata.length > 0) {
            const labels = pdata.map(p => p.name);
            const latData = pdata.map(p => p.avg_latency);
            const srData = pdata.map(p => p.success_rate);

            if (!providerChart) {
                const ctx = document.getElementById('providerChart').getContext('2d');
                providerChart = new Chart(ctx, {
                    type: 'bar',
                    data: {
                        labels: labels,
                        datasets: [{
                            label: 'Avg Latency (s)',
                            data: latData,
                            backgroundColor: '#2196f3'
                        }, {
                            label: 'Success Rate (%)',
                            data: srData,
                            backgroundColor: '#4caf50'
                        }]
                    },
                    options: { responsive: true, maintainAspectRatio: false }
                });
            } else {
                providerChart.data.labels = labels;
                providerChart.data.datasets[0].data = latData;
                providerChart.data.datasets[1].data = srData;
                providerChart.update('none');
            }

            pdata.forEach(p => {
                const row = document.createElement('tr');
                const btn = "<button class='inline-action' style='background: " + (p.enabled ? "#f44336" : "#4caf50") + "' onclick=\"toggleProvider('" + p.name + "', " + !p.enabled + ")\">" + (p.enabled ? "Disable" : "Enable") + "</button>";
                row.innerHTML = "<td>" + p.name + "</td>" +
                               "<td>" + p.avg_latency.toFixed(3) + "s</td>" +
                               "<td>" + p.success_rate.toFixed(1) + "%</td>" +
                               "<td>" + btn + "</td>";
                ptbody.appendChild(row);
            });
        }
    } catch (e) {}

    try {
        const sresp = await fetch('/api/savings');
        const sdata = await sresp.json();
        document.getElementById('total-savings').innerText = '$' + sdata.total.toFixed(2);
    } catch (e) {}

    try {
        const resp = await fetch('/api/rankings');
        const data = await resp.json();
        const tbody = document.querySelector('#rankings tbody');
        tbody.innerHTML = '';
        lastRanked = data;
        data.forEach((m, i) => {
            const row = document.createElement('tr');
            row.innerHTML = "<td>" + (i === 0 ? '★ ' : '') + m.id + "</td>" +
                           "<td>" + m.provider + "</td>" +
                           "<td class='score'>" + Math.round(m.score) + "</td>" +
                           "<td class='latency'>" + m.latency.toFixed(3) + "s</td>" +
                           "<td>" +
                           "<button class='inline-action' onclick=\"doAction('/api/models/skip?id=' + encodeURIComponent('" + m.id + "'))\">Skip</button>" +
                           "<button class='inline-action' onclick=\"doAction('/api/models/blacklist?id=' + encodeURIComponent('" + m.id + "'))\">Blacklist</button>" +
                           "</td>";
            tbody.appendChild(row);
        });
        document.getElementById('status').innerText = 'Last updated: ' + new Date().toLocaleTimeString();
    } catch (e) {
        document.getElementById('status').innerText = 'Error loading rankings: ' + e;
    }

    try {
        const resp = await fetch('/api/metrics');
        const data = await resp.json();
        const tbody = document.querySelector('#metrics tbody');
        tbody.innerHTML = '';
        if (data && data.length > 0) {
            const labels = data.map(m => new Date(m.timestamp).toLocaleTimeString()).reverse();
            const qpmData = data.map(m => m.qpm).reverse();
            const tpsData = data.map(m => m.tps).reverse();

            if (!stabilityChart) {
                const ctx = document.getElementById('stabilityChart').getContext('2d');
                stabilityChart = new Chart(ctx, {
                    type: 'line',
                    data: {
                        labels: labels,
                        datasets: [{
                            label: 'QPM',
                            data: qpmData,
                            borderColor: '#4caf50',
                            tension: 0.1
                        }, {
                            label: 'TPS',
                            data: tpsData,
                            borderColor: '#2196f3',
                            tension: 0.1
                        }]
                    },
                    options: { responsive: true, maintainAspectRatio: false }
                });
            } else {
                stabilityChart.data.labels = labels;
                stabilityChart.data.datasets[0].data = qpmData;
                stabilityChart.data.datasets[1].data = tpsData;
                stabilityChart.update('none');
            }

            data.forEach(m => {
                const row = document.createElement('tr');
                row.innerHTML = "<td>" + new Date(m.timestamp).toLocaleTimeString() + "</td>" +
                               "<td>" + m.qpm.toFixed(1) + "</td>" +
                               "<td>" + m.tps.toFixed(1) + "</td>";
                tbody.appendChild(row);
            });
        } else {
            tbody.innerHTML = '<tr><td colspan="3">No metrics yet</td></tr>';
        }
    } catch (e) {
        console.error('Error loading metrics:', e);
    }
}

setInterval(refresh, 5000);
refresh();
loadConfig();

const wsProtocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
const ws = new WebSocket(wsProtocol + '//' + window.location.host + '/ws/logs');
ws.onmessage = (event) => {
    const l = JSON.parse(event.data);
    const logDiv = document.getElementById('logs');
    const entry = document.createElement('div');
    entry.innerText = "[" + new Date(l.timestamp).toLocaleTimeString() + "] " + l.message;
    logDiv.appendChild(entry);
    logDiv.scrollTop = logDiv.scrollHeight;
    if (logDiv.childNodes.length > 200) logDiv.removeChild(logDiv.firstChild);
};
ws.onerror = (e) => console.error('WS Error:', e);
