/*
 * printMatrix.h
 *
 *  Created on: 2016-4-11
 *      Author: Yuqi Zhang
 */

#ifndef PRINTMATRIX_H_
#define PRINTMATRIX_H_


class Printer{
public:
	// print the unordered_map<string, Line*> hashmap
	static void printMapMatrix(unordered_map<string, Line*>& hashmap) {
		for (auto p2 : hashmap) {
			cout << "userid:" << p2.first;
			unordered_map<string, Time*> line = (p2.second)->getLine();
			for (auto time : line) {
				cout << "timeid=" << time.first << endl;
				(time.second)->cal_probability();
				cout << "prob:" << endl;
				std::unordered_map<std::string, float> mapc =
						(time.second)->getCMap();
				std::unordered_map<std::string, float> mapp =
						(time.second)->getPMap();
				for (auto c : mapc) {
					cout << "c_id=" << c.first << ",count:" << c.second << endl;
				}
				for (auto p : mapp) {
					cout << "p_id=" << p.first << ",count:" << p.second << endl;
				}
			}
		}
	}
	//print the Feature Object
	static void printFeatureMatrix(Feature &f){
		unordered_map<string, Line*> hashmap = f.getMatrix();
		printMapMatrix(hashmap);
	}
};



#endif /* PRINTMATRIX_H_ */
