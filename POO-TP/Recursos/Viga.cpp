//
// Created by Daniel Fernandes on 16/12/2021.
//

#include "Viga.h"

string Viga::toString()const {
    return getsigla() + " - " + to_string(int(getQuantidade()))  + " qtd";
}
