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
#include "produit.h"
#include "pointst.h"

class Carte
{
  public:
    Carte(){}
    std::string recommander() const;
    void set_date_actuelle(const Date);
    void placer_epicerie(const Epicerie);
    void approvisionner(const Epicerie&, const Produit, const int);

  private:
    Date date_actuelle;
    // ArbreMap<PoinST, Epicerie> carte;
    Tableau<Epicerie> epiceries;
};

void Carte::set_date_actuelle(const Date date)
{
  date_actuelle = date;
}

void Carte::placer_epicerie(const Epicerie epicerie)
{
  epiceries.ajouter(epicerie);
}

void Carte::approvisionner(const Epicerie& epicerie, const Produit produit, const int nombre)
{
  int index_epicerie = epiceries.chercher(epicerie);


}

#endif
