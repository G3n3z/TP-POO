//
// Created by Daniel Fernandes on 09/11/2021.
//

#ifndef POO_TP1_ZONA_H
#define POO_TP1_ZONA_H
#include "Edificio.h"
#include "Trabalhadores/lenhador.h"
#include "Trabalhadores/mineiro.h"
#include "Trabalhadores/operario.h"
#include <vector>
#include <sstream>
class Deserto;
class Floresta;
class Montanha;
class Pantano;
class Pastagem;
class ZonaX;
class Zona {
public:
    Zona();
    Zona(string, double, string);
    string showNome() const;
    string showNomeCompleto() const;
    string showEdificio() const;
    string showTrabalhadores() const;
    virtual void constroiEdif(string, const string*, double);
    void contrataMiner(string , int);
    void contrataOper(string, int);
    void contrataLen(string, int);
    string contarTrab() const;
    bool verificaEdificio() const;
    virtual string showInformation(int , int) const;
    void liga();
    void desliga();
    virtual Recurso* produz();
    int contatrabalhadores()const;
    void addTrablhador(Trabalhador* );
    Trabalhador* searchTrab(string, bool move = false);
    string getEdifName()const;
    void addZonaAdj(Zona*);
    Recurso* produzEdif();
    virtual void verificaDemissoes(int);
    Zona* constroiZona(double , double[],const string*);
    int qtdMineiros()const;
    int qtdLenhadores()const;
    void retiraRecursoZonaAdj(string, string, double );
    virtual double retiraRecursoZona(string , double);
    virtual void efeitosZonas();
    virtual double retiraRecursoPorTodasZonas(string, double);
    bool verificaRecEmZonaAdj(string, string, double) const;
    void retiraRecursoPorEdifAdjacentes(string, Recurso*, double, double);
    int qtdOper() const;
    virtual ~Zona(){
        delete edif;
        vector<Trabalhador*>::iterator it = t.begin();
        while (it<t.end()){
            delete *it;
            it = t.erase(it);
        }
    }

    bool operator==(const Zona& outro){
        return this->nome == outro.nome;
    }

    bool verificaRecEmEdifAdj(string nEdif, string nRec, double qtd)const;
    void setEstadoEdif(bool )const;
    void demiteAlltrabalhadores();
    void eliminaEdif();
    void efeitosEdif();
    virtual const Recurso * getRecurso() const;
    const Recurso* getRecursoEdif()const;
    string recToString() const;
    double retiraRecurso(string, double)const;
    void vendeEdif(double *);
    double sobeNivel(double)const;
    Trabalhador* getTrabalhador(int)const;
    bool podeSubirNivel()const;
    int getcustoNivel()const;
    virtual Zona& operator=(const Zona& outro);
    Zona* constroiZonaByString(string)const;
    void setQtdProdEdificio(double)const;
    virtual bool addRecurso(string, double);
    virtual int mudaPrecoConstrucao() const;

private:
    double percD; // percentagem de demissao da zona
    string nome, nomeCompleto;
private:
    Edificio *edif;
    vector<Trabalhador*> t;
    vector<Zona*> zAdjacentes;


};


#endif //POO_TP1_ZONA_H
