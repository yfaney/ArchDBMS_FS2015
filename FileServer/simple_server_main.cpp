#include <iostream>
#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>


using namespace std;

const char* FILE_PATH = "/tmp/";

/**
 * @brief Left Trim
 *
 * Trims whitespace from the left end of the provided std::string
 *
 * @param[out] s The std::string to trim
 *
 * @return The modified std::string&
 */
std::string& ltrim(std::string& s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(),
    std::ptr_fun<int, int>(std::isgraph)));
  return s;
}

/**
 * @brief Right Trim
 *
 * Trims whitespace from the right end of the provided std::string
 *
 * @param[out] s The std::string to trim
 *
 * @return The modified std::string&
 */
std::string& rtrim(std::string& s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
    std::ptr_fun<int, int>(std::isgraph)).base(), s.end());
  return s;
}

/**
 * @brief Trim
 *
 * Trims whitespace from both ends of the provided std::string
 *
 * @param[out] s The std::string to trim
 *
 * @return The modified std::string&
 */
std::string& trim(std::string& s) {
  return ltrim(rtrim(s));
}

int send_file(string fileName, ServerSocket* sock){
	//ServerSocket sk = *sock;
	ifstream myfile;
	string filePath = string(FILE_PATH) + fileName;
//	string filePath = fileName;
	cout << "opening : " << filePath.c_str() << '\n';
	myfile.open(filePath.c_str());
        try{
          if(myfile.is_open()){
	    string line;
	    while(getline(myfile, line)){
              cout << line;
	      *(sock) << line;
	    }
            *(sock) << " ";
	  }
	  else{
	    *(sock) << "File was not open\n";
	  }
        }
        catch ( SocketException& e )
        {
          cout << "Exception was caught:" << e.description() << "\nExiting.\n";
        }
}

void *server_module(void * args){
	ServerSocket* sock;
	sock = (ServerSocket*) args;
	string filename;
	*(sock) >> filename;
	send_file(trim(filename), sock);
	*(sock) >> filename;
	send_file(trim(filename), sock);
	*(sock) >> filename;
	send_file(trim(filename), sock);
	*(sock) >> filename;
	send_file(trim(filename), sock);
}

int main ( int argc, char* argv[] )
{
  cout << "running....\n";

  try
  {
    // Create the socket
    ServerSocket server ( 55700 );
//    pthread_t serverThread[NO_OF_NODES];
//    int i;
    //for ( i = 0; i <= NO_OF_NODES; i++ )
    while ( true )
    {
      ServerSocket new_sock;
      server.accept ( new_sock );
//      pthread_t thread1;
//      int rc = pthread_create(&thread1, NULL, server_module, (void*)&new_sock);
//      cout << "Thread " << i << "Created.\n";
//      ++i;
//		  string data;
//		  new_sock >> data;
//		  new_sock << data;
      try{
	string filename;
        while(1){
	  new_sock >> filename;
	  send_file(trim(filename), &new_sock);
//        if(rc) cout << "Error:" << rc <<endl;
        }
      }
      catch ( SocketException& e )
      {
        cout << "Exception was caught:" << e.description() << "\nExiting.\n";
      }
    }
  }
  catch ( SocketException& e )
  {
    cout << "Exception was caught:" << e.description() << "\nExiting.\n";
  }
  return 0;
}

