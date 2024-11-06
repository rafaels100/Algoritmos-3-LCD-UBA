#include <vector>
#include <map>
#include <iostream>
#include <stack>
#include <algorithm>

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
          {1, vector<int>{2, 3, 4, 5}},
          {2, vector<int>{1, 3}},
          {3, vector<int>{1, 2, 5}},
          {4, vector<int>{1, 5, 6}},
          {5, vector<int>{1, 3, 4}},
          {6, vector<int>{4}}
          };
          
vector<bool> visitados(g.size(), 0);
vector<int> padres(g.size(), -1);
vector<pair<int, int>> tree_edges;
vector<pair<int, int>> back_edges;
vector<bool> finalizados(g.size(), 0);
stack<int> stk;
void DFS(grafo g, int nodo){
  visitados[nodo - 1] = true;
  stk.push(nodo);
  for (int vecino : g[nodo]) {
    if (!visitados[vecino - 1]) {
      //si el nodo al que estoy llegando es blanco, es decir aun no lo habia visitado, se trata de una tree edge
      padres[vecino - 1] = nodo;
      tree_edges.push_back(make_pair(nodo, vecino));
      DFS(g, vecino);
    }else if (padres[nodo - 1] != vecino and !finalizados[vecino - 1]){
      //si estoy llegando a una arista que ya habia visitado antes que NO es mi padre, se trata de un candidato a backedge.
      //Para descartar las que no son backedge, me basta con ver si dicho nodo es negro o gris. Si es gris, es decir, aun no esta finalizada su exploracion,
      //entonces es backedge. Si es negro, significa que ya lo habia terminado de explorar, y lo que estoy viendo entonces es un duplicado de arista que ya habia clasificado
      //como treeedge o backedge en un momento previo. (Duplicado en el sentido de que es la misma arista (u, v), solo que con los extremos cambiados de lugar, (v, u). 
      //(En grafos son lo mismo)
      back_edges.push_back(make_pair(nodo, vecino));
      //encontrar una backedge en DFS sobre grafo es encontrar un ciclo en el grafo original
      cout << "Se ha detectado un ciclo:" << endl;
      vector<int> desapilados;
      cout << "El ciclo es: ";
      while (stk.top() != vecino) {
        cout << stk.top() << " ";
        desapilados.push_back(stk.top());
        stk.pop();
      }
      cout << stk.top() << endl;
      //vuelvo a apilar a los desapilados, en sentido contrario a como los saque
      for (int i = desapilados.size() - 1; i >= 0; i--) {
        stk.push(desapilados[i]);
      }
    }
    //si no entro a ninguno de los casos anteriores, significa que no es una tree edge ni una backedge. Esto no es posible en DFS sobre grafo, son las unicas dos posibilidades.
    //Ocurre que encontre un 'duplicado' de arista, algo que ya esta en mi arbol DFS como tree edge o backedge, solo que de forma (u, v) en vez de (v, u). 
    //Esto es asi por la implementacion de la lista de adyacencias, que 'duplica' las aristas en grafo, pues tenemos tanto (u, v) como (v, u), cuando en realidad estas son lo mismo
  }
  finalizados[nodo - 1] = true;
  stk.pop();
  return;
}

int main(){
  //seteo a 1 como la raiz del arbol DFS, por lo tanto es su propio padre
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
  return 0;
}
