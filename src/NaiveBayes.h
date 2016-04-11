/*
 * NaiveBayes.h
 *
 *  Created on: 2016-4-9
 *      Author: Yuqi Zhang
 */
#ifndef NAIVEBAYES_H_
#define NAIVEBAYES_H_
#include "unordered_map"
#include "map"
#include "string"
#include "feature.h"
#include "line.h"
#include "cmath"

class NaiveBayes{
private:
	string trainFile;
	string testFile;
	string resultFile;
	double threshold;
	Feature * f;
	Feature * f_t;
	fileIO &fIO;
	int lableNum;
	map<int,unordered_map<string,Line*>> lableMatrix;
public:
	NaiveBayes(string file0,string file1,string file2,double t):trainFile(file0),
			testFile(file1),resultFile(file2),threshold(t),f(new Feature(trainFile)),f_t(0)
				,fIO(fileIO::getIntance()),lableNum(4),lableMatrix(){
		f->initialFeature();
		f_t = new Feature(testFile);
		f_t->initialFeature2();
		initialLableMatrix();
	}
	unordered_map<string,Line*> transformFeatureVector(string filename){
		f_t->printMatrix();
		return f_t->getMatrix();
	}
	void initialLableMatrix(){
		unordered_map<string,Line*> matrix = f->getMatrix();
		for(auto p:matrix){
			lableMatrix[(p.second)->getLable()].insert({p.first,p.second});
		}
//		//print
//		for(auto p:lableMatrix){
//			cout<<"label:"<<p.first<<endl;
//			unordered_map<string,Line*> hashmap = p.second;
//			for (auto p2 : hashmap) {
//				cout << "userid:" << p2.first;
//				unordered_map<string,Time*> line = (p2.second)->getLine();
//				for (auto time : line) {
//					cout << "timeid=" << time.first << endl;
//					(time.second)->cal_probability();
//					cout << "prob:" << endl;
//					std::unordered_map<std::string, float> mapc =
//							(time.second)->getCMap();
//					std::unordered_map<std::string, float> mapp =
//							(time.second)->getPMap();
//					for (auto c : mapc) {
//						cout << "c_id=" << c.first << ",count:" << c.second
//								<< endl;
//					}
//					for (auto p : mapp) {
//						cout << "p_id=" << p.first << ",count:" << p.second
//								<< endl;
//					}
//				}
//			}
//		}
	}
	double calcPLable(int lable){
		int countLable = lableMatrix[lable].size();
		int total = f->getDataSize();
		return (double)countLable/total;
	}
	void predict(){
		unordered_map<string,Line*> matrix_test =  transformFeatureVector(testFile);
		unordered_map<string,Line*> matrix_sample = f->getMatrix();


		map<int,double> result;
		for(int l=0;l<lableNum;l++){
			result[l] = calcPLable(l);
		}
		cout<<"matrix_test:"<<matrix_test.size()<<endl;
		string head = "UsereId,Label";
		fIO.setNameW(resultFile);
		fIO.writeLine(head);         //write the head of the file
		for(auto line:matrix_test){
			stringstream str("");
			str<<line.first<<",";

			cout << "label:" << (line.second)->getLable() << endl;
			vector<double> f = (line.second)->getFeature();

			for(auto i:f){
				cout<<i<<",";
			}
			cout<<endl;
			int maxlable = 0;
			double max = 0;
			for(int l=0;l<lableNum;l++){
				int total = lableMatrix[l].size();
				int count = 0;
				for(auto line:lableMatrix[l]){

					if(isSimilarity(f,(line.second)->getFeature())){
						count++;
					}
				}
				double pcon = (double)count / total;
				result[l] *= pcon;
				if(max<result[l]) {max=result[l];maxlable = l;}
			}
			str<<maxlable;
			fIO.writeLine(str.str());
		}
	}

	void setThreshold(double tsd) {
	    threshold = tsd;
	}

	double getThreshold() const {
	    return threshold;
	}

	bool isSimilarity(std::vector<double> vec1, std::vector<double> vec2) {
	    if( calCosine(vec1, vec2) >= threshold )
	        return true;
	    else
	        return false;
	}

	double calCosine(std::vector<double> vec1, std::vector<double> vec2) {
	    if(vec1.size() > vec2.size()) {
	        vec2.resize(vec1.size());
	    } else if(vec1.size() < vec2.size()) {
	        vec1.resize(vec2.size());
	    } else ;


	    double result, dotProduct = 0, vecMode1 = 0, vecMode2 = 0;
	    unsigned int i;
	    for(i = 0; i < vec1.size(); i++) {
	        dotProduct += vec1[i]*vec2[i];
	        vecMode1 += vec1[i]*vec1[i];
	        vecMode2 += vec2[i]*vec2[i];
	        //std::cout << "vec1:" <<  vec1[i] << "vec2:" << vec2[i] << std::endl;
	    }
	    result = dotProduct/(sqrt(vecMode1)*sqrt(vecMode2));
	    return result;
	}
};

#endif /* NAIVEBAYES_H_ */
