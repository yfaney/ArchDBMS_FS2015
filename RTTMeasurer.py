#!/usr/bin/python
import datetime
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
DEBUG = True
#At first, get the current node address

MyAddress = socket.gethostname()

# Read node list from a file
f = open("nodelist.txt")
rawList = f.readlines()

nodeList = []

for item in rawList:
    if item != MyAddress:
        print item.strip()
        nodeList.append(socket.gethostbyname(item.strip()))

print "Node Size: %d" % len(nodeList)

def receive(sock):
        chunks = []
        bytes_recd = 0
#        running = True
        while True:
            chunk = sock.recv(BLOCK_SIZE)
            if chunk[len(chunk)-1:] == '\n':
                chunks.append(chunk[:len(chunk)-1])
                break
            else:
                chunks.append(chunk)
        return ''.join(chunks)

#create an INET, STREAMing socket
sk = socket.socket(
    socket.AF_INET, socket.SOCK_STREAM)
#now connect to the web server on port 80
# - the normal http port

#Log Structure: [ Source, Target, TImestamp, FileSize, Delay ]

resultLog = []

for node_list in nodeList:
    #sk.connect(("192.168.0.16", 55700))
    sk.connect(node_list,55700)
    for file in TEST_FILES:
        for i in range(1,4):
            sk.send(file["name"])
            recvd = receive(sk)
            #print recvd
            #print (len(recvd))
        sk.send(file["name"])
        startTime = datetime.datetime.now()
        recvd = receive(sk)
        endTime = datetime.datetime.now()
        if 'File was not open' in recvd[len('File was not open')]:
            print "File Error: File was not open"
        else:
            td = endTime - startTime
            delay = td.seconds + float(td.microseconds/1000000.0)
            #print recvd
            if(DEBUG):
                print (len(recvd))
                print delay
            resultLog.append([MyAddress, node_list, startTime, file["size"], delay])
    sk.close()

with open("resultLog.csv", "wb") as f:
    writer = csv.writer(f)
    writer.writerows(resultLog)
