#if !defined(_ARBREAVL___H_)
#define _ARBREAVL___H_
#include <cassert>
#include "pile.h"
#include <algorithm>

template <class T>
class ArbreAVL 
{
  public:
    ArbreAVL();
    ArbreAVL(const ArbreAVL&);
    ~ArbreAVL();

    bool vide() const;
    bool contient(const T&);
    void inserer(const T&);
    void vider();
    int hauteur() const;
    ArbreAVL& operator = (const ArbreAVL&);
    void enlever(const T& element);
    
    // Fonctions pour certains tests ou diagnostique
    int taille() const;
    void afficher() const;

    class Iterateur;
    Iterateur debut() const;
    Iterateur fin() const;
    Iterateur rechercher(const T&) const;
    Iterateur rechercherEgalOuSuivant(const T&) const;
    Iterateur rechercherEgalOuPrecedent(const T&) const;
    const T& operator[](const Iterateur&) const;
    T& operator[](const Iterateur&);

  private:
    struct Noeud{
        Noeud(const T&);
        T contenu;
        int equilibre;
        Noeud *gauche;
        Noeud *droite;
    };
    Noeud* racine;

    // Fonctions internes
    bool inserer(Noeud*&, const T&);
    void rotationGaucheDroite(Noeud*&);
    void rotationDroiteGauche(Noeud*&);
    void vider(Noeud*&);
    T* recherche(Noeud*&, const T&);
    void copier(const Noeud*, Noeud*&) const;
    int hauteur(const Noeud*) const;
    int compter(const Noeud*) const;
    void preparerafficher(const Noeud* n, int profondeur, int& rang, T* elements, int* profondeurs) const;
    int maximum(const int&, const int&) const;
    const T& maxNoeud(Noeud*) const;
    bool enlever(Noeud*&, const T&);
  
  public:
    class Iterateur
    {
      public:
        Iterateur(const ArbreAVL& a);
        Iterateur(const Iterateur& a);
        Iterateur(const ArbreAVL& a, Noeud* c);

        operator bool() const;
        bool operator!() const;
        bool operator==(const Iterateur&) const;
        bool operator!=(const Iterateur&) const;
        
        const T& operator*() const;

        Iterateur& operator++();
        Iterateur operator++(int);
        Iterateur& operator = (const Iterateur&);
      private:
        const ArbreAVL& arbre_associe;
        Noeud* courant;
        Pile<Noeud*> chemin;
        
      friend class ArbreAVL;
    };
};


//-----------------------------------------------------------------------------

template <class T>
ArbreAVL<T>::Noeud::Noeud(const T& c)
 : contenu(c), equilibre(0), gauche(nullptr), droite(nullptr)
{
}

template <class T>
ArbreAVL<T>::ArbreAVL() 
 : racine(nullptr)
{
}

template <class T>
ArbreAVL<T>::ArbreAVL(const ArbreAVL<T>& autre)
 : racine(nullptr)
{
  copier(autre.racine, racine);
}

template <class T>
ArbreAVL<T>::~ArbreAVL()
{
  vider(racine);
}

template <class T>
bool ArbreAVL<T>::contient(const T& element)
{
  return recherche(racine, element) != nullptr;
}

template <class T>
T* ArbreAVL<T>::recherche(Noeud*& noeud, const T& element)
{
  if (noeud == nullptr)
  {
    return nullptr;
  }
  if (element == noeud->contenu) 
  {
    return &(noeud->contenu);
  }
  else if(element < noeud->contenu)
  {
    return recherche(noeud->gauche, element);
  }
  return recherche(noeud->droite, element);
}

template <class T>
void ArbreAVL<T>::inserer(const T& element)
{
  inserer(racine, element);
}

template <class T>
bool ArbreAVL<T>::inserer(Noeud*& noeud, const T& element)
{
  if (noeud == nullptr)
  {
    noeud = new Noeud(element);
    return true;
  }
  if (element < noeud->contenu)
  {
    if (inserer(noeud->gauche, element))
    {
      noeud->equilibre++;
      if (noeud->equilibre == 0) return false;
      if (noeud->equilibre == 1) return true;
      assert(noeud->equilibre == 2);
      if(noeud->gauche->equilibre == -1)
        rotationDroiteGauche(noeud->gauche);
      rotationGaucheDroite(noeud);
    }    
  }
  else if (noeud->contenu < element)
  {
    if (inserer(noeud->droite, element))
    {
      noeud->equilibre--;
      if (noeud->equilibre == 0) return false;
      if (noeud->equilibre == -1) return true;
      assert(noeud->equilibre == -2);
      if(noeud->droite->equilibre == 1)
        rotationGaucheDroite(noeud->droite);
      rotationDroiteGauche(noeud);
    }
  }
  else
  {
    noeud->contenu = element;
  }
  return false;
}

