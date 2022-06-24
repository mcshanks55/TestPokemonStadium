/*
* Pokemon Project
*
* StatusConditionMove.h
* A status move that changes the opp Pokemon Status Condition if successful
*
*/
#ifndef POKEMONSTADIUM_STATUSCONDITIONMOVE_H
#define POKEMONSTADIUM_STATUSCONDITIONMOVE_H

#include "StatusMove.h"
#include "StatusConditionEffect.h"

namespace PokemonStadium
{
   class StatusConditionMove : public StatusMove {
   public:
      // Constructor
      StatusConditionMove(ConsoleOutput *out, 
         string name, Type type, int pp, int accuracy, string description);
      StatusConditionMove(ConsoleOutput *out, 
         string name, Type type, int pp, int accuracy, string description,
         string statusCondition);
      StatusConditionMove(StatusConditionMove *other);

      // memeber functions
      StatusConditionEffect getStatusConditionEFfect() const;
      void useStatusConditionMove(Stats *userPokemonStats, StatusCondition *userStatusCondition,
         Stats *oppPokemonStats, StatusCondition *oppStatusCondition,
         Type oppPrimaryType, Type oppSecondaryType);

   private:
      StatusConditionEffect statusConditonEffect;
   };
}
#endif

