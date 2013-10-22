#include <fstream>
#include <iostream>
#include "CelestialObject.hpp"

/*
 * @param id Short string describing object.
 */
CelestialObject :: CelestialObject(std::string id, arma::vec coors, arma::vec vel, double m) {
  this->m = m;
  this->pos = coors;
  this->v = vel;
  this->id = id;
  savefile = "<not_set>";
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
 * Stores name of savefile
 */
void CelestialObject :: setSavefile(std::string savefilename) {
  savefile = savefilename;

  // Write header
  std::ofstream outfile;
  outfile.open(savefile.c_str());
  outfile << "Positions for: " << getId() << std::endl << "#syntax: x y" << std::endl;;
  outfile.close();
}

/*
 * Stores current position to its given savefile. If no savefile is set
 * function aborts.
 */
void CelestialObject :: saveCurrentPos() {
  if (std::strcmp(savefile.c_str(),"<not_set>") == 0) { return; }

  std::ofstream outfile;
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
  arma::vec dist = other.getPos() - getPos();
  return dist;
}

double CelestialObject :: getM() { return m; }
arma::vec CelestialObject :: getPos() { return pos; }
arma::vec CelestialObject :: getV() { return v; }
arma::vec CelestialObject :: getForce() { return F; }
std::string CelestialObject :: getId() { return id; }
