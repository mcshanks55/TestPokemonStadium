/*
* Pokemon Project
*
* StatsChangingMove.cpp
* A status move that changes one or more pokemon stats
*
*/

#include "StatsChangingMove.h"

// name, type, category, pp, power, accuracy, description set with StatusMove constructor
PokemonStadium::StatsChangingMove::StatsChangingMove(ConsoleOutput *out, 
   string name, Type type, int pp, int accuracy, string description,
   vector<string> statsToChange, vector<string> changingAmountWords, vector<bool> useOnSelf, 
   int priority) :
   StatusMove(out, name, type, pp, accuracy, description, priority) {
   // if vectors are not the same should be handle in StatChangingEffect
   this->statsChangingEFfect = StatChangingEffect(out, accuracy,
      statsToChange, changingAmountWords, useOnSelf);
}

// Constructor that takes in a pointer to another StatsChangingMove and
// set this StatsChangingMove to other
PokemonStadium::StatsChangingMove::StatsChangingMove(PokemonStadium::StatsChangingMove *other) :
   StatusMove(other->out,
      other->getName(), other->getType(), other->getTotalPP(),
      other->getAccuracy(), other->getDescription(), other->getPriority()) {
   this->statsChangingEFfect = other->statsChangingEFfect;
}

// gets the stats changing effect
PokemonStadium::StatChangingEffect
PokemonStadium::StatsChangingMove::getStatsChangingEFfect() const {
   return statsChangingEFfect;
}

// minus the currentPP, then check if stats changing effect can apply and apply if it can
void 
PokemonStadium::StatsChangingMove::useStatsChangingMove(
   Stats *userPokemonStats, StatusCondition *userStatusCondition,
   Stats *oppPokemonStats, StatusCondition *oppStatusCondition, 
   Type oppPrimaryType, Type oppSecondaryType) {
   currentPP--;
   logBattleMove();
   if (getType().attackEffectiveNess(oppPrimaryType, oppSecondaryType) > 0) {
      // apply effect, if it returns false effect missed
      if (!statsChangingEFfect.applyStatChangingEffect(userPokemonStats, oppPokemonStats)) {
         out->log("effect missed");
      }
   }
   else {
      out->log("It has no effect");
   }
}
