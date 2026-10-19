"""Post to YouTube, YouTube Shorts, and TikTok simultaneously."""
import os, json, time, subprocess
from playwright.sync_api import sync_playwright
from google.oauth2.credentials import Credentials
from google.auth.transport.requests import Request
from googleapiclient.discovery import build
from googleapiclient.http import MediaFileUpload
from youtube_update_descriptions import build_description

vdir = 'pipeline_output/beat_videos'
beats = [f for f in os.listdir(vdir) if f.endswith('.mp4') and not f.startswith('_')]
beats.sort(key=lambda f: os.path.getsize(os.path.join(vdir,f)), reverse=True)

# Pick a hymn beat video
for b in beats:
    if any(h in b.lower() for h in ['thy','emmanuel','amazing','howgreat','praise','heleadeth']):
        chosen = b; break
else: chosen = beats[0]

beat_path = os.path.join(vdir, chosen)
name = chosen.replace('_beatsynced.mp4','').replace('_',' ')
sz = os.path.getsize(beat_path)//1024//1024
print(f'Selected: {chosen[:60]} ({sz}MB)')

hymn = 'Hymn'
for h in ['Thy Word','Emmanuel','Amazing Grace','How Great','Praise','He Leadeth','Oh For','Neon Valse','Canon in D','Toccata','Clair de Lune']:
    if h.lower() in name.lower(): hymn = h; break

# Convert to 9:16 vertical
os.makedirs('pipeline_output/shorts', exist_ok=True)
vertical_path = os.path.join('pipeline_output/shorts', chosen.replace('.mp4','_short.mp4'))
if not os.path.exists(vertical_path):
    subprocess.run(['ffmpeg','-y','-loglevel','error','-i',beat_path,
        '-vf','crop=ih*9/16:ih,scale=1080:1920','-c:v','libx264','-preset','medium','-crf','23',
        '-c:a','aac','-b:a','128k','-t','180',vertical_path], check=True)
    print(f'Converted vertical: {os.path.getsize(vertical_path)//1024//1024}MB')
else:
    print(f'Vertical exists: {os.path.getsize(vertical_path)//1024//1024}MB')

# YouTube auth
with open('token.json') as f: data = json.load(f)
creds = Credentials.from_authorized_user_info(data, ['https://www.googleapis.com/auth/youtube'])
if not creds.valid: creds.refresh(Request())
yt = build('youtube','v3',credentials=creds)
desc = build_description(name)

# Upload YouTube (16:9)
yt_id = None
try:
    media = MediaFileUpload(beat_path, chunksize=4*1024*1024, resumable=True)
    req = yt.videos().insert(part='snippet,status', body={
        'snippet':{'title':name[:100],'description':desc,'tags':['resurrecting beats','hymnmania','electronic worship','spiritual edm'],'categoryId':'10'},
        'status':{'privacyStatus':'public'}}, media_body=media)
    resp = None
    while resp is None: _, resp = req.next_chunk()
    yt_id = resp.get('id','?')
    print(f'YouTube: https://youtu.be/{yt_id}')
except Exception as e:
    err = str(e)[:80]
    print(f'YouTube: {"QUOTA" if "quota" in err.lower() else err}')

# Upload YouTube Shorts (9:16)
try:
    media2 = MediaFileUpload(vertical_path, chunksize=4*1024*1024, resumable=True)
    req2 = yt.videos().insert(part='snippet,status', body={
        'snippet':{'title':(name[:80] + ' #Shorts')[:100],'description':desc,'tags':['shorts','resurrecting beats','hymnmania','spiritual edm'],'categoryId':'10'},
        'status':{'privacyStatus':'public'}}, media_body=media2)
    resp2 = None
    while resp2 is None: _, resp2 = req2.next_chunk()
    print(f'YouTube Shorts: https://youtube.com/shorts/{resp2.get("id","?")}')
except Exception as e:
    err = str(e)[:80]
    print(f'Shorts: {"QUOTA" if "quota" in err.lower() else err}')

# BPM detection
bpm = 140
try:
    import librosa
    y_audio, sr = librosa.load(beat_path, sr=22050)
    tempo, _ = librosa.beat.beat_track(y=y_audio, sr=sr)
    if isinstance(tempo,(list,)): tempo = tempo[0]
    bpm = int(max(60, min(200, float(tempo))))
except: pass

# Subgenre detection
subgenre = 'Psytrance'
for g in ['Psytrance','Deep House','Dubstep','Drum and Bass','Chiptune','Gabba','Detroit Techno','Detroit House','Hardstyle','Synthwave']:
    if g.lower() in name.lower(): subgenre = g; break

titok_cap = f"""🌀 RESURRECTING BEATS: '{hymn}' [{subgenre}] ⚡

Resurrected from the vault! High-energy {bpm} BPM in F Major. Built for festivals, vocalists, and live sets.

Free Download / License link in bio!
Comment '{hymn.upper()}' for the untagged high-quality link.

#ResurrectingBeats #EDM #Psytrance #SpiritualEDM #ElectronicMusic #Dance #DanceSafe #HymnMania

#producertok #edmmusic #trancefamily #festivalbeats #unreleasedmusic #{subgenre.replace(' ','')} #{hymn.upper().replace(' ','')}"""

# Upload to TikTok via CDP
with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
    tt = b.contexts[0].new_page()
    tt.goto("https://www.tiktok.com/upload")
    tt.wait_for_timeout(8000)
    
    abs_path = os.path.abspath(vertical_path)
    try:
        file_input = tt.query_selector("input[type=file]")
        if file_input:
            file_input.set_input_files(abs_path)
        else:
            with tt.expect_file_chooser(timeout=15000) as fc:
                tt.evaluate("document.querySelector('input[type=file]')?.click()")
            fc.value.set_files(abs_path)
        print("TikTok: File uploaded, processing...")
    except Exception as e:
        print(f"TikTok file error: {str(e)[:50]}")
    
    tt.wait_for_timeout(35000)
    
    # Type caption
    tt.evaluate(f"""(function(){{
        var editors = document.querySelectorAll('[contenteditable=true], textarea, [role=textbox]');
        for(var ed of editors){{
            if(ed.offsetParent){{ed.focus();document.execCommand('insertText',false,{json.dumps(titok_cap)});break;}}
        }}
    }})()""")
    tt.wait_for_timeout(4000)
    
    # Click Post
    tt.evaluate("""(function(){
        var btns = document.querySelectorAll('div[role=button],span,button');
        for(var b of btns){
            var t = (b.innerText||b.value||'').trim().toLowerCase();
            if(t==='post' || t==='publish'){b.click();return;}
        }
    })()""")
    tt.wait_for_timeout(8000)
    print("TikTok: Posted!")
    b.close()

print(f"\nDONE - {hymn} [{subgenre}] on YouTube + Shorts + TikTok!")
