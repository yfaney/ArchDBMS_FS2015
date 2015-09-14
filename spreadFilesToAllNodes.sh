#!/bin/bash

for dest in $(<nodelist.txt); do
   echo "Copy files to $dest ..."
   scp -iid_rsa_dbms2 /tmp/file* nodelist.txt ./RTTMeasurer.py ./simple_server ./*.sh umkc_yjang@${dest}:/home/umkc_yjang

done
