#include <vector>
#include <map>
#include <iostream>

using namespace std;

using grafo = map<int, vector<int>>;

grafo g = {
          {0, vector<int>{1, 2, 3}},
          {1, vector<int>{2}},
          {2, vector<int>{}},
          {3, vector<int>{4, 5}},
          {4, vector<int>{0, 2}},
          {5, vector<int>{}}
          };
          
vector<bool> visitados(g.size(), 0);
vector<int> padres(g.size(), -1);
vector<pair<int, int>> back_edges;
int t = 0;
vector<int> t_d(g.size(), -1);
vector<int> t_f(g.size(), -1);
void DFS(grafo g, int nodo){
  cout << nodo << " ";
  visitados[nodo] = true;
  //descubrimos al nodo actual en tiempo t
  t_d[nodo] = t;
  //e incrementamos en una unidad el tiempo. Es como si descubirlo nos llevara una unidad de tiempo
  t++;
  for (int vecino : g[nodo]) {
    if (!visitados[vecino]) {
      padres[vecino] = nodo;
      DFS(g, vecino);
    }else{
      //estamos revisitando un nodo, por lo que se puede tr
      if () {
      
      }
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
  cout << "Las forward edges son:" << endl;
  for (pair<int, int> edge : forward_edges) cout << "(" << edge.first << ", " << edge.second << "), ";
  cout << endl;
  cout << "Las cross edges son:" << endl;
  for (pair<int, int> edge : cross_edges) cout << "(" << edge.first << ", " << edge.second << "), ";
  cout << endl;
  return 0;
}
