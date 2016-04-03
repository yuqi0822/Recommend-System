/*
 * naiveBayes.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: yuqi2
 */

#include "naiveBayes.h"
#include "iostream"
#include <sstream>
#include <ctime>

naiveBayes::naiveBayes(const string & trainfile,const string &testfile,const string &resultfile)
:trainFile(trainfile),testFile(testfile),resultFile(resultfile),rf(fileIO::getIntance()),sampleNum(0),isTrain(false),lables(),poss(SIZE,vector<float>(NUM,1))
{
	rf.setNameR(trainfile);
}

void naiveBayes::splitByCommaTrain(string s, int lable) {
	stringstream ss(s);
	string item;
	int i = 0;
	while (getline(ss, item, ',')) {
		if (!item.empty()) {
			if (std::stoi(item)) {
				poss[lable][i] += 1;
			}
			i++;
		}
	}
}
void naiveBayes::splitByCommaPredict(string s) {
	string item;
	double max = 0;
	int maxLable = 0;
	for (int i = 0; i <SIZE; i++) {
		stringstream ss(s);
		double temp = lables.find(i)->second;//=1;
		int j =0;
		while (getline(ss, item, ',')) {
			if (!item.empty()) {
			  if (std::stoi(item)) {
				  	  temp *=  poss[i][j];
			      }else{
			    	  temp *= (1-poss[i][j]);
			      }
			   j++;
		     }
	   }
		if(temp>max)
		{
			max = temp;
			maxLable = i;
		}
		if(j != NUM)
		{
				std::cout<<"exist text data has different columns with training data:"<<j<<endl;
		}
   }
 //cout<<"maxLable:"<<maxLable<<endl;
	static int index = 0;
	index++;
	stringstream str("");
	str<<index<<","<<maxLable;
	rf.writeLine(str.str());
}
void  naiveBayes::caculatePoss(){
	for(int i=0;i<SIZE;i++)
	{
		int total = (lables.find(i)->second) + 1;   //this time lables still store the count of lable i;the lable is '0...SIZE';
		//for Extension:use an array map each lable one to one to the 0...SIZE
		for (int j = 0; j < NUM; j++) {
			poss[i][j] /= total;
		}
	}
	for(int i =0;i<SIZE;i++)
	{
		lables.find(i)->second /= sampleNum;
	}
}

void  naiveBayes::printPoss() const{
	for(unsigned i=0;i<SIZE;i++)
	{
		for(unsigned j=0;j<NUM;j++)
		{
			cout<<poss[i][j]<<",";
		}
		cout<<endl;
	}
}
void naiveBayes::printLable() const{
	map<int,float>::const_iterator it = lables.begin();
	while(it!=lables.end())
	{
		cout << it->first<<":"<<it->second<<endl;
		it++;
	}
}
void naiveBayes::train(){
	string temp = rf.readLine(); //read the colums name,which we don't need
	while(!temp.empty())
	{
		temp = rf.readWordCsv(); // read the lable
		if (!temp.empty()) {
			sampleNum += 1;
			int lable = std::stoi(temp);
			std::map<int,float>::iterator it = lables.find(lable);
			if(it==lables.end())
			{
				 lables[lable] = 1;
			}else{
				 lables[lable] ++;
			}
			temp = rf.readLine();  //read feature vector
			splitByCommaTrain(temp,lable);
		}
	}
	caculatePoss();//calculate the condition possibility first,the calculate the lable's possibility
	isTrain = true;
}
void naiveBayes::predict(){
	if(isTrain)
	{
		rf.setNameR(testFile);
		string temp = rf.readLine();

//		int count = 0;
		rf.setNameW(resultFile);    //open the file to write the result
		string head = "ImageId,Label";
		rf.writeLine(head);               //write the head of the file

		while(true)
		{
			temp = rf.readLine();
			if(temp.empty())
			{
				break;
			}
			splitByCommaPredict(temp);  //write the result pair
			//count++;                                   //for debug
			//cout<<count<<endl;our submission scored 0.83257,
		}
	}else{
		cout<<"train before predict"<<endl;
	}
}
int main(){
	double elapsed_train,elapsed_predict;
	clock_t begin = clock();
	naiveBayes nb( "/home/yuqi2/workspace2/naiveBayes/file/train.csv"
			, "/home/yuqi2/workspace2/naiveBayes/file/test.csv","/home/yuqi2/workspace2/naiveBayes/file/result.csv");
	nb.train();
	clock_t end = clock();
	elapsed_train = double(end - begin) / CLOCKS_PER_SEC;
	cout<<"trainning spends "<<elapsed_train<<" seconds."<<endl;
	//nb.printPoss();
	//nb.printLable();
	//cout<<nb.getSampleNum()<<endl;
	begin = clock();
	nb.predict();
	end = clock();
	elapsed_predict = double(end - begin) / CLOCKS_PER_SEC;
	cout<<"predict spends "<<elapsed_predict<<" seconds."<<endl;
	cout<<"The sum time is "<<elapsed_predict+elapsed_train<<" seconds."<<endl;

	return 0;
}
