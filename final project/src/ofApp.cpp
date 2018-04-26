#include "ofApp.h"
#include <cmath>
#include <iomanip>
#include "../settings.h"


// Setup all the planet's and reset the simulation
void ofApp::setup() {

	ofSetVerticalSync(false);
	ofSetFrameRate(30); //ofEnableDepthTest();

	// Create array of planets
	for (int i = 0; i < number_of_planets; i++) {
		//cout << i << endl;
		planets.push_back(planet());
	}

	resetSimulation();
}


// Updates everything about the planets in order to orbit.
void ofApp::update() {

	planets_left = planets.size();

	destroy();
	//calculateForceComponents();
	//calculateVelocity();
	for (unsigned i = 0; i < planets.size(); i++) {
		for (unsigned j = 0; j < planets.size(); j++) {

			if (i != j) {
				
				// Will never divide by zero becuase we check to destroy a planet before this
				// Magnitude of all the force on the planet, F = G*M1*M2/(d^2)
				main_force_holder = gravitational_constant * planets[i].mass * planets[j].mass /
					ofDistSquared(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y);


				// X-component of the force
				// Fx = F * ((x2 - x1) / d), Fx = the force proportional to the x distance
				if (planets[i].position.x > planets[j].position.x) {
					force_x_holder = ((planets[j].position.x - planets[i].position.x) /
						ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y)) * main_force_holder;
				}
				else if (planets[i].position.x < planets[j].position.x) {
					force_x_holder = ((planets[j].position.x - planets[i].position.x) /
						ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y)) * main_force_holder;
				}

				// Y-component of the force
				if (planets[i].position.y > planets[j].position.y) {
					force_y_holder = ((planets[j].position.y - planets[i].position.y) /
						ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y)) * main_force_holder;
				}
				else if (planets[i].position.y < planets[j].position.y) {
					force_y_holder = ((planets[j].position.y - planets[i].position.y) /
						ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y)) * main_force_holder;
				}

				planets[i].force_components.x += force_x_holder;
				planets[i].force_components.y += force_y_holder;

				main_force_holder = 0;
				force_x_holder = 0;
				force_y_holder = 0;
			}

		}


		// Acceleration = Force / Mass
		planets[i].acceleration.x = planets[i].force_components.x / planets[i].mass;
		planets[i].acceleration.y = planets[i].force_components.y / planets[i].mass;

		// Taken from: https://github.com/conorrussomanno/conorRussomanno_algo2012/blob/master/wk5_planet_simulation/src/Planet.h
		planets[i].velocity.x += planets[i].acceleration.x;
		planets[i].velocity.y += planets[i].acceleration.y;


		// Set max X-velocity
		if (planets[i].velocity.x > max_speed) {
			planets[i].velocity.x = max_speed;
			cout << "Planet " << i << " hit max speed." << endl;
		}
		if (planets[i].velocity.x < -max_speed) {
			planets[i].velocity.x = -max_speed;
			cout << "Planet " << i << " hit max speed." << endl;
		}
		// Set max Y-velocity
		if (planets[i].velocity.y > max_speed) {
			planets[i].velocity.y = max_speed;
			cout << "Planet " << i << " hit max speed." << endl;
		}
		if (planets[i].velocity.y < -max_speed) {
			planets[i].velocity.y = -max_speed;
			cout << "Planet " << i << " hit max speed." << endl;
		}
	}




	for (unsigned i = 0; i < planets.size(); i++) {
		planets[i].update();
	}

	resetVectors();
}


// Calculates the force components for all the planets
void ofApp::calculateForceComponents() {

	for (unsigned i = 0; i < planets.size(); i++) {
		for (unsigned j = 0; j < planets.size(); j++) {
			if (i != j) {

				// Will never divide by zero becuase we check to destroy a planet before this
				// Magnitude of all the force on the planet, F = G*M1*M2/(d^2)
				main_force_holder = gravitational_constant * planets[i].mass * planets[j].mass /
					ofDistSquared(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y);


				// X-component of the force
				// Fx = F * ((x2 - x1) / d), Fx = the force proportional to the x distance
				if (planets[i].position.x > planets[j].position.x) {
					force_x_holder = ((planets[j].position.x - planets[i].position.x) /
						ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y)) * main_force_holder;
				}
				else if (planets[i].position.x < planets[j].position.x) {
					force_x_holder = ((planets[j].position.x - planets[i].position.x) /
						ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y)) * main_force_holder;
				}

				// Y-component of the force
				if (planets[i].position.y > planets[j].position.y) {
					force_y_holder = ((planets[j].position.y - planets[i].position.y) /
						ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y)) * main_force_holder;
				}
				else if (planets[i].position.y < planets[j].position.y) {
					force_y_holder = ((planets[j].position.y - planets[i].position.y) /
						ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y)) * main_force_holder;
				}

				planets[i].force_components.x += force_x_holder;
				planets[i].force_components.y += force_y_holder;

				main_force_holder = 0;
				force_x_holder = 0;
				force_y_holder = 0;
			}
		}
	}
}


