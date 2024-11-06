#include <vector>
#include <map>
#include <iostream>
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
void DFS(grafo g, int nodo){
  cout << nodo << " ";
  visitados[nodo - 1] = true;
  for (int vecino : g[nodo]) {
    if (!visitados[vecino - 1]) {
      padres[vecino - 1] = nodo;
      tree_edges.push_back(make_pair(nodo, vecino));
      DFS(g, vecino);
      //si estoy llegando a una arista que ya habia visitado antes que NO es mi padre, se trata de un candidato a backedge.
      //Para descartar las que no son backedge, me basta con ver si dicho nodo es negro o gris. Si es gris, es decir, aun no esta finalizada su exploracion,
      //entonces es backedge. Si es negro, significa que ya lo habia terminado de explorar, y lo que estoy viendo entonces es un duplicado de arista que ya habia clasificado
      //como treeedge en un momento previo. (Duplicado en el sentido de que es la misma arista (u, v), solo que con los extremos cambiados de lugar, (v, u). En grafos son lo mismo)
    }else if (padres[nodo - 1] != vecino and !finalizados[vecino - 1]){
      back_edges.push_back(make_pair(nodo, vecino));
    }else{
      //encontre un 'duplicado' de arista, algo que ya esta en mi arbol DFS como tree edge o backedge, solo que de forma (u, v) en vez de (v, u). Puedo comprobarlo, buscando en 
      //la lista de tree_edges la arita (u, v), y en caso de no estar ahi, deberia ser una backedge, tambien de la forma (u, v)
      auto it = find(tree_edges.begin(), tree_edges.end(), make_pair(vecino, nodo));
      cout << "Encontre una arista 'duplicado': (" << nodo << ", " << vecino << ") ";
      if (it != tree_edges.end()) {
        cout << "Encontrada! " << "(" << it->first << ", " << it->second << ")" << endl;
      }else{
        cout << "No encontrada como treedge. Debe ser backedge. Buscandola: ";
        auto it = find(back_edges.begin(), back_edges.end(), make_pair(vecino, nodo));
        if (it != back_edges.end()) {
          cout << "Encontrada! " << "(" << it->first << ", " << it->second << ")" << endl;
        }else{
          cout << "Tampoco encontrada como backedge. Error en la implementacion o en mi entendimiento de la teoria" << endl;
        }
      }
    }
  }
  finalizados[nodo - 1] = true;
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
