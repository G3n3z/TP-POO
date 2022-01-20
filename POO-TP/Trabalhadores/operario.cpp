//
// Created by Daniel Fernandes on 15/12/2021.
//

#include "operario.h"

bool operario::pedeDemissao(double f, int d)const{
    if (d > (getDia() + 10)){
        if(r_uniforme01() <= f + 0.05)
            return true;
    }
    return false;
}

operario::~operario() {

}