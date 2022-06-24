/*
* Pokemon Project
*
* StatusMove.h
* A non damage battle move that change stats or status conditon
*
*/
#ifndef POKEMONSTADIUM_STATUSMOVE_H
#define POKEMONSTADIUM_STATUSMOVE_H

#include "BattleMove.h"

namespace PokemonStadium
{

   class StatusMove : public BattleMove {
   public:
      // Constructor
      StatusMove();
      StatusMove(ConsoleOutput *out, 
         string name, Type type, int pp, int accuracy, string description, int priority = 0);
      virtual void display() const;

   protected:

   private:

   };
}
#endif

