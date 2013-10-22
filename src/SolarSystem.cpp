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
const string DATA_PATH = "../data";

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
      oss << DATA_PATH << "/" << id << ".dat";
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
  colvec force = zeros<colvec>(DIMENSIONALITY);
  mat K1 = zeros<mat>(getNoOfObjects(),DIMENSIONALITY);
  mat K2 = zeros<mat>(getNoOfObjects(),DIMENSIONALITY);
  mat K3 = zeros<mat>(getNoOfObjects(),DIMENSIONALITY);
  mat K4 = zeros<mat>(getNoOfObjects(),DIMENSIONALITY);
  mat yn = zeros<mat>(getNoOfObjects(),DIMENSIONALITY);
  mat vn = zeros<mat>(getNoOfObjects(),DIMENSIONALITY);

  // K1 for everybody
  for (int i = 0; i < getNoOfObjects(); i++) {
    // Storage
    vn.col(i) = objects[i].getV();
    yn.col(i) = objects[i].getPos();

    // K1
    force = getForces(objects[i]);
    K1.col(i) = force / objects[i].getM();

    // Move must be done for all before calculating K2
    objects[i].setV(vn.col(i) + 0.5*dt*K1.col(i));
    objects[i].setPos(yn.col(i) + 0.5*dt*objects[i].getV());
  }

  // K2 for everybody
  for (int i = 0; i < getNoOfObjects(); i++) {
    // K2
    force = getForces(objects[i]);
    K2.col(i) = force / objects[i].getM();

    // Again, move before calculating K3
    objects[i].setV(vn.col(i) + 0.5*dt*K2.col(i));
    objects[i].setPos(yn.col(i) + 0.5*dt*objects[i].getV());
  }

  // K3 for everybody
  for (int i = 0; i < getNoOfObjects(); i++) {
    // K3
    force = getForces(objects[i]);
    K3.col(i) = force / objects[i].getM();

    // Move for calculating K4
    objects[i].setV(vn.col(i) + dt*K3.col(i));
    objects[i].setPos(yn.col(i) + dt*objects[i].getV());
  }

  // K4 for everybody and final real move
  for (int i = 0; i < getNoOfObjects(); i++) {
    // K4
    force = getForces(objects[i]);
    K4.col(i) = force / objects[i].getM();

    // Final move
    objects[i].setV( vn.col(i) + (1./6) * (K1.col(i) + 2*K2.col(i) + 2*K3.col(i) + K4.col(i)) );
    objects[i].setPos( yn.col(i) + (1./6) * (K1.col(i) + 2*K2.col(i) + 2*K3.col(i) + K4.col(i)) );

    // After final move, save coordinates
    objects[i].saveCurrentPos();
  }

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
  vec force = zeros(DIMENSIONALITY); arma::vec r;

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
