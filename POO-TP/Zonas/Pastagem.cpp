//
// Created by Daniel Fernandes on 15/12/2021.
//

#include "Pastagem.h"

Pastagem::Pastagem(string n): Zona(n,0.0, "Pastagem"){}

void Pastagem::verificaDemissoes(int){return;}

Pastagem::~Pastagem() {

}

Pastagem &Pastagem::operator=(const Zona &outro) {
    if(this == &outro)
        return *this;
    Zona::operator=(outro);

    return *this;
}
