/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Hiver 2022 | TP2

    AUTEUR(S):
     1) Nom + Code permanent du l'étudiant.e 1
     2) Nom + Code permanent du l'étudiant.e 2
*/

#include <iostream>
#include <string>

#include "commande.h"

int main(int argc, const char** argv)
{
  Commande c;
  std::cout << c.traiter("PLACER Foudici (45.506873,-73.568921) ;") << std::endl;
  std::cout << c.traiter("APPROV Foudici : Bleuets 4 2017-11-01 Lait 4 2017-11-01 Pain 3 2017-11-01;") << std::endl;
  std::cout << c.traiter("INVENTAIRE Foudici;") << std::endl;
  std::cout << c.traiter("APPROV Foudici : Bleuets 3 2017-11-01 Fraises 3 2017-10-30 ;") << std::endl;
  std::cout << c.traiter("INVENTAIRE Foudici;") << std::endl;
  return 0;
}
