#include "Lista.cpp"

int main(){
  Lista l = Lista();
  l.agregarAtras(1);
  l.agregarAdelante(25);
  l.agregarAtras(10);
  //l.mostrar(cout);
  cout << l << endl;
  l.eliminar(0);
  cout << l << endl;
  return 0;
}
