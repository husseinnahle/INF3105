#if !defined(__TABLEAU__H__)
#define __TABLEAU__H__
#include <assert.h>

template <class T>
class Tableau
{
  public:
    Tableau(int capacite_initiale=4);
    Tableau(const Tableau&);
    ~Tableau();

    void           ajouter(const T& item);
    void           vider();
    int            taille() const;
    void           inserer(const T& element, int index=0);
    void           enlever(int index=0);
    int            chercher(const T& item) const;
    // Generer toutes les combinaisons possibles des elements d'un tableau
    void           permuter(Tableau<Tableau<T>>& permutations);

    const T&       operator[] (int index) const;
    T&             operator[] (int index);

    bool           operator == (const Tableau<T>& autre) const;
    Tableau<T>&    operator = (const Tableau<T>& autre);

  private:
    T*             elements;
    int            nbElements;
    int            capacite;
    void           redimentionner(int capacite);
    void           permuter(Tableau<Tableau<T>>& permutations, Tableau<T>& tableau, int taille);
    void           swap(int premier, int deuxieme);
};

template <class T>
Tableau<T>::Tableau(int capacite)
{
  this->capacite = capacite;
  nbElements = 0;
  elements = new T[capacite];
}

template <class T>
Tableau<T>::Tableau(const Tableau& autre)
{
  capacite = autre.capacite;
  nbElements = autre.nbElements;
  elements = new T[capacite];
  for (int i = 0; i < nbElements; i++)
  {
    elements[i] = autre.elements[i];
  }
}

template <class T>
Tableau<T>::~Tableau()
{
  delete[] elements;
  elements = nullptr;
}

template <class T>
void Tableau<T>::redimentionner(int capacite)
{
  this->capacite = capacite;
  T* temp = new T[capacite];
  for (int i = 0; i < nbElements; i++)
  {
    temp[i] = elements[i];
  }
  delete[] elements;
  elements = temp;
}

template <class T>
int Tableau<T>::taille() const
{
    return nbElements;
}

template <class T>
void Tableau<T>::ajouter(const T& item)
{
  if (nbElements + 1 > capacite)
  {
    redimentionner(2 * capacite);
  }
  elements[nbElements++] = item;
}

template <class T>
void Tableau<T>::inserer(const T& element, int index)
{
  if (++nbElements > capacite)
  {
    redimentionner(capacite * 2);
  }
  T nouveau = element;
  for (int i = index; i < nbElements; i++)
  {
    T ancien = elements[i];
    elements[i] = nouveau;
    nouveau = ancien;
  }
}

template <class T>
void Tableau<T>::enlever(int index)
{
  for (int i = index; i < nbElements - 1; i++)
  {
    elements[i] = elements[i + 1];
  }
  nbElements--;
}

template <class T>
int Tableau<T>::chercher(const T& item) const
{
  for (int i = 0; i < nbElements; i++)
  {
    if (item == elements[i])
    {
      return i;
    }    
  }
  return -1;
}

template <class T>
void Tableau<T>::vider()
{
  nbElements = 0;
}

template <class T>
void Tableau<T>::swap(int premier, int deuxieme)
{
  T temp = elements[premier];
  elements[premier] = elements[deuxieme];
  elements[deuxieme] = temp;
}

template <class T>
void Tableau<T>::permuter(Tableau<Tableau<T>>& permutations, Tableau<T>& tableau, int taille)
{
  if (taille == 1)
  {
    permutations.ajouter(tableau);
    return;
  }
  for (int i = 0; i < taille; i++)
  {
    permuter(permutations, tableau, taille - 1);
    if (taille % 2 == 1)
    {
      tableau.swap(0, taille - 1);
    }
    else
    {
      tableau.swap(i, taille - 1);
    }    
  }
}

template <class T>
void Tableau<T>::permuter(Tableau<Tableau<T>>& permutations)
{
  Tableau<T> tab = *this;
  permuter(permutations, tab, tab.taille());
}

template <class T>
const T& Tableau<T>::operator[] (int index) const
{
  assert("Erreur, indice hors limite" && index < nbElements);
  return elements[index];
}

template <class T>
T& Tableau<T>::operator[] (int index)
{
  assert("Erreur, indice hors limite" && index < nbElements);
  return elements[index];
}

template <class T>
Tableau<T> &Tableau<T>::operator=(const Tableau<T> &autre)
{
  if (this == &autre)
    return *this;
  nbElements = autre.nbElements;
  if (capacite < autre.nbElements)
  {
    delete[] elements;
    capacite = autre.nbElements;
    elements = new T[capacite];
  }
  for (int i = 0; i < nbElements; i++)
    elements[i] = autre.elements[i];
  return *this;
}

template <class T>
bool Tableau<T>::operator==(const Tableau<T> &autre) const
{
  if (autre.elements == elements)
    return true;
  if (nbElements == autre.nbElements)
  {
    for (int i = 0; i < nbElements; i++)
      if (elements[i] != autre.elements[i])
        return false;
    return true;
  }
  return false;
}

#endif
