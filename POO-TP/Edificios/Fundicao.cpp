//
// Created by Daniel Fernandes on 15/12/2021.
//

#include "Fundicao.h"

Fundicao::Fundicao(string n, double p):Edificio(n,"fundicao",false, p), a(new BarradeAco) , qtdMax(100.0){
    addRecurso(a);
}

Recurso *Fundicao::produzE() {

    if(!getEstado())
        return nullptr;


    if(a->getQuantidade() >= qtdMax)
        return nullptr;

    int q = contOper();
    if(q == 0){
        return nullptr;
    }


    Recurso *r ;
    string nEdif;

    if(!verificaRecursoeQtd("mnf","ferro",1.5))
        return nullptr;

    Recurso *f = new Ferro;


    if(verificaRecursoeQtd("mnc", "carvao", 0.5)){
        r = new Carvao;
        nEdif = "mnc";
    }

    else if(verificaRecursoeQtd("elec", "carvao" , 0.5)){
        r = new Carvao;
        nEdif = "elec";
    }
    else{
        delete f;
        return nullptr;
    }


    retiraRecursoDeEdifAdj("mnf", f, 1.5, 1.5);
    retiraRecursoDeEdifAdj(nEdif, r, 0.5, 0.5);
    delete f;
    delete r;

    Recurso* x = new BarradeAco;

    x->setQuantidade(1);
    a->setQuantidade(1);

    return x;
}

Fundicao::~Fundicao() {
    delete a;
}

Fundicao &Fundicao::operator=(const Edificio &outro) {
    if(this == &outro)
        return *this;

    Edificio::operator=(outro);

    if(outro.getName() == getName()){
        const Fundicao* x = dynamic_cast<const Fundicao*>(&outro);
        a->setQuantidade(-a->getQuantidade());
        a->setQuantidade(x->a->getQuantidade());
        qtdMax = x->qtdMax;
    }
    return *this;
}
