#include "line.h"

Line::Line(string catid, string propid, string amount, string time, string l) :
	line(), label(l) {
	line[time] = new Time(catid,propid,amount);
}

void Line::setLine(string catid,string propid,string amount,string time,string l){
	label = l;
	if(line.find(time) == line.end()){
		line[time] = new Time(catid,propid,amount);
	}else{
		line[time]->setTime(catid,propid,amount);
	}
}
