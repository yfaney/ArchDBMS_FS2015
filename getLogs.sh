#!/bin/bash

# Requires the arguments for nodelist and retry list
if [ "$#" -ne 1 ]; then
    echo "usage ./getLogs.sh nodelist.txt"
    exit
fi
FORNOW=$(date +%Y-%m-%d_%H%M%S)


# Retrieves the result and logs from the Planetlab nodes
for dest in $(<$1); do
   echo "Getting logs from $dest ..."
   scp -iid_rsa_dbms2 umkc_yjang@${dest}:/home/umkc_yjang/resultLog.csv /home/pi/logs/result_${dest}_${FORNOW}.csv
   scp -iid_rsa_dbms2 umkc_yjang@${dest}:/home/umkc_yjang/client_log.log /home/pi/logs/log_${dest}_${FORNOW}.log
done


