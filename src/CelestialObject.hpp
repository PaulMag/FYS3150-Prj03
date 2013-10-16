class CelestialObject {
  public:
    CelestialObject(string,double,double,double);
    double getX(),getY(),getV(),getF(),getId(); // Get-functions
    void setF(double); // Save current force

  private:
    double x,y,v,F,m; // Current x,y position, velocity, force and mass
    string id;
};
