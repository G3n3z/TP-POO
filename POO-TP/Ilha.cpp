//
// Created by Daniel Fernandes on 07/11/2021.
//

#include "Ilha.h"
#include <cstdlib>
#include <algorithm>


Ilha::Ilha(int linha, int coluna):lin(linha), col(coluna), dinheiro(500), dia(1), faseDoDia(1), pontuacao(0)
{

    int i = 0, j = 0;
    double x;

    zonas = new Zona*[(lin*col)];
    double vec[6];
    for (int k = 0; k < TAMSTRINGS; ++k) {
        vec[k]=((k+1)/(double)TAMSTRINGS);
    }

    for (int k = 0; k < lin*col; ++k) {
        zonas[k] = nullptr;

    }


    while(i < lin*col){
        x = uniforme01();
        while (zonas[i]!= nullptr){
            x = uniforme01();
        }
        zonas[i] = zonas[i]->constroiZona(x, vec, tipozonas);
        if(zonas[i] != nullptr && zonas[i]->showNome() == tipozonas[2])
            indicesPasto.push_back(i);
        i++;
    }

    compoeZonasAdjacentes();
    configMaps();

}
void Ilha::compoeZonasAdjacentes() {
    int x, ind;
    for (int i = 0; i < lin; ++i) {
        for (int j = 0; j < col; ++j) {
            ind = i*col +j;
            if(validaTam(i-1, j)){
                x = (i-1) * col + j;
                zonas[ind]->addZonaAdj(zonas[x]);
            }
            if(validaTam(i+1, j)){
                x = (i+1) * col + j;
                zonas[ind]->addZonaAdj(zonas[x]);
            }
            if(validaTam(i, j-1)){
                x = i * col + (j-1);
                zonas[ind]->addZonaAdj(zonas[x]);
            }
            if(validaTam(i, j+1)){
                x = i * col + (j+1);
                zonas[ind]->addZonaAdj(zonas[x]);
            }
        }
    }
}


string Ilha::showIlha () const{   //Funcao de impressao da Ilha
    ostringstream oss;

    oss << "-";
    for(int i = 0; i<col-1;i++){
        oss <<"-----";

    }
    oss<< "-----" << endl;

    for (int i = 0; i < lin  ; i++) {
        oss << "|";
        for (int j = 0; j < col; ++j) {
            oss << (*(zonas+i*col +j))->showNome();  //Nome da zona
            for (int k = (int)(*(zonas+i*col +j))->showNome().length(); k < 4; k++) //Calculo de espacos
                oss << " ";
            oss << "|";
        }
        oss << endl;
        oss << "|";
        for (int j = 0; j < col; ++j) {
            oss << (*(zonas+i*col +j))->showEdificio(); // Nome do edificio
            for (int k = (int)(*(zonas+i*col +j))->showEdificio().length(); k < 4; k++)
                oss << " ";
            oss<<"|";
        }
        oss << endl;
        oss << "|";
        for (int j = 0; j < col; ++j) {
            oss <<(*(zonas+i*col +j))->showTrabalhadores(); //Nome dos trabalhadores
            for (int k = (int)(*(zonas+i*col +j))->showTrabalhadores().length(); k < 4; k++)
                oss << " ";
            oss << "|";
        }
        oss << endl;
        oss << "|";
        for (int j = 0; j < col; ++j) {
            oss<< (*(zonas+i*col +j))->contarTrab(); //Numero dos trabalhadores
            for (int k = (int)(*(zonas+i*col +j))->contarTrab().length(); k < 4; k++)
                oss << " ";
            oss << "|";
        }
        oss << endl;
        if(i!=lin-1) {
            oss << "|";
            for (int j = 0; j < col; ++j) {
                oss << "----|";

            }

            oss << endl;
        }

    }

    oss << "-";
    for(int i = 0; i<col-1;i++){
        oss <<"-----";

    }
    oss<< "-----" << endl;
    oss << "Dia: "<< dia << endl << "Dinheiro: " << dinheiro << endl;
    oss << getRecursos() << endl << "Meio dia!";
    return oss.str();
}

bool Ilha::validaTam(int l, int c) const{ //Validacao da linha e coluna introduzida nos comandos

    return (l > -1 && c > -1)  && (l < lin && c < col);
}

void Ilha::randomPast(int &x)const {   //Calcula uma posicao de pasto random

    int z =( rand() % indicesPasto.size());
    x = indicesPasto[z];
}

