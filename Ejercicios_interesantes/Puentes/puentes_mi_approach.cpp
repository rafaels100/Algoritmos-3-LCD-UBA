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
          {4, vector<int>{2, 8}},
          {5, vector<int>{2}},
          {6, vector<int>{3}},
          {7, vector<int>{1, 3}},
          {8, vector<int>{2, 4, 9}},
          {9, vector<int>{2, 8}}
          };
          
vector<bool> visitados(g.size(), 0);
vector<int> padres(g.size(), -1);
vector<pair<int, int>> tree_edges;
vector<pair<int, int>> back_edges;
vector<bool> finalizados(g.size(), 0);
stack<int> stk;
vector<int> cubren(g.size(), 0);
void DFS(grafo g, int nodo){
  visitados[nodo - 1] = true;
  //meto en el stack al nodo que acabo de descubrir
  stk.push(nodo);
  for (int vecino : g[nodo]) {
    if (!visitados[vecino - 1]) {
      padres[vecino - 1] = nodo;
      tree_edges.push_back(make_pair(nodo, vecino));
      DFS(g, vecino);
      //si estoy llegando a una arista que ya habia visitado antes que NO es mi padre, se trata de un candidato a backedge.
      //Para descartar las que no son backedge, me basta con ver el tiempo de descubrimiento.
      //Si el tiempo de descubrimiento del nodo al que estoy llegando es menor que el de salida, entonces
      //es backedge. Sino, es pseudoforward edge o pseudocrossedge, y la descarto
    }else if (padres[nodo - 1] != vecino and !finalizados[vecino - 1]){
      back_edges.push_back(make_pair(nodo, vecino));
      //muestro el ciclo que encontre
      cout << "Se ha detectado un ciclo:" << endl;
      cout << "La cantidad de nodos stackeados es: " << stk.size() << endl;
      vector<int> desapilados;
      cout << "El ciclo es: ";
      while (stk.top() != vecino) {
        cout << stk.top() << " ";
        desapilados.push_back(stk.top());
        //incremento en uno el cubren de este nodo, pues descubri una forma extra en la que puedo llegar a el, gracias a la backedge y el ciclo que encontre
        cubren[stk.top() - 1] += 1;
        stk.pop();
      }
      cout << stk.top() << endl;
      //vuelvo a apilar a los desapilados, en sentido contrario a como los saque
      for (int i = desapilados.size() - 1; i >= 0; i--) {
        stk.push(desapilados[i]);
      }
    }
  }
  //desapilo el nodo, una vez termine de explorarlo
  finalizados[nodo - 1] = true;
  cout << "Desapilo: " << stk.top() << endl;
  stk.pop();
}

int main(){
  //elijo al nodo 1 como la raiz. Es su propio padre.
  padres[0] = 1;
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
  cout << "Tamanio del stack al finalizar: " << stk.size() << endl;
  for (int elem : cubren) cout << elem << " ";
  cout << endl;
  //las aristas que son puente son las que terminan en un 0
  //la raiz tiene 0 pero no tiene padre, asi que no tiene ninguna arista que le llegue, no importa que el nodo raiz sea 0 en cubren, siempre sera asi.
  for (int i = 1; i < cubren.size(); i++) {
    if (cubren[i] == 0) {
      cout << "La arista (" << padres[i] << ", " << i + 1 << ")" << " es puente" << endl;
    }
  }
  return 0;
}
