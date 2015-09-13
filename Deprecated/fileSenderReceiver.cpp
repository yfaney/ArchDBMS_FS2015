#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define NO_OF_NODES 60

using namespace std;

//#define NUM_THREADS     60

const char* AVG_FILE_PATH = "address.data";

vector<string> getAddressList(const char* filePath){
	string addresses[NO_OF_NODES];
	string line;
	int index = 0;
	vector<string> addrList;
	ifstream myfile;
	myfile.open(filePath);
	if(myfile.is_open()){
		while(getline(myfile, line)){
			addresses[index] = line;
			++index;
		}
		myfile.close();
		addrList.assign(addresses, addresses + index);
	}
	else{
		ofstream newfile;
		newfile.open(filePath);
		if(newfile.is_open()){
			myfile.close();
		}else cout << "Unable to open file during making!";
	}
	return addrList;
}

int downloadFilesFromServer(vector<string> addressList){
	for(vector<string>::iterator it = addressList.begin(); it != addressList.end(); ++it){
		myfile << *it << '\n';
	}
}

struct thread_data{
   int  thread_id;
   string message;
};

struct socket_data{
	string ip;
	string port;
	string filename
}

void *PrintHello(void *threadarg)
{
   struct thread_data *my_data;

   my_data = (struct thread_data *) threadarg;

   cout << "Thread ID : " << my_data->thread_id ;
   cout << " Message : " << my_data->message << endl;

   pthread_exit(NULL);
}

void *ServerModule(void *threadarg){
	struct thread_data *my_data;

	my_data = (struct thread_data *) threadarg;

	cout << "Thread ID : " << my_data->thread_id ;
	cout << " Message : " << my_data->message << endl;
	
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, 
	(struct sockaddr *) &cli_addr, 
	&clilen);
	if (newsockfd < 0) 
	error("ERROR on accept");
	bzero(buffer,256);
	n = read(newsockfd,buffer,255);
	if (n < 0) error("ERROR reading from socket");
	printf("Here is the message: %s\n",buffer);
	n = write(newsockfd,"I got your message",18);
	if (n < 0) error("ERROR writing to socket");
	close(newsockfd);
	close(sockfd);

	
	pthread_t serverThread[NO_OF_NODES];
	int i;
	for(i = 0; i <= NO_OF_NODES; i++){
		wait();
		rc = pthread_create(&serverThread[i], NULL, ServerModule, (void*)&td);
	}
	pthread_exit(NULL);
}

void *send_File_To_Client(void *socket_arg){
	struct socket_data *my_data;
	my_data = (struct socket_data *) socket_arg;
	string target_ip = my_data->ip;
	string target_port = my_data->port;
	strubg filename = my_data->filename;

	ofstream myfile;
	
	string filePath = target_address + "_" + file_name;
	myfile.open(filePath);
	if(myfile.is_open()){
		while(read){}
			myfile << read;
		}
		myfile.close();
	}else cout << "Unable to open file!";
}


int main (int argc, char** argv)
{
/*
	pthread_t threads[NUM_THREADS];
   struct thread_data td[NUM_THREADS];
   int rc;
   int i;

   for( i=0; i < NUM_THREADS; i++ ){
      cout <<"main() : creating thread, " << i << endl;
      td[i].thread_id = i;
      td[i].message = oss.str();
      rc = pthread_create(&threads[i], NULL,
                          PrintHello, (void *)&td[i]);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
*/
	pthread_t serverThread;
	struct thread_data td;
	int rc;
	rc = pthread_create(&serverThread, NULL, ServerModule, (void*)&td);
	if (rc){
		cout << "Error:unable to create thread," << rc << endl;
		exit(-1);
	}
	/* From here - Client Part!!! */
	pthread_exit(NULL);
	return 0;
}
