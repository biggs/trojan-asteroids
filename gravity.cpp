//
//  gravity.cpp
//  trojan_asteroids
//



#include "gravity.h"

#include <iostream>


cav::Vec3 grav_acc(const solar_state s, const double m, const cav::Vec3 r){
    cav::Vec3 g(0,0,0);
    cav::Vec3 rfroms = r - s.rs;
    cav::Vec3 rfromp = r - s.rp;
    g = - grav_const * ( rfroms * pow(rfroms.len(),-3) + m * rfromp * pow(rfromp.len(),-3) );
    return g;
}


//gravatiational tensor from a single body mass 1 at r=0
double grav_tensor_single(const cav::Vec3 r, const char i, const char j){
    double val = 0;
    
    if (i=='x'){
        val = -3 * r.x();
    } else if (i=='y') {
        val = -3 * r.y();
    } else if (i=='z') {
        val = -3 * r.z();
    } else {
        std::cout << "Error, i is not valid\n";
        return 11111;    //special value, not the best way
    }
    
    if (i==j) val += r.len2();
    
    val *= pow(r.len(),-5);
    
    return val;
}



double grav_tensor(const cav::Vec3 r, solar_state s, double m, char i, char j){
    return (-grav_const *(grav_tensor_single((r-s.rs), i, j) + m*grav_tensor_single((r-s.rp), i, j)));
}



//test grav_acc
void test_grav_acc(){
    system_params ptest = {0.3,10};
    solar_state s = calc_sol_state(5, ptest);
    cav::Vec3 rtest;
    
    for (double x=-20; x<=20; x+=1){
        for (double y=-20; y<=20; y+=1){
            rtest = cav::Vec3(x,y,0);
            
            cav::Vec3 g = grav_acc(s,ptest.m,rtest);
            if(g.len() < 5) std::cout << rtest.x() << ' ' << rtest.y() << ' ' << g.x() << ' ' << g.y() << '\n';     //avoid really big g near planet and sun
        }
    }
    
    std::cout << "\nSun in position ";
    s.rs.print(std::cout);
    std::cout << ", planet (mass " << ptest.m << ") in position ";
    s.rp.print(std::cout);
    std::cout << ". Data in format rx,ry,gx,gy.\nTry: \"plot 'filename' u 1:2:3:4 w vectors head filled, \"<echo ' " << s.rs.x() << ' ' << s.rs.y() << " \\n " << s.rp.x() << ' ' << s.rp.y() << "'\" with points ls 2\"\n";
}