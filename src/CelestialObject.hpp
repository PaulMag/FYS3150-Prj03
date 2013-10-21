#include <string>
#include <armadillo>

class CelestialObject {
  public:
    CelestialObject(std::string,arma::vec,arma::vec,double);
    double getM(); // Get-functions
    std::string getId();
    void setF(arma::vec); // Save current force
    void setPos(arma::vec); // Set new position
    void setVel(arma::vec); // Set new velocity
    arma::vec getDistTo(CelestialObject); // Returns distance to other object
    arma::vec getCoors(),getV(),getForce();

  private:
    double m;
    arma::vec pos,v,F;
    std::string id;
};