// Calculate the velocity of each planet
void ofApp::calculateVelocity() {
	for (unsigned i = 0; i < planets.size(); i++) {

		// Acceleration = Force / Mass
		planets[i].acceleration.x = planets[i].force_components.x / planets[i].mass;
		planets[i].acceleration.y = planets[i].force_components.y / planets[i].mass;

		// Taken from: https://github.com/conorrussomanno/conorRussomanno_algo2012/blob/master/wk5_planet_simulation/src/Planet.h
		planets[i].velocity.x += planets[i].acceleration.x;
		planets[i].velocity.y += planets[i].acceleration.y;
	}

	checkMaxVelocity();
}

void ofApp::checkMaxVelocity() {
	for (int i = 0; i < planets.size(); i++) {

		// Set max X-velocity
		if (planets[i].velocity.x > max_speed) {
			planets[i].velocity.x = max_speed;
			cout << "Planet " << i << " hit max speed." << endl;
		}
		if (planets[i].velocity.x < -max_speed) {
			planets[i].velocity.x = -max_speed;
			cout << "Planet " << i << " hit max speed." << endl;
		}
		// Set max Y-velocity
		if (planets[i].velocity.y > max_speed) {
			planets[i].velocity.y = max_speed;
			cout << "Planet " << i << " hit max speed." << endl;
		}
		if (planets[i].velocity.y < -max_speed) {
			planets[i].velocity.y = -max_speed;
			cout << "Planet " << i << " hit max speed." << endl;
		}
	}
}


// Draw all the planet's
void ofApp::draw() {
	ofBackgroundGradient(ofColor(60, 60, 60), ofColor(10, 10, 10));

	//3d
	//cam.begin();

	for (unsigned int i = 0; i < planets.size(); i++) {
		planets[i].draw();
	}

	//3D
	//ofDrawGridPlane(20, 50, false);
	
	// Draw frame stuff
	ofSetColor(244, 244, 244);
	string frame_num = "Frame: " + ofToString(ofGetFrameNum(), 4);
	ofDrawBitmapString(frame_num, 100, 100);
	string frame_rate = "Frame rate: " + ofToString(ofGetFrameRate(), 4);
	ofDrawBitmapString(frame_rate, 100, 110);

	// Better way to do this?
	// Doesn't work because can go back to zero if slow down
	string time = "Days: " + ofToString((seconds / 86400.0f) * velocity_factor, 4);
	ofDrawBitmapString(time, 100, 120);
	
	//3d
	//cam.end();

	
}


// Totally reset the simulation to start simulation
void ofApp::resetSimulation() {
	for (unsigned int i = 0; i < planets.size(); i++) {
		planets[i].totalReset();
	}

	main_force_holder = 0;
	force_x_holder = 0;
	force_y_holder = 0;
}


// Reset all vector's but velocity so they can be updated
void ofApp::resetVectors() {
	for (unsigned int i = 0; i < planets.size(); i++) {
		planets[i].reset();
	}
}


// Destory planets when collide - will throw error if two many collide at one time
void ofApp::destroy() {
	for (unsigned i = 0; i < planets.size(); i++) {
		for (unsigned j = 0; j < planets.size(); j++) {

			if (i != j) {
				// Change to area of circle
				if (planets[i].radius + planets[j].radius >
					ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y) + collision_distance_helper) {

					// Bigger planet absorbs littler planet
					if (planets[i].radius > planets[j].radius) {

						planets[i].mass += planets[j].mass;
						planets.erase(planets.begin() + j);
					}
					else {
						planets[j].mass += planets[i].mass;
						planets.erase(planets.begin() + i);
					}
				}
			}

		}
	}

}


/**********************************************************/


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_F12) {
		ofToggleFullscreen();
		return;
	}

	int upper_key = toupper(key); // Standardize on upper case

	if (key == OF_KEY_RIGHT) {
		velocity_factor *= 2;
	} 
	else if (key == OF_KEY_LEFT) {
		velocity_factor /= 2;
	}

	cout << velocity_factor << endl;
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