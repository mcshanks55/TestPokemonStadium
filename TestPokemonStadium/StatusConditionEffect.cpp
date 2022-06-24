#include "StatusConditionEffect.h"

// empty constructor
PokemonStadium::StatusConditionEffect::StatusConditionEffect() : BattleMoveEffects() {
   this->effectCondition = "";
}

// constructor for set the condition blank to empty
PokemonStadium::StatusConditionEffect::StatusConditionEffect(ConsoleOutput *out, int chancesOfSuccess) :
   BattleMoveEffects(out, chancesOfSuccess) {
   this->effectCondition = "";
}

// constructor for status condition effect
PokemonStadium::StatusConditionEffect::StatusConditionEffect(ConsoleOutput *out, int chancesOfSuccess,
   string effectCondition): BattleMoveEffects (out, chancesOfSuccess){
   // if condition is not blank or in in the vector of all conditions set condition
   if (find(allConditions.begin(), allConditions.end(), effectCondition) != allConditions.end()) {
      this->effectCondition = effectCondition;
   }
   // else throw an error
   else {
      throw invalid_argument(effectCondition + " is not an acceptable condition");
   }
}

// Constructor that takes in a pointer to another StatusConditionEffect and
// set this StatusConditionEffect to other
PokemonStadium::StatusConditionEffect::StatusConditionEffect(StatusConditionEffect *other) :
   BattleMoveEffects(other->out, other->getChancesOfSuccess()) {
   this->effectCondition = other->effectCondition;
}

// returns the Status Condition the effect will produce
string 
PokemonStadium::StatusConditionEffect::getEffectCondition() const {
   return effectCondition;
}

// check if the status condition can be change, if it cann see if effect landed, and if it can
// set the condition to the opp.
bool
PokemonStadium::StatusConditionEffect::applyStatusConditionEffect(Stats *oppStats, StatusCondition *oppStatusCondition,
   Type oppPrimaryType, Type oppSecondaryType) {

   // check if status condition can be changed before changing it
   if (oppStatusCondition->statusConditionCanBeChanged(effectCondition, 
      oppPrimaryType, oppSecondaryType)) {
      // if chances of effect landing was successfull, set condition
      if (effectLanded(getChancesOfSuccess())) {
         // if confused set confusion, otherwise use setCondition
         if (effectCondition == "confused") {
            oppStatusCondition->setConfusion();
         }
         else {
            oppStatusCondition->setCondition(effectCondition, oppStats);
         }
         return true;
      }
      else {
         return false;
      }
   }
   else {
      return true;
   }
}

// applies Status Condition effect, used to be called by BattleMoves OtherEffects
bool
PokemonStadium::StatusConditionEffect::applyEffect(Stats *userStats, 
   Stats *oppStats, StatusCondition *oppStatusCondition,
   Type oppPrimaryType, Type oppSecondaryType) {
   return applyStatusConditionEffect(oppStats, oppStatusCondition,
      oppPrimaryType, oppSecondaryType);
}