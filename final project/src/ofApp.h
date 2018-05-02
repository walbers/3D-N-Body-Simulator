#pragma once

#include "ofMain.h"
#include "../planet.h"
#include <vector>

// 1. compare to github to speed up			X - how to make functions way faster
// 2. global constants thing				X - how many?
// 3. speed up velocity						X - fix time thing
// 4. only tails when so many left			X - prolly better way to do
// 5. different scenarios/scaled correctly
// 6. 3d									X - add z motion, correct viewing angle
// 7. Textures?
// 8. max speed thing - make a boolean global
// 9. font thing
// 10. Development.md

// velocity/time thing				meter / sec			pix / frame

// Slow down/speed up only works when its constant not changing.



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void resetVectors();
		void resetSimulation();
		void destroy();
		void calculateForceComponents(int, int);
		void calculateVelocity(int);
		void checkMaxVelocity(int);
		void keyPressed(int key);

		void drawIntro();
		void draw2d();
		void draw3d();
		void drawSolarSystem();

		ofEasyCam cam;		// 3d
		vector<planet> planets;
		float seconds;

		// Holders
		double main_force_holder;
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
