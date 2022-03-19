/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/

#if !defined(__DATE_H__)
#define __DATE_H__

#include <iostream>
#include <string>

class Date
{
  public:
    Date():jour(1), mois(1), annee(2000){};
    Date(const std::string&);
    bool operator <(const Date& date) const;

  private:
    int jour;
    int mois;
    int annee;

  friend std::ostream& operator << (std::ostream&, const Date&);
  friend std::istream& operator >> (std::istream&, Date&);
};

#endif
