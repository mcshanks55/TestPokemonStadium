/*
* Pokemon
*
* Global.h
* All global variables used

*/
#ifndef POKEMONSTADIUM_GLOBAL_H
#define POKEMONSTADIUM_GLOBAL_H
#define SET_LV_CALC 22

#include <string>
using std::string;
#include <vector>
using std::vector;

namespace PokemonStadium {


   // accuracy value for never miss attacks
   static const int NEVER_MISS = 1000;

   // most a stat can be modified
   static const int MAX_MODIFIER = 6;

   static const string RECHARGE_DESCRIPTION = "needs to recharge";

   // calculate the damage the pokemon will recieve from the attack, base of the
   // attacking damage move type stat of the attacking Pokemon and defending Pokemon
   // defenisve damage move type stat times the power of the attack
   static const int 
   calculatePureDamage(int attackPower, int attackingStat, int defendingStat) {
      int pureDamage = (int)(((SET_LV_CALC * attackPower * (attackingStat / defendingStat)) / 50));
      // reutrn 1 if pureDamage is less than 1
      if (pureDamage < 1)
         return 1;

      return pureDamage;
   }
}

#endif