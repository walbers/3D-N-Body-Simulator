#include "ofApp.h"
#include <cmath>
#include <iomanip>
#include "../settings.h"


// Setup all the variables and reset the simulation
void ofApp::setup() {

	// Default is true - tries to set frame rate to monitor refresh rate
	ofSetVerticalSync(false);
	// So time moves consistently because 1 frame is 1 second when velocity_factor = 1
	ofSetFrameRate(30);
	// Sets circle resolution
	ofSetCircleResolution(100);
	seconds = 0;
	current_mode = INTRO;

	// Create array of planets
	for (int i = 0; i < number_of_planets; i++) {
		planets.push_back(planet());
	}

	resetSimulation();
}

void ofApp::reset() {

	planets.clear();
	seconds = 0;

	// Create array of planets
	for (int i = 0; i < number_of_planets; i++) {
		planets.push_back(planet());
	}

	resetSimulation();

	restart = false;
}


// Updates everything about the planets in order to orbit.
void ofApp::update() {


	if (current_mode == INTRO) {
		if (restart == true) {
			reset();
		}
	}

	else if (current_mode == CLASSIC_2D || current_mode == SOLAR_SYSTEM_2D) {

		if (restart == true) {
			
			if (current_mode == CLASSIC_2D) {
				number_of_planets = 100;
			}
			else {
				number_of_planets = 3;
			}

			reset();
		}
		else {

			seconds += (1 * velocity_factor);

			planets_left = planets.size();

			destroy2d();
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
	}

	else if (current_mode == CLASSIC_3D) {
		if (restart == true) {
			number_of_planets = 100;
			reset();
		}
		else {
			seconds += (1 * velocity_factor);

			planets_left = planets.size();

			destroy3d();
			for (unsigned i = 0; i < planets.size(); i++) {
				for (unsigned j = 0; j < planets.size(); j++) {

					if (i != j) {

						// Will never divide by zero becuase we check to destroy a planet before this
						// Magnitude of all the force on the planet, F = G*M1*M2/(d^2)
						main_force_holder = gravitational_constant * planets[i].mass * planets[j].mass /
							ofDistSquared(planets[i].position.x, planets[i].position.y, planets[i].position.z, planets[j].position.x, planets[j].position.y, planets[j].position.z);


						// X-component of the force
						// Fx = F * ((x2 - x1) / d), Fx = the force proportional to the x distance
						if (planets[i].position.x > planets[j].position.x) {
							force_x_holder = ((planets[j].position.x - planets[i].position.x) /
								ofDist(planets[i].position.x, planets[i].position.y, planets[i].position.z, planets[j].position.x, planets[j].position.y, planets[j].position.z)) * main_force_holder;
						}
						else if (planets[i].position.x < planets[j].position.x) {
							force_x_holder = ((planets[j].position.x - planets[i].position.x) /
								ofDist(planets[i].position.x, planets[i].position.y, planets[i].position.z, planets[j].position.x, planets[j].position.y, planets[j].position.z)) * main_force_holder;
						}

						// Y-component of the force
						if (planets[i].position.y > planets[j].position.y) {
							force_y_holder = ((planets[j].position.y - planets[i].position.y) /
								ofDist(planets[i].position.x, planets[i].position.y, planets[i].position.z, planets[j].position.x, planets[j].position.y, planets[j].position.z)) * main_force_holder;
						}
						else if (planets[i].position.y < planets[j].position.y) {
							force_y_holder = ((planets[j].position.y - planets[i].position.y) /
								ofDist(planets[i].position.x, planets[i].position.y, planets[i].position.z, planets[j].position.x, planets[j].position.y, planets[j].position.z)) * main_force_holder;
						}

						// Z-component of the force
						if (planets[i].position.z > planets[j].position.z) {
							force_z_holder = ((planets[j].position.x - planets[i].position.x) /
								ofDist(planets[i].position.x, planets[i].position.y, planets[i].position.z, planets[j].position.x, planets[j].position.y, planets[j].position.z)) * main_force_holder;
						}
						else if (planets[i].position.z < planets[j].position.z) {
							force_z_holder = ((planets[j].position.x - planets[i].position.x) /
								ofDist(planets[i].position.x, planets[i].position.y, planets[i].position.z, planets[j].position.x, planets[j].position.y, planets[j].position.z)) * main_force_holder;
						}

						planets[i].force_components.x += force_x_holder;
						planets[i].force_components.y += force_y_holder;
						planets[i].force_components.z += force_z_holder;

						main_force_holder = 0;
						force_x_holder = 0;
						force_y_holder = 0;
						force_z_holder = 0;
					}
				}

				// Acceleration = Force / Mass
				planets[i].acceleration.x = planets[i].force_components.x / planets[i].mass;
				planets[i].acceleration.y = planets[i].force_components.y / planets[i].mass;
				planets[i].acceleration.z = planets[i].force_components.z / planets[i].mass;

				// Taken from: https://github.com/conorrussomanno/conorRussomanno_algo2012/blob/master/wk5_planet_simulation/src/Planet.h
				planets[i].velocity.x += planets[i].acceleration.x;
				planets[i].velocity.y += planets[i].acceleration.y;
				planets[i].velocity.z += planets[i].acceleration.z;


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
	}
}


// Draw the different mode's
void ofApp::draw() {
	if (current_mode == INTRO) {
		drawIntro();
	}
	else if (current_mode == CLASSIC_2D || current_mode == SOLAR_SYSTEM_2D) {
		draw2d();
	}
	else if (current_mode == CLASSIC_3D) {
		draw3d();
	}
}


// Draws the intro mode
void ofApp::drawIntro() {
	ofBackgroundGradient(ofColor(60, 60, 60), ofColor(10, 10, 10));
	ofSetColor(244, 244, 244);
	ofDrawBitmapString("Click 1 to come to this screen\nClick 2 to watch planets in 2d\nClick 3 to watch planets 3d\nClick 4 to watch planets in a solar system", 100, 130);
}

// Draws the 2d mode
void ofApp::draw2d() {
	ofBackgroundGradient(ofColor(60, 60, 60), ofColor(10, 10, 10));

	// Draw's planets
	for (unsigned int i = 0; i < planets.size(); i++) {
		planets[i].draw();
	}

	// Draw frame rate and time
	ofSetColor(244, 244, 244);
	string frame_rate = "Frame rate: " + ofToString(ofGetFrameRate(), 4);
	ofDrawBitmapString(frame_rate, 100, 110);
	string days = "Total days: " + ofToString((seconds / 86400.0f), 4);
	ofDrawBitmapString(days, 100, 120);
	string years = "Total years: " + ofToString((seconds / 31536000.0f), 4);
	ofDrawBitmapString(years, 100, 130);
}


// Draws the 3d mode
void ofApp::draw3d() {
	ofBackgroundGradient(ofColor(60, 60, 60), ofColor(10, 10, 10));

	// Starts camera for viewing in 3d
	cam.begin();

	// Draw's planets
	for (unsigned int i = 0; i < planets.size(); i++) {
		planets[i].draw();
	}

	// Draws grid for reference when in 3d
	ofSetColor(ofColor::deepPink);
	ofDrawGridPlane(20, 50, false);

	// Draw frame rate and time
	ofSetColor(244, 244, 244);
	string frame_rate = "Frame rate: " + ofToString(ofGetFrameRate(), 4);
	ofDrawBitmapString(frame_rate, 100, 110);
	string days = "Total days: " + ofToString((seconds / 86400.0f), 4);
	ofDrawBitmapString(days, 100, 120);
	string years = "Total years: " + ofToString((seconds / 31536000.0f), 4);
	ofDrawBitmapString(years, 100, 130);

	cam.end();
}


// Totally reset the simulation to start simulation
void ofApp::resetSimulation() {
	for (unsigned int i = 0; i < planets.size(); i++) {
		planets[i].totalReset();
	}

	main_force_holder = 0;
	force_x_holder = 0;
	force_y_holder = 0;
	force_z_holder = 0;
}


// Reset all vector's but velocity so they can be updated
void ofApp::resetVectors() {
	for (unsigned int i = 0; i < planets.size(); i++) {
		planets[i].reset();
	}
}


// Destory planets when collide in 2d mode - will throw error if two many collide at one time
void ofApp::destroy2d() {
	for (unsigned i = 0; i < planets.size(); i++) {
		for (unsigned j = 0; j < planets.size(); j++) {
			if (i != j) {

				// Check if radii are touch and the planets are inside each other by the helper amount
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

// Destory planets when collide in 3d mode - will throw error if two many collide at one time
void ofApp::destroy3d() {
	for (unsigned i = 0; i < planets.size(); i++) {
		for (unsigned j = 0; j < planets.size(); j++) {
			if (i != j) {

				// Check if radii are touch and the planets are inside each other by the helper amount
				if (planets[i].radius + planets[j].radius >
					ofDist(planets[i].position.x, planets[i].position.y, planets[i].position.z, 
						planets[j].position.x, planets[j].position.y, planets[j].position.z) + collision_distance_helper) {

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

// Speeds up or slows down time with arrow's or switches modes with 1, 2, 3, or 4
void ofApp::keyPressed(int key) {
	if (key == OF_KEY_F12) {
		ofToggleFullscreen();
		return;
	}

	if (key == OF_KEY_RIGHT) {
		velocity_factor *= 2;
	}
	else if (key == OF_KEY_LEFT) {
		velocity_factor /= 2;
	}
	else if (key == '1') {
		current_mode = INTRO;
		restart = true;
	}
	else if (key == '2') {
		current_mode = CLASSIC_2D;
		restart = true;
	}
	else if (key == '3') {
		current_mode = CLASSIC_3D;
		restart = true;
	}
	else if (key = '4') {
		current_mode = SOLAR_SYSTEM_2D;
		restart = true;
	}
}