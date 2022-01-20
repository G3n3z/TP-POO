//
// Created by Daniel Fernandes on 16/12/2021.
//

#ifndef POO_TP1_FERRO_H
#define POO_TP1_FERRO_H

#include "../Recurso.h"
class Ferro  : public Recurso{
public:
    Ferro(string s = "ferro"): Recurso("ferro", s, 0, 2){}
    string toString()const override;
    ~Ferro(){}
};



#endif //POO_TP1_FERRO_H
