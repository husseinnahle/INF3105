#if !defined(__LIEU_H__)
#define __LIEU_H__

#include <istream>
#include <vector>
#include <string>
#include "coordonnee.h"
#include "lieu.h"

class Direction;

class Lieu 
{
  public:
    Lieu(std::string, Coordonnee);
    double distance(const Lieu&) const;
  // private:
    std::string nom;
    Coordonnee position;
    std::vector<Direction> directions;

  friend class Carte; 
};

class Direction 
{
  public:
    Direction(int, std::string);

  // private:
    int lieu;
    std::string route;

  friend class Carte;
  friend class Lieu;
};

#endif