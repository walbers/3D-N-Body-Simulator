# Development
Problems:
 - the .assign() method doesn't get random values when creating multiple objects
 - splitting force into component's became tricky
 - finding a collision distance for planets
 - sharing data between classes
 - switching between simulations
 - drawing planet's tails
 - running the program efficiently (lag issues)
 - scaling velocity
 - keeping track of time/changing time
 - tuning variables
 
 Solutions:
  - Using a for loop
  - Making sure the data isn't going out of range or below range for it's type
  - Used radius of planets with a help distance variable
  - Using a settings class with extern
  - used enumerated types
  - kept a vector of a certain amount of the planet's past centers
  - Keeping if statements to a minimum and not making extreme for loops
  - Used the settings class
  - Used the scaling velocity to speed or slow time and defined 1 sec as each time the update method is called
  - Looked up realistic values, to make up for distance differences used velocity scaling
