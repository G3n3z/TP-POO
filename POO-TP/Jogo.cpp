//
// Created by Daniel Fernandes on 06/01/2022.
//

#include "Jogo.h"

Comand Jogo::comands[TAMCOMANDS]{ Comand({"cons", "tipo"},2,edificios,TAMEDIFS),
                            Comand({"exec", "ficheiro"},0),
                            Comand({"liga"},2),
                            Comand({"des"},2),
                            Comand({"move", "id"},2),
                            Comand({"vende","tipo"},1,tipodeMaterial,TAMSTRINGS),
                            Comand({"cont", "tipo"},0,trabalhadores,TAMTRABALHADOR),
                            Comand({"list"},2),
                            Comand({"vende"},2),
                            Comand({"next"},0),
                            Comand({"save", "nome"},0),
                            Comand({"load", "nome"},0),
                            Comand({"apaga","nome"},0),
                            Comand({"config","ficheiro"},0),
                            Comand({"debcash"},1),
                            Comand({"debed","tipo"},2,edificios,TAMEDIFS),
                            Comand({"debkill", "id"}),
                            Comand({"list"},0),
                            Comand({"exit"},0),
                            Comand({"sobenivel"},2),
                            Comand({"mostra"},0),
                            Comand({"debrec","tipo"},3,tipodeMaterial, TAMSTRINGS)};

void Jogo::run() {

    int  lin, col, val = 0 , i;
    string linha, aux;

    cout << "Bem vindo! " << endl;

    cout << "Quantas linhas e colunas para a ilha -> ";
    cin >> lin >>col;

    //Validacao do tamanho da ilha pedido ao utilizador
    while (cin.fail()|| (lin < TAMMINLIN || lin > TAMMAXLIN) || (col < TAMMINCOL || col > TAMMAXCOL) ){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Quantas linhas e colunas para a ilha -> ";
        cin >> lin >>col;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int vec[3];
    tab = new Ilha(lin, col); //Construcao da Ilha
    cout << impressaoComandos() << endl;  //Impressao de Comandos
    cout << tab->showIlha() << endl;   //Impressao da Ilha

    while (val==0){    //Ciclo do jogo

        cout << "Digite o comando --> ";
        getline(cin, linha);
        val = verificaComando(linha);

        if(val == 0){
            cout << "Erro de comando" << endl;
        }
        else if(val == 2){
            execFicheiro(comands->getString());
            val = 0;
        }
        else if(val >= 11 && val <=13){
            if(val == 11){ //comando save
                comandSave(comands->getString());
            }
            else if(val == 12){ //load
                comandLoad(comands->getString());

            }
            else if(val == 13){ //apaga
                comandApaga(comands->getString());
            }
            val = 0;
            cout << tab->showIlha() << endl;
        }
        else if(val == 21){
            for (i = 0; i < ilhas.size(); ++i) {
                cout << i+1 << " - " << ilhas[i]->showDetails() << endl;
            }
            if(i == 0){
                cout << "Nao tem snapshots guardados" << endl;
            }
            val = 0;
        }
        else if(tab!= nullptr){
            vec[0] =comands->getInteiro(0);
            vec[1] = comands->getInteiro(1);
            vec[2] = comands->getInteiro(2);
            val = tab->execComand(val, comands->getString(), vec);
            if(val == -1){
                tab->verificaGameOver();
                break;
            }
            cout << tab->showIlha() << endl;
        }
        else{
            cout << "Comando valido mas não existe nenhuma ilha" << endl;
        }

        if(tab->verificaGameOver()){
            cout << "Perdeu o Jogo. Ficou sem recursos, sem trabalhadores e sem dinheiro" << endl;
            return;
        }
    }
    cout << tab->showDetails() << endl;
}

int Jogo::verificaComando(string linha)const {

    for (int i = 0; i < TAMCOMANDS; ++i) {
       if (comands[i].verificaConsComando(linha)) //Se encontrar correspondecia
            return i+1;
    }
    return 0;  //Caso nao seja um comando valido
}


string Jogo::impressaoComandos()const {   //Impressao dos comandos
    ostringstream oss;

    for (int i = 0; i < TAMCOMANDS; ++i) {
        oss << "Comando " << i + 1 << ": " << comands[i].getVecComandos(); //Obtem o comando e seus tipos
        if (comands[i].getnumInt() == 1) {
            if (i == 5 )
                oss << "quanto" << endl;
            else if (i == 14)
                oss << "valor" << endl;
            else
                oss << "Id" << endl;
        } else if (comands[i].getnumInt() == 2)
            oss << "Linha Coluna" << endl;
        else if (comands[i].getnumInt() == 3)
            oss << "Id Linha Coluna" << endl;
        else
            oss << endl;
    }
    return oss.str();
}

void Jogo::execFicheiro(string sComando) { //Execucao de ficheiro de comandos
    ifstream fin;
    string comando;
    int val, count= 0;
    int vec[3];
    fin.open(sComando);
    if(fin.fail()){
        cout << "Erro de abertura de ficheiro" << endl;
        return;
    }
    while(!fin.eof()){
        getline(fin, comando);
        val = this->verificaComando(comando);
        if(val == 0){
            cout << "Erro de comando <-> " + comando << endl;
        }
        else if(val == 2){
            cout << "Comando lido com sucesso <-> " << comando << endl;
            ++count;
            if(count >=5)
                break;
            execFicheiro(comands->getString());
            val = 0;
        }
        else if(val >= 11 && val <=13){
            cout << "Comando lido com sucesso <-> " << comando << endl;
            if(val == 11){ //comando save
                comandSave(comands->getString());
            }
            else if(val == 12){ //load
                comandLoad(comands->getString());

            }
            else if(val == 13){ //apaga
                comandApaga(comands->getString());
            }
            val = 0;
            cout << tab->showIlha() << endl;
        }
        else{
            cout << "Comando lido com sucesso <-> " << comando << endl;
            vec[0] =comands->getInteiro(0);
            vec[1] = comands->getInteiro(1);
            vec[2] = comands->getInteiro(2);
            tab->execComand(val, comands->getString(), vec);
            cout << tab->showIlha() << endl;
        }
        cout << endl;

    }
    fin.close();

}

Jogo::~Jogo() {

    for (auto it: ilhas) {
        delete it;
    }

    if(tab!= nullptr){
        delete tab;
    }
}

void Jogo::comandSave(string nome) {
    for(auto it: ilhas){
        if(it->getName() == nome){
            cout << "Ja existe um save com esse nome. Tente outro" << endl;
            return;
        }
    }
    Ilha* x = new Ilha(tab->getLin(), tab->getCol());
    x->setName(nome);
    x->operator=( *tab);
    ilhas.push_back(x);
}

void Jogo::comandLoad(string nome) {
    for (auto it:ilhas) {
        if(it->getName() == nome){
            delete tab;
            tab = new Ilha(it->getLin(), it->getCol());
            tab->operator=(*it);
            return;
        }
    }
    cout << "Nao foi encontrado um estado de jogo com esse nome" << endl;
}

void Jogo::comandApaga(string nome) {
    vector<Ilha*>::iterator it = ilhas.begin();
    for (; it < ilhas.end(); ++it) {
        if((*it)->getName() == nome){
            ilhas.erase(it);
            delete *it;
            return;
        }
    }
    cout << "Nao foi encontrado um estado de jogo com esse nome" << endl;

}
