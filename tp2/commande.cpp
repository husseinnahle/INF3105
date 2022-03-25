/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/

#include "commande.h"

std::string Commande::traiter(const std::string& raw_commande)
{
  Tableau<std::string> commande;
  traiter(raw_commande, commande);
  // for (int i = 0; i < commande.taille(); i++)
  // {
  //   std::cout << commande[i] << std::endl;
  // }
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
  for (int i = 0; i < raw_commande.length(); i++)
  {
    if (raw_commande[i] == ' ')
    {
      if (element.length() == 0)
      {
        continue;
      }
      commande.ajouter(element);
      element = "";
      continue;
    }
    else if (raw_commande[i] == ';' && i == raw_commande.length()-1)
    {
      if (element.length() != 0)
      {
        commande.ajouter(element);
      }
      if (i != raw_commande.length()-1)
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
    Produit produit(nom_produit, date);
    carte.approvisionner(nom_epicerie, produit, quantite);
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
  carte.recommander(position, nombre_max_epicerie, distance_total_max, produits);
  return "";
}

// // RAMASSER Fraises 2; Foudici IGA;
// std::string Commande::ramasser(const Tableau<std::string>& commande)
// {
//   std::string reponse = "";
//   bool complet = true;
//   int index_separateur = commande.chercher(";");
//   for (int j = index_separateur+1; j < commande.taille(); j++)
//   {
//     reponse += j != commande.taille() -1 ? "\n" : "";
//     std::string nom_epicerie = commande[j];
//     for (int i = 1; i < index_separateur; i+=2)
//     {
//       reponse += i > 1 ? "\n" : "";
//       int quantite_non_trouvee = carte.ramasser(nom_epicerie, commande[i], std::stoi(commande[i+1]));
//       if (quantite_non_trouvee != 0)
//       {
//         reponse += "MANQUE " + commande[i] + " " + std::to_string(quantite_non_trouvee) + ";";
//         complet = false;
//         continue;
//       }
//     }  
//     reponse += complet == true ? "COMPLET" : "";
//   }
//   return reponse;
// }

// RAMASSER Fraises 2; Foudici IGA;
std::string Commande::ramasser(Tableau<std::string>& commande)
{
  std::string reponse = "";
  int index_separateur = commande.chercher(";");
  for (int i = index_separateur+1; i < commande.taille(); i++)
  {
    std::string nom_epicerie = commande[i];
    for (int j = 1; j < index_separateur; j+=2)
    {
      std::string nom_produit = commande[j];
      int quantite = std::stoi(commande[j+1]);
      carte.ramasser(nom_epicerie, nom_produit, quantite);
      commande[j+1] = std::to_string(quantite);
    }
  }
  for (int j = 1; j < index_separateur; j+=2)
  {
    std::string nom_produit = commande[j];
    int quantite = std::stoi(commande[j+1]);
    if (quantite != 0)
    {
      reponse += "MANQUE " + nom_produit + " " + std::to_string(quantite) + ";";
      reponse += j+2 == index_separateur ? "" : "\n";
    }    
  }
  reponse += reponse == "" ? "COMPLET" : "";
  return reponse;
}

std::string Commande::afficher_inventaire(const Tableau<std::string>& commande)
{
  Tableau<Produit> produits = carte.get_produits(commande[1]);
  ArbreMap<std::string, int> map;
  for (int i = 0; i < produits.taille(); i++)
  {
    std::string produit = produits[i].get_nom();
    if (map.contient(produit))
    {
      map[produit] += 1;
      continue;
    }
    map[produit] = 1;    
  }  
  ArbreMap<std::string, int>::Iterateur iter = map.debut();
  while (iter)
  {
    std::cout << iter.cle() << " " << iter.valeur() << "     ";
    ++iter;
  }  
  return ";";
}
