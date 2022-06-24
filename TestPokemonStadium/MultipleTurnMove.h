/*
* Pokemon Project
*
* MultipleTurnMove.h
* A damage move that takes more than one turn
*
*/
#ifndef POKEMONSTADIUM_MULTIPLETURNMOVE_H
#define POKEMONSTADIUM_MULTIPLETURNMOVE_H

#include "DamageMove.h"

namespace PokemonStadium
{
   class MultipleTurnMove : public DamageMove {
   public:
   // Constructors
   MultipleTurnMove(ConsoleOutput *out, 
      string name, Type type, string category, int pp, int power, int accuaracy, string description,
      string typeOfTurnMove);

   MultipleTurnMove(ConsoleOutput *out, 
      string name, Type type, string category, int pp, int power, int accuaracy, string description,
      string typeOfTurnMove, string waitTurnDescription);

   MultipleTurnMove(ConsoleOutput *out, 
      string name, Type type, string category, int pp, int power, int accuaracy, string description,
      BattleMoveEffects *otherEffect,
      string typeOfTurnMove, string waitTurnDescription);

   // memeber functions
   string getTypeOfTurnMove();
   string getWaitTurnDescription();

   protected:
      bool turnMoveCalled;

   private:
      string typeOfTurnMove;
      string waitTurnDescription;
   };
}
#endif


