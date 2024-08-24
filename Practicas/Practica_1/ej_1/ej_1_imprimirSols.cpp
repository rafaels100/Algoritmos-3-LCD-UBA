#include <iostream>
#include <vector>

using namespace std;
//declaro las variables globales
//la cantidad de elementos
int n = 3;
//el conjunto de elementos 
vector<int> C = {6, 12, 6};
//la solucion parcial
vector<bool> p(n);
//contador de llamados recursivos
int contador = 0;
/*
FUNCION OBJETIVO:
Queremos minimizar la diferencia entre el numero k y los elementos del conjunto C, con la restriccion de que dicha diferencia debe ser >= 0
*/

bool fact_futura(int i, int j){
  int suma = 0;
  for (int k = 0; k < i; k++) {
    suma += C[k];
  }
  return (suma >= j);
}
void ss(int i, int j){
    contador++;
    //chequeo si llegue al final
    if (i == -1) {
      if (j == 0) {
        //imprimo la solucion
        for (int k = 0; k < n; k++) cout << p[k] << " ";
        cout << "\n";
      }
      return;
    }
    //regla de factibilidad por elecciones hechas
    if (j < 0) {
      return;
    }
    //regla de factibilidad por elecciones a hacer
    if (i > 1 and !fact_futura(i, j)) {
      return;
    }
    
    //en el primer camino no elijo este elemento
    p[i] = 0;
    ss(i-1, j);
    //en el segundo camino si lo elijo
    p[i] = 1;
    ss(i-1, j - C[i]);
    return;
}

int main(){
  int k = 12;
  ss(n - 1, k);
  cout << "Cantidad de llamados recursivos: " << contador << "\n";
  return 0;
}
