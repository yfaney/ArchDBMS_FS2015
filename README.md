# ArchDBMS_FS2015
Arch. of DBMS Project repository for FS2015 at UMKC

How To Use:

1. Run "makeFileList" script: Make dummy files which size are 32b, 1kb, 256kb, 512kb, 1mb
<h4>$ ./makeDummyFiles.sh</h4>

2. Run "spreadFilesToAllNodes.sh" script : spread all files to our all 60 nodes
<h4>$ ./spreadFilesToAllNodes.sh</h4>

3. Run "startNodesLogging.sh" script : It remotely runs all server program on 60 nodes and run client program by turns on 60 nodes, finally gets all logs
<h4>$ ./startNodesLogging.sh</h4>

