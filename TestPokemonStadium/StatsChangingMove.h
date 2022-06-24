/*
* Pokemon Project
*
* StatsChangingMove.h
* A status move that changes one or more pokemon stats
*
*/
#ifndef POKEMONSTADIUM_STATSCHANGINGMOVE_H
#define POKEMONSTADIUM_STATSCHANGINGMOVE_H

#include "StatusMove.h"
#include "StatChangingEffect.h"

namespace PokemonStadium
{
   class StatsChangingMove : public StatusMove {
   public:
      // Constructor
      StatsChangingMove(ConsoleOutput *out, 
         string name, Type type, int pp, int accuracy, string description,
         vector<string> statsToChange, vector<string> changingAmountWords, vector<bool> useOnSelf,
         int priority = 0);
      StatsChangingMove(StatsChangingMove *other);

      // memeber functions
      StatChangingEffect getStatsChangingEFfect() const;
      void useStatsChangingMove(Stats *userPokemonStats, StatusCondition *userStatusCondition,
         Stats *oppPokemonStats, StatusCondition *oppStatusCondition,
         Type oppPrimaryType, Type oppSecondaryType);

   private:
      StatChangingEffect statsChangingEFfect;
   };
}
#endif

