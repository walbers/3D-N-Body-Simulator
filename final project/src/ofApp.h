#pragma once

#include "ofMain.h"
#include "../planet.h"
#include <vector>


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void reset();
	void resetVectors();
	void resetSimulation();
	void destroy2d();
	void destroy3d();
	void keyPressed(int key);

	// Drawing
	void draw();
	void drawIntro();
	void draw2d();
	void draw3d();

	ofEasyCam cam;
	vector<planet> planets;
	float seconds;

	// Holders
	double main_force_holder;
	float force_x_holder;
	float force_y_holder;
	float force_z_holder;
};