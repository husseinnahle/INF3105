/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/

#include "commande.h"
#include "tableau.h"

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
    assert(commande.taille() == 2);
    return ramasser(commande);
  }
  else if (commande[0] == "INVENTAIRE")
  {
    assert(commande.taille() == 2);
    return afficher_inventaire(commande);
  }
  return "Commande non trouvée";
}
