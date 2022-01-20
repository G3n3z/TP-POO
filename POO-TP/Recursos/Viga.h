//
// Created by Daniel Fernandes on 16/12/2021.
//

#ifndef POO_TP1_VIGA_H
#define POO_TP1_VIGA_H
#include "../Recurso.h"

class Viga: public Recurso{
public:
    Viga(string s = "viga"): Recurso("viga", s, 0, 2){}
    string toString()const override;
    ~Viga(){}
};


#endif //POO_TP1_VIGA_H
