#!/bin/bash
echo "Killing server..."
kill $(ps -e | grep nohup | awk '{print $1}')
