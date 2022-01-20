//
// Created by Daniel Fernandes on 15/12/2021.
//

#include "Deserto.h"
Deserto::Deserto(string n): Zona(n, 0.0, "Deserto"){}

Deserto::~Deserto() {

}

Deserto &Deserto::operator=(const Zona &outro) {
    if(this == &outro)
        return *this;

    Zona::operator=(outro);

    return *this;
}

void Deserto::constroiEdif(string x, const string * edificios, double preco) {
    Zona::constroiEdif(x, edificios, preco);

    if(getEdifName() == edificios[4] || getEdifName() == edificios[5]){
        setQtdProdEdificio(0.5);
    }

}


