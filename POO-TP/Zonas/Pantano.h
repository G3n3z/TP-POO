//
// Created by Daniel Fernandes on 15/12/2021.
//

#ifndef POO_TP1_PANTANO_H
#define POO_TP1_PANTANO_H

#include "../Zona.h"
class Pantano: public Zona{
public:
    Pantano(string n);
    void efeitosZonas();
    ~Pantano();
    Pantano& operator=(const Zona& outro);

private:
    int dia;
};


#endif //POO_TP1_PANTANO_H
