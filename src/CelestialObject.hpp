class CelestialObject {
  public:
    CelestialObject(string,double,double,double);
    double getX(),getY(),getV(),getF(),getM(); // Get-functions
    string getId();
    void setF(double); // Save current force
    void setPos(double,double); // Set new position
    void setVel(double); // Set new velocity

  private:
    double x,y,v,F,m; // Current x,y position, velocity, force and mass
    string id;
};
