#include <iostream>
#include <initializer_list>
using namespace std;

#ifndef LISTA_H
#define LISTA_H

typedef unsigned long Nat;

class Lista{
public:
	struct Nodo{
		int valor;
		Nodo* sig;
		Nodo* ant;
		Nodo* prim;
		//constructor overload
		Nodo(int v, Nodo* a, Nodo* s, Nodo* p) : valor(v), ant(a), sig(s), prim(p) {}
	};
	//default constructor
	Lista();
	//overload constructor
	Lista(initializer_list<int> elems);
	//constructor por copia de la lista
	Lista(const Lista& l);
	//destructor
	~Lista();
	//operador asignacion
	Lista& operator=(const Lista& aCopiar);
	//mutadores
	//agregar adelante
	//Agrega al final de los nodos, si estos estuvieran
	//ordenados como una lista con indices (I know, poco intuitivo)
	void agregarAtras(int x);
	//agregar adelante
	//agrega al frente de la lista, es decir, el que agregue
	//sera el nuevo prim
	void agregarAdelante(int x);
	//eliminar iesimo: where boys come to die and men are born
	void eliminar(int i);
	
	

	//otros metodos
	//mostrar la lista. Se debe pasar cout como argumento para que funcione. Pero usando << obtengo el mismo resultado.
	void mostrar(ostream& o);
	//obtener el iesimo nodo (solo lectura)
	Nodo* getIesimo(Nat i) const;
	//obtener la longitud de la lista
	int longitud() const;
	
	//mostrar direccion del primer elemento de la lista
	void showPrim() const;
	
        //operador para imprimir la lista con cout de toda la vida
	friend ostream& operator<<(ostream& os, Lista& l){
		l.mostrar(os);
		return os;
	}

private:
	int longitud_;
	Nodo* prim;

	void destruirNodos();
	void copiarNodos(const Lista &o);
};
#endif
