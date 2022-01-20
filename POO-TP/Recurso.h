//
// Created by Daniel Fernandes on 16/12/2021.
//

#ifndef POO_TP1_RECURSO_H
#define POO_TP1_RECURSO_H
#include <iostream>
using namespace std;

class Recurso {
public:
    Recurso(string, string , double, double );
    void setQuantidade(double);
    double getPreco()const;

    bool operator==(const Recurso& outro);

    Recurso& operator+= (const Recurso& outro);
    double getQuantidade()const;
    string getsigla()const;
    virtual ~Recurso(){}
    virtual string toString() const;

private:
    string nome, sigla;
    double quantidade;
    double preco;

};

#endif //POO_TP1_RECURSO_H
