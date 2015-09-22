/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
*/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

void dostuff(int); /* function prototype */
int send_file(string , int );
string& ltrim(string& );
string& rtrim(string& );
string& trim(string& );

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, pid;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;

     if (argc < 2) {
         cerr << "ERROR, no port provided" <<endl;
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     while (1) {
         newsockfd = accept(sockfd,
               (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0)
             error("ERROR on accept");
         pid = fork();
         if (pid < 0)
             error("ERROR on fork");
         if (pid == 0)  {
             close(sockfd);
             dostuff(newsockfd);
             exit(0);
         }
         else close(newsockfd);
     } /* end of while */
     close(sockfd);
     return 0; /* we never get here */
}

/******** DOSTUFF() *********************
 There is a separate instance of this function
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/
void dostuff (int sock)
{
   int n;
   char buffer[256];
   while(n >= 0){
      bzero(buffer,256);
      n = read(sock,buffer,255);
      if (n < 0) error("ERROR reading from socket");
//      cout << "Here is the message: " << buffer << endl;
      string fileName(buffer);
      if(fileName.length() == 0) break;
      send_file(trim(fileName), sock);
      if (n < 0) error("ERROR writing to socket");
   }
}

int send_file(string fileName, int sock){
  ifstream myfile;
//  string filePath = string(FILE_PATH) + fileName;
  string filePath = fileName;
  cout << "opening : " << filePath.c_str() << '\n';
  myfile.open(filePath.c_str());
  int n;
  if(myfile.is_open()){
    string line;
    while(getline(myfile, line)){
      n = write(sock, line.c_str(), line.length());
      if (n < 0) error("ERROR writing to socket");
    }
    n = write(sock, " ", 1);
  }
  else{
    n = write(sock, "File was not open.", 18);
  }
}

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
