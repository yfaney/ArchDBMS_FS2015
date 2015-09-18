#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "usage: ./spreadFilesToAllNodes.sh nodelist.txt"
    exit
fi

for dest in $(<$1); do
   echo "Killing server on $dest ..."
   ssh -iid_rsa_dbms2 umkc_yjang@${dest} /home/umkc_yjang/stopServer.sh &
done
echo "Waiting 3min until every nodes start server..."
sleep 3m
for dest in $(<$1); do
   echo "Copy files to $dest ..."
#   scp -iid_rsa_dbms2 -oConnectTimeout=60 ./file* $1 ./RTTMeasurer.py ./simple_server ./*.sh umkc_yjang@${dest}:/home/umkc_yjang &
   scp -iid_rsa_dbms2 -oConnectTimeout=60 ./file* $1 ./dfm ./simple_server ./simple_client ./*.sh umkc_yjang@${dest}:/home/umkc_yjang &
done
echo "Waiting 4min until every nodes get all files..."
sleep 4m
echo "Done."
