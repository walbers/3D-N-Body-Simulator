#include "planet.h"

planet::planet() {
	// Change so their are more smaller and less bigger planets
	// Look up a factor for proportionality
	radius = ofRandom(3, 25);
	mass = ofRandom(0, 2) * radius * 1.0e7; // mass scales with radius, earth and mars scale ~1.0e6-1.07 from radius to mass
	
	/*
	if (ofRandom(0, 100) < 2) {
		radius = 80;
		mass = 5 * radius * 1.0e8;
	}
	*/
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
	reset();
}

// Update the planet's position
void planet::update() {
	position.x += velocity.x;
	position.y += velocity.y;
}

// Draw the planet
void planet::draw() {
	ofSetColor(66, 83, 244); // blue
	ofDrawCircle(position.x, position.y, radius);
	ofSetColor(244, 83, 66); // red
	ofDrawBitmapString(mass, position.x, position.y);

	// Arrow pointing code - doesn't work
	/*
	ofSetColor(83, 244, 66);
	ofVec3f arrowTailPoint(position.x, position.y);
	ofVec3f arrowHeadPoint(acceleration.x, acceleration.y);
	ofDrawArrow(arrowTailPoint, arrowHeadPoint, 15.0);
	*/
}

// Draw planet if it has reached max speed
void planet::drawMax() {
	ofSetColor(83, 244, 66); // green
	ofDrawCircle(position.x, position.y, radius);
	ofSetColor(244, 83, 66); // red
	ofDrawBitmapString(mass, position.x, position.y);
}

void planet::checkMaxSpeed() {
	//max_speed = 20;
}
