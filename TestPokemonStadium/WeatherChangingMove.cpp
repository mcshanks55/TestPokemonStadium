/*
* Pokemon
*
* WeatherChangingMove.cpp
* A status move that changes the batte weather.
*/

#include "WeatherChangingMove.h"

// constructor
// name, type, category, pp, power, accuracy, description set with StatusMove constructor
PokemonStadium::WeatherChangingMove::WeatherChangingMove(ConsoleOutput *out, 
   string name, Type type, int pp, string description,
   Weather *newWeather) :
   StatusMove(out, name, type, pp, NEVER_MISS, description) {
   this->newWeather = newWeather;
}

// Constructor that takes in a pointer to another WeatherChangingMove and
// set this WeatherChangingMove to other
PokemonStadium::WeatherChangingMove::WeatherChangingMove(PokemonStadium::WeatherChangingMove *other) :
   StatusMove(other->getConsoleOutput(),
      other->getName(), other->getType(), other->getTotalPP(),
      other->getAccuracy(), other->getDescription()) {
   this->newWeather = other->newWeather;
}

// gets the Weather the move is going to set
PokemonStadium::Weather*
PokemonStadium::WeatherChangingMove::getWeatherToSet() const {
   return newWeather;
}

// use move, if the battle weather isn't already the weather trying to be set,
// set the battle field weather to the new weather
void
PokemonStadium::WeatherChangingMove::useWeatherChanginMove(Weather **battleWeather) {
   currentPP--;
   logBattleMove();
   string newWeatherName = newWeather->getName();
   if (**battleWeather == *newWeather) {
      out->log("Weather is already set to " + newWeatherName);
   }
   else {
      // determines the class of the new weather and 
      // sets battle weather to it
      if (ChangePowerWeather *cpWeather =
      dynamic_cast<ChangePowerWeather *>(newWeather)) {
         *battleWeather = new ChangePowerWeather(cpWeather);
      }
      else if (DamageWeather *dWeather =
      dynamic_cast<DamageWeather *>(newWeather)) {
         *battleWeather = new DamageWeather(dWeather);
      }
      // throw an error if its not the above classes
      else {
         cerr << newWeatherName << " is not proper weather class\n";
         exit(EXIT_FAILURE);
      }
      out->log((*battleWeather)->getStartingOutput());
   }
}
