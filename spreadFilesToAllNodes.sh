#!/bin/bash

for dest in $(<nodelist.txt); do
  scp /tmp/file_* ${dest}:/home/umkc_yjang

done
