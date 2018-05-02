#pragma once
#ifndef SETTINGS_H
#define SETTINGS_H

enum simulationState {
	INTRO,
	CLASSIC_2D,
	CLASSIC_3D,
	SOLAR_SYSTEM_2D
};

extern int planets_left;
extern int number_of_planets;
extern float velocity_factor;

extern const float max_speed;
extern const float collision_distance_helper;
extern const float gravitational_constant;

extern simulationState current_mode;



//extern float distance_factor;
#endif