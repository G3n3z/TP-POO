//
// Created by Daniel Fernandes on 06/01/2022.
//

#ifndef ILHA_CPP_JOGO_H
#define ILHA_CPP_JOGO_H
#include "Ilha.h"
#include "utils/utils.h"
#include "Comand.h"
#include <limits>

class Jogo {

public:
    void run();
    int verificaComando(string linha)const;
    string impressaoComandos()const;
    void execFicheiro(string sComando);
    ~Jogo();
    void comandSave(string);
    void comandLoad(string);
    void comandApaga(string);
private:
    static Comand comands[TAMCOMANDS];
    vector<Ilha*>ilhas;
    Ilha* tab;
};


#endif //ILHA_CPP_JOGO_H
