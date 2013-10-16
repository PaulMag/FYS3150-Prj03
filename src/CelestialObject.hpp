class CelestialObject {
  public:
    CelestialObject(string,double,double,double);
    double getX(),getY(),getV(),getF(),getId(); // Get-functions
    void setF(double); // Save current force

  private:
    double x,y,v,F; // Current x,y position, velocity and force
    string id;
};
