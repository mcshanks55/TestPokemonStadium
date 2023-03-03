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

   static const int NO_PRIORTY = 0;
   static const int LOWEST_PRIORTY = 1;
   static const int HIGHEST_PRIORITY = 5;

   // calculate the damage the pokemon will recieve from the attack, base of the
   // attacking damage move type stat of the attacking Pokemon and defending Pokemon
   // defenisve damage move type stat times the power of the attack
   static const int 
   calculatePureDamage(int attackPower, double attackingStat, double defendingStat) {
      double stat_calc = (double)(attackingStat / defendingStat);
      int pureDamage = (int)(((SET_LV_CALC * attackPower * stat_calc) / 50));
      // reutrn 1 if pureDamage is less than 1
      if (pureDamage < 1)
         return 1;

      return pureDamage;
   }
}

#endif