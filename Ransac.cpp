/*
 * Ransac.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: teja
 */


#include "Ransac.h"
#include "vec2.h"

namespace std {

Ransac::Ransac(vector<vec2f> inpts, int initerNum, float inthDist, float ininlrRatio, int instart) {
	pts = inpts;
	iterNum = initerNum;
	inlrRatio = ininlrRatio;
	thInlrNum = inlrRatio*pts.size();
	startPt = instart;
	thDist = inthDist;
	srand(time(NULL));

}

vec2f Ransac::getModel() {
	/* returns a model vector [a,b] of form y = ax+b */
	vec2f model;
	int ptNum = pts.size();
	int inlrNum = (inlrRatio*ptNum);
	vector<float> Thetas;
	vector<float> Rhos;

	vector<int> ptsUsed;
	vector<vector<int> > ptsUsedIter;

	int maxInlierNum = 0;
	int maxInlierInd = 0;

	for(int i=0; i<iterNum; i++) {
		vector<int> ptSample = getSampleSet(startPt, pts.size(), 2, 50);
		//cout << "point sample is " << ptSample[0] << " " << ptSample[1] << " \n";
		//cout << "point is (" << pts[ptSample[0]].x << "," << pts[ptSample[0]].y << ") ("
		//		<< pts[ptSample[1]].x << "," << pts[ptSample[1]].y << ")\n";

		vector<int> inliers = getInliers(ptSample, pts);


		float theta, rho;
		if( (pts[ptSample[1]].y - pts[ptSample[0]].y) == 0 && (pts[ptSample[1]].x - pts[ptSample[0]].x) == 0) {
			continue;
		}
		else {
			theta = atan2(-1*(pts[ptSample[1]].x - pts[ptSample[0]].x), (pts[ptSample[1]].y - pts[ptSample[0]].y));
		}
		rho = pts[ptSample[1]].x*cos(theta) + pts[ptSample[1]].y*sin(theta);

		//cout << "model is " << theta << "," << rho << "\n";

		if(inliers.size() < thInlrNum) {
					continue;
				}
		Thetas.push_back(theta);
		Rhos.push_back(rho);
		ptsUsedIter.push_back(inliers);


	}

	for(unsigned int i=0; i<Thetas.size(); i++) {
		cout << "(" << Thetas[i] << " " << Rhos[i] << ") " << ptsUsedIter[i].size() << "  \n";
		if(ptsUsedIter[i].size() > maxInlierNum) {
			maxInlierNum = ptsUsedIter[i].size();
			maxInlierInd = i;
		}
	}
	cout << "\n";
	ptsUsed = ptsUsedIter[maxInlierInd];
	model.x = Thetas[maxInlierInd];
	model.y = Rhos[maxInlierInd];

	return model;
}

vector<int> Ransac::getSampleSet(int start, int maxIndex, int len, int shift) {

	vector<int> sample;
	int stop;
	if(start+shift > maxIndex) {
		stop = maxIndex;
	}
	else {
		stop = start + shift;
	}
	for(int i=0; i<len; i++) {

		int pt = rand() % (stop-start) + start;
		sample.push_back(pt);
	}
	sort(sample.begin(), sample.end());
	//cout << "sample set is"<< sample[0] << " " << sample[1] << "\n";
	return sample;
}

vec2f Ransac::getNormDirVec(vec2f pt1, vec2f pt2) {
	vec2f dir = pt2-pt1;
	dir = dir.normalize();
	vec2f normDir = vec2f(-1*dir.y, dir.x);
	return normDir;
}

vector<int> Ransac::getInliers(vector<int> ptSample, vector<vec2f> &pts) {

	vector<int> inliers;
	vec2f normVec = getNormDirVec(pts[ptSample[0]], pts[ptSample[1]]);
	vec2f samplePt = pts[ptSample[0]];

	for(unsigned int i=0; i<pts.size(); i++) {
		float dist = samplePt.dot(normVec, samplePt-pts[i]);
		if(fabs(dist) <= thDist) {
			inliers.push_back(i);
		}
	}
	/* pick only the points that are continuous around sample point 1 */
	sort(inliers.begin(), inliers.end());
	int ptInd = 0;
	for(int i=0; i<inliers.size(); i++) {
		if(inliers[i] == ptSample[0]) {
			ptInd = i;
			break;
		}

	}

	//add Points to the left of the starting point
	vector<int> newInliers;
	newInliers.push_back(inliers[ptInd]);
	for(int i = ptInd-1; i>=0; i--) {
		if(fabs(pts[inliers[i]].x-pts[inliers[i+1]].x) > 0.04) {
			break;
		}
		else {
			newInliers.push_back(inliers[i]);
		}
	}
	// add points to the right of the starting point
	for(int i = ptInd+1; i < inliers.size(); i++) {
		if(fabs(pts[inliers[i]].x-pts[inliers[i-1]].x) > 0.04) {
			break;
		}
		else {
			newInliers.push_back(inliers[i]);
		}
	}
	sort(newInliers.begin(), newInliers.end());

	return newInliers;
}

Ransac::~Ransac() {

}

} /* namespace std */
