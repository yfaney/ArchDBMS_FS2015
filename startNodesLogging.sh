#!/bin/bash

# Requires the arguments for nodelist
if [ "$#" -ne 1 ]; then
    echo "usage: ./startNodesLogging.sh nodelist.txt"
    exit
fi

# Starts server process remotely. It runs simultaneously using background process
./remote_startServer.sh $1
echo "Wait 5 min so that every server gets started..."
sleep 5m

# Starts client process remotely. It runs simultaneously using background process 
for dest in $(<$1); do
   echo "Running client program on $dest ..."
#   ssh -iid_rsa_dbms2 -oConnectTimeout=60 umkc_yjang@${dest} python /home/umkc_yjang/RTTMeasurer.py $1
#   ssh -iid_rsa_dbms2 -oConnectTimeout=60 umkc_yjang@${dest} /home/umkc_yjang/simple_client /home/umkc_yjang/$1 /home/umkc_yjang/resultLog.csv >> ~/logs/client_log_${dest}.log 2>&1 &
   ssh -iid_rsa_dbms2 -oConnectTimeout=60 umkc_yjang@${dest} /home/umkc_yjang/local_startClient.sh &
done

# Wait until every client process finishes. The longest duration we observed was 2.5 hours so we wait 3.5 hours which is safely enough
echo "Wait 210 min so that every server gets results..."
FROMHERE=210
for ((i=FROMHERE; i>=1; i--))
do
    echo "$i min remains..."
    sleep 1m
done

# Stops server process remotely. It runs simultaneously using background process
./remote_stopServer.sh $1

# Get logs from every planetlab nodes
./getLogs.sh $1
