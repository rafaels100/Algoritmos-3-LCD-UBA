#include <iostream>
#include <vector>

using namespace std;
/*
El ejercicio consiste en optimizar la ganancia neta en la compra de asteroides. El precio de los asteroides cada dia viene dado por un array.
Solo se puede comprar uno por dia, y no se puede vender si no tenemos stock. Empezamos con 0 de stock.
*/
//variables globales
//precio de los asteroides
vector<int> A = {2,3,5,6};
int n = A.size();

/*
Semantica funcion objetivo:
f(i, j): da la maxima ganancia neta que puedo obtener comerciando i dias, partiendo con j asteroides inicialmente.
*/
int f(int i, int j){
  if (i == n) {
    return 0;
  }
  if (j > 0) { //significa que tengo asteroides para comerciar, puedo no hacer nada, comprar o vender
    int max_cand = max(f(i+1, j), f(i+1, j + 1) - A[i]);
    return max(max_cand, f(i+1, j-1) + A[i]);
    //return max({f(i-1, j), f(i-1, j + 1) - A[i], f(i-1, j-1) + A[i]});
  }else{ //no tengo asteroides para comerciar, solo puedo no hacer nada o comprar
    return max(f(i+1, j), f(i+1, j + 1) - A[i]);
  }
}
/*
HOW IT WORKS:
Es un knapsack en donde elijo o no elijo compar, pero con el extra de que si tengo la posibilidad tambien puedo vender, por lo que a veces
se agrega una rama extra al arbol de llamadas recursivas.
*/
//COMPLEJIDAD: O(3**n)
//Digamos que siempre tengo esas tres posibilidades, si el arbol fuera muy grande

int main(){
  cout << f(0, 0) << endl;
  return 0;
}
