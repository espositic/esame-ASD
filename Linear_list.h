#ifndef _LISTALIN_H
#define _LISTALIN_H

#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

template< class T, class P >
class Linear_list{
 public:
	typedef T value_type;
	typedef P position;
	virtual void create() = 0;
	virtual bool empty() const = 0;
	virtual value_type read(position) const = 0;
	virtual void write(const value_type & x, position p) = 0;
	virtual position begin() const = 0;
	virtual bool end(position) const = 0;
	virtual position next(position) const = 0;
	virtual position previous(position) const = 0;
	virtual void insert(const value_type &, position) = 0;
	virtual void erase(position pos) = 0;


	int size() const{
		position p = begin();
		int c = 0;
		while (!end(p)) {c++; p = next(p);}
		return c;
    }
	virtual void push_front(const value_type &);
	virtual void push_back(const value_type &);
	virtual void pop_front();
	virtual void pop_back();
	virtual void clear(){
      while(!empty())
        erase(begin());
    }

};


#endif // _LISTALIN_H
