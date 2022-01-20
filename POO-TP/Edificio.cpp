//
// Created by Daniel Fernandes on 08/11/2021.
//
#include <random>
#include "Edificio.h"
#include "Zona.h"
#include "Edificios/Fundicao.h"
#include "Edificios/EdificioX.h"
#include "Edificios/Bateria.h"
#include "Edificios/CentralEletrica.h"
#include "Edificios/MinadeCarvao.h"
#include "Edificios/MinadeFerro.h"
#include "Edificios/Serracao.h"


Edificio::Edificio(string n, string nc, bool e, double preco):nome(n), nomeCompleto(nc),
estado(e), estadoEdif(true), preco(preco){}

string Edificio::getName() const{
    return this->nome;
}

bool Edificio::getEstado()const {
    return estado;
}

void Edificio::estadoOn() {
    estado = true;
}

void Edificio::estadoOff() {
    estado = false;
}
Recurso* Edificio::produzE() {

    return nullptr;
}

void Edificio::addRecurso(Recurso* r) {
    rec.push_back(r);
}

void Edificio::setZona(Zona *x) {
    z = x;

}


Edificio *Edificio::buildEdif(string x, const string* edificios, double preco)const {
    if(x == edificios[0]){
        return  new Fundicao(edificios[0], preco);
    }
    else if(x == edificios[1])
        return new EdificioX(edificios[1], preco);
    else if(x == edificios[2])
        return new Bateria(edificios[2], preco);
    else if(x == edificios[3])
        return new CentralEletrica(edificios[3], preco);
    else if(x == edificios[4])
        return new MinadeCarvao(edificios[4], preco);
    else if(x == edificios[5])
        return new MinadeFerro(edificios[5], preco);
    else if(x == edificios[6])
        return new Serracao(edificios[6], preco);

    return nullptr;
}

int Edificio::contMiner()const {
    return z->qtdMineiros();
}
int Edificio::contOper()const{
    return z->qtdOper();
}
int Edificio::contLen()const{
    return z->qtdLenhadores();
}

void Edificio::vZona(string nZona, string r, double qtd)const{
    return z->retiraRecursoZonaAdj(nZona, r, qtd) ;
}

Recurso* Edificio::retornaRecursoEdificio(Recurso* r) { //Retira a totalidade do recurso

    for (auto it:rec) {
        if(it->getsigla() == r->getsigla()){
            return it;
        }
    }
    return nullptr;
}

void Edificio::retiraRecursoDeEdifAdj(string nEdif ,Recurso * r, double qtd, double maxAobter)const {
    z->retiraRecursoPorEdifAdjacentes(nEdif, r, qtd , maxAobter);
}

bool Edificio::verificaRecursoeQtd(string nEdif, string nRec, double qtd)const{
    return z->verificaRecEmEdifAdj(nEdif, nRec, qtd);
}

double Edificio::verificaEdifRecQtd(string nRec, double qtd) {

    for (auto it:rec) {
        if(it->getsigla() == nRec){
            return it->getQuantidade();
        }
    }

    return 0.0;
}

string Edificio::nameZona()const {
    return z->showNome();
}

bool Edificio::getEstadoEdif()const {
    return estadoEdif;
}

void Edificio::setEstadoEdif(bool e) {
    estadoEdif = e;
}

void Edificio::efeitos() {
    return;
}

const Recurso *Edificio::getRecurso()const {
    return rec[0];
}

double Edificio::retiraRec(string nRec, double qtd) {
    for (auto it:rec) {
        if(it->getsigla() == nRec){
            if(it->getQuantidade() >= qtd){ //Se existe quantidade suficiente
                it->setQuantidade(-qtd);
                return qtd;
            }
            else{  //Se nao existe quantidade suficiente
                qtd = it->getQuantidade();
                it->setQuantidade(-it->getQuantidade());
                return qtd;
            }
        }
    }

    return 0;
}

bool Edificio::verificaRecEqtdZonasAdj(string nZona, string nRec, double qtd) const {
    return z->verificaRecEmZonaAdj(nZona, nRec, qtd);
}

double Edificio::getPreco()const {
    return preco;
}

Edificio::~Edificio() {

}

double Edificio::subirNivel(double dinherio) {
    cout << "Este edificio não tem nivel" << endl;
    return 0;
}

string Edificio::toString() const {
    ostringstream oss;

    oss << "----------------" << endl;
    oss << "Edificio:  " << nomeCompleto << endl;
    oss << rec[0]->toString() << endl;
    oss << "Estado :  " << (estado == true ?"ON":"OFF");

    return oss.str();
}

bool Edificio::podeSubirNivel() {
    return false;
}

int Edificio::getCustoNivel() const {
    return 0;
}

Edificio &Edificio::operator=(const Edificio& outro) {
    if(this == &outro)
        return *this;

    //this->rec.clear();
    string nome = outro.nome;
    string nomeCompleto = outro.nomeCompleto;
    estado = outro.estado;
    estadoEdif = outro.estadoEdif;
    preco = outro.preco;
    z = nullptr;

    return *this;

}

void Edificio::setQtdProdEdificio(double) {
    return;
}

bool Edificio::adicionaRecurso(string nRec, double qtd) {


    if(rec.size() == 0)
        return false;

    if(rec[0]->getsigla() == nRec){
        rec[0]->setQuantidade(qtd);
        return true;
    }

    return false;
}

