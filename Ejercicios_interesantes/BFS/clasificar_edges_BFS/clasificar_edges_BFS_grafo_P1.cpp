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
          {1, vector<int>{2, 3, 4, 5}},
          {2, vector<int>{1, 3}},
          {3, vector<int>{1, 2, 5}},
          {4, vector<int>{1, 5, 6}},
          {5, vector<int>{1, 3, 4}},
          {6, vector<int>{4}}
          };
vector<pair<int, int>> tree_edges;
vector<pair<int, int>> cross_edges;
void BFS(grafo g, int raiz){
  queue<int> q;
  q.push(raiz);
  vector<bool> visitados(g.size(), 0);
  vector<bool> finalizados(g.size(), 0);
  vector<int> distancias(g.size(), INF);
  vector<int> padres(g.size(), -1);
  padres[raiz - 1] = raiz;
  distancias[raiz - 1] = 0;
  visitados[raiz - 1] = true;
  cout << "Los nodos segun son visitados por BFS son: ";
  cout << raiz << " ";
  while (!q.empty()) {
    int nodo = q.front();
    for (int vecino : g[nodo]) {
      if (!visitados[vecino - 1]) {
        //si no lo habia visto antes, estaba blanco, lo pinto de gris, lo visito
        cout << vecino << " ";
        visitados[vecino - 1] = true;
        distancias[vecino - 1] = distancias[nodo - 1] + 1;
        padres[vecino - 1] = nodo;
        tree_edges.push_back(make_pair(nodo, vecino));
        //lo agrego a la cola para explorarlo luego
        q.push(vecino);
      }else if (padres[nodo - 1] != vecino and !finalizados[vecino - 1]) {
        //si encuentro un nodo que ya visite previamente, y dicho nodo no es mi padre, se trata de una cross edge. 
        //Por cuestiones de implementacion de la lista de adyacencias, si no tengo cuidado de que ya termine de explorar al nodo al que estoy llegando,
        //voy a duplicar las cross edges, por eso mantengo un vector con los finalizados, y lo chequeo para no caputar las aristas (u, v) y las (v, u), que son lo mismo en grafos
        cross_edges.push_back(make_pair(nodo, vecino));
      }
    }
    //finalizo la exploracion de este nodo
    finalizados[nodo - 1] = true;
    //una vez visite a todos los vecinos, considero al nodo actual como explorado, y lo pinto de negro. Lo saco de la cola
    q.pop();
  }
  //veo las distancias al nodo fuente
  cout << endl;
  cout << "Distancias desde el nodo fuente: " << endl;
  for (int i = 0; i < distancias.size(); i++) {
    cout << "(" << i + 1 << ", " << distancias[i] << "), ";
  }
  cout << endl;
  cout << "Los padres de cada nodo por BFS son:";
  for (int i = 0; i < padres.size(); i++) cout << "(" << i + 1 << ", " << padres[i] << "), ";
  cout << endl;
  return;
}

int main(){
  int raiz = 1;
  BFS(g, raiz);
  cout << "Las tree edges son:" << endl;
  for (pair<int, int> edge : tree_edges) cout << "(" << edge.first << ", " << edge.second << "), ";
  cout << endl;
  cout << "Las cross edges son:" << endl;
  for (pair<int, int> edge : cross_edges) cout << "(" << edge.first << ", " << edge.second << "), ";
  cout << endl;
  return 0;
}
