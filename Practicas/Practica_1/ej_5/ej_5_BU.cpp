#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<bool>> M;

void imprimirDPT(M &DPT){
  for (int i = 0; i < DPT.size(); i++) {
    for (int j = 0; j < DPT[0].size(); j++) {
      cout << DPT[i][j] << " ";
    }
    cout << "\n";
  }
  return;
}

bool f(vector<int> &C, int k){
  //creo la DPT
  /*
  La primera fila n = 0 indica que considero 0 items y me pregunto si puedo lograr el resultado k sumando items del conjunto C.
  La segunda fila n = 1 indica que considero 1 items y me pregunto si puedo lograr el resultado k sumando items del conjunto C.
  La tercera fila n = 2 indica que considero 2 items y me pregunto si puedo lograr el resultado k sumando items del conjunto C.
  */
  int n = C.size();
  M DPT(n + 1, vector<bool>(k + 1)); //quiero considerar n = 0 y k = 0
  //lleno la primera fila a mano
  DPT[0][0] = true;
  for (int i = 1; i <= k; i++) DPT[0][i] = false;
  //calculo el resto de filas usando la relacion entre los subproblemas:
  //f(i, j) = f(i-1, j) || f(i-1, j - C[i])  (RESULTADO TEORICO)
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= k; j++) {
      if ((j - C[i-1]) < 0) { //prueba de factibilidad
        DPT[i][j] = DPT[i-1][j];
      }else{
        DPT[i][j] = DPT[i-1][j] || DPT[i-1][j - C[i-1]]; //puede surgir confusion debido a la fila i de la DPT y el elemento i-1 del array C
        //conceptualmente la fila i de la DPT no se refiere al elemento i del array, sino que f(i, j) se pregunta si puedo lograr j usando una cantidad i de elementos del
        //conjunto C, en terminos de indices esto es los elementos [0 -> i) del array C, asi que en este contexto podria decirse que i es la cantidad 
        //de elementos del array C que tenemos permitido usar para lograr j, y C[i - 1] es el ultimo elemento del array que tenemos permitido usar.
      }
    }
  }
  imprimirDPT(DPT);
  return DPT[n][k];
}

int main(){
  vector<int> C = {6, 12, 6};
  int k = 12;
  cout << f(C, k) << endl;
  return 0;
}
