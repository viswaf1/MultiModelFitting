/*
 * Ransac.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: teja
 */

#include "Ransac.h"
#include "vec2.h"

namespace std {

Ransac::Ransac(vector<vec2<float>> inpts, int initerNum, float ininlrRatio, int instart=0) {
	pts = inpts;
	iterNum = initerNum;
	inlrRatio = ininlrRatio;
	startPt = instart;

}

Ransac::~Ransac() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
