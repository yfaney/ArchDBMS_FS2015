#include <iostream>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <pthread.h>
#include <string>

using namespace std;

//#define NUM_THREADS     60

struct thread_data{
   int  thread_id;
   string message;
};

void *PrintHello(void *threadarg)
{
   struct thread_data *my_data;

   my_data = (struct thread_data *) threadarg;

   cout << "Thread ID : " << my_data->thread_id ;
   cout << " Message : " << my_data->message << endl;

   pthread_exit(NULL);
}

void *send_File_To_Client(void *threadarg){
	struct thread_data *my_data;
	my_data = (struct thread_data *) threadarg;

}


int main ()
{
   pthread_t threads[NUM_THREADS];
   struct thread_data td[NUM_THREADS];
   int rc;
   int i;

   for( i=0; i < NUM_THREADS; i++ ){
      cout <<"main() : creating thread, " << i << endl;
      td[i].thread_id = i;
      ostringstream oss;
      oss << "This is message from THREAD " << i; 
      td[i].message = oss.str();
      rc = pthread_create(&threads[i], NULL,
                          PrintHello, (void *)&td[i]);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}
