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
          {1, vector<int>{2, 3, 4}},
          {2, vector<int>{3}},
          {3, vector<int>{}},
          {4, vector<int>{5, 6}},
          {5, vector<int>{1, 3, 4}},
          {6, vector<int>{}}
          };
vector<pair<int, int>> tree_edges;
vector<pair<int, int>> cross_edges;
vector<pair<int, int>> back_edges;
void BFS(digrafo g, int raiz){
  queue<int> q;
  q.push(raiz);
  vector<bool> visitados(g.size(), 0);
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
      }else{
        //si encuentro un nodo que ya visite previamente, se trata de una cross o backedge
        //Para saber si es backedge o crossedge, basta con ver que el nodo al que estoy llegando no forme parte de los ancestros del nodo actual.
        //primero, me deshago del caso problematico en que podria ser backedge: si el nodo al que estoy llegando es la raiz de una, entonces es backedge,
        //pues estoy yendo a un ancestro. La raiz es ancestro de todos
        if (vecino == raiz) {
          back_edges.push_back(make_pair(nodo, vecino));
        }else{
          //aun cabe la posibilidad de que sea back edge, si ocurre que el vecino es ancestro no trivial del nodo en exploracion
          int ancestro = padres[nodo - 1];
          while (ancestro != vecino and ancestro != raiz) {
            ancestro = padres[ancestro - 1];
          }
          //va a salir del while si o si, porque en algun momento algun nodo tendra como ancestro a la raiz, si no encuentro ancestro no trivial
          if (ancestro != raiz) {
            //si al salir del while encontre un ancestro que es distinto del trivial, se trata de una back edge
            back_edges.push_back(make_pair(nodo, vecino));
          }else{
            //si llegue hasta el nodo raiz sin encontrar ancestros, entonces no hay ancestro no trivial, y se trata de una cross edge
            cross_edges.push_back(make_pair(nodo, vecino));
          }
        }
      }
    }
    //una vez visite a todos los vecinos, considero al nodo actual como explorado, y lo pinto de negro. Lo saco de la cola
    q.pop();
  }
  //veo las distancias al nodo fuente
  cout << endl;
  cout << "Distancias desde la raiz: " << endl;
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
  int raiz = 1; //el nodo raiz
  BFS(g, raiz);
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
