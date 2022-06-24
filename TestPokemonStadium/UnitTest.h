/*
* Pokemon Project7
*
* UnitTest.h
* Test all of the Pokemon project classes
*
*/

#ifndef POKEMONSTADIUM_UNITTEST_H
#define POKEMONSTADIUM_UNITTEST_H

#include <ostream>
using std::ostream;

namespace PokemonStadium
{
   void Initialize(ostream &out);
   void DisplaySummary();
   void TestAllTypes();
   void TestStats();
   void TestWeather();
   void TestStatusCondition();
   void TestDamageMove();
   void TestChargeMove();
   void TestHiddenMove();
   void TestRechargeMove();
   void TestHealingMove();
   void TestStatsChangingMove();
   void TestStatusConditionMove();
   void TestWeatherChangingMove();
   void TestPokemonCharacter();
   void TestTrainer();
}
#endif
