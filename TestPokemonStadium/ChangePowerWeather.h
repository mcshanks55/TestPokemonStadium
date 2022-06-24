/*
* Pokemon Project
*
* ChangePowerWeather.h
* A Weather class that increase some Type and decrease
* other types
*
*/
#ifndef POKEMONSTADIUM_CHANGEPOWERWEATHER_H
#define POKEMONSTADIUM_CHANGEPOWERWEATHER_H

#include "Weather.h"

namespace PokemonStadium
{
   static const double CHANGE_POWER_PER = 0.5;

   class ChangePowerWeather : public Weather {

   public:
      // Constructor
      ChangePowerWeather(string name, 
         string startingOutput, string stillActiveOutput, string endingOutput,
         vector<Type> increaseTypes, vector<Type> decreaseTypes);
      ChangePowerWeather(ChangePowerWeather *other);

      // memeber functions
      vector<Type> getIncreaseDamageTypes() const;
      vector<Type> getDecreaseDamageTypes() const;
      // virtual functions
      virtual double typeStatMultiplier(Type type) const;
      //virtual bool operator==(const Weather &other) const;

   private:
      vector<Type> increaseTypes;
      vector<Type> decreaseTypes;
   };
}
#endif
