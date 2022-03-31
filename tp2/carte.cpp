#include "carte.h"

// Ajouter une épicerie
void Carte::ajouter_epicerie(const Epicerie epicerie)
{
  epiceries.inserer(epicerie);
}

// Enlever, pour chaque épicerie, les produits expirés
void Carte::enlever_produits_expires(const Date& date_courante)
{
  ArbreAVL<Epicerie>::Iterateur iter = epiceries.debut();
  while (iter)
  {  
    epiceries[iter].enlever_produits_expires(date_courante);
    ++iter;
  }
}

// Ajouter un produit dans l'inventaire d'une épicerie
void Carte::approvisionner(const std::string& nom_epicerie, const std::string& nom_produit, const Date& date, const int quantite)
{
  epiceries[epiceries.rechercher(Epicerie(nom_epicerie))].ajouter_produits(nom_produit, date, quantite);
}

// Ramasser des produits
bool Carte::ramasser(const std::string& nom_epicerie, ArbreMap<std::string, int>& produits)
{
  Epicerie* epicerie = &epiceries[epiceries.rechercher(Epicerie(nom_epicerie))];
  ArbreMap<std::string, int>::Iterateur iter = produits.debut();
  bool complet = true;
  while (iter)
  {
    epicerie->enlever_produits(iter.cle(), iter.valeur());
    if (iter.valeur() > 0)
    {
      complet = false;
    }
    ++iter;
  }
  return complet;
}

std::string Carte::get_inventaire(const std::string& nom_epicerie)
{
  return epiceries[epiceries.rechercher(Epicerie(nom_epicerie))].get_inventaire();
}

std::string Carte::recommander(const PointST& position, const int& nombre_max_epicerie, const int& distance_total_max, ArbreMap<std::string, int>& produits)
{
  // if (nombre_max_epicerie == 2)
  // {
  //   return recommander2(position, nombre_max_epicerie, distance_total_max, produits);
  // }
  // if (nombre_max_epicerie == 3)
  // {
  //   return recommander3(position, nombre_max_epicerie, distance_total_max, produits);
  // }
  
  ArbreMap<double, Epicerie*> epiceries_par_ordre;
  ranger_epiceries_par_ordre(epiceries_par_ordre, position, distance_total_max);
  ArbreMap<double, Epicerie*>::Iterateur iter_epiceries = epiceries_par_ordre.debut();
  while (iter_epiceries)
  {
    if (iter_epiceries.valeur()->contient_produits(produits))
    {
      double distance = 2 * position.distance(iter_epiceries.valeur()->get_position());
      if (distance > distance_total_max)
      {
        break;
      }
      return std::to_string((int)std::round(distance)) + "m " + iter_epiceries.valeur()->get_nom();
    }    
    ++iter_epiceries;
  }
  return "IMPOSSIBLE";
}

// CAS 2: Deux épiceries
std::string Carte::recommander2(const PointST& position, const int& nombre_max_epicerie, const int& distance_total_max, ArbreMap<std::string, int>& produits)
{
  ArbreMap<double, Epicerie*> epiceries_par_ordre;
  ranger_epiceries_par_ordre(epiceries_par_ordre, position, distance_total_max);

  Tableau<Epicerie*> tab(nombre_max_epicerie);

  double distance_total = 0.0;
  bool complet = false;
  ArbreMap<double, Epicerie*>::Iterateur iter_epiceries = epiceries_par_ordre.debut();
  while (iter_epiceries)
  {
    Epicerie* premiere = iter_epiceries.valeur();
    Epicerie* deuxieme = chercher_epicerier_proche(*premiere);
    if (deuxieme == nullptr)
    {
      ++iter_epiceries;
      break;
    }

    double temp_distance_total = 0;
    temp_distance_total += position.distance(premiere->get_position());
    temp_distance_total += premiere->get_position().distance(deuxieme->get_position());
    temp_distance_total += deuxieme->get_position().distance(position);

    ArbreMap<std::string, int>::Iterateur iter_produits = produits.debut();
    while (iter_produits)
    {
      int quantite = premiere->get_quantite(iter_produits.cle()) + deuxieme->get_quantite(iter_produits.cle());
      if (quantite < iter_produits.valeur())
      {
        complet= false;
        tab.vider();
        break;
      }
      complet = true;
      ++iter_produits;
    }
    if ((distance_total == 0 || temp_distance_total < distance_total) && complet)
    {
      distance_total = temp_distance_total;
      tab.vider();
      tab.ajouter(premiere); tab.ajouter(deuxieme);
    }

    ++iter_epiceries;
  }
  if (tab.taille() == 0)
  {
    return "IMPOSSIBLE";
  }
  std::string reponse = std::to_string((int)std::round(distance_total)) + "m ";
  for (int i = 0; i < tab.taille(); i++)
  {
    reponse += tab[i]->get_nom() + " ";
  }
  return reponse;
}

