#!/bin/bash
if [ "$#" -ne 1 ]; then
    echo "usage: ./startNodesLogging.sh nodelist.txt"
    exit
fi

./remote_startServer.sh $1
echo "Wait 5 min so that every server gets started..."
sleep 5m

for dest in $(<$1); do
   echo "Running client program on $dest ..."
#   ssh -iid_rsa_dbms2 -oConnectTimeout=60 umkc_yjang@${dest} python /home/umkc_yjang/RTTMeasurer.py $1
#   ssh -iid_rsa_dbms2 -oConnectTimeout=60 umkc_yjang@${dest} /home/umkc_yjang/simple_client /home/umkc_yjang/$1 /home/umkc_yjang/resultLog.csv >> ~/logs/client_log_${dest}.log 2>&1 &
   ssh -iid_rsa_dbms2 -oConnectTimeout=60 umkc_yjang@${dest} /home/umkc_yjang/local_startClient.sh &
done

echo "Wait 210 min so that every server gets results..."
FROMHERE=210
for ((i=FROMHERE; i>=1; i--))
do
    echo "$i min remains..."
    sleep 1m
done

./remote_stopServer.sh $1

./getLogs.sh $1
