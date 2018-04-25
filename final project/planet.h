#pragma once
#include "ofMain.h"

class planet {
	
public:

	// Done in constructor
	planet();
	float mass;
	float radius;

	// Updated
	//float force_vector;
	ofVec2f force_components;
	ofVec2f acceleration;
	ofVec2f position;
	ofVec2f velocity;

	vector<ofVec2f> past_centers;
	ofVec2f past_centers_holder;

	// Methods
	void reset();
	void totalReset();
	void update();
	void draw();
	void createSun();
};