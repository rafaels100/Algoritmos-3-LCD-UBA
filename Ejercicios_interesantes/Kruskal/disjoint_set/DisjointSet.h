#include "lista_enlazada/Lista.h"

#ifndef DISJOINTSET_H
#define DISJOINTSET_H

class DisjointSet : public Lista {
public:
  //default constructor
  DisjointSet();
  //overload constructor
  //toma el primer elemento con el que creamos el disjoint set
  //DisjointSet(const int e);
  ~DisjointSet();
  
  //Funciones mutadoras | setters
  //Por que necesitamos funciones mutadoras? Para tener mas control sobre el tipo de cambios que queremos permitir sobre las variables privadas
  //Por ejemplo, en el setter podemos especificar que solo permitimos que la variable edad sea no negativa
  //void setRepr(int r);
  //setea la variable repr
  //@param r - Entero representante del union set
  
  //Funciones de acceso | getters
  //Se usan para permitir acceso de solo lectura a las variables privadas
  //int getLargo() const;
  //muestra la variable largo
  
private:
  int repr;
  int largo;
};

#endif // !DISJOINTSET_H
