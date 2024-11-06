#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>

using namespace std;

template<int index> struct TupleLess
 {
    template<typename Tuple>
    bool operator() (const Tuple& left, const Tuple& right) const
    {
        return get<index>(left) < get<index>(right);
    }
};

//el AGM como es un arbol puede ser representado como una lista de adyacencia, donde cada indice es un nodo y cada elemento es el nodo al que llega, el peso de la arista que los
//une, y el indice de la arista
map<int, vector<tuple<int, int, int>>> AGM;

//separo a las aristas segun su peso
map<int, vector<int>> aristas_por_peso;

//vector con los resultados. Cada arista que fue agregada por el usuario tiene su posicion en el vector
vector<int> res;
//0: la arista no pertenece a ningun AGM
//1: la arista pertenece a al menos un AGM
//2: la arista pertenece a todos los AGM

int main(){
  //doy el grafo como lista de aristas. Les agrego un indice a cada una para saber cual es cual
  vector<tuple<int, int, int, int>> g = {make_tuple(1, 3, 7, 0), make_tuple(3, 4, 2, 1), make_tuple(4, 2, 5, 2), make_tuple(1, 2, 1, 3), make_tuple(2, 5, 6, 4), make_tuple(5, 7, 9, 5), 
                              make_tuple(7, 8, 4, 6), make_tuple(6, 8, 9, 7), make_tuple(6, 5, 3, 8)};
  int m = 9;
  int n = 8;
  res.resize(m, 0); //inicialmente todas las aristas no forman parte de ningun AGM
  sort(g.begin(), g.end(), TupleLess<2>());
  //creo un diccionario con los grupos de aristas segun su peso
  for (int i = 0; i < g.size(); i++) {
    int w = get<2>(g[i]);
    int idx = get<3>(g[i]);
    if (aristas_por_peso.count(w) == 0) {
      aristas_por_peso.insert({w, vector<int>{idx}});
    }else{
      aristas_por_peso[w].push_back(idx);
    }
  }
  cout << "Las aristas ordenadas segun su peso: " << endl;
  for (auto const& [key, val] : aristas_por_peso) {
    cout << key << " : (";
    for (auto const& elem : val) {
      cout << elem << " ";
    }
    cout << ")" << endl;
  }
  //el disjoint set lo represento como un array donde un numero negativo significa que ese nodo es raiz. Tambien es su rango, la cantidad de nodos
  //que tiene el arbol. De esa manera, un numero negativo grande indica que es un nodo raiz y que tiene varios nodos en su arbol
  vector<int> padres(8, -1);
  for (tuple<int, int, int, int> arista : g) {
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
      //esta arista forma parte de al menos algun AGM, en particular el que estoy construyendo
      res[idx] = 1;
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
  
  for (auto const& [key, val] : AGM) {
    cout << key << " : ";
    for (auto const& elem : val) {
      cout << "(" << get<0>(elem) << ", " << get<1>(elem) << ", " << get<2>(elem) << "), ";
    }
    cout << endl;
  }
  cout << "La clasificacion de las aristas segun fueron ingresadas es: ";
  for (auto arista : g) {
    cout << "(" << get<0>(arista) << ", " << get<1>(arista) << ", " << get<2>(arista) << ") : " << res[get<3>(arista)] << endl;
  }
  return 0;
}
