//
// Created by Daniel Fernandes on 15/12/2021.
//

#ifndef POO_TP1_PASTAGEM_H
#define POO_TP1_PASTAGEM_H

#include "../Zona.h"
class Pastagem : public Zona{
public:
    Pastagem(string n);
    void verificaDemissoes(int);
    ~Pastagem();
    Pastagem& operator=(const Zona& outro);
};


#endif //POO_TP1_PASTAGEM_H
