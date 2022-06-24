/*
* Pokemon Project
*
* Weather.h
* The Weather on the battle field set by a Pokemon battle move or ability
* Weather starts off as clear and returns to clear when the Weather change
* ends
*/
#ifndef POKEMONSTADIUM_WEATHER_H
#define POKEMONSTADIUM_WEATHER_H

#include "Type.h"
#include "Stats.h"
#define WEATHER_TIME_MAX 5

//#define TYPE_OF_WEATHER_CP "change power"
//#define TYPE_OF_WEATHER_D "damage"

namespace PokemonStadium
{
   
   class Weather {
   public:
      // Constructor
      Weather();
      Weather(string name, 
         string startingOutput, string stillActiveOutput, string endingOutput);

      // member functions
      string getName() const;
      int getTurnsSinceStarted() const;
      bool noWeather();
      bool weatherStillActive();
      void resetWeather();
      // virtual functions
      virtual double typeStatMultiplier(Type type) const;
      virtual void applyWeatherDamages(Stats *pokemonStats,
         Type type1, Type type2=Type());
      virtual string getStartingOutput();
      virtual string getStillActiveOutput();
      virtual string getEndingOutput();

      // Operators
      bool operator==(const Weather &other) const;

   private:
      string name;
      int turns_since_started = 0;
      string startingOutput;
      string stillActiveOutput;
      string endingOutput;
   };
}
#endif
