#include "settings.h"

extern int planets_left = 0;
extern int number_of_planets = 100;						// Past 150 it starts to lag heavily
extern float velocity_factor = 1024;						// Changes velocity and time
extern bool restart = true;								// Bool to keep track of when changing modes
extern bool create_sun = false;
extern simulationState current_mode = INTRO;

extern const int length_of_tail = 50;
extern const float max_speed = 40;						// Max speed so planets don't skip over each other
extern const float collision_distance_helper = 5;		// Can control when planets collide
extern const float gravitational_constant = 6.67e-11;	// Gravitational constant from the equation