int Ilha::execComand(int num, string sComando, int vec[]) {  //Funcao de execucao de comandos



    switch (num) {
        case 1: //Comando de construcao de edificios
            if(validaTam(vec[0]-1,vec[1]-1) ) {
                int mul = (*(zonas + (vec[0] - 1) * col + (vec[1] - 1)))->mudaPrecoConstrucao();
                if ((*(zonas + (vec[0] - 1) * col + (vec[1] - 1)))->verificaEdificio()){ //Adicionar recursos
                    auto it = custoEdifRec.find(sComando);
                    if (it != custoEdifRec.end()) {
                        int custo = verificaCustoRecurso(sComando, mul); //Verifica se existe o recurso

                        if (!custo) { //Se for 0 há recursos suficientes

                            retiraRec(it->second.first, it->second.second * mul); //retira o recurso dos edificios e zonas
                            (*(zonas + (vec[0] - 1) * col + (vec[1] - 1)))->constroiEdif(sComando,edificios, 0);
                        } else {
                            cout<< "custo: " << custo << endl;
                            int retirar = custo;
                            auto it = custoConfig.find(sComando);
                            if(it != custoConfig.end())
                                custo = custo * it->second;

                            if (dinheiro >= custo) {
                                auto it = custoEdifRec.find(sComando);
                                if (it != custoEdifRec.end())
                                    retiraRec(it->second.first, (it->second.second * mul) - retirar); //retira o recurso dos edificios e zonas
                                dinheiro -= custo;
                                (*(zonas + (vec[0] - 1) * col + (vec[1] - 1)))->constroiEdif(sComando,
                                                                                             edificios, custo);
                            } else
                                cout << "Nao tem dinhiro e/ou recursos suficientes" << endl;

                        }

                    }
                    else{
                        auto it =  custoTotalEdifRec.find(sComando);
                        if(it != custoTotalEdifRec.end()){
                            int custo = verificaCustoTotalRecurso(it->second.first, it->second.second * mul);
                            if(!custo){
                                auto i = custoConfig.find(sComando);
                                if(i != custoConfig.end()){
                                    if(dinheiro >= i->second * mul){
                                        retiraRec(it->second.first, it->second.second * mul);
                                        dinheiro -= i->second * mul;
                                        (*(zonas + (vec[0] - 1) * col + (vec[1] - 1)))->constroiEdif(sComando,edificios, i->second * mul);
                                    }
                                    else{
                                        cout << "Nao tem dinhiro suficientes" << endl;
                                        break;
                                    }
                                }
                                else {//Caso não exista ficheiro de configuração
                                    (*(zonas + (vec[0] - 1) * col + (vec[1] - 1)))->constroiEdif(sComando,edificios, 0);
                                }
                            }
                            else
                                cout << "Nao tem recursos suficientes" << endl;
                        }
                        else{

                            auto it = custoConfig.find(sComando);
                            int custo = 0;
                            if(it != custoConfig.end())
                                custo = it->second * mul;
                            if(dinheiro >= custo){
                                dinheiro -= custo;
                                (*(zonas + (vec[0] - 1) * col + (vec[1] - 1)))->constroiEdif(sComando,
                                                                                             edificios, custo);
                            }
                            else
                                cout << "Nao tem dinhiro e recursos suficientes" << endl;
                        }
                    }

                }
                else{
                    cout << "Ja existe um edificio" << endl;
                }
            }
            else
                cout << "Tentou aceder a uma area nao existente" << endl;
            break;
        case 3: //Comando liga
            if(validaTam(vec[0]-1,vec[1]-1) ) {
                if (!((*(zonas+(vec[0]-1)*col +(vec[1]-1)))->verificaEdificio())) //Adicionar recursos
                    (*(zonas+(vec[0]-1)*col +(vec[1]-1)))->liga();
                else
                    cout << "Ainda nao existe edificio" << endl;
            }
            else
                cout << "Tentou aceder a uma area nao existente" << endl;
            break;
        case 4://Desliga
            if(validaTam(vec[0]-1,vec[1]-1) ) {
                if (!((*(zonas+(vec[0]-1)*col +(vec[1]-1)))->verificaEdificio())) //Adicionar recursos
                    (*(zonas+(vec[0]-1)*col +(vec[1]-1)))->desliga();
                else
                    cout << "Ainda nao existe edificio" << endl;
            }
            else
                cout << "Tentou aceder a uma area nao existente" << endl;
            break;
        case 5: //move trabalhador

            if(validaTam(vec[0]-1,vec[1]-1) ){
                //Procura trabalhador
                Trabalhador* t1;
                for(int i = 0; i < lin*col; ++i){
                    t1 = zonas[i]->searchTrab(sComando, true);
                    if(t1 != nullptr){
                        (*(zonas+(vec[0]-1)*col +(vec[1]-1)))->addTrablhador(t1);
                        break;
                    }

                }
                if(t1 == nullptr)
                    cout << "Ja movimentou este trabalhador ou nao existe trabalhador com esse id" << endl;
            }
            break;

        case 6: //vende tipo
            if(verificaVendeRecurso(sComando, vec[0])){
                //retira recursos
                retiraRec(sComando, vec[0]);
            }
            else
                cout << "Nao existe essa quantidade de recurso" << endl;
            break;
        case 7: {// Comando cont
            auto custo = custoConfig.find(sComando);
            if(custo != custoConfig.end()){
                if(dinheiro >= custo->second){
                    contrataTrab(sComando); //Adicionar recursos
                    dinheiro -= custo->second;
                }
                else{
                    cout << "Nao tem dinheiro suficiente" << endl;
                }
            }
            else { //Assume-se o valor 0
                contrataTrab(sComando); //Adicionar recursos
            }

            break;
        }
        case 8: //Comando list com celulas

            if(validaTam(vec[0]-1,vec[1]-1))
                cout << (*(zonas+(vec[0]-1)*col +(vec[1]-1)))->showInformation(vec[0],vec[1]) << endl;
            else
                cout << "Tentou aceder a uma zona nao permitida" << endl;
            break;
        case 9: //vende edificio linha coluna

            if(validaTam(vec[0]-1,vec[1]-1))
                if(!(*(zonas+(vec[0]-1)*col +(vec[1]-1)))->verificaEdificio()){
                    (*(zonas+(vec[0]-1)*col +(vec[1]-1)))->vendeEdif(&dinheiro);
                }
                else {
                    cout << "Nao existe edificio" << endl;
                }
            else
                cout << "Tentou aceder a uma area nao existente" << endl;
            break;
        case 10: //next
            avancaFase();
            break;
        case 14: //Comando ficheiro de configuracao
            if(!custoConfig.empty()){
                reconfig(sComando);
                //Atualizar custos
            }
            break;
        case 15://debcash
            if((dinheiro + vec[0]) < 0)
                break;
            dinheiro += vec[0];

            break;
        case 16: //debed
            if(validaTam(vec[0]-1,vec[1]-1) ) {
                if ((*(zonas + (vec[0] - 1) * col + (vec[1] - 1)))->verificaEdificio()) { //Adicionar edificio
                    (*(zonas + (vec[0] - 1) * col + (vec[1] - 1)))->constroiEdif(sComando,edificios, 0);
                }
            }
            break;
        case 17://debkill

                //Procura trabalhador
            Trabalhador *t1;
            for (int i = 0; i < lin * col; ++i) {
                t1 = zonas[i]->searchTrab(sComando);
                if (t1 != nullptr){
                    cout << t1->getTipo() << " apagado" << endl ;
                    delete t1;
                    break;
                }
            }

            break;
        case 18: //Comando list
            for (int i = 0; i < lin ; i++){
                for (int j = 0; j < col; ++j) {
                    cout << (*(zonas+i*col +j))->showInformation(i+1, j+1) << endl;
                }
            }
            if(!custoConfig.empty())
                cout << imprimeCustos() << endl;
            break;
        case 19: //Comando exit
            return -1;
        case 20:
            if(validaTam(vec[0]-1,vec[1]-1) ) {
                if(!(*(zonas + (vec[0] - 1) * col + (vec[1] - 1)))->verificaEdificio()){
                    if(!(*(zonas + (vec[0] - 1) * col + (vec[1] - 1)))->podeSubirNivel()){
                        cout << "Nao e possivel subir nivel" << endl;
                        break;
                    }
                    auto it = custoPNivel.find((*(zonas + (vec[0] - 1) * col + (vec[1] - 1)))->showEdificio());
                    if(it == custoPNivel.end())
                        dinheiro -= (*(zonas + (vec[0] - 1) * col + (vec[1] - 1)))->sobeNivel(dinheiro);
                    else{
                        for (auto i: rec) {
                            if(i->getsigla() == it->second.first && i->getQuantidade() >= it->second.second &&
                            dinheiro >= (*(zonas + (vec[0] - 1) * col + (vec[1] - 1)))->getcustoNivel()){
                                i->setQuantidade(-it->second.second);
                                retiraRec(it->second.first, it->second.second);
                                dinheiro -= (*(zonas + (vec[0] - 1) * col + (vec[1] - 1)))->sobeNivel(dinheiro);
                            }
                            else if(i->getsigla() == it->second.first && i->getQuantidade() >= it->second.second)
                                cout << "Nao existe dinheiro suficiente" << endl;

                            else if(i->getsigla() == it->second.first && dinheiro >= (*(zonas + (vec[0] - 1) * col + (vec[1] - 1)))->getcustoNivel()){
                                cout << "Nao existe recursos suficiente" << endl;
                            }

                        }
                    }
                }
                else
                    cout << "Nao existe edificio" << endl;
            }
            else
                cout << "Tentou aceder a uma zona nao existente" << endl;
            break;
        case 22:
            if(validaTam(vec[1]-1,vec[2]-1) ) {
                addRecurso(sComando, vec);
            }
            else
                cout << "Tentou aceder a uma zona nao existente" << endl;
            break;
    }
    return 0;
}


