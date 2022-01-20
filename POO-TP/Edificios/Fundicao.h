//
// Created by Daniel Fernandes on 15/12/2021.
//

#ifndef POO_TP1_FUNDICAO_H
#define POO_TP1_FUNDICAO_H
#include "../Edificio.h"

class Fundicao: public Edificio{
public:
    Fundicao(string n, double p = 0);
    Recurso* produzE();
    ~Fundicao();
    Fundicao& operator=(const Edificio& outro);

private:
    Recurso *a;
    double qtdMax;
};


#endif //POO_TP1_FUNDICAO_H
