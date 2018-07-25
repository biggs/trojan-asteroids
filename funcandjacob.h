//
//  funcandjacob.h
//  trojan_asteroids
//


#ifndef trojan_asteroids_func_h
#define trojan_asteroids_func_h


int funcs (double t, const double y[], double f[], void *params);
int jacob (double t, const double y[], double *dfdy, double dfdt[], void *params);

#endif