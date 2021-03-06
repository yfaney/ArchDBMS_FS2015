#include <iostream>
//#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <signal.h>

using namespace std;

/*vector<float> getRssiList(const char* filePath){
	float rssis[8];
	string line;
	int index = 0;
	vector<float> rssiList;
	ifstream myfile;
	myfile.open(filePath);
	if(myfile.is_open()){
		while(getline(myfile, line)){
			rssis[index] = atof(line.c_str());
			++index;
		}
		myfile.close();
		rssiList.assign(rssis, rssis + index);
	}
	else{
		ofstream newfile;
		newfile.open(filePath);
		if(newfile.is_open()){
			myfile.close();
		}else cout << "Unable to open file during making!";
	}
	return rssiList;
}

void writeRssiList(const char* filePath, vector<float> rssiList){
	ofstream myfile;
	myfile.open(filePath);
	if(myfile.is_open()){
		for(vector<float>::iterator it = rssiList.begin(); it != rssiList.end(); ++it){
			myfile << *it << '\n';
		}
		myfile.close();
	}else cout << "Unable to open file!";
}
*/
float average(vector<float> list){
	if(list.size() > 0){
		float sum;
		for(vector<float>::iterator it = list.begin(); it != list.end(); ++it){
			sum += *it;
		}
		return sum/list.size();
	}else return 0;
}
void printList(vector<float> list){
	if(list.size() > 0){
		float sum;
		for(vector<float>::iterator it = list.begin(); it != list.end(); ++it){
			cout << *it <<"  ";
		}
		cout << '\n';
	}
}

bool is_light_on = false;
void light_init(){
	system("gpio mode 7 out");
}
void light_onoff(bool onoff){
	is_light_on = onoff;
	if(onoff){
		cout << "Light On!\n";
		system("gpio write 7 1");
	}
	else{
		cout << "Light Off!\n";
		system("gpio write 7 0");
	}
}


const char* AVG_FILE_PATH = "/var/ramdrive/beacon_avg_data.data";
const char* MY_BEACON_ID = "4D 79 20 42 4C 45 20 44 61 74 61 21 21 21 21 21 21";
const int MAX_QUEUE_SIZE = 8;
const float MAX_RSSI = 218.0;
const float MIN_RSSI = 162.0;
const float THRESHOLD_LOW = 27.0;
const float THRESHOLD_HIGH = 40.0;
const bool DEBUG = false;

void signal_callback_handler(int signum){
	cout << "Exited by user\n";
	light_onoff(false);
	exit(signum);
}
int main(int argc, char** argv){
	string lineInput;
	while(getline(cin, lineInput)){
		//cout << lineInput << '\n';
		cout << "Output:: " << lineInput << '\n';
	}
	/*
	if(argc <= 1){
		cout << "Argument Needed!" << argc;
		return 2;
	}
	writeRssiList(AVG_FILE_PATH, rssiList);
	else return 0;
	*/
	return 0;
}
