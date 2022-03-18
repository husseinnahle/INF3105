/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/
#include <iostream>
#include "produit.h"

Produit::Produit(const std::string& nom, const Date& date_expiration)
{
  this->nom = nom;
  this->date_expiration = date_expiration;
}

std::ostream& operator << (std::ostream& os, const Produit& produit)
{
  os << produit.nom << " " << produit.date_expiration;
  return os;
}
  
  
std::istream& operator >> (std::istream& is, Produit& produit)
{
  char i;
  is >> produit.nom >> i >> produit.date_expiration;
  return is;
}