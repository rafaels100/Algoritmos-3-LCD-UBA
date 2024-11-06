#include <vector>
#include <map>
#include <iostream>
#include <stack>

using namespace std;

using grafo = map<int, vector<int>>;

/*
La idea detras de este cubren es tener un vector que inicialmente tiene todos 0, y cada vez que encontramos otra forma de llegar al nodo,
incrementamos en 1. Es decir, cuando detectamos un ciclo, aumentamos en 1 a todos los involucrados en el ciclo (excepto el primero de todos), pues
al haber encontrado una backedge, es como si hubiese encontrado otra forma de llegar a ese nodo, y no solo eso, tambien encontre una forma de llegar
a todos los que estan cubiertos por esa backedge.

Una arista sera puente si existe una sola manera de llegar al nodo, es decir, son las aristas que de un padre llegan a un hijo que tiene 0 formas
distintas de llegar a el, son los nodos que nunca incrementaron con este procedimiento (excepto la raiz, nunca incrementa pero no puede ser hija de nadie,
asi que es valido este criterio de deteccion de puentes).
*/
/*
grafo g = {
          {0, vector<int>{1, 2, 3}},
          {1, vector<int>{0, 2}},
          {2, vector<int>{0, 1, 4}},
          {3, vector<int>{0, 4, 5}},
          {4, vector<int>{0, 2, 3}},
          {5, vector<int>{3}}
          };
*/
grafo g = {
          {1, vector<int>{2, 3, 7}},
          {2, vector<int>{1, 4, 5, 8, 9}},
          {3, vector<int>{1, 6, 7}},
          {4, vector<int>{2, 6, 8}},
          {5, vector<int>{2}},
          {6, vector<int>{3, 4}},
          {7, vector<int>{1, 3}},
          {8, vector<int>{2, 4, 9}},
          {9, vector<int>{2, 8}}
          };
          
vector<bool> visitados(g.size(), 0);
vector<int> padres(g.size(), -1);
vector<pair<int, int>> tree_edges;
vector<pair<int, int>> back_edges;
vector<bool> finalizados(g.size(), 0);
vector<int> backedges_entrantes(g.size(), 0);
vector<int> backedges_salientes(g.size(), 0);
void DFS(grafo g, int nodo){
  cout << nodo << " ";
  //exploro el vecinadario
  for (int vecino : g[nodo]) {
    if (!visitados[vecino - 1]) {
      tree_edges.push_back(make_pair(nodo, vecino));
      visitados[vecino - 1] = true;
      padres[vecino - 1] = nodo;
      DFS(g, vecino);
    }else if (padres[nodo - 1] != vecino and !finalizados[vecino - 1]) {
      //encontre una backedge
      back_edges.push_back(make_pair(nodo, vecino));
      backedges_salientes[nodo - 1] += 1; 
      backedges_entrantes[vecino - 1] += 1; 
    }
      //en el arbol dfs solo hay back y treeedges. No podria ocurrir que haya una forward edge, porque como las flechas van y vienen, la busqueda hubiese tomado
      //la flecha de vuelta al llegar al nodo final, y esa arista hubiese sido clasificada como backedge
      //tampoco podria ocurrir una cross edge, porque como las flechas van y vienen, al llegar al nodo de salida hubiese tomado esa arista, y esa parte del arbol
      //que seria otra 'seccion', en realidad hubiese sido una prolongacion de la seccion del arbol de donde deberia haber salido la cross edge. Hubiese sido clasif como tree edge.
      //Por eso es que las unicas veces que no se cumplen las condiciones anteriores es cuando encuentre un 'duplicado' (u, v) de una arista (v, u) que ya vi
  }
  finalizados[nodo - 1] = true;
  return;
}

vector<int> cubren(g.size(), -1);
int cubriendo(int nodo){
  visitados[nodo - 1] = true;
  if (cubren[nodo - 1] != -1) {
    return cubren[nodo - 1];
  }
  int res = 0;
  res += backedges_salientes[nodo - 1] - backedges_entrantes[nodo - 1];
  for (int vecino : g[nodo]) {
    if (!visitados[vecino - 1] and vecino != padres[nodo - 1] and !finalizados[vecino - 1]) {
      res += cubriendo(vecino);
    }
  }
  finalizados[nodo - 1] = true;
  cubren[nodo - 1] = res;
  return cubren[nodo - 1];
}

int main(){
  //el nodo 1, que le corresponde la posicion 0 en el array de padres, es su propio padre
  padres[0] = 1;
  //lo marco como visitado
  visitados[0] = 1;
  DFS(g, 1);
  cout << endl;
  cout << "Los padres de cada nodo por DFS son:";
  for (int i = 0; i < padres.size(); i++) cout << "(" << i + 1 << ", " << padres[i] << "), ";
  cout << endl;
  cout << "Las tree edges son:" << endl;
  for (pair<int, int> edge : tree_edges) cout << "(" << edge.first << ", " << edge.second << "), ";
  cout << endl;
  cout << "Las back edges son:" << endl;
  for (pair<int, int> edge : back_edges) cout << "(" << edge.first << ", " << edge.second << "), ";
  cout << endl;
  //las aristas que son puente son las que terminan en un 0
  //la raiz tiene 0 pero no tiene padre, asi que no tiene ninguna arista que le llegue, no importa que el nodo raiz sea 0 en cubren, siempre sera asi.
  /*
  for (int i = 1; i < cubren.size(); i++) {
    if (cubren[i] == 0) {
      cout << "La arista (" << padres[i] << ", " << i << ")" << " es puente" << endl;
    }
  }
  */
  //reinicializo el vector de visitados y finalizados, para el algoritmo cubriendo
  fill(finalizados.begin(), finalizados.end(), 0);
  fill(visitados.begin(), visitados.end(), 0);
  cubriendo(1);
  for (int i = 0; i < g.size(); i++) {
    cout << "Cubren de " << i + 1 << ": " << cubren[i] << endl;
  }
  //los puentes son aquellas nodo a los que le llega una arista y siguen siendo 0. La raiz no puede ser, porque no le 'llega' ninguna arista
  for (int i = 1; i < g.size(); i++) {
    if (cubren[i] == 0) {
      cout << "La arista " << "(" << padres[i] << ", " << i + 1 << ") " << "es puente" << endl; 
    }
  }
  return 0;
}
