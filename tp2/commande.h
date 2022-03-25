/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/
#if !defined(_COMMANDE__H_)
#define _COMMANDE__H_

#include <string>
#include <sstream>
#include <assert.h>
#include "arbremap.h"
#include "tableau.h"
#include "carte.h"
#include "epicerie.h"
#include "produit.h"
#include "date.h"
#include "pointst.h"

class Commande
{
  public:
    Commande(){}
    void traiter(const std::string&, Tableau<std::string>&);
    std::string traiter(const std::string&);

  private:
    Carte carte;
    std::string set_date(const Tableau<std::string>&);
    std::string placer(const Tableau<std::string>&);
    std::string approvisionner(const Tableau<std::string>&);
    std::string recommander(const Tableau<std::string>&);
    std::string ramasser(Tableau<std::string>&);
    std::string afficher_inventaire(const Tableau<std::string>&);
    Date str_to_date(const std::string&);
    PointST str_to_pointst(const std::string&);
};

#endif
