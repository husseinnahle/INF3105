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
    void enlever_produits_expires(const Date&);
    void ajouter_epicerie(const Epicerie);
    void ajouter_porduits(const std::string&, const std::string&, const int&);
    void approvisionner(const std::string&, const Produit, const int);
    void ramasser(const std::string& , const std::string& , int&);
    void recommander(const PointST&, const int&, const int&, const ArbreMap<std::string, int>&);
    const Tableau<Produit>& get_produits(const std::string&);

  private:
    ArbreMap<Epicerie, Tableau<Produit>> carte;
    const Epicerie* chercher_epicerie(const std::string&);
};

#endif
