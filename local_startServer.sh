#!/bin/sh

echo "Running Server..."

nohup /home/umkc_yjang/simple_server 55700 >> /home/umkc_yjang/server_log.log 2>&1 &
