#!/bin/bash
if [ "$#" -ne 1 ]; then
    echo "usage: ./deleteLogsRemote.sh nodelist.txt"
    exit
fi
for dest in $(<$1); do
   echo "Deleting logs on $dest ..."
   ssh -iid_rsa_dbms2 umkc_yjang@${dest} rm /home/umkc_yjang/resultLog.csv &
done


