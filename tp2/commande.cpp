/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/

#include <sstream>
#include <string>

#include "arbremap.h"
#include "commande.h"
#include "tableau.h"
#include "epicerie.h"
#include "produit.h"
#include "date.h"
#include "pointst.h"

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
    if (c == ' ' || c == ';')
    {
      if (element.length() == 0)
      {
        continue;
      }      
      commande.ajouter(element);
      element = "";
      continue;
    }
    else if (c == ':' || c == '\n' || c == '\\')
    {
      continue;
    }
    element += c;
  }
}

Date Commande::str_to_date(const std::string& raw_date)
{
  Date date;
  std::istringstream is(raw_date);
  is >> date;
  return date;
}

PointST Commande::str_to_pointst(const std::string& raw_position)
{
  PointST position;
  std::istringstream is(raw_position);
  is >> position;
  return position;
}

std::string Commande::set_date(const Tableau<std::string>& commande)
{
  Date date = str_to_date(commande[1]);
  carte.set_date_actuelle(date);
  return "OK";
}

std::string Commande::placer(const Tableau<std::string>& commande)
{
  PointST position = str_to_pointst(commande[2]);
  Epicerie epicerie(commande[1], position);
  carte.placer_epicerie(epicerie);
  return "OK";
}

std::string Commande::approvisionner(const Tableau<std::string>& commande)
{
  std::string nom_epicerie = commande[1];
  for (int i = 2; i+2 < commande.taille(); i+=3)
  {
    std::string nom_produit = commande[i];
    int quantite = stoi(commande[i+1]);
    Date date = str_to_date(commande[i+2]);
    Produit produit(nom_produit, date);
    carte.approvisionner(nom_epicerie, produit, quantite);
  }
  return "OK";
}

std::string Commande::recommander(const Tableau<std::string>& commande)
{
  return "";
}

std::string Commande::ramasser(const Tableau<std::string>& commande)
{
  return "";
}

std::string Commande::afficher_inventaire(const Tableau<std::string>& commande)
{
  ArbreMap<Produit, int>::Iterateur iter = carte.inventaire_iter(commande[1]);
  ArbreMap<std::string, int> inventaire;
  while (iter)
  {
    std::string nom = iter.cle().get_nom();
    if (inventaire.contient(nom))
    {
      inventaire[nom] += iter.valeur();
      ++iter;
      continue;
    }
    inventaire[iter.cle().get_nom()] = iter.valeur();
    ++iter;    
  }
  ArbreMap<std::string, int>::Iterateur iter_inventaire = inventaire.debut();
  while (iter_inventaire)
  {
    std::cout << iter_inventaire.cle() << " " << iter_inventaire.valeur() << "     ";
    ++iter_inventaire;
  }  
  return ";";
}
