#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

#include "SolarSystem.hpp"

int main(int argc, char* argv[]) {
  SolarSystem mySystem = SolarSystem("../data/sunEarthSystem.dat");
  cout << "Reached end of main." << endl;
  return 0;
}
