//
// Created by Coolbay on 14/11/2021.
//

#ifndef MAIN_CPP_TRABALHADOR_H
#define MAIN_CPP_TRABALHADOR_H
#include <iostream>
#include <sstream>
#include <string>
#include "utils/utils.h"

using namespace std;

class Trabalhador {
public:

    Trabalhador(char, string, int);
    char getTipo() const;
    string setId(int, int);
    virtual ~Trabalhador(){

    }
    int getDia()const;
    virtual bool pedeDemissao(double, int)const;
    virtual int getdiasTrabalho() const;
    virtual void folga();
    virtual string toString()const;
    string getIdent()const;
    Trabalhador* clonagem()const; // analisa o trabalhador enviado e dada uma percentagem devolve uma copia
    virtual Trabalhador& operator=(const Trabalhador& outro);
    string strDespedimento()const;
    bool getMovimentacao()const;
    void repoeMovimentacao();
    void movimentou();

private:
    static int idIn;
    char tipo; // O, M, L
    string nome;
    int id, dia;
    string ident;
    bool movimentacao;
};


#endif //MAIN_CPP_TRABALHADOR_H
