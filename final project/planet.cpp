#include "planet.h"

planet::planet() {
	// Change so their are more smaller and less bigger planets
	// Look up a factor for proportionality
	radius = ofRandom(3, 25);
	mass = ofRandom(0, 2) * radius * 1.0e7; // mass scales with radius, earth and mars scale ~1.0e6-1.07 from radius to mass
	
	createSun();
}

void planet::createSun() {
	if (ofRandom(0, 100) < 1) {
		radius = 80;
		mass = 5 * radius * 1.0e8;
	}
}

// Reset some of the planet's vectors to be recalculated - not velocity becuase that's accumalated
void planet::reset() {
	force_components.x = 0;
	force_components.y = 0;
	acceleration.x = 0;
	acceleration.y = 0;
}

// Reset the whole simulation - used to setup the simulation
void planet::totalReset() {
	position.x = ofRandomWidth();
	position.y = ofRandomHeight();
	velocity.x = 0;
	velocity.y = 0;
	
	past_centers.push_back(position);

	reset();
}

// Update the planet's position
void planet::update() {
	position.x += velocity.x;
	position.y += velocity.y;
	past_centers.push_back(position);

	if (past_centers.size() > 60) {
		past_centers.erase(past_centers.begin());
	}
}

// Draw the planet
void planet::draw() {
	ofSetCircleResolution(100);
	ofSetColor(66, 83, 244); // blue
	ofDrawCircle(position.x, position.y, radius);
	//ofDrawSphere(position.x, position.y, radius);			//3d
	ofSetColor(244, 83, 66); // red
	ofDrawBitmapString(mass / 1.0e7 , position.x, position.y);

	ofSetColor(83, 244, 66);
	for (unsigned i = 0; i < past_centers.size(); i++) {
		ofDrawCircle(past_centers[past_centers.size() - i - 1].x, past_centers[past_centers.size() - i - 1].y, 2);
	}
	
	//ofDrawCurve(1, 1, past_centers[0][0][0], )
	//ofDrawLine(position.x -10, position.y - 10, position.x, position.y);
}