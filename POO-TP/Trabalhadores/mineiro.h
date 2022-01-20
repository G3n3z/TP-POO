//
// Created by Daniel Fernandes on 15/12/2021.
//

#ifndef POO_TP1_MINEIRO_H
#define POO_TP1_MINEIRO_H

#include "../Trabalhador.h"
class mineiro  : public Trabalhador{

public:
    mineiro(string n, int dia): Trabalhador('M',n, dia){}
    bool pedeDemissao(double, int)const;

    ~mineiro();
};


#endif //POO_TP1_MINEIRO_H
