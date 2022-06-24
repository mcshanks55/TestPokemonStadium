/*
* Pokemon Project
*
* WeatherChangingMove.h
* A status move that changes the batte weather.
*
*/
#ifndef POKEMONSTADIUM_WEATHERCHANGINGMOVE_H
#define POKEMONSTADIUM_WEATHERCHANGINGMOVE_H

#include "StatusMove.h"
#include "ChangePowerWeather.h"
using PokemonStadium::ChangePowerWeather;
#include "DamageWeather.h"
using PokemonStadium::DamageWeather;

namespace PokemonStadium
{
   class WeatherChangingMove : public StatusMove {
   public:
      // Constructor
      WeatherChangingMove(ConsoleOutput *out, 
         string name, Type type, int pp, string description,
         Weather *newWeather);
      WeatherChangingMove(WeatherChangingMove *other);

      // memeber functions
      Weather *getWeatherToSet() const;

      // virtual functions
      void useWeatherChanginMove(Weather **battleWeather);

   private:
      Weather *newWeather;
   };
}
#endif

