#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

/*
En esta implementacion de Kruskal, uso un disjoint set representado por un array.
*/

template<int index> struct TupleLess
 {
    template<typename Tuple>
    bool operator() (const Tuple& left, const Tuple& right) const
    {
        return get<index>(left) < get<index>(right);
    }
};


int main(){
  //doy el grafo como lista de aristas
  vector<tuple<int, int, int>> g = {make_tuple(1, 3, 7), make_tuple(3, 4, 2), make_tuple(4, 2, 5), make_tuple(1, 2, 1), make_tuple(2, 5, 6), make_tuple(5, 7, 9), 
                              make_tuple(7, 8, 4), make_tuple(6, 8, 8), make_tuple(6, 5, 3)};
  //ordeno las aristas de menor a mayor
  sort(g.begin(), g.end(), TupleLess<2>());
  //el disjoint set lo represento como un array donde un numero negativo significa que ese nodo es raiz. Tambien es su rango, la cantidad de nodos
  //que tiene el arbol. De esa manera, un numero negativo grande indica que es un nodo raiz y que tiene varios nodos en su arbol
  vector<int> padres(8, -1);
  for (tuple<int, int, int> arista : g) {
    //para esta arista, busco los representantes que tiene cada nodo. Voy a encontrar un representante cuando, siguiente el trail de padres,
    //descubra un valor negativo. Una vez descubra al representante, obtengo su rango, que es el tamanio que tiene el arbol del que el es raiz.
    //Los comparo, y sobrevive la raiz con mayor rango. Si hay empate, es indistinto cual sobreviva.
    //para empezar a buscar al representante, lo propongo como el nodo mismo, y en caso de no serlo, sigo buscando por el array de padres
    int repr_1 = get<0>(arista);
    while (padres[repr_1 - 1] > 0) {
      repr_1 = padres[repr_1 - 1]; //resto 1 para acceder al padre de repr_1 pues la lista esta indexada desde 0, y los nodos empiezan desde 1
    }
    //hago lo propio con el otro nodo al final de la arisa actual
    int repr_2 = get<1>(arista);
    while (padres[repr_2 - 1] > 0) {
      repr_2 = padres[repr_2 - 1];
    }
    //si los representantes de estos nodos son diferentes, significa que pertenecen a disjoint sets diferentes. Aplico UNIONSET
    if (repr_1 != repr_2) {
      //esta arista si la consideramos para el arbol
      cout << "Tree edge: (" << get<0>(arista) << ", " << get<1>(arista) << ")" << endl;
      //comparo los rangos de los respectivos representantes. Gana el mas negativo, es decir, el mas pequenio. Seteo que en caso de empate gane el repr_1
      if (padres[repr_1 - 1] <= padres[repr_2 - 1]) {
        //aumentamos el rango del ganador, el repr_1, una cantidad igual a la cantidad de elementos que tenia su competidor, la raiz que fue derrotada
        padres[repr_1 - 1] += padres[repr_2 - 1]; //como los dos son numeros negativos, pues eran dos raices, al sumar negativo con negativo obtenemos negativo
        //sobrevive el repr_1 como raiz, y repr_2 pasa a ser un nodo hijo de la raiz superviviente.
        padres[repr_2 - 1] = repr_1;
      }else{
        //aqui el ganador es el repr_2. Lo mismo que antes, pero al reves
        padres[repr_2 - 1] += padres[repr_1 - 1];
        padres[repr_1 - 1] = repr_2;
      }
    }else{
      //si los nodos pertenecen al mismo disjoint set, agregar esta arista generara un ciclo. Evitamos agregarla
      cout << "Genera ciclo agregar: (" << get<0>(arista) << ", " << get<1>(arista) << ")" << endl;
    }
    
  }
  for (int elem : padres) cout << elem << " ";
  cout << endl;
  return 0;
}
