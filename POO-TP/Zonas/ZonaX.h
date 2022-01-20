//
// Created by Daniel Fernandes on 15/12/2021.
//

#ifndef POO_TP1_ZONAX_H
#define POO_TP1_ZONAX_H
#include "../Zona.h"

class ZonaX : public Zona{
public:
    ZonaX(string n);
    ~ZonaX();
    ZonaX& operator=(const Zona& outro)override;
    void efeitosZonas() override;

};


#endif //POO_TP1_ZONAX_H
