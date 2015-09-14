#!/usr/bin/python
import datetime
import socket
import sys

NODE_LIST_FILE = ["192.168.0.16"]
TEST_FILES = ["file_32B", "file_1K", "file_256K","file_512K", "file_1M"]

MAX_LEN = 1048576
BLOCK_SIZE = 2048
DEBUG = True

# Read node list from a file
f = open("nodelist.txt")
nodeList = f.readlines()

for item in nodeList:
    print item.strip()
    print socket.gethostbyname(item.strip())
    

print len(nodeList)

def receive(sock):
        chunks = []
        bytes_recd = 0
        running = True
        while running:
            chunk = sock.recv(BLOCK_SIZE)
            if ' ' in chunk:
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


for node_list in nodeList:
    #sk.connect(("192.168.0.16", 55700))
	sk.connect(socket.gethostbyname(node_list.strip()),55700)
    for fileName in TEST_FILES:
        for i in range(1,4):
            sk.send(fileName)
            recvd = receive(sk)
            #print recvd
            #print (len(recvd))
        sk.send(fileName)
        startTime = datetime.datetime.now()
        recvd = receive(sk)
        endTime = datetime.datetime.now()
        td = endTime - startTime
        delay = td.seconds + float(td.microseconds/1000000.0)
        #print recvd
        if(DEBUG):
            print (len(recvd))
            print delay
    sk.close()
