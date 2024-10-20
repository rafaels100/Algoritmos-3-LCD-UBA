#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <queue>
#include <typeinfo>

using namespace std;
map<int, vector<tuple<int, int>>> g = {
                              {0, vector<tuple<int, int>>{make_tuple(1, 10)}},
                              {1, vector<tuple<int, int>>{make_tuple(0, 10), make_tuple(2, 20), make_tuple(4, 20)}},
                              {2, vector<tuple<int, int>>{make_tuple(1, 20), make_tuple(4, 10), make_tuple(3, 5)}},
                              {3, vector<tuple<int, int>>{make_tuple(2, 5), make_tuple(5, 10)}},
                              {4, vector<tuple<int, int>>{make_tuple(1, 20), make_tuple(2, 10), make_tuple(5, 5)}},
                              {5, vector<tuple<int, int>>{make_tuple(3, 10), make_tuple(4, 5)}}
                            };

void imprimirVecindario(int nodo){
  for (tuple<int, int> vecino : g[nodo]) {
    cout << get<0>(vecino) << " ";
  }
  cout << endl;
  return;
}
vector<int> visitados(10, 0);
void dfs(int nodo){
  visitados[nodo] = 1;
  cout << "visite " << nodo << endl; 
  for (tuple<int, int> vecino : g[nodo]) {
    if (visitados[get<0>(vecino)] == 0) {
      dfs(get<0>(vecino));
    }
  }
  return;
}

int bfs(int nodo){
  vector<int> visitades(10, 0);
  cout << "visite " << nodo << endl; 
  visitades[nodo] = 1;
  /*
  El espiritu de BFS es visitar a todos los vecinos del nodo que estoy explorando,
  y dejar pendiente de eploracion a dichos vecinos
  */
  queue<int> cola;
  cola.push(nodo);
  int acum = 0;
  while (!cola.empty()) {
    //comienzo la exploracion del nodo en frente de la queue. Guardo su info y lo desencolo.
    int actual = cola.front();
    cola.pop();
    //comienzo la exploracion
    for (tuple<int, int> vecino : g[actual]) {
      if (visitades[get<0>(vecino)] == 0) {
        //si hay un nodo que no habia visto antes, lo visito
        cout << "visite " << get<0>(vecino) << endl; 
        visitades[get<0>(vecino)] = 1;
        acum += get<1>(vecino);
        //tambien lo dejo pendiente para explorarlo mas adelante
        cola.push(get<0>(vecino));
      }
      /*BFS sigue la politica de FIFO. El primer nodo que deje pendiente de exploracion sera el primero que comienze a explorar*/
    }
  }
  cout << "El acumulado de las aristas es: " << acum << endl;
  return acum;
}

int main(){
  imprimirVecindario(1);
  cout << "sd" << endl;
  dfs(0);
  for (int elem : visitados) cout << elem << " ";
  cout << endl;
  int minimo = bfs(0);
  int candidato;
  for (int i = 1; i < 6; i++) {
    candidato = bfs(i);
    minimo = (candidato < minimo) ? candidato : minimo;
  }
  cout << "El arbol BFS mas pequeño posible es: " << minimo << endl;
}
