#include <vector>
#include <map>
#include <iostream>
#include <stack>

using namespace std;

using grafo = map<int, vector<int>>;

/*
En grafos, vamos a tener solo dos tipos de edges cuando hacemos DFS:
Tree edge: arista que forma parte del arbol DFS
Back edge: arista que esta en el grafo pero que no forma parte del arbol DFS.

Las backedges aparecen cuando visitamos a un nodo que ya habiamos visto, que ya lo hicimos parte del arbol DFS. Como en las aristas de un grafo podemos ir y volver,
no esta claro quien es el antecesor o sucesor. Ambos lo son, pero como vamos de abajo para arriba, decimos que es una backedge.
Por esta razon no tenemos forward edges, ni cross edges.

NOTAR que los digrafos admiten cross edges porque las edges no tienen doble direccion. Si asi fuera, al ir en profundidad por una rama, encontrariamos esa edge que
esta conectando a la otra rama, y hariamos el salto ahi mismo, y toda esa rama pasaria a formar parte de la rama en profundidad actual.
*/

grafo g = {
          {0, vector<int>{1, 2, 3}},
          {1, vector<int>{0, 2}},
          {2, vector<int>{0, 1, 4}},
          {3, vector<int>{0, 4, 5}},
          {4, vector<int>{0, 2, 3}},
          {5, vector<int>{3}}
          };
          
vector<bool> visitados(g.size(), 0);
vector<int> padres(g.size(), -1);
vector<pair<int, int>> tree_edges;
vector<pair<int, int>> back_edges;
int t = 0;
vector<int> t_d(g.size(), -1);
vector<int> t_f(g.size(), -1);
stack<int> stk;
void DFS(grafo g, int nodo){
  cout << nodo << " ";
  visitados[nodo] = true;
  //descubrimos al nodo actual en tiempo t
  t_d[nodo] = t;
  //e incrementamos en una unidad el tiempo. Es como si descubirlo nos llevara una unidad de tiempo
  t++;
  //meto en el stack al nodo que acabo de descubrir
  stk.push(nodo);
  for (int vecino : g[nodo]) {
    if (!visitados[vecino]) {
      padres[vecino] = nodo;
      tree_edges.push_back(make_pair(nodo, vecino));
      DFS(g, vecino);
      //si estoy llegando a una arista que ya habia visitado antes que NO es mi padre, se trata de un candidato a backedge.
      //Para descartar las que no son backedge, me basta con ver el tiempo de descubrimiento.
      //Si el tiempo de descubrimiento del nodo al que estoy llegando es menor que el de salida, entonces
      //es backedge. Sino, es pseudoforward edge o pseudocrossedge, y la descarto
    }else if (padres[nodo] != vecino and t_d[vecino] < t_d[nodo]){
      back_edges.push_back(make_pair(nodo, vecino));
      //muestro el ciclo que encontre
      cout << "Se ha detectado un ciclo:" << endl;
      cout << "La cantidad de nodos stackeados es: " << stk.size() << endl;
      while (stk.top() != vecino) {
        cout << stk.top() << " ";
        //stk.pop();
      }
      cout << stk.top() << endl;
      //stk.pop();
    }
  }
  t_f[nodo] = t;
  //finalizar de explorar un nodo tambien hace crecer en una unidad el tiempo
  t++;
}

int main(){
  padres[0] = 0;
  DFS(g, 0);
  cout << endl;
  cout << "Los padres de cada nodo por DFS son:";
  for (int i = 0; i < padres.size(); i++) cout << "(" << i << ", " << padres[i] << "), ";
  cout << endl;
  cout << "Los tiempos de descubrimiento y de finalizacion de cada nodo por DFS son:";
  for (int i = 0; i < t_d.size(); i++) cout << "(" << t_d[i] << ", " << t_f[i] << "), ";
  cout << endl;
  cout << "Las tree edges son:" << endl;
  for (pair<int, int> edge : tree_edges) cout << "(" << edge.first << ", " << edge.second << "), ";
  cout << endl;
  cout << "Las back edges son:" << endl;
  for (pair<int, int> edge : back_edges) cout << "(" << edge.first << ", " << edge.second << "), ";
  cout << endl;
  return 0;
}
