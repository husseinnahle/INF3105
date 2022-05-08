#if !defined(_INSTALLATION__H_)
#define _INSTALLATION__H_

#include <iostream>
#include "tableau.h"
#include "immeuble.h"
#include "station.h"

// Installation contient les informations sur une station installée
class Installation : public Station, public Immeuble
{
  public:
    Installation();
    Installation(const Station&);
    Installation(const Station&, const Immeuble&);

    std::string    get_immeuble_nom() const;
    std::string    get_station_nom() const;
    int            get_nombre_clients() const; 

    void           ajouter_client(const Immeuble&);
    int            chercher_client(const Immeuble&) const;
    double         distance(const Installation&) const;

    Installation& operator = (const Installation&);

  private:
    Tableau<Immeuble> clients;
    int nombre_clients;
};

Installation::Installation()
{
  nombre_clients = 0;
}

Installation::Installation(const Station& station)
: Station(station)
{
  nombre_clients = 0;
}

Installation::Installation(const Station& station, const Immeuble& immeuble)
: Station(station), Immeuble(immeuble)
{
  nombre_clients = 0;
}

std::string Installation::get_immeuble_nom() const
{
  return Immeuble::get_nom();
}

std::string Installation::get_station_nom() const
{
  return Station::get_nom();
}

int Installation::get_nombre_clients() const
{ 
  return nombre_clients;
}

void Installation::ajouter_client(const Immeuble& immeuble)
{  
  if (clients.chercher(immeuble) != -1)
  {
    return;
  }
  clients.ajouter(immeuble);
  nombre_clients += immeuble.get_nombre_residents();
}

double Installation::distance(const Installation& autre) const
{
  return get_position().distance(autre.get_position());
}

int Installation::chercher_client(const Immeuble& immeuble) const
{
  return clients.chercher(immeuble);
}

Installation& Installation::operator = (const Installation& autre)
{
  Station::operator=(autre.get_station());
  Immeuble::operator=(autre.get_immeuble());
  clients = autre.clients;
  nombre_clients = autre.nombre_clients;
  return *this;
}
#endif
