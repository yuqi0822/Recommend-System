/*
 * fileIO.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: yuqi2
 */

#include "fileIO.h"
fileIO::fileIO():fileNameR(""),fileNameW(""),filer(),filew()
{}
void fileIO::openFile(string n,char mode){
	  try {
			 switch(mode)
			 {
				 case 'r':filer.open(n.c_str(),std::ifstream::in);break;
				 case 'w':filew.open(n.c_str(),std::ofstream::out);break;
				 default:cout<<"please input the file opt mode"<<endl;break;
			 }
	  }
	  catch (std::ifstream::failure &e) {
	    std::cerr << "Exception opening file"+n<<endl;
	  }
}
string fileIO::readWordCsv(){
	string s;
	if (filer.is_open()) {
		if (filer.good()) {
			getline(filer, s, ',');
		}
	} else {
		cout << fileNameR+"  File is closed." << endl;
	}
	return s;
}
string fileIO::readLine(){
	string s;
	if (filer.is_open()) {
		if (filer.good()) {
			getline(filer, s);
		}
	} else {
		cout << fileNameR + " File is closed." << endl;
	}
	return s;
}
