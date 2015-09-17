#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <omp.h>
#include <stdlib.h>
#include <netdb.h>
#define NO_OF_NODES 60
#define NO_OF_FILES 5
using namespace std;

int hostname_to_ip(char *  , char *);
vector<string> getAddrList(const char*);
void writeLogList(const char*, vector<string>);
string recvContents(ClientSocket*);
vector<string> getTestList();

const char* NODE_LIST = "nodelist.txt";
const string FILE_LIST[] = {"file_32B", "file_1K", "file_256K", "file_512K", "file_1M"};
const char* RESULT_FILE = "resultLog.csv";
const bool DEBUG = false;

int main ( int argc, char* argv[] )
{
  char lhost[256];
  lhost[255] = '\0';
  gethostname(lhost, 255);
  string myhost(lhost);
//  cout << "Hostname:" << myhost <<endl;
//  struct hostent* h;
//  h = gethostbyname(lhost);
//  cout << "Hostname:" << h->h_name;
  char ip[15];
  char hostName[256];
  vector<string> addrList = getAddrList(argv[1]);
//  vector<string> addrList = getTestList();
  vector<string> logList;
  for(vector<string>::iterator it = addrList.begin(); it != addrList.end(); ++it){
    if(myhost.compare(*it) == 0) continue;
    try{
      strcpy(hostName, (*it).c_str());
      cout << "Connecting to "<<hostName<< "..." <<flush;
      hostname_to_ip(hostName, ip);
      ClientSocket client_socket ( ip, 55700 );
      cout << "Connected. Measuring RTT..." << flush;
      string reply;
      try{
        int i=0;
        int j=0;
        for(i=0; i<4; i++){
          for(j=0; j<NO_OF_FILES; j++){
  	    client_socket << FILE_LIST[j];
            reply = recvContents(&client_socket);
          }
        }
        for(j=0; j<NO_OF_FILES; j++){
          if(DEBUG) cout << "Req:" << FILE_LIST[j] << endl;
          double t_start = omp_get_wtime();
	  client_socket << FILE_LIST[j];
          reply = recvContents(&client_socket);
          double t_end = omp_get_wtime();
          double delay = t_end - t_start;
//          if(DEBUG) cout << "We received this response from the server:\n" << reply << endl;
          if(DEBUG) cout << "Received: " << reply.length() << '\t' << "Delay: " << delay << endl;
          stringstream ss;
          ss << "\"" << myhost <<"\",\"" << *it << "\"," << reply.length() << "," << delay;
          logList.push_back(ss.str());
        }
        cout << "Measured." <<endl << flush;
      }
      catch ( SocketException& ) {}
    }
    catch ( SocketException& e )
    {
      cout << endl << "Exception was caught:" << e.description() << "\n";
    }
  }
  if(logList.size() > 0){
    //writeLogList(RESULT_FILE, logList);
    for(vector<string>::iterator it = logList.begin(); it != logList.end(); ++it){
      cout << *it << endl;
    }
  }
  return 0;
}

string recvContents(ClientSocket* sk){
  string result;
  string buff;
  while(true){
    *sk >> buff;
    if(buff.find(" ") == string::npos){
      result.append(buff);
    }
    else{
      result.append(buff.substr(0, buff.find(" ")));
//      cout << result.length() << "total received."<<endl;
      return result;
    }
  }
}
vector<string> getTestList(){
  vector<string> list;
  list.push_back("localhost");
  return list;
}

/*
    Get ip from domain name
 */

int hostname_to_ip(char * hostname , char* ip)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ( (he = gethostbyname( hostname ) ) == NULL)
    {
        // get the host info
        herror("gethostbyname");
        return 1;
    }

    addr_list = (struct in_addr **) he->h_addr_list;

    for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;
    }
    return 1;
}

vector<string> getAddrList(const char* filePath){
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
//        cout<<"Test!"<<endl;
        return addrList;
}

void writeLogList(const char* filePath, vector<string> logList){
        ofstream myfile;
        myfile.open(filePath);
        if(myfile.is_open()){
                for(vector<string>::iterator it = logList.begin(); it != logList.end(); ++it){
                        myfile << *it << '\n';
                }
                myfile.close();
        }else cout << "Unable to open file!";
}
