//
//  simulation.cpp
//  trojan_asteroids
//

#include <iostream>
#include "Vec3.h"
#include "solar_state.h"
#include "funcandjacob.h"
#include "simulation.h"

#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>


//do the simulation. Return -1 if gets too close or too far away from planet
double simulate(double m, double planet_sep, double t0, double t1, cav::Vec3 r0, cav::Vec3 v0, int no_outs, bool bound_only, bool output){
    double t = t0;
    system_params params = {m,planet_sep};
    gsl_odeiv2_system sys = {funcs, jacob, 6, &params};
    gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rkf45, 1e-7, 1e-9, 0.0);
    double y[6] = { r0.x(), r0.y(), r0.z(), v0.x(), v0.y(), v0.z() };
    
    double maxangle = 0;
    double minangle = pi/3;
    
    for (int i = 1; i <= no_outs; i++)
    {
        double ti = i * t1 / double(no_outs);
        int status = gsl_odeiv2_driver_apply (d, &t, ti, y);
        
        if (status != GSL_SUCCESS)
        {
            std::cout << "Error: " << status;
            break;
        }
        
        //handle outputs
        cav::Vec3 r(y[0],y[1],y[2]);
        cav::Vec3 v(y[3],y[4],y[5]);
        solar_state s = calc_sol_state(t, params);
        cav::Vec3 R = corot_pos(t, params, r);
        double ang = angle({0,0,0},R,{1,0,0});
        
        if ((ang > 2*pi/3 - 0.05 || ang < 0.05) && bound_only) return -1;    //return false and stop running if escapes from stable position
        if (maxangle < ang) maxangle = ang; //use these to calculate angle range
        if (minangle > ang) minangle = ang;
        
        if(output) std::cout << ti << ' ' << r << ' ' << v << ' ' << R << ' ' << (R-l4_position(t, params)).len() << ' ' << ang-pi/3 << '\n';
    }
    
    gsl_odeiv2_driver_free (d);
    return (maxangle - minangle);
}
