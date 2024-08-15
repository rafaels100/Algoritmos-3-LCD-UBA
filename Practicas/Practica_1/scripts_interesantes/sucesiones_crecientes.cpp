#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/*
Tiro un dado de {1, 2, ..., N} caras unas n veces.
Quiero las sucesiones estrictamente crecientes.
*/
int N = 9;
int n = 4;
vector<int> camino(n);
vector<vector<int>> S;
int contador = 0;
void suc_crec_con_repo(int i){
  if (i == n) {
    S.push_back(camino);
    return;
  }
  for (int k = 1; k <= N; k++) {
    /*
    La idea es generar por cada n nivel del arbol unos N nodos, pues no 'gasto' caras del cado cada vez que lo tiro, sino que es como una
    extraccion con reposicion
    */
    //ademas, el k que estoy considerando debe ser mayor al anterior para mantener la sucesion esctrictamente creciente
    if (i > 0){
      if (k > camino[i-1]) {
        camino[i] = k;
        suc_crec_con_repo(i + 1);
      }    
    }else{
      camino[i] = k;
      suc_crec_con_repo(i + 1);
    }
  }
  return;
}

//para la recursion sin repo me conviene tener un vector U con las caras del dado, pues voy a tener que buscar cuando tomar el camino y cuando no
vector<int> U(N);
void suc_crec_sin_repo(int i){
  if (i == n) {
    S.push_back(camino);
    return;
  }
  for (int elem : U) {
    if (! (find(camino.begin(), camino.begin() + i, elem) != camino.begin() + i)) {
      /*
      Como es extraccion sin reposicion, no puedo usar bolillas que ya use previamente en el camino actual.
      La idea es chequear el vector de camino que vengo armando, y ver si el elemento elem de U que estoy considerando ahora
      en el for ya lo use previamente en mi camino. Si es asi, no lo elijo, y no entro a este if. Si es asi, continuo por este camino
      */
      //ademas, el elem que estoy considerando debe ser mayor al anterior para mantener la sucesion esctrictamente creciente
      if (i > 0){
        if (elem > camino[i-1]) {
          camino[i] = elem;
          suc_crec_sin_repo(i + 1);
        }    
      }else{
        camino[i] = elem;
        suc_crec_sin_repo(i + 1);
      }
    }
  }
  return;
}


int main(){
  //empiezo la recursion desde la primera posicion
  
  suc_crec_con_repo(0);
  for (int i = 0; i < S.size(); i++) {
    for (int j = 0; j < S[i].size(); j++) {
      cout << S[i][j] << " ";
    }
    cout << endl;
  }
  cout << "Cardinal de S sucesiones crecientes con reposicion es: " << S.size() << endl;
  
  S.clear();
  //reinicializo el vector S del espacio muestral. No es necesario reinicializar el vector camino, pues lo voy a llenar acordemente
  //en la recusion sin reposicion.
  //Lleno al vector U que tiene a los dados a tirar
  for (int i = 0; i < N; i++) U[i] = i+1;
  suc_crec_sin_repo(0);
  for (int i = 0; i < S.size(); i++) {
    for (int j = 0; j < S[i].size(); j++) {
      cout << S[i][j] << " ";
    }
    cout << endl;
  }
  cout << "Cardinal de S sucesiones crecientes sin reposicion es: " << S.size() << endl;
  //tiene sentido que ambos approachs den lo mismo, pues no se pueden repetir elementos en las sucesiones
  //estrictamente crecientes. La reposicion no se tiene en cuenta aqui.
}
