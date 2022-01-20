//
// Created by Daniel Fernandes on 15/12/2021.
//

#ifndef POO_TP1_DESERTO_H
#define POO_TP1_DESERTO_H
#include "../Zona.h"

class Deserto: public Zona{
public:
    Deserto(string  n = "dsr");
    ~Deserto();
    Deserto& operator=(const Zona& outro) override;
    void constroiEdif(string, const string *, double) override;
};


#endif //POO_TP1_DESERTO_H
