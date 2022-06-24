/*
* Pokemon
*
* Type.h
* The class Type is use characterizing a Pokemon or an attack type.
* Each type has lists for the set effectiveness the type has against
* other types and a function to determine the effective an attack would have
*
*/
#ifndef POKEMONSTADIUM_TYPE_H
#define POKEMONSTADIUM_TYPE_H

#include <string>
using std::string;
#include <vector>
using std::vector;

namespace PokemonStadium
{
   static const double DBL_SUPER_EFFECTIVE = 4.0;
   static const double SUPER_EFFECTIVE = 2.0;
   static const double EFFECTIVE = 1.0;
   static const double NOT_VERY_EFFECTIVE = 0.5;
   static const double DBL_NOT_VERY_EFFECTIVE = 0.25;
   static const double NO_EFFECT = 0.0;

   class Type {
   public:
      Type();
      // Constructor
      Type(string type,
         vector<string> superEffectiveAgainstList,
         vector<string> notVeryEffectiveAgainstList,
         vector<string> noEffectAgainstList,
         vector<string> weaknesses,
         vector<string> resistances,
         vector<string> immunities);

      // memeber variables

      // memeber functions
      string getName() const;
      vector<string> getSuperEffectiveAgainstList() const;
      vector<string> getNotVeryEffectiveAgainstList() const;
      vector<string> getNoEffectAgainstList() const;
      vector<string> getWeaknesses() const;
      vector<string> getResistances() const;
      vector<string> getImmunities() const;
      double attackEffectiveNess(Type opponentsPrimaryType, Type opponentsSecondaryType) const;
      // Operators
      bool operator==(const Type &other) const;

   private:
      string name;
      vector<string> superEffectiveAgainstList;
      vector<string> notVeryEffectiveAgainstList;
      vector<string> noEffectAgainstList;
      vector<string> weaknesses;
      vector<string> resistances;
      vector<string> immunities;

   };
}
#endif
