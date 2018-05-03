#pragma once
#include "ofMain.h"

class planet {

public:

	float mass;
	float radius;
	ofVec3f force_components;
	ofVec3f acceleration;
	ofVec3f position;
	ofVec3f velocity;
	vector<ofVec3f> past_centers;

	planet();
	void reset();
	void totalReset();
	void update();
	void draw();
	void createSun();
};