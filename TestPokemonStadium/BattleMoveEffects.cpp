#include "BattleMoveEffects.h"

// default constructor, sets values to blank
PokemonStadium::BattleMoveEffects::BattleMoveEffects() {
   out = NULL;
   chancesOfSuccess = 0;
}

// constructor, sets the chances of success of the battle move
PokemonStadium::BattleMoveEffects::BattleMoveEffects(ConsoleOutput *out, int chancesOfSuccess) {
   this->out = out;
   this->chancesOfSuccess = chancesOfSuccess;
}

// gets the chances of success
int 
PokemonStadium::BattleMoveEffects::getChancesOfSuccess() const {
   return chancesOfSuccess;
}

// check if effect landed based on the chancesOfSuccess
// return true if successful
bool
PokemonStadium::BattleMoveEffects::effectLanded(int chancesOfSuccess) {
   // Pokemon has a chancesOfSuccess percent chance that effect will land
   int random_value = rand() % 100;
   if (random_value <= chancesOfSuccess) {
      return true;
   }
   else {
      return false;
   }
}

// check if effect lands and if it does apply effect.
// effect can either be a status condition or stat changing effect
bool 
PokemonStadium::BattleMoveEffects::applyEffect(Stats *userStats,
   Stats *oppStats, StatusCondition *oppStatusCondition,
   Type oppPrimaryType, Type oppSecondaryType) {
   return false;
}