string Ilha::imprimeCustos() const {
    ostringstream oss;
    oss << "Nome" << "/Custo" << endl;

    for (auto it = custoConfig.begin(); it != custoConfig.end(); ++it) {
        oss << it->first << "  " << it->second << endl;
    }
    return oss.str();
}

void Ilha::reconfig(string fich) { //Comando config, atualiza ou adiciona novos custos
    ifstream fin;
    istringstream iss;
    fin.open(fich);
    string aux, linha;
    int custo;

    map<string, int>::iterator it;

    if(fin.fail()){
        cout << "Erro na abertura do ficheiro de configuração" << endl;
        return;
    }

    while(!fin.eof() && !fin.fail()){
        getline(fin, linha);
        iss.str(linha);
        iss.clear();
        iss >> aux;
        iss >> custo;
        if (iss.fail())
            break;
        else {
            for (it = custoConfig.begin(); it != custoConfig.end(); ++it) {
                if (aux == it->first)
                    it->second = custo;
            }
        }
        aux = "";
    }

    fin.close();

}

void Ilha::contrataTrab(string sComando) {
    string aux = sComando;
    int custo = -1;
    auto it = this->custoConfig.begin();
    for( ;it != custoConfig.end(); it++){
        if(it->first == aux){
            custo = it->second;
            break;
        }
    }

    if(custo == -1)
        return;


    if(custo > dinheiro){
        cout << "Nao tem dinheiro suficiente" << endl;
        return;
    }

    int x;
    randomPast(x);
    if(aux == trabalhadores[0])
        zonas[x]->contrataOper(aux, dia);
    else if(aux == trabalhadores[1])
        zonas[x]->contrataLen(aux, dia);
    else
        zonas[x]->contrataMiner(aux, dia);

 }

