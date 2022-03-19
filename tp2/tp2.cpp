/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Hiver 2022 | TP2

    AUTEUR(S):
     1) Nom + Code permanent du l'étudiant.e 1
     2) Nom + Code permanent du l'étudiant.e 2
*/
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <limits>
// #include "date.h"
// #include "epicerie.h"
// #include "pointst.h"
// #include "produit.h"
// #include "commande.h"
#include <sstream>
#include "arbremap.h"

using namespace std;

int main(int argc, const char** argv)
{
    ArbreMap<int, int> map1;
    map1[1] = 10;
    map1[2] = 20;
    map1[3] = 30;

    map1[1] = 40;
    std::cout << map1.rechercher(2).valeur() << std::endl;


  return 0;
}

