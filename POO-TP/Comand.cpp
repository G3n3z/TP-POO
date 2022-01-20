//
// Created by Daniel Fernandes on 07/11/2021.
//

#include "Comand.h"
#include <sstream>
#include <limits>


ComandoValido Comand::comandoValidado;

Comand::Comand(initializer_list<string> comandos, int nums, const string* arg, int tam) {
    initializer_list<string>::iterator it;

    for(it = comandos.begin(); it < comandos.end(); it++){
        this->comandos.push_back(*it);
    }

    this->numArgs = comandos.size();
    this->numInt = nums;
    this->args = arg;
    this->tamArgs = tam;

}

bool Comand::verificaConsComando(const string& linha) {
    istringstream iss;
    string aux;
    vector<string>::iterator it;
    it = this->comandos.begin();
    int i = 0, val,j;
    iss.str(linha);

    while (i < this->numArgs){
        iss >> aux;
        if(i == 0 && aux != *it){ //Validacao do primeiro parametro
            return false; //retorna 0, signfica que o primeiro parametro nao corresponde a  nenhum dos programados
        }
        if(i == 1){ //Validacao do segundo parametro caso exista

            if ((*it == "ficheiro" || *it == "nome")) {
                if (aux != *--it) {
                    comandoValidado.setArgumento(aux);
                    return true;
                } else
                    return false;
            }
            else if(*it == "id"){
                comandoValidado.setArgumento(aux);
                break;
            }
            for (j = 0; j < this->tamArgs ; j++){ //Vai procurar com a lista associada aquele comando
                if (args[j] == aux){
                    comandoValidado.setArgumento(aux);
                    break;
                }

            }
            if(j == tamArgs)
                return false;

        }
        i++;
        it++;
    }


    i = 0;

    while (i < this->numInt){  //Validacao dos parametros do tipo numero. Se eles realmente são numeros
        iss >> val;
        if(iss.fail()){
            iss.clear();
            iss.ignore(numeric_limits<streamsize>::max(), '\n');   //rever se necessario
            return false;
        }
        else
             comandoValidado.setInteiros(val,i);
        i++;
    }
    if(iss.eof()) // Se a string nao foi processada ate ao fim
        return true;

    return false;
}


int Comand::getInteiro( int indice)const{
    return comandoValidado.getInteiro(indice);
}

string Comand::getString() const{
    return comandoValidado.getString();
}

string Comand::getVecComandos()const {
    ostringstream oss;

    int i = 0;
    for (; i< comandos.size(); i++) {
        oss << comandos[i] << " ";
    }
    if(this->tamArgs != 0){
        oss << "{";
        for (int i = 0; i < this->tamArgs; ++i) {
            oss << this->args[i]<< (i != tamArgs-1 ? ",":"");
        }
        oss << "} ";
    }
    return oss.str();
}

int Comand::getnumInt() const {
    return numInt;
}

Comand::~Comand() {}
