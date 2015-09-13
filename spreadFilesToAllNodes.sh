#!/bin/bash

for dest in $(<nodelist.txt); do
  scp /tmp/file_32B ${dest}:remote/path/

done
