/*
 * MultiRansac.h
 *
 *  Created on: Apr 1, 2016
 *      Author: teja
 */

#ifndef MULTIRANSAC_H_
#define MULTIRANSAC_H_

#include<vector>
#include<stdlib.h>
#include <iostream>
#include <ctime>
#include <algorithm>
#include "vec2.h"
#include "Ransac.h"

namespace std {

typedef struct {
	vec2f point;
	int index;
} DataPoint;

typedef struct{
	vector<int> inliers;
	vec2f model;
} CSElement;


class MultiRansac {
	void updateCS(vector<CSElement> &Sw);
public:

	vector<DataPoint> dataPts;
	int iterNum;
	float inlrRatio;
	int thInlrNum;
	float thDist;
	vector<CSElement> CS;
	bool checkDisjoint(vector<CSElement> &Sw, CSElement &S);
	bool checkDisjointElements(CSElement &E1, CSElement &E2);

	MultiRansac(vector<vec2f> pts, int iterNum, float thDist, float inlrRatio);
	vector<vec2f> getMultiModels();
	virtual ~MultiRansac();



};

} /* namespace std */

#endif /* MULTIRANSAC_H_ */
