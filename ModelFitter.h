/*
 * ModelFitter.h
 *
 *  Created on: Apr 22, 2016
 *      Author: teja
 */

#ifndef MODELFITTER_H_
#define MODELFITTER_H_

#include<vector>
#include<float.h>
#include<math.h>
#include"vec2.h"


namespace std {

class ModelFitter {
	vector<vec2f> points;
	vector<vec2f> multiModels;
public:
	ModelFitter(vector<vec2f>& points, vector<vec2f>& multiModels);
	vector<vec2f> fitModels();
	virtual ~ModelFitter();
};

} /* namespace std */

#endif /* MODELFITTER_H_ */
