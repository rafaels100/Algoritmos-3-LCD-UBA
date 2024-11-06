#include <iostream>
#include <vector>

using namespace std;

#ifndef HUMANO_H
#define HUMANO_H

class Humano {
public:
  //default constructor
  Humano();
  
  //overload constructor
  Humano(unsigned int edad,unsigned int peso);
  
  //destructor
  ~Humano();
  
  //getters
  unsigned int getEdad() const;
  //devuelve la edad. Solo lectura de la variable privada
  
  unsigned int getPeso() const;
  //devuelve el peso. Solo lectura de la variable privada
  
  unsigned int getHP() const;
  //devuelve los puntos de vida. Solo lectura de la variable privada
  
  //mutadores
  void setEdad(unsigned int edad);
  //setea la edad. La constraint es que no puede tener menos de 18 años. Debe ser un humano adulto
  //@param edad - Entero positivo, la edad del humano
  
  void setPeso(unsigned int peso);
  //setea el peso, en kg. Debe pesar mas de 60 kg
  //@param peso - Entero positivo, el peso del humano
  
  void setHP(unsigned int hp);
  //setea los puntos de vida del humano. Debe ser numero no negativo, menor o igual a 100
  //@param hp - Entero positivo, los nuevos puntos de vida del humano
  

private:
  int edad_;
  int peso_;
  int hp_;
};
#endif // !HUMANO_H
