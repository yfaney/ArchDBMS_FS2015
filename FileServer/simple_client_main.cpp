#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
//#include <omp.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <netdb.h>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#define NO_OF_NODES 256
#define NO_OF_FILES 5

using namespace std;

int hostname_to_ip(string  , char *);
int mysleep(int );
// random generator function:
int myrandom (int i) { return rand()%i;}
void writeLogList(const char*, vector<string>);
void tuneNetwork(ClientSocket* );
vector<string> getAddrList(const char*);
vector<string> getTestList();
string recvContents(ClientSocket*);
string timeNow();
string getMyHostName();
double getTimeDiff(struct timeval , struct timeval );


const char* NODE_LIST = "/home/umkc_yjang/nodelist.txt";
const string FILE_LIST[] = {"file_32B", "file_1K", "file_256K", "file_512K", "file_1M"};
const char* RESULT_FILE = "/home/umkc_yjang/resultLog.csv";
const bool DEBUG = false;

int main ( int argc, char* argv[] )
{
  if(argc < 3){
    cout << "usage: " << argv[0] << " <NODE_LIST_FILE> <OUTPUT_LOG_FILE>" <<endl;
    return 1;
  }
  cout << "Current Time: " << timeNow() << endl;
  struct timeval t_start, t_end, pt_start, pt_end;
  string myhost = getMyHostName();
  char ip[15];
  vector<string> addrList = getAddrList(argv[1]);
//vector<string> addrList = getTestList();
//Shuffling the list
  srand ( unsigned ( time(0) ) );
  random_shuffle ( addrList.begin(), addrList.end(), myrandom);
  vector<string> logList;
  int progress = 1;
  int retryCount = 0;
  for(vector<string>::iterator it = addrList.begin(); it != addrList.end(); ++it){
// Retry up to 3 times to avoid some temporary problems
    if(retryCount > 0 && retryCount < 3){
      if(it != addrList.begin()) --it;
      cout << "Retry on " << *it << "after 3 seconds..." << endl;
      mysleep(3000);
    }else{
      retryCount = 0;
    }
    if(myhost.compare(*it) == 0) continue;
    try{
      cout << "I" << progress << ":Connecting:"<< *it << "." <<flush;
      hostname_to_ip(*it, ip);
      ClientSocket client_socket ( ip, 55700 );
      cout << "Connected." << flush;
      gettimeofday(&pt_start, NULL);
      string reply;
      try{
        int i=0;
        tuneNetwork(&client_socket);
// Now Real Measuring!! -Start
        string currTime = timeNow();
        cout << "Measuring RTT..." << flush;
        for(i=0; i<NO_OF_FILES; i++){
          if(DEBUG) cout << "Req:" << FILE_LIST[i] << endl;
          gettimeofday(&t_start, NULL);
	  client_socket << FILE_LIST[i];
          reply = recvContents(&client_socket);
          gettimeofday(&t_end, NULL);
          double delay = getTimeDiff(t_start, t_end);
          if(DEBUG) cout << "Received: " << reply.length() << '\t' << "Delay: " << delay << endl;
          stringstream ss;
          ss << "\"" << myhost    << "\",\"" << *it << "\","
             << "\"" << currTime <<  "\","   << reply.length()
             << ","  << delay;
          logList.push_back(ss.str());
        }
        gettimeofday(&pt_end, NULL);
        cout << "Done within " <<getTimeDiff(pt_start, pt_end)/1000 << "sec." << endl << flush;
        ++progress;
        retryCount = 0;
      }
      catch ( SocketException& e) {
        cout << endl << "Exception was caught during file receiving:" << e.description() << endl;
        ++retryCount;
      }
    }
    catch ( SocketException& e )
    {
      cout << endl << "Exception was caught:" << e.description() << endl;
      ++retryCount;
    }
  }
  if(logList.size() > 0){
    writeLogList(argv[2], logList);
    //printLogList(RESULT_FILE, logList);
  }
  cout << "Finished on " << timeNow() <<  endl;
  return 0;
}

void tuneNetwork(ClientSocket* sk){
  string reply;
  int i;
  int j;
  for(i=0; i<4; i++){
    for(j=0; j<NO_OF_FILES; j++){
      *(sk) << FILE_LIST[j];
      reply = recvContents(sk);
    }
  }
}
int mysleep(int msec){
  struct timespec tim;
  tim.tv_sec = msec / 1000;
  tim.tv_nsec = (msec - tim.tv_sec * 1000) * 1000000;
  return nanosleep(&tim, NULL);
}

string getMyHostName(){
  char lhost[256];
  lhost[255] = '\0';
  gethostname(lhost, 255);
  string myhost(lhost);
  return myhost;
}

string timeNow(){
  time_t rawtime;
  struct tm * timeinfo;
  char buffer [80];

  time (&rawtime);
  timeinfo = localtime (&rawtime);

  strftime (buffer,80,"%Y-%m-%d %H:%M:%S",timeinfo);
  string nowstring(buffer);
  return nowstring;
}

double getTimeDiff(struct timeval t1, struct timeval t2){
  return (double)(t2.tv_sec - t1.tv_sec)*1000 + (double)(t2.tv_usec - t1.tv_usec)/1000;
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

int hostname_to_ip(string hostName , char* ip)
{
    char lHostName[256];
    strcpy(lHostName, hostName.c_str());
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ( (he = gethostbyname( lHostName ) ) == NULL)
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
                        myfile << *it << endl;
                }
                myfile.close();
        }else cout << "Unable to open file!";
}

void printLogList(vector<string> logList){
  for(vector<string>::iterator it = logList.begin(); it != logList.end(); ++it){
    cout << *it << endl;
  }
}
