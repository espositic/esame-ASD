#ifndef ALBEROBINARIOC_H_
#define ALBEROBINARIOC_H_

#include "alberoBinario.h"
#include "exceptions.h"

template <class T>
class alberoBinarioC : public alberoBinario<T, int>{
    static const int NIL = -1;

  public:

	typedef typename alberoBinario<T, int>::value_type value_type;
	typedef typename alberoBinario<T, int>::Nodo Nodo;

    struct _cella{
        Nodo genitore;
        Nodo sinistro;
        Nodo destro;
        value_type valore;
      };

    typedef struct _cella Cella;
    alberoBinarioC();
    alberoBinarioC(int);
    ~alberoBinarioC();
    void create();
    bool empty() const;
    Nodo root() const;
    Nodo parent(Nodo) const;
    Nodo sx(Nodo) const;
    Nodo dx(Nodo) const;
    bool sx_empty(Nodo) const;
    bool dx_empty(Nodo) const;
    void erase(Nodo);
    int height();
    void controllaNodiFigli(Nodo n,int *altezza, int altezzaAttuale);
    T read(Nodo) const;
    void write(Nodo , value_type );

    void ins_root(Nodo);
    void ins_sx(Nodo);
    void ins_dx(Nodo);

  private:
    int MAXLUNG;
    Cella *spazio;
    int nNodi;
    Nodo inizio;
    Nodo libera;
};

template <class T>
alberoBinarioC<T>::alberoBinarioC()
{
  MAXLUNG = 100;
  spazio = new Cella[MAXLUNG];
  create();
}

template <class T>
alberoBinarioC<T>::alberoBinarioC(int nNodi): MAXLUNG(nNodi)
{
  spazio = new Cella[nNodi];
  create();
}


template <class T>
alberoBinarioC<T>::~alberoBinarioC()
{
  erase(inizio);
  delete[] spazio;
}

template <class T>
void alberoBinarioC<T>::create()
{
  inizio = NIL;
  for (int i = 0; i < MAXLUNG; i++)
    {
      spazio[i].sinistro = (i+1) % MAXLUNG;
    }

  libera = 0;
  nNodi = 0;
}

template <class T>
bool alberoBinarioC<T>::empty() const
{
  return(nNodi == 0);
}

template <class T>
typename alberoBinarioC<T>::Nodo alberoBinarioC<T>::root() const
{
  return(inizio);
}

template <class T>
typename     alberoBinarioC<T>::Nodo alberoBinarioC<T>::parent(Nodo n) const
{
  if (n != inizio)
    return (spazio[n].genitore);
  else
    return(n);
}

template <class T>
typename     alberoBinarioC<T>::Nodo alberoBinarioC<T>::sx(Nodo n) const
{
  if (!sx_empty(n))
    return (spazio[n].sinistro);
  else
    return(n);
};

template <class T>
typename     alberoBinarioC<T>::Nodo alberoBinarioC<T>::dx(Nodo n) const
{
  if (!dx_empty(n))
    return (spazio[n].destro);
  else
    return(n);
}

template <class T>
bool alberoBinarioC<T>::sx_empty(alberoBinarioC<T>::Nodo n) const
{
  return (spazio[n].sinistro == NIL);
}

template <class T>
bool alberoBinarioC<T>::dx_empty(alberoBinarioC<T>::Nodo n) const
{
  return (spazio[n].destro == NIL);
}

template <class T>
void alberoBinarioC<T>::ins_root(alberoBinarioC<T>::Nodo n)
{
  if (inizio == NIL)
    {
      inizio = libera;
      libera = spazio[libera].sinistro;
      spazio[inizio].sinistro = NIL;
      spazio[inizio].destro = NIL;
      nNodi++;
    }
	else
		throw RootExists();
}


template <class T>
void alberoBinarioC<T>::ins_sx(Nodo n)
{
	if (inizio == NIL)
		throw EmptyTree();
	if (n == NIL)
		throw NullNode();
	if (spazio[n].sinistro != NIL)
		throw NodeExists();
	if (nNodi >= MAXLUNG)
		throw FullSize();
  else
    {
      Nodo q = libera;
      libera = spazio[libera].sinistro;
      spazio[n].sinistro = q;
      spazio[q].sinistro = NIL;
      spazio[q].genitore = n;
      spazio[q].destro = NIL;
      nNodi++;
    }
}

template <class T>
void alberoBinarioC<T>::ins_dx(Nodo n)
{
	if (inizio == NIL)
		throw EmptyTree();
	if (n == NIL)
		throw NullNode();
	if (spazio[n].destro != NIL)
		throw NodeExists();
	if (nNodi >= MAXLUNG)
		throw FullSize();
	else
    {
      Nodo q = libera;
      libera = spazio[libera].sinistro;
      spazio[n].destro = q;
      spazio[q].genitore = n;
      spazio[q].sinistro = NIL;
      spazio[q].destro = NIL;
      nNodi++;
    }
}

template <class T>
void alberoBinarioC<T>::erase(Nodo n)
{
  if (n != NIL) {
      if (!sx_empty(n))
        erase(spazio[n].sinistro);
      if (!dx_empty(n))
        erase(spazio[n].destro);
      if (n != inizio) {
          Nodo p = parent(n);
          if (spazio[p].sinistro == n)
            spazio[p].sinistro = NIL;
          else
            spazio[p].destro = NIL;
        }
      else
        inizio = NIL;
      nNodi--;
      spazio[n].sinistro = libera;
      libera = n;
    }
	else
		throw NullNode();
}

template <class T>
int alberoBinarioC<T>::height(){
	Nodo n;
	int altezza=0;
	int altezzaAttuale=0;
	if(!empty()){
		n=root();
		altezza++;
		altezzaAttuale=altezza;
		if(dx_empty(n))
			controllaNodiFigli(dx(n),&altezza,altezzaAttuale);
		if(sx_empty(n))
			controllaNodiFigli(dx(n),&altezza,altezzaAttuale);
	}
	return altezza;
}

template <class T>
void alberoBinarioC<T>::controllaNodiFigli(Nodo n,int *altezza, int altezzaAttuale){
	altezzaAttuale++;
	if(altezzaAttuale>=*(altezza))
		(*altezza)=altezzaAttuale;
	if(dx_empty(n))
		controllaNodiFigli(dx(n),altezza, altezzaAttuale);
	if(sx_empty(n),*altezza)
		controllaNodiFigli(dx(n),altezza, altezzaAttuale);
}

template <class T>
T alberoBinarioC<T>::read(Nodo n) const
{
  if (n != NIL)
	  return (spazio[n].valore);
  else
	  throw NullNode();
}

template <class T>
void alberoBinarioC<T>::write(Nodo n, value_type a)
{
	if (n != NIL)
		spazio[n].valore = a;
	else
		throw NullNode();
}


#endif /* ALBEROBINARIOC_H_ */
