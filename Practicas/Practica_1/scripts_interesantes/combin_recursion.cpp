#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/*
Tiro un dado de {1, 2, ..., N} caras unas n veces.
*/
int N = 4;
int n = 3;
vector<int> camino(n);
vector<vector<int>> S;
int contador = 0;
void rec_con_repo(int i){
  if (i == n) {
    S.push_back(camino);
    return;
  }
  for (int k = 1; k <= N; k++) {
    /*
    La idea es generar por cada n nivel del arbol unos N nodos, pues no 'gasto' caras del cado cada vez que lo tiro, sino que es como una
    extraccion con reposicion
    */
    camino[i] = k;
    rec_con_repo(i+1);
  }
  return;
}

//para la recursion sin repo me conviene tener un vector U con las caras del dado, pues voy a tener que buscar cuando tomar el camino y cuando no
vector<int> U(N);
void rec_sin_repo(int i){
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
      camino[i] = elem;
      rec_sin_repo(i + 1);
    }
  }
  return;
}


int main(){
  //empiezo la recursion desde la primera posicion
  rec_con_repo(0);
  for (int i = 0; i < S.size(); i++) {
    for (int j = 0; j < S[i].size(); j++) {
      cout << S[i][j] << " ";
    }
    cout << endl;
  }
  cout << "Cardinal de S con reposicion es: " << S.size() << endl;
  
  S.clear();
  //reinicializo el vector S del espacio muestral. No es necesario reinicializar el vector camino, pues lo voy a llenar acordemente
  //en la recusion sin reposicion.
  //Lleno al vector U que tiene a los dados a tirar
  for (int i = 0; i < N; i++) U[i] = i+1;
  rec_sin_repo(0);
  for (int i = 0; i < S.size(); i++) {
    for (int j = 0; j < S[i].size(); j++) {
      cout << S[i][j] << " ";
    }
    cout << endl;
  }
  cout << "Cardinal de S sin reposicion es: " << S.size() << endl;
}
