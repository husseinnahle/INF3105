/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Hiver 2022 | TP2

    AUTEURS:
     1) Hussein Nahle - NAHH85090004
     2) Ridley Saint-Orice - SAIR77090109
*/
#include <fstream>
#include <iostream>
#include <string>
#include "commande.h"

int run(std::istream &entree)
{
  Commande commande;
  std::string ligne = "";
  while (std::getline(entree, ligne))
  {
    std::cout << commande.traiter(ligne) << std::endl;
  }
  return 0;
}

// syntaxe d'appel : ./tp2 [nomfichier.txt]
int main(int argc, const char **argv)
{
  // Gestion de l'entrée :
  //  - lecture depuis un fichier si un argument est spécifié;
  //  - sinon, lecture depuis std::cin.
  // argc=2;
  // argv[1] ="./tests/testE1.txt";
  if (argc > 1)
  {
    std::ifstream entree_fichier(argv[1]);
    if (entree_fichier.fail())
    {
      std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
      return 1;
    }
    return run(entree_fichier);
  }
  return run(std::cin);
}
