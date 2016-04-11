/*
 * Feature.h
 *
 *  Created on: 2016-4-3
 *      Author: Yuqi Zhang
 */

#ifndef FEATURE_H_
#define FEATURE_H_


#include "unordered_map"
#include "string.h"
#include "sstream"
#include "line.h"
#include "time.h"
class Feature{
private:
	fileIO &fIO;
	string fileName;
	int dataSize;
	unordered_map<string,Line*> matrix;
public:
	Feature(string filename):fIO(fileIO::getIntance()),fileName(filename),dataSize(0),matrix(){
				fIO.setNameR(fileName);
		}
	~Feature(){
		for(auto it : matrix){
			delete it.second;
		}
	}
	int getDataSize(){
		return dataSize;
	}
	unordered_map<string,Line*> getMatrix(){
		return matrix;
	}
	void splitLinetoitem(string s,vector<string>& items){
		stringstream ss(s);
		string item;
		while (getline(ss, item, ',')) {
			if (!item.empty()) {
				items.push_back(item);
			}
		}
	}
	void initialFeature(){
		string temp = fIO.readLine(); //read the colums name,which we don't need
		while(!temp.empty())
		{
			temp = fIO.readLine();
			if(!temp.empty())
			{
				vector<string> line;
				splitLinetoitem(temp,line);
				//line[0]: userid
				//line[2]: catid
				//line[4]: proid
				//line[5]: amount
				//line[6]: time
				//line[7]: birthday
				//line[8]: lable
//				cout<<"userid"<<":"<<line[0]<<","<<"catid"<<line[2]<<
//							",proid"<<":"<<line[4]<<",amount"<<line[5]<<",time"<<"line[6]"
//									<<",birthday:"<<line[7]<<",lable:"<<line[8]<<endl;
				std::unordered_map<string,Line*>::iterator it = matrix.find(line[0]);
				if(it==matrix.end())
				{
					matrix[line[0]] = new Line(line[2],line[4],line[5],line[6],line[8]);
				}else{
					matrix[line[0]]->setLine(line[2],line[4],line[5],line[6],line[8]);
				}
			}
		}
		dataSize = matrix.size();
	}
	void initialFeature2(){
			string temp = fIO.readLine(); //read the colums name,which we don't need
			while(!temp.empty())
			{
				temp = fIO.readLine();
				if(!temp.empty())
				{
					vector<string> line;
					splitLinetoitem(temp,line);
					//line[0]: userid
					//line[2]: catid
					//line[4]: proid
					//line[5]: amount
					//line[6]: time
					std::unordered_map<string,Line*>::iterator it = matrix.find(line[0]);
					if(it==matrix.end())
					{
						matrix[line[0]] = new Line(line[2],line[4],line[5],line[6],"0");
					}else{
						matrix[line[0]]->setLine(line[2],line[4],line[5],line[6],"0");
					}
				}
			}
			dataSize = matrix.size();
		}
};
#endif /* FEATURE_H_ */
