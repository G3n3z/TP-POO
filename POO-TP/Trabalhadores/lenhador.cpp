//
// Created by Daniel Fernandes on 15/12/2021.
//

#include "lenhador.h"

lenhador::~lenhador() {}

int lenhador::getdiasTrabalho() const{
    return diastrab;
}

void lenhador::folga() {
    if(diastrab == 0){
        diastrab =4;
        return;
    }
    --diastrab;
}

string lenhador::toString() const{
    return Trabalhador::toString() + (diastrab == 0 ? " |Estou de folga":" |Dia de folga daqui a " + to_string(diastrab) + " dias");
}

lenhador &lenhador::operator=(const Trabalhador &outro) {

    if(this == &outro)
        return *this;

    Trabalhador::operator=(outro);

    if(getTipo() == outro.getTipo()){
        const lenhador* x = dynamic_cast<const lenhador*>(&outro);
        diastrab = x->diastrab;
    }


    return *this;
}
