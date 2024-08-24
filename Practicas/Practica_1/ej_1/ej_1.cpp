#include <iostream>
#include <vector>

using namespace std;
//declaro las variables globales
//la cantidad de elementos
int n = 3;
//el conjunto de elementos 
vector<int> C = {6, 12, 6};
//contador de llamados recursivos
int contador = 0;
/*
FUNCION OBJETIVO:
ss(i, j): Me dice si puedo lograr j usando i elementos del conjunto C.
En terminos de indices, se pregunta si se puede lograr j si me permito usar los elementos [0 -> i) del array C
*/

bool ss(int i, int j){
    contador++;
    //chequeo si llegue al final
    if (i == -1) {
      if (j == 0) {
        return true;
      }
      return false;
    }
    //regla de factibilidad por elecciones hechas
    if (j < 0) {
      return false;
    }
    
    return ss(i-1, j) or ss(i-1, j - C[i]);
}

int main(){
  int k = 13;
  cout << ss(n - 1, k) << "\n";
  cout << "Cantidad de llamados recursivos: " << contador << "\n";
  return 0;
}
