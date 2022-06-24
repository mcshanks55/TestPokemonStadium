/*
* Pokemon Project
*
* ChangePowerWeather.h
* A Weather class that increase and decrease
* battle move of types specified in the class 
*
*/

#include "ChangePowerWeather.h"

// sets the name of the Weather by calling Weather constructor
// sets the increase types and decrease types
PokemonStadium::ChangePowerWeather::ChangePowerWeather(string name, 
   string startingOutput, string stillActiveOutput, string endingOutput,
   vector<Type> increaseTypes, vector<Type> decreaseTypes) : 
   Weather(name, startingOutput, stillActiveOutput, endingOutput) {
   this->increaseTypes = increaseTypes;
   this->decreaseTypes = decreaseTypes;

}

// Constructor that takes in a pointer to another ChangePowerWeather and
// set this ChangePowerWeather to other
PokemonStadium::ChangePowerWeather::ChangePowerWeather(ChangePowerWeather *other) :
   Weather(other->getName(),
      other->getStartingOutput(), other->getStillActiveOutput(), other->getEndingOutput()) {
   this->increaseTypes = other->increaseTypes;
   this->decreaseTypes = other->decreaseTypes;

}

// Gets the list of Types that will increase damage
vector<PokemonStadium::Type> 
PokemonStadium::ChangePowerWeather::getIncreaseDamageTypes() const {
   return increaseTypes;
}

// Gets the list of Types that will decrease damage
vector<PokemonStadium::Type> 
PokemonStadium::ChangePowerWeather::getDecreaseDamageTypes() const {
   return decreaseTypes;
}

// determines the how much to change the power of attack based on their type
double 
PokemonStadium::ChangePowerWeather::typeStatMultiplier(Type type) const {
   // if the Type is in the increase damgage returns 100% plus CHANGE_POWER_PER percent
   for (auto & incType : increaseTypes) {
      if (incType == type)
         return 1 + CHANGE_POWER_PER;
   }
   // if the Type is in the decrease damgage returns 100% plus CHANGE_POWER_PER percent
   for (auto & incType : decreaseTypes) {
      if (incType == type)
         return 1 - CHANGE_POWER_PER;
   }

   // if its Type is not in the increase or decrease list, 
   // damage power percentage remains the same
   return 1;
}
