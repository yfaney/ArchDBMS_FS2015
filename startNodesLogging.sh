#!/bin/bash



for dest in $(<nodelist.txt); do
   echo "Starting server program on $dest ..."
   ssh -iid_rsa_dbms2 umkc_yjang@${dest} /home/umkc_yjang/startServer.sh &

for dest in $(<nodelist.txt); do
   echo "Running client program on $dest ..."
   ssh -iid_rsa_dbms2 umkc_yjang@${dest} python /home/umkc_yjang/RTTMeasurer.py

for dest in $(<nodelist.txt); do
   echo "Killing server program on $dest ..."
   ssh -iid_rsa_dbms2 umkc_yjang@${dest} /home/umkc_yjang/stopServer.sh &

FORNOW=$(date +%Y-%m-%d_%H%M%S)

for dest in $(<nodelist.txt); do
   echo "Getting logs from $dest ..."
   scp -iid_rsa_dbms2 umkc_yjang@${dest}:/home/umkc_yjang/resultLog.csv ~/logs/result_${dest}_${FORNOW}.csv

