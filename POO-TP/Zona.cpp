//
// Created by Daniel Fernandes on 09/11/2021.
//

#include "Zona.h"
#include "Zonas/Deserto.h"
#include "Zonas/Floresta.h"
#include "Zonas/Montanha.h"
#include "Zonas/Pantano.h"
#include "Zonas/Pastagem.h"
#include "Zonas/ZonaX.h"

Zona::Zona():nome(), edif(nullptr){   //Construtor

}
Zona::Zona(string n, double f, string nCompleto): nome(n), percD(f), edif(nullptr), nomeCompleto(nCompleto) {}

string Zona::showNome() const{
    return nome;
}

string Zona::showEdificio() const {
    if(edif!= nullptr)
        return edif->getName();
    else return "";
}


void Zona::constroiEdif(string x, const string * edificios, double preco) { //Construcao do edificio

    edif = edif->buildEdif(x, edificios, preco);
    if(edif != nullptr){
        edif->setZona(this);
    }
}

string Zona::showTrabalhadores() const{   //Mostra os tipos dos trabalhadores na zona
    ostringstream oss;

    for(int i = 0; i < t.size() && i < 4; i++)
        oss << t[i]->getTipo();

    return oss.str();
}
void Zona::contrataOper(string nome,  int dia) {  //Aloca memoria e adiciona ao vector
    Trabalhador* novo;
    novo = new operario(nome, dia); //Alocacao de um trabalhador
    t.push_back((novo));
}
void Zona::contrataMiner(string nome, int dia){
    Trabalhador* novo;
    novo = new mineiro(nome, dia);
    t.push_back((novo));
}

void Zona::contrataLen(string nome, int dia){
    Trabalhador* novo;
    novo = new lenhador(nome, dia);
    t.push_back((novo));
}


string Zona::contarTrab() const{   //Contagem para impressao dos trabalhadores
    ostringstream oss;
    oss << t.size();
    return oss.str();
}

bool Zona::verificaEdificio() const{ //Verifica se ja existe algum edificio construido

    if(this->edif != nullptr)
        return false;

    return true;
}

string Zona::showInformation(int i, int j) const{   //Mostra informacao da zona i,j
    ostringstream oss;
    oss << "Zona " << i <<" "<< j <<  " : " << this->showNomeCompleto() << endl;

    oss << recToString();

    if(edif != nullptr){
        oss << edif->toString() << endl;

    }
    else
        oss << "Nao tem edificio construido" << endl;

    if(!t.empty()){
        int tipoO = 0, tipoM = 0, tipoL = 0;
        for (int i = 0; i < t.size(); ++i) {
            oss << t[i]->toString() << endl;
            if(t[i]->getTipo() == 'L')
                tipoL++;
            else if(t[i]->getTipo() == 'O')
                tipoO++;
            else
                tipoM++;
        }
        oss << "Empregados: " << tipoL << " Lenhadores  |  " <<tipoM << " Mineiros  |  " << tipoO << " Operarios" << endl;
    }
    else
        oss << "Nao tem trabalhadores"<< endl;


    return oss.str();
}

void Zona::liga() {
    edif->estadoOn();
}
void Zona::desliga() {
    edif->estadoOff();
}

Recurso* Zona::produz() {
    return nullptr;
}

int Zona::contatrabalhadores()const {
    return t.size();
}

void Zona::addTrablhador(Trabalhador* x) {
    t.push_back(x);
}

Trabalhador *Zona::searchTrab(string id, bool move) {

    vector<Trabalhador*>::iterator it =t.begin();
    Trabalhador * x;
    while(it != t.end()){
        if((*it)->getIdent() == id){
            if( move == true && (*it)->getMovimentacao() == move )
                return nullptr;
            (*it)->movimentou();
            x = *it;
            t.erase(it);
            return x;
        }
        else
            ++it;
    }

    return nullptr;
}
string Zona::getEdifName()const{
    return edif->getName();
}

void Zona::addZonaAdj(Zona * adj) {

    zAdjacentes.push_back(adj);

}

