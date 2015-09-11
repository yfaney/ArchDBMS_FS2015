#!/bin/bash

#Making files: 32B, 1KB, 512KB, 1MB, 1GB
#or 32B, 1KB, 256KB, 512KB, 1MB

echo "Making files: 32B..."
dd if=/dev/zero of=/tmp/file_32B  bs=1  count=1
echo "Making files: 1KB..."
dd if=/dev/zero of=/tmp/file_1KB  bs=1K  count=1
echo "Making files: 512KB..."
dd if=/dev/zero of=/tmp/file_512KB  bs=1K  count=512
echo "Making files: 1MB..."
dd if=/dev/zero of=/tmp/file_1MB  bs=1M  count=1
echo "Making files: 1GB..."
dd if=/dev/zero of=/tmp/file_1KB  bs=1G  count=1

echo "Sending them to all nodes..."


for dest in $(<nodelist.txt); do
  scp /tmp/file_32B ${dest}:remote/path/

done
