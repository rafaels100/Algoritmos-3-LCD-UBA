#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int n = 8;
vector<int> s =  {7,8,1,2,4,6,3,5};
vector<int> DPA(s.size(), 1);
/*
IDEA:
La idea es pararme en un lugar j del array y ver si puedo extender un LDS a partir de todos los i elementos anteriores a j.
Puedo extender si para algun i perteneciente a [0 -> j), ocurre que s[j] < s[i]. Extiendo agarrando la solucion optima que tuve para i, y le sumo +1.
Luego me fijo el maximo entre todos esas posibles soluciones que puedo extender.

Asi obtengo, para cada posicion i del vector, el largo de la maxima subsecuencia que puedo crear si considero todos los elementos de [0->i].
Para averiguar cual es el largo de la subsecuencia mas grande que puedo crear, calculo el maximo entre todos estos resultados, estas soluciones optimas.
*/

int LDS_BU(vector<int> &s){
  //inicializo el Dynamic Programming Array con la solucion optima minima, esta es 1, que es el largo de la subsecuencia mas larga si solo
  //considero el elemento actual.
  
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
  //for (int i = 0; i < s.size(); i++) cout << DPA[i] << " ";
  return *max_element(DPA.begin(), DPA.end());
}
/*
HOW IT WORKS:
NOTA: Chequear la idea antes de leer esta implementacion.
En la implementacion, no me fijo el maximo de todo al mismo tiempo, sino que voy guardando el maximo que encuentro en DPA[j] a medida
que recorro los i elementos entre 0 y j.
*/
vector<int> sol(n);
void sols(int i){
  if (DPA[i] == 1) {
    sol[i] = 1;
    //for (int elem: sol) cout << elem << " ";
    for (int j = 0; j < n; j++) {
      if (sol[j] == 1){
        cout << s[j] << " ";
      }
    }
    sol[i] = 0;
    cout << endl;
    return;
  }
  for (int j = 0; j < i; j++) {
    if (DPA[j] == (DPA[i] - 1) and s[j] > s[i]) {
      sol[j] = 1;
      sols(j);
      sol[j] = 0;
    }
  }
  return;
}

int main(){
  //el largo de la subsecuencia comun mas larga es
  int maximo = LDS_BU(s);
  //busco todos los indices
  /*
  for(int i = 0; i < n; i++){
    if (DPA[i] == lis) {
      sol[i] = 1;
      sols(i);
      sol[i] = 0;
    }
  }
  */
  //otra forma de buscar los lugares donde ocurren los maximos
  //busco el iterador a la primera aparicion del maximo en el vector de soluciones optimas
  cout << "Las subsecuencias decrementales mas largas que hay en el array son: " << endl;
  vector<int>::iterator target = find(DPA.begin(), DPA.end(), maximo);
  //va a entrar a este while al menos una vez, pues hay un maximo en el vector de soluciones optimas
  while(target != DPA.end()){
    //calculo el indice donde halle el lugar donde se produce el maximo en las soluciones optimas
    int index = distance(DPA.begin(), target);
    //cout << index << endl;
    //este elemento se eligio en la solucion
    sol[index] = 1;
    //calculo todos los otros elementos que forman parte de esta solucion maxima
    sols(index);
    //quito esta eleccion para la proxima iteracion, si la hay
    sol[index] = 0;
    //busco un nuevo maximo luego del que ya halle
    target = find(target+1, DPA.end(), maximo);
  }
  return 0;
}