Recurso *Zona::produzEdif() {

    Recurso *r;
    if(edif != nullptr)
        r = edif->produzE();
    else
        return nullptr;
    return r;
}
/*========== Verifica demissoes no vetor de trabalhadores da zona ==========*/
void Zona::verificaDemissoes(int dia){
    vector<Trabalhador*>::iterator it = t.begin();
    while (it < t.end()){
        if((*it)->pedeDemissao(percD, dia)){
            cout << (*it)->strDespedimento();
            delete *it;
            it = t.erase(it);
        }
        ++it;
    }
}

Zona *Zona::constroiZona(double x, double vec[], const string* tipozonas) {
    if(x <= vec[0]) {
        return new Deserto(tipozonas[0]);
    }
    else if(x <= vec[1]) {
        return new Montanha(tipozonas[1]);
    }
    else if(x <= vec[2]) {
        return new Pastagem(tipozonas[2]);

    }
    else if(x <= vec[3]) {
        return new Floresta(tipozonas[3]);
    }
    else if(x <= vec[4]) {
        return new Pantano(tipozonas[4]);
    }
    else if(x <= vec[5]) {
        return new ZonaX(tipozonas[5]);
    }

    return nullptr;
}

int Zona::qtdMineiros()const {

    int count = 0;
    for (auto it: t) {
        if(it->getTipo() == 'M')
            ++count;
    }

    return count;
}

int Zona::qtdOper()const{

    int count = 0;
    for (auto it: t) {
        if(it->getTipo() == 'O')
            ++count;
    }

    return count;
}

void Zona::retiraRecursoZonaAdj(string nZona, string rec, double qtd) {

    for (auto it :zAdjacentes) {
        if(it->showNome() == nZona){
            qtd -= it->retiraRecursoZona(rec, qtd);
            if(qtd == 0.0)
                return;

        }
    }
    return;
}

double Zona::retiraRecursoZona(string x, double qtd) {
    return qtd;
}
void Zona::retiraRecursoPorEdifAdjacentes(string nEdif, Recurso* r, double qtd, double max) { //Tira a totalidade ou uma qtd do recurso
    Recurso* y;
    for (auto it: zAdjacentes) {
        if(it->edif != nullptr){
            if(it->edif->getName() == nEdif){
                y = it->edif->retornaRecursoEdificio(r);
                if(y!= nullptr){
                    if(qtd == -1){ //Se qtd = -1 é apra tirar toda a quantidade
                        if(y->getQuantidade() > max){
                            y->setQuantidade(-max);
                            r->setQuantidade(max);
                            return;
                        }
                        else {
                            max -= y->getQuantidade();
                            r->setQuantidade(y->getQuantidade());
                            y->setQuantidade(-y->getQuantidade());
                        }

                    }
                    else{
                        if(y->getQuantidade() >= qtd){ //Se existir mais quantidade do que a pedida
                            y->setQuantidade(-qtd);
                            r->setQuantidade(qtd);
                            return;
                        }
                        if(y->getQuantidade() < qtd){ //Se nao existir quantidade suficiente
                            qtd -= y->getQuantidade();
                            r->setQuantidade(y->getQuantidade());
                            y->setQuantidade(-y->getQuantidade());

                        }
                    }

                }
            }
        }
    }
    return;

}


bool Zona::verificaRecEmEdifAdj(string nEdif, string nRec, double qtd)const{

    double soma = 0.0;
    for(auto it:zAdjacentes){
        if(it->edif != nullptr){
            if(it->edif->getName() == nEdif){
                soma +=it->edif->verificaEdifRecQtd(nRec, qtd);
            }
        }
    }

    return (soma >= qtd);
}

int Zona::qtdLenhadores()const {
    int count = 0;
    for (auto it: t) {
        if(it->getTipo() == 'L' && it->getdiasTrabalho() !=0)
            ++count;
    }

    return count;
}

void Zona::efeitosZonas() {

    for (auto it:t) {
        if(it->getTipo() == 'L'){
            it->folga();
        }
        it->repoeMovimentacao();
    }

    return;
}

void Zona::setEstadoEdif(bool e)const {
    if(edif!= nullptr)
        edif->setEstadoEdif(e);
}

