/*
* Pokemon
*
* HealingMove.cpp
* A status move that heals a Pokemon.
*/

#include "HealingMove.h"

// empty constructor
PokemonStadium::HealingMove::HealingMove() :
   StatusMove() {
   this->healPower = 0;
   // set weather changes to empty
   this->incPowerWeather = {};
   this->decPowerWeather = {};
   this->weatherPowerChange = 1;
}

// no weather power changes
// name, type, category, pp, power, accuracy, description set with StatusMove constructor
PokemonStadium::HealingMove::HealingMove(ConsoleOutput *out, 
   string name, Type type, int pp, int accuracy, string description,
   double healPower) :
   StatusMove(out, name, type, pp, accuracy, description) {
   this->healPower = healPower;
   // set weather changes to empty
   this->incPowerWeather = {};
   this->decPowerWeather = {};
   this->weatherPowerChange = 1;
}

// weather changes
// name, type, category, pp, power, accuracy, description set with BattleMove constructor
PokemonStadium::HealingMove::HealingMove(ConsoleOutput *out, 
   string name, Type type, int pp, int accuracy,string description,
   double healPower, vector<Weather> incPowerWeather, vector<Weather> decPowerWeather, double weatherPowerChange) :
   StatusMove(out, name, type, pp, accuracy, description) {
   this->healPower = healPower;
   this->incPowerWeather = incPowerWeather;
   this->decPowerWeather = decPowerWeather;
   this->weatherPowerChange = weatherPowerChange;
}

// Constructor that takes in a pointer to another HealingMove and
// set this HealingMove to other
PokemonStadium::HealingMove::HealingMove(PokemonStadium::HealingMove *other) :
   StatusMove(other->out,
      other->getName(), other->getType(), other->getTotalPP(), other->getAccuracy(), other->getDescription()) {
   this->healPower = other->healPower;
   this->incPowerWeather = other->incPowerWeather;
   this->decPowerWeather = other->decPowerWeather;
   this->weatherPowerChange = other->weatherPowerChange;
}

// gets the heal power percentage
double 
PokemonStadium::HealingMove::getHealPower() const {
   return healPower;
}

// gets the list of weather to increase power of healing
vector<PokemonStadium::Weather>
PokemonStadium::HealingMove::getIncreasePowerWeather() const {
   return incPowerWeather;
}

// gets the power percentage if the increase or decrease weather is out when move is made
double 
PokemonStadium::HealingMove::getWeatherPowerChange() const {
   return weatherPowerChange;
}

// gets the list of weather to decrease power of healing
vector<PokemonStadium::Weather>
PokemonStadium::HealingMove::getDecreasePowerWeather() const {
   return decPowerWeather;
}

// virtual functions use the battle move, different
// for each type of battle move. Returns if battle move
// was successful
// TODO a move that heals both user and opp
void
PokemonStadium::HealingMove::useHealMove(Weather *battleWeather,
   Stats *userPokemonStats, Stats *oppPokemonStats) {
   currentPP--;
   logBattleMove();
   // if no weather changes healingPower stays the same s helower
   double healingPower = healPower;
   // if the field is the incPowerWeather,
   // increase the healing power
   for (auto & weather : incPowerWeather) {
      if (weather == *battleWeather) {
         healingPower *= weatherPowerChange;
      }
   }

   // if the field is the decPowerWeather,
   // decrease the healing power
   for (auto & weather : decPowerWeather) {
      if (weather == *battleWeather) {
         healingPower /= weatherPowerChange;
      }
   }

   // applies healing to user
   userPokemonStats->healPercentageHealth(healingPower);
}
