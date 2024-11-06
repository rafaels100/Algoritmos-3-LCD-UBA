#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <stack>

using namespace std;
//cantidad de nodos y aristas
int n, m;
using arista = tuple<int, int, int, int>;
using grafo = map<int, vector<tuple<int, int, int>>>;

//lista de aristas, donde tendremos nodos u, v, el peso w de la arista, y el indice idx de la misma
vector<arista> aristas;
//AGM creado por kruskal
grafo AGM;
//un vector con las aristas presentes en el AGM
vector<arista> aristas_AGM;

//funcion para comparar las aristas segun su peso
bool compararAristas(const arista &e_1, const arista &e_2){
      return get<2>(e_1) < get<2>(e_2);
}

void kruskal(vector<arista> &aristas, int n){
  //el disjoint set lo represento como un array donde un numero negativo significa que ese nodo es raiz. Tambien es su rango, la cantidad de nodos
  //que tiene el arbol. De esa manera, un numero negativo grande indica que es un nodo raiz y que tiene varios nodos en su arbol
  vector<int> padres(n, -1);
  for (tuple<int, int, int, int> arista : aristas) {
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
      //cout << "Tree edge: (" << get<0>(arista) << ", " << get<1>(arista) << ")" << endl;
      int u = get<0>(arista);
      int v = get<1>(arista);
      int w = get<2>(arista);
      int idx = get<3>(arista);
      if (AGM.count(u) == 0) {
        AGM.insert({u, vector<tuple<int, int, int>>{make_tuple(v, w, idx)}});
      }else{
        AGM[u].push_back(make_tuple(v, w, idx));
      }
      if (AGM.count(v) == 0) {
        AGM.insert({v, vector<tuple<int, int, int>>{make_tuple(u, w, idx)}});
      }else{
        AGM[v].push_back(make_tuple(u, w, idx));
      }
      //agrego a la arista a la lista de aristas en el AGM
      aristas_AGM.push_back(arista);
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
      //cout << "Genera ciclo agregar: (" << get<0>(arista) << ", " << get<1>(arista) << ")" << endl;
      continue;
    }
  }
  return;
}

int main(){
  //el usuario me pasa la cantidad de nodos y aristas
  //cin >> n >> m;
  
  n = 8;
  m = 9;
  //doy el grafo como lista de aristas. Les agrego un indice a cada una para saber cual es cual
  aristas = {make_tuple(1, 3, 7, 0), make_tuple(3, 4, 2, 1), make_tuple(4, 2, 5, 2), make_tuple(1, 2, 1, 3), make_tuple(2, 5, 6, 4), make_tuple(5, 7, 9, 5), 
             make_tuple(7, 8, 4, 6), make_tuple(6, 8, 9, 7), make_tuple(6, 5, 3, 8)};
  
  //el primer paso de kruskal es ordenar a las aristas por peso
  sort(aristas.begin(), aristas.end(), compararAristas);
  kruskal(aristas, n);
  //muestro el AGM creado
  cout << "El AGM creado por Kruskal es:" << endl;
  for (auto const& [key, val] : AGM) {
    cout << key << " : ";
    for (auto const& elem : val) {
      cout << "(" << get<0>(elem) << ", " << get<1>(elem) << ", " << get<2>(elem) << "), ";
    }
    cout << endl;
  }
  return 0;
}
