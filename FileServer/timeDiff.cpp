#include <iostream>
#include <sys/time.h>
using namespace std;

int main (int argc, char* argv[]){
	struct timeval t1, t2;
	gettimeofday(&t1, NULL);
        int i;
        for(i=0 ; i < 50000 ; i++){
		cout << i;
	}
	gettimeofday(&t2, NULL);
	int milliSeconds = (t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec)/1000;
	cout << endl << endl <<milliSeconds<<endl;
}
