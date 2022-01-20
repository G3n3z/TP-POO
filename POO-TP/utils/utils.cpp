//
// Created by Daniel Fernandes on 16/12/2021.
//

#include "utils.h"
#include <random>
#include <iostream>
#include <chrono>
using namespace std;

double uniforme01(){
    static default_random_engine e;
    static uniform_real_distribution<double> u(0.0, 1.0);
    return u(e);
}

double r_uniforme01(){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    static default_random_engine e(seed);
    static uniform_real_distribution<double> u(0.0, 1.0);
    return u(e);
}