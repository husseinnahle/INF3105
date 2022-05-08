/*  INF3105 - Structures de données et algorithmes
    UQAM | Département d'informatique
    Hiver 2022 | TP2
*/

#if !defined(_POINTST__H_)
#define _POINTST__H_

#include <iostream>

// Cette classe représente un point sur la surface de la Terre.
class PointST {

  public:
    PointST(){}
    PointST(double latitude_, double longitude_);
    PointST(const PointST&);

    double distance(const PointST&) const;
    bool operator < (const PointST&) const;

  private:
    double latitude;
    double longitude;

  friend std::ostream& operator << (std::ostream&, const PointST&);
  friend std::istream& operator >> (std::istream&, PointST&);
};

#endif

