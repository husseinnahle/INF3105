#if !defined(__PILE__H__)
#define __PILE__H__

template <class T>
class Pile
{
  public:
    Pile();
    ~Pile();

    const T& sommet() const;
    int taille() const;
    bool vide() const;

    void empiler(const T&);
    void depiler();
    void depiler(T&);

  private:
    class Cellule
    {
      public:
        Cellule(const T& c, Cellule* c): contenu(c), suivante(s) {}
        T contenu;
        Cellule* suivante;
    };
    Cellule* sommet;
    int nbCellule;
};

template <class T>
Pile::Pile()
{
  sommet = nullptr;
  taille = 0;
}

template <class T>
Pile::~Pile()
{
  vider();
}

template <class T>
const T& Pile::sommet() const
{
  return &sommet;
}

template <class T>
int Pile::taille() const
{
  return nbCellule;
}

template <class T>
bool Pile::vide()
{
  return sommet == nullptr;
}

// template <class T>
// void Pile::vider()
// {
//   while (sommet != nullptr)
//   {
//     Cellule* ancien_sommet = 
//     somm
//   }
// }
#endif