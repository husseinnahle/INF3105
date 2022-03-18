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
#include "date.h"
#include "epicerie.h"
#include "pointst.h"
#include "produit.h"
#include "commande.h"

using namespace std;

int main(int argc, const char** argv)
{
  Commande c;
  Tableau <std::string> e;
  c.traiter("RAMASSER Chocolat 2 Lait 3 Pommes 3 ; IGA ;", e);
  for (int i = 0; i < e.taille(); i++)
  {
    std::cout << e[i] << std::endl;
  }

  return 0;
}

