#include "date.h"
#include <cstdio>
#include <string>
#include <iomanip>
#include <assert.h>

Date::Date(const std::string& raw_date)
{
  annee = stoi(raw_date.substr(0, 4));
  mois = stoi(raw_date.substr(5, 2));
  jour = stoi(raw_date.substr(8, 2));
}

// L'opérateur < retourne la valeur inverse. Par exemple : (2022-03-29 > 2022-03-28) = false
// Cet opérateur est utilisé par la class arbreAvl pour ranger les dates par ordre décroissant (voir class Info (dans epicerie.h))
bool Date::operator < (const Date& date) const
{
  if (annee > date.annee || (annee == date.annee && mois > date.mois) || 
      (annee == date.annee && mois == date.mois && jour > date.jour))
  {
    return true;
  }  
  return false;
}

bool Date::operator == (const Date& date) const
{
  return jour == date.jour && mois == date.mois && annee == date.annee;
}

std::ostream& operator << (std::ostream& os, const Date& date)
{
  char chaine[40];
  sprintf(chaine, "%04d-%02d-%02d", date.annee, date.mois, date.jour);
  os << chaine;
  return os;
}

std::istream& operator >> (std::istream& is, Date& date)
{
  char tiret[2] = {0, 0};
  is >> date.annee >> tiret[0] >> date.mois >> tiret[1] >> date.jour;
  assert(tiret[0] == '-' && tiret[1] == '-');
  return is;
}
