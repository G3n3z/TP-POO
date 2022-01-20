//
// Created by Daniel Fernandes on 18/11/2021.
//

#ifndef POO_TP1_COMANDOVALIDO_H
#define POO_TP1_COMANDOVALIDO_H
#include <vector>
#include <iostream>

using namespace std;

class ComandoValido {
public:
    ComandoValido(){}

    void setArgumento(string arg){
        this->argumento = arg;
    }
    void setInteiros(int x, int indice){
        vector<int>::iterator it;
        if(indice >= inteiros.size()){
            inteiros.push_back(x);
        }
        else
        {
            inteiros[indice] = x;
        }
    }

    int getInteiro(int indice)const{
        if(indice >= inteiros.size())
            return -1;
        return this->inteiros[indice];
    }

    string getString() const{
        return this->argumento;
    }
    ~ComandoValido(){}

private:
    string argumento;
    vector<int> inteiros;
};


#endif //POO_TP1_COMANDOVALIDO_H
