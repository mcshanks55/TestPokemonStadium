/*
* Pokemon
*
* StatChangingEffect.cpp
* Changes the stat/s of either the user Pokemon, opponents Pokemon
* or both.
*/

#include "StatChangingEffect.h"

// empty constructor
PokemonStadium::StatChangingEffect::StatChangingEffect() :
BattleMoveEffects() {
   this->changingAmountWord = {};
   this->changingAmountValue = {};
   this->statsToChange = {};
   this->useOnSelf = {};
}

// regular constructor
// set the changingAmountWord, changingAmountValue, statsToChange, useOnSelf as long as all vectors
// have the same total amount in them otherwise throws an error
// set the chance of success with BattleMoveEffects
PokemonStadium::StatChangingEffect::StatChangingEffect(ConsoleOutput *out, int chancesOfSuccess, 
   vector<string> statsToChange, vector<string> changingAmountWord, vector<bool> useOnSelf) :
   BattleMoveEffects(out, chancesOfSuccess) {

   if (statsToChange.size() == changingAmountWord.size() && changingAmountWord.size() == useOnSelf.size()) {
      // sets each numeric value for each word in changingAmountWord
      this->changingAmountWord = changingAmountWord;
      for (auto & change : changingAmountWord) {
         this->changingAmountValue.push_back(determineAmount(change));
      }
      this->statsToChange = statsToChange;
      this->useOnSelf = useOnSelf;
   }
   else {
      cerr << "all vectors are not the same size\n" <<
         "statsToChange size = " << statsToChange.size() << "\n" <<
         "changingPower size = " << changingAmountWord.size() << "\n" <<
         "useOn size = " << useOnSelf.size() << "\n";
   }
}

// Constructor that takes in a pointer to another StatChangingEffect and
// set this StatChangingEffect to other
PokemonStadium::StatChangingEffect::StatChangingEffect(StatChangingEffect *other) :
   BattleMoveEffects(other->out, other->getChancesOfSuccess()) {
   this->statsToChange = other->statsToChange;
   this->changingAmountWord = other->changingAmountWord;
   this->changingAmountValue = other->changingAmountValue;
   this->useOnSelf = other->useOnSelf;
}
// gets a vector of stat names to change
vector<string>
PokemonStadium::StatChangingEffect::getStatsToChange() const {
   return statsToChange;
}

// gets a vector of changing amount words
vector<string>
PokemonStadium::StatChangingEffect::getChangingAmountWord() const {
   return changingAmountWord;
}

// gets changing amount values
vector<int>
PokemonStadium::StatChangingEffect::getChangingAmountValue() const {
   return changingAmountValue;
}

// get vector use on self or opp
vector<bool>
PokemonStadium::StatChangingEffect::getUseOnSelf() const {
   return useOnSelf;
}

// determines how much changingPower will be base on the chaningPowerName
int
PokemonStadium::StatChangingEffect::determineAmount(string powerName) {
   // returns the power number based on the power name
   if (powerName == "rose")
      return ROSE;
   else if (powerName == "fell")
      return FELL;
   else if (powerName == "rose sharply")
      return SHARPLY;
   else if (powerName == "fell harshly")
      return HARSHLY;
   else
      cerr << powerName << " is not an accpetable value change";
   return 0;
}

// check if the all stats of the useOnSelf Trainer's Pokemon in statsToChange 
// can be chagned by changingAmount, if all of them can, return turn
bool
PokemonStadium::StatChangingEffect::pokemonStatsCanChange(Stats *usersPokemonStats, 
   Stats *oppPokemonStats) {
   bool statCanChanged = true;
   size_t change = 0;
   // loops through all vectors until reach the end or a stat
   // cannot be change. 
   while (statCanChanged && change < useOnSelf.size()) {
      // check if the stat being changed is for the user or opponent
      if (useOnSelf[change]) {
         // check if there was a successful stat change
         statCanChanged = usersPokemonStats->canModifierBeChanged(statsToChange[change],
            changingAmountValue[change]);
      }
      else {
         // check if there was a successful stat change
         statCanChanged = oppPokemonStats->canModifierBeChanged(statsToChange[change],
            changingAmountValue[change]);
      }
      // if stat did not change print reason
      if (!statCanChanged) {
         // determine if increase or decrese
         string changeType = "";
         if (changingAmountValue[change] > 0)
            changeType = "increased";
         else
            changeType = "decreased";
         string target = "";
         if (useOnSelf[change])
            target = "User's";
         else
            target = "Opponent's";

         out->log(target + " " + statsToChange[change] + " cannot be " + changeType + " anymore");
      }
      change++;
   }
   return statCanChanged;
}

void 
PokemonStadium::StatChangingEffect::changePokemonStats(Stats *usersPokemonStats, 
   Stats *oppPokemonStats) {
   // loops through all vectors and change the stats in them
   for (size_t i = 0; i < useOnSelf.size(); i++) {
      // check if the stat being changed is for the user or opponent
      if (useOnSelf[i]) {
         usersPokemonStats->changeModifier(statsToChange[i],
            changingAmountValue[i]);
         // print the change
         out->userLog(statsToChange[i]
            + " " + changingAmountWord[i]);
      }
      else {
         oppPokemonStats->changeModifier(statsToChange[i],
            changingAmountValue[i]);

         // print the change
         out->oppLog(statsToChange[i]
            + " " + changingAmountWord[i]);
      }
   }
}

// check if the status condition can be change, if it cann see if effect landed, and if it can
// set the condition to the opp.
bool
PokemonStadium::StatChangingEffect::applyStatChangingEffect(Stats *userStats, 
   Stats *oppStats) {
   if (effectLanded(getChancesOfSuccess())) {
      // if all modifiers can be changed, make changes to modifier
      if (pokemonStatsCanChange(userStats, oppStats)) {
         changePokemonStats(userStats, oppStats);
      }
      return true;
   }
   else {
      return false;
   }
}

// applies stat changing effect, used to be called by BattleMoves OtherEffects
bool 
PokemonStadium::StatChangingEffect::applyEffect(Stats *userStats,
   Stats *oppStats, StatusCondition *oppStatusCondition,
   Type oppPrimaryType, Type oppSecondaryType) {
   return applyStatChangingEffect(userStats, oppStats);
}
