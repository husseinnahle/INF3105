/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/
#if !defined(_COMMANDE__H_)
#define _COMMANDE__H_

#include <string>
#include <assert.h>
#include "tableau.h"
#include "carte.h"

class Commande
{
  public:
    Commande(){}
    void traiter(const std::string&, Tableau<std::string>&);
    //std::string traiter(const std::string&);

  private:
    Carte carte;
    std::string set_date(const Tableau<std::string>&);
    std::string placer(const Tableau<std::string>&);
    std::string approvisionner(const Tableau<std::string>&);
    std::string recommander(const Tableau<std::string>&);
    std::string ramasser(const Tableau<std::string>&);
    std::string afficher_inventaire(const Tableau<std::string>&);
};

#endif
