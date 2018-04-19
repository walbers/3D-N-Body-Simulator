#include "ofApp.h"
#include <cmath>

// Setup all the planet's and reset the simulation
void ofApp::setup() {
	for (int i = 0; i < number_of_planets; i++) {
		planets.push_back(planet());
	}

	resetSimulation();
}

//--------------------------------------------------------------
void ofApp::update() {	// split up into methods

	//cout << ofGetFrameRate() << endl;
	//cout << ofGetFrameNum() << endl;						////////
	
	// Go through each planet getting its force
	for (unsigned i = 0; i < planets.size(); i++) {
		for (unsigned j = 0; j < planets.size(); j++) {

			if (i != j) {

				// Destory planets when collide - will throw error if two many collide at one time
				// Change to area of circle
				if (planets[i].radius + planets[j].radius > 
						ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y) + collision_distance_helper) {

					if (planets[i].radius > planets[j].radius) {

						planets[i].mass += planets[j].mass;
						planets.erase(planets.begin() + j);
					}
					else {
						planets[j].mass += planets[i].mass;
						planets.erase(planets.begin() + i);
					}
				}

				else {

					// Will never divide by zero becuase we check to destroy a planet before this
					// Magnitude of all the force on the planet, F = G*M1*M2/(d^2)
					planets[i].main_force += gravitational_constant * planets[i].mass * planets[j].mass /
							ofDistSquared(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y);

					/*
					if (i == 0) {
						cout << "main: ";
						cout << planets[i].main_force << endl;						///////
					}
					*/

					// Sum of all X-component's of the force, if neither < or > then default is 0
					// Fx = F * ((x2 - x1) / d), Fx = the force proportional to the x distance
					if (planets[i].position.x > planets[j].position.x) {
						planets[i].force_components.x += ((planets[j].position.x - planets[i].position.x) /
							ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y)) * planets[i].main_force;
					}
					else if (planets[i].position.x < planets[j].position.x) {
						planets[i].force_components.x += ((planets[j].position.x - planets[i].position.x) /
							ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y)) * planets[i].main_force;
					}

					// Sum of all Y-component's of the force, if neither < or > then default is 0
					// Check this
					if (planets[i].position.y > planets[j].position.y) {
						planets[i].force_components.y += ((planets[j].position.y - planets[i].position.y) /
							ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y)) * planets[i].main_force;
					}
					else if (planets[i].position.y < planets[j].position.y) {
						planets[i].force_components.y += ((planets[j].position.y - planets[i].position.y) /
							ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y)) * planets[i].main_force;
					}
					
					// Print components of force
					/* 
					if (i == 0) {
						cout << planets[i].force_components.x << endl;						///////
						cout << planets[i].force_components.y << endl;						///////
					}
					*/
					
					// This works - checked on calculator
					/*
					if (i == 0) {
						cout << "combined: ";
						cout << sqrtf((pow(planets[i].force_components.x, 2) + pow(planets[i].force_components.y, 2))) << endl;
					}
					*/

				}
			}
		}

		

		// Acceleration = Force / Mass
		planets[i].acceleration.x = planets[i].force_components.x / planets[i].mass;
		planets[i].acceleration.y = planets[i].force_components.y / planets[i].mass;

		// Taken from: https://github.com/conorrussomanno/conorRussomanno_algo2012/blob/master/wk5_planet_simulation/src/Planet.h
		// I don't think is accurate because of the different timings?
		planets[i].velocity.x += planets[i].acceleration.x;
		planets[i].velocity.y += planets[i].acceleration.y;
		
		// Set max X-velocity
		if (planets[i].velocity.x > max_speed) {
			planets[i].velocity.x = max_speed;
		}
		if (planets[i].velocity.x < -max_speed) {
			planets[i].velocity.x = -max_speed;
		}
		// Set max Y-velocity
		if (planets[i].velocity.y > max_speed) {
			planets[i].velocity.y = max_speed;
		}
		if (planets[i].velocity.y < -max_speed) {
			planets[i].velocity.y = -max_speed;
		}


		// cout << "planet " + i << endl;
		//cout << "main: ";
		//cout << planets[i].main_force << endl;
		//cout << planets[i].force_components.x << endl;
		//cout << planets[i].force_components.y << endl;
		//cout << planets[i].acceleration.x << endl;
		//cout << planets[i].acceleration.y << endl;
	}
		
	
	for (unsigned i = 0; i < planets.size(); i++) {
		planets[i].update();
	}

	resetVectors();
}

// Draw all the planet's
void ofApp::draw() {
	ofBackgroundGradient(ofColor(60, 60, 60), ofColor(10, 10, 10));

	for (unsigned int i = 0; i < planets.size(); i++) {
		// Set max X-acceleration
		if (planets[i].velocity.x == 30 || planets[i].velocity.x == -30 || planets[i].velocity.y == 30 || planets[i].velocity.y == -30) {
			cout << "green" << endl;
			planets[i].drawMax();
		}
		else {
			planets[i].draw();
		}
	}
	ofSetColor(244, 244, 244);
	string frame_num = "Frame: " + ofToString(ofGetFrameNum(), 4);
	ofDrawBitmapString(frame_num, 100, 100);
	string frame_rate = "Frame rate: " + ofToString(ofGetFrameRate(), 4);
	ofDrawBitmapString(frame_rate, 100, 110);
}

// Totally reset the simulation to start simulation
void ofApp::resetSimulation() {
	for (unsigned int i = 0; i < planets.size(); i++) {
		planets[i].totalReset();
	}
}

// Reset all vector's but velocity so they can be updated
void ofApp::resetVectors() {
	for (unsigned int i = 0; i < planets.size(); i++) {
		planets[i].reset();
	}
}


/**********************************************************/


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}