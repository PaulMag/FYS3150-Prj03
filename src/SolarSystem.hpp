#include "CelestialObject.hpp"

class SolarSystem {
  public:
    void addObject(CelestialObject);
    void advance(double);

  private:
    CelestialObject* objects; // To contain objects in solar system
};
