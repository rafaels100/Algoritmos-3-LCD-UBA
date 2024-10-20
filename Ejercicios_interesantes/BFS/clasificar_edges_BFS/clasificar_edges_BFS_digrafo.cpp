#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;
int INF = 1000;
using digrafo = map<int, vector<int>>;

/*
En BFS con digrafo vamos a tener tres tipos de aristas:
tree edge: son las aristas que estan en el arbol BFS
cross edges: son aristas que no estan en el grafo DFS y que NO van de un nodo a un ancestro suyo
cross edges: son aristas que no estan en el grafo DFS y que SI van de un nodo a un ancestro suyo
*/

digrafo g = {
          {0, vector<int>{1, 2, 3}},
          {1, vector<int>{2}},
          {2, vector<int>{}},
          {3, vector<int>{4, 5}},
          {4, vector<int>{0, 2, 3}},
          {5, vector<int>{}}
          };
vector<pair<int, int>> tree_edges;
vector<pair<int, int>> cross_edges;
vector<pair<int, int>> back_edges;
void BFS(digrafo g, int src){
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
        //si encuentro un nodo que ya visite previamente, se trata de una cross o backedge
        //Para saber si es backedge o crossedge, basta con ver que el nodo al que estoy llegando no forme parte de los ancestros del nodo actual.
        //primero, me deshago del caso problematico en que podria ser backedge: si el nodo al que estoy llegando es el src de una, entonces es backedge,
        //pues estoy yendo a un ancestro. La raiz es ancestro de todos
        if (vecino == src) {
          back_edges.push_back(make_pair(explorando, vecino));
        }else{
          //aun cabe la posibilidad de que sea back edge, si ocurre que el vecino es ancestro no trivial del nodo en exploracion
          int ancestro = padres[explorando];
          while (ancestro != vecino and ancestro != src) {
            ancestro = padres[ancestro];
          }
          //va a salir del while si o si, porque en algun momento algun nodo tendra como ancestro a la raiz, si no encuentro ancestro no trivial
          if (ancestro != src) {
            //si al salir del while encontre un ancestro que es distinto del trivial, se trata de una back edge
            back_edges.push_back(make_pair(explorando, vecino));
          }else{
            //si llegue hasta el nodo src sin encontrar ancestros, entonces no hay ancestro no trivial, y se trata de una cross edge
            cross_edges.push_back(make_pair(explorando, vecino));
          }
        }
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
  cout << "Las back edges son:" << endl;
  for (pair<int, int> edge : back_edges) cout << "(" << edge.first << ", " << edge.second << "), ";
  cout << endl;
  cout << "Las cross edges son:" << endl;
  for (pair<int, int> edge : cross_edges) cout << "(" << edge.first << ", " << edge.second << "), ";
  cout << endl;
  return 0;
}
