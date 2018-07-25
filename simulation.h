//
//  simulation.h
//  trojan_asteroids
//

#ifndef trojan_asteroids_simulation_h
#define trojan_asteroids_simulation_h
#include "vec3.h"

double simulate(double m, double planet_sep, double t0, double t1, cav::Vec3 r0, cav::Vec3 v0, int no_outs, bool bound_only, bool output);


#endif