#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

struct Arista {
  vector<int> e;
  char c;
  int w;
  //default constructor
  Arista() : e(vector<int>(2, -1)) {}; //que la arista empieze y termine en -1 significa que esos nodos no existen, aun no se han seteado los nodos de salida y llegada
  //overload constructors
  Arista(int u, int v) : e(vector<int>{u, v}){};
  Arista(int u, int v, char color) : e(vector<int>{u, v}), c(color){};
  Arista(int u, int v, int peso) : e(vector<int>{u, v}), w(peso){};
};

struct Nodo {
  int n;
  char c;
  //default constructor
  Nodo() : n(-1) {}; //el nodo -1 aun no existe
  //overload constructors
  Nodo(int n) : n(n){};
  Nodo(int n, char color) : n(n), c(color){};
};

//using grafo = map<int, vector<Arista>>;
using grafo = map<int, vector<pair<int, char>>>;


grafo construir_g(vector<pair<int, int>> &l){
  grafo g;
  for (pair<int, int> ari : l) {
    if (g.count(ari.first) == 0) {
      g.insert({ari.first, vector<pair<int, char>>{make_pair(ari.second, 'b')}});
    }else{
      g[ari.first].push_back(make_pair(ari.second, 'b'));
    }
    if (g.count(ari.second) == 0) {
      g.insert({ari.second, vector<pair<int, char>>{make_pair(ari.first, 'b')}});
    }else{
      g[ari.second].push_back(make_pair(ari.first, 'b'));
    }
  }
  return g;
}

bool buscarElem(int elem, vector<int> v){
  return (find(v.begin(), v.end(), elem) != v.end()) ? 1 : 0;
}

vector<int> distancias_a_src(9, -1);
vector<int> padres(9, -1);
vector<int> BFS(grafo g, int src){
  grafo tree;
  queue<int> q;
  q.push(src);
  vector<int> visitados;
  visitados.push_back(0);
  padres[src] = src;
  distancias_a_src[src] = 0;
  while (!q.empty()) {
    int frente = q.front();
    q.pop();
    //descubro a los vecinos
    for (pair<int, char> elem : g[frente]) {
      if (!buscarElem(elem.first, visitados)) {
        visitados.push_back(elem.first);
        padres[elem.first] = frente;
        distancias_a_src[elem.first] = distancias_a_src[frente] + 1;
        cout << "Elem: " << elem.first << " distancia_a_src: " << distancias_a_src[elem.first] << endl;
        q.push(elem.first);
        elem.second = 'g';
      }
    }
    
  }
  return visitados;
}


int main(){
  Arista e0 = Arista();
  cout << e0.e[0] << endl;
  Arista e1 = Arista(2,3);
  Arista e2 = Arista(4,2,'b');
  
  //Puedo pasar de la lista de aristas al grafo. Las voy a poner unidireccionales y en el grafo las duplico
  vector<pair<int, int>> l_ari = {make_pair(1, 2), make_pair(2, 0), make_pair(0, 3), make_pair(0, 5), make_pair(5, 8),
                          make_pair(2, 4), make_pair(0, 4), make_pair(4, 6), make_pair(4, 7)};
  //paso de la lista de aristas al grafo
  grafo g;
  g.insert({0, vector<pair<int, char>>{make_pair(2, 'b')}});
  //cout << g.count(Nodo(2)) << endl;
  //g[2].push_back(Nodo(3));
  //cout << g[2].size() << endl;
  grafo g1 = construir_g(l_ari);
  //pair<int, char> t = make_pair(3,'c');
  //cout << t.first << t.second << endl;
  cout << g1.size() << endl;

  for (auto const& x : g1) {
    cout << x.first << ": ";
    for (auto elem : x.second) cout << "(" << elem.first << ", " << elem.second << "), ";
    cout << endl;
  }
  vector<int> v = {3,1,2,5};
  cout << buscarElem(34, v) << endl;
  vector<int> vs = BFS(g1, 0);
  for (int i = 0; i < vs.size(); i++) cout << vs[i] << " ";
  cout << endl;
  for (int i = 0; i < vs.size(); i++) cout << "(" << i << ", " << distancias_a_src[i] << "), ";
  cout << endl;
  
  cout << "Arbol" << endl;
  for (int i = 0; i < padres.size(); i++) cout << "(" << padres[i] << ", " << i << ")";
  cout << endl;
}
