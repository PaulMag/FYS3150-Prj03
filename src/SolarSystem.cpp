#include <iostream>
#include <armadillo>
#include <sstream>
#include "SolarSystem.hpp"

using namespace std;
using namespace arma;

/*
 * Constants
 */
const double GRAV_CONST = 6.67384e-11; // [m^3 kg^-1 s^-2]
const int DIMENSIONALITY = 2;
const string OBJECTS_DATA_PATH = "../data/objects";

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
 * Can be initialized at certain time.
 */
SolarSystem :: SolarSystem(double t) {
  this->t = t;
}

/*
 * Constructor that takes datafile. An already setup system can be read from
 * this file. Assumes file is in a certain syntax.
 *
 * @param systemfile The file to read the system data from.
 */
SolarSystem :: SolarSystem(string systemfile) {
  // File relevant
  ifstream datafile;
  datafile.open(systemfile.c_str());
  string line,col,id;

  bool record = false; // Switch for knowing when past meta in datafile
  double x0,y0,v0x,v0y,m;
  vector<string> data;

  while (datafile.good()) {
    if (!record) {
      datafile >> line;
      if (strcmp(line.c_str(),"#DATA#") == 0) { record = true; }
    } else {
      datafile >> id >> x0 >> y0 >> v0x >> v0y >> m;

      if (!datafile.good()) { break; }

      vec position; position << x0 << y0;
      vec velocity; velocity << v0x << v0y;

      ostringstream oss;
      oss << OBJECTS_DATA_PATH << "/" << id << ".dat";
      string savefile = oss.str();

      CelestialObject newObject = CelestialObject(id,position,velocity,m,savefile);
      addObject(newObject);
    }
  }

  datafile.close();
}

/*
 * Advances the solar system by a given timestep via the RungeKutta4 scheme.
 * This implementation makes it easier to use adaptive methods later since
 * timestep can be varied.
 *
 * Huge problem in implementation. There are four steps in the Runge Kutta 4
 * method. For each step you can't only move one object. You have to move them
 * all so that the all forces follow. Therefore, have to calculate every object
 * in one go.
 *
 * @param dt The timestep to advance.
 */
void SolarSystem :: advance(double dt) {
  double M;

  // Solve once to find all new velocities
  for (int i = 0; i < getNoOfObjects(); i++) {
    vn.col(i) = objects[i].getV();
    vK1.col(i) = getForces(objects[i]) / objects[i].getM();
  }
  for (int i = 0; i < getNoOfObjects(); i++) {
    objects[i].setV( vn.col(i) + 0.5*dt*vK1.col(i) );
  }

  // Solve again to find all new positions

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

/*
 * Returns a double representing the total force working on this object from
 * all other objects in the system.
 */
arma::vec SolarSystem :: getForces(CelestialObject object) {
  vec force = zeros(DIMENSIONALITY); vec r;

  for (int i = 0; i < getNoOfObjects(); i++) {
    // Not find force from itself
    if (strcmp(objects[i].getId().c_str(),object.getId().c_str()) == 0) { continue; }

    // Gravitational force
    r = object.getDistTo(objects[i]);
    force += GRAV_CONST * (object.getM()*objects[i].getM()) / r;
  }

  return force;
}

int SolarSystem :: getNoOfObjects() { return objects.size(); }
double SolarSystem :: getT() { return t; }
