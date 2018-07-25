//
//  funcandjacob.cpp
//  trojan_asteroids
//

#include "funcandjacob.h"

#include "Vec3.h"
#include "solar_state.h"
#include "gravity.h"
#include "constsanddatatypes.h"

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>


int funcs (double t, const double y[], double f[], void *params)
{
    system_params p = *(system_params *)params;
    const cav::Vec3 r(y[0],y[1],y[2]);
    const solar_state s = calc_sol_state(t, p);
    const cav::Vec3 g = grav_acc(s, p.m, r);
    
    f[0] = y[3];
    f[1] = y[4];
    f[2] = y[5];
    
    f[3] = g.x();
    f[4] = g.y();
    f[5] = g.z();
    
    return GSL_SUCCESS;
}



int jacob (double t, const double y[], double *dfdy, double dfdt[], void *params)
{
    system_params p = *(system_params *)params;
    const cav::Vec3 r(y[0],y[1],y[2]);
    const solar_state s = calc_sol_state(t, p);
    
    
    
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, 6, 6);  //allow temporary access to save memory
    
    gsl_matrix * m = &dfdy_mat.matrix;
    
    gsl_matrix_set_zero(m); //most values are just 0
    
    gsl_matrix_set (m, 0, 3, 1.0);
    gsl_matrix_set (m, 1, 4, 1.0);
    gsl_matrix_set (m, 2, 5, 1.0);
    
    gsl_matrix_set (m, 3, 3, grav_tensor(r, s, p.m, 'x', 'x'));
    gsl_matrix_set (m, 3, 4, grav_tensor(r, s, p.m, 'x', 'y'));
    gsl_matrix_set (m, 3, 5, grav_tensor(r, s, p.m, 'x', 'z'));
    gsl_matrix_set (m, 4, 3, grav_tensor(r, s, p.m, 'y', 'x'));
    gsl_matrix_set (m, 4, 4, grav_tensor(r, s, p.m, 'y', 'y'));
    gsl_matrix_set (m, 4, 5, grav_tensor(r, s, p.m, 'y', 'z'));
    gsl_matrix_set (m, 5, 3, grav_tensor(r, s, p.m, 'z', 'x'));
    gsl_matrix_set (m, 5, 4, grav_tensor(r, s, p.m, 'z', 'y'));
    gsl_matrix_set (m, 5, 5, grav_tensor(r, s, p.m, 'z', 'z'));
    
    
    dfdt[0] = 0.0;
    dfdt[1] = 0.0;
    dfdt[2] = 0.0;
    dfdt[3] = 0.0;
    dfdt[4] = 0.0;
    dfdt[5] = 0.0;
    
    return GSL_SUCCESS;
}