#!/bin/bash

#Making files: 32B, 1KB, 512KB, 1MB, 1GB
#or 32B, 1KB, 256KB, 512KB, 1MB

echo "Making files: 1GB..."
#dd if=/dev/zero of=/tmp/file_1G  bs=1G  count=1
./dfm 1G
