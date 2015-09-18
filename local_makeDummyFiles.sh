#!/bin/bash

#Making files: 32B, 1KB, 512KB, 1MB, 1GB
#or 32B, 1KB, 256KB, 512KB, 1MB

echo "Making files: 32B..."
#dd if=/dev/zero of=/tmp/file_32B  bs=1  count=32
./dfm 32B
echo "Making files: 1KB..."
#dd if=/dev/zero of=/tmp/file_1K  bs=1K  count=1
./dfm 1K
echo "Making files: 256KB..."
#dd if=/dev/zero of=/tmp/file_256K  bs=1K  count=256
./dfm 256K
echo "Making files: 512KB..."
#dd if=/dev/zero of=/tmp/file_512K  bs=1K  count=512
./dfm 512K
echo "Making files: 1MB..."
#dd if=/dev/zero of=/tmp/file_1M  bs=1M  count=1
./dfm 1M
#echo "Making files: 1GB..."
#dd if=/dev/zero of=/tmp/file_1KB  bs=1G  count=1
