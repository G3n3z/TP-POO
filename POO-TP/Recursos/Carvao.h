//
// Created by Daniel Fernandes on 16/12/2021.
//

#ifndef POO_TP1_CARVAO_H
#define POO_TP1_CARVAO_H

#include "../Recurso.h"
class Carvao  : public Recurso{
public:
    Carvao(string s = "carvao"): Recurso("carvao", s, 0, 1){}
    string toString()const override;
    ~Carvao(){}
};


#endif //POO_TP1_CARVAO_H
