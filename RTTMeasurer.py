#!/usr/bin/python
import datetime
import gc, time
import socket
import sys
import csv

TEST_FILES = [{"name" : "file_32B", "size" : 32},
                {"name" : "file_1K","size" : 1024},
                {"name" : "file_256K","size" : 256 * 1024},
                {"name" : "file_512K","size" : 512 * 1024},
                {"name" : "file_1M","size" : 1024 * 1024}]

MAX_LEN = 1048576
BLOCK_SIZE = 2048
DEBUG = False
#At first, get the current node address

MyAddress = socket.gethostname()

# Read node list from a file
f = open(sys.argv[1], 'r')
rawList = f.readlines()
f.close()

nodeList = []

for item in rawList:
    if item.strip() != MyAddress:
        #print item.strip()
        nodeList.append(item.strip())

print "Node Size: %d" % len(nodeList)

def receive(sock):
        chunks = []
#        bytes_recd = 0
#        running = True
        while True:
            chunk = sock.recv(BLOCK_SIZE)
            if chunk[len(chunk)-1:] == ' ':
                chunks.append(chunk[:len(chunk)-1])
                break
            else:
                chunks.append(chunk)
        return ''.join(chunks)

#Log Structure: [ Source, Target, TImestamp, FileSize, Delay ]

resultLog = []

for node_list in nodeList:
    #sk.connect(("192.168.0.16", 55700))
    print ("%s - %s" % (MyAddress, node_list))
    node = socket.gethostbyname(node_list)
    try:
        #create an INET, STREAMing socket
        sk = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sk.settimeout(60.0)
        sk.connect((node, 55700))
        for file in TEST_FILES:
            if DEBUG:
                print file["name"]
            for i in range(1,4):
                sk.send(file["name"])
                recvd = receive(sk)
                #print recvd
                #print (len(recvd))
            startTime = datetime.datetime.now()
            sk.send(file["name"])
            recvd = receive(sk)
            endTime = datetime.datetime.now()
            if 'File was not open' == recvd[:len('File was not open')]:
                print "File Error: File was not open"
            else:
                td = endTime - startTime
                delay = td.seconds + float(td.microseconds/1000000.0)
                #print recvd
                if(DEBUG):
                    print ("Bytes received: %d" %len(recvd))
                    print ("Delay: %f ms..." % delay)
                resultLog.append('"%s","%s","%s",%d,%f\n' % (MyAddress, node_list, startTime, file["size"], delay))
        del recvd
        sk.close()
        del sk
        # GC and Wait 10sec to GC working
        gc.enable()
        time.sleep(10)
    except Exception,e:
        print ("Measuring Error :%s" % str(e))

#with open("resultLog.csv", "wb") as f:
#    writer = csv.writer(f)
#    writer.writerows(resultLog)
try:
    f = open("/home/umkc_yjang/resultLog.csv", 'w')
    f.writelines(resultLog)
    f.close()
except Exception,e:
    print(str(e))
#for line in resultLog:
#    f.write
print ("Done.")
