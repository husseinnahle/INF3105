/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/

#include "commande.h"
#include "tableau.h"
#include <sstream>

/* Traiter le format de la commande (string --> Tableau<string>).
   exemple:
     raw_commande = "PLACER Foudici (45.506873,-73.568921) ;"
     commade = ["PLACER", "Foudici", "(45.506873,-73.568921)"]
*/
void Commande::traiter(const std::string& raw_commande, Tableau<std::string>& commande)
{
  std::string element = "";
  for (const char& c : raw_commande)
  {
    if (c == ' ')
    {
      if (element.length() == 0)
      {
        continue;
      }      
      commande.ajouter(element);
      element = "";
      continue;
    }
    else if (c == ';' || c == ':' || c == '\n')
    {
      continue;
    }
    element += c;
  }
}

std::string Commande::traiter(const std::string& raw_commande)
{
  Tableau<std::string> commande;
  traiter(raw_commande, commande);
  if (commande[0] == "DATE")
  {
    assert(commande.taille() == 2);
    return set_date(commande);
  }
  else if (commande[0] == "PLACER")
  {
    assert(commande.taille() == 3);
    return placer(commande);
  }
  else if (commande[0] == "APPROV")
  {
    assert((commande.taille() - 2) % 3 == 0);
    return approvisionner(commande);
  }
  else if (commande[0] == "RECOMMANDER")
  {
    assert((commande.taille() - 4) % 2 == 0);
    return recommander(commande);
  }
  else if (commande[0] == "RAMMASSER")
  {
    assert(commande.taille() > 1);
    return ramasser(commande);
  }
  else if (commande[0] == "INVENTAIRE")
  {
    assert(commande.taille() == 2);
    return afficher_inventaire(commande);
  }
  return "Commande non trouvée";
}

std::string Commande::set_date(const Tableau<std::string>& commande)
{
  Date date;
  std::istringstream is(commande[1]);
  is >> date;
  carte.set_date_actuelle(date);
  return "OK";
}

std::string Commande::placer(const Tableau<std::string>& commande)
{
  PointST position;
  std::istringstream is(commande[2]);
  is >> position;
  carte.placer_epicerie(Epicerie(commande[1], position));
  return "OK";
}

std::string Commande::approvisionner(const Tableau<std::string>& commande)
{
  for (int i = 0; i < count; i++)
  {
    /* code */
  }
  

  carte.approvisionner()
}