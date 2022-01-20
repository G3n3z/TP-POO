//
// Created by Daniel Fernandes on 15/12/2021.
//

#include "MinadeCarvao.h"

int MinadeCarvao::custo(10);
MinadeCarvao::MinadeCarvao(string n, double p):Edificio(n,"mina de carvao", false, p),qtdProducao(2)
,qtdPporNivel(1), maxArma(100), maxArmPNivel(10), nivel(0) {
    r = new Carvao;
    Edificio::addRecurso(r);
}

Recurso *MinadeCarvao::produzE() {

    if(!getEstado())
        return nullptr;

    if(contMiner() == 0)
        return nullptr;

    int max = maxArma + (maxArmPNivel * nivel);
    if(r->getQuantidade() == max)
        return nullptr;

    Recurso *f = new Carvao;
    double qtd = qtdProducao + (qtdPporNivel * nivel);


    if(r->getQuantidade() + qtd > max){
        f->setQuantidade(max - r->getQuantidade());
        r->setQuantidade(max); //Fica com o maximo se excedeu
        return f;
    }

    f->setQuantidade(qtd);
    r->operator+=(*f);

    return f;

}

void MinadeCarvao::efeitos() {
    int r = rand()%100;
    if(r < 15)
        setEstadoEdif(false);
}

MinadeCarvao::~MinadeCarvao() {
    delete r;
}

double MinadeCarvao::subirNivel(double dinheiro) {
    if(dinheiro >= custo && nivel <=5){
        ++nivel;
        return custo;
    }

    return 0;
}

string MinadeCarvao::toString() const{
    return Edificio::toString() + "\n" + "Nivel: " +to_string(nivel);
}

bool MinadeCarvao::podeSubirNivel() {
    return (nivel <5? true:false);
}

int MinadeCarvao::getCustoNivel() const {
    return custo;
}

MinadeCarvao &MinadeCarvao::operator=(const Edificio &outro) {
    if(this == &outro)
        return *this;

    Edificio::operator=(outro);

    if(outro.getName() == getName()){
        const MinadeCarvao* x = dynamic_cast<const MinadeCarvao*>(&outro);
        qtdProducao = x->qtdProducao;
        qtdPporNivel = x->qtdPporNivel;
        r->setQuantidade(-r->getQuantidade());
        r->setQuantidade(x->r->getQuantidade());

        maxArma = x->maxArma;
        maxArmPNivel = x->maxArmPNivel;
        nivel = x->nivel;
    }
    return *this;
}

void MinadeCarvao::setQtdProdEdificio(double q) {
    qtdProducao *= q;
    qtdPporNivel*= q;
}
