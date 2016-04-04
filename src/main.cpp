/*
 * main.cpp
 *
 *  Created on: 2016-4-3
 *      Author: Yuqi Zhang
 */
#include "feature.h"
int main(){
	Feature f("test_sample1.csv");
	f.initialFeature();
	f.printMatrix();
	return 0;
}


