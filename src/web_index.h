#ifndef WEB_INDEX_H
#define WEB_INDEX_H

const char* const html_template = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Escher Doorbell AI</title>
<style>
  :root {
    --bg-body: #f2f2f2; --bg-card: #ffffff; --text-main: #333333; --text-label: #555555;
    --input-bg: #ffffff; --input-border: #ddd; --heading-color: #007bff; --divider-color: #eee;
    --chat-guest-bg: #007bff; --chat-guest-text: #ffffff;
    --chat-ai-bg: #f1f0f0; --chat-ai-text: #333333;
    --chat-sys-bg: #e9ecef; --chat-sys-text: #6c757d;
  }
  body.dark-mode {
    --bg-body: #121212; --bg-card: #1e1e1e; --text-main: #e0e0e0; --text-label: #bbbbbb;
    --input-bg: #2d2d2d; --input-border: #444; --heading-color: #4dabf7; --divider-color: #333;
    --chat-guest-bg: #0d6efd; --chat-guest-text: #ffffff;
    --chat-ai-bg: #333333; --chat-ai-text: #e0e0e0;
    --chat-sys-bg: #343a40; --chat-sys-text: #adb5bd;
  }
  body { font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif; background: var(--bg-body); color: var(--text-main); padding: 20px; margin: 0; transition: background 0.3s, color 0.3s; }
  .container { display: flex; flex-wrap: wrap; gap: 20px; max-width: 1000px; margin: 0 auto; }
  .header-bar { width: 100%; display: flex; justify-content: space-between; align-items: center; margin-bottom: 20px; }
  h1.main-title { margin: 0; color: var(--heading-color); font-size: 24px; }
  .theme-toggle-btn { background: var(--bg-card); border: 1px solid var(--input-border); color: var(--text-main); padding: 8px 15px; border-radius: 20px; cursor: pointer; font-size: 14px; font-weight: bold; display: flex; align-items: center; gap: 5px; }
  .card { background: var(--bg-card); flex: 1; min-width: 300px; padding: 20px; border-radius: 10px; box-shadow: 0 4px 6px rgba(0,0,0,0.1); display: flex; flex-direction: column; transition: background 0.3s; }
  h2 { color: var(--heading-color); margin-top: 0; margin-bottom: 20px; border-bottom: 2px solid var(--divider-color); padding-bottom: 10px; }
  label { font-weight: bold; display: block; margin-top: 15px; font-size: 13px; color: var(--text-label); }
  input[type=text], input[type=password], input[type=number], textarea { width: 100%; padding: 10px; margin-top: 5px; border: 1px solid var(--input-border); background: var(--input-bg); color: var(--text-main); border-radius: 5px; box-sizing: border-box; font-size: 14px; }
  input:focus, textarea:focus { border-color: var(--heading-color); outline: none; }
  textarea.config { height: 150px; font-family: 'Courier New', monospace; font-size: 12px; line-height: 1.4; }
  button.save-btn { width: 100%; background-color: var(--heading-color); color: white; padding: 12px; border: none; border-radius: 5px; cursor: pointer; margin-top: 20px; font-size: 16px; font-weight: bold; }
   
  /* Chat Window Styling */
  .chat-container {
      height: 350px;
      overflow-y: auto;
      background: var(--bg-card);
      border: 1px solid var(--input-border);
      border-radius: 8px;
      padding: 15px;
      display: flex;
      flex-direction: column;
      gap: 12px;
      margin-bottom: 15px;
  }
  .msg { display: flex; width: 100%; }
  .msg.guest { justify-content: flex-end; }
  .msg.ai { justify-content: flex-start; }
  .msg.system { justify-content: center; margin: 5px 0; }
  
  .bubble {
      max-width: 75%;
      padding: 10px 15px;
      border-radius: 18px;
      font-size: 15px;
      line-height: 1.4;
      position: relative;
      word-wrap: break-word;
  }
  .msg.guest .bubble {
      background-color: var(--chat-guest-bg);
      color: var(--chat-guest-text);
      border-bottom-right-radius: 4px;
  }
  .msg.ai .bubble {
      background-color: var(--chat-ai-bg);
      color: var(--chat-ai-text);
      border-bottom-left-radius: 4px;
  }
  .msg.system .bubble {
      background-color: var(--chat-sys-bg);
      color: var(--chat-sys-text);
      border-radius: 20px;
      font-size: 12px;
      padding: 5px 15px;
      font-weight: bold;
      max-width: 90%;
  }
  
  .chat-label-small { font-size: 10px; margin-bottom: 2px; opacity: 0.6; padding: 0 5px; }
  .msg.guest .chat-label-small { text-align: right; }
  
  /* --- ANIMATIONS --- */
  
  /* 1. Listening Wave (Guest) */
  .listening-wave {
    display: inline-block;
    position: relative;
    width: 40px;
    height: 15px;
    display: flex;
    align-items: center;
    justify-content: space-between;
  }
  .listening-wave div {
    background-color: #fff;
    width: 6px;
    height: 100%;
    animation: wave 1.2s infinite ease-in-out;
  }
  .listening-wave div:nth-child(1) { animation-delay: -1.2s; }
  .listening-wave div:nth-child(2) { animation-delay: -1.1s; }
  .listening-wave div:nth-child(3) { animation-delay: -1.0s; }
  @keyframes wave {
    0%, 40%, 100% { transform: scaleY(0.4); }
    20% { transform: scaleY(1.0); }
  }

  /* 2. Typing Dots (AI Thinking) */
  .typing-dots {
    display: inline-block;
    width: 40px;
  }
  .typing-dots div {
    display: inline-block;
    width: 6px;
    height: 6px;
    border-radius: 50%;
    background-color: var(--text-main);
    animation: bounce 1.4s infinite ease-in-out both;
    margin: 0 2px;
  }
  .typing-dots div:nth-child(1) { animation-delay: -0.32s; }
  .typing-dots div:nth-child(2) { animation-delay: -0.16s; }
  @keyframes bounce {
    0%, 80%, 100% { transform: scale(0); }
    40% { transform: scale(1.0); }
  }

  /* 3. Speaking Bars (AI Speaking) */
  .speaking-bars {
    display: flex;
    align-items: center;
    height: 15px;
  }
  .speaking-bars div {
    background-color: var(--text-main);
    width: 4px;
    height: 100%;
    margin: 0 2px;
    animation: speak 0.8s infinite ease-in-out;
  }
  .speaking-bars div:nth-child(1) { animation-delay: 0.1s; }
  .speaking-bars div:nth-child(2) { animation-delay: 0.2s; }
  .speaking-bars div:nth-child(3) { animation-delay: 0.3s; }
  @keyframes speak {
    0%, 100% { height: 4px; }
    50% { height: 15px; }
  }

  #terminal { background-color: #1e1e1e; color: #00ff00; font-family: 'Courier New', monospace; padding: 15px; height: 150px; overflow-y: auto; border-radius: 5px; font-size: 11px; white-space: pre-wrap; line-height: 1.3; border: 1px solid var(--input-border); }
  .clear-btn { background: #6c757d; color: white; border: none; padding: 6px 15px; border-radius: 4px; cursor: pointer; font-size: 12px; margin-top: 10px; }
  .toggle-btn { background: #28a745; color: white; border: none; padding: 6px 15px; border-radius: 20px; cursor: pointer; font-size: 13px; font-weight: bold; }
  .status-badge { display:inline-block; padding: 6px 12px; border-radius: 20px; background: #e9ecef; color: #495057; font-weight: bold; font-size: 12px; border: 1px solid #ced4da; }
  .status-badge.live { background: #d4edda; color: #155724; border-color: #c3e6cb; }
  .status-badge.live::before { content: "● "; color: #28a745; }
  .stream-box { width: 100%; height: 0; padding-bottom: 56.25%; position: relative; background: #000; border-radius: 8px; margin-bottom: 15px; overflow: hidden; }
  .stream-box iframe { position: absolute; top:0; left: 0; width: 100%; height: 100%; border: none; }
</style>
<script>
  function toggleTheme() {
    document.body.classList.toggle('dark-mode');
    const isDark = document.body.classList.contains('dark-mode');
    document.getElementById('theme-icon').innerText = isDark ? '☀️' : '🌙';
    document.getElementById('theme-text').innerText = isDark ? 'Light Mode' : 'Dark Mode';
  }

  let lastChatHTML = "";
  let lastState = -1;

  setInterval(function() {
    // Poll Logs
    fetch('/logs').then(r => r.text()).then(data => {
      var term = document.getElementById("terminal");
      if(term.innerHTML !== data) { term.innerHTML = data; term.scrollTop = term.scrollHeight; }
    });
    
    // Poll Conversation & State
    fetch('/conversation').then(r => r.json()).then(data => {
      const chatBox = document.getElementById("chat-container");
      let html = "";
      let history = data.history || [];
      let state = data.state || 0; // 0=Idle, 1=Listening, 2=Thinking, 3=Speaking, 4=WaitTTS
      
      if (history.length === 0 && state === 0) {
        html = '<div style="text-align:center; color:gray; font-size:13px; padding-top:20px;">No conversation yet.<br>Press "Toggle Talk" to start.</div>';
      } else {
          history.forEach(msg => {
            if(msg.role === 'guest') {
                 html += `<div class="msg guest"><div><div class="chat-label-small">Guest</div><div class="bubble">${msg.text}</div></div></div>`;
            } else if(msg.role === 'ai') {
                 html += `<div class="msg ai"><div><div class="chat-label-small">AI</div><div class="bubble">${msg.text}</div></div></div>`;
            } else if(msg.role === 'system') {
                 html += `<div class="msg system"><div class="bubble">${msg.text}</div></div>`;
            }
          });
      }
      
      // Add Animation Bubble based on State
      if (state === 1) { // Listening (Guest)
         html += `<div class="msg guest"><div><div class="chat-label-small">Listening...</div><div class="bubble"><div class="listening-wave"><div></div><div></div><div></div></div></div></div></div>`;
      } else if (state === 2) { // LLM Processing (AI)
         html += `<div class="msg ai"><div><div class="chat-label-small">Thinking...</div><div class="bubble"><div class="typing-dots"><div></div><div></div><div></div></div></div></div></div>`;
      } else if (state === 3 || state === 4) { // TTS (AI)
         html += `<div class="msg ai"><div><div class="chat-label-small">Speaking...</div><div class="bubble"><div class="speaking-bars"><div></div><div></div><div></div></div></div></div></div>`;
      }
      
      // Update DOM only if content changed
      if(lastChatHTML !== html || lastState !== state) {
          chatBox.innerHTML = html;
          chatBox.scrollTop = chatBox.scrollHeight;
          lastChatHTML = html;
          lastState = state;
      }
    });
  }, 1000);

  // NEW: Save Configuration via AJAX
  function saveConfig(e) {
    e.preventDefault();
    var form = document.getElementById('configForm');
    var data = new URLSearchParams(new FormData(form));
    
    // Change button text
    var btn = document.querySelector('.save-btn');
    var oldText = btn.innerText;
    btn.innerText = "Saving...";
    btn.disabled = true;

    fetch('/save', { method: 'POST', body: data })
      .then(res => {
        if(res.ok) {
           alert("Settings saved successfully!\n\nThe device is restarting.\nThe page will attempt to reload in 5 seconds...");
           setTimeout(function() { window.location.reload(); }, 5000); 
        } else {
           alert("Error: Save failed. Please check connection.");
           btn.innerText = oldText;
           btn.disabled = false;
        }
      })
      .catch(e => {
        alert("Request Error: " + e);
        btn.innerText = oldText;
        btn.disabled = false;
      });
  }
</script>
</head>
<body>
<div class="container">
  <div class="header-bar">
    <h1 class="main-title">Escher Doorbell Dashboard</h1>
    <button class="theme-toggle-btn" onclick="toggleTheme()">
      <span id="theme-icon">🌙</span> <span id="theme-text">Dark Mode</span>
    </button>
  </div>

  <!-- CONFIG COLUMN -->
  <div class="card">
    <h2>Configuration</h2>
    <form id="configForm" onsubmit="saveConfig(event)">
      <label>WiFi SSID</label><input type="text" name="ssid" id="ssid">
      <label>WiFi Password</label><input type="password" name="pass" id="pass">
      
      <!-- AI SETTINGS (Top) -->
      <div style="margin: 20px 0; border-top: 1px solid var(--divider-color);"></div>
      <h3>AI Settings</h3>
      <label>ASR Key</label><input type="text" name="asrkey" id="asrkey">
      <label>ASR Cluster</label><input type="text" name="asrclus" id="asrclus">
      <label>OpenAI Key</label><input type="password" name="apikey" id="apikey">
      <label>Base URL</label><input type="text" name="apiurl" id="apiurl">
      <label>System Prompt</label><textarea class="config" name="prompt" id="prompt"></textarea>
      
      <label>No Speech Timeout (sec)</label><input type="number" name="timeout" id="timeout">

      <!-- MQTT & STREAM SETTINGS -->
      <div style="margin: 20px 0; border-top: 1px solid var(--divider-color);"></div>
      <h3>IoT Settings</h3>
      <label>Broker IP/URL</label><input type="text" name="mqserver" id="mqserver">
      <label>Port (Default 1883)</label><input type="text" name="mqport" id="mqport">
      <label>Username (Optional)</label><input type="text" name="mquser" id="mquser">
      <label>Password (Optional)</label><input type="password" name="mqpass" id="mqpass">
      
      <label>History Topic (JSON)</label><input type="text" name="mqpub_hist" id="mqpub_hist" placeholder="escher/doorbell/history">
      <label>Subscribe Topic</label><input type="text" name="mqsub" id="mqsub" placeholder="escher/doorbell/in">
      
      <label style="color:#28a745;">Camera Stream URL</label>
      <input type="text" name="stream" id="stream">
      
      <button class="save-btn" type="submit">Save & Restart Device</button>
    </form>
  </div>

  <!-- INTERACTION COLUMN -->
  <div class="card">
    <h2>Live Interaction</h2>
    
    <!-- STREAM WINDOW -->
    <div class="stream-box">
        <iframe src="STREAM_URL_PLACEHOLDER" allowfullscreen></iframe>
    </div>

    <div style="display:flex; justify-content:space-between; align-items:center; margin-bottom:15px;">
      <div class="status-badge live">System Active</div>
      <button class="toggle-btn" onclick="fetch('/toggle')">🎤 Toggle Talk</button>
    </div>

    <!-- NEW CHAT WINDOW -->
    <div id="chat-container" class="chat-container">
        <!-- Messages will be injected here via JS -->
    </div>

    <hr style="margin: 20px 0; border: 0; border-top: 1px solid var(--divider-color);">
    <label style="margin-top:0;">System Log</label>
    <div id="terminal">Loading logs...</div>
    <button class="clear-btn" onclick="fetch('/clearlogs')">Clear Logs</button>
  </div>
</div>
</body></html>
)rawliteral";
#endif
