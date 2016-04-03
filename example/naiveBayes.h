/*
 * naiveBayes.h
 *
 *  Created on: Nov 13, 2015
 *      Author: yuqi2
 */
#ifndef NAIVEBAYES_H_
#define NAIVEBAYES_H_
#include "string"
#include "map"
#include "vector"
#include "tool/fileIO.h"
using namespace std;
class naiveBayes{
private:
	const string trainFile;
	const string testFile;
	const string resultFile;
	fileIO &rf;
	int sampleNum;
	bool isTrain;
	std::map<int,float> lables;
	enum s{
		SIZE = 10, //number of label
		NUM = 784  //number of feature
	};
	vector<vector<float>> poss;
public:
	naiveBayes(const string & trainfile , const string &testFile,const string &resultfile);
	void splitByCommaTrain(string s,int lable);
	void splitByCommaPredict(string s);
	void caculatePoss();
	void printPoss() const;
	void printLable() const;
	int getSampleNum() const {return sampleNum;}
	void train();
	void predict();
};
#endif /* NAIVEBAYES_H_ */
