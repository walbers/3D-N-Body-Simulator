#pragma once
#ifndef SETTINGS_H
#define SETTINGS_H

enum simulationState {
	INTRO,
	CLASSIC_2D,
	CLASSIC_3D,
	SOLAR_SYSTEM_2D
};

extern bool create_sun;
extern bool restart;
extern int planets_left;
extern int number_of_planets;
extern float velocity_factor;
extern simulationState current_mode;

extern const int length_of_tail;
extern const float max_speed;
extern const float collision_distance_helper;
extern const float gravitational_constant;

#endif