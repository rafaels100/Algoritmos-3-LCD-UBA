#include "Humano.h"

//default constructor
Humano::Humano() {
  edad_ = 18; //anios
  peso_ = 75;  //kg
  hp_ = 100; //puntos de vida
}

//overload constructor
Humano::Humano(unsigned int edad, unsigned int peso) {
  //para no sobrecargar al mutador con condiciones propias solo de la inicializacion, agrego condiciones para los valores que puede ingresar el usuario.
  //dejo las condiciones en los mutadores de manera minimal, para que impidan cambios en la edad una vez los objetos fueron creados
  if (edad >= 18) {
    edad_ = edad;
  }else{
    cout << "La edad debe ser mayor o igual a 18. Se seteo la edad por default a 18 anios. Si desea cambiar este atributo a un valor permitido, utilice setEdad." << endl;
    edad_ = 18; //anios
  }
  if (peso >= 60) {
    peso_ = peso;
  }else{
    cout << "El peso debe ser mayor o igual a 60kg. Se seteo el peso por default a 75kg. Si desea cambiar este atributo a un valor permitido, utilice setPeso." << endl;
    peso_ = 75; //kg
  }
  hp_ = 100; //los puntos de vida iniciales de todo humano son 100
}

//destructor
Humano::~Humano(){
  cout << "El destructor de humanos fue ejecutado" << endl;  
}

//setters
void Humano::setEdad(unsigned int edad){
  if (edad >= 18){
    edad_ = edad;
    cout << "La edad fue cambiada exitosamente a " << edad_ << " anios." << endl;
  }else{
    cout << "La edad debe ser mayor o igual a 18 años. La edad no fue modificada, y es " << edad_ << " anios." << endl;
  }
  return;
}

void Humano::setPeso(unsigned int peso){
  if (peso >= 60){
    peso_ = peso;
    cout << "El peso fue cambiado exitosamente a " << peso_ << " kg." << endl;
  }else{
    cout << "El peso debe ser mayor o igual a 60 kg. El peso no fue modificado, y es " << peso_ << " kg." << endl;
  }
  return;
}

//getters
unsigned int Humano::getEdad() const {
  return edad_;
}

unsigned int Humano::getPeso() const {
  return peso_;
}
