#!/bin/bash
if [ "$#" -ne 1 ]; then
    echo "usage: ./stopServerRemote.sh nodelist.txt"
    exit
fi
for dest in $(<$1); do
   echo "Starting server program on $dest ..."
   ssh -iid_rsa_dbms2 umkc_yjang@${dest} /home/umkc_yjang/local_stopServer.sh &
done

