#if !defined(_EPICERIE__H_)
#define _EPICERIE__H_

#include <cmath>
#include "arbremap.h"
#include "pointst.h"
#include "date.h"

// La class Info stock les informations d'un produit. Pour chaque produit il existe un objet Info
class Info
{
  public:
    Info() { quantite = 0; }
    const int& get_quantite() const { return quantite; }
    void ajouter(const Date&, const int& quantite);
    void enlever(int& quantite);
    void enlever_dates_expires(const Date&);
    void afficher();

  private:
    // Cet arbre range les dates par ordre decroissant (voir operateur < de la class Date)
    // La clé représente la date d'expiration et la valeur représente la quantité.
    ArbreMap<Date, int> info;
    // Quantité total (Égale à la somme des valeurs de l'arbre info)
    int quantite;
  friend class Carte;
  friend class Epicerie;
};

class Epicerie
{
  public:
    Epicerie(){}
    Epicerie(const std::string&);
    Epicerie(const std::string&, const PointST&);
    
    const std::string& get_nom() const { return nom; }
    const PointST& get_position() const { return position; }
    std::string get_inventaire();
    const int get_quantite(const std::string& produit);

    void enlever_produits_expires(const Date&);
    void enlever_produits(const std::string&, int&);
    void ajouter_produits(const std::string&, const Date&, const int&);
    bool contient_produits(ArbreMap<std::string, int>&);

    bool operator < (const Epicerie& epicerie) const { return nom < epicerie.nom; }
    bool operator == (const Epicerie& epicerie) const { return nom == epicerie.nom; }

  private:
    std::string nom;
    PointST position;
    // La clé représente le nom d'un produit.
    ArbreMap<std::string, Info> inventaire;
};

#endif
