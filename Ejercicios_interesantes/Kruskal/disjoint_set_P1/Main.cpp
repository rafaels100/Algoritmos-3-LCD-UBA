#include "DisjointSet.cpp"

int main(){
  DisjointSet dj;
  cout << dj << endl;
  DisjointSet dj_1(4);
  cout << dj_1 << endl;
  for (int i = 0; i < 10; i++) {
    dj_1.agregarAdelante(i);
    cout << dj_1.getIesimo(i)->prim->valor << endl;
  }
  for (int i = 0; i < 10; i++) {
    cout << dj_1.getIesimo(i)->prim->valor << endl;
  }
  cout << dj_1 << endl;
  cout << "El tamaño del disjoint set es: " << dj_1.longitud() << endl;
  cout << "El tamaño del disjoint set es: " << dj.longitud() << endl;
  Lista::Nodo* c = dj_1.getIesimo(0);
  cout << c->valor << endl;
  cout << c->prim << endl;
  //cout << dj_1 << endl;
  Lista l;
  l.agregarAtras(1);
  Lista r({2,5,7});
  cout << r << endl;
  //cout << r.getIesimo(0) << endl;
  Lista j = r;
  return 0;
}
