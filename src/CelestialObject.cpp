#include "CelestialObject.cpp"
#include <stdlib.h>
using namespace std;

/*
 * @param id Short string describing object.
 * @param x0 Starting x.
 * @param y0 Starting y.
 * @param v0 Startinv v.
 */
CelestialObject(string id, double m, double x0, double y0, double v0) {
  m = m;
  x = x0;
  y = y0;
  v = v0;
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
void setF(double newF) {
  F = newF;
}

/*
 * Set new positions.
 *
 * @param x New x position.
 * @param y New y position.
 */
void setPos(double x, double y) {
  x = x;
  y = y;
}

/*
 * Updates velocity of object.
 *
 * @param newVel The new velocity.
 */
void setVel(double newVel) {
  v = newVel;
}

/*
 * Get functions
 */
double getX() { return x; }
double getY() { return y; }
double getV() { return v; }
double getM() { return m; }
string getId() { return id; }
