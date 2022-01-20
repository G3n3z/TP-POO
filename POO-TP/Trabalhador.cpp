//
// Created by Coolbay on 14/11/2021.
//

#include "Trabalhador.h"
#include "Trabalhadores/mineiro.h"
#include "Trabalhadores/lenhador.h"
#include "Trabalhadores/operario.h"

int Trabalhador::idIn(0);

Trabalhador::Trabalhador(char c ,string t,  int d):tipo(c), nome(t),
dia(d), id(++idIn), ident(setId(id,dia)), movimentacao(false){} //Construtor


char Trabalhador::getTipo() const{
    return this->tipo;
}

string Trabalhador::setId(int i, int d){
    ostringstream oss;
    oss << i << "." << d;
    return oss.str();
}

bool Trabalhador::pedeDemissao(double f, int d)const {
    if(r_uniforme01() < f)
        return true;


    return false;
}



int Trabalhador::getdiasTrabalho() const {
    return 1;
}

void Trabalhador::folga() {
    return;
}

string Trabalhador::toString() const {
    return  this->nome + " |id:" + ident ;
}

string Trabalhador::getIdent()const {
    return ident;
}

Trabalhador* Trabalhador::clonagem()const{
    Trabalhador* x = nullptr;
    if(r_uniforme01() <= 0.1){
        if(tipo == 'O'){
            x = new operario(nome,dia);
        }
        else if(tipo == 'L' && getdiasTrabalho() != 0){
            x = new lenhador(nome,dia);
        }
        else if(tipo == 'M'){
            x = new mineiro(nome,dia);
        }
        return x;
    }
    return x;
}

Trabalhador &Trabalhador::operator=(const Trabalhador &outro) {
    if(this == &outro)
        return  *this;

    tipo = outro.tipo;
    nome = outro.nome;
    id = outro.id;
    dia = outro.dia;
    ident = outro.ident;
    --idIn;
    return *this;
}

string Trabalhador::strDespedimento()const {
    return "Eu sou o " + nome + " com id: " + ident + " e fartei-me disto... Despeco-me!" + "\n";
}

bool Trabalhador::getMovimentacao()const {
    return movimentacao;
}

void Trabalhador::repoeMovimentacao() {
    movimentacao = false;
}

void Trabalhador::movimentou() {
    movimentacao = true;
}

int Trabalhador::getDia() const {
    return dia;
}


