/*  INF3105 - Structures de données et algorithmes
    Lab 10 -- Graphes / Représentations et algorithmes de base
    http://cria2.uqam.ca/INF3105/lab11/
*/
#if !defined(__GRAPHE_H__)
#define __GRAPHE_H__

#include <queue>
#include <map>
#include <set>
#include <iostream>

using namespace std;

template <class S>
class Graphe
{
  public:
    void ajouterSommet(const S& s);
    void ajouterAreteOrientee(const S& s1, const S& s2);
    void ajouterAreteNonOrientee(const S& s1, const S& s2);
    void parcoursRechercheProfondeur(const S& s) const;
    void parcoursRechercheLargueur(const S& s) const;
    void extraireComposantesConnexes() const;

  private:
    struct Sommet
    {
      set<S> voisins; 
      mutable bool isVisited;
    };
    map<S, Sommet> sommets; // identification --> sommet
    void parcoursProfondeurRecursif(const S&) const;
    void resetBoolValues() const;
};

template <class S>
void Graphe<S>::ajouterSommet(const S& s)
{
  sommets[s];
}

template <class S>
void Graphe<S>::ajouterAreteNonOrientee(const S& s1, const S& s2)
{
  ajouterAreteOrientee(s1, s2);
  ajouterAreteOrientee(s2, s1);
}

template <class S>
void Graphe<S>::ajouterAreteOrientee(const S& s1, const S& s2)
{
  sommets[s1].voisins.insert(s2);
}

template <class S>
void Graphe<S>::parcoursProfondeurRecursif(const S& s) const
{
  sommets.at(s).isVisited = true;
  cout << s << " ";
  for (const S& voisin : sommets.at(s).voisins)
  {
    if (!sommets.at(voisin).isVisited)
    {
      parcoursProfondeurRecursif(voisin);
    }
  }  
}

template <class S>
void Graphe<S>::parcoursRechercheProfondeur(const S& s) const
{
  resetBoolValues();
  parcoursProfondeurRecursif(s);
  cout << endl;
}

template <class S>
void Graphe<S>::parcoursRechercheLargueur(const S& s) const
{
  resetBoolValues();
  queue<S> file;
  sommets.at(s).isVisited = true;
  file.push(s);
  while (!file.empty())
  {
    S element = file.front;
    file.pop();
    const Sommet& sommet = sommets.at(element);
    for (const S& voisin : sommet.voisins)
    {
      if (!sommets.at(voisin).isVisited)
      {
        sommets.at(voisin).isVisited = true;
        file.push(voisin);
      }
    }
  }
  cout << endl;
}
template <class S>
void Graphe<S>::extraireComposantesConnexes() const
{
  resetBoolValues();
  cout << "{";
  for (const auto& pair : sommets)
  {
    if (pair.second.isVisited)
    {
      continue;
    }
    cout << "{";
    queue<S> file;
    pair.second.isVisited = true;
    file.push(pair.first);
    while (!file.empty())
    {
      S element = file.front();
      file.pop();
      cout << element << " ";
      const Sommet& sommet = sommets.at(element);
      for (const S& voisin : sommet.voisins)
      {
        if (!sommets.at(voisin).isVisited)
        {
          sommets.at(voisin).isVisited = true;
          file.push(voisin);
        }
      }
    }
    cout << "}" << endl;
  }
  cout << "}" << endl;
}

template <class S>
void Graphe<S>::resetBoolValues() const
{
  for (auto& pair : sommets)
  {
    pair.second.isVisited = false;
  }
}

#endif
