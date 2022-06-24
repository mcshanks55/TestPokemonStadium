/*
* Pokemon Project
*
* BattleMoveEffects.h
* Class for battle move effects like changes stats
* or status condition
*
*/
#ifndef POKEMONSTADIUM_BATTLEMOVEEFFECTS_H
#define POKEMONSTADIUM_BATTLEMOVEEFFECTS_H

#include <stdexcept>
using std::invalid_argument;
#include <iostream>
using std::cerr;
#include "ConsoleOutput.h"
using PokemonStadium::ConsoleOutput;
#include "Type.h"
using PokemonStadium::Type;
#include "StatusCondition.h"
using PokemonStadium::StatusCondition;
#include "Global.h"

namespace PokemonStadium
{
   class BattleMoveEffects {
   public:
      // Constructor
      BattleMoveEffects();
      BattleMoveEffects(ConsoleOutput *out, int chancesOfSuccess);

      // memeber functions
      int getChancesOfSuccess() const;
     
      // virtual functions
      virtual bool applyEffect(Stats *userStats,
         Stats *oppStats, StatusCondition *oppStatusCondition,
         Type oppPrimaryType, Type oppSecondaryType);

   protected:
      ConsoleOutput *out;
      bool effectLanded(int chancesOfSuccess);

   private:
      int chancesOfSuccess;
   };
}
#endif

