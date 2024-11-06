#include "Herrero.h"
/*
Herrero::Herrero() : Humano(30, 85){
  herreria_skill_lvl_ = 50;
}
*/
Herrero::Herrero(){
}

Herrero::Herrero(unsigned int edad, unsigned int peso, unsigned int herreria_skill_lvl) : Humano(edad, peso) {
  herreria_skill_lvl_ = herreria_skill_lvl;
}

//destructor
Herrero::~Herrero() {
  cout << "El destructor de herreros fue ejecutado" << endl;
}

unsigned int Herrero::getHerr_skill_lvl() const {
  return herreria_skill_lvl_;
}
