#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/*
IDEA:
La idea es pararme en un lugar j del array y ver si puedo extender un LDS a partir de todos los i elementos anteriores a j.
Puedo extender si para algun i perteneciente a [0 -> j), ocurre que s[j] < s[i]. Extiendo agarrando la solucion optima que tuve para i, y le sumo +1.
Luego me fijo el maximo entre todos esas posibles soluciones que puedo extender.

Asi obtengo, para cada posicion i del vector, el largo de la maxima subsecuencia que puedo crear si considero todos los elementos de [0->i].
Para averiguar cual es el largo de la subsecuencia mas grande que puedo crear, calculo el maximo entre todos estos resultados, estas soluciones optimas.
*/

void LDS_BU(vector<int> &s){
  //inicializo el Dynamic Programming Array con la solucion optima minima, esta es 1, que es el largo de la subsecuencia mas larga si solo
  //considero el elemento actual.
  vector<int> DPA(s.size(), 1);
  //acutalizo la DPA en base a la idea
  //me paro en un elemento j
  for (int j = 0; j < s.size(); j++){
    //miro los elementos de 0 a j buscando por soluciones que pueda extender
    for (int i = 0; i < j; i++) {
      //si puedo extender una solucion optima con mi elemento j
      if (s[j] < s[i])  {
        //veo si esa solucion optima en i que estoy puediendo extender (+1) supera al optimo actual
        DPA[j] = max(DPA[j], DPA[i] + 1);
      }
    }
  }
  for (int i = 0; i < s.size(); i++) cout << DPA[i] << " ";
  cout << endl;
  cout << "La subsecuencia decreciente mas larga que existe en el array es: " << *max_element(DPA.begin(), DPA.end()) << endl;
  return;
}
/*
HOW IT WORKS:
NOTA: Chequear la idea antes de leer esta implementacion.
En la implementacion, no me fijo el maximo de todo al mismo tiempo, sino que voy guardando el maximo que encuentro en DPA[j] a medida
que recorro los i elementos entre 0 y j.
*/

int main(){
vector<int> s = {-1, 3, 4, 5, 2, 2, 2, 2};
  LDS_BU(s);
  return 0;
}
