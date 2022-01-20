//
// Created by Daniel Fernandes on 16/12/2021.
//

#include "Recurso.h"

Recurso::Recurso(string n,string s, double q, double p):nome(n), sigla(s), quantidade(q), preco(p) {}

void Recurso::setQuantidade(double x) {
    quantidade += x;
}

double Recurso::getPreco()const{
    return preco;
}

string Recurso::toString()const{
    return nome + " - " + to_string(quantidade).substr(0,4) ;
}

Recurso &Recurso::operator+=(const Recurso &outro) {

    this->quantidade += outro.quantidade;
    return *this;
}

bool Recurso::operator==(const Recurso &outro) {
    if(outro.sigla == sigla)
        return true;

    return false;
}

double Recurso::getQuantidade() const {
    return quantidade;
}

string Recurso::getsigla() const {
    return sigla;
}



