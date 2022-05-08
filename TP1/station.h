#if !defined(_STATION__H_)
#define _STATION__H_
#include <iostream>
#include <sstream>
#include <string>

class Station
{
  public:
    const Station& get_station() const;
    std::string    get_nom() const;
    double         get_rayon() const;
    double         get_hauteur() const;
    double         get_frequence() const;

    Station&       operator = (const Station&);

  private:
    std::string nom;
    double rayon;
    double hauteur;
    double frequence;

    friend void operator >> (const std::string&, Station&);
    friend std::ostream& operator << (std::ostream&, const Station&);
};

#endif
