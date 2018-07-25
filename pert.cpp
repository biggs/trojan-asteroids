//
//  pert.cpp
//  trojan_asteroids
//


#include "simulation.h"
#include "Vec3.h"
#include "solar_state.h"



//simulate a steady state solution with small perterbations r1 and v1
//such that v = v0 + v1 and r = r0 + r1
double simulate_perterbation_from_l4(double planet_m, double planet_sep, double final_time, cav::Vec3 r1, cav::Vec3 v1, int no_outs, bool output){
    cav::Vec3 r0 = l4_position(0,{planet_m,planet_sep});
    double modv0 = stable_omega({planet_m,planet_sep})*planet_sep;
    cav::Vec3 v0 = rotate({0,modv0,0},zaxis,pi/3);
    
    return simulate(planet_m,planet_sep,0.0,final_time,r0+r1,v0+v1,no_outs,1,output);
}


double pert_to_angle(double angle, double m, double sep, bool out, double maxt){
    double steps = 5000;
    
    cav::Vec3 r0 = rotate(l4_position(0,{m,sep}),zaxis,angle);
    double modv0 = stable_omega({m,sep})*calc_sol_state(0,{m,sep}).rp.len();
    cav::Vec3 v0 = rotate({0,modv0,0},zaxis,pi/3);
    
    return simulate(m, sep, 0, maxt, r0, v0, steps,1, out);
}
