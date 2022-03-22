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
  est_expire = false;
}

const std::string& Produit::get_nom() const
{
  return nom;
}

const Date& Produit::get_date_expiration() const
{
  return date_expiration;
}

// const bool& Produit::get_est_expire() const
// {
//   return est_expire;
// }

// void Produit::set_est_expire()
// {
//   est_expire = true;
// }

bool Produit::operator < (const Produit& produit) const
{
  if (nom == produit.nom)
  {
    return date_expiration < produit.date_expiration;
  }
  return nom < produit.nom;
}

bool Produit::operator == (const Produit& produit) const
{
  return nom == produit.nom && date_expiration == produit.date_expiration;
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