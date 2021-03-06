#if !defined(__DATE_H__)
#define __DATE_H__

#include <iostream>
#include <string>

class Date
{
  public:
    Date():jour(1), mois(1), annee(2000){};
    Date(const std::string&);
    bool operator < (const Date&) const;
    bool operator == (const Date&) const;

  private:
    int jour;
    int mois;
    int annee;

  friend std::ostream& operator << (std::ostream&, const Date&);
  friend std::istream& operator >> (std::istream&, Date&);
};

#endif
