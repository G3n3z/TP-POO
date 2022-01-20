//
// Created by Daniel Fernandes on 16/12/2021.
//

#ifndef POO_TP1_ELETRICIDADE_H
#define POO_TP1_ELETRICIDADE_H
#include "../Recurso.h"

class Eletricidade  : public Recurso{
public:
    Eletricidade(string s = "elet"): Recurso("eletricidade", s, 0, 1.5){}

    ~Eletricidade(){}
    string toString()const override;

};



#endif //POO_TP1_ELETRICIDADE_H
