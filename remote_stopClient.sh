#!/bin/bash
if [ "$#" -ne 1 ]; then
    echo "usage: ./remote_stopClient.sh nodelist.txt"
    exit
fi
for dest in $(<$1); do
   echo "Stopping client program on $dest ..."
#   kill $(ps -e | grep simple_client | awk '{print $1}')
   ssh -iid_rsa_dbms2 umkc_yjang@${dest} /home/umkc_yjang/local_stopClient.sh &
done

