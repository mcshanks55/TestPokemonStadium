/*
* Pokemon
*
* DamageWeather.cpp
*/
#include "DamageWeather.h"

// sets the name of the Weather by calling Weather constructor
// sets noDamagaeTypes
PokemonStadium::DamageWeather::DamageWeather(string name, 
   string startingOutput, string stillActiveOutput, string endingOutput,
   vector<Type> noDamageTypes) : 
   Weather(name, startingOutput, stillActiveOutput, endingOutput) {
   this->noDamageTypes = noDamageTypes;
}

// Constructor that takes in a pointer to another DamageWeather and
// set this DamageWeather to other
PokemonStadium::DamageWeather::DamageWeather(DamageWeather *other) 
   : Weather(other->getName(), 
      other->getStartingOutput(), other->getStillActiveOutput(), other->getEndingOutput()) {
   this->noDamageTypes = other->noDamageTypes;
}

// Gets the list of Types that will not recieve damage
vector<PokemonStadium::Type> PokemonStadium::DamageWeather::getNoDamageTypes() const {
   return noDamageTypes;
}

// if one of the type of the Pokemon are in the no damage type list
// the the pokemon wil recieve is zero
// otherwise apply the damagepercent amount to Pokemon
void
PokemonStadium::DamageWeather::applyWeatherDamages(Stats *pokemonStats,
   Type type1, Type type2) {
   // if one of the Types is in the noDamageType, 
   // exit function
   for (auto & noDamageType : getNoDamageTypes()) {
      if (noDamageType == type1 || noDamageType == type2)
         return;
   }
   // else apply damage to pokemon
   pokemonStats->damagePercentToHealth(DAMAGE_PER);
}

//// if Weather name is the same as other Weather name, fileds are the same
//bool
//PokemonStadium::DamageWeather::operator==(const Weather &other) const {
//   if (getName() == other.getName())
//      return true;
//   else
//      return false;
//}
