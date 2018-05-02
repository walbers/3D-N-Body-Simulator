#include "settings.h"

// Put all constants in here or just the ones needed for ofApp and planet?

extern int planets_left = 0;
extern int number_of_planets = 150;						// ik gets laggy at 400, with tails 100
extern float velocity_factor = 1;						// Changes velocity and time, 1m = 6.6846e-12 AU, 6.4e6m = Rearth, lets say earth is 6 px radius, each pixel is 1e6m

extern const float max_speed = 40;						// Max speed so planets don't skip over each other
extern const float collision_distance_helper = 5;		// Can control when planets collide
extern const float gravitational_constant = 6.67e-11;	// 6.67408e-11 is the real value

extern simulationState current_mode = INTRO;

//extern float distance_factor = 1e6;