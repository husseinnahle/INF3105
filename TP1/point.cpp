#include "point.h"

Point::Point(const Point& point)
  : x(point.x), y(point.y) 
{
}

Point::Point(double x_, double y_) 
  : x(x_), y(y_)
{
}

double Point::distance(const Point& point) const
{
  return sqrt(pow(this->x - point.x, 2) + pow(this->y - point.y, 2));
}

bool Point::operator == (const Point& autre) const
{
  return this->x == autre.x && this->y == autre.y;
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

