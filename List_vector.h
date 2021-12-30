#ifndef _LISTAV_H
#define _LISTAV_H

#include "Linear_list.h"

template< class T >
class List_vector: public Linear_list<T, int>{
 public:
	typedef typename Linear_list<T, int>::value_type value_type;
	typedef typename Linear_list<T, int>::position position;

	List_vector();
	List_vector(int);
	List_vector(const List_vector<T>& );
	~List_vector();
	void create();
	bool empty() const;
	value_type read(position) const;
	void write(const value_type &, position);
	position begin() const;
	bool end(position) const;
	position next(position) const;
	position previous(position) const;
	void insert(const value_type &, position);
	void erase(position);

	List_vector<T>& operator=(const List_vector<T>&);
	bool operator==(const List_vector<T> &) const;

 private:
	void change_dimension_(T*& , int , int );
	value_type* elements_;
	int length_; // the length of the list
	int array_dimension_; // array's dimension
};

template< class T >
List_vector< T >::List_vector() {
  array_dimension_ = 10;
  this->create();
}

template< class T >
List_vector< T >::List_vector(int dim){
  array_dimension_ = dim;
  this->create();
}

template< class T >
List_vector< T >::List_vector(const List_vector<T>& Lista) {
  this->array_dimension_ = Lista.array_dimension_;
  this->length_ = Lista.length_;
  this->elements_ = new T[array_dimension_];
  for (int i=0; i<Lista.array_dimension_; i++)
     this->elements_[i] = Lista.elements_[i];
}

template< class T >
List_vector< T >::~List_vector(){
	delete[] elements_;
}

template< class T >
void List_vector< T >::create(){
  this->elements_ = new T[array_dimension_];
  this->length_ = 0;
}

template< class T >
bool List_vector< T >::empty() const {
    return(length_ == 0);
}

template< class T >
typename List_vector< T >::position List_vector< T >::begin() const {
	return(1); // e quindi pos(1)=pos(n+1) se la lista -Ah vuota (n=0)
}

template< class T >
typename List_vector< T >::position List_vector< T >::next(position p) const {
	if ( (0 < p) && (p < length_+1)) // precondizione
		return(p+1);
	else
		return(p);
}

template< class T >
typename List_vector< T >::position List_vector< T >::previous(position p) const {
	if ( (1 < p) && (p < length_+1)) // precondizione
		return(p-1);
	else
		return(p);
}

template< class T >
bool List_vector< T >::end(position p) const {
	if ( (0 < p) && (p <= length_+1)) // precondizione
		return( p == length_+1);
	else
		return(false);
}

template< class T >
typename List_vector< T >::value_type List_vector< T >::read(position p) const {
	if ( (0 < p) && (p < length_+1)) // precondizione
		return(elements_[p-1]);
}

template< class T >
void List_vector< T >::write(const value_type &a, position p) {
  if ( (0 < p) && (p < length_+1)) // precondizione
    elements_[p-1] = a;
}

template< class T >
void List_vector< T >::insert(const value_type &a, position p){
  if (length_ == array_dimension_){
    change_dimension_(elements_, array_dimension_, array_dimension_ * 2);
    array_dimension_ = array_dimension_ * 2;
  }
  if ( (0 < p) && (p <= length_+1)) { // precondizione
		for (int i=length_; i>=p; i--)
			elements_[i] = elements_[i-1];
		elements_[p-1]=a;
		length_++;
	}
}

template< class T >
void List_vector< T >::erase(position p){
  if ( (0 < p) && ( p < length_ + 1)) // precondizione
    if (!empty()) {
			for (int i=p-1;i<(length_-1);i++)
				elements_[i]=elements_[i+1];
			length_--;
		}
}

template<class T>
void List_vector< T >::change_dimension_(T*& a, int vecchiaDim, int nuovaDim){

  T* temp = new T[nuovaDim];
  int number;
  if (vecchiaDim < nuovaDim)
     number = vecchiaDim;
  else
     number = nuovaDim;
  for (int i=0; i<number; i++)
     temp[i]=a[i];
  delete [] a;
  a = temp;
}

template<class T>
List_vector<T>& List_vector<T>::operator=(const List_vector<T>& l){
	if (this != &l){   // attenzione agli autoassegnamenti: l = l
		this->array_dimension_ = l.array_dimension_;
		this->length_ = l.length_;
		delete this->elements_;
		this->elements_ = new T[array_dimension_];
		for (int i=0; i<l.array_dimension_; i++)
			this->elements_[i] = l.elements_[i];
	}
	return *this;
}

template<class T>
bool List_vector<T>::operator==(const List_vector<T> &l) const{
	if (l.length_ != this->length_)
		return false;
  for (int i=0; i<this->array_dimension_; i++)
		if (this->elements_[i] != l.elements_[i])
			return false;
	return true;
}

#endif
