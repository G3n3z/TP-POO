//
// Created by Daniel Fernandes on 15/12/2021.
//
#include "../Zonas/Floresta.h"
#include "CentralEletrica.h"
CentralEletrica::CentralEletrica(string x, double p):Edificio(x, "centraleletrica", false, p), c(new Carvao),
e(new Eletricidade("elet")),qtdElet(1), qtdCarvao(1), maxCarvao(100){
    Edificio::addRecurso(c);
    Edificio::addRecurso(e);
}

Recurso *CentralEletrica::produzE() {

    e->setQuantidade(-e->getQuantidade()); //Verificar

    if(!getEstado())
        return nullptr;

    if(!contOper())
        return nullptr;

    if(c->getQuantidade() == maxCarvao)
        return nullptr;

    if(!verificaRecEqtdZonasAdj("flr", "madeira", 1.0)){
        return nullptr;
    }

    Recurso *r = new Carvao;

    vZona("flr", "madeira", 1);

    r->setQuantidade(qtdCarvao);
    c->setQuantidade(qtdCarvao);
    e->setQuantidade(qtdElet);
    //falta depois de retirar a energia dispensa-la
    return r;
}

CentralEletrica::~CentralEletrica() {
    delete e;
    delete c;
}

CentralEletrica &CentralEletrica::operator=(const Edificio &outro) {
    if(this == &outro)
        return *this;

    Edificio::operator=(outro);

    if(outro.getName() == getName()) {
        const CentralEletrica *x = dynamic_cast<const CentralEletrica *>(&outro);
        c->setQuantidade(-c->getQuantidade());
        c->setQuantidade(x->c->getQuantidade());

        qtdCarvao = x->qtdCarvao;
        qtdElet = x->qtdElet;
        maxCarvao = x->maxCarvao;
    }
    return *this;
}


