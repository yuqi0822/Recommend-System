/*
 * main.cpp
 *
 *  Created on: 2016-4-3
 *      Author: Yuqi Zhang
 */
#include "NaiveBayes.h"
#include "tool/utils.h"

int main(){
	string trainFile="trainning.csv",testFile="test.csv",resultFile="output.csv";
	string mapFileName="index.csv";
	Utils::getInstance(mapFileName);
	double thredhold=0.8;
	NaiveBayes nb(trainFile,testFile,resultFile,thredhold);
	nb.predict();
	return 0;
}


