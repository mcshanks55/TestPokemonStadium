
/*
* Pokemon Project
*
* DamageWeather.h
* A Weather class that cause damage to Pokemon that aren't
* in the specific type list
*
*/
#ifndef POKEMONSTADIUM_DAMAGEWEATHER_H
#define POKEMONSTADIUM_DAMAGEWEATHER_H

#include "Weather.h"

namespace PokemonStadium
{
   static const double DAMAGE_PER = 0.0625;

   class DamageWeather : public Weather {

   public:
      // Constructor
      DamageWeather(string name, 
         string startingOutput, string stillActiveOutput, string endingOutput,
         vector<Type> noDamageTypes);
      DamageWeather(DamageWeather *other);

      // memeber functions
      vector<Type> getNoDamageTypes() const;
      // virtual functions
      virtual void applyWeatherDamages(Stats *pokemonStats,
         Type type1, Type type2 = Type());
      //virtual bool operator==(const Weather &other) const;

   private:
      vector<Type> noDamageTypes;
   };
}
#endif
