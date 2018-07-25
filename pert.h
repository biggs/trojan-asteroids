//
//  pert.h
//  trojan_asteroids
//

#ifndef trojan_asteroids_pert_h
#define trojan_asteroids_pert_h


double simulate_perterbation_from_l4(double planet_m, double planet_sep, double final_time, cav::Vec3 r1, cav::Vec3 v1, int no_outs, bool output);
double maximum_wander(double m, bool out);
double pert_to_angle(double angle, double m, double sep, bool out, double maxt);


#endif
