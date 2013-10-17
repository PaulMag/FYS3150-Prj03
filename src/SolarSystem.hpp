#include "CelestialObject.hpp"
#include <vector>

class SolarSystem {
  public:
    SolarSystem();
    SolarSystem(std::string); // Can take infile with system
    void addObject(CelestialObject); // Add a new object
    void advance(double); // Advance system a time dt
    int getNoOfObjects(); // Get number of objects

  private:
    double t; // Current time
    std::vector<CelestialObject> objects; // To contain objects in solar system
};
