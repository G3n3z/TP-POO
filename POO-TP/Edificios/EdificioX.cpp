//
// Created by Daniel Fernandes on 15/12/2021.
//

#include "EdificioX.h"

int EdificioX::custo(20);

EdificioX::EdificioX(string n, double p):Edificio(n,"edificioX",false, p), e(new Eletricidade),
                                         prod(0.5), prodPNivel(0.5), maxElet(100), maxPNivel(10), nivel(0){
    Edificio::addRecurso(e);
}

Recurso *EdificioX::produzE() {
    if(!getEstado() || nameZona() != "pas")
        return nullptr;

    double cap = maxElet + (maxPNivel * nivel);
    if (e->getQuantidade() == cap)
        return nullptr;

    double prodDiaria = prod + (prodPNivel * nivel);

    Recurso *r = new Eletricidade;
    if(e->getQuantidade() + prodDiaria > cap){
        r->setQuantidade(cap - e->getQuantidade());
        e->setQuantidade(cap);
        return r;
    }

    r->setQuantidade(prodDiaria);
    e->operator+=(*r);

    return r;
}

double EdificioX::subirNivel(double dinheiro) {
    if(dinheiro >= custo && nivel <=5){
        ++nivel;
        return custo;
    }

    return 0;
}

string EdificioX::toString() const{
    return Edificio::toString() + "\n" + "Nivel: " +to_string(nivel);
}

EdificioX::~EdificioX() {
    delete e;
}

bool EdificioX::podeSubirNivel() {
    return (nivel <5? true:false);
}

int EdificioX::getCustoNivel() const {
    return custo;
}

EdificioX &EdificioX::operator=(const Edificio &outro) {
    if(this == &outro)
        return *this;

    Edificio::operator=(outro);

    if(outro.getName() == getName()) {
        const EdificioX *x = dynamic_cast<const EdificioX *>(&outro);

        e->setQuantidade(-e->getQuantidade());
        e->setQuantidade(x->e->getQuantidade());

        maxElet = x->maxElet;
        maxPNivel = x->maxPNivel;
        prod = x->prod;
        prodPNivel = x->prodPNivel;
        nivel = x->nivel;
    }
    return *this;
}
