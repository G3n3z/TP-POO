#include "../Zonas/Floresta.h"
#include "Serracao.h"

Serracao::Serracao(string n, double p):Edificio(n,"serracao",false,p), v(new Viga) , qtdMax(100.0){
    addRecurso(v);
}

Recurso *Serracao::produzE() {
    if(!getEstado())
        return nullptr;

    if(v->getQuantidade() >= qtdMax)
        return nullptr;

    int q = contLen();
    if(q == 0){
        return nullptr;
    }

    if(!verificaRecEqtdZonasAdj("flr", "madeira", 2.0)){
        return nullptr;
    }

    vZona("flr","madeira",2.0);

    Recurso *r = new Viga;
    r->setQuantidade(1);

    v->setQuantidade(1);
    return r;
}

Serracao::~Serracao() {
    delete v;
}

Serracao &Serracao::operator=(const Edificio &outro) {
    if(this == &outro)
        return *this;
    Edificio::operator=(outro);

    if(outro.getName() == getName()) {
        const Serracao *x = dynamic_cast<const Serracao *>(&outro);
        v->setQuantidade(-v->getQuantidade());
        v->setQuantidade(x->v->getQuantidade());
        qtdMax = x->qtdMax;
    }
    return *this;
}

