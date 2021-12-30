#ifndef ALBEROBINARIO_H_
#define ALBEROBINARIO_H_


#include <iostream>

template <class T, class N>
class alberoBinario {
  static const int NIL = -1;

  public:

    typedef T value_type;
    typedef N Nodo;
    virtual void create() = 0;
    virtual bool empty() const =  0;

    virtual Nodo root() const = 0;
    virtual Nodo parent(Nodo) const =  0;
    virtual Nodo sx(Nodo) const = 0;
    virtual Nodo dx(Nodo) const = 0;
    virtual bool sx_empty(Nodo) const = 0;
    virtual bool dx_empty(Nodo) const = 0;

    virtual void erase(Nodo) = 0;

    virtual T read(Nodo) const = 0;
    virtual void write(Nodo , value_type ) = 0;

    virtual void ins_root(Nodo) = 0;
    virtual void ins_sx(Nodo) = 0;
    virtual void ins_dx(Nodo) = 0;


    virtual void print() const;

private:
    virtual void printSubTree(const Nodo) const;


  };


#endif
