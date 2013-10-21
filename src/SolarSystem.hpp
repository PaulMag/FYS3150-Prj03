#include <vector>
#include <armadillo>
#include "CelestialObject.hpp"

class SolarSystem {
  public:
    SolarSystem();
    SolarSystem(double);
    SolarSystem(std::string); // Can take infile with system
    void addObject(CelestialObject); // Add a new object
    void advance(double); // Advance system a time dt
    int getNoOfObjects(); // Get number of objects
    arma::vec getForces(CelestialObject); // Get force working on object
    double getT();

  private:
    double t; // Current time
    std::vector<CelestialObject> objects; // To contain objects in solar system
};
