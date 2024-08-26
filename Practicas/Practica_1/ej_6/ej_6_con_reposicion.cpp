#include <iostream>
#include <vector>
#include <math.h>

/*
EL problema es el del cambio con reposicion de monedas.
Tenemos un conjunto C de monedas/billetes con distintas denominaciones, y podemos usar infinita cantidad de dichas denominaciones. El objetivo
es determinar la minima cantidad de monedas necesarias para dar ese monto, de ser posible.
*/

using namespace std;
vector<int> B = {5, 3, 2};
int c = 11;
int INF = 1000;
/*
SEMANTICA FUNCION OBJETIVO:
f(i): Me dice la minima cantidad de billetes que necesito usar de un conjunto C para alcanzar el monto i si se pueden usar infinitos billetes
Parametros:
i pert N>=0, objetivo monto a alcanzar
*/
int contador = 0;
int f(int i){
  contador++;
  if (i == 0) {
    return 0;
  }
  if (i < 0) {
    return INF;
  }
  int min = INF;
  int candidato;
  for (int elem : B) {
    candidato = 1 + f(i - elem);
    if (candidato < min) {
      min = candidato;
    }
  }
  return min;
}
/*
HOW IT WORKS:
En cada llamado se pregunta cual de todos estos llamados es el que genera un minimo. 
Luego va breadth first haciendose esa pregunta, y en algun momento alguno de ellos puede lograr devolver un 0, lo que hace que al volver
al loop for que se esta evaluando, se le sume + 1 y el minimo sea 1. Entonces la funcion para ese llamado devuelve 1.
Ese minimo ganador luego 'sube de nivel' y pasa a competir con los otros llamados para ver quien realmente acumulo el minimo cuando
bajo por sus respectivas ramas. De esa comparacion surge un nuevo minimo, que cuando suba de nivel se le va a sumar un + 1, y pasara a competir
con otros llamados que acumularon minimos previamente.
Asi vamos de abajo hacia arriba, justo como dibujamos en el arbol recursivo en [9] (I_rec_rec)
*/

//COMPLEJIDAD: O(N**n)
//N: cantidad de elementos
//n: nivel mas profundo que alcanza el arbol. Viene dado por la cantidad de veces que la moneda de denominacion mas chica entra en el monto objetivo.

int main(){
  cout << f(c) << endl;
  cout << "Complejidad teorica: " << pow(3, c / 2) << "\n" << "Complejidad experimental: " << contador << "\n";
  return 0;
}
