//
// Created by Daniel Fernandes on 15/12/2021.
//

#ifndef POO_TP1_OPERARIO_H
#define POO_TP1_OPERARIO_H
#include "../Trabalhador.h"

class operario: public Trabalhador{
public:
    operario(string n, int dia): Trabalhador('O',n, dia){}
    bool pedeDemissao(double, int)const;

    ~operario();
};


#endif //POO_TP1_OPERARIO_H
