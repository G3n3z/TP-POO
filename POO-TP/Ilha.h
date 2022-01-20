//
// Created by Daniel Fernandes on 07/11/2021.
//

#ifndef POO_TP1_ILHA_H
#define POO_TP1_ILHA_H
#include "Comand.h"
#include "Zona.h"
#include <fstream>
#include <map>
#include "utils/utils.h"


class Ilha {
public:
    Ilha(int, int);  //Construtor da ilha
    string showIlha() const;
    int execComand(int, string, int vec[]);
    bool validaTam(int, int) const;
    void randomPast(int&)const;
    void configMaps();
    void reconfig(string);
    void contrataTrab(string); //veriica qual o trab a contratar, ver o custo e se existe dinheiro - Se existir contrata
    string imprimeCustos()const;
    void avancaFase();
    void compoeZonasAdjacentes();
    string getRecursos() const;
    string getTrab()const;
    bool verificaVendeRecurso(string nRec, double qtd);
    ~Ilha();
    void retiraRec(string, double);
    int verificaCustoRecurso(string, int );
    string getName()const;
    void setName(string);
    int getLin()const;
    int getCol()const;
    string showDetails()const;
    int verificaCustoTotalRecurso(string, int);
    bool verificaGameOver();
    Ilha& operator=(const Ilha& outro);
    void addRecurso(string, int v[])const;



private:

    int lin, col, dia, faseDoDia;
    double dinheiro;
    Zona **zonas;
    vector<int> indicesPasto;
    map <string, int> custoConfig;
    map <string, pair<string, int>> custoEdifRec;
    map <string, pair<string, int>> custoTotalEdifRec;
    map<string, pair<string, int>> custoPNivel;
    vector<Recurso*>rec;
    string name;
    double pontuacao;
};


#endif //POO_TP1_ILHA_H
