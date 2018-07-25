//
//  constsanddatatypes.h
//  trojan_asteroids
//


#ifndef trojan_asteroids_constsanddatatypes_h
#define trojan_asteroids_constsanddatatypes_h

//useful physical constants
const double pi = 3.14159265359;
const double grav_const = 4*pi*pi;  //sun set to mass 1
const cav::Vec3 zaxis(0,0,1);


//object for paramaters
typedef struct{
    double m;
    double sep;
} system_params;


//object for solar system state
typedef struct{
    cav::Vec3 rs;   //sun position
    cav::Vec3 rp;   //planet position
} solar_state;


#endif
