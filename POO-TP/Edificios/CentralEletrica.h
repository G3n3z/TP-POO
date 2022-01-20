//
// Created by Daniel Fernandes on 15/12/2021.
//

#ifndef POO_TP1_CENTRALELETRICA_H
#define POO_TP1_CENTRALELETRICA_H

#include "../Edificio.h"
class CentralEletrica: public Edificio{

public:
    CentralEletrica(string n, double p = 0);
    Recurso* produzE() override;
    ~CentralEletrica();

    CentralEletrica& operator=(const Edificio& outro)override;


private:
    Recurso *c, *e;
    int qtdCarvao, qtdElet;
    int maxCarvao;
};


#endif //POO_TP1_CENTRALELETRICA_H
