/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/
#if !defined(_EPICERIE__H_)
#define _EPICERIE__H_

#include <string>
#include "tableau.h"
#include "arbremap.h"
#include "pointst.h"
#include "produit.h"

class Epicerie
{
  public:
    Epicerie(){}
    Epicerie(const std::string&, const PointST&);
    void ajouter_produit(const Produit, int);
    ArbreMap<Produit, int>::Iterateur inventaire_iter();

  private:
    std::string nom;
    PointST position;
    ArbreMap<Produit, int> inventaire;

  friend class Carte;
  friend std::ostream& operator << (std::ostream&, const Epicerie&);
  friend std::istream& operator >> (std::istream&, Epicerie&);
};

#endif
