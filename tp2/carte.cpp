#include "carte.h"

Carte::Carte()
{
}

// Chercher l'index d'une epicerie
const Epicerie* Carte::chercher_epicerie(const std::string& nom_epicerie)
{
  ArbreMap<Epicerie, Tableau<Produit>>::Iterateur iter = carte.debut();
  while (iter)
  {
    if (iter.cle().get_nom() == nom_epicerie)
    {
      return &iter.cle();
    }    
    ++iter;
  }
  return nullptr;
}

// Enlever pour chaque epicerie, les produits expires
void Carte::enlever_produits_expires(const Date& date_courante)
{
  ArbreMap<Epicerie, Tableau<Produit>>::Iterateur iter = carte.debut();
  while (iter)
  {
    for (int i = 0; i < iter.valeur().taille(); i++)
    {
      if (iter.valeur()[i].get_date_expiration() <= date_courante)
      {
        iter.valeur().enlever(i--);
      }
    }
    ++iter;
  }
}

// Ajouter une epicerie
void Carte::ajouter_epicerie(const Epicerie epicerie)
{
  carte[epicerie] = Tableau<Produit>();
}

// Ajouter le produit dans l'inventaire d'une epicerie
void Carte::approvisionner(const std::string& nom_epicerie, const Produit produit, const int quantite)
{
  Tableau<Produit>* produits = &carte[*chercher_epicerie(nom_epicerie)];
  assert(produits != nullptr);
  for (int i = 0; i < quantite; i++)
  {
    produits->ajouter(produit);
  }
}

// Ramasser des produits
int Carte::ramasser(const std::string& nom_epicerie, const std::string& nom_produit, const int& quantite)
{
  Tableau<Produit>* produits = &carte[*chercher_epicerie(nom_epicerie)];
  assert(produits != nullptr);
  int quantite_trouve = 0;
  for (int i = 0; i < produits->taille() && quantite_trouve < quantite; i++)
  {
    std::string nom = (*produits)[i].get_nom();
    if ((*produits)[i].get_nom() == nom_produit)
    {
      quantite_trouve++;
      produits->enlever(i--);
    }
  }
  return quantite - quantite_trouve;
}

// Chercher et retourner les produits d'une epicerie
const Tableau<Produit>& Carte::get_produits(const std::string& nom_epicerie)
{
  return carte[*chercher_epicerie(nom_epicerie)];
}