// CAS 3: Trois épiceries
std::string Carte::recommander3(const PointST& position, const int& nombre_max_epicerie, const int& distance_total_max, ArbreMap<std::string, int>& produits)
{
  ArbreMap<double, Epicerie*> epiceries_par_ordre;
  ranger_epiceries_par_ordre(epiceries_par_ordre, position, distance_total_max);

  Tableau<Epicerie*> tab(nombre_max_epicerie);

  double distance_total = 0.0;
  bool complet = false;
  ArbreMap<double, Epicerie*>::Iterateur iter_epiceries = epiceries_par_ordre.debut();
  while (iter_epiceries)
  {
    Epicerie* premiere = iter_epiceries.valeur();
    Epicerie* deuxieme = chercher_epicerier_proche(*premiere);
    Epicerie* troisieme = chercher_epicerier_proche(*deuxieme);
    if (deuxieme == nullptr || troisieme == nullptr)
    {
      ++iter_epiceries;
      break;
    }

    double temp_distance_total = position.distance(premiere->get_position());
    temp_distance_total += premiere->get_position().distance(deuxieme->get_position());
    temp_distance_total += deuxieme->get_position().distance(troisieme->get_position());
    temp_distance_total += troisieme->get_position().distance(position);

    if (temp_distance_total > distance_total_max)
    {
      ++iter_epiceries;
      continue;
    }

    ArbreMap<std::string, int>::Iterateur iter_produits = produits.debut();
    while (iter_produits)
    {
      int quantite = premiere->get_quantite(iter_produits.cle()) + deuxieme->get_quantite(iter_produits.cle()) + troisieme->get_quantite(iter_produits.cle());
      if (quantite < iter_produits.valeur())
      {
        complet= false;
        break;
      }
      complet = true;
      ++iter_produits;
    }
    if ((distance_total == 0 || temp_distance_total < distance_total) && complet)
    {
      distance_total = temp_distance_total;
      tab.vider();
      tab.ajouter(premiere); tab.ajouter(deuxieme); tab.ajouter(troisieme);
    }

    ++iter_epiceries;
  }
  if (tab.taille() == 0)
  {
    return "IMPOSSIBLE";
  }
  std::string reponse = std::to_string((int)std::round(distance_total)) + "m ";
  for (int i = 0; i < tab.taille(); i++)
  {
    reponse += tab[i]->get_nom() + " ";
  }
  return reponse;
}

Epicerie* Carte::chercher_epicerier_proche(const Epicerie& epicerie)
{
  ArbreMap<double, Epicerie*> epiceries_par_ordre;
  ArbreAVL<Epicerie>::Iterateur iter = epiceries.debut();
  while (iter)
  {
    if (epiceries[iter].get_nom() != epicerie.get_nom())
    {
      double distance = epicerie.get_position().distance(epiceries[iter].get_position());
      epiceries_par_ordre[distance] = &epiceries[iter];
    }
    ++iter;
  }
  if (epiceries_par_ordre.debut())
    return epiceries_par_ordre.debut().valeur();
  return nullptr;
}


// Ranger les épiceries par ordre du plus proche au plus éloigné de position
void Carte::ranger_epiceries_par_ordre(ArbreMap<double, Epicerie*>& epiceries_par_ordre, const PointST& position, const int& distance_max)
{
  ArbreAVL<Epicerie>::Iterateur iter = epiceries.debut();
  while (iter)
  {
    double distance = position.distance(epiceries[iter].get_position());
    if (2*distance <= distance_max)
    {
      epiceries_par_ordre[distance] = &epiceries[iter];
    }
    ++iter;
  }
}
