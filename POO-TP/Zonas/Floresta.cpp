//
// Created by Daniel Fernandes on 15/12/2021.
//

#include "Floresta.h"

Floresta::Floresta(string n): Zona(n, 0.0, "Floresta"), qtdP(1), r(new Madeira("madeira")), qtdMaxArvores(100), diaInicial(0){
    //Falta adicionar a quantidade de Arvores. Tem de ser entre 20 e 40
    qtdArvores = (rand()%20) + 20;
    r->setQuantidade(1);
}


double Floresta::retiraRecursoZona(string nRec, double quant) {
    if(r->getsigla() != nRec)
        return 0;

    if (r->getQuantidade() - quant >= 0){ //Totalidade do recurso
        r->setQuantidade(-quant);
        return quant;
    }

    quant = r->getQuantidade();
    r->setQuantidade(-r->getQuantidade());

    return quant;
}


Recurso *Floresta::produz() {

    int len = qtdLenhadores();
    if(!len || qtdArvores == 0){
        return nullptr;
    }
    Recurso* m = new Madeira;

    if(qtdArvores >= len){
        m->setQuantidade(qtdP * len);
        r->operator+=(*m);
        qtdArvores -= len;
        return m;
    }

    m->setQuantidade(qtdP * qtdArvores);
    r->operator+=(*m);
    qtdArvores = 0;
    return m;
}

void Floresta::efeitosZonas() {
    Zona::efeitosZonas();
    if(!verificaEdificio()){
        if(qtdArvores > 0)
            --qtdArvores;
        return;
    }

    if(qtdArvores == qtdMaxArvores)
        return;

    ++diaInicial;
    if(diaInicial == 2){
        ++qtdArvores;
        diaInicial = 0;
    }

}

const Recurso *Floresta::getRecurso()const {
    if (r->getQuantidade() == 0)
        return nullptr;
    return r;
}

double Floresta::retiraRecursoPorTodasZonas(string nrec, double qtd) {
    if(r->getsigla() != nrec)
        return 0;
    if(r->getQuantidade() >= qtd){
        r->setQuantidade( - qtd);
        return qtd;
    }
    qtd = r->getQuantidade();
    r->setQuantidade( -r->getQuantidade());
    return qtd;

}

Floresta::~Floresta() {
    delete r;
}

Floresta &Floresta::operator=(const Zona &outro) {
    if(this == &outro)
        return *this;

    Zona::operator=(outro);

    if(outro.showNome() == showNome()){
        const Floresta *x = dynamic_cast<const Floresta *>(&outro);
        r->setQuantidade(-r->getQuantidade());
        r->setQuantidade(x->r->getQuantidade());
        qtdP = x->qtdP;
        qtdArvores = x->qtdArvores;
        qtdMaxArvores = x->qtdMaxArvores; //Quantidade de arvores
        diaInicial = x->diaInicial;
    }

    return *this;
}

string Floresta::showInformation(int i, int j) const {

    return Zona::showInformation(i, j) + "Qtd Avores: " +  to_string(qtdArvores) + "\n";


}

bool Floresta::addRecurso(string nRec, double qtd) {

    if(Zona::addRecurso(nRec, qtd))
        return true;

    if(r->getsigla() == nRec){
        r->setQuantidade(qtd);
        return true;
    }
    return false;

}


//metodo produz