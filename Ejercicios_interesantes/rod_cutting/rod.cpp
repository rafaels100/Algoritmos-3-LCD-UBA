#include <vector>
#include <iostream>

using namespace std;
//los precios de los cortes son
int n = 10;
vector<int> p = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
int INF = 1000;

/*
Problema rod-cutting:
Se quiere saber cual es la manera mas optima de cortar una barra para que la empresa maximize sus ganancias.
Hay len(p) lugares de cortes, y resulta en una subbarra que a su vez se puede cortar (en menos lugares claro), y que dara a su vez mas barras, y asi.
Presenta el formato de subestructura optima, pues al cortar una barra tendre otra barra que puede ser considerada como una nueva instancia del problema rod-cutting,
solo que mas pequeña.
*/
int f(int i){
  if (i == 0) {
    return 0;
  }
  int maximo = -INF;
  //int candidato;
  for (int j = 0; j < i; i++) {
    maximo = max(maximo, p[j] + f(i-j));
  }
  return maximo;
}

int main(){
  cout << f(p.size()) << endl;
  return 0;
}
