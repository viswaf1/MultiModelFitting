/*
 * test.cpp
 *
 *  Created on: Mar 25, 2016
 *      Author: teja
 */

#include <iostream>
#include <vector>
#include "vec2.h"
#include "Ransac.h"

using namespace std;
int main() {
	int N;
	cin >> N;

	vector<vec2f> points;
	for(int n=0; n<N; n++) {
		float x,y;
		cin >> x;
		cin >> y;

		vec2f pt(x,y);
		points.push_back(pt);
		//cout << pt.x << " " << pt.y << "\n";
	}
	Ransac ransac(points, 100, 0.25, 0.1, 150);
	vec2f model = ransac.getModel();
	cout << "the model is " << model.x << " " << model.y << "\n";

	return 0;
}





