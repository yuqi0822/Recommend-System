#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED
#include <iostream>
#include <unordered_map>
#include "string"
#include "time.h"
using namespace std;

class Line{
public:
	Line(string cid,string pid,string a,string t, string l);
	~Line(){
		unordered_map<string,Time *>::iterator it = line.begin();
		for(;it!=line.end();it++){
			delete it->second;
		}
		line.clear();
	}
	void setLine(string cid,string pid,string a,string t, string l);
	unordered_map<string,Time*> getLine(){
		return line;
	}
	int getLabel(){
		return label;
	}

private:
	std::unordered_map<std::string,Time*> line;
	int label;
};

#endif
