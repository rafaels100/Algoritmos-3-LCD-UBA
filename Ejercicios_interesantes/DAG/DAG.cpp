#include <vector>
#include <map>
#include <iostream>
#include <stack>

using namespace std;

using digrafo = map<int, vector<int>>;

/*
Para que haya un ciclo en un digrafo, basta con encontrar una backedge.
Para ello me basta con pintar los nodos de colores: 
Blanco si aun no lo visite
Gris si ya lo visite pero aun no finalize su exploracion
Negro si ya finalize su exploracion

Si encuentro que estoy volviendo a ver un nodo pintado de gris, esto es, un ancestro del nodo actual, que aun no ha terminado su exploracion, entonces es una backedge.
Puedo afirmar que el grafo no admite DAG.
*/
/*
//este tiene un ciclo
digrafo g = {
          {1, vector<int>{2, 3, 4}},
          {2, vector<int>{3}},
          {3, vector<int>{}},
          {4, vector<int>{5, 6}},
          {5, vector<int>{1, 3}},
          {6, vector<int>{}}
          };
*/      
digrafo g = {
          {1, vector<int>{2, 3, 4}},
          {2, vector<int>{3}},
          {3, vector<int>{}},
          {4, vector<int>{5, 6}},
          {5, vector<int>{3}},
          {6, vector<int>{}}
          };
          
vector<bool> visitados(g.size(), 0);
vector<int> padres(g.size(), -1);
vector<pair<int, int>> tree_edges;
vector<bool> finalizados(g.size(), 0);
stack<int> stk;
int cant_ciclos = 0;
void DFS(digrafo g, int nodo){
  //cout << nodo << " ";
  visitados[nodo - 1] = true;
  stk.push(nodo);
  for (int vecino : g[nodo]) {
    if (!visitados[vecino - 1]) {
      padres[vecino - 1] = nodo;
      tree_edges.push_back(make_pair(nodo, vecino));
      DFS(g, vecino);
    }else if (padres[vecino - 1] != nodo and !finalizados[vecino - 1]){
      //si el nodo al que estoy volviendo a visitar aun no ha finalizado su exploracion, entonces es un ancestro del nodo actual, y se trata de una backedge
      //cout << "Se ha detectado un ciclo. El grafo no es DAG" << endl;
      cant_ciclos++;
    }
  }
  //finalize este nodo
  finalizados[nodo - 1] = true;
  //no desapilo al nodo una vez termine de explorarlo, pues si resulta que no hay ciclos, entonces el stack que voy armando con los nodos apilados, al desapilarlo e invertirlo,
  //me dara como debo ubicar a los nodos para que con las tree edges que voy guardando pueda dibujar el DAG
  return;
}

int main(){
  //seteo la raiz en el nodo 1, que le asigno la posicion 0 del array
  padres[0] = 1;
  DFS(g, 1); //corro DFS desde la raiz
  /*
  cout << "Los padres de cada nodo por DFS son:";
  for (int i = 0; i < padres.size(); i++) cout << "(" << i + 1 << ", " << padres[i] << "), ";
  cout << endl;
  cout << "Las tree edges son:" << endl;
  for (pair<int, int> edge : tree_edges) cout << "(" << edge.first << ", " << edge.second << "), ";
  cout << endl;
  */
  if (cant_ciclos != 0) {
    cout << "El grafo NO es DRAG... digo, DAG, pues tiene al menos un ciclo. De hecho tiene " << cant_ciclos << endl;
  }else{
    cout << "El grafo es DAG, y su representacion como tal, en fila, con aristas que van de izquierda a derecha siempre, es: " << endl;
    vector<int> desapilados;
    while (!stk.empty()) {
      desapilados.push_back(stk.top());
      stk.pop();
    }
    //camino en reverso a traves del vector de desapilados para dar el DAG
    for (int i = desapilados.size() - 1; i >= 0; i--) cout << desapilados[i] << " ";
    cout << endl;
    cout << "y las aristas a dibujar son: ";
    for (int i = 0; i < tree_edges.size(); i++) cout << "(" << tree_edges[i].first << ", " << tree_edges[i].second << ") ";
    cout << endl;
  } 
  return 0;
}
