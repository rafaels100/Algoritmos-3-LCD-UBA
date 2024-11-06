#include <vector>
#include <map>
#include <iostream>
#include <stack>

using namespace std;

using digrafo = map<int, vector<int>>;

/*
CONCEPTOS UTILES:
Antecesor: cuando empezamos a recorrer en profundidad desde la raiz, podemos bajar por cierta rama. Digamos que tenemos 3 ramas, 3 hijos de la raiz.
Bajamos en profundidad por la rama de la izquierda, y llegamos a una buena profundidad, digamos, 10 niveles. Todos esos nodos forman parte de esa rama,
y son todos ancestros no solo de la raiz, sino del primer hijo de la izquierda, y a su vez los que estan por debajo del hijo del hijo de la izquierda
tienen por ancestro a ese hijo de hijo, y asi, hasta llegar a los nodos hoja, que no son ancestros de nadie, pero tienen de ancestros a todos los que
pertenecen a esa rama iniciada por el hijo de la izquierda.

Cuando terminamos de explorar esta rama de la izquierda, hacemos backtracking y llegamos a la raiz, listos para explorar a los otros dos hijos en profundidad.
Resulta que este hijo del medio sera el ancestro de todos los nodos que pertenezcan a esa rama del medio, con el mismo razonamiento que hicimos antes.
Asi, estos nodos tienen como ancestro al hijo del medio, pero NO tienen como ancestro a nadie de la rama izquierda, de los nodos que descubrimos al principio, cuando
fuimos por profunidad por el hijo de la izquierda.

Lo mismo pasara con el hijo de la derecha, sera el ancestro de todos los que spamean de la rama de la derecha.

NOTAR que la raiz es ancestro de TODOS, tanto de los nodos de las branches de la izquierda, centro y derecha.

El concepto de sucesor es lo contrario de ancestro, no necesitamos analizar nada, solo decimos que si v es ancestro de w, entonces w es sucesor de v, es una cuestion
sintactica.
*/

/*
En un digrafo, al hacer DFS podemos tenes todos los tipos de aristas:
Tree edges: son las aristas que forman parte de mi arbol DFS
Back edges: son las aristas que van de un nodo a su ancestro en el arbol DFS, es decir, que van de un nodo gris a uno gris, del nodo al que acabamos de descubrir
a otro que habiamos descubierto previamente pero que aun no habiamos terminado de explorar.
Forward edges: son las aristas que van de un nodo a su sucesor en el arbol DFS, es decir, van de un gris a un negro. El hecho de que vayamos de un ancestro a un sucesor
hace que el tiempo de descubrimiento de una arista (u, v) sea u.d < v.d, y que u.f > v.f
Cross edges: son las aristas que no van ni a un nodo nuevo, ni a un sucesor, ni a un antecesor. Si bien van de un gris a un negro como las forward eges, la diferencia
es que estas 'cruzan' de una rama de la exploracion a otra, es decir, ya terminamos de explorar en profundidad una rama y de repente encontramos algo que la conecta con otra.
El hecho de que encontremos este nodo de nuevo luego de haber finalizado de explorar su ancestro mas lejano, hace que una arista (u, v) sea u.d > v.d, y que u.f > v.f
Es decir, lo que nos ayuda a diferenciar una forward de una cross es el tiempo de descubrimiento.

NOTAR que los digrafos admiten cross edges porque las edges no tienen doble direccion. Si asi fuera, al ir en profundidad por una rama, encontrariamos esa edge que
esta conectando a la otra rama, y hariamos el salto ahi mismo, y toda esa rama pasaria a formar parte de la rama en profundidad actual.

Por eso tampoco admiten forward edges. Si asi fuera, como hay doble direccion, esa edge pasaria a formar parte del arbol DFS, pues la hubiesemos descubierto
cuando explorabamos el nodo al que estariamos llegando desde un sucesor, si fuera digrafo.

Este tipo de pensamiento de mirar el digrafo y preguntarme que es lo que hubiese pasado en la busqueda si esta arista hubiese permitido doble direccion,
me ayuda a ver por que cierto tipo de aristas no aparecen en los grafos pero si en los digrafos.
*/

digrafo g = {
          {0, vector<int>{1, 2, 3}},
          {1, vector<int>{2}},
          {2, vector<int>{}},
          {3, vector<int>{4, 5}},
          {4, vector<int>{0, 2}},
          {5, vector<int>{}}
          };
          
vector<bool> visitados(g.size(), 0);
vector<int> padres(g.size(), -1);
vector<pair<int, int>> tree_edges;
vector<pair<int, int>> back_edges;
vector<pair<int, int>> forward_edges;
vector<pair<int, int>> cross_edges;
int t = 0;
vector<int> t_d(g.size(), -1);
vector<int> t_f(g.size(), -1);
stack<int> stk;
void DFS(digrafo g, int nodo){
  //cout << nodo << " ";
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
    }else{
      if (t_f[vecino] == -1) { 
      //si el nodo al que estoy volviendo a visitar aun no ha finalizado su exploracion, entonces es un ancestro del nodo actual, y se trata de una backedge
      back_edges.push_back(make_pair(nodo, vecino));
      cout << "Se ha detectado un ciclo:" << endl;
      cout << "La cantidad de nodos stackeados es: " << stk.size() << endl;
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
      }else{
        //si el nodo al que estamos llegando ya habia finalizado su tiempo de exploracion (es negro), entonces puede ser forward edge o crossedge
        //depende de su tiempo de descubrimiento t_d
        if (t_d[nodo] < t_d[vecino]) {
          //estamos viendo a un sucesor, al que pudimos llegar pero ya habia finalizado su exploracion. Por eso el tiempo de descubrimiento del nodo
          //actual es menor al tiempo del descubrimiento del nodo al que estamos llegando, pues ya lo vimos antes, pero no habiamos terminado de explorar al nodo actual
          forward_edges.push_back(make_pair(nodo, vecino));
        }else{
          //en caso contrario, tenemos que t_d[nodo] > t_d[vecino], es decir, estamos 'cruzando' de una rama a otra de la profundidad, puesto que ya habiamos terminado
          //de explorar al nodo al que estamos llegando, pero resulta que el tiempo en que lo descubrimos tambien fue anterior al tiempo en que descubrimos al nodo actual,
          //lo que indica que ya habiamos terminado de explorar en profundidad la branch a la que el nodo al que estoy llegando pertenece
          cross_edges.push_back(make_pair(nodo, vecino));
        }
      }
    }
  }
  t_f[nodo] = t;
  //finalizar de explorar un nodo tambien hace crecer en una unidad el tiempo
  t++;
  //desapilo el nodo, una vez termine de explorarlo
  //cout << "Desapilo: " << stk.top() << endl;
  stk.pop();
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
