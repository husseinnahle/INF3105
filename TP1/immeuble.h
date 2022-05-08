#if !defined(_IMMEUBLE__H_)
#define _IMMEUBLE__H_

#include <iostream>
#include <sstream>
#include <string>
#include "point.h"

class Immeuble
{
  public:
    Immeuble();

    const Immeuble& get_immeuble() const;    
    std::string     get_nom() const;
    Point           get_position() const;
    double          get_hauteur() const;
    int             get_nombre_residents() const;

    double          distance(const Immeuble&) const;
    
    Immeuble&       operator = (const Immeuble&);
    bool            operator == (const Immeuble&) const;

  private:
    std::string     nom;
    Point           position;
    double          hauteur;
    int             nombre_residents;

    friend void operator >> (const std::string&, Immeuble&);
    friend std::ostream& operator << (std::ostream&, const Immeuble&);
};
#endif
