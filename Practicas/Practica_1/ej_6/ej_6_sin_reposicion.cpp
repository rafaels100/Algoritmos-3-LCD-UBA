#include <iostream>
#include <vector>
#include <math.h>

/*
EL problema es el del cambio sin reposicion de monedas.
Tenemos un conjunto C de monedas/billetes con distintas denominaciones, y podemos usar solo las monedas que tenemos en dicho conjunto. El objetivo
es determinar la minima cantidad de monedas necesarias para dar ese monto, de ser posible.
*/

using namespace std;
vector<int> B = {5, 3, 2};
int n = B.size();
int c = 9;
int INF = 1000;
/*
SEMANTICA FUNCION OBJETIVO:
f(i): Me dice la minima cantidad de billetes que necesito usar de un conjunto C para alcanzar el monto i si se pueden usar infinitos billetes
Parametros:
i pert N>=0, objetivo monto a alcanzar
*/
/*
int contador = 0;
int f(int i, int j){
  contador++;
  if (j == 0) {
    return 0;
  }
  if (j > 0 and i < 0) { //me quede sin monedas para chequear y aun no llegue a j
    return INF;
  }
  return min(f(i - 1, j), 1 + f(i - 1, j - B[i]));
}
Pero esto, si bien me da la minima cantidad de monedas necesarias cuando el cambio existe, o me da INF si el cambio no existe, no es lo que pide el ejercicio 6,
pues no estoy teniendo en cuenta el minimizar la perdida al dar el cambio.
*/

//mejor:
int min_cant = INF;
int g(int i, int j, int contador){
  if (j <= 0) {
    if (abs(j) < min_cant) {
      min_cant = contador;
    }
    return abs(j);
  }
  if (j > 0 and i < 0) { //me quede sin monedas para chequear y aun no llegue a j
    return INF;
  }
  return min(g(i - 1, j, contador), g(i - 1, j - B[i], contador + 1));
}

/*
HOW IT WORKS:
Como un knapsack en el cual vamos actualizando por la minima cantidad de monedas necesarias cada vez
*/

int main(){
  //cout << f(n-1, c) << endl;
  //cout << "Complejidad teorica: " << pow(2, n) << "\n" << "Complejidad experimental: " << contador << "\n";
  cout << g(n-1, c, 0) << " " << min_cant << "\n";
  return 0;
}
