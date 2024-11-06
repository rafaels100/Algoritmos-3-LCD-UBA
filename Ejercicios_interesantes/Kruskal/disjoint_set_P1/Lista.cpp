#include "Lista.h"


//default constructor
Lista::Lista() {
	longitud_ = 0;
	prim = nullptr;
}
//overload constructor
Lista::Lista(initializer_list<int> elems){
  longitud_ = 0;
  prim = nullptr;
  //itero por los enteros en la lista y los voy agregando como nodos a mi lista
  for (int elem : elems) {
    agregarAtras(elem);
  }
};

//constructor por copia
Lista::Lista(const Lista& l){
	longitud_ = 0;
	prim = nullptr;
	copiarNodos(l);
}

//destructor
Lista::~Lista() {
	//EN este caso no debo considerar los casos en que 
	//hay 0 elementos o mas de 0 elementos. La forma 
	//en que lo vamos a hacer nos ahorrara ese problema.
	//empiezo desde el principio
	Nodo* actual = prim;
	//este while se ocupa de los dos casos, pues se va a detener
	//cuando el actual sea la direccion null
	while(actual != nullptr){
		//creo un nuevo elemento estatico que apunte al siguiente
		//pues si borro el actual voy a perder esa info
		Nodo* siguiente = actual->sig;
		//libero al actual
		delete actual;
		//ahora ya no puedo acceder a la memoria que apunta
		//el puntero actual.
		//sin embargo, si puedo cambiar el lugar a donde apunta
		//el puntero actual, a un lugar al que si puedo acceder
		//(a menos que sea el nullptr, en ese caso no puedo
		//acceder a el, ni mucho menos borrarlo)
		actual = siguiente;
		//como una frivolidad puedo tambien reducir
		//la longitud de la lista
		longitud_--;
	}
	//si salio del while, entonces elimino todo, pues llegamos
	//hasta apuntar al nullptr borrando todo lo previo

	//el prim ahora esta apuntando a un lugar de la memoria
	//que no podemos acceder, pues lo liberamos en el while,
	//y que no sabemos a donde apunta, ni nos interesa ya.
	//Debemos hacer que ese puntero apunte al nullptr, como
	//lo hacia por default cuando creamos el objeto Lista
	prim = nullptr;

	//MORALEJA: 
	//Hacer delete sobre un puntero no afecta al puntero,
	//que es en definitiva una variable estatica, del stack,
	//sino que va a traves de ella y libera la memoria en el 
	//heap a la que apunta dicho puntero. 
	//Una vez que se libero esa memoria, puedo reapuntar al
	//puntero que acabo de usar para liberar otro espacio de 
	//memoria.

	//El puntero es una arma para liberar memoria,
	//que puede ser redirigida hacia otra direccion que 
	//necesite ser liberada. Es un libertador. Como San Martin.
        cout << "El destructor de Lista fue ejecutado" << endl;
}
//operador asigancion
Lista& Lista::operator=(const Lista& aCopiar){
	//primero, elimino cada elemento que podria
	//haber tenido la lista que va a ser asignada a otra
	//reciclo el codigo del destructor
	Nodo* actual = prim;
	while(actual != nullptr){
		//creo un nuevo elemento estatico que apunte al siguiente
		//pues si borro el actual voy a perder esa info
		Nodo* siguiente = actual->sig;
		//libero al actual
		delete actual;
		actual = siguiente;
		longitud_--;
	}
	prim = nullptr;
	//ahora la lista a ser asignada se encuentra en un estado
	//primigenio nuevamente. La lleno con la data de aCopiar
	copiarNodos(aCopiar);
	return *this;
}

//mutadores
void Lista::agregarAtras(int x){
    //en ambos casos, la longitud de la lista aumento en 1
    longitud_++;
	//hay dos casos que debo tener en cuenta:
	//el caso en que empezamos con 0 nodos, 
	//y el caso en que hay algun nodo
	//en ambos casos, sin embargo, debo crear un nuevo
	//nodo en el heap
	Nodo* nuevo = new Nodo(x, nullptr, nullptr, prim);
	if (prim == nullptr){
	  //seteo prim a este primer nuevo nodo
	  prim = nuevo;
	  //y el prime nodo nuevo apunta a si mismo
	  nuevo->prim = prim;
	  return;
	}
	//empiezo a recorrer desde el nodo inicial
	Nodo* actual = prim;
	while (actual -> sig != nullptr) {
		actual = actual -> sig;
	}
	//el nodo ya esta creado, solo es cuestion de que 
	//el ultimo nodo que apuntaba al nullptr ahora apunte
	//a este nuevo nodo que reside en el heap.
	//al salir del while, nos aseguramos que ese nodo que apunta 
	//al nullptr es el actual. Modificamos a donde apunta
	actual->sig = nuevo;
	//a su vez, el nuevo nodo debe apuntar "para atras" a este
	//nodo actual, que es ahora el anteultimo de la lista
	nuevo->ant = actual;
	//el nuevo nodo apunta tambien al principio de la lista, debido a que fue creado con prim en el tercer argumento
	//de este modo "insertamos" al nuevo nodo en nuestra lista
	//atras del todo


}

