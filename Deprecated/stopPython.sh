#!/bin/bash
echo "Killing server..."
#kill $(ps -e | grep nohup | awk '{print $1}')
kill $(ps -e | grep RTTMeasurer.py | awk '{print $1}')
