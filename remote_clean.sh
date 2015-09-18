#!/bin/bash
if [ "$#" -ne 1 ]; then
    echo "usage ./cleanRemote.sh nodelist.txt"
    exit
fi

for dest in $(<$1); do
   echo "Delete everything from $dest ..."
   ssh -iid_rsa_dbms2 umkc_yjang@${dest} rm -rf /home/umkc_yjang/*.csv
done


