#if !defined(_POINT__H_)
#define _POINT__H_
#include <iostream>
#include <assert.h>
#include <math.h>

class Point
{
  public:
    Point(const Point&);
    Point(double x=0, double y=0);
    double distance(const Point&) const;
    bool operator == (const Point&) const;

  private:
    double x;
    double y;

    friend std::istream& operator >> (std::istream&, Point&);
    friend std::ostream& operator << (std::ostream&, const Point&);
};
#endif

