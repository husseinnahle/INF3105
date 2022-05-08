/*  AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/

#if !defined(_CARTE___H_)
#define _CARTE___H_

#include <string>
#include "arbreavl.h"
#include "arbremap.h"
#include "epicerie.h"
#include "pointst.h"

// La classe carte est utilisé pour stocker les épiceries 
class Carte
{
  public:
    Carte(){}
    void ajouter_epicerie(const Epicerie);
    void enlever_produits_expires(const Date&);
    void approvisionner(const std::string&, const std::string&, const Date&, const int);
    bool ramasser(const std::string& , ArbreMap<std::string, int>&);
    std::string recommander(const PointST&, const int&, const int&, ArbreMap<std::string, int>&);
    std::string recommander2(const PointST&, const int&, const int&, ArbreMap<std::string, int>&);
    std::string recommander3(const PointST&, const int&, const int&, ArbreMap<std::string, int>&);

    std::string get_inventaire(const std::string&);

  private:
    ArbreAVL<Epicerie> epiceries;
    void ranger_epiceries_par_ordre(ArbreMap<double, Epicerie*>&, const PointST&, const int&);
    Epicerie* chercher_epicerier_proche(const Epicerie&);
};

#endif
