#ifndef GUARD_SYSTEM_H
#define GUARD_SYSTEM_H

//
// TO TO
//

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <boost/random.hpp>

#include <iostream>



class System {
 public:
  System(double dt, double kappa,  double gamma, double T, double m, int seed);
   
  // evolve in time
  void integrate(double t);

  double getX()  const { return x; }
  double getY()  const { return y; }
  double getVX() const { return vx; }
  double getVY() const { return vy; }

 private:
  // single time step
  void step(double dt);


  double x, y;
  double vx, vy;

  double dt_; // time step
  double kappa_;
  double gamma_;
  double T_;
  double m_;

	// random number generator

	int seed_;
	const boost::normal_distribution<double> ndist;
	boost::mt19937 rng;		
	boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> > rndist;
};

System::System(double dt, double kappa, double gamma, double T,
               double m, int seed)
    : x(0), y(0), vx(0), vy(0), dt_(dt), kappa_(kappa), gamma_(gamma), T_(T),
      m_(m), seed_(seed), ndist(0., std::sqrt(2*T*gamma*dt)),
      rng(seed), rndist(rng, ndist) 
{ };


void System::integrate(double t)
{
  while (t - dt_ > 0) {
    step(dt_); 
    t -= dt_;
  }
  step(t);
}

void System::step(double dt)
{
  double dvx, dvy; 
  x += vx * dt;
  y += vy * dt;

  dvx = ( kappa_ * vy - vx * gamma_) * dt + rndist(); 
  dvy = (-kappa_ * vx - vy * gamma_) * dt + rndist();

  vx += dvx / m_;
  vy += dvy / m_;
}

#endif //GUARD_SYSTEM_H
