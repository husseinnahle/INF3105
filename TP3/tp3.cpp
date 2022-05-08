/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Hiver 2022 | TP3
    Auteur: Hussein Nahle
*/

#include <math.h>
#include <fstream>
#include <iostream>
#include "carte.h"

using namespace std;

int run(Carte &carte, istream &is) {
  while (is) 
  {
    string lieux = "";
    string routes = "";
    double distance = 0;
    string origine;
    vector<string> destinations;
    char sep;
    is >> origine >> sep;
    if (origine == "")
    {
      return 0;
    }
    while (is)
    {
      string destination;
      is >> destination;
      if (destination == ";")
      {
        break;
      }
      destinations.push_back(destination);
    }
    distance = carte.chercher_chemin(origine, destinations, lieux, routes);
    cout << lieux << origine << endl;
    cout << routes << endl;
    cout << round(distance) << " m" << endl;
  }
  return 0;
}

int main(int argc, const char **argv) {
  if (argc < 2)
  {
    cout << "Usage : ./tp3 carte.txt [mission.txt]" << endl;
    return 1;
  }

  ifstream fichier_carte(argv[1]);
  if (fichier_carte.fail())
  {
    cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
    return 1;
  }
  // Initialiser la carte
  Carte carte;
  fichier_carte >> carte;

  if (argc > 2)
  {
    ifstream fichier_mission(argv[2]);
    if (fichier_mission.fail())
    {
      cerr << "Erreur d'ouverture du fichier '" << argv[2] << "'" << std::endl;
      return 1;
    }
    return run(carte, fichier_mission);
  }
  return run(carte, cin);
}
