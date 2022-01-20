//
// Created by Daniel Fernandes on 15/12/2021.
//

#ifndef POO_TP1_MINADECARVAO_H
#define POO_TP1_MINADECARVAO_H
#include "../Edificio.h"

class MinadeCarvao : public Edificio{
public:
    MinadeCarvao(string n, double p = 0);
    Recurso* produzE()override;
    void efeitos()override;
    ~MinadeCarvao();
    double subirNivel(double) override;
    string toString() const override;
    bool podeSubirNivel() override;
    int getCustoNivel() const override;
    void setQtdProdEdificio(double) override;
    MinadeCarvao& operator=(const Edificio& outro)override;

private:
    double qtdProducao, qtdPporNivel; //qtd de producao por dia e por nivel
    Recurso *r;
    double maxArma, maxArmPNivel; //qtd de armazenamento e o incrmento por nivel
    static int custo;
    int nivel;
};


#endif //POO_TP1_MINADECARVAO_H
