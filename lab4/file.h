/*
  INF3105 - Structures de donn�es et algorithmes
  UQAM / D�partement d'informatique
*/
 
#if  !defined(__FILE_H__)
 #define  __FILE_H__

template <class T> class File
{
  public:
    File();
    ~File();

    void  enfiler(const T&);
    T     defiler();
    void  defiler(T&);
    bool  vide() const {return queue==nullptr;}

  private:

    class Cellule
    {
      public:
        Cellule(const T& e, Cellule* c=nullptr);
        T          element;
        Cellule*   suivante;
    };

    Cellule *queue;
};

#include <assert.h>

template <class T>
File<T>::File()
{
    queue = nullptr;
}

template <class T>
File<T>::~File()
{
    // � compl�ter.
}

template <class T>
File<T>::Cellule::Cellule(const T& e, Cellule* c)
: element(e), suivante(c)
{
}

template <class T>
void File<T>::enfiler(const T& e)
{
    // � compl�ter.
    assert(queue);
}

template <class T>
T File<T>::defiler()
{
    T result;
    return result;
}

template <class T>
void File<T>::defiler(T& r)
{
    // � compl�ter.
}

#endif
