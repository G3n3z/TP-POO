//
// Created by Daniel Fernandes on 15/12/2021.
//

#include "mineiro.h"

bool mineiro::pedeDemissao(double f, int d)const{
    if (d > (getDia() + 2)){
        if(r_uniforme01() <= (f + 0.1))
            return true;
    }
    return false;
}

mineiro::~mineiro() {}