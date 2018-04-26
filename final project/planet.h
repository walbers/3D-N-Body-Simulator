#pragma once
#include "ofMain.h"
//#include "setting.h"

class planet {
	
public:

	// Done in constructor
	planet();
	float mass;
	float radius;

	// Updated
	ofVec2f force_components;
	ofVec2f acceleration;
	ofVec2f position;
	ofVec2f velocity;
	vector<ofVec2f> past_centers; // set size so array or vector?

	// Methods
	void reset();
	void totalReset();
	void update();
	void draw();
	void createSun();
};