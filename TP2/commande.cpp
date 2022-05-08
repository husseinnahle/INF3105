#include "commande.h"

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
  else if (commande[0] == "RAMASSER")
  {   
    assert(commande.taille() > 4);
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
     commande = ["PLACER", "Foudici", "(45.506873,-73.568921)"]
*/
void Commande::traiter(const std::string& raw_commande, Tableau<std::string>& commande)
{
  std::string element = "";
  for (int i = 0; i < (int)raw_commande.length(); i++)
  {
    if (raw_commande[i] == ' ' || raw_commande[i] == '\t')
    {
      if (element.length() == 0)
      {
        continue;
      }
      commande.ajouter(element);
      element = "";
      continue;
    }
    else if (raw_commande[i] == ';' && i == (int)raw_commande.length()-1)
    {
      if (element.length() != 0)
      {
        commande.ajouter(element);
      }
      if (i != (int)raw_commande.length()-1)
      {
        commande.ajouter(";");
      }
      continue;
    }
    else if (raw_commande[i] == ':' || raw_commande[i] == '\n' || raw_commande[i] == '\\')
    {
      continue;
    }
    element += raw_commande[i];
  }
}

// String to Date
Date Commande::str_to_date(const std::string& raw_date)
{
  Date date;
  std::istringstream is(raw_date);
  is >> date;
  return date;
}

// String to PointST
PointST Commande::str_to_pointst(const std::string& raw_position)
{
  PointST position;
  std::istringstream is(raw_position);
  is >> position;
  return position;
}

// Changer la date courante
std::string Commande::set_date(const Tableau<std::string>& commande)
{
  Date date = str_to_date(commande[1]);
  carte.enlever_produits_expires(date);
  return "OK";
}

std::string Commande::placer(const Tableau<std::string>& commande)
{
  PointST position = str_to_pointst(commande[2]);
  Epicerie epicerie(commande[1], position);
  carte.ajouter_epicerie(epicerie);
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
    carte.approvisionner(nom_epicerie, nom_produit, date, quantite);
  }
  return "OK";
}

std::string Commande::recommander(const Tableau<std::string>& commande)
{
  PointST position = str_to_pointst(commande[1]);
  int nombre_max_epicerie = std::stoi(commande[2]);
  int distance_total_max = std::stoi(commande[3]);
  ArbreMap<std::string, int> produits;
  for (int i = 4; i+1 < commande.taille(); i+=2)
  {
    produits[commande[i]] = std::stoi(commande[i+1]);
  }
  return carte.recommander(position, nombre_max_epicerie, distance_total_max, produits);
}

std::string Commande::ramasser(Tableau<std::string>& commande)
{
  std::string reponse = "MANQUE ";
  int index_separateur = commande.chercher(";");
  ArbreMap<std::string, int> produits;
  for (int j = 1; j < index_separateur; j+=2)
  {
    std::string nom_produit = commande[j];
    int quantite = std::stoi(commande[j+1]);
    produits[nom_produit] = quantite;
  }
  bool complet = false;
  for (int i = index_separateur+1; i < commande.taille() && !complet; i++)
  {
    std::string nom_epicerie = commande[i];
    complet = carte.ramasser(nom_epicerie, produits);
  }
  ArbreMap<std::string, int>::Iterateur iter = produits.debut();
  while (iter)
  {
    reponse += iter.valeur() != 0 ? iter.cle() + " " + std::to_string(iter.valeur()) + "\t" : "";
    ++iter;
  }
  if (reponse == "MANQUE ")
  {
    return "COMPLET";
  }
  return reponse + ";";
}

std::string Commande::afficher_inventaire(const Tableau<std::string>& commande)
{
  return carte.get_inventaire(commande[1]) + ";";
}
