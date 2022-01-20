//
// Created by Daniel Fernandes on 15/12/2021.
//

#ifndef POO_TP1_MONTANHA_H
#define POO_TP1_MONTANHA_H

#include "../Zona.h"
class Montanha: public Zona {
public:
    Montanha(string n);
    Recurso* produz() override;
    const Recurso* getRecurso()const override;
    double retiraRecursoPorTodasZonas(string, double) override;
    ~Montanha();
    Montanha& operator=(const Zona& outro) override;
    void constroiEdif(string, const string *, double) override;
    bool addRecurso(string, double) override;
    int mudaPrecoConstrucao() const override;
private:
    Recurso* r;
    double qtd;
};


#endif //POO_TP1_MONTANHA_H
