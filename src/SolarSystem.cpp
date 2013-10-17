#include "SolarSystem.hpp"
#include "CelestialObject.hpp"

/*
 * Constructor
 */
SolarSystem :: SolarSystem() {
  t = 0
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
