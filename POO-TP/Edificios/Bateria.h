//
// Created by Daniel Fernandes on 15/12/2021.
//

#ifndef POO_TP1_BATERIA_H
#define POO_TP1_BATERIA_H
#include "../Edificio.h"

class Bateria : public Edificio{
public:
    Bateria(string n = "bat", double p = 0);
    Recurso* produzE() override;
    ~Bateria(){
        delete e;
    }
    double subirNivel(double dinheiro) override;
    string toString() const override;
    bool podeSubirNivel() override;
    int getCustoNivel() const override;
    Bateria& operator=(const Edificio& outro)override;

private:
    double capacidade, capacidadePN, nivel;
    static int Custo;
    Recurso *e;

};


#endif //POO_TP1_BATERIA_H
