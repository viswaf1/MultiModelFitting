/*
 * Ransac.h
 *
 *  Created on: Mar 26, 2016
 *      Author: teja
 */

#ifndef RANSAC_H_
#define RANSAC_H_

#include<vector>
#include<stdlib.h>
#include <iostream>
#include <ctime>
#include <algorithm>
#include "vec2.h"

namespace std {

class Ransac {
	vector<vec2<float> > pts;
	int iterNum;
	float inlrRatio;
	int thInlrNum;
	int startPt;
	float thDist;
	vector<int> ptsUsed;

	vector<int> getSampleSet(int start, int maxIndex, int len, int shift);
	vector<int> getInliers(vector<int> ptSample, vector<vec2f> &pts);
	vec2f getNormDirVec(vec2f pt1, vec2f pt2);

public:
	Ransac(vector<vec2f> pts, int iterNum, float thDist, float inlrRatio, int start=0);
	virtual ~Ransac();
	vec2f getModel();
	vector<int> getUsedPts();
};

} /* namespace std */

#endif /* RANSAC_H_ */
