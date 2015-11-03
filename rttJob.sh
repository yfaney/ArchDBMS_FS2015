#!/bin/bash

# Move failed node list to retry list
mv failedNode.txt retry.txt
# Spread files to all Planetlab nodes in nodelist.txt, if any nodes failed, it will saved into retry.txt for future work
./spreadFilesToAllNodes.sh nodelist.txt retry.txt
# Start RTT Measurement remotely in all the Planet nodes in nodelist.txt and collect the results
./startNodesLogging.sh nodelist.txt
# clean the results from remote nodes because we already got the result from startNodesLogging.sh script
./remote_clean.sh nodelist.txt >> ~/logs/remote_clean.log 2>&1 &
# Concatenate all logs into one file and email it to team members
../concatLogAndEmail.sh

sleep 30

FINT=$(date +%Y-%m-%d_%H%M%S)
echo "Finished on $FINT."
