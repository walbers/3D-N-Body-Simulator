#include "planet.h"
#include "settings.h"

planet::planet() {
	// Change so their are more smaller and less bigger planets
	// Change to density
	radius = ofRandom(3, 25);
	mass = ofRandom(0, 2) * radius * 1.0e7; // mass scales with radius, earth and mars scale ~1.0e6-1.07 from radius to mass, mass of earth 6x10^24

											/*
											if (ofRandom(0, 100) < 1) {
											createSun();
											}
											*/
}

void planet::createSun() {
	radius = 80;
	mass = 5 * radius * 1.0e8;
}

// Reset some of the planet's vectors to be recalculated - not velocity becuase that's accumalated
void planet::reset() {
	force_components.x = 0;
	force_components.y = 0;
	force_components.z = 0;
	acceleration.x = 0;
	acceleration.y = 0;
	acceleration.z = 0;
}

// Reset the whole simulation - used to setup the simulation
void planet::totalReset() {
	if (current_mode == CLASSIC_3D) {
		position.x = ofRandomHeight();
		position.y = ofRandomHeight();
		position.z = ofRandomHeight();
	}
	else {
		position.x = ofRandomWidth();
		position.y = ofRandomHeight();
		position.z = ofRandomHeight();
	}
	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;

	past_centers.push_back(position);

	reset();
}

// Update the planet's position and remember the past one
void planet::update() {
	// Need to check with max speed
	position.x += (velocity.x * velocity_factor);
	position.y += (velocity.y * velocity_factor);
	position.z += (velocity.z * velocity_factor);

	// Store planet's past centers for planet tail's (50 because any higher makes the program lag)
	if (planets_left < 50) {
		past_centers.push_back(position);
		if (past_centers.size() > length_of_tail) {
			past_centers.erase(past_centers.begin());
		}
	}
}

// Draw the planet and it's accessories
void planet::draw() {

	if (current_mode == CLASSIC_2D) {
		// Draw planet
		ofSetColor(66, 83, 244); // blue
		ofDrawCircle(position.x, position.y, radius);

		// Draw planet's mass
		ofSetColor(244, 83, 66); // red
		ofDrawBitmapString(mass / 1.0e7, position.x, position.y);

		// Draw planet's tail
		if (planets_left < 50) {
			ofSetColor(83, 244, 66); // green
			for (unsigned i = 0; i < past_centers.size(); i++) {
				ofDrawCircle(past_centers[past_centers.size() - i - 1].x, past_centers[past_centers.size() - i - 1].y, 2);
			}
		}
	}

	else if (current_mode == CLASSIC_3D) {

		// Draw planet
		ofSetColor(66, 83, 244); // blue
		ofDrawSphere(position.x, position.y, position.z, radius);

		// Draw planet's tail
		if (planets_left < 50) {
			ofSetColor(83, 244, 66); // green
			for (unsigned i = 0; i < past_centers.size(); i++) {
				ofDrawSphere(past_centers[past_centers.size() - i - 1].x, past_centers[past_centers.size() - i - 1].y, past_centers[past_centers.size() - i - 1].z, 2);
			}
		}
	}
}