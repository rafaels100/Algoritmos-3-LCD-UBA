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
int t = 0;
vector<int> t_i(g.size());
vector<int> t_f(g.size());
void DFS(grafo g, int nodo){
  cout << nodo << " ";
  visitados[nodo] = true;
  t_i[nodo] = t;
  t++;
  for (int vecino : g[nodo]) {
    if (!visitados[vecino]) {
      padres[vecino] = nodo;
      DFS(g, vecino);
    }
  }
  t_f[nodo] = t;
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
  for (int i = 0; i < t_i.size(); i++) cout << "(" << t_i[i] << ", " << t_f[i] << "), ";
  cout << endl;
  return 0;
}
