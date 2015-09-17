#!/bin/bash
if [ "$#" -ne 1 ]; then
    echo "usage: ./startNodesLogging.sh nodelist.txt"
    exit
fi
for dest in $(<$1); do
   echo "Starting server program on $dest ..."
   ssh -iid_rsa_dbms2 umkc_yjang@${dest} /home/umkc_yjang/startServer.sh &
done
echo "Wait 2.5 min so that every server program starts..."
sleep 2.5m
for dest in $(<$1); do
   echo "Running client program on $dest ..."
#   ssh -iid_rsa_dbms2 -oConnectTimeout=60 umkc_yjang@${dest} python /home/umkc_yjang/RTTMeasurer.py $1
   ssh -iid_rsa_dbms2 -oConnectTimeout=60 umkc_yjang@${dest} /home/umkc_yjang/simple_client $1
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


