#include "DisjointSet.h"

//default constructor
DisjointSet::DisjointSet() {
  cout << "El constructor por default fue ejecutado" << endl;
}

//overload constructor
DisjointSet::DisjointSet(unsigned int x) {
  //las disjointset tienen al menos un elemento, es el representante. Empiezo creando una disjointset con este representante, x
  this->agregarAtras(x);
  cout << "El constructor overload fue ejecutado" << endl;
}

//destructor
DisjointSet::~DisjointSet() {
  cout << "El destructor de disjoint set fue ejectuado" << endl;
}
