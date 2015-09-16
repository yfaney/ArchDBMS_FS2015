#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#define NO_OF_NODES 60
#define NO_OF_FILES 5
using namespace std;

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
        cout<<"Test!"<<endl;
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

const char* NODE_LIST = "nodelist.txt";
const string FILE_LIST[] = {"file_32B", "file_1K", "file_256K", "file_512K", "file_1M"};
const char* RESULT_FILE = "resultLog.csv";
const bool DEBUG = true;

int main ( int argc, char* argv[] )
{
  vector<string> addrList = getAddrList(argv[1]);
  for(vector<string>::iterator it = addrList.begin(); it != addrList.end(); ++it){
    try{
      ClientSocket client_socket ( *it, 55700 );
      string reply;
      try{
        int i=0;
        int j=0;
        for(i=0; i<4; i++){
          for(j=0; j<NO_OF_FILES; j++){
  	    client_socket << FILE_LIST[j];
  	    client_socket >> reply;
          }
        }
        for(j=0; j<NO_OF_FILES; j++){
          time_t t_start;
          time_t t_end;
          time(&t_start);
	  client_socket << FILE_LIST[j];
	  client_socket >> reply;
          time(&t_end);
          double delay = difftime(t_end, t_start);
          if(DEBUG) cout << "We received this response from the server:\n\"" << reply << "\"\n";;
          if(DEBUG) cout << "Length: " << reply.length() << endl;
          if(DEBUG) cout << "Delay: " << delay << endl;
        }
      }
      catch ( SocketException& ) {}
    }
    catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }
  }
  return 0;
}
