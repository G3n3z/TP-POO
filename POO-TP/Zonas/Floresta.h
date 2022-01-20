//
// Created by Daniel Fernandes on 15/12/2021.
//

#ifndef POO_TP1_FLORESTA_H
#define POO_TP1_FLORESTA_H

#include "../Zona.h"
class Floresta:public Zona {
public:
    Floresta(string n);
    double retiraRecursoZona(string , double ) override;
    Recurso* produz() override;
    void efeitosZonas() override;
    const Recurso* getRecurso()const override;
    double retiraRecursoPorTodasZonas(string, double)override;
    ~Floresta();
    Floresta& operator=(const Zona& outro) override;
    string showInformation(int, int) const override;
    bool addRecurso(string, double) override;
private:
    Recurso *r;
    double qtdP; //qtd de producao
    int qtdArvores, qtdMaxArvores; //Quantidade de arvores
    int diaInicial;

};


#endif //POO_TP1_FLORESTA_H
