/*
* Pokemon Project
*
* StatusConditionEffect.h
* A battle move effect that attempts to change the
* Status Condition of the opponent's Pokemon
*
*/
#ifndef POKEMONSTADIUM_STATUSCONDITIONEFFECT_H
#define POKEMONSTADIUM_STATUSCONDITIONEFFECT_H

#include "BattleMoveEffects.h"
#include "StatusCondition.h"
using PokemonStadium::StatusCondition;

namespace PokemonStadium
{
   class StatusConditionEffect : public BattleMoveEffects {
   public:
      // Constructor
      StatusConditionEffect();
      StatusConditionEffect(ConsoleOutput *out, int chancesOfSuccess);
      StatusConditionEffect(ConsoleOutput *out, int chancesOfSuccess, string effectCondition);
      StatusConditionEffect(StatusConditionEffect *otherEffect);

      // Memeber functions
      string getEffectCondition() const;
      bool applyStatusConditionEffect(Stats *oppStats, StatusCondition *oppStatusCondition,
         Type opp_primary_type, Type opp_secondary_type);
      virtual bool applyEffect(Stats *userStats, Stats *oppStats, StatusCondition *oppStatusCondition,
         Type oppPrimaryType, Type oppSecondaryType);

   private:
      string effectCondition;
   };
}
#endif

