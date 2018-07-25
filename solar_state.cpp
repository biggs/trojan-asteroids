//
//  solar_state.cpp
//  trojan_asteroids
//  solve the two body problem


#include "solar_state.h"

//calculate angle bac
double angle(cav::Vec3 a, cav::Vec3 b, cav::Vec3 c){
    cav::Vec3 ab = b - a;
    ab.normalise();
    cav::Vec3 ac = c - a;
    ac.normalise();
    return acos(ab%ac);
}




//orbital periods
double stable_period(system_params p){
    return (2 * pi * pow(p.sep,1.5) * pow(grav_const*(1 + p.m),-0.5));
}

double stable_omega(system_params p){
    return 2*pi/stable_period(p);
}


//seperation vector at time t
cav::Vec3 circ_sep_vect(const double t, const system_params p){
    const cav::Vec3 sep0(p.sep,0,0);
    return rotate(sep0,zaxis,stable_omega(p)*t);
}


//calculate and return solar_state for given params and time
solar_state calc_sol_state(const double t, const system_params p){
    solar_state s;
    cav::Vec3 sep_vec = circ_sep_vect(t, p);
    s.rs = sep_vec * (- p.m /(1+p.m));
    s.rp = sep_vec * (1 / (1+p.m));
    return s;
}


cav::Vec3 l4_position(double t, system_params p){
    return rotate(calc_sol_state(t,p).rs + circ_sep_vect(t,p), zaxis, pi/3) - calc_sol_state(t, p).rs;
}

//convert a r vector to a corotating displacement from l4
cav::Vec3 corot_pos(double t, system_params p, cav::Vec3 r){
    return rotate(r,zaxis,-stable_omega(p)*t);
}