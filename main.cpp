//
//  main.cpp
//  trojan_asteroids
//


#include <iostream>
#include "Vec3.h"
#include "solar_state.h"
#include "pert.h"
#include "gravity.h"
#include "simulation.h"




int main (int argc, char* argv[])
{
    
    if(argc>2) return 1;
    if (argc==1) {
        std::cout << "Program takes inputs direct from command line:\n'g': test grav field (outputs some text as well as data)\n'2': no planet y-z orbit\n'j': unperturbed jupiter\n'z': z perturbation jupiter\n'p': angularly perturbed jupiter\n'w': Find range of wander\nExample usage: './trojan_asteroids j > ./data.txt'\n";
        return 0;
    }
    
    switch (*argv[1]) {
        case 'g': test_grav_acc(); break;
        case '2': simulate(0,1,0,50,{0,1,0},{0,0,stable_omega({0.0,1})},1000,0,1); break;
        case 'j': simulate_perterbation_from_l4(0.001,5.2,500,{0,0,0},{0,0,0},10000,1); break;
        case 'z': simulate_perterbation_from_l4(0.001,5.2,500,{0,0,0},{0,0,0.1},10000,1);break;
        case 'p': pert_to_angle(0.15, 0.001, 5.2, 1, 500); break;

        case 'w': {
            for (double m=0.0; m<0.03; m+=0.0002){
                std::cout << m << ' ' << pert_to_angle(pow(2,-4), m, 1, 0, 80) << '\n';
            }
        }
    }
    return 0;
}