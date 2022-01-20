//
// Created by Daniel Fernandes on 16/12/2021.
//

#ifndef POO_TP1_UTILS_H
#define POO_TP1_UTILS_H
#define TAMCOMANDS 22
#define TAMTRABALHADOR 3
#define TAMSTRINGS 6
#define TAMEDIFS 7
#define TAMMINLIN 3
#define TAMMINCOL 3
#define TAMMAXLIN 8
#define TAMMAXCOL 16
#include <iostream>

using namespace std;

double uniforme01();

double r_uniforme01();

const string tipozonas[TAMSTRINGS]{"dsr", "mnt", "pas", "flr", "pnt", "znx"};
const string edificios[TAMEDIFS]{"fun","edx","bat","elec","mnc","mnf","ser"};
const string tipodeMaterial[TAMSTRINGS]{"ferro", "aco","carvao","madeira","viga", "elet"};
const string trabalhadores[TAMTRABALHADOR]{"oper","len","miner"};


#endif //POO_TP1_UTILS_H
