/*
* Pokemon Project
*
* ChargeMove.h
* A MultipleTurnMove that first charges and then does damage
*
*
*/
#ifndef POKEMONSTADIUM_CHARGEMOVE_H
#define POKEMONSTADIUM_CHARGEMOVE_H

#include "MultipleTurnMove.h"
#define TYPE_OF_MOVE_CHARGE "charge"

namespace PokemonStadium
{
   class ChargeMove : public MultipleTurnMove {
   public:
      // Constructors
      // no extra battle effects 
      ChargeMove(ConsoleOutput *out, 
         string name, Type type, string category, int pp, int power, int accuaracy, string description,
         string waitTurnDescription);

      // extra battle move effect
      ChargeMove(ConsoleOutput *out, 
         string name, Type type, string category, int pp, int power, int accuaracy, string description,
         BattleMoveEffects *otherEffect, bool applyDuringCharge,
         string waitTurnDescription);

      // has a noChargeWeather, no extra battle move effect
      ChargeMove(ConsoleOutput *out, 
         string name, Type type, string category, int pp, int power, int accuaracy, string description,
         string waitTurnDescription, vector<Weather> noChargeWeather);

      ChargeMove(ChargeMove *other);

      ~ChargeMove();

      // virtual functions
      void useChargeMove(Weather *battleWeather,
         Stats *userPokemonStats, StatusCondition *userStatusCondition, Type userPrimaryType, Type userSecondaryType,
         Stats *oppPokemonStats, StatusCondition *oppStatusCondition, Type oppPrimaryType, Type oppSecondaryType);

   private:
      vector<Weather> noChargeWeather;
      bool moveCharged;
      bool applyDuringCharge;
   };
}
#endif


