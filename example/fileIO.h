/*
 * fileIO.h
 *
 *  Created on: Nov 13, 2015
 *      Author: yuqi2
 */
#include <string>
#include <fstream>
#include "iostream"
using namespace std;
class fileIO{
	fileIO();
	std::string fileNameR;
	std::string fileNameW;
	std::ifstream filer;
	std::ofstream filew;
public:
	static fileIO& getIntance(){
		static fileIO rf;
		return rf;
	}
	~fileIO(){
		if (filer.is_open()) {
			filer.close();
		}
		if (filew.is_open()) {
			filew.close();
		}
	}
	void setNameR(const string &n){
		fileNameR=n;
		if(filer.is_open())
		{
			filer.close();
		}
		openFile(fileNameR,'r');
	}
	void setNameW(const string &n){
			fileNameW=n;
			if(filew.is_open())
			{
				filew.close();
			}
			openFile(fileNameW,'w');
		}
	std::ifstream&  getFileR() {return filer;}
	std::ofstream&  getFileW() {return filew;}
	void openFile(string n,char mode); // mode:'r' for read, 'w' for write
	string readWordCsv();
	string readLine();
	template<typename  T>
	bool writeLine(T lable){
		if(filew.is_open())
		{
			filew<< lable << std::endl;
			return true;
		}else{
			cout<<"filew is not open!"<<endl;
			return false;
		}
	}
	template<typename  T>
	void writeArray(vector<T> &a)
	{
		if(filew.is_open())
		{
			for(int i=0; i<a.size();i++)
			{
				filew << a[i] << ',';
			}
		}else{
			cout<<"filew is not open!"<<endl;
		}
	}
	template<typename  T>
	void writeArray_NoEndComma(vector<T> &a)
	{
		if (filew.is_open()) {
			for (int i = 0; i < a.size()-1; i++) {
				filew << a[i] << ',';
			}
			filew << a[a.size()-1] ;
		} else {
			cout << "filew is not open!" << endl;
		}
	}
};


