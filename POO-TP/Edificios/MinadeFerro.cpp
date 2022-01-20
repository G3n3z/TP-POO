//
// Created by Daniel Fernandes on 15/12/2021.
//

#include "MinadeFerro.h"
#include "../Zona.h"
int MinadeFerro::custo(15);
MinadeFerro::MinadeFerro(string n, double p): maxArma(100), maxArmPNivel(10) , Edificio(n, "Mina de Ferro", false, p),
                                    qtdProducao(2), qtdPporNivel(1), nivel(0) {
    r = new Ferro;
    addRecurso(r);
}

Recurso *MinadeFerro::produzE() {

    if(!getEstado())
        return nullptr;

    double max = maxArma + (maxArmPNivel * nivel); //maximo de Armazenamento

    if(contMiner() == 0)
        return nullptr;

    if(r->getQuantidade() == max) //Se chegou ao limite
        return nullptr;

    double qtd = qtdProducao + (qtdPporNivel * nivel);

    Recurso *f = new Ferro;
    if(r->getQuantidade() + qtd > max){
        f->setQuantidade(max - r->getQuantidade());
        r->setQuantidade(max); //Fica com o maximo se excedeu
        return f;
    }

    f->setQuantidade(qtd);
    r->operator+=(*f);

    return f;
}

void MinadeFerro::efeitos() {
    int r = rand()%100;
    if(r < 10)
        setEstadoEdif(false);
}

MinadeFerro::~MinadeFerro() {
    delete r;
}

double MinadeFerro::subirNivel(double dinheiro) {
    if(dinheiro >= custo && nivel <=5){
        ++nivel;
        return custo;
    }

    return 0;
}

string MinadeFerro::toString() const{
    return Edificio::toString() + "\n" + "Nivel: " +to_string(nivel);
}

bool MinadeFerro::podeSubirNivel() {
    return (nivel <5? true:false);
}

int MinadeFerro::getCustoNivel() const {
    return custo;
}

MinadeFerro &MinadeFerro::operator=(const Edificio &outro) {
    if(this == &outro)
        return *this;

    Edificio::operator=(outro);

    if(outro.getName() == getName()) {
        const MinadeFerro *x = dynamic_cast<const MinadeFerro *>(&outro);
        qtdProducao = x->qtdProducao;
        qtdPporNivel = x->qtdPporNivel; //qtd de producao por dia e por nivel
        r->setQuantidade(-r->getQuantidade());
        r->setQuantidade(x->r->getQuantidade());

        maxArma = x->maxArma;
        maxArmPNivel = x->maxArmPNivel; //qtd de armazenamento e o incrmento por nivel
        nivel = x->nivel;
    }
    return *this;
}

void MinadeFerro::setQtdProdEdificio(double q) {
    qtdProducao *= q;
    qtdPporNivel*= q;
}
