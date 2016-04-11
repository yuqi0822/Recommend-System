#include "line.h"

Line::Line(string catid, string propid, string amount, string time, string l) :
	util(Utils::getInstance("index.csv")), line(), label(l), tMax(util.getTMax()),
	vecLength(tMax*(util.getCatNum()+util.getProNum())), vec(vecLength), vecMap(util.getMapping()), dateMap(util.getTMap()) {

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
