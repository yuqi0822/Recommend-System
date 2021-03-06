#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED
#include <iostream>
#include <unordered_map>
#include "string"
#include "time.h"
#include "tool/utils.h"

using namespace std;

class Line{
public:
	Line(string cid,string pid,string a,string t,string l);
	~Line(){
		unordered_map<string,Time *>::iterator it = line.begin();
		for(;it!=line.end();it++){
			delete it->second;
		}
		line.clear();
	}
	void setLine(string cid,string pid,string a,string t,string l);

	vector<double> getFeature() {
        for(auto time:line) {
            for(auto cid:(time.second)->getCMap()) {
                vec[vecMap[cid.first] + dateMap[(time.first).substr(0,4)]*vecLength] = cid.second;
            }

            for(auto pid:(time.second)->getPMap()) {
                vec[vecMap[pid.first] + dateMap[(time.first).substr(0,4)]*vecLength] = pid.second;
            }
        }
        return vec;
	}
	unordered_map<string,Time*> getLine(){
		return line;
	}
	int getLable(){
		return (atoi(label.c_str()));
	}

private:
    Utils& util;
	std::unordered_map<std::string,Time*> line;
	string label;
	int tMax;
	int vecLength;
	vector<double> vec;
	unordered_map<std::string, int> vecMap;
	unordered_map<std::string, int> dateMap;
};

#endif
