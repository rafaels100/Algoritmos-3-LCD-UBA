#include "Humano.h"

#ifndef HERRERO_H
#define HERRERO_H

class Herrero : public Humano {
public:
  //default constructor
  Herrero();
  
  //overload constructor
  Herrero(unsigned int peso, unsigned int edad, unsigned int herreria_skill_lvl);
  
  //destructor
  ~Herrero();
  
  //getters
  unsigned int getHerr_skill_lvl() const;

private:
  unsigned int herreria_skill_lvl_;
};
#endif // !HERRERO_H
