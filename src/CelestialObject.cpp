#include <fstream>
#include <iostream>
#include "CelestialObject.hpp"

using namespace std;
using namespace arma;

/*
 * @param id Short string describing object.
 */
CelestialObject :: CelestialObject(string id, vec coors, vec vel, double m, string savefile) {
  this->m = m;
  this->pos = coors;
  this->v = vel;
  this->id = id;
  this->savefile = savefile;

  // Write header to savefile
  ofstream outfile;
  outfile.open(savefile.c_str());
  outfile << "Positions for: " << getId() << std::endl << "#syntax: x y" << std::endl;;
  outfile.close();
}

/*
 * Set functions
 */

/*
 * Saves the current force exerted on the this object.
 *
 * @param newF The force exerted.
 */
void CelestialObject :: setF(arma::vec newF) {
  F = newF;
}

/*
 * Set new positions.
 */
void CelestialObject :: setPos(arma::vec newPos) {
  pos = newPos;
}

/*
 * Updates velocity of object.
 */
void CelestialObject :: setV(arma::vec newVel) {
  v = newVel;
}

/*
 * Stores current position to its given savefile.
 */
void CelestialObject :: saveCurrentPos() {
  ofstream outfile;
  outfile.open(savefile.c_str(), std::ios::app);
  outfile << getPos()[0] << " " << getPos()[1] << std::endl;
  outfile.close();
}

/*
 * Get functions
 */

/*
 * Returns the distance from this object to a different one.
 *
 * @param other The other celestial object to find distance to.
 */
arma::vec CelestialObject :: getDistTo(CelestialObject other) {
  vec dist = other.getPos() - getPos();
  return dist;
}

double CelestialObject :: getM() { return m; }
arma::vec CelestialObject :: getPos() { return pos; }
arma::vec CelestialObject :: getV() { return v; }
arma::vec CelestialObject :: getForce() { return F; }
std::string CelestialObject :: getId() { return id; }
