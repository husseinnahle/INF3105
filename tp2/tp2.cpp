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
  std::cout << c.traiter("DATE 2017-11-01 ;") << std::endl;
  std::cout << c.traiter("PLACER Foudici (45.506873,-73.568921) ;") << std::endl;
  std::cout << c.traiter("PLACER IGA (45.507798,-73.563369) ;") << std::endl;
  std::cout << c.traiter("APPROV Foudici : Pommes 4 2017-11-20 ;") << std::endl;
  std::cout << c.traiter("APPROV IGA : Pommes 3 2017-11-14 Fraises 3 2017-11-27 ;") << std::endl;
  std::cout << c.traiter("RAMASSER Pommes 2 Fraises 1 ; IGA Foudici ;") << std::endl;
  std::cout << c.traiter("INVENTAIRE IGA ;") << std::endl;
  // std::cout << c.traiter("INVENTAIRE Foudici ;") << std::endl;
  // std::cout << c.traiter("RAMASSER Pommes 1 Fraises 1 ; Foudici IGA ;") << std::endl;
  // std::cout << c.traiter("INVENTAIRE IGA ;") << std::endl;
  // std::cout << c.traiter("INVENTAIRE Foudici ;") << std::endl;

  // std::cout << c.traiter("RECOMMANDER (45.509339,-73.568465) 1 999000 : Fraises 1 ;") << std::endl;
  // std::cout << c.traiter("RECOMMANDER (45.509339,-73.568465) 1 999000 : Fraises 2 ;") << std::endl;
  // std::cout << c.traiter("RECOMMANDER (45.509339,-73.568465) 1 999000 : Fraises 1 Pommes 2 ;") << std::endl;
  // std::cout << c.traiter("RECOMMANDER (45.509339,-73.568465) 2 999000 : Fraises 1 Pommes 2 ;") << std::endl;

  return 0;
}
