/*
* Pokemon Project
*
* StatusConditionEffect.cpp
* A status move that changes the opp Pokemon Status Condition if successful
*
*/

#include "StatusConditionMove.h"

// constuctor for a cure status condition
// name, type, category, pp, power, accuracy, description set with StatusMove constructor
PokemonStadium::StatusConditionMove::StatusConditionMove(ConsoleOutput *out, 
   string name, Type type, int pp, int accuracy, string description) :
   StatusMove(out, name, type, pp, accuracy, description) {
   // if vectors are not the same should be handle in StatChangingEffect
   this->statusConditonEffect = StatusConditionEffect(out, accuracy);
}

// name, type, category, pp, power, accuracy, description set with StatusMove constructor
PokemonStadium::StatusConditionMove::StatusConditionMove(ConsoleOutput *out, 
   string name, Type type, int pp, int accuracy, string description,
   string statusCondition) : 
   StatusMove(out, name, type, pp, accuracy, description) {
   // if vectors are not the same should be handle in StatChangingEffect
   this->statusConditonEffect = StatusConditionEffect(out, accuracy,
      statusCondition);
}

// Constructor that takes in a pointer to another StatusConditionMove and
// set this StatusConditionMove to other
PokemonStadium::StatusConditionMove::StatusConditionMove(PokemonStadium::StatusConditionMove *other) :
   StatusMove(other->getConsoleOutput(), 
      other->getName(), other->getType(), other->getTotalPP(), other->getAccuracy(), other->getDescription()) {
   this->statusConditonEffect = other->statusConditonEffect;
}

// gets the stats changing effect
PokemonStadium::StatusConditionEffect
PokemonStadium::StatusConditionMove::getStatusConditionEFfect() const {
   return statusConditonEffect;
}

// minus the currentPP, then check if stats changing effect can apply and apply if it can
void
PokemonStadium::StatusConditionMove::useStatusConditionMove(
   Stats *userPokemonStats, StatusCondition *userStatusCondition,
   Stats *oppPokemonStats, StatusCondition *oppStatusCondition, 
   Type oppPrimaryType, Type oppSecondaryType) {
   currentPP--;
   logBattleMove();
   if (statusConditonEffect.getEffectCondition() == "") {
      if (userStatusCondition->getCondition() != "") {
         userStatusCondition->cured(userPokemonStats);
         out->log("Cured status condition");
      }
      else {
         out->log("status condition already cured");
      }
   }
   else {
      // if apply effect doesn't succeed print missed
      if (!statusConditonEffect.applyStatusConditionEffect(oppPokemonStats, 
         oppStatusCondition, oppPrimaryType, oppSecondaryType)) {
         out->log("effect missed");
      }
   }
}
