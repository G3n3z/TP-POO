//
// Created by Daniel Fernandes on 15/12/2021.
//

#include "Pantano.h"

Pantano::Pantano(string n): Zona(n,0.0, "Pantano"), dia(0){


}

void Pantano::efeitosZonas() {
    Zona::efeitosZonas();

    if(verificaEdificio())
        return;

    if(dia < 10){
        ++dia;
    }

    if(dia == 10){
        dia = 0;
        setEstadoEdif(false);
        eliminaEdif();
        demiteAlltrabalhadores();

    }





}

Pantano::~Pantano() {

}

Pantano &Pantano::operator=(const Zona &outro) {
    if(this == &outro)
        return *this;

    Zona::operator=(outro);

    if(outro.showNome() == showNome()) {
        const Pantano *x = dynamic_cast<const Pantano*>(&outro);
        dia = x->dia;
    }
    return *this;

}
