#!/bin/bash
R=/srv/www/robertpelloni.com
V=$R/wp-content/uploads/untitled.mp4

echo "=== probe ==="
ffprobe -v error -select_streams v:0 \
	-show_entries stream=width,height,duration,codec_name,r_frame_rate \
	-show_entries format=duration,size,bit_rate \
	-of default=noprint_wrappers=1 "$V" 2>&1

DUR=$(ffprobe -v error -show_entries format=duration -of csv=p=0 "$V" 2>/dev/null)
echo "duration seconds: $DUR"
GRAB=$(awk -v d="$DUR" 'BEGIN{ t=d*0.15; if (t<1) t=1; if (t>8) t=8; printf "%.2f", t }')
echo "grabbing frame at ${GRAB}s"
echo "$GRAB" >/tmp/rp_grab_sec

echo
echo "=== generate 16:9 thumbnail (blurred bg + centred vertical video) ==="
cd /tmp
ffmpeg -y -v error -ss "$GRAB" -i "$V" \
	-filter_complex "[0:v]scale=1280:720:force_original_aspect_ratio=increase,crop=1280:720,gblur=sigma=28,eq=brightness=-0.12[bg];[0:v]scale=-1:680[fg];[bg][fg]overlay=(W-w)/2:(H-h)/2,format=yuvj420p" \
	-frames:v 1 /tmp/untitled-poster.jpg 2>&1
ls -lh /tmp/untitled-poster.jpg
identify /tmp/untitled-poster.jpg 2>/dev/null || ffprobe -v error -show_entries stream=width,height -of csv=p=0 /tmp/untitled-poster.jpg
