#include <iostream>
#include <armadillo>
#include <sstream>
#include "SolarSystem.hpp"

using namespace std;

/*
 * Constants
 */
const double GRAV_CONST = 6.67384e-11; // [m^3 kg^-1 s^-2]
const int DIMENSIONALITY = 2;
const std::string DATA_PATH = "../data";

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
  t = t;
}

/*
 * Constructor that takes datafile. An already setup system can be read from
 * this file. Assumes file is in a certain syntax.
 *
 * @param systemfile The file to read the system data from.
 */
SolarSystem :: SolarSystem(std::string systemfile) {
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
      cout << "id: " << id << " m: " << m << endl;
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
  arma::vec force = arma::zeros<arma::vec>(DIMENSIONALITY);
  arma::mat K1,K2,K3,K4,vn,yn = arma::zeros<arma::mat>(getNoOfObjects(),DIMENSIONALITY);

  // K1 for everybody
  for (int i = 0; i < getNoOfObjects(); i++) {
    // Storage
    vn.row(i) = objects[i].getV();
    yn.row(i) = objects[i].getPos();

    // K1
    force = getForces(objects[i]);
    K1.row(i) = force / objects[i].getM();

    // Move must be done for all before calculating K2
    objects[i].setV(vn.row(i) + 0.5*dt*K1.row(i));
    objects[i].setPos(yn.row(i) + 0.5*dt*objects[i].getV());
  }

  // K2 for everybody
  for (int i = 0; i < getNoOfObjects(); i++) {
    // K2
    force = getForces(objects[i]);
    K2.row(i) = force / objects[i].getM();

    // Again, move before calculating K3
    objects[i].setV(vn.row(i) + 0.5*dt*K2.row(i));
    objects[i].setPos(yn.row(i) + 0.5*dt*objects[i].getV());
  }

  // K3 for everybody
  for (int i = 0; i < getNoOfObjects(); i++) {
    // K3
    force = getForces(objects[i]);
    K3.row(i) = force / objects[i].getM();

    // Move for calculating K4
    objects[i].setV(vn.row(i) + dt*K3.row(i));
    objects[i].setPos(yn.row(i) + dt*objects[i].getV());
  }

  // K4 for everybody and final real move
  for (int i = 0; i < getNoOfObjects(); i++) {
    // K4
    force = getForces(objects[i]);
    K4.row(i) = force / objects[i].getM();

    // Final move
    objects[i].setV( vn.row(i) + (1./6) * (K1.row(i) + 2*K2.row(i) + 2*K3.row(i) + K4.row(i)) );
    objects[i].setPos( yn.row(i) + (1./6) * (K1.row(i) + 2*K2.row(i) + 2*K3.row(i) + K4.row(i)) );

    // After final move, save coordinates
    objects[i].saveCurrentPos();
  }

  // After advance
  t += dt;
}

/*
 * Adds a new celestial object to the collection of objects. This also
 * automatically sets a savefile for the object.
 *
 * @param newObject The new object. Instance of `CelestialObject`.
 */
void SolarSystem :: addObject(CelestialObject newObject) {
  objects.push_back(newObject);
  
  std::ostringstream oss;
  oss << DATA_PATH << "/" << newObject.getId() << ".dat";
  newObject.setSavefile(oss.str());
}

/*
 * Get functions
 */

/*
 * Returns a double representing the total force working on this object from
 * all other objects in the system.
 */
arma::vec SolarSystem :: getForces(CelestialObject object) {
  arma::vec force = arma::zeros(DIMENSIONALITY); arma::vec r;

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
