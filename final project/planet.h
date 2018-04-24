#pragma once
#include "ofMain.h"

class planet {
	
public:
	/*
	Fg = (G * m1 * m2) / d^2
	F = m1 * a
	*/

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

	// Methods
	void reset();
	void totalReset();
	void update();
	void draw();
	void drawMax();
	void checkMaxSpeed();
};