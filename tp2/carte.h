/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/

#if !defined(_CARTE___H_)
#define _CARTE___H_

#include <string>
#include <assert.h>
#include "arbremap.h"
#include "tableau.h"
#include "epicerie.h"
#include "produit.h"
#include "pointst.h"

class Carte
{
  public:
    Carte();
    std::string recommander() const;
    void set_date_actuelle(const Date);
    void placer_epicerie(const Epicerie);
    void approvisionner(const std::string&, const Produit, const int);
    void recommnander();
    void enlever_produit(const std::string&, const std::string&, const int);
    ArbreMap<Produit, int>::Iterateur inventaire_iter(const std::string&);

  private:
    Date date_actuelle;
    Tableau<Epicerie> epiceries;
    int chercher_epicerie(const std::string&) const;
};

#endif
