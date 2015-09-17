#!/bin/bash

for dest in $(<$1); do
   echo "Killing server on $dest ..."
   ssh -iid_rsa_dbms2 umkc_yjang@${dest} /home/umkc_yjang/stopServer.sh &
done
echo "Waiting 2.5min until every nodes start server..."
sleep 2.5m
for dest in $(<$1); do
   echo "Copy files to $dest ..."
   scp -iid_rsa_dbms2 -oConnectTimeout=60 ./file* $1 ./RTTMeasurer.py ./simple_server ./*.sh umkc_yjang@${dest}:/home/umkc_yjang &
done
echo "Waiting 4min until every nodes get all files..."
sleep 4m
echo "Done."
