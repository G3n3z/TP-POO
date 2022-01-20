//
// Created by Daniel Fernandes on 15/12/2021.
//

#ifndef POO_TP1_LENHADOR_H
#define POO_TP1_LENHADOR_H
#include "../Trabalhador.h"

class lenhador : public Trabalhador{
public:
    lenhador(string n, int dia): Trabalhador( 'L' ,n, dia){}
    int getdiasTrabalho() const;

    ~lenhador();
    void folga();
    string toString()const;

    lenhador& operator= (const Trabalhador& outro);

private:
    int diastrab = 4;
};


#endif //POO_TP1_LENHADOR_H
