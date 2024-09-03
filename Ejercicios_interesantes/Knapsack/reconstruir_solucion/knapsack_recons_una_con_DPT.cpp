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
  if (DPT[i][j]) {
    return DPT[i][j];
  }
  int noTomar = f(i - 1, j);
  int tomar = f(i - 1, j - P[i]) + B[i];
  DPT[i][j] = max(noTomar, tomar);
  return DPT[i][j];
}


int main(){
  int capacidad = 9;
  int cantItems = N - 1;
  int res = f(cantItems, capacidad);
  cout << "Los pesos de los items de la mochila son:" << "\n";
  for (int elem : P) cout << elem << "kg ";
  cout << "\n";
  cout << "Los beneficios que aporta cada item son: " << "\n";
  for (int elem : B) cout << elem << "$ ";
  cout << "\n";
  cout << "El optimo de beneficio posible utilizando " << N << " items con restriccion de capacidad " << capacidad << "kg es: " << res << "$\n";
  cout << "La Dynamic Programming table es:" << endl;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 15; j++) {
      cout << DPT[i][j] << " ";
    }
    cout << endl;
  }
  
  //a partir de la DPT puedo reconstruir la solucion optima elegida. 
  //La idea es, empezando desde el beneficio maximo obtenido al llamar a la funcion con f(N - 1, P_tot),
  //ir a la fila anterior, a las columnas del peso actual (el maximo) (que es el nodo hijo de no haber tomado el item),
  //y la columna del peso actual - el peso del objeto de la fila en la que estoy (en este caso, el item i = N - 1)
  //si el beneficio que estoy viendo es igual al beneficio que tenia en la celda (i = N - 2, P_tot), significa que
  //gano el nodo que no tomo el item i = N - 1, por lo que puedo estar seguro que no se tomo ese item.
  //Pongo 0 en la posicion N - 1 de un vector de booleanos que me ayudara a identificar que items se tomaron.
  //En caso de que los beneficios sean diferentes, sabre que si se tomo el item. Pongo 1 en el vector de bools en i = N - 1
  
   //NOTA: Este metodo solo funciona para hallar UNA solucion optima. Si hay varias, puedo usar el metodo de la matriz de decisiones 
   //NOTA 2: Con una recursion se pueden obtener todas las soluciones solo con la DPT. Ver archivo knapsack_recons_todas_con_DPT.cpp
  
  int p = capacidad;
  vector<bool> optimo(N);
  for (int i = N - 1; i >= 0; i--) {
    //hay un problema al mirar a los hijos desde el nodo actual, es que cuando lleguemos al nivel i = 0 ya no podremos
    //mirar a sus hijos, pues el i = -1 no esta en la DPT. 
    //El little hack consiste en mirar el peso actual con el que vengo, p. Si ocurre que al llegar al nivel i = 0 tengo un peso
    //p >= al peso del item 0, es decir, la columna j en la que estoy esta a derecha de la columna del peso del objeto i = 0,
    //entonces todavia me quedaba lugar en la mochila para meter ese item, y lo debi haber metido. Pongo 1 en la posicion 0.
    //Si llego con un p que no me permite 'guardar' este primer item, significa que no lo debi haber elegido en primer lugar. Pongo 0 en la posicion 0.
    if (i == 0) {
      optimo[0] = (p >= P[0]) ? true : false; //si todavia nos quedaba lugar para meter el unico item que falta, lo debimos haber metido
      //si no nos quedaba lugar, entonces no lo elegimos. Dejamos al 0 como esta en esa posicion.
      break; //salgo del loop para no evaluar a la DPT con numeros negativos. Ya termine con todos los niveles del arbol invertido.
    }
    //si los beneficios del nivel anterior son distintos a los de este nivel, significa que elegi el item,
    //y la solucion del camino optimo (a futuro) del siguiente nivel en el arbol va a estar en la columna del peso actual menos el peso del item que elegi
    if (DPT[i][p] != DPT[i - 1][p]) {
      optimo[i] = 1;
      p -= P[i];
    }else{
      optimo[i] = 0;
      //dejo el peso como esta, ya que no se eligio el item actual en el camino optimo
    }
  }
  cout << "Una solucion optima es usar los elementos: ";
  for (int i = 0; i < optimo.size(); i++) cout << optimo[i] << " ";
  cout << "con capacidad restante en la mochila de " << (p - optimo[0] * P[0]) << "kg\n";
}
