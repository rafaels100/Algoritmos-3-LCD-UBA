#include <iostream>
#include <vector>

using namespace std;
int N = 4;
const int N_ = 4;
int P[N_] = {3, 3, 3, 2};
int B[N_] = {60, 60, 60, 60};
int INF = 1000;
int DPT[N_][15]; //necesito peso_tot + 1 valores
int deci[N_][15];
int sol_opt[N_] = {0};

/*
f(i, j): f da el maximo beneficio que puedo obtener si me permito
usar los elementos de 0 a i de la mochila, teniendo en cuenta un
limite j de peso que puedo alcanzar.
*/

int f(int i, int j){
  if (j < 0) {
    return -INF;
  }else if(i == -1){
    return 0;
  }
  int noTomar = f(i - 1, j);
  int tomar = f(i - 1, j - P[i]) + B[i];
  if (tomar == noTomar) { 
    //si hay dos soluciones optimas que convergen en este nodo, indico que es indistinto tomar un camino u otro para 
    //hallar una solucion optima. Lo hago con un -1 en la matriz de decisiones
    deci[i][j] = -1;
  }else{
    //si hay un solo camino que nos lleva a un optimo, indico que ese camino es el de la izquierda (no tomar) con 0,
    //o el de la derecha (tomar), con 1
    deci[i][j] = (tomar > noTomar) ? 1 : 0;
  }
  DPT[i][j] = max(noTomar, tomar);
  return DPT[i][j];
}

//funcion para reconstruir las soluciones optimas siguiendo varios caminos
int solu[N_] = {0};
int cant_sols = 0;
void g(int i, int j){
  if (i == -1) {
    for (int elem : solu) {
      cout << elem << " ";
    }
    cout << endl;
    cant_sols++;
    return;
  }
  //hubo un empate entre los nodos, ambos caminos llevan a soluciones optimas
  if (deci[i][j] == -1) {
    solu[i] = 0;
    g(i-1, j);//no tomar ese camino
    solu[i] = 1;
    g(i-1, j - P[i]); //tomar el camino
    return;
  //solo tomar el item lleva a solucion optima
  }else if(deci[i][j] == 1){
    solu[i] = 1;
    g(i-1, j - P[i]);
    return;
  //solo no tomarlo lleva a solucion optima
  }else{
    solu[i] = 0;
    g(i-1, j);
    return;
  }
}

int main(){
  int capacidad = 9;
  int cantItems = N - 1;
  int res = f(cantItems, capacidad);
  cout << res << endl;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 15; j++) {
      cout << DPT[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 15; j++) {
      cout << deci[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
  /*
  RECONSTRUIR TODAS LAS SOLUCIONES CON LA MATRIZ DE DECISIONES
  En la matriz de decision fui registrando las siguientes cosas
  1: Tome el item
  0: No tome el item
  -1: Tanto tomar como no tomar llevan a soluciones optimas
  
  La idea ahora es usar una recursion que va nivel por nivel en el arbol de decisiones, y si encuentra un 1 en deci[i][p], toma la rama derecha (indica que tomo el item),
  si encuentra un 0, toma la rama izquierda (no tomo el item), y si encuentra un -1, toma ambos caminos (hay empate entre los nodos).
  */
  g(cantItems, capacidad);
  cout << "cantidad de soluciones " << cant_sols << endl;
  return 0;
}
