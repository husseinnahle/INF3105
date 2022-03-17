/************************************************
  Laboratoire 1
  INF3105 | Structures de données et algorithmes
  UQAM | Département d'informatique
  Source: http://ericbeaudry.ca/INF3105/lab1/
  
INSTRUCTIONS:
  Vous devez compléter ce fichier.
*************************************************/

#include <assert.h>
#include <math.h>
#include "point.h"

Point::Point(const Point& point)
  : x(point.x), y(point.y) 
{
}

Point::Point(float _x, float _y) 
  : x(_x), y(_y)
{
}


float Point::distance(const Point& point) const {
  // À compléter
  return 0;
}


std::ostream& operator << (std::ostream& os, const Point& point) {
  os << "(" << point.x << "," << point.y << ")";
  return os;
}

std::istream& operator >> (std::istream& is, Point& point) {
  char po, vir, pf;
  is >> po;
  if(is){
    is >> point.x >> vir >> point.y >> pf;
    assert(po=='(');
    assert(vir==',');
    assert(pf==')');
  }
  return is;
}


