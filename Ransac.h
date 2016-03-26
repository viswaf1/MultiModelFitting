/*
 * Ransac.h
 *
 *  Created on: Mar 26, 2016
 *      Author: teja
 */

#ifndef RANSAC_H_
#define RANSAC_H_

#include<vector>

namespace std {

class Ransac {
	vector<vec2<float>> pts;
	int iterNum;
	float inlrRatio;
	int startPt;

public:
	Ransac(vector<vec2<float>> pts, int iterNum, float inlrRatio, int start=0);
	virtual ~Ransac();
};

} /* namespace std */

#endif /* RANSAC_H_ */
