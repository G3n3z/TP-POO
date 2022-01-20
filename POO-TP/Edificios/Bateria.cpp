//
// Created by Daniel Fernandes on 15/12/2021.
//

#include "Bateria.h"
int Bateria::Custo(5);

Bateria::Bateria(string n, double p):Edificio(n,"Bateria",false, p), e(new Eletricidade),
capacidade(100), capacidadePN(10), nivel(0){
    addRecurso(e);
}

Recurso *Bateria::produzE() {

    if(!getEstado())
        return nullptr;

    double max  = capacidade + (capacidadePN * nivel);
    if(e->getQuantidade() >= max){
        return nullptr;
    }

    Recurso *ele = new Eletricidade;
    double maxAObter = max - e->getQuantidade();

    retiraRecursoDeEdifAdj("elec", ele, -1, maxAObter);

    if(ele->getQuantidade() == 0.0)
        return nullptr;

    e->setQuantidade(ele->getQuantidade());

    return ele;
}

double Bateria::subirNivel(double dinheiro) {
    if(dinheiro >= Custo && nivel <=5){
        ++nivel;
        return Custo;
    }

    return 0;
}

string Bateria::toString()const {
    return Edificio::toString() + "\n" + "Nivel: " +to_string(nivel);
}

bool Bateria::podeSubirNivel() {
    return (nivel <5? true:false);
}

int Bateria::getCustoNivel() const {
    return Custo;
}

Bateria &Bateria::operator=(const Edificio &outro) {
    if(this == &outro)
        return *this;


    if(outro.getName() == getName()) {
        const Bateria *x = dynamic_cast<const Bateria *>(&outro);
        capacidade = x->capacidade;
        capacidadePN = x->capacidadePN;
        nivel = x->nivel;
        e->setQuantidade(-e->getQuantidade());
        e->setQuantidade(x->e->getQuantidade());
    }
    return *this;
}

