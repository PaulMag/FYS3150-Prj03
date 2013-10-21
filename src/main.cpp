#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

#include "SolarSystem.hpp"

int main(int argc, char* argv[]) {
  SolarSystem mySystem = SolarSystem("../data/sunEarthSystem.dat");

  if (argc != 3) {
    cout << "Need step size and number of steps." << endl;
    return 1;
  }

  double dt = atof(argv[1]);
  double N = atof(argv[2]);

  for (int i = 0; i < dt*N; i++) {
    mySystem.advance(dt);
  }

  cout << "Reached end of main." << endl;
  return 0;
}
