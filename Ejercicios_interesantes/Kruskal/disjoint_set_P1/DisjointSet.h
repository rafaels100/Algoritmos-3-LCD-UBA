#include <iostream>
#include "Lista.cpp"

using namespace std;

#ifndef DISJOINTSET_H
#define DISJOINTSET_H
class DisjointSet : public Lista {
public:
  //default constructor
  DisjointSet();
  //overload constructor
  DisjointSet(unsigned int x);
  //destructor
  ~DisjointSet();
  
  //otros
  

private:
};
#endif // !DISJOINTSET_H
