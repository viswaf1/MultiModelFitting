/*
 * ModelFitter.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: teja
 */

#include "ModelFitter.h"

namespace std {

ModelFitter::ModelFitter(vector<vec2f>& inpoints, vector<vec2f>& inmultiModels) {
	points = inpoints;
	multiModels = inmultiModels;
}

vector<vec2f> ModelFitter::fitModels() {

	for(int i=0; i<points.size(); i++) {
		vec2f currentPoint = points[i];
		float minDist = FLT_MAX;
		vec2f bestModel;
		bool modelFound = false;

		for(int j=0; j<multiModels.size(); j++) {
			float theta = multiModels[j].x;
			float rho = multiModels[j].y;

			vec2f pointProj;
			pointProj.x = currentPoint.x;

			if(sin(theta) == 0) {
				continue;
			}
			else{
				pointProj.y = (rho/sin(theta)) - (pointProj.x*(cos(theta)/sin(theta))) ;
				modelFound = true;
			}

			/* calculate distance between the projected point and the actual point */
			float dist = currentPoint.dist(pointProj);
			if(dist < minDist){
				minDist = dist;
				bestModel = multiModels[j];
			}

		}
		if(minDist <= 100) {
			if(modelFound == true) {
				points[i].y = (bestModel.y/sin(bestModel.x)) - (points[i].x*(cos(bestModel.x)/sin(bestModel.x))) ;

			}
		}
	}
	return points;
}

ModelFitter::~ModelFitter() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
