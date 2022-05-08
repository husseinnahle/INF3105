#if !defined(__CARTE_H__)
#define __CARTE_H__

#include <algorithm>
#include <istream>
#include <limits>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include "lieu.h"

using namespace std;

class Carte
{
  public:
    double chercher_chemin(const string&, vector<string>, string&, string&) const;
  
  private:
    // Tableau contenant les lieux (sommets)
    vector<Lieu> lieux;
    // string -> nom du sommet ; int -> index de l'objet lieu dans le tableau lieux
    unordered_map<string, int> carte;

    // Utiliser dans la fonction chercher_chemin pour faciliter la construction d'une file prioritaire.
    struct Priorite
    {
      int position;
      double estimation;
      Priorite(int position, double estimation)
      {
        this->position = position;
        this->estimation = estimation;
      }
      bool operator < (const Priorite &o) const
      {
        return estimation > o.estimation;
      }  
    };

    void ajouter_lieu(const Lieu&);
    void ajouter_direction(string&, const vector<string>&);
    
    double chercher_chemin(const int&, const int&, stack<string>&, stack<string>&) const;
    double distance(const Lieu&, const Lieu&) const;
    void consrtuire_chemin(int, unordered_map<int, int>&, stack<string>&, stack<string>&) const;
    void transferer_resulat(stack<string>&, stack<string>&, string&, string&, string&) const;
 
  friend ostream& operator << (ostream &os, Carte &carte);
  friend istream& operator >> (istream &is, Carte &carte);
};
#endif
