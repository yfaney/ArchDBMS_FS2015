#!/bin/bash

for dest in $(<$1); do
   echo "Killing python on $dest ..."
   ssh -iid_rsa_dbms2 -oConnectTimeout=60 umkc_yjang@${dest} /home/umkc_yjang/stopPython.sh &
done
