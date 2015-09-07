#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

void light_init(){
	system("gpio mode 7 out");
}

const long UNIT_KILOBYTE = 1024;
const long UNIT_MEGABYTE = 1024 * 1024;
const long UNIT_GIGABYTE = 1024 * 1024 * 1024;
bool DEBUG = true;

int main(int argc, char** argv){
	if(argc <= 1){
		cout << "Dummy File Maker\nUsage: " << argv[0] << " [FileSize: 1B or 10M or 1G\nExample: "<< argv[0] << " 10M\n";
		return 2;
	}
	string argu(argv[1]);
	string sSize = argu.substr(0, argu.length()-1);
	string sUnit = argu.substr(argu.length()-1, 1);
	if(DEBUG) cout << sSize << " : " << sUnit << '\n';
	long index = 0;
	long nSize = atol(sSize.c_str());
	if(sUnit.compare("K") == 0){
		nSize *= UNIT_KILOBYTE;
	}else if(sUnit.compare("M") == 0){
		nSize *= UNIT_MEGABYTE;
	}else if(sUnit.compare("G") == 0){
		nSize *= UNIT_GIGABYTE;
	}else{
		nSize = 1;
	}
	string fileName = "file_" + sSize + sUnit;
	cout<<"Writing " << nSize <<"byte into :"<< fileName << '\n';
	ofstream myfile;
	myfile.open(fileName.c_str());
	if(myfile.is_open()){
		for(index = 0; index < nSize ; index++){
			myfile << index % 10;
		}
		myfile.close();
		cout<<"Done\n";
	}else cout << "Unable to open file!";
	//}
	/*
	writeRssiList(AVG_FILE_PATH, rssiList);
	else return 0;
	*/
	return 0;
}
