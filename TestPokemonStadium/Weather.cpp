/*
* Pokemon
*
* Weather.cpp
*/
#include "Weather.h"

// An empty weather class is called clear
PokemonStadium::Weather::Weather() {
   this->name = "clear";
   this->startingOutput = "The skies become clear";
   this->stillActiveOutput = "";
   this->endingOutput = "";
}

// empty Weather
PokemonStadium::Weather::Weather(string name, 
   string startingOutput, string stillActiveOutput, string endingOutput) {
   this->name = name;
   this->startingOutput = startingOutput;
   this->stillActiveOutput = stillActiveOutput;
   this->endingOutput = endingOutput;

}

// Gets the name of the Weather 
string PokemonStadium::Weather::getName() const {
   return name;
}

// Gets the number of turns it has been since the 
// Weather first became active
int PokemonStadium::Weather::getTurnsSinceStarted() const {
   return turns_since_started;
}

// returns true if there is no weather
bool PokemonStadium::Weather::noWeather() {
   return name == "clear";
}

// If there have been more turns since the Weather has started
// then the Weather Time Maxium the Weather the Weather resets
// else increase the turn count
bool PokemonStadium::Weather::weatherStillActive() {
   if (turns_since_started >= WEATHER_TIME_MAX) {
      resetWeather();
      return false;
   }
   else {
      turns_since_started++;
      return true;
   }
}

// Reset turns since started
void PokemonStadium::Weather::resetWeather() {
   turns_since_started = 0;
}

// virtual function determines the power of attack
// based on their type
double
PokemonStadium::Weather::typeStatMultiplier(Type type) const {
   return 1.0;
}

// virtual function does damage to the Pokemon if the
// damage weather is out and given pokemon is not in noDamage list
void
PokemonStadium::Weather::applyWeatherDamages(Stats *pokemonStats, Type type1, Type type2) {}

// output for when weather begins 
string
PokemonStadium::Weather::getStartingOutput() {
   return startingOutput;
}

// output for when weather is still active 
string
PokemonStadium::Weather::getStillActiveOutput(){
   return stillActiveOutput;
}

// output for when weather ends 
string
PokemonStadium::Weather::getEndingOutput(){
   return endingOutput;
}

// if Weather name is the same as other Weather name, Weathers the same
bool
PokemonStadium::Weather::operator==(const Weather &other) const {
   if (getName() == other.getName())
      return true;
   else
      return false;
}