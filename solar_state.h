//
//  solar_state.h
//  trojan_asteroids
//


#ifndef trojan_asteroids_solar_state_h
#define trojan_asteroids_solar_state_h

#include "vec3.h"
#include "constsanddatatypes.h"

solar_state calc_sol_state(const double t, const system_params p);
cav::Vec3 l4_position(double t, system_params p);
double stable_omega(system_params p);
cav::Vec3 corot_pos(double t, system_params p, cav::Vec3 r);
double angle(cav::Vec3 a, cav::Vec3 b, cav::Vec3 c);


#endif