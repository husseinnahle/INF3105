#include "immeuble.h"

Immeuble::Immeuble()
{
  nom = "--";
  nombre_residents = 0;
}

const Immeuble& Immeuble::get_immeuble() const
{
  return *this;
}

std::string Immeuble::get_nom() const
{
  return nom;
}

Point Immeuble::get_position() const
{
  return position;
}

double Immeuble::get_hauteur() const
{
  return hauteur;
}

int Immeuble::get_nombre_residents() const
{
  return nombre_residents;
}

double Immeuble::distance(const Immeuble& immeuble) const
{
  return position.distance(immeuble.position);
}

Immeuble& Immeuble::operator = (const Immeuble& immeuble)
{
  nom              = immeuble.nom;
  hauteur          = immeuble.hauteur;
  nombre_residents = immeuble.nombre_residents;
  position         = immeuble.position;
  return *this;
}

bool Immeuble::operator == (const Immeuble& immeuble) const
{
  if (this == &immeuble)
  {
    return true;
  }
  
  return nom == immeuble.nom && 
         position == immeuble.position &&
         hauteur == immeuble.hauteur &&
         nombre_residents == immeuble.nombre_residents;
}

void operator >> (const std::string& input, Immeuble& immeuble)
{
  std::istringstream(input) >> immeuble.nom
                            >> immeuble.position
                            >> immeuble.hauteur
                            >> immeuble.nombre_residents;
}

std::ostream& operator << (std::ostream& output_stream, const Immeuble& immeuble)
{
  output_stream << immeuble.nom;
  return output_stream;
}
