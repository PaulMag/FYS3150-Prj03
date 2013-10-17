#include <iostream>

#include "SolarSystem.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  SolarSystem mySystem = SolarSystem("../data/sunEarthSystem.dat");
  cout << "Reached end of main." << endl;
  return 0;
}
