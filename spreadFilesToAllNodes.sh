#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "usage: ./spreadFilesToAllNodes.sh nodelist.txt"
    exit
fi

./remote_stopServer.sh $1
echo "Waiting 2min until every nodes start server..."
sleep 2m

./remote_stopClient.sh $1
echo "Waiting 2min until every nodes start server..."
sleep 2m

for dest in $(<retry.txt); do
   echo "Copy files to $dest ..."
#   scp -iid_rsa_dbms2 -oConnectTimeout=60 ./file* $1 ./RTTMeasurer.py ./simple_server ./*.sh umkc_yjang@${dest}:/home/umkc_yjang &
   scp -iid_rsa_dbms2 -oConnectTimeout=45 ./file* $1 ./dfm ./simple_server ./simple_client ./local_*.sh umkc_yjang@${dest}:/home/umkc_yjang
   rcode=$?
   if test $rcode -ne 0; then
      echo "$dest" >> failedNodes.txt
   fi
done
echo "Waiting 5min until every node gets all files..."
sleep 5m
echo "Done."
