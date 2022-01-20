//
// Created by Daniel Fernandes on 16/12/2021.
//

#ifndef POO_TP1_MADEIRA_H
#define POO_TP1_MADEIRA_H

#include "../Recurso.h"
class Madeira  : public Recurso{
public:
    Madeira(string s = "madeira"): Recurso("madeira", s, 0, 1){}
    string toString()const override;
    ~Madeira(){}
};


#endif //POO_TP1_MADEIRA_H
