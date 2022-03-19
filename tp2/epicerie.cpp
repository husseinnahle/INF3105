/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/
#include <iostream>
#include "epicerie.h"

Epicerie::Epicerie(const std::string& nom, const PointST& position)
{
  this->nom = nom;
  this->position = position;
}

void Epicerie::ajouter_produit(const Produit produit, int nombre)
{
  if (inventaire.contient(produit))
  {
    inventaire[produit] += nombre;
    return;
  }
  inventaire[produit] = nombre;
}

ArbreMap<Produit, int>::Iterateur Epicerie::inventaire_iter()
{
  return inventaire.debut();
}

std::ostream& operator << (std::ostream& os, const Epicerie& epicerie)
{
  os << epicerie.nom << ' ' << epicerie.position;
  return os;
}

std::istream& operator >> (std::istream& is, Epicerie& epicerie)
{
  is >> epicerie.nom >> epicerie.position;
  return is;
}