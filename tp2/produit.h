/*  INF3105 - Structures de données et algorithmes
    UQAM | Département d'informatique
    Hiver 2022 | TP2
*/

#if !defined(_PRODUIT__H_)
#define _PRODUIT__H_

#include <string>
#include <iostream>
#include "date.h"

// Cette classe représente un produit.
class Produit 
{
  public:
    Produit(){}
    Produit(const std::string&, const Date&);
    const std::string& get_nom() const;
    const Date& get_date_expiration() const;
    // const bool& get_est_expire() const;
    // void set_est_expire();

    bool operator < (const Produit&) const;
    bool operator == (const Produit&) const;

  private:
    std::string nom;
    Date date_expiration;
    bool est_expire;

  friend std::ostream& operator << (std::ostream&, const Produit&);
  friend std::istream& operator >> (std::istream&, Produit&);
};

#endif