void Ilha::avancaFase() {

    ++faseDoDia;
    cout << endl << "Anoitecer!" << endl;
    //Recolha dos recurso
    //impressao dos recursos obtidos
    Recurso *x;

    for (auto it:rec) {
        it->setQuantidade(-it->getQuantidade());
    }

    for (int i = 0; i < lin*col; ++i) {
        x =zonas[i]->produz();
        if(x == nullptr)
            continue;
        for (int j = 0; j < rec.size(); ++j) {
            if(rec[j]->operator==(*x))
                (*rec[j]).operator+=(*x);
        }
        delete x;
    }


    for(int i = 0 ; i <lin*col; ++i){
        if(!zonas[i]->verificaEdificio()){
            if(zonas[i]->showEdificio() != "bat" && zonas[i]->showEdificio()!= "fun"){
                x = zonas[i]->produzEdif();
                if(x != nullptr){
                    for (int j = 0; j < rec.size(); ++j) {
                        if(rec[j]->operator==(*x))
                            (*rec[j]).operator+=(*x);

                    }
                    delete x;
                }
            }
        }
    }

    for(int i = 0 ; i <lin*col; ++i){
        if(!zonas[i]->verificaEdificio()){
            if(zonas[i]->showEdificio() == "bat" || zonas[i]->showEdificio() == "fun"){
                x = zonas[i]->produzEdif();
                if(x != nullptr){
                    for (int j = 0; j < rec.size(); ++j) {
                        if(rec[j]->operator==(*x))
                            (*rec[j]).operator+=(*x);

                    }
                    delete x;
                }
            }
        }
    }



/*     *  Dia de simulação e riqueza acumulada */
    cout << "Dia de Simulacao: " << dia << endl << endl;
    cout << "Riqueza Acumulada :" << endl;
    for(auto it : rec){
        cout << it->getsigla() << " produzido:  " << it->getQuantidade() << endl;
    }
    cout << endl;
    cout << getRecursos() << endl; // Quantidade de recursos e lista de quais existem
    cout << getTrab() << endl; //Quantidade de trabalhadores e lista de quais existem

    dia++;
    faseDoDia = 1;
    cout << "Amanhecer!" << endl;
    //efeitos das zonas

    for(int i = 0 ; i <lin*col; ++i){ //Efeitos das zonas e edificios de desabamento
        zonas[i]->efeitosZonas();
        zonas[i]->efeitosEdif();
        zonas[i]->verificaDemissoes(dia);

    }

    ++faseDoDia;

}



