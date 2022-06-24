/*
* Pokemon Project
*
* HealingMove.h
* A status move that heals a Pokemon.
*
*/
#ifndef POKEMONSTADIUM_HEALINGMOVE_H
#define POKEMONSTADIUM_HEALINGMOVE_H

#include "StatusMove.h"

namespace PokemonStadium
{
   class HealingMove : public StatusMove {
   public:
      // Constructor
      HealingMove();
      HealingMove(ConsoleOutput *out, 
         string name, Type type, int pp, int accuracy, string description,
         double healPower);
      HealingMove(ConsoleOutput *out, 
         string name, Type type, int pp, int accuracy, string description,
         double healPower, vector<Weather> incPowerWeather, vector<Weather> decPowerWeather, double weatherPowerChange);
      HealingMove(HealingMove *other);

      // memeber functions
      double getHealPower() const;
      vector<Weather> getIncreasePowerWeather() const;
      vector<Weather> getDecreasePowerWeather() const;
      double getWeatherPowerChange() const;
      void useHealMove(Weather *battleWeather,
         Stats *userPokemonStats, Stats *oppPokemonStats);

   private:
      double healPower;
      vector<Weather> incPowerWeather;
      vector<Weather> decPowerWeather;
      double weatherPowerChange;
   };
}
#endif

