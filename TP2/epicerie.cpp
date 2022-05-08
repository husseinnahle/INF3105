#include "epicerie.h"

// Ajouter n produit
void Info::ajouter(const Date& date, const int& quantite)
{
  this->quantite += quantite;
  if (info.contient(date))
  {
    info[date] += quantite;
    return;
  }
  info[date] = quantite;
}

// Enlever n produit
void Info::enlever(int& quantite)
{
  ArbreMap<Date, int>::Iterateur iter = info.debut();
  while (iter && quantite > 0)
  {
    if (quantite <= iter.valeur())
    {
      info[iter.cle()] -= quantite;
      this->quantite -= quantite;
      quantite = 0;
      return;
    }
    quantite -= iter.valeur();
    this->quantite -= iter.valeur();
    info[iter.cle()] = 0;
    ++iter;
  }
}

// Enlever les produits avec des dates expirées
void Info::enlever_dates_expires(const Date& date_courante)
{
  ArbreMap<Date, int>::Iterateur iter = info.rechercherEgalOuSuivant(date_courante);
  while (iter)
  {
    quantite -= iter.valeur();
    info[iter.cle()] = 0;
    ++iter;
  }
}

// ----------------------------------------------------------------------------- //

Epicerie::Epicerie(const std::string& nom)
{
  this->nom = nom;
}

Epicerie::Epicerie(const std::string& nom, const PointST& position)
{
  this->nom = nom;
  this->position = position;
}

std::string Epicerie::get_inventaire()
{  
  ArbreMap<std::string, Info>::Iterateur iter = inventaire.debut();
  std::string inventaire_str = "";
  while (iter)
  {
    inventaire_str += iter.valeur().get_quantite() != 0 
                    ? iter.cle() + " " + std::to_string(iter.valeur().get_quantite()) + "\t" 
                    : "";
    ++iter;
  }
  return inventaire_str;
}

// Ajouter n produits
void Epicerie::ajouter_produits(const std::string& nom_produit, const Date& date, const int& quantite)
{
  inventaire[nom_produit].ajouter(date, quantite);
}

// Enlever les produits avec des dates expirées
void Epicerie::enlever_produits_expires(const Date& date_courante)
{
  ArbreMap<std::string, Info>::Iterateur iter = inventaire.debut();
  while (iter)
  {
    iter.valeur().enlever_dates_expires(date_courante);
    ++iter;
  }
}

// Enlever n produits
void Epicerie::enlever_produits(const std::string& nom_produit, int& quantite)
{
  inventaire[nom_produit].enlever(quantite);
}

// Retourne true si tous les produits ont été trouvés.
bool Epicerie::contient_produits(ArbreMap<std::string, int>& produits)
{
  ArbreMap<std::string, int>::Iterateur iter = produits.debut();
  while (iter)
  {
    if (inventaire[iter.cle()].get_quantite() < iter.valeur())
    {
      return false;
    }
    ++iter;
  }
  return true;
}

const int Epicerie::get_quantite(const std::string& produit) 
{
  if (!inventaire.rechercher(produit))
  {
    return 0;
  }
  return inventaire[produit].get_quantite();
}
