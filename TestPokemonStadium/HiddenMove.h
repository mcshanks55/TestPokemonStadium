/*
* Pokemon Project
*
* HiddenMove.h
* A MultipleTurnMove that first charges and then does damage
*
*
*/
#ifndef POKEMONSTADIUM_HIDDENMOVE_H
#define POKEMONSTADIUM_HIDDENMOVE_H

#include "MultipleTurnMove.h"
#define TYPE_OF_MOVE_HIDDEN "hidden"

namespace PokemonStadium
{
   class HiddenMove : public MultipleTurnMove {
   public:
      // Constructors
      HiddenMove(ConsoleOutput *out, 
         string name, Type type, string category, int pp, int power, int accuaracy, string description,
         string waitTurnDescription);
      HiddenMove(HiddenMove *other);

      // virtual functions
      virtual void useHiddenMove(Weather *battleWeather,
         Stats *userPokemonStats, StatusCondition *userStatusCondition, Type userPrimaryType, Type userSecondaryType,
         Stats *oppPokemonStats, StatusCondition *oppStatusCondition, Type oppPrimaryType, Type oppSecondaryType);

   private:
   };
}
#endif


