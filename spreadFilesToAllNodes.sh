#!/bin/bash

# Requires the arguments for nodelist and retry list
if [ "$#" -ne 2 ]; then
    echo "usage: ./spreadFilesToAllNodes.sh nodelist.txt retry.txt"
    exit
fi

# Stops server process remotely in Planetlab nodes to avoid inconcurrent process
./remote_stopServer.sh $1

# The remote_stopServer.sh script runs remotely simultaneously at once. It takes about 2 min so we wait 3 min to finish every ssh commands finishes
echo "Waiting 3min until every nodes stop server..."
sleep 3m

# Stops server process one more time to work more safely
./remote_stopClient.sh $1

echo "Waiting 3min until every nodes stop client..."
sleep 3m

# Now spread all required files(sh files, client program, server program, testing files(32b, 1kb, 256kb, 512kb, 1mb)) to all Planetlab nodes.
# If file transferring failed for some reason(Because Planetlab connection quality is very low and unstable), saves the node into failed list
# And retry the file transfer again for future iteration.
for dest in $(<$2); do
   echo "Copy files to $dest ..."
   scp -iid_rsa_dbms2 -oConnectTimeout=45 ./file* $1 ./dfm ./simple_server ./simple_client ./local_*.sh umkc_yjang@${dest}:/home/umkc_yjang
   rcode=$?
   if test $rcode -ne 0; then
      echo "$dest" >> failedNodes.txt
   fi
done
#echo "Waiting 5min until every node gets all files..."
#sleep 5m
echo "Done."
