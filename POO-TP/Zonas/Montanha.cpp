//
// Created by Daniel Fernandes on 15/12/2021.
//

#include "Montanha.h"

Montanha::Montanha(string n): Zona(n, 0.05, "Montanha"), qtd(0), r(new Ferro("ferro")){
    r->setQuantidade(1.0);
}

Recurso* Montanha::produz() {

    int x = contatrabalhadores();
    if(x == 0)
        return nullptr;
    Recurso *f = new Ferro ;
    f->setQuantidade((x*0.1));
    r->setQuantidade(x*0.1);
    return f;
}

const Recurso *Montanha::getRecurso()const {
    if (r->getQuantidade() == 0)
        return nullptr;
    return r;
}

double Montanha::retiraRecursoPorTodasZonas(string nrec, double qtdd) {
    if(r->getsigla() != nrec)
        return 0;
    if(r->getQuantidade() >= qtdd){
        r->setQuantidade( - qtdd);
        return qtdd;
    }
    qtdd = r->getQuantidade();
    r->setQuantidade( -r->getQuantidade());
    return qtdd;

}

Montanha::~Montanha() {
    delete r;
}

Montanha &Montanha::operator=(const Zona &outro) {
    if(this == &outro)
        return *this;

    Zona::operator=(outro);

    if(outro.showNome() == showNome()) {
        const Montanha *x = dynamic_cast<const Montanha *>(&outro);
        r->setQuantidade(-r->getQuantidade());
        r->setQuantidade(x->r->getQuantidade());
        qtd = x->qtd;
    }
    return *this;

}

void Montanha::constroiEdif(string x, const string * edificios, double preco) {
    Zona::constroiEdif(x, edificios, preco);

    if(getEdifName() == edificios[4] || getEdifName() == edificios[5]){
        setQtdProdEdificio(2);
    }
}

bool Montanha::addRecurso(string nRec, double qtd) {
    if(Zona::addRecurso(nRec, qtd))
        return true;

    if(r->getsigla() == nRec){
        r->setQuantidade(qtd);
        return true;
    }
    return false;
}

int Montanha::mudaPrecoConstrucao() const {
    return 2;
}
