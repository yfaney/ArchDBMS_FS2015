#!/bin/bash

for dest in $(<$1); do
   echo "Starting server program on $dest ..."
   ssh -iid_rsa_dbms2 umkc_yjang@${dest} /home/umkc_yjang/startServer.sh &
done
for dest in $(<$1); do
   echo "Running client program on $dest ..."
   ssh -iid_rsa_dbms2 umkc_yjang@${dest} python /home/umkc_yjang/RTTMeasurer.py $1
done
for dest in $(<$1); do
   echo "Killing server program on $dest ..."
   ssh -iid_rsa_dbms2 umkc_yjang@${dest} /home/umkc_yjang/stopServer.sh &
done

FORNOW=$(date +%Y-%m-%d_%H%M%S)

for dest in $(<$1); do
   echo "Getting logs from $dest ..."
   scp -iid_rsa_dbms2 umkc_yjang@${dest}:/home/umkc_yjang/resultLog.csv ~/logs/result_${dest}_${FORNOW}.csv
done


