#include "station.h"

const Station& Station::get_station() const
{
  return *this;
}

std::string Station::get_nom() const
{
  return nom;
}

double Station::get_rayon() const
{
  return rayon;
}

double Station::get_hauteur() const
{
  return hauteur;
}

double Station::get_frequence() const
{
  return frequence;
}

Station& Station::operator = (const Station& autre)
{
  nom              = autre.nom;
  hauteur          = autre.hauteur;
  frequence        = autre.frequence;
  rayon            = autre.rayon;
  return *this;
}

void operator >> (const std::string& input, Station& station)
{
  std::istringstream(input) >> station.nom
                            >> station.rayon
                            >> station.hauteur
                            >> station.frequence;
}

std::ostream& operator << (std::ostream& output_stream, const Station& station)
{
  output_stream << station.nom;
  return output_stream;
}
