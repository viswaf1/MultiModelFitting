/*
 * MultiRansac.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: teja
 */

#include "MultiRansac.h"

namespace std {

bool CSElmCompare(CSElement el1, CSElement el2) {
	return(el1.inliers.size() < el2.inliers.size());
}

MultiRansac::MultiRansac(vector<vec2f> inpts, int initerNum, float inthDist, float ininlrRatio) {
	iterNum = initerNum;
	inlrRatio = ininlrRatio;
	thInlrNum = inlrRatio*inpts.size();
	thDist = inthDist;
	for(unsigned int i=0; i<inpts.size(); i++) {
		DataPoint tempPt;
		tempPt.point = inpts[i];
		tempPt.index = i;
		dataPts.push_back(tempPt);
	}
	srand(time(NULL));
}

vector<vec2f> MultiRansac::getMultiModels() {
	int numMultiIters = 1;

	for(int i=0; i<numMultiIters; i++) {
		vector<DataPoint> currentData = dataPts;
		int startInd = rand() % (currentData.size() );
		vector<CSElement> newCS;
		for(int j=0; j<200; j++) {

			if(currentData.size() < 2) {
				break;
			}
			vector<vec2f> dataPts;
			for(unsigned int x=0; x<currentData.size(); x++)
				dataPts.push_back(currentData[x].point);

			CSElement curCSEl;

			Ransac ransac(dataPts, iterNum, thDist, inlrRatio, startInd);
			curCSEl.model = ransac.getModel();
			vector<int> ptsUsedIter = ransac.getUsedPts();

			//if the size of points used is empty, then there are no models in the data
			if(ptsUsedIter.size() < 1) {
				break;
			}

			/* Conver the points used in the current iteration of RANSAC
			  to inliers indexed on the original data */

			vector<int> inliersIter;
			for(unsigned int x=0; x<ptsUsedIter.size(); x++) {
				inliersIter.push_back(currentData[ptsUsedIter[x]].index);
			}
			curCSEl.inliers = inliersIter;

			// remove point used in the current iteration from currentData
			vector<int> usedPtsMap(currentData.size());
			for(unsigned int x=0; x<ptsUsedIter.size(); x++) {
				usedPtsMap[ptsUsedIter[x]] = 1;
			}

			vector<DataPoint> newCurrentData;
			for(unsigned int x=0; x<currentData.size(); x++) {
				if(!usedPtsMap[x]){
					newCurrentData.push_back(currentData[x]);
				}
			}
			startInd = startInd - ptsUsedIter.size();
			startInd = (startInd+10)%newCurrentData.size();

			currentData = newCurrentData;
			newCS.push_back(curCSEl);
			//cout << "size of remaining points is " << currentData.size() << "\n";
			//cout << "the model iter is " << curCSEl.model.x << " " << curCSEl.model.y << "\n";

		}
		updateCS(newCS);

	}

	vector<vec2f> multiModels;
	for(int i=0; i<CS.size(); i++) {
		multiModels.push_back(CS[i].model);
	}
	return multiModels;

}

void MultiRansac::updateCS(vector<CSElement> &Sw) {
	vector<CSElement> allCS = CS;
	CS.clear();
	for(unsigned int i=0; i<Sw.size(); i++){
		allCS.push_back(Sw[i]);
	}
	sort(allCS.begin(), allCS.end(), CSElmCompare);
	while(allCS.size() > 0) {
		CSElement curEl = allCS[allCS.size()-1];
		allCS.pop_back();

		if(checkDisjoint(CS, curEl)) {
			CS.push_back(curEl);
		}

	}


}

bool MultiRansac::checkDisjoint(vector<CSElement> &Sw, CSElement &S) {

	if(Sw.size() < 1)
		return true;

	for(unsigned int i=0; i<Sw.size(); i++) {
		if(!checkDisjointElements(Sw[i], S))
			return false;
	}
	return true;
}

bool MultiRansac::checkDisjointElements(CSElement &E1, CSElement &E2) {
	sort(E1.inliers.begin(), E1.inliers.end());
	sort(E2.inliers.begin(), E2.inliers.end());
	vector<int> interInliers;

	set_intersection(E1.inliers.begin(), E1.inliers.end(), E2.inliers.begin(),
			E2.inliers.end(), back_inserter(interInliers));

	if(interInliers.size() > 5) {
		return false;
	}
	else {
		return true;
	}

	return true;
}

MultiRansac::~MultiRansac() {


}

} /* namespace std */
