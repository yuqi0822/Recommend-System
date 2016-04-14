/*
 * main.cpp
 *
 *  Created on: 2016-4-3
 *      Author: Yuqi Zhang
 */
#include "NaiveBayes.h"
#include "tool/utils.h"
#include <ctime>

int main(){
		string trainFile="newtraining.csv",testFile="newtraining.csv",resultFile="output.csv";
		string mapFileName="newindex.csv";
		Utils::getInstance(mapFileName);

	    double elapsed_train,elapsed_predict;
		clock_t begin = clock();
		double thredhold=0.8;
		NaiveBayes nb(trainFile,testFile,resultFile,thredhold);
		clock_t end = clock();
		elapsed_train = double(end - begin) / CLOCKS_PER_SEC;
		cout<<"trainning spends "<<elapsed_train<<" seconds."<<endl;


		//turn off CalcCondProb() in ctor of naiveBayes.h to use predict_Similarity();
//		begin = clock();
//		nb.predict_Similarity();
//		end = clock();
//		elapsed_predict = double(end - begin) / CLOCKS_PER_SEC;
//		cout<<"predict spends "<<elapsed_predict<<" seconds."<<endl;

		//turn on CalcCondProb() in ctor of naiveBayes.h to use predict_NaiveBayes();

		begin = clock();
		nb.predict_NaiveBayes();
		end = clock();
		elapsed_predict = double(end - begin) / CLOCKS_PER_SEC;
		cout << "predict spends " << elapsed_predict << " seconds." << endl;

		cout << "The sum time is " << elapsed_predict + elapsed_train << " seconds."
			 << endl;
		return 0;
}