template <class T>
void ArbreAVL<T>::rotationDroiteGauche(Noeud*& racinesousarbre)
{
  Noeud *temp = racinesousarbre->droite;
  int ea = temp->equilibre;
  int eb = racinesousarbre->equilibre;
  int neb = (-ea > 0 ? -ea : 0) + 1 + eb;
  int nea = ea + (neb > 0 ? neb : 0) + 1;
  temp->equilibre = neb;
  racinesousarbre->equilibre = nea;
  racinesousarbre->droite = temp->gauche;
  temp->gauche = racinesousarbre;
  racinesousarbre = temp;
}

template <class T>
void ArbreAVL<T>::rotationGaucheDroite(Noeud*& racinesousarbre)
{
  Noeud *temp = racinesousarbre->gauche;
  int  ea = temp->equilibre;
  int  eb = racinesousarbre->equilibre;
  int  neb = -(ea>0 ? ea : 0) - 1 + eb;
  int  nea = ea + (neb < 0 ? neb : 0) - 1;
  temp->equilibre = nea;
  racinesousarbre->equilibre = neb;
  racinesousarbre->gauche = temp->droite;
  temp->droite = racinesousarbre;
  racinesousarbre = temp;
}

template <class T>
bool ArbreAVL<T>::vide() const
{
  return racine == nullptr;
}

template <class T>
void ArbreAVL<T>::vider()
{
  vider(racine);
  racine = nullptr;
}

template <class T>
void ArbreAVL<T>::vider(Noeud*& noeud)
{
  if (noeud == nullptr)
  {
    return;
  }
  vider(noeud->gauche); 
  vider(noeud->droite);    
  delete noeud;
}

template <class T>
void ArbreAVL<T>::copier(const Noeud* source, Noeud*& noeud) const
{
  if (source != nullptr)
  {
    noeud = new Noeud(source->contenu);
    copier(source->gauche, noeud->gauche);
    copier(source->droite, noeud->droite);
  }
}

template <class T>
int  ArbreAVL<T>::hauteur() const
{
  return hauteur(racine);
}

template <class T>
int  ArbreAVL<T>::taille() const
{
  return compter(racine);
}

template <class T>
int ArbreAVL<T>::maximum(const int& a, const int& b) const
{
  int max = a > b ? a : b;
  return a > b ? a : b;
}

template <class T>
int  ArbreAVL<T>::hauteur(const Noeud* n) const
{
  if(n == nullptr)
  {
    return 0;
  }
  return 1 + maximum(hauteur(n->gauche), hauteur(n->droite));
}

template <class T>
int ArbreAVL<T>::compter(const Noeud* n) const
{
  if(n == nullptr)
  {
    return 0;
  }
  return 1 + compter(n->gauche) + compter(n->droite);
}

template <class T>
ArbreAVL<T>& ArbreAVL<T>::operator=(const ArbreAVL& autre)
{
  if(this == &autre)
  {
    return *this;
  }
  vider();
  copier(autre.racine, racine);
  return *this;
}

// ------ Optionnel Lab 6 -----
template <class T>
const T& ArbreAVL<T>::maxNoeud(Noeud* n) const
{
    Noeud* courant = n;
    while (courant->gauche != nullptr) {
        courant = courant->gauche;
    }
    return courant->contenu;
}

template <class T>
void ArbreAVL<T>::enlever(const T& element)
{
  enlever(racine, element);
}

template <class T>
bool ArbreAVL<T>::enlever(Noeud*& noeud, const T& element)
{
  if (!contient(element))
  {
    return false;
  }
  if(element < noeud->contenu)
  {
    if(enlever(noeud->gauche, element))
    {
      noeud->equilibre = hauteur(noeud->gauche) - hauteur(noeud->droite);
      if(noeud->equilibre == 0)
        return true;
      if(noeud->equilibre == -1)
        return true;
      //assert(noeud->equilibre == -2);
      if(noeud->droite->equilibre == 2)
        rotationGaucheDroite(noeud->droite);
      rotationDroiteGauche(noeud);
    }
    return false;
  }
  else if(element > noeud->contenu)
  {
    if(enlever(noeud->droite, element))
    {   
      noeud->equilibre = hauteur(noeud->gauche) - hauteur(noeud->droite);
      if(noeud->equilibre == 0) {
        return true;
      }
      if(noeud->equilibre == 1) {
        return true;
      }
      //assert(noeud->equilibre == 2);
      if(noeud->gauche->equilibre == -2)
        rotationDroiteGauche(noeud->gauche);
      rotationGaucheDroite(noeud);
    }
    return false;
  }
  else if(element == noeud->contenu)
  {
    if (noeud->gauche==nullptr && noeud->droite==nullptr)
    {
      delete noeud;
      noeud = nullptr;
      return true;
    }
    else
    {
      if (noeud->gauche==nullptr||noeud->droite==nullptr) {
        if (noeud->gauche == nullptr) { 
          Noeud* temp = noeud->droite;
          delete noeud;
          noeud = temp;
        } else { 
          Noeud* temp = noeud->gauche;
          delete noeud;
          noeud = temp;
        }
      } else {
        noeud->contenu = maxNoeud(noeud->gauche);
        return enlever(noeud->gauche, noeud->contenu);
      }
      return true;
    }
  }
  return false;
}