string Ilha::getRecursos() const {
    ostringstream oss;
    const Recurso *x , *y;

    for (auto it:rec) {
        it->setQuantidade(-it->getQuantidade());
    }

    for (int i = 0; i < lin*col; ++i) {
        x = zonas[i]->getRecurso();
        y = zonas[i]->getRecursoEdif();
        if(x != nullptr){
            for (int j = 0; j < rec.size(); ++j) {
                if(rec[j]->operator==(*x))
                    (*rec[j]).operator+=(*x);
            }
        }
        if(y != nullptr){
            for (int j = 0; j < rec.size(); ++j) {
                if (rec[j]->operator==(*y))
                    (*rec[j]).operator+=(*y);
            }
        }
    }

    for (auto it : rec) {
        oss << it->toString() << endl;
    }

    return oss.str();
}

string Ilha::getTrab()const {

    ostringstream oss;

    int len = 0, min = 0, op = 0;
    for (int i = 0; i < lin*col; ++i) {
        len += zonas[i]->qtdLenhadores();
        min += zonas[i]->qtdMineiros();
        op += zonas[i]->qtdOper();
    }

    oss << "Trabalhadores: " << (len+min+op) << endl;
    oss << len << " lenhadores | " << min << " mineiros | " << op << " operarios" << endl;

    return oss.str();
}

