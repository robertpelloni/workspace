https://mcp.daloopa.com/authorize?response_type=code&client_id=3kHhdgaGmIVq11752e2LXw&code_challenge=BbLwCSHy4PzYU3lA3chgfIuqEfFlg-x5-qam30CEHo4&code_challenge_method=S256&redirect_uri=http%3A%2F%2Flocalhost%3A54621%2Fcallback&scope=mcp%3Atools+mcp%3Aresources+mcp%3Aprompts


cd C:\\Users\\hyper\\workspace\\zen-mcp-server\\
.\run-server.ps1

npx @srbhptl39/mcp-superassistant-proxy@latest --config ./.superassistant.json --outputTransport ws


# Run on default port 3000
npx super-mcp-router@latest --transport http --port 3333

magg serve --http --port 3334

npx samanhappy/mcphub

mcpproxy serve
mcpproxy serve --listen 127.0.0.1:8081
mcpproxy-tray


chroma
zen
serena




Please check in and have a conference with all the other major AI models through zen and come up with a definitive list of features to develop and their priority, and then come back and document your decisions, findings, recommendations, and plans in detail using both the memory systems in place and md documentation in the project folder.
