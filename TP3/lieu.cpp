#include "lieu.h"

Lieu::Lieu(std::string nom, Coordonnee position)
{
  this->nom = nom;
  this->position = position;
}

double Lieu::distance(const Lieu& lieu) const
{
  return position.distance(lieu.position);
}

Direction::Direction(int lieu, std::string route)
{
  this->lieu = lieu;
  this->route = route;
}
