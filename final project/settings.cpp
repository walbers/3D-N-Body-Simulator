#include "settings.h"

// Put all constants in here or just the ones needed for ofApp and planet?

extern float velocity_factor = 1;				// Changes velocity and time
extern float max_speed = 40;					// Max speed so planets don't skip over each other
extern float collision_distance_helper = 5;		// Can control when planets collide
extern int number_of_planets = 150;				// ik gets laggy at 400, with tails 100
extern float gravitational_constant = 8.0e-14;	// 6.67408e10-11 is the real value
// Better way to do this?
extern int planets_left = 0;					