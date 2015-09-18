#!/bin/bash
#echo "Killing server..."
#kill $(ps -e | grep nohup | awk '{print $1}')
kill $(ps -e | grep simple_client | awk '{print $1}')
