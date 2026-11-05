#!/bin/bash
D=/root/backups/aimoneymachine-20260916-164843
echo "=== what is actually in the 3.0G archive? ==="
tar -tzvf "$D/opt-aimoneymachine.tar.gz" 2>/dev/null | sort -k3 -n -r | head -8 | awk '{printf "  %8.1f MB  %s\n", $3/1048576, $6}'
echo
echo "=== building model-free archive (code + DBs + logs) ==="
tar -C /opt -czf "$D/opt-aimoneymachine-nomodel.tar.gz" \
	--exclude='aimoneymachine/venv' \
	--exclude='__pycache__' \
	--exclude='*.pyc' \
	--exclude='*.gguf' \
	aimoneymachine 2>&1 | tail -2
echo "  -> $(du -h "$D/opt-aimoneymachine-nomodel.tar.gz" | cut -f1)"
tar -tzf "$D/opt-aimoneymachine-nomodel.tar.gz" >/dev/null 2>&1 && echo "  archive OK" || echo "  ARCHIVE CORRUPT"
cd "$D" && sha256sum opt-aimoneymachine-nomodel.tar.gz >>checksums.sha256
echo "  checksum appended"
echo
echo "=== key data files inside ==="
tar -tzvf "$D/opt-aimoneymachine-nomodel.tar.gz" 2>/dev/null | grep -E "\.db$|\.log$|\.json$" | sort -k3 -n -r | head -8 | awk '{printf "  %8.2f MB  %s\n", $3/1048576, $6}'
