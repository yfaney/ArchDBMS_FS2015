#!/bin/bash

for dest in $(<$1); do
   echo "Copy files to $dest ..."
   ssh -iid_rsa_dbms2 umkc_yjang@${dest} python --version

done
