#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;
int n;
int INF = 1000;
using grafo = map<int, vector<int>>;

/*
En BFS con grafo, tenemos dos tipos de aristas:
tree edges: las aristas que pertenecen al arbol BFS
cross edges: las aristas que no pertenecen al arbol BFS
Este script deja duplicadas las crossedges, pero las identifica
*/


vector<bool> visitados;
vector<int> distancias;
void BFS(grafo g, int raiz){
  queue<int> q;
  q.push(raiz);
  distancias[raiz - 1] = 0;
  visitados[raiz - 1] = true;
  while (!q.empty()) {
    int nodo = q.front();
    for (int vecino : g[nodo]) {
      if (!visitados[vecino - 1]) {
        //si no lo habia visto antes, estaba blanco, lo pinto de gris, lo visito
        visitados[vecino - 1] = true;
        distancias[vecino - 1] = distancias[nodo - 1] + 1;
        //lo agrego a la cola para explorarlo luego
        q.push(vecino);
      }
    }
    //una vez visite a todos los vecinos, considero al nodo actual como explorado, y lo pinto de negro. Lo saco de la cola
    q.pop();
  }
  return;
}

int main(){
  grafo g;
  cin >> n;
  visitados.resize(n ,0);
  distancias.resize(n ,INF);
  int a = 1;
  while (a < n) {
  	if (g.count(a) == 0) {
  		g.insert({a, vector<int>{a+1}});
  	}else{
  		g[a].push_back(a+1);
  	}
  	if (g.count(a + 1) == 0) {
  		g.insert({a + 1, vector<int>{a}});
  	}else{
  		g[a+1].push_back(a);
  	}
   a++;
  }
  //agrego las aristas correspondientes a los atajos
  int atajo;
  for (int i = 1; i <= n; i++) {
    cin >> atajo;
    if ((atajo - i) > 1) { //las agrego solo si mejoran el salto a otras aulas, es decir, si van mas alla de su oficina inmediatamente vecina
      g[i].push_back(atajo);
      g[atajo].push_back(i);
    }
  }
  /*
  for (auto const &[key, val] : g) {
  	cout << key << " : ";
  	for (int elem : val) cout << elem << " ";
  	cout << endl;
  }
  */
  int raiz = 1;
  BFS(g, raiz);
  //veo las distancias al nodo fuente
  for (int i = 0; i < distancias.size(); i++) {
    //cout << "(" << i + 1 << ", " << distancias[i] << "), ";
    cout << distancias[i] << " ";
  }
  cout << endl;
  return 0;
}
