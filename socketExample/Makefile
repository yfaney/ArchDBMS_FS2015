# Makefile for the socket programming example
#
socklibs = -lnsl -lpthread
simple_server_objects = ServerSocket.o Socket.o simple_server_main.o


all : simple_server

simple_server: $(simple_server_objects)
	g++ -o simple_server $(socklibs) $(simple_server_objects)



Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
simple_server_main: simple_server_main.cpp


clean:
	rm -f *.o simple_server simple_client
