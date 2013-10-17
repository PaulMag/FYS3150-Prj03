#include <string>

class CelestialObject {
  public:
    CelestialObject(std::string,double,double,double,double,double);
    double getX(),getY(),getVX(),getVY(),getF(),getM(); // Get-functions
    std::string getId();
    void setF(double); // Save current force
    void setPos(double,double); // Set new position
    void setVel(double,double); // Set new velocity

  private:
    double x,y,vx,vy,F,m; // Current x,y position, velocity, force and mass
    std::string id;
};
