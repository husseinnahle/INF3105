/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/
#if !defined(_CARTE__H_)
#define _CARTE__H_

#include <string>
#include "arbremap.h"
#include "tableau.h"
#include "epicerie.h"
#include "pointst.h"

class Carte
{
  public:
    Carte(){}
    std::string recommander() const;
    void set_date(const Date&);

  private:
    Date date_actuelle;
    ArbreMap<PointST, Epicerie> carte;
    // Tableau<Epicerie> Epiceries;

};

#endif
