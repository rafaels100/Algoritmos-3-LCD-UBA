#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;
int INF = 1000;
using grafo = map<int, vector<int>>;

grafo g = {
          {0, vector<int>{1, 2, 3}},
          {1, vector<int>{2}},
          {2, vector<int>{}},
          {3, vector<int>{4, 5}},
          {4, vector<int>{0, 2}},
          {5, vector<int>{}}
          };

void BFS(grafo g, int src){
  queue<int> q;
  q.push(src);
  vector<bool> visitados(g.size(), 0);
  vector<int> distancias(g.size(), INF);
  vector<int> padres(g.size(), -1);
  padres[src] = src;
  distancias[src] = 0;
  visitados[src] = true;
  cout << "Los nodos segun son visitados por BFS son: ";
  cout << src << " ";
  while (!q.empty()) {
    int explorando = q.front();
    for (int vecino : g[explorando]) {
      if (!visitados[vecino]) {
        //si no lo habia visto antes, estaba blanco, lo pinto de gris, lo visito
        cout << vecino << " ";
        visitados[vecino] = true;
        distancias[vecino] = distancias[explorando] + 1;
        padres[vecino] = explorando;
        //lo agrego a la cola para explorarlo luego
        q.push(vecino);
      }
    }
    //una vez visite a todos los vecinos, considero al nodo actual como explorado, y lo pinto de negro. Lo saco de la cola
    q.pop();
  }
  //veo las distancias al nodo fuente
  cout << endl;
  cout << "Distancias desde el nodo fuente: " << endl;
  for (int i = 0; i < distancias.size(); i++) {
    cout << "(" << i << ", " << distancias[i] << "), ";
  }
  cout << endl;
  cout << "Los padres de cada nodo por BFS son:";
  for (int i = 0; i < padres.size(); i++) cout << "(" << i << ", " << padres[i] << "), ";
  cout << endl;
  return;
}

int main(){
  BFS(g, 0);
  return 0;
}
