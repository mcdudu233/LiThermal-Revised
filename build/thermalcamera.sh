if [ -f /mnt/UDISK/LiThermal ]; then
    while true; do
        chmod +x /mnt/UDISK/LiThermal
      	chmod +x /mnt/UDISK/BSOD
        if /mnt/UDISK/LiThermal; then
            echo "[Process exited normally]"
            break;
        elif [ -f /tmp/poweroff ]; then
            echo "[Power off]"
            break;
        elif [ -f /tmp/debug ]; then
            echo "[Debug mode detected]"
            /mnt/UDISK/BSOD
            break;
        else
            /mnt/UDISK/BSOD
            sleep 1
        fi
    done
fi
