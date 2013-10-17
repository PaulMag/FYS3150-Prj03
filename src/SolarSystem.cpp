#include "SolarSystem.hpp"
#include <fstream>
#include <iostream>

/*
 * Constructors
 */

/*
 * No arg constructor only sets atributes.
 */
SolarSystem :: SolarSystem() {
  t = 0;
}

/*
 * Constructor that takes datafile. An already setup system can be read from
 * this file. Assumes file is in a certain syntax.
 *
 * @param systemfile The file to read the system data from.
 */
SolarSystem :: SolarSystem(std::string systemfile) {
  // File relevant
  std::ifstream datafile;
  datafile.open(systemfile.c_str());
  std::string line,col;

  bool record = false; // Switch for knowing when past meta in datafile
  double x0,y0,v0x,v0y,m;
  std::string id;
  int c; // Counter
  std::vector<std::string> data;

  // Loop through file lines
  while (std::getline(datafile, line)) {
    if (std::strcmp(line.c_str(),"#DATA#") == 0) {
      record = true;
    }
    if (record) {
      c = 0;
      while (std::getline(datafile, col, ' ')) {
        /*
         * There must be a better way to do this
         */
        switch (c) {
          case 0:
            id = col;
            break;
          case 1:
            x0 = atof(col.c_str());
            break;
          case 2:
            y0 = atof(col.c_str());
            break;
          case 3:
            v0x = atof(col.c_str());
            break;
          case 4:
            v0y = atof(col.c_str());
            break;
          case 5:
            m = atof(col.c_str());
            break;
        }
        c++;
      }
      // Completed read of one object, now create it
      CelestialObject newObject = CelestialObject(id,x0,y0,v0x,v0y,m);
      addObject(newObject);
    }
  }
}

/*
 * Advances the solar system by a given timestep via the RungeKutta4 scheme.
 * This implementation makes it easier to use adaptive methods later since
 * timestep can be varied.
 *
 * @param dt The timestep to advance.
 */
void SolarSystem :: advance(double dt) {
  //TODO

  // After advance
  t += dt;
}

/*
 * Adds a new celestial object to the collection of objects.
 *
 * @param newObject The new object. Instance of `CelestialObject`.
 */
void SolarSystem :: addObject(CelestialObject newObject) {
  objects.push_back(newObject);
}

/*
 * Get functions
 */
int SolarSystem :: getNoOfObjects() { return objects.size(); }
