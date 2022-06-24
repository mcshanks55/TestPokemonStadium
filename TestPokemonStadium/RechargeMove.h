/*
* Pokemon Project
*
* RechargeMove.h
* A MultipleTurnMove that unless the attack and then needs a recharge
* the next turn
*/
#ifndef POKEMONSTADIUM_RECHARGEMOVE_H
#define POKEMONSTADIUM_RECHARGEMOVE_H

#include "MultipleTurnMove.h"
#define TYPE_OF_MOVE_RECHARGE "recharge"
#define WAIT_TURN_DESC "needs to recharge."

namespace PokemonStadium
{
   class RechargeMove : public MultipleTurnMove {
   public:
      // Constructors
      RechargeMove(ConsoleOutput *out, 
         string name, Type type, string category, int pp, int power, int accuaracy, string description);
      RechargeMove(RechargeMove *other);

      // virtual functions
      virtual void useRechargeMove(Weather *battleWeather,
         Stats *userPokemonStats, StatusCondition *userStatusCondition, Type userPrimaryType, Type userSecondaryType,
         Stats *oppPokemonStats, StatusCondition *oppStatusCondition, Type oppPrimaryType, Type oppSecondaryType);

   private:
   };
}
#endif