// Code fourni pour afficher l'arbre :
#include <iostream>
template <class T>
void ArbreAVL<T>::afficher() const{
    std::cout << "Contenu de l'arbre (";
    int n = taille();
    std::cout << n << " noeuds)\n";
    T* elements = new T[n];
    int* profondeurs = new int[n];
    n=0;
    preparerafficher(racine, 0, n, elements, profondeurs);
    for(int p=0;;p++){
        bool derniereprofondeur = true;
        for(int i=0;i<n;i++){
            if(profondeurs[i]==p){
                std::cout << elements[i];
                derniereprofondeur = false;
            }
            std::cout << '\t';
        }
        std::cout << '\n';
        if(derniereprofondeur) break;
    }
    delete[] profondeurs;
    delete[] elements;
    std::cout << "-------------" << std::endl;
}

template <class T>
void ArbreAVL<T>::preparerafficher(const Noeud* n, int profondeur, int& rang, T* elements, int* profondeurs) const{
  if(n==nullptr) return;
  preparerafficher(n->gauche, profondeur+1, rang, elements, profondeurs);
  elements[rang] = n->contenu;
  profondeurs[rang] = profondeur;
  rang++;
  preparerafficher(n->droite, profondeur+1, rang, elements, profondeurs);
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::debut() const
{
  Iterateur iter(*this);
  iter.courant = racine;
  if (iter.courant != nullptr)
  {
    while (iter.courant->gauche != nullptr)
    {
      iter.chemin.empiler(iter.courant);
      iter.courant = iter.courant->gauche;
    }      
  }
  return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::fin() const
{
  return Iterateur(*this);
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercher(const T& e) const
{
  Iterateur iter(*this);
  Noeud* n = racine;
  while(n)
  {
    if (e < n->contenu)
    {
      iter.chemin.empiler(n);
      n = n->gauche;
    }
    else if(n->contenu < e)
    {
      n = n->droite;
    }
    else
    {
      iter.courant = n;
      return iter;
    }
  }
  iter.chemin.vider();
  return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuSuivant(const T& e) const
{
  Iterateur iter(*this);
  Noeud* n = racine;
  while (n)
  {
    if (e < n->contenu)
    {
      iter.courant = n;
      n = n->gauche;
    }
    else if (n->contenu < e)
    {
      n = n->droite;
    }
    else
    {
      return rechercher(e);
    }
  }
  if (iter.courant != nullptr)
  {
    return rechercher(iter.courant->contenu);
  }
  return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuPrecedent(const T& e) const
{
  Noeud* n = racine;
  Noeud* dernier = nullptr;
  while(n)
  {
    if(e < n->contenu)
    {
      n = n->gauche;
    }
    else if(n->contenu < e)
    {
      dernier = n;
      n = n->droite;
    }
    else
    {
      return rechercher(e);
    }
  }
  if (dernier != nullptr)
  {
    return rechercher(dernier->contenu);
  }  
  return Iterateur(*this);
}

template <class T>
const T& ArbreAVL<T>::operator[](const Iterateur& iterateur) const
{
  assert(&iterateur.arbre_associe == this);
  assert(iterateur.courant);
  return iterateur.courant->contenu;
}

template <class T>
T& ArbreAVL<T>::operator[](const Iterateur& iterateur)
{
  assert(&iterateur.arbre_associe == this);
  assert(iterateur.courant);
  return iterateur.courant->contenu;
}

template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL& a)
 : arbre_associe(a), courant(nullptr)
{
}

template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL<T>::Iterateur& a)
: arbre_associe(a.arbre_associe)
{
  courant = a.courant;
  chemin = a.chemin;
}

// Pr??-incr??ment
template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator++()
{
  assert(courant);
  Noeud* suivant = courant->droite;
  while (suivant)
  {
    chemin.empiler(suivant);
    suivant = suivant->gauche;
  }
  if (!chemin.vide())
  {
    courant = chemin.depiler();
    return *this;
  }
  courant = nullptr;
  return *this;
}

// Post-incr??ment
template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::Iterateur::operator++(int)
{
    Iterateur copie(*this);
    operator++();
    return copie;
}

template <class T>
ArbreAVL<T>::Iterateur::operator bool() const
{
    return courant!=nullptr;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!() const{
    return courant==nullptr;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator==(const Iterateur& o) const{
    assert(&arbre_associe==&o.arbre_associe);
    return courant==o.courant;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!=(const Iterateur& o) const{
    assert(&arbre_associe==&o.arbre_associe);
    return courant!=o.courant;
}

template <class T>
const T& ArbreAVL<T>::Iterateur::operator *() const
{
    assert(courant!=nullptr);
    return courant->contenu;
}

template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator = (const Iterateur& autre){
    assert(&arbre_associe==&autre.arbre_associe);
    courant = autre.courant;
    chemin = autre.chemin;
    return *this;
}

#endif
