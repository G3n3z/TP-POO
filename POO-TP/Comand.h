//
// Created by Daniel Fernandes on 07/11/2021.
//

#ifndef POO_TP1_COMAND_H
#define POO_TP1_COMAND_H
#include <initializer_list>
#include "ComandoValido.h"


class Comand {
public:
    Comand(initializer_list<string> ={}, int nums = 0, const string *arg = nullptr, int tam = 0);
    bool verificaConsComando(const string&);
    string getString() const;
    int getInteiro(int indice)const;
    string getVecComandos()const;
    int getnumInt()const;
    ~Comand();

private:
    vector <string> comandos;
    const string *args;
    int tamArgs; //Tam do Args
    int numArgs; // Quantidade de args do vector
    int numInt; // Quantidade de inteiros necessarios
    static ComandoValido comandoValidado;
};


#endif //POO_TP1_COMAND_H
