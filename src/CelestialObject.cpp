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
void setF(double newF) { F = newF; }

/*
 * Get functions
 */
double getX() { return x; }
double getY() { return y; }
double getV() { return v; }
double getM() { return m; }
string getId() { return id; }
