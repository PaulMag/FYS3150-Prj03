#include "CelestialObject.hpp"
#include <cmath>

/*
 * @param id Short string describing object.
 * @param x0 Starting x.
 * @param y0 Starting y.
 * @param v0 Startinv v.
 */
CelestialObject :: CelestialObject(std::string id, double x0, double y0, double v0x, double v0y, double m) {
  m = m;
  x = x0;
  y = y0;
  vx = v0x;
  vy = v0y;
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
void CelestialObject :: setF(double newF) {
  F = newF;
}

/*
 * Set new positions.
 *
 * @param x New x position.
 * @param y New y position.
 */
void CelestialObject :: setPos(double x, double y) {
  x = x;
  y = y;
}

/*
 * Updates velocity of object.
 *
 * @param vx Velocity x direction.
 * @param vy Velocity y direction.
 */
void CelestialObject :: setVel(double vx, double vy) {
  vx = vx;
  vy = vy;
}

/*
 * Get functions
 */

/*
 * Returns the distance from this object to a different one.
 *
 * @param other The other celestial object to find distance to.
 */
double CelestialObject :: getDistTo(CelestialObject other) {
  double distX = other.getX() - getX();
  double distY = other.getY() - getY();
  return sqrt(distX*distX + distY*distY);
}

double CelestialObject :: getX() { return x; }
double CelestialObject :: getY() { return y; }
double CelestialObject :: getVX() { return vx; }
double CelestialObject :: getVY() { return vy; }
double CelestialObject :: getM() { return m; }
std::string CelestialObject :: getId() { return id; }
