//
//  gravity.h
//  trojan_asteroids
//

#ifndef trojan_asteroids_gravity_h
#define trojan_asteroids_gravity_h

#include "vec3.h"
#include "constsanddatatypes.h"
#include "solar_state.h"

cav::Vec3 grav_acc(const solar_state s, const double m, const cav::Vec3 r);
double grav_tensor(const cav::Vec3 r, solar_state s, double m, char i, char j);
void test_grav_acc();


#endif