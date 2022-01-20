//
// Created by Daniel Fernandes on 16/12/2021.
//

#ifndef POO_TP1_BARRADEACO_H
#define POO_TP1_BARRADEACO_H

#include "../Recurso.h"
class BarradeAco : public Recurso{
public:
    BarradeAco(string s = "aco"): Recurso("barra de aco", s, 0, 2){}
    string toString() const override;
    ~BarradeAco(){}
};


#endif //POO_TP1_BARRADEACO_H


