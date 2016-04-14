/*
 * NaiveBayes.h
 *
 *  Created on: 2016-4-9
 *  Author: Yuqi Zhang
 */
#ifndef NAIVEBAYES_H_
#define NAIVEBAYES_H_
#include "unordered_map"
#include "map"
#include "string"
#include "feature.h"
#include "line.h"
#include "cmath"
#include "tool/printMatrix.h"
#include "tool/utils.h"
#include "vector"
class NaiveBayes{
private:
	string trainFile;
	string testFile;
	string resultFile;
	double threshold;
	Feature * f;
	Feature * f_t;
	fileIO &fIO;
	Utils& util;
	map<int,double> probLable;
	map<int,unordered_map<string,Line*>> lableMatrix;
	vector<vector<double>> condProb; // lable , feature , value
public:
	NaiveBayes(string file0,string file1,string file2,double t):trainFile(file0),
			testFile(file1),resultFile(file2),threshold(t),f(new Feature(trainFile)),f_t(0)
				,fIO(fileIO::getIntance()),util(Utils::getInstance("index.csv")),probLable(),lableMatrix(),
				condProb(vector<vector<double>>(util.getLabelNum(),vector<double>(util.getFeatureDim(),1))){
		f->initialFeature();
		f_t = new Feature(testFile);
		f_t->initialFeature2();
		initialLableMatrix();
		int lableNum = util.getLabelNum();
		for(int l=0;l<lableNum;l++){
			probLable[l] = calcPLable(l);
		}

		CalcCondProb();
	}
	unordered_map<string,Line*> transformFeatureVector(){
		//Printer::printFeatureMatrix(*f_t);
		return f_t->getMatrix();
	}
	void initialLableMatrix(){
		unordered_map<string,Line*> matrix = f->getMatrix();
		for(auto p:matrix){
			lableMatrix[(p.second)->getLable()].insert({p.first,p.second});
		}
	}
	void CalcCondProb(){
		int lableNum = util.getLabelNum();
		int featureNum = util.getFeatureDim();
		for(int i=0;i<lableNum;i++){
			unordered_map<string,Line*> m = lableMatrix[i];
			for(auto p:m){
				vector<double> f = (p.second)->getFeature();
				for(int j=0;j<featureNum;j++){
					condProb[i][j] += f[j]*1;
				}
			}
			for(int j=0;j<featureNum;j++){
				condProb[i][j]/=lableMatrix[i].size();
			}
		}
	}
	double calcPLable(int lable){
		int countLable = lableMatrix[lable].size();
		int total = f->getDataSize();
		return (double)countLable/total;
	}
	void predict_Similarity(){
		unordered_map<string,Line*> matrix_test =  transformFeatureVector();
		unordered_map<string,Line*> matrix_sample = f->getMatrix();
		int lableNum = util.getLabelNum();
		string head = "UsereId,Label";
		fIO.setNameW(resultFile);
		fIO.writeLine(head);         //write the head of the file
		for(auto line:matrix_test){
			stringstream str("");
			str<<line.first<<",";
			vector<double> f = (line.second)->getFeature();
			int maxlable = 0;
			double max = 0;
			for(int l=0;l<lableNum;l++){
				map<int,double> result(probLable.begin(),probLable.end());
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
	void predict_NaiveBayes() {
		unordered_map<string,Line*> matrix_test = transformFeatureVector();
		unordered_map<string,Line*> matrix_sample = f->getMatrix();
		int lableNum = util.getLabelNum();
		int featureNum = util.getFeatureDim();
		string head = "UsereId,Label";
		fIO.setNameW(resultFile);
		fIO.writeLine(head); //write the head of the file
		for(auto line:matrix_test) {
			stringstream str("");
			str<<line.first<<",";
			vector<double> f = (line.second)->getFeature();
			int maxlable = 0;
			double max = 0;
			for(int l=0;l<lableNum;l++) {
				map<int,double> result(probLable.begin(),probLable.end());
				//for(int l=0;l<lableNum;l++){cout<<result[l]<<endl;}
				for(int j=0;j<featureNum;j++){
					result[l] *= log2(2+condProb[l][j]*f[j]);
				}
				//cout<<l<<":"<<result[l];
				if(max<result[l]){max=result[l];maxlable = l;}
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
