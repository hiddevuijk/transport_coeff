

#include "system.h"
#include "diffusion.h"
#include "multi_diffusion.h"

#include "ConfigFile.h"

#include <iostream>
#include <vector>

using namespace std;

int main()
{

  ConfigFile config("input.txt");
  double time  = config.read<double>("time");
  double dt    = config.read<double>("dt");
  double kappa = config.read<double>("kappa");
  double gamma = config.read<double>("gamma");
  double T     = config.read<double>("T");
  double m     = config.read<double>("m");
  int seed     = config.read<int>("seed");

  int ntime = config.read<int>("ntime");
  double dtSample = config.read<double>("dtSample");

  System system(dt, kappa, gamma, T, m, seed);
  system.integrate(time/10);

  Diffusion diffx(ntime, dtSample);
  Diffusion diffy(ntime, dtSample);
  MDiffusion mdiff(2, ntime, dtSample);

  double t = 0;
  int i = 0;
  while( t < time ) {
    t += dtSample;
    ++i;
    system.integrate(dtSample);
    diffx.sample(system.getX() );
    diffy.sample(system.getY() );
    mdiff.sample(0, system.getX() );
    mdiff.sample(1, system.getY() );
    if( i % 10000 == 0 ) cout << t << endl;
  }

  diffx.save("msdx.dat"); 
  diffy.save("msdy.dat"); 
  mdiff.save("msd.dat"); 
  

  return 0;
}
