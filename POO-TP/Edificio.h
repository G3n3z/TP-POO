//
// Created by Daniel Fernandes on 08/11/2021.
//

#ifndef POO_TP1_EDIFICIO_H
#define POO_TP1_EDIFICIO_H

#include <vector>
#include "Recursos/BarradeAco.h"
#include "Recursos/Carvao.h"
#include "Recursos/Eletricidade.h"
#include "Recursos/Madeira.h"
#include "Recursos/Viga.h"
#include "Recursos/Ferro.h"

class Bateria;
class CentralEletrica;
class EdificioX;
class Fundicao;
class MinadeCarvao;
class MinadeFerro;
class Serracao;
class Zona;
class Edificio {
public:


    Edificio(string, string, bool, double);
    virtual ~Edificio();
    string getName() const;
    bool getEstado()const;
    void estadoOn();
    void estadoOff();
    void addRecurso(Recurso*);
    virtual Recurso* produzE();
    void setZona(Zona* x);
    Edificio* buildEdif(string , const string*, double)const;
    void vZona(string ,string, double)const;
    Recurso* retornaRecursoEdificio(Recurso*);
    void retiraRecursoDeEdifAdj(string, Recurso*, double, double )const;
    bool verificaRecursoeQtd(string nEdif, string nRec, double)const;
    int contMiner() const;
    int contOper() const;
    int contLen() const;
    double verificaEdifRecQtd(string, double);
    string nameZona()const;
    bool getEstadoEdif()const;
    void setEstadoEdif(bool);
    virtual void efeitos();
    const Recurso* getRecurso()const;
    double retiraRec(string, double);
    bool verificaRecEqtdZonasAdj(string, string, double)const;
    double getPreco()const;
    virtual double subirNivel(double);
    virtual string toString() const;
    virtual bool podeSubirNivel() ;
    virtual int getCustoNivel()const;
    virtual Edificio& operator=(const Edificio& outro);
    virtual void setQtdProdEdificio(double);
    bool adicionaRecurso(string, double);

private:
    string nome;
    string nomeCompleto;
    bool estado;
    bool estadoEdif;
    Zona* z;
    vector<Recurso*> rec;
    double preco;

};


#endif //POO_TP1_EDIFICIO_H
