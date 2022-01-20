#ifndef POO_TP1_SERRACAO_H
#define POO_TP1_SERRACAO_H
#include "../Edificio.h"

class Serracao: public Edificio{
public:
    Serracao(string n, double p = 0);
    Recurso* produzE()override;
    ~Serracao();

    Serracao& operator=(const Edificio& outro)override;

private:
    Recurso *v;
    double qtdMax;
};


#endif //POO_TP1_SERRACAO_H
