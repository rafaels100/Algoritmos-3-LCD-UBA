#include <iostream>
#include <vector>

using namespace std;
int N = 4;
const int N_ = 4;
int P[N_] = {3, 3, 3, 2};
int B[N_] = {60, 60, 60, 60};
int INF = 1000;
int DPT[N_][15]; //necesito peso_tot + 1 valores
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
  if (DPT[i][j]){
    return DPT[i][j];
  }
  int noTomar = f(i - 1, j);
  int tomar = f(i - 1, j - P[i]) + B[i];
  DPT[i][j] = max(noTomar, tomar);
  return DPT[i][j];
}

vector<bool> optimo(N, 0);
void reconstr_sols(int i, int p){
  if (i == 0) {
    optimo[0] = (p >= P[0]) ? true : false; //si todavia nos quedaba lugar para meter el unico item que falta, lo debimos haber metido
    //si no nos quedaba lugar, entonces no lo elegimos, y seteamos false.
    //termino para no evaluar a la DPT con numeros negativos. Ya termine con todos los niveles del arbol invertido.
    for (int i = 0; i < optimo.size(); i++) cout << optimo[i] << " ";
    cout << endl;
    return;
  }
  //si daba lo mismo cambiar de columna o no cambiar, significa que hay dos soluciones validas. Para ver si daba lo mismo o no, comparo 
  //el valor de la solucion optima si elijo tomar, con el valor de la solucion optima de no tomar sumado al beneficio de tomar. Si son iguales,
  //significa que hay mas de una forma de lograr el maximo beneficio posible para la capacidad p permitiendome usar i items, y hubo un empate entre estos nodos,
  //por lo que tengo que seguir ambas ramas ya que tienen soluciones optimas
  if (DPT[i - 1][p] == (DPT[i - 1][p - P[i]] + B[i])) {
    //por un lado me voy por la rama de tomar el item
    optimo[i] = 1;
    reconstr_sols(i-1, p - P[i]);
    //y luego me voy por la rama de no tomarlo
    optimo[i] = 0;
    //dejo el peso como esta, ya que no se eligio el item actual en el camino optimo
    reconstr_sols(i-1, p);
    return;
  }
  //si ocurre que no da lo mismo el camino de tomar o no tomar, significa que hay solo un camino posible en este nivel del arbol
  if (DPT[i][p] != DPT[i - 1][p]) {
    //si ocurre que i > 0, estamos considerando al menos un item, y debemos ver si me mantengo en la misma columna (no elegi el item i+1) o si cambio de columna (si lo elegi) 
    optimo[i] = 1;
    p -= P[i];
    reconstr_sols(i-1, p);
  }else {
    optimo[i] = 0;
    //dejo el peso como esta, ya que no se eligio el item actual en el camino optimo
    reconstr_sols(i-1, p);
  }
  return;
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
  
  //a partir de la DPT puedo reconstruir la solucion optima elegida. 
  //La idea es, empezando desde el beneficio maximo obtenido al llamar a la funcion con f(N - 1, P_tot),
  //ir a la fila anterior, a las columnas del peso actual (el maximo) (que es el nodo hijo de no haber tomado el item),
  //y la columna del peso actual - el peso del objeto de la fila en la que estoy (en este caso, el item i = N - 1)
  //si el beneficio que estoy viendo es igual al beneficio que tenia en la celda (i = N - 2, P_tot), significa que
  //gano el nodo que no tomo el item i = N - 1, por lo que puedo estar seguro que no se tomo ese item.
  //Pongo 0 en la posicion N - 1 de un vector de booleanos que me ayudara a identificar que items se tomaron.
  //En caso de que los beneficios sean diferentes, sabre que si se tomo el item. Pongo 1 en el vector de bools en i = N - 1
  
  //MUCHAS SOLUCIONES, MUCHOS CAMINOS
  //implementando esta idea en una funcion recursiva puedo reconstruir todas las soluciones tan solo usando la DPT:
  reconstr_sols(N-1, capacidad);
}
