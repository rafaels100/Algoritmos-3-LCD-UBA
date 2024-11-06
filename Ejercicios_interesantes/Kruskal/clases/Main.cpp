#include "Humano.cpp"
#include "Herrero.cpp"

int main(){
  /*
  Humano Pedro;
  Humano Juan = Humano();
  Humano Manuel = Humano(20, 70);
  cout << Manuel.getEdad() << endl;
  cout << Juan.getPeso() << endl;
  Humano Marc(10, 20);
  cout << Marc.getEdad() << endl;
  cout << Marc.getPeso() << endl;
  Marc.setEdad(10);
  */
  Herrero Pablo;
  cout << Pablo.getEdad() << endl;
  cout << Pablo.getPeso() << endl;
  cout << Pablo.getHerr_skill_lvl() << endl;
  
  Herrero Leo(50, 90, 85);
  cout << Leo.getEdad() << endl;
  cout << Leo.getPeso() << endl;
  cout << Leo.getHerr_skill_lvl() << endl;
  return 0;
}
