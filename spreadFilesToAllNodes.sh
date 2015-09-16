#!/bin/bash

for dest in $(<$1); do
   echo "Copy files to $dest ..."
   ssh -iid_rsa_dbms2 umkc_yjang@${dest} /home/umkc_yjang/stopServer.sh
   scp -iid_rsa_dbms2 /tmp/file* $1 ./RTTMeasurer.py ./simple_server ./*.sh umkc_yjang@${dest}:/home/umkc_yjang

done