void Lista::agregarAdelante(int x){
    //la lista crecio
    longitud_++;
	//hay dos casos que debo tener en cuenta:
	//el caso en que empezamos con 0 nodos, 
	//y el caso en que hay algun nodo
	//en ambos casos, sin embargo, debo crear un nuevo
	//nodo en el heap
	Nodo* nuevo = new Nodo(x, nullptr, nullptr, prim);
	if (prim == nullptr){
	  //seteo prim a este primer nuevo nodo
	  prim = nuevo;
	  //y el prim nodo nuevo apunta a si mismo
	  nuevo->prim = prim;
	  return;
	}
	//en este caso no hay nada que buscar: ya se cual 
	//es el nodo que enlazara con este nuevo nodo: el prim
	//solo debo asegurarme que el prim actual apunte hacia 
	//atras a este nuevo nodo, que ya apunta hacia atras a la nada
	prim->ant = nuevo;
	//a su vez, el nuevo prim debe apuntar hacia adelante 
	//al viejo prim
	nuevo->sig = prim;
	//ahora, el nuevo nodo debe llamarse formalmente prim
	prim = nuevo;
	//y el prim del prim es el mismo
	nuevo->prim = prim;
        //y debemos modificar para todos los nodos de la lista el prim al que apuntan
        Nodo* actual = prim;
        while (actual->sig != nullptr) {
          actual = actual->sig;
          actual->prim = prim;
        }
}

//obtener el iesimo nodo
Lista::Nodo* Lista::getIesimo(Nat i) const {
	//si queremos acceder a la data del prim nodo
	//creariamos un getter para el prim
	//pero nos dicen que deben ser naturales,
	//es decir, esperamos una lista con un elemento
	//o mas, para poder acceder a el.

	//empiezo desde el primer nodo
	Nodo* actual = prim;
	//empiezo a recorrer la lista hasta el iesimo elemento
	for(int j = 0; j < i; j++){
		actual = actual -> sig;
	}
	//la data que estoy buscando esta en el nodo actual,
	//que resulta de avanzar i veces a traves de mis nodos,
	//empezando desde el primero
	return actual;
}



//eliminar el iesimo elemento
void Lista::eliminar(int i){
	//va a ser util tener un nodo que apunte
	//tanto al nodo actual como al previo
	Nodo* actual = prim;
	Nodo* prev;
	//de la misma manera que hicimos en obtener iesimo,
	for(int j = 0; j < i; j++){
		//guardamos la info del actual antes de avanzar
		//al nuevo actual
		prev = actual;
		//avanzamos
		actual = actual->sig;
	}
	//al salir del for, el actual es el que tenemos que
	//eliminar
	if(i != 0){
		//si no me piden eliminar el primero, entonces
		//el previo debe apuntar al siguiente del actual,
		//efectivamente salteandose al actual y dejandolo
		//afuera de la cadena
		prev->sig = actual->sig;
	}else{
		//si nos piden eliminar al primero, debemos decir que
		//el nuevo primero sera aquel al que apunta el actual
		//(que coincide con el prim, si entramos en este else)
		prim = actual->sig;
	}
	//no debemos olvidarnos de liberar la memoria a donde 
	//apunta el nodo actual, que puede ser o bien el prim
	//o cualquier otro nodo, si entro en el for
	delete actual;
	//el tamanio de la lista decrecio en 1
	longitud_--;
}

//copiar los elementos de mi lista a otra o 
void Lista::copiarNodos(const Lista &o){
	//empiezo por el principio de la lista donde 
	//copiare la data de mi Lista
	Nodo* actual = o.prim;
	while(actual != nullptr){
		//agregarAtras no solo se encarga de hacer crecer
		//la cadena, sino de aumentar longitud_
		agregarAtras(actual->valor);
		actual = actual->sig;
	}
} 

int Lista::longitud() const {
	return longitud_;
}

void Lista::mostrar(ostream& o){
	//hay dos situaciones: si aun no se agrego ningun elemento
	//a la lista, no hay nada que demostrar, y si trato de 
	//mostrar algo, va a ocurrir un segmentation fault, 
	//porque no tengo permiso para ver ni modificar lo
	//que hay en la direccion a la que apunta el nullptr
	//(el prim apunta al nullptr de nodo por default)
	if (prim != nullptr){
		//empiezo por el nodo inicial
		Nodo* actual = prim;
		//recorro hasta el ultimo nodo
		while (actual -> sig != nullptr){
			o << actual -> valor << " ";
			actual = actual -> sig;
		}
		//imprimo finalmente el ultimo, el que si apunta a la nada
		//(o el primero, si no entro al loop)
		o << actual -> valor;
	}else{
		o << "Aun no se han agregado nodos";
	}
}

void Lista::showPrim() const {
  cout << prim << endl;
}
