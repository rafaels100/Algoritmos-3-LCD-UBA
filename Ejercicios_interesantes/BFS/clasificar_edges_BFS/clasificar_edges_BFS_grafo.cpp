#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;
int INF = 1000;
using grafo = map<int, vector<int>>;

/*
En BFS con grafo, tenemos dos tipos de aristas:
tree edges: las aristas que pertenecen al arbol BFS
cross edges: las aristas que no pertenecen al arbol BFS
Este script deja duplicadas las crossedges, pero las identifica
*/

grafo g = {
          {0, vector<int>{1, 2, 3, 4}},
          {1, vector<int>{0, 2}},
          {2, vector<int>{0, 1, 4}},
          {3, vector<int>{0, 4, 5}},
          {4, vector<int>{0, 2, 3}},
          {5, vector<int>{3}}
          };
vector<pair<int, int>> tree_edges;
vector<pair<int, int>> cross_edges;
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
        tree_edges.push_back(make_pair(explorando, vecino));
        //lo agrego a la cola para explorarlo luego
        q.push(vecino);
      }else{
        //si encuentro un nodo que ya visite previamente, y dicho nodo no es mi padre, se trata de una cross edge
        if (padres[explorando] != vecino) {
          cross_edges.push_back(make_pair(explorando, vecino));
        }
        //esto funciona relativamente bien, captura las crossedges pero las duplica. No tengo ganas ahora de pensar en una forma de solucionarlo
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
  cout << "Las tree edges son:" << endl;
  for (pair<int, int> edge : tree_edges) cout << "(" << edge.first << ", " << edge.second << "), ";
  cout << endl;
  cout << "Las cross edges son:" << endl;
  for (pair<int, int> edge : cross_edges) cout << "(" << edge.first << ", " << edge.second << "), ";
  cout << endl;
  return 0;
}
