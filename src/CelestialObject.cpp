#include "CelestialObject.hpp"

/*
 * @param id Short string describing object.
 */
CelestialObject :: CelestialObject(std::string id, arma::vec coors, arma::vec vel, double m) {
  m = m;
  pos = coors;
  v = vel;
  id = id;
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
 * Get functions
 */

/*
 * Returns the distance from this object to a different one.
 *
 * @param other The other celestial object to find distance to.
 */
arma::vec CelestialObject :: getDistTo(CelestialObject other) {
  arma::vec dist = other.getCoors() - getCoors();
  return dist;
}

double CelestialObject :: getM() { return m; }
arma::vec CelestialObject :: getCoors() { return pos; }
arma::vec CelestialObject :: getV() { return v; }
arma::vec CelestialObject :: getForce() { return F; }
std::string CelestialObject :: getId() { return id; }
