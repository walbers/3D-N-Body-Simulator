#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	//1024, 768
	//1920, 1080
	//2048, 1080
	//3840, 2160
	//1900, 1900 good
	ofSetupOpenGL(3840, 2160, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
 