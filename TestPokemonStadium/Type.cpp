/*
* Pokemon
*
* Type.h
* The class Type is use characterizing a Pokemon or an attack type.
* Each type has lists for the set effectiveness the type has against
* other types and a function to determine the effective an attack would have
*
*/
#include "Type.h"

// empty type (used for when a Pokemon does not have a secondary type)
PokemonStadium::Type::Type() {
   name = "";
}

// initializes the name of the type, offenses and defenses 
PokemonStadium::Type::Type(string name,
   vector<string> superEffectiveAgainstList,
   vector<string> notVeryEffectiveAgainstList,
   vector<string> noEffectAgainstList,
   vector<string> weaknesses,
   vector<string> resistances,
   vector<string> immunities) {
   this->name = name;
   this->superEffectiveAgainstList = superEffectiveAgainstList;
   this->notVeryEffectiveAgainstList = notVeryEffectiveAgainstList;
   this->noEffectAgainstList = noEffectAgainstList;
   this->weaknesses = weaknesses;
   this->resistances = resistances;
   this->immunities = immunities;
}

// Gets the name of the type 
string
PokemonStadium::Type::getName() const {
   return name;
}

// Gets the list of the name of Types the Type does super effective damage to
vector<string>
PokemonStadium::Type::getSuperEffectiveAgainstList() const {
   return superEffectiveAgainstList;
}

// Gets the list of the name of Types the Type does not very effective damage to
vector<string>
PokemonStadium::Type::getNotVeryEffectiveAgainstList() const {
   return notVeryEffectiveAgainstList;
}

// Gets the list of the name of Types the Type does no damage to
vector<string>
PokemonStadium::Type::getNoEffectAgainstList() const {
   return noEffectAgainstList;
}

// Gets the list of the name of Types the Type is super effective to
vector<string>
PokemonStadium::Type::getWeaknesses() const {
   return weaknesses;
}

// Gets the list of the name of Types the Type is not very effective to
vector<string>
PokemonStadium::Type::getResistances() const {
   return resistances;
}

// Gets the list of the name of Types the Type is immune to
vector<string>
PokemonStadium::Type::getImmunities() const {
   return immunities;
}

// Return the effectiveness of the current Type attack against a Pokemon types
double
PokemonStadium::Type::attackEffectiveNess(Type opponentsPrimaryType, Type opponentsSecondaryType) const {
   string oppType1 = opponentsPrimaryType.getName();
   string oppType2 = opponentsSecondaryType.getName();
   // result starts as effective and can get change from the list 
   double result = EFFECTIVE;
   // the attack is super effect if given type is in the Super Effective Against List
   for (auto & type : getSuperEffectiveAgainstList()) {
      // if both types are in the super effective list the 
      // return double super effective power
      if (type == oppType1 && type == oppType2)
         return DBL_SUPER_EFFECTIVE;
      // if only one type is in the super effective list, change results 
      else if (type == oppType1 || type == oppType2)
         result *= SUPER_EFFECTIVE;
   }

   // the attack is not very effect if given type is in the Not Very Effective Against List
   for (auto & type : getNotVeryEffectiveAgainstList()) {
      // if both types are in the not very effective list the 
      // return double not very effective power
      if (type == oppType1 && type == oppType2)
         return DBL_NOT_VERY_EFFECTIVE;
      // if only one type is in the not very effective list, change results
      else if (type == oppType1 || type == oppType2)
         result *= NOT_VERY_EFFECTIVE;
   }

   // the attack is not very effect if given type is in the Not Very Effective Against List
   for (auto & type : getNoEffectAgainstList()) {
      // if only one type is in the no effect list, return no effect power
      if (type == oppType1 || type == oppType2)
         return NO_EFFECT;
   }
   // should get to here only if attack is effective, 
   // not very effective or super effective
   return result;
}

// return if types are equal to each other based on name
bool
PokemonStadium::Type::operator==(const Type &other) const {
   return name == other.getName();
}