void Zona::demiteAlltrabalhadores() {
    vector<Trabalhador*>::iterator it = t.begin();

    while (it<t.end()){
        delete *it;
        ++it;
    }
    t.clear();
}

void Zona::eliminaEdif() {
    if(edif == nullptr)
        return;

    delete edif;
    edif = nullptr;
}

void Zona::efeitosEdif() {
    if(edif == nullptr)
        return;
    edif->efeitos();
    if(!edif->getEstadoEdif()){
        delete edif;
        edif = nullptr;
    }
}

const Recurso * Zona::getRecurso() const {
    return nullptr;
}

const Recurso *Zona::getRecursoEdif() const{
    if(edif == nullptr)
        return nullptr;
    return edif->getRecurso();
}

string Zona::recToString() const {
    const Recurso* x = getRecurso();

    if(x != nullptr){
        return  x->toString() + "\n";
    }
    return "";
}

double Zona::retiraRecurso(string nRec, double qtd)const {
    if(edif!= nullptr)
        return edif->retiraRec(nRec, qtd);
    return 0;
}

double Zona::retiraRecursoPorTodasZonas(string x, double qtd) {
    return 0;
}

void Zona::vendeEdif(double * din) {
    const Recurso* r = edif->getRecurso();
    (*din) += (r->getQuantidade() * r->getPreco()) + edif->getPreco();
    delete edif;
    edif = nullptr;
}

string Zona::showNomeCompleto() const {
    return nomeCompleto;
}

bool Zona::verificaRecEmZonaAdj(string nZona, string nRec, double qtd)const {
    double soma = 0.0;
    const Recurso* x;
    for(auto it:zAdjacentes){
        if(it->showNome() == nZona){
            x = it->getRecurso();
            if(x != nullptr && x->getsigla() == nRec){
                soma +=x->getQuantidade();
            }

        }
    }

    return (soma >= qtd);
}

double Zona::sobeNivel(double d)const {

    return edif->subirNivel(d);
}

Trabalhador *Zona::getTrabalhador(int x)const {
    return t[x];
}

bool Zona::podeSubirNivel()const {

    return edif== nullptr ? false : edif->podeSubirNivel();
}

int Zona::getcustoNivel() const {
    return edif->getCustoNivel();
}

Zona &Zona::operator=(const Zona &outro) {

    if(this == &outro)
        return *this;

    zAdjacentes.clear();

    if(edif != nullptr)
        delete edif;

    if(outro.edif != nullptr){
        edif = edif->buildEdif(outro.edif->getName(), edificios, outro.edif->getPreco());

        edif->operator=(*outro.edif);
        edif->setZona(this);
    }
    else
        edif = nullptr;


    vector<Trabalhador*>::iterator it = t.begin();
    for (;it < t.end();) {
        delete *it;
        it = t.erase(it);
    }

    for (int i = 0; i < outro.t.size(); ++i) {
        if(outro.t[i]->getTipo() == 'O')
            contrataOper(trabalhadores[0], 0);
        else if(outro.t[i]->getTipo() == 'L')
            contrataLen(trabalhadores[1],0);
        else
            contrataMiner(trabalhadores[2],0);

        (*t[i]).operator=(*outro.t[i]);
    }

    return *this;
}

Zona *Zona::constroiZonaByString(string n)const {
    if (n == tipozonas[0])
         return new Deserto(tipozonas[0]);
    else if (n == tipozonas[1])
        return new Montanha(tipozonas[1]);
    else if (n == tipozonas[2])
        return new Pastagem(tipozonas[2]);
    else if (n == tipozonas[3])
        return new Floresta(tipozonas[3]);
    else if (n == tipozonas[4])
        return new Pantano(tipozonas[4]);
    else if (n == tipozonas[5])
        return new ZonaX(tipozonas[5]);

    return nullptr;
}

void Zona::setQtdProdEdificio(double x)const {
    edif->setQtdProdEdificio(x);
}

bool Zona::addRecurso(string nRec, double qtd) {

    if(edif == nullptr)
        return false;

    if(edif->adicionaRecurso(nRec, qtd))
        return true;

    return false;
}

int Zona::mudaPrecoConstrucao() const {
    return 1;
}





