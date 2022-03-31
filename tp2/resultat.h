/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/
#if !defined(_RESULTAT__H_)
#define _RESULTAT__H_

#include "tableau.h"
#include "epicerie.h"

class Resultat
{
  public:
    Resultat(){complet = false;}
   
  private:
    bool complet;
    Tableau<Epicerie> epicerie;

  friend class Carte;
};



#endif
