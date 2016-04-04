#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED
#include <iostream>
#include <unordered_map>
#include "time.h"
class Line{
public:
	Line(string cid,string pid,string a,string t, string l);
	~Line(){
		line::iterator it = line.begin() ;
		for(;it!=line.end();it++){
			delete it->second;
		}
		line.clear();
	}
	void setLine(string cid,string pid,string a,string t, string l);
	
private:
	std::unordered_map<std::string,Time*> line;
}
