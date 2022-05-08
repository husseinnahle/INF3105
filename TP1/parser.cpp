#include "parser.h"

Parser::Parser(const std::string& fichier)
{
  nom_fichier = fichier;
}

void Parser::lire()
{
  std::string ligne;
  std::ifstream fichier(nom_fichier);
  if(fichier.fail())
  {
    throw std::ifstream::failure("Lecture du fichier '" + nom_fichier + "'");
  }
  while (getline(fichier, ligne))
  {
    entrees.ajouter(ligne);
  }
  if (entrees.taille() > 0)
  {
    try
    {
      nombre_stations = std::stoi(entrees[0]);
    }
    catch(const std::invalid_argument& exception)
    {
      std::cerr << "Le format du fichier '" + nom_fichier + "' est incorrect.\n";
      throw exception;
    }
    entrees.enlever(0);
  }
}

void Parser::stations(Tableau<Station>& stations)
{
  for (int i = 0; i < nombre_stations && i < entrees.taille(); i++)
  {
    if (entrees[i].empty())
    {
      continue;
    }
    Station station;
    entrees[i] >> station;
    stations.ajouter(station);
  }
}

void Parser::immeubles(Tableau<Immeuble>& immeubles)
{
  for (int i = nombre_stations; i < entrees.taille(); i++)
  {
    if (entrees[i].empty())
    {
      continue;
    }
    Immeuble immeuble;
    entrees[i] >> immeuble;
    immeubles.ajouter(immeuble);
  }
}
