#pragma once

#include "ofMain.h"
#include "../planet.h"
//#include "../setting.h"
#include <vector>

// 1. compare to github to speed up			X - how to make functions way faster
// 2. global constants thing				X - how many?
// 3. speed up velocity						X - fix time thing
// 4. only tails when so many left			X - prolly better way to do
// 5. different scenarios/scaled correctly
// 6. 3d

// velocity/time thing				meter / sec			pix / frame

//float gravitational_constant = 8.0e-15; //6.67408e10-11 //-15

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void resetVectors();
		void resetSimulation();
		void destroy();
		void calculateForceComponents();
		void calculateVelocity();
		void checkMaxVelocity();
		void keyPressed(int key);

		//3d
		//ofEasyCam cam;
		vector<planet> planets;
		int seconds;

		// Holders
		float main_force_holder;
		float force_x_holder;
		float force_y_holder;

		//***********//
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
