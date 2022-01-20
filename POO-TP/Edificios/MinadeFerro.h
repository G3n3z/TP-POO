//
// Created by Daniel Fernandes on 15/12/2021.
//

#ifndef POO_TP1_MINADEFERRO_H
#define POO_TP1_MINADEFERRO_H

#include "../Edificio.h"
class MinadeFerro : public Edificio {

public:
    MinadeFerro(string n, double p = 0);
    Recurso* produzE()override;
    void efeitos()override;
    ~MinadeFerro();
    double subirNivel(double) override;
    string toString() const override;
    bool podeSubirNivel() override;
    int getCustoNivel() const override;
    void setQtdProdEdificio(double) override;
    MinadeFerro& operator=(const Edificio& outro)override;

private:
    Recurso *r;
    double maxArma, maxArmPNivel; //qtd de armazenamento e o incrmento por nivel
    double qtdProducao, qtdPporNivel; //qtd de producao por dia e por nivel
    static int custo;
    int nivel;
};


#endif //POO_TP1_MINADEFERRO_H
