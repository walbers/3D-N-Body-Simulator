#pragma once

#include "ofMain.h"
#include "../planet.h"
#include <vector>

// TO DO: ADD TIME, fix velocity, tune variables to represent real world
// optional: add spin/angular momentum, make 3D (spheres), add an option to create our solar system, elastic/inelastic collisions (shatter the planet), better planets (pictures instead of circle), tidal forces

// Problems ran into: timing, sin/cos/asin weren't accurate enough, .assignn for constructor didn't get random, splitting force into componenets, collision distance with different size planets
//							  Fx = proportional way isn't accurate either


// double

//singleton class/pattern, extern in header and cpp or static variable in class
// global variable pattern

// scale velocity

// make a grid

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void resetVectors();
		void resetSimulation();
		void destroy();

		vector<planet> planets;
		ofEasyCam cam;
		
		// Constants - make const
		float gravitational_constant = 8.0e-8; //6.67408e10-11
		float max_speed = 40;
		float collision_distance_helper = 1; // Can control when planets collide
		int number_of_planets = 150; // ik gets laggy at 400

		// Holders
		float main_force_holder;
		float force_x_holder;
		float force_y_holder;

		
		//***********//
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
