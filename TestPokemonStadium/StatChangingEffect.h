/*
* Pokemon Project
*
* StatChangingEffect.h
* Changes the stat/s of either the user Pokemon, opponents Pokemon
* or both. 
*
*/
#ifndef POKEON_STATCHANGINGEFFECT_H
#define POKEON_STATCHANGINGEFFECT_H

#include "BattleMoveEffects.h"
#include "Stats.h"
using PokemonStadium::Stats;

namespace PokemonStadium
{
   // stat changing values
   static const int ROSE = 1;
   static const int FELL = -1;
   static const int SHARPLY = 2;
   static const int HARSHLY = -2;

   class StatChangingEffect : public BattleMoveEffects {
   public:
      // Constructor
      StatChangingEffect();
      StatChangingEffect(ConsoleOutput *out, int chancesOfSuccess, 
         vector<string> statsToChange, vector<string> changingAmountWords, vector<bool> useOnSelf);
      StatChangingEffect(StatChangingEffect *other);
      // Memeber functions
      vector<string> getStatsToChange() const;
      vector<string> getChangingAmountWord() const;
      vector<int> getChangingAmountValue() const;
      vector<bool> getUseOnSelf() const;
      int determineAmount(string powerName);
      bool pokemonStatsCanChange(Stats *usersPokemonStats, Stats *oppPokemonStats);
      void changePokemonStats(Stats *usersPokemonStats,
         Stats *oppPokemonStats);
      bool applyStatChangingEffect(Stats *userStats, Stats *oppStats);
      virtual bool applyEffect(Stats *userStats,
         Stats *oppStats, StatusCondition *oppStatusCondition,
         Type oppPrimaryType, Type oppSecondaryType);
   private:
      vector<string> statsToChange;
      vector<string> changingAmountWord;
      vector<int> changingAmountValue;
      vector<bool> useOnSelf;
   };
}
#endif