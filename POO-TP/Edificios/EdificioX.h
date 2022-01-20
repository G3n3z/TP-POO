//
// Created by Daniel Fernandes on 15/12/2021.
//

#ifndef POO_TP1_EDIFICIOX_H
#define POO_TP1_EDIFICIOX_H
#include "../Edificio.h"

class EdificioX: public Edificio{ //central eolica
public:
    EdificioX(string, double p = 0);
    Recurso* produzE() override;
    ~EdificioX();
    double subirNivel(double) override;
    string toString() const override;
    bool podeSubirNivel() override;
    int getCustoNivel() const override;
    EdificioX& operator=(const Edificio& outro) override;
private:
    Recurso *e;
    double maxElet, maxPNivel, prod, prodPNivel;
    int nivel;
    static int custo;
};


#endif //POO_TP1_EDIFICIOX_H