bool Ilha::verificaVendeRecurso(string nRec, double qtd) {
    for (auto it: rec) {
        if(it->getsigla() == nRec){
            if(it->getQuantidade() >= qtd){
                it->setQuantidade(-qtd);
                dinheiro +=(qtd * it->getPreco());
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}

void Ilha::retiraRec(string nrec, double qtd) {

    //Primeiro damos preferencia a retirar aos edificios
    for (int i = 0; i < lin*col; ++i) {
        qtd -= zonas[i]->retiraRecurso(nrec,qtd);
        if(qtd == 0.0){
            return;
        }
    }

    for (int i = 0; i < lin*col; ++i) {
        qtd -= zonas[i]->retiraRecursoPorTodasZonas(nrec, qtd);
        if(qtd == 0)
            return;
    }

}

int Ilha::verificaCustoRecurso(string sComando, int mul) {

     map <string, pair<string, int>>::iterator it;
     int q = 0;
     it = custoEdifRec.find(sComando);
     if(it != custoEdifRec.end()) {
         for(auto i:rec){
             if(i->getsigla()== it->second.first){
                 if(i->getQuantidade() >= (it->second.second * mul)){
                     i->setQuantidade(-it->second.second);
                     return 0;
                 }
                 else{
                     q = (it->second.second * mul) - (int)i->getQuantidade();
                     i->setQuantidade(-(int)i->getQuantidade());
                     return q;
                 }
             }
         }
         return it->second.second * mul;
     }


     return 0;
}

string Ilha::getName()const{
    return name;
}

void Ilha::setName(string n) {
    name = n;
}

int Ilha::getLin()const{
    return lin;
}

int Ilha::getCol() const {
    return col;
}

Ilha& Ilha::operator=(const Ilha& outro) {

    if(this == &outro)
        return *this;

    if(zonas!= nullptr){
        for (int i = 0; i < lin*col; ++i) {
            delete zonas[i];
        }

        delete []zonas;
    }


    //corrigir
    dinheiro = outro.dinheiro;
    lin = outro.lin;
    col = outro.col;
    dia = outro.dia;
    faseDoDia = outro.faseDoDia;
    custoConfig = outro.custoConfig;
    custoEdifRec = outro.custoEdifRec;
    custoPNivel = outro.custoPNivel;
    indicesPasto = outro.indicesPasto;
    pontuacao = outro.pontuacao;

    zonas = new Zona*[(lin*col)];
    for (int i = 0; i < (outro.lin*outro.col); ++i) {
        zonas[i] = zonas[i]->constroiZonaByString(outro.zonas[i]->showNome());
        zonas[i]->operator=(*outro.zonas[i]);
    }

    compoeZonasAdjacentes();


    return *this;
}

Ilha::~Ilha() {
    for (int i = 0; i < lin*col; ++i) {
        delete zonas[i];
    }

    delete []zonas;

    vector<Recurso*>::iterator it = rec.begin();
    for (; it < rec.end() ;++it ) {
        delete *it;
    }
    rec.clear();

}

string Ilha::showDetails() const{
    ostringstream oss;
    if(name.length() != 0){
        oss << "Nome : " << name << " | ";
    }
    oss<< "Dia: " << dia << " | Dinheiro: " << dinheiro << " | Pontuacao: " << pontuacao;
    return oss.str();
}

int Ilha::verificaCustoTotalRecurso(string sComando, int numRec) {

    vector<Recurso*>::iterator it;
    it = rec.begin();

    for (; it < rec.end(); ++it) {
        if((*it)->getsigla() == sComando){
            if((*it)->getQuantidade() >= numRec)
                return 0;
            else
                return 1;
        }
    }

    return 1;

}

void Ilha::addRecurso(string nrec, int v[])const {

    int i = (v[1] - 1)*col+(v[2] - 1);
    cout << zonas[i]->addRecurso(nrec, v[0]) << endl;

}

bool Ilha::verificaGameOver() {
    int pont = 0;
    pontuacao = 0;
    int custolen, custoOper, custoMiner;

    auto jt = custoConfig.find(trabalhadores[0]);
    custoOper = jt->second;
    jt = custoConfig.find(trabalhadores[1]);
    custolen = jt->second;
    jt = custoConfig.find(trabalhadores[2]);
    custoMiner = jt->second;
    vector<Recurso*>::iterator it;

    for (auto it: rec) {
        pont += it->getQuantidade();
        pontuacao += (it->getQuantidade() * it->getPreco());
    }
    for(int i = 0; i < lin*col; i++){
        pont += zonas[i]->contatrabalhadores();
        pontuacao += (custoOper * zonas[i]->qtdOper()) + (custolen * zonas[i]->qtdLenhadores()) + (custoMiner * zonas[i]->qtdMineiros());
    }
    pont += dinheiro;
    pontuacao += dinheiro;
    if(pont == 0)
        return true;

    return false;
}

void Ilha::configMaps() {
    rec.push_back(new Ferro(tipodeMaterial[0]));
    rec.push_back(new BarradeAco(tipodeMaterial[1]));
    rec.push_back(new Carvao(tipodeMaterial[2]));
    rec.push_back(new Madeira(tipodeMaterial[3]));
    rec.push_back(new Viga(tipodeMaterial[4]));
    rec.push_back(new Eletricidade(tipodeMaterial[5]));

    custoEdifRec[edificios[1]] = make_pair(tipodeMaterial[1], 5);
    custoEdifRec[edificios[4]] = make_pair(tipodeMaterial[4], 10);
    custoEdifRec[edificios[5]] = make_pair(tipodeMaterial[4], 10);

    custoTotalEdifRec[edificios[2]] = make_pair(tipodeMaterial[4], 10);


    custoPNivel[edificios[1]] = make_pair(tipodeMaterial[1], 1);
    custoPNivel[edificios[4]] = make_pair(tipodeMaterial[4], 1);
    custoPNivel[edificios[5]] = make_pair(tipodeMaterial[4], 1);

    custoConfig[edificios[0]] = 10;
    custoConfig[edificios[1]] = 10;
    custoConfig[edificios[2]] = 10;
    custoConfig[edificios[3]] = 15;
    custoConfig[edificios[4]] = 10;
    custoConfig[edificios[5]] = 10;
    custoConfig[edificios[6]] = 20;
    custoConfig[trabalhadores[0]] = 15;
    custoConfig[trabalhadores[1]] = 20;
    custoConfig[trabalhadores[2]] = 10;
}



