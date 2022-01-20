//
// Created by Daniel Fernandes on 15/12/2021.
//

#include "ZonaX.h"

ZonaX::ZonaX(string n): Zona(n,0.0, "ZonaX"){}

ZonaX::~ZonaX() {

}

void ZonaX::efeitosZonas() {
    Zona::efeitosZonas();
    int tot = contatrabalhadores();
    Trabalhador *a, *aux;
    for( int i = 0; i < tot; i++){
        a = getTrabalhador(i);
        aux = a->clonagem();
        if(aux!= nullptr)
            addTrablhador(aux);
    }
}

ZonaX &ZonaX::operator=(const Zona &outro) {
    if(this == &outro)
        return *this;

    Zona::operator=(outro);

    return *this;
}
