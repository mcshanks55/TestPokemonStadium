/*
* Pokemon Project7
*
* UnitTest.h
* Test all of the Pokemon project classes
*
*/

// Include standard library headers
#include <iostream>
using std::endl;

#include <ostream>
using std::ostream;

#include <sstream>
using std::stringstream;

#include <string>
using std::string;

// Include test headers
#include "UnitTest.h"
#include "TestFramework.h"

// Include Pokemon headers
#include "ConsoleOutput.h"
using PokemonStadium::ConsoleOutput;

#include "Stats.h"
using PokemonStadium::Stats;

#include "AllWeathers.h"
using PokemonStadium::Type;
using PokemonStadium::Weather;
using PokemonStadium::ChangePowerWeather;
using PokemonStadium::DamageWeather;

#include "StatusCondition.h"
using PokemonStadium::StatusCondition;

#include "StatusConditionEffect.h"
using PokemonStadium::StatusConditionEffect;
#include "StatChangingEffect.h"
using PokemonStadium::StatChangingEffect;

#include "DamageMove.h"
using PokemonStadium::DamageMove;
#include "ChargeMove.h"
using PokemonStadium::ChargeMove;
#include "HiddenMove.h"
using PokemonStadium::HiddenMove;
#include "RechargeMove.h"
using PokemonStadium::RechargeMove;

#include "HealingMove.h"
using PokemonStadium::HealingMove;
#include "StatsChangingMove.h"
using PokemonStadium::StatsChangingMove;
#include "StatusConditionMove.h"
using PokemonStadium::StatusConditionMove;
#include "WeatherChangingMove.h"
using PokemonStadium::WeatherChangingMove;

#include "PokemonCharacter.h"
using PokemonStadium::PokemonCharacter;

#include "Trainer.h"
using PokemonStadium::Trainer;

void PokemonStadium::Initialize(ostream &out) {
	TestFramework::Initialize(&out);
}

void PokemonStadium::DisplaySummary() {
	TestFramework::DisplaySummary();
}

void TestTypeNormalType() {
   TestFramework::BeginTest("Test Type: Normal Type");

   // Test name
   Type pokemonPrimaryType = type_normal;
   TEST_ASSERT("Normal" == pokemonPrimaryType.getName());

   vector<string> superEffectiveList = pokemonPrimaryType.getSuperEffectiveAgainstList();
   // Normal has no types its super effective to
   TEST_ASSERT(superEffectiveList.empty());

   // Test getNotVeryEffectiveAgainstList
   vector<string> notVeryEffectiveList = pokemonPrimaryType.getNotVeryEffectiveAgainstList();
   // Normal is not very effective against Rock or Steel
   for (auto & type : notVeryEffectiveList) {
      TEST_ASSERT(type == "Rock" || type == "Steel");
   }

   // Test getNoEffectAgainstList
   vector<string> noEffectList = pokemonPrimaryType.getNoEffectAgainstList();
   // Normal is no effect against Ghost
   for (auto & type : noEffectList) {
      TEST_ASSERT(type == "Ghost");
   }

   // Test getWeaknesses
   vector<string> weaknessesList = pokemonPrimaryType.getWeaknesses();
   // Normal is weak against Fight
   for (auto & type : weaknessesList) {
      TEST_ASSERT(type == "Fighting");
   }

   // Test getResistances
   vector<string> resistancesList = pokemonPrimaryType.getResistances();
   // Normal has no types its resistance to
   TEST_ASSERT(resistancesList.empty());
   
   // Test getImmunities
   vector<string> immunityList = pokemonPrimaryType.getImmunities();
   // Normal is immune against Ghost
   for (auto & type : immunityList) {
      TEST_ASSERT(type == "Ghost");
   }

   // test operator
   PokemonStadium::Type POKEMONSTADIUM_type = type_normal;
   TEST_ASSERT(POKEMONSTADIUM_type == type_normal);

   // test attackEffectiveness
   double effectivness = type_normal.attackEffectiveNess(type_fire, type_water);
   TEST_ASSERT(1 == effectivness);
   effectivness = type_normal.attackEffectiveNess(type_grass, type_rock);
   TEST_ASSERT(0.5 == effectivness);
   effectivness = type_normal.attackEffectiveNess(type_rock, type_steel);
   TEST_ASSERT(0.25 == effectivness);
   effectivness = type_fighting.attackEffectiveNess(type_normal, Type());
   TEST_ASSERT(2 == effectivness);
   effectivness = type_fighting.attackEffectiveNess(type_rock, type_normal);
   TEST_ASSERT(4 == effectivness);
   effectivness = type_normal.attackEffectiveNess(type_ghost, type_rock);
   TEST_ASSERT(0 == effectivness);

   TestFramework::EndTest();
}

void PokemonStadium::TestAllTypes() {
   TestTypeNormalType();
}

void TestStats_Gets() {
   TestFramework::BeginTest("Test Stats: Gets");
   Stats pokemonStats = Stats(98, 102, 97, 95, 99, 101);
   // check all stats
   TEST_ASSERT(98 == pokemonStats.getTotalHeath());
   TEST_ASSERT(102 == pokemonStats.getAttack());
   TEST_ASSERT(97 == pokemonStats.getSpecialAttack());
   TEST_ASSERT(95 == pokemonStats.getDefense());
   TEST_ASSERT(99 == pokemonStats.getSpecialDefense());
   TEST_ASSERT(101 == pokemonStats.getSpeed());
   TestFramework::EndTest();
}

void TestStats_HealthChanges() {
   TestFramework::BeginTest("Test Stats: Health Changes");
   Stats pokemonStats = Stats(98, 102, 97, 95, 99, 101);
   TEST_ASSERT(98 == pokemonStats.getCurrentHeath());
   // apply damage and check changes
   pokemonStats.damageToHealth(8);
   TEST_ASSERT(90 == pokemonStats.getCurrentHeath());
   pokemonStats.damagePercentToHealth(.1);
   TEST_ASSERT(81 == pokemonStats.getCurrentHeath());
   pokemonStats.healHealth(9);
   TEST_ASSERT(90 == pokemonStats.getCurrentHeath());
   pokemonStats.healPercentageHealth(.1);
   TEST_ASSERT(98 == pokemonStats.getCurrentHeath());
   TestFramework::EndTest();
}

void TestStats_Modifiers() {
   TestFramework::BeginTest("TestStats Modifiers");
   Stats pokemonStats = Stats(98, 102, 97, 95, 99, 101);
   TEST_ASSERT(102 == pokemonStats.getStatValueByName("attack"));
   TEST_ASSERT(0 == pokemonStats.getModifierByName("special attack"));
   TEST_ASSERT(95 == pokemonStats.getModifiedStatValue("defense"));
   TEST_ASSERT(pokemonStats.canModifierBeChanged("special defense", 1));
   // change modifier and check stat modifier and modified stat value has been change
   pokemonStats.changeModifier("speed", 2);
   TEST_ASSERT(2 == pokemonStats.getModifierByName("speed"));
   TEST_ASSERT(202 == pokemonStats.getModifiedStatValue("speed"));
   TEST_ASSERT(!pokemonStats.canModifierBeChanged("speed", 5));
   pokemonStats.addStatusConditionModifier("attack", .5);
   TEST_ASSERT(51 == pokemonStats.getModifiedStatValue("attack"));
   pokemonStats.resetModifiers();
   TEST_ASSERT(0 == pokemonStats.getModifierByName("speed"));
   TEST_ASSERT(51 == pokemonStats.getModifiedStatValue("attack"));
   pokemonStats.clearStatusConditionModifier();
   TEST_ASSERT(102 == pokemonStats.getModifiedStatValue("attack"));
   pokemonStats.cannotMiss();
   TEST_ASSERT(334.33333333333331 == pokemonStats.getModifiedStatValue("accuracy"));
   pokemonStats.changeModifier("evasion", 3);
   TEST_ASSERT(3 == pokemonStats.getModifierByName("evasion"));
   TEST_ASSERT(2 == pokemonStats.getModifiedStatValue("evasion"));
   TestFramework::EndTest();
}

void PokemonStadium::TestStats() {
   TestStats_Gets();
   TestStats_HealthChanges();
   TestStats_Modifiers();
}

void TestWeather_ClearSkies() {
   TestFramework::BeginTest("Test Weather: ClearSkies");
   Weather battleWeather = clear_skies;
   // confirm battleWeather shows clear skies
   TEST_ASSERT("clear" == battleWeather.getName());
   TEST_ASSERT(0 == battleWeather.getTurnsSinceStarted());
   TEST_ASSERT("The skies become clear" == battleWeather.getStartingOutput());
   TEST_ASSERT("" == battleWeather.getStillActiveOutput());
   TEST_ASSERT("" == battleWeather.getEndingOutput());
   TEST_ASSERT(battleWeather.noWeather());
   TestFramework::EndTest();
}
void TestWeather_ChangePowerWeather() {
   TestFramework::BeginTest("Test Weather: ChangePowerWeather");
   ChangePowerWeather battleWeather = harsh_sun;
   TEST_ASSERT("harsh sun" == battleWeather.getName());
   TEST_ASSERT("The sunlight turned harsh!" == battleWeather.getStartingOutput());
   TEST_ASSERT(0 == battleWeather.getTurnsSinceStarted());
   TEST_ASSERT(!battleWeather.noWeather());
   // count turns until Weather Time Max is reach and see if
   // getTurnsSinceStarted and WeatherStill Acitve are correct
   for (size_t turns = 0; turns < WEATHER_TIME_MAX; turns++) {
      TEST_ASSERT(turns == battleWeather.getTurnsSinceStarted());
      TEST_ASSERT(battleWeather.weatherStillActive());
      TEST_ASSERT("The sunlight is strong." == battleWeather.getStillActiveOutput());
   }
   TEST_ASSERT(!battleWeather.weatherStillActive());
   TEST_ASSERT("The harsh sunlight faded." == battleWeather.getEndingOutput());

   // Harsh sun increase damage type = fire
   vector<Type> increaseDamageTypes = battleWeather.getIncreaseDamageTypes();
   for (auto & type : increaseDamageTypes) {
      TEST_ASSERT(type == type_fire);
   }

   // Harsh sun decrease damage type = water
   vector<Type> decreaseDamageTypes = battleWeather.getDecreaseDamageTypes();
   for (auto & type : decreaseDamageTypes) {
      TEST_ASSERT(type == type_water);
   }
   TEST_ASSERT(1 == battleWeather.typeStatMultiplier(type_grass));
   TEST_ASSERT(1.5 == battleWeather.typeStatMultiplier(type_fire));
   TEST_ASSERT(.5 == battleWeather.typeStatMultiplier(type_water));
   TestFramework::EndTest();
}

void TestWeather_DamageWeather() {
   TestFramework::BeginTest("Test Weather: DamageWeather");
   DamageWeather battleWeather = hail;
   TEST_ASSERT("hail" == battleWeather.getName());
   TEST_ASSERT("It started to hail!" == battleWeather.getStartingOutput());
   TEST_ASSERT(0 == battleWeather.getTurnsSinceStarted());
   TEST_ASSERT(!battleWeather.noWeather());
   // count turns until Weather Time Max is reach and see if
   // getTurnsSinceStarted and WeatherStill Acitve are correct
   for (size_t turns = 0; turns < WEATHER_TIME_MAX; turns++) {
      TEST_ASSERT(turns == battleWeather.getTurnsSinceStarted());
      TEST_ASSERT(battleWeather.weatherStillActive());
      TEST_ASSERT("Hail continues to fall." == battleWeather.getStillActiveOutput());
   }
   TEST_ASSERT(!battleWeather.weatherStillActive());
   TEST_ASSERT("The hail stopped." == battleWeather.getEndingOutput());

   // Hail no damage type = ice
   vector<Type> noDamageTypes = battleWeather.getNoDamageTypes();
   for (auto & type : noDamageTypes) {
      TEST_ASSERT(type == type_ice);
   }
   Stats pokemonStats = Stats(98, 102, 97, 95, 99, 101);
   // apply weather damages to a type on the non damage list
   // and confirm no damage has been applied
   battleWeather.applyWeatherDamages(&pokemonStats, type_ice, type_bug);
   TEST_ASSERT(98 == pokemonStats.getCurrentHeath());
   battleWeather.applyWeatherDamages(&pokemonStats, type_rock, type_ice);
   TEST_ASSERT(98 == pokemonStats.getCurrentHeath());
   // apply weather damages and confirm damages has been applied
   battleWeather.applyWeatherDamages(&pokemonStats, type_water);
   TEST_ASSERT(92 == pokemonStats.getCurrentHeath());
   TestFramework::EndTest();
}

void PokemonStadium::TestWeather() {
   TestWeather_ClearSkies();
   TestWeather_ChangePowerWeather();
   TestWeather_DamageWeather();
}

void TestStatusCondition_NoStatusCondition() {
   TestFramework::BeginTest("Test StatusCondition: No Status Condition");
   StatusCondition pokemonStatusCondition = StatusCondition();
   TEST_ASSERT("" == pokemonStatusCondition.getCondition());
   TEST_ASSERT(!pokemonStatusCondition.isConfused());
   // apply post effect and confirm no changes made to modified stats
   Stats pokemonStats = Stats(98, 102, 97, 95, 99, 101);
   // no pre affect pokemon should be able to attack
   TEST_ASSERT(!pokemonStatusCondition.applyPreAffects(&pokemonStats));
   pokemonStatusCondition.applyPostAffect(&pokemonStats);
   TEST_ASSERT(98 == pokemonStats.getCurrentHeath());
   TEST_ASSERT(102 == pokemonStats.getModifiedStatValue("attack"));
   TEST_ASSERT(97 == pokemonStats.getModifiedStatValue("special attack"));
   TEST_ASSERT(95 == pokemonStats.getModifiedStatValue("defense"));
   TEST_ASSERT(99 == pokemonStats.getModifiedStatValue("special defense"));
   TEST_ASSERT(101 == pokemonStats.getModifiedStatValue("speed"));
   TestFramework::EndTest();
}

void TestStatusCondition_Asleep() {
   TestFramework::BeginTest("Test StatusCondition: Asleep");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatusCondition pokemonStatusCondition = StatusCondition(co);
   Stats pokemonStats = Stats(98, 102, 97, 95, 99, 101);
   pokemonStatusCondition.setCondition("asleep", &pokemonStats);
   TEST_ASSERT("User is asleep\n" == ss.str());
   TEST_ASSERT("asleep" == pokemonStatusCondition.getCondition());
   TEST_ASSERT(!pokemonStatusCondition.isConfused());
   // confirm all stats have not been modified
   TEST_ASSERT(102 == pokemonStats.getModifiedStatValue("attack"));
   TEST_ASSERT(97 == pokemonStats.getModifiedStatValue("special attack"));
   TEST_ASSERT(95 == pokemonStats.getModifiedStatValue("defense"));
   TEST_ASSERT(99 == pokemonStats.getModifiedStatValue("special defense"));
   TEST_ASSERT(101 == pokemonStats.getModifiedStatValue("speed"));
   // sleep turns set a random number that the pokemon should be asleep
   // for. Loop through the set amount and confirm it returns
   // turn for sleep length
   int sleepTurns = pokemonStatusCondition.getSleepTurns();
   for (int turn = 0; turn < sleepTurns; turn++) {
      ss.str("");
      TEST_ASSERT(pokemonStatusCondition.applyPreAffects(&pokemonStats));
      TEST_ASSERT("User is fast asleep\n" == ss.str());
   }
   ss.str("");
   // Pokemon should be awake and able to attack
   TEST_ASSERT(!pokemonStatusCondition.applyPreAffects(&pokemonStats));
   TEST_ASSERT("User woke up\n" == ss.str());
   // apply post effect and confirm no changes made to current health
   pokemonStatusCondition.applyPostAffect(&pokemonStats);
   TEST_ASSERT(98 == pokemonStats.getCurrentHeath());
   delete co;
   TestFramework::EndTest();
}

void TestStatusCondition_Burned() {
   TestFramework::BeginTest("Test StatusCondition: Burned");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatusCondition pokemonStatusCondition = StatusCondition(co);
   Stats pokemonStats = Stats(98, 102, 97, 95, 99, 101);
   pokemonStatusCondition.setCondition("burned", &pokemonStats);
   TEST_ASSERT("burned" == pokemonStatusCondition.getCondition());
   TEST_ASSERT("User is burned\n" == ss.str());
   TEST_ASSERT(!pokemonStatusCondition.isConfused());
   // confirm that attack is the only stat that has been modified
   TEST_ASSERT(51 == pokemonStats.getModifiedStatValue("attack"));
   TEST_ASSERT(97 == pokemonStats.getModifiedStatValue("special attack"));
   TEST_ASSERT(95 == pokemonStats.getModifiedStatValue("defense"));
   TEST_ASSERT(99 == pokemonStats.getModifiedStatValue("special defense"));
   TEST_ASSERT(101 == pokemonStats.getModifiedStatValue("speed"));
   // burn does not have a pre affect
   TEST_ASSERT(!pokemonStatusCondition.applyPreAffects(&pokemonStats));
   // apply post effect and confirm changes made to current health
   pokemonStatusCondition.applyPostAffect(&pokemonStats);
   TEST_ASSERT(92 == pokemonStats.getCurrentHeath());
   delete co;
   TestFramework::EndTest();
}
void TestStatusCondition_Frozen() {
   TestFramework::BeginTest("Test StatusCondition: Frozen");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatusCondition pokemonStatusCondition = StatusCondition(co);
   Stats pokemonStats = Stats(98, 102, 97, 95, 99, 101);
   pokemonStatusCondition.setCondition("frozen", &pokemonStats);
   TEST_ASSERT("frozen" == pokemonStatusCondition.getCondition());
   TEST_ASSERT(!pokemonStatusCondition.isConfused());
   // confirm all stats have not been modified
   TEST_ASSERT(102 == pokemonStats.getModifiedStatValue("attack"));
   TEST_ASSERT(97 == pokemonStats.getModifiedStatValue("special attack"));
   TEST_ASSERT(95 == pokemonStats.getModifiedStatValue("defense"));
   TEST_ASSERT(99 == pokemonStats.getModifiedStatValue("special defense"));
   TEST_ASSERT(101 == pokemonStats.getModifiedStatValue("speed"));
   // pokemon remains frozen until break dethawn chances is hit
   while (pokemonStatusCondition.applyPreAffects(&pokemonStats)) {}
   // apply post effect and confirm no changes made to stats
   pokemonStatusCondition.applyPostAffect(&pokemonStats);
   TEST_ASSERT(98 == pokemonStats.getCurrentHeath());
   delete co;
   TestFramework::EndTest();
}
void TestStatusCondition_Paralyzed() {
   TestFramework::BeginTest("Test StatusCondition: Paralyzed");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatusCondition pokemonStatusCondition = StatusCondition(co);
   Stats pokemonStats = Stats(98, 102, 97, 95, 99, 101);
   pokemonStatusCondition.setCondition("paralyzed", &pokemonStats);
   TEST_ASSERT("paralyzed" == pokemonStatusCondition.getCondition());
   TEST_ASSERT(!pokemonStatusCondition.isConfused());
   // confirm the speed is the only stat that has been modified
   TEST_ASSERT(102 == pokemonStats.getModifiedStatValue("attack"));
   TEST_ASSERT(97 == pokemonStats.getModifiedStatValue("special attack"));
   TEST_ASSERT(95 == pokemonStats.getModifiedStatValue("defense"));
   TEST_ASSERT(99 == pokemonStats.getModifiedStatValue("special defense"));
   TEST_ASSERT(50.5 == pokemonStats.getModifiedStatValue("speed"));
   bool attackBlocked = false;
   bool attackProceed = false;
   // Loop through until you get a case of confusion blocking
   // attack and attack not being blocked while still being confused
   while ((!attackBlocked) || (!attackProceed)) {
      bool temp = pokemonStatusCondition.applyPreAffects(&pokemonStats);
      if (temp) {
         attackBlocked = true;
      }
      else {
         attackProceed = true;
      }
   }
   TEST_ASSERT(attackBlocked);
   TEST_ASSERT(attackProceed);
   // apply post effect and confirm no changes to health
   pokemonStatusCondition.applyPostAffect(&pokemonStats);
   TEST_ASSERT(98 == pokemonStats.getCurrentHeath());
   delete co;
   TestFramework::EndTest();
}
void TestStatusCondition_Poison() {
   TestFramework::BeginTest("Test StatusCondition: Poison");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatusCondition pokemonStatusCondition = StatusCondition(co);
   Stats pokemonStats = Stats(98, 102, 97, 95, 99, 101);
   pokemonStatusCondition.setCondition("poison", &pokemonStats);
   TEST_ASSERT("poison" == pokemonStatusCondition.getCondition());
   TEST_ASSERT(!pokemonStatusCondition.isConfused());
   // confirm all stats have not been modified
   TEST_ASSERT(102 == pokemonStats.getModifiedStatValue("attack"));
   TEST_ASSERT(97 == pokemonStats.getModifiedStatValue("special attack"));
   TEST_ASSERT(95 == pokemonStats.getModifiedStatValue("defense"));
   TEST_ASSERT(99 == pokemonStats.getModifiedStatValue("special defense"));
   TEST_ASSERT(101 == pokemonStats.getModifiedStatValue("speed"));
   // burn does not have a pre affect
   TEST_ASSERT(!pokemonStatusCondition.applyPreAffects(&pokemonStats));
   // apply post effect and confirm changes made to current health
   pokemonStatusCondition.applyPostAffect(&pokemonStats);
   TEST_ASSERT(86 == pokemonStats.getCurrentHeath());
   pokemonStatusCondition.applyPostAffect(&pokemonStats);
   TEST_ASSERT(74 == pokemonStats.getCurrentHeath());
   delete co;
   TestFramework::EndTest();
}

void TestStatusCondition_BadlyPoison() {
   TestFramework::BeginTest("Test StatusCondition: Badly Poison");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatusCondition pokemonStatusCondition = StatusCondition(co);
   Stats pokemonStats = Stats(98, 102, 97, 95, 99, 101);
   pokemonStatusCondition.setCondition("badly poison", &pokemonStats);
   TEST_ASSERT("poison" == pokemonStatusCondition.getCondition());
   TEST_ASSERT(!pokemonStatusCondition.isConfused());
   // confirm all stats have not been modified
   TEST_ASSERT(102 == pokemonStats.getModifiedStatValue("attack"));
   TEST_ASSERT(97 == pokemonStats.getModifiedStatValue("special attack"));
   TEST_ASSERT(95 == pokemonStats.getModifiedStatValue("defense"));
   TEST_ASSERT(99 == pokemonStats.getModifiedStatValue("special defense"));
   TEST_ASSERT(101 == pokemonStats.getModifiedStatValue("speed"));
   // burn does not have a pre affect
   TEST_ASSERT(!pokemonStatusCondition.applyPreAffects(&pokemonStats));
   // apply post effect and confirm changes made to current health
   pokemonStatusCondition.applyPostAffect(&pokemonStats);
   TEST_ASSERT(86 == pokemonStats.getCurrentHeath());
   pokemonStatusCondition.applyPostAffect(&pokemonStats);
   TEST_ASSERT(68 == pokemonStats.getCurrentHeath());
   delete co;
   TestFramework::EndTest();
}

void TestStatusCondition_Confusion() {
   TestFramework::BeginTest("Test StatusCondition: Confusion");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatusCondition pokemonStatusCondition = StatusCondition(co);
   Stats pokemonStats = Stats(98, 102, 97, 95, 99, 101);
   pokemonStatusCondition.setConfusion();
   TEST_ASSERT("" == pokemonStatusCondition.getCondition());
   TEST_ASSERT(pokemonStatusCondition.isConfused());
   // confirm all stats have not been modified
   TEST_ASSERT(102 == pokemonStats.getModifiedStatValue("attack"));
   TEST_ASSERT(97 == pokemonStats.getModifiedStatValue("special attack"));
   TEST_ASSERT(95 == pokemonStats.getModifiedStatValue("defense"));
   TEST_ASSERT(99 == pokemonStats.getModifiedStatValue("special defense"));
   TEST_ASSERT(101 == pokemonStats.getModifiedStatValue("speed"));
   // apply post effect and confirm no changes made to current health
   pokemonStatusCondition.applyPostAffect(&pokemonStats);
   TEST_ASSERT(98 == pokemonStats.getCurrentHeath());
   bool attackBlocked = false;
   bool attackProceed = false;
   // Loop through until you get a case of confusion blocking
   // attack and attack not being blocked while still being confused
   while (!attackBlocked || !attackProceed) {
      bool temp = pokemonStatusCondition.applyPreAffects(&pokemonStats);
      if (pokemonStatusCondition.isConfused()) {
         if (temp) {
            attackBlocked = true;
         }
         else {
            attackProceed = true;
         }
      }
      // if confusion has been unset before gettting both case
      // reset confusion
      else {
         pokemonStatusCondition.setConfusion();
      }
   }
   TEST_ASSERT(attackBlocked);
   TEST_ASSERT(attackProceed);

   Stats test2 = Stats(300, 102, 97, 95, 99, 101);
   while (!pokemonStatusCondition.applyPreAffects(&test2)) {
      if (!pokemonStatusCondition.isConfused()) {
         pokemonStatusCondition.setConfusion();
      }
   }
   TEST_ASSERT(283 == test2.getCurrentHeath());
   delete co;
   TestFramework::EndTest();
}

void PokemonStadium::TestStatusCondition() {
   TestStatusCondition_NoStatusCondition();
   TestStatusCondition_Asleep(); 
   TestStatusCondition_Burned();
   TestStatusCondition_Frozen();
   TestStatusCondition_Paralyzed();
   TestStatusCondition_Poison();
   TestStatusCondition_BadlyPoison();
   TestStatusCondition_Confusion();
}

void TestDamageMove_DamageMoveNoExtras() {
   TestFramework::BeginTest("Test DamageMove: Damage Move No Extras");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   DamageMove test1 = DamageMove(co, "test", type_bug, "physical", 15, 50, 100, "test bug type physical, 50 power 100% accuracy move");
   // check battle move gets
   TEST_ASSERT(100 == test1.getAccuracy());
   TEST_ASSERT("physical" == test1.getCategory());
   TEST_ASSERT(test1.getChangeAccuracyTo().empty());
   TEST_ASSERT(test1.getChangeAccuracyWeather().empty());
   TEST_ASSERT(15 == test1.getCurrentPP());
   TEST_ASSERT("test bug type physical, 50 power 100% accuracy move" == test1.getDescription());
   TEST_ASSERT("test" == test1.getName());
   TEST_ASSERT(NULL == test1.getOtherEffect());
   TEST_ASSERT(50 == test1.getPower());
   TEST_ASSERT(0 == test1.getSelfDamage());
   TEST_ASSERT(15 == test1.getTotalPP());
   TEST_ASSERT(type_bug == test1.getType());
   TEST_ASSERT(!test1.isMovedLocked());
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // use battle move
   test1.useDamageMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_water, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_fire, type_dark);
   TEST_ASSERT(!test1.isMovedLocked());
   // check results after using battle move
   TEST_ASSERT(14 == test1.getCurrentPP());
   TEST_ASSERT(56 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(79 == attackingPOKEMONSTADIUM_stats.getCurrentHeath());
   delete co;
   TestFramework::EndTest();
}

void TestDamageMove_DamageMoveSelfDamage() {
   TestFramework::BeginTest("Test DamageMove: Damage Move Self");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   DamageMove test1 = DamageMove(co, "test", type_normal, "physical", 15, 50, 100, 
      "test normal type physical, 50 power 100% accuracy move with self damage", 
      true, .25);
   TEST_ASSERT(100 == test1.getAccuracy());
   TEST_ASSERT("physical" == test1.getCategory());
   TEST_ASSERT(test1.getChangeAccuracyTo().empty());
   TEST_ASSERT(test1.getChangeAccuracyWeather().empty());
   TEST_ASSERT(15 == test1.getCurrentPP());
   TEST_ASSERT("test normal type physical, 50 power 100% accuracy move with self damage" == test1.getDescription());
   TEST_ASSERT("test" == test1.getName());
   TEST_ASSERT(NULL == test1.getOtherEffect());
   TEST_ASSERT(50 == test1.getPower());
   TEST_ASSERT(.25 == test1.getSelfDamage());
   TEST_ASSERT(15 == test1.getTotalPP());
   TEST_ASSERT(type_normal == test1.getType());
   Stats attackingPOKEMONSTADIUM_stats
      = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   test1.useDamageMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_water, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_fire, type_dark);
   TEST_ASSERT(14 == test1.getCurrentPP());
   TEST_ASSERT(56 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(74 == attackingPOKEMONSTADIUM_stats.getCurrentHeath());
   delete co;
   TestFramework::EndTest();
}

void TestDamageMove_DamageMoveBattleEffect() {
   TestFramework::BeginTest("Test DamageMove: Damage Move Battle Effect");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatusConditionEffect paraylze = StatusConditionEffect(co, 100, "paralyzed");
   DamageMove *test1 = new DamageMove(co, "test", type_ground, "physical", 15, 50, 100, 
      "test ground type physical, 50 power 100% accuracy move with extra effect",
      &paraylze
   );
   TEST_ASSERT(100 == test1->getAccuracy());
   TEST_ASSERT("physical" == test1->getCategory());
   TEST_ASSERT(test1->getChangeAccuracyTo().empty());
   TEST_ASSERT(test1->getChangeAccuracyWeather().empty());
   TEST_ASSERT(15 == test1->getCurrentPP());
   TEST_ASSERT("test ground type physical, 50 power 100% accuracy move with extra effect" == test1->getDescription());
   TEST_ASSERT("test" == test1->getName());
   TEST_ASSERT(NULL != test1->getOtherEffect());
   TEST_ASSERT(50 == test1->getPower());
   TEST_ASSERT(0 == test1->getSelfDamage());
   TEST_ASSERT(15 == test1->getTotalPP());
   TEST_ASSERT(type_ground == test1->getType());
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // use battle move and check damage applied
   test1->useDamageMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_water, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_bug, type_grass);
   TEST_ASSERT(14 == test1->getCurrentPP());
   TEST_ASSERT(73 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(79 == attackingPOKEMONSTADIUM_stats.getCurrentHeath());
   // check effect landed
   TEST_ASSERT("paralyzed" == defendingPokemonStatusCondition.getCondition());
   Stats electricPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition electricPokemonStatusCondition = StatusCondition(co);
   test1->useDamageMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_water, Type(),
      &electricPOKEMONSTADIUM_stats, &electricPokemonStatusCondition, type_electric, type_water);
   TEST_ASSERT("" == electricPokemonStatusCondition.getCondition());
   delete test1;
   delete co;
   TestFramework::EndTest();
}

void TestDamageMove_DamageMoveWeatherAccuracyInc() {
   TestFramework::BeginTest("Test DamageMove: Damage Move Weather Accuracy Increase");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   DamageMove test1 = DamageMove(co, "test", type_electric, "special", 15, 110, 10,
      "test electric type special, 110 power 10% accuracy move",
      {rain}, {100}
   );
   
   TEST_ASSERT(10 == test1.getAccuracy());
   TEST_ASSERT("special" == test1.getCategory());
   vector<Weather> moveAccWeather = test1.getChangeAccuracyWeather();
   // confirm rain is only weather in list
   for (auto & weather : moveAccWeather) {
      TEST_ASSERT(weather == rain);
   }
   vector<double> moveAccWeatherIncrease = test1.getChangeAccuracyTo();
   // confirm 100 is only number in list
   for (auto & acc : moveAccWeatherIncrease) {
      TEST_ASSERT(acc == 100);
   }
   TEST_ASSERT(15 == test1.getCurrentPP());
   TEST_ASSERT("test electric type special, 110 power 10% accuracy move" == test1.getDescription());
   TEST_ASSERT("test" == test1.getName());
   TEST_ASSERT(NULL == test1.getOtherEffect());
   TEST_ASSERT(110 == test1.getPower());
   TEST_ASSERT(0 == test1.getSelfDamage());
   TEST_ASSERT(15 == test1.getTotalPP());
   TEST_ASSERT(type_electric == test1.getType());
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // use move with clear skies to see move missed
   test1.useDamageMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_water, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_flying, type_water);
   TEST_ASSERT(14 == test1.getCurrentPP());
   TEST_ASSERT(78 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(79 == attackingPOKEMONSTADIUM_stats.getCurrentHeath());
   // use move with while raining to see accuraccy increase
   test1.useDamageMove(&rain,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_water, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_flying, type_water);
   TEST_ASSERT(13 == test1.getCurrentPP());
   TEST_ASSERT(0 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(79 == attackingPOKEMONSTADIUM_stats.getCurrentHeath());
   delete co;
   TestFramework::EndTest();
}

void TestDamageMove_DamageMoveBattleEffectWeatherInc() {
   TestFramework::BeginTest("Test DamageMove: Damage Move Weather Accuracy Increase & Extra Effect");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatChangingEffect decreaseDefense = StatChangingEffect(co, 100, 
      {"defense"}, {"fell"}, {false});
   DamageMove *test1 = new DamageMove(co, "test", type_fire, "special", 15, 50, 10,
      "test fire type special, 110 power 10% accuracy move with extra effect",
      &decreaseDefense, {harsh_sun}, {100}
   );

   TEST_ASSERT(10 == test1->getAccuracy());
   TEST_ASSERT("special" == test1->getCategory());
   vector<Weather> moveAccWeather = test1->getChangeAccuracyWeather();
   for (auto & weather : moveAccWeather) {
      TEST_ASSERT(weather == harsh_sun);
   }
   vector<double> moveAccWeatherIncrease = test1->getChangeAccuracyTo();
   for (auto & acc : moveAccWeatherIncrease) {
      TEST_ASSERT(acc == 100);
   }
   TEST_ASSERT(15 == test1->getCurrentPP());
   TEST_ASSERT("test fire type special, 110 power 10% accuracy move with extra effect" == test1->getDescription());
   TEST_ASSERT("test" == test1->getName());
   TEST_ASSERT(NULL != test1->getOtherEffect());
   TEST_ASSERT(50 == test1->getPower());
   TEST_ASSERT(0 == test1->getSelfDamage());
   TEST_ASSERT(15 == test1->getTotalPP());
   TEST_ASSERT(type_fire == test1->getType());
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // use move in clear skies to see move missed and effect didn't apply
   test1->useDamageMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_water, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_flying, type_water);
   TEST_ASSERT(14 == test1->getCurrentPP());
   TEST_ASSERT(78 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(79 == attackingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(0 == defendingPOKEMONSTADIUM_stats.getModifierByName("defense"));
   // use move in harsh sun to see move is more powerful
   test1->useDamageMove(&harsh_sun,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_water, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_dragon, type_grass);
   TEST_ASSERT(13 == test1->getCurrentPP());
   // if change power wasn't in effect hp would equal 56
   TEST_ASSERT(45 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(79 == attackingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(-1 == defendingPOKEMONSTADIUM_stats.getModifierByName("defense"));
   delete test1;
   delete co;
   TestFramework::EndTest();
}
void PokemonStadium::TestDamageMove() {
   TestDamageMove_DamageMoveNoExtras();
   TestDamageMove_DamageMoveSelfDamage();
   TestDamageMove_DamageMoveBattleEffect();
   TestDamageMove_DamageMoveWeatherAccuracyInc();
   TestDamageMove_DamageMoveBattleEffectWeatherInc();
}

void TestChargeMove_ChargeMoveNoExtras() {
   TestFramework::BeginTest("Test ChargeMove: Charge Move No Extras");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   ChargeMove test1 = ChargeMove(co, "test", type_dark, "physical", 10, 120, 100, 
      "test dark type physical, 120 power 100% accuracy move that needs a turn to charge",
      "charge"
   );
   TEST_ASSERT(100 == test1.getAccuracy());
   TEST_ASSERT("physical" == test1.getCategory());
   TEST_ASSERT(test1.getChangeAccuracyTo().empty());
   TEST_ASSERT(test1.getChangeAccuracyWeather().empty());
   TEST_ASSERT(10 == test1.getCurrentPP());
   TEST_ASSERT("test dark type physical, 120 power 100% accuracy move that needs a turn to charge" == test1.getDescription());
   TEST_ASSERT("test" == test1.getName());
   TEST_ASSERT(NULL == test1.getOtherEffect());
   TEST_ASSERT(120 == test1.getPower());
   TEST_ASSERT(0 == test1.getSelfDamage());
   TEST_ASSERT(10 == test1.getTotalPP());
   TEST_ASSERT(type_dark == test1.getType());
   TEST_ASSERT("charge" == test1.getWaitTurnDescription());
   TEST_ASSERT(!test1.isMovedLocked());
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // use move on, confirm no damage done because move is charing
   test1.useChargeMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_ground, type_rock,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_rock, Type());
   TEST_ASSERT(9 == test1.getCurrentPP());
   TEST_ASSERT(78 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(test1.isMovedLocked());
   // use move again, see damage has been done and move is unlocked
   test1.useChargeMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_ground, type_rock,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_rock, Type());
   TEST_ASSERT(9 == test1.getCurrentPP());
   TEST_ASSERT(26 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(!test1.isMovedLocked());
   delete co;
   TestFramework::EndTest();
}

void TestChargeMove_ChargeMoveExtraDuringCharge() {
   TestFramework::BeginTest("Test ChargeMove: Charge Move Extra Effect During Charge");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatChangingEffect increaseDefense = StatChangingEffect(co, 100, 
      {"defense"}, {"rose"}, {true});
   ChargeMove *test1 = new ChargeMove(co, "test", type_normal, "physical", 10, 120, 100,
      "test normal type physical, 120 power 100% accuracy move that raise defense during charging turn",
      &increaseDefense, true,
      "lowers its head"
   );
   TEST_ASSERT(100 == test1->getAccuracy());
   TEST_ASSERT("physical" == test1->getCategory());
   TEST_ASSERT(test1->getChangeAccuracyTo().empty());
   TEST_ASSERT(test1->getChangeAccuracyWeather().empty());
   TEST_ASSERT(10 == test1->getCurrentPP());
   TEST_ASSERT("test normal type physical, 120 power 100% accuracy move that raise defense during charging turn" == test1->getDescription());
   TEST_ASSERT("test" == test1->getName());
   TEST_ASSERT(NULL != test1->getOtherEffect());
   TEST_ASSERT(120 == test1->getPower());
   TEST_ASSERT(0 == test1->getSelfDamage());
   TEST_ASSERT(10 == test1->getTotalPP());
   TEST_ASSERT(type_normal == test1->getType());
   TEST_ASSERT("lowers its head" == test1->getWaitTurnDescription());
   TEST_ASSERT(!test1->isMovedLocked());
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // use move, move is charging and effect applies
   test1->useChargeMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_normal, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_water, type_grass);
   TEST_ASSERT(9 == test1->getCurrentPP());
   TEST_ASSERT(78 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(test1->isMovedLocked());
   TEST_ASSERT(1 == attackingPOKEMONSTADIUM_stats.getModifierByName("defense"));
   // use move again, damage is applied, effect doesn't apply again
   test1->useChargeMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_normal, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_water, type_grass);
   TEST_ASSERT(9 == test1->getCurrentPP());
   TEST_ASSERT(0 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(!test1->isMovedLocked());
   TEST_ASSERT(1 == attackingPOKEMONSTADIUM_stats.getModifierByName("defense"));
   delete test1;
   delete co;
   TestFramework::EndTest();
}

void TestChargeMove_ChargeMoveExtraAfterCharge() {
   TestFramework::BeginTest("Test ChargeMove: Charge Move Extra Effect After Charge");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatusConditionEffect burnEffect = StatusConditionEffect(co, 100, "burned");
   ChargeMove *test1 = new ChargeMove(co, "test", type_fire, "special", 10, 100, 100,
      "test type fire, 100 power 100% accuracy move that burns the pokemon after landed",
      &burnEffect, false,
      "charge a fire shot"
   );
   TEST_ASSERT(100 == test1->getAccuracy());
   TEST_ASSERT("special" == test1->getCategory());
   TEST_ASSERT(test1->getChangeAccuracyTo().empty());
   TEST_ASSERT(test1->getChangeAccuracyWeather().empty());
   TEST_ASSERT(10 == test1->getCurrentPP());
   TEST_ASSERT("test type fire, 100 power 100% accuracy move that burns the pokemon after landed" == test1->getDescription());
   TEST_ASSERT("test" == test1->getName());
   TEST_ASSERT(NULL != test1->getOtherEffect());
   TEST_ASSERT(100 == test1->getPower());
   TEST_ASSERT(0 == test1->getSelfDamage());
   TEST_ASSERT(10 == test1->getTotalPP());
   TEST_ASSERT(type_fire == test1->getType());
   TEST_ASSERT("charge a fire shot" == test1->getWaitTurnDescription());
   TEST_ASSERT(!test1->isMovedLocked());
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // use move, move is charging, no effect applies
   test1->useChargeMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_normal, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_water, type_grass);
   TEST_ASSERT(9 == test1->getCurrentPP());
   TEST_ASSERT(78 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(test1->isMovedLocked());
   TEST_ASSERT("" == defendingPokemonStatusCondition.getCondition());
   // use move, damages apply and effect applies
   test1->useChargeMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_normal, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_water, type_grass);
   TEST_ASSERT(9 == test1->getCurrentPP());
   int defending = defendingPOKEMONSTADIUM_stats.getCurrentHeath();
   TEST_ASSERT(34 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(!test1->isMovedLocked());
   TEST_ASSERT("burned" == defendingPokemonStatusCondition.getCondition());
   delete test1;
   delete co;
   TestFramework::EndTest();
}

void TestChargeMove_ChargeMoveNoChargeWeather() {
   TestFramework::BeginTest("Test ChargeMove: Charge Move No Charge Weather");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   ChargeMove test1 = ChargeMove(co, "test", type_grass, "special", 10, 10, 100,
      "test grass type special, 10 power 100% accuracy move that takes in sunlight",
      "absorb sunglight",
      {harsh_sun}
   );
   TEST_ASSERT(100 == test1.getAccuracy());
   TEST_ASSERT("special" == test1.getCategory());
   TEST_ASSERT(test1.getChangeAccuracyTo().empty());
   TEST_ASSERT(test1.getChangeAccuracyWeather().empty());
   TEST_ASSERT(10 == test1.getCurrentPP());
   TEST_ASSERT("test grass type special, 10 power 100% accuracy move that takes in sunlight" == test1.getDescription());
   TEST_ASSERT("test" == test1.getName());
   TEST_ASSERT(NULL == test1.getOtherEffect());
   TEST_ASSERT(10 == test1.getPower());
   TEST_ASSERT(0 == test1.getSelfDamage());
   TEST_ASSERT(10 == test1.getTotalPP());
   TEST_ASSERT(type_grass == test1.getType());
   TEST_ASSERT("absorb sunglight" == test1.getWaitTurnDescription());
   TEST_ASSERT(!test1.isMovedLocked());
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // use move in clear skies, move is charging
   test1.useChargeMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_water, type_grass,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_normal, Type());
   TEST_ASSERT(9 == test1.getCurrentPP());
   int health = defendingPOKEMONSTADIUM_stats.getCurrentHeath();
   TEST_ASSERT(78 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(test1.isMovedLocked());
   // use move again, damage applies
   test1.useChargeMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_water, type_grass,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_normal, Type());
   TEST_ASSERT(9 == test1.getCurrentPP());
   health = defendingPOKEMONSTADIUM_stats.getCurrentHeath();
   TEST_ASSERT(72 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(!test1.isMovedLocked());
   // use move in harsh sun, see move charged and applies damages
   test1.useChargeMove(&harsh_sun,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_water, type_grass,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_normal, Type());
   TEST_ASSERT(8 == test1.getCurrentPP());
   health = defendingPOKEMONSTADIUM_stats.getCurrentHeath();
   TEST_ASSERT(66 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(!test1.isMovedLocked());
   delete co;
   TestFramework::EndTest();
}

void PokemonStadium::TestChargeMove() {
   TestChargeMove_ChargeMoveNoExtras();
   TestChargeMove_ChargeMoveExtraDuringCharge();
   TestChargeMove_ChargeMoveExtraAfterCharge();
   TestChargeMove_ChargeMoveNoChargeWeather();
}

void TestHiddenMove_HiddenMoveGets() {
   TestFramework::BeginTest("Test HiddenMove: Hidden Move Gets");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   HiddenMove test1 = HiddenMove(co, "test", type_ground, "physical", 10, 80, 100,
      "test ground type physical move that pokemon digs itself underground first before attacking",
      "dug itself underground"
   );
   // check gets of move
   TEST_ASSERT(100 == test1.getAccuracy());
   TEST_ASSERT("physical" == test1.getCategory());
   TEST_ASSERT(test1.getChangeAccuracyTo().empty());
   TEST_ASSERT(test1.getChangeAccuracyWeather().empty());
   TEST_ASSERT(10 == test1.getCurrentPP());
   TEST_ASSERT("test ground type physical move that pokemon digs itself underground first before attacking" == test1.getDescription());
   TEST_ASSERT("test" == test1.getName());
   TEST_ASSERT(NULL == test1.getOtherEffect());
   TEST_ASSERT(80 == test1.getPower());
   TEST_ASSERT(0 == test1.getSelfDamage());
   TEST_ASSERT(10 == test1.getTotalPP());
   TEST_ASSERT(type_ground == test1.getType());
   TEST_ASSERT("dug itself underground" == test1.getWaitTurnDescription());
   TEST_ASSERT(!test1.isMovedLocked());
   delete co;
   TestFramework::EndTest();
}
void TestHiddenMove_UseMove() {
   TestFramework::BeginTest("Test HiddenMove: Hidden Move Gets");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   HiddenMove test1 = HiddenMove(co, "test", type_ground, "physical", 10, 80, 100,
      "test ground type physical move that pokemon digs itself underground first before attacking",
      "dug itself underground"
   );
   DamageMove test2 = DamageMove(co, "test", type_normal, "physical", 15, 50, 100,
      "test normal type physical, 50 power 100% accuracy move");
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // use hidden move
   test1.useHiddenMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_rock, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_steel, type_rock);
   TEST_ASSERT(9 == test1.getCurrentPP());
   TEST_ASSERT(78 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(test1.isMovedLocked());
   // defending pokemon attack now and misses attack because pokemon is hidden
   test2.useDamageMove(&clear_skies,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_steel, type_rock,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_rock, Type());
   TEST_ASSERT(79 == attackingPOKEMONSTADIUM_stats.getCurrentHeath());
   // use move again, damage apply
   test1.useHiddenMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_rock, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_steel, type_rock);
   TEST_ASSERT(9 == test1.getCurrentPP());
   TEST_ASSERT(0 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(!test1.isMovedLocked());
   // defending pokemon attacks, move does not miss because pokemon is no longer hidden
   test2.useDamageMove(&clear_skies,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_steel, type_rock,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_rock, Type());
   TEST_ASSERT(79 == attackingPOKEMONSTADIUM_stats.getCurrentHeath());
   delete co;
   TestFramework::EndTest();
}

void PokemonStadium::TestHiddenMove() {
   TestHiddenMove_HiddenMoveGets();
   TestHiddenMove_UseMove();
}


void TestRechargeMove_Move() {
   TestFramework::BeginTest("Test RechargeMove: Recharge Move");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   RechargeMove test1 = RechargeMove(co, "test", type_rock, "physical", 5, 150, 100,
      "test rock type physical, 150 power 100% that needs recharge after"
   );
   TEST_ASSERT(100 == test1.getAccuracy());
   TEST_ASSERT("physical" == test1.getCategory());
   TEST_ASSERT(test1.getChangeAccuracyTo().empty());
   TEST_ASSERT(test1.getChangeAccuracyWeather().empty());
   TEST_ASSERT(5 == test1.getCurrentPP());
   TEST_ASSERT("test rock type physical, 150 power 100% that needs recharge after" == test1.getDescription());
   TEST_ASSERT("test" == test1.getName());
   TEST_ASSERT(NULL == test1.getOtherEffect());
   TEST_ASSERT(150 == test1.getPower());
   TEST_ASSERT(0 == test1.getSelfDamage());
   TEST_ASSERT(5 == test1.getTotalPP());
   TEST_ASSERT(type_rock == test1.getType());
   TEST_ASSERT("needs to recharge." == test1.getWaitTurnDescription());
   TEST_ASSERT(!test1.isMovedLocked());
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // use move, damages are applied and move is locked
   test1.useRechargeMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_rock, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_steel, type_rock);
   TEST_ASSERT(4 == test1.getCurrentPP());
   TEST_ASSERT(29 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(test1.isMovedLocked());
   // use move, pokemon must recharge
   test1.useRechargeMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_ground, type_rock,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_rock, Type());
   TEST_ASSERT(4 == test1.getCurrentPP());
   TEST_ASSERT(29 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(!test1.isMovedLocked());
   delete co;
   TestFramework::EndTest();
}

void PokemonStadium::TestRechargeMove() {
   TestRechargeMove_Move();
}

void TestHealingMove_HealingMoveNoExtra() {
   TestFramework::BeginTest("Test HeadlingMove: Heal After Damage");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   HealingMove test1 = HealingMove(co, "test", type_normal, 15, 100, "heals the user 10%", .1);
   DamageMove attackMove = DamageMove(co, "test", type_psychic, "physical", 15, 50, 100, "test fire type physical, 50 power 100% accuracy move");
   TEST_ASSERT(100 == test1.getAccuracy());
   TEST_ASSERT("status" == test1.getCategory());
   TEST_ASSERT(15 == test1.getCurrentPP());
   TEST_ASSERT("heals the user 10%" == test1.getDescription());
   TEST_ASSERT("test" == test1.getName());
   TEST_ASSERT(0 == test1.getPower());
   TEST_ASSERT(15 == test1.getTotalPP());
   TEST_ASSERT(type_normal == test1.getType());
   TEST_ASSERT(!test1.isMovedLocked());
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // damage pokemon
   attackMove.useDamageMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_psychic, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_ghost, type_fairy);
   TEST_ASSERT(45 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(79 == attackingPOKEMONSTADIUM_stats.getCurrentHeath());
   // use move, damaged pokemon heals
   test1.useHealMove(&clear_skies,
      &defendingPOKEMONSTADIUM_stats,
      &attackingPOKEMONSTADIUM_stats
      );
   TEST_ASSERT(52 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(14 == test1.getCurrentPP());
   TEST_ASSERT(!test1.isMovedLocked());
   delete co;
   TestFramework::EndTest();
}

void TestHealingMove_HealingMoveWeatherChanges() {
   TestFramework::BeginTest("Test HeadlingMove: Heal After Damage With Weather Changes");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   HealingMove test1 = HealingMove(co, "test", type_normal, 15, 100, "heals the user 20%", 
      .2, {harsh_sun}, {hail, rain, sandstorm}, 2);
   DamageMove attackMove = DamageMove(co, "test", type_psychic, "physical", 15, 50, 100, "test fire type physical, 50 power 100% accuracy move");
   TEST_ASSERT(100 == test1.getAccuracy());
   TEST_ASSERT("status" == test1.getCategory());
   TEST_ASSERT(15 == test1.getCurrentPP());
   TEST_ASSERT("heals the user 20%" == test1.getDescription());
   TEST_ASSERT("test" == test1.getName());
   TEST_ASSERT(0 == test1.getPower());
   TEST_ASSERT(15 == test1.getTotalPP());
   TEST_ASSERT(type_normal == test1.getType());
   TEST_ASSERT(!test1.isMovedLocked());
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // damage pokemon
   attackMove.useDamageMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_psychic, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_ghost, type_fairy);
   TEST_ASSERT(45 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(79 == attackingPOKEMONSTADIUM_stats.getCurrentHeath());
   // heal damaged pokemon in rain, see that healing is lower
   test1.useHealMove(&rain,
      &defendingPOKEMONSTADIUM_stats,
      &attackingPOKEMONSTADIUM_stats
   );
   TEST_ASSERT(52 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(14 == test1.getCurrentPP());
   // heal damaged pokemon in rain, see that healing is normal
   test1.useHealMove(&clear_skies,
      &defendingPOKEMONSTADIUM_stats,
      &attackingPOKEMONSTADIUM_stats
   );
   TEST_ASSERT(67 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(13 == test1.getCurrentPP());
   // damage pokemon
   attackMove.useDamageMove(&clear_skies,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_psychic, Type(),
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_ghost, type_fairy);
   TEST_ASSERT(34 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   // heal damaged pokemon in rain, see that healing is more
   test1.useHealMove(&harsh_sun,
      &defendingPOKEMONSTADIUM_stats,
      &attackingPOKEMONSTADIUM_stats
   );
   TEST_ASSERT(65 == defendingPOKEMONSTADIUM_stats.getCurrentHeath());
   TEST_ASSERT(12 == test1.getCurrentPP());
   delete co;
   TestFramework::EndTest();
}

void PokemonStadium::TestHealingMove() {
   TestHealingMove_HealingMoveNoExtra();
   TestHealingMove_HealingMoveWeatherChanges();
}

void TestStatsChangingMove_Move() {
   TestFramework::BeginTest("Test StatsChangingMove: Test Move");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatsChangingMove test1 = StatsChangingMove(co, "test", type_dark, 15, 100, 
      "raise special attack", {"special attack"}, {"rose sharply"}, {true});
   TEST_ASSERT(100 == test1.getAccuracy());
   TEST_ASSERT("status" == test1.getCategory());
   TEST_ASSERT(15 == test1.getCurrentPP());
   TEST_ASSERT("raise special attack" == test1.getDescription());
   TEST_ASSERT("test" == test1.getName());
   TEST_ASSERT(0 == test1.getPower());
   TEST_ASSERT(15 == test1.getTotalPP());
   TEST_ASSERT(type_dark == test1.getType());
   TEST_ASSERT(!test1.isMovedLocked());
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // use move, cofirm change in stats
   test1.useStatsChangingMove(
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_dark, type_fairy
   );
   TEST_ASSERT(2 == attackingPOKEMONSTADIUM_stats.getModifierByName("special attack"));
   TEST_ASSERT(14 == test1.getCurrentPP());
   delete co;
   TestFramework::EndTest();
}

void TestStatsChangingMove_MissMove() {
   TestFramework::BeginTest("Test StatsChangingMove: Miss Move");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatsChangingMove test1 = StatsChangingMove(co, "test", type_dark, 15, 1,
      "raise attack and lower defense", {"attack", "defense"}, {"rose", "fell"}, {true,false});
   TEST_ASSERT(1 == test1.getAccuracy());
   TEST_ASSERT("status" == test1.getCategory());
   TEST_ASSERT(15 == test1.getCurrentPP());
   TEST_ASSERT("raise attack and lower defense" == test1.getDescription());
   TEST_ASSERT("test" == test1.getName());
   TEST_ASSERT(0 == test1.getPower());
   TEST_ASSERT(15 == test1.getTotalPP());
   TEST_ASSERT(type_dark == test1.getType());
   TEST_ASSERT(!test1.isMovedLocked());
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // use move, see that move misses
   test1.useStatsChangingMove(
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_dark, type_fairy
   );
   TEST_ASSERT(0 == attackingPOKEMONSTADIUM_stats.getModifierByName("attack"));
   TEST_ASSERT(0 == defendingPOKEMONSTADIUM_stats.getModifierByName("defense"));
   TEST_ASSERT(14 == test1.getCurrentPP());
   delete co;
   TestFramework::EndTest();
}

void TestStatsChangingMove_OverLoadModifier() {
   TestFramework::BeginTest("Test StatsChangingMove: Miss Move");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatsChangingMove test1 = StatsChangingMove(co, "test", type_dark, 15, 100,
      "raise attack sharply", {"attack"}, {"rose sharply"}, {true});
   TEST_ASSERT(100 == test1.getAccuracy());
   TEST_ASSERT("status" == test1.getCategory());
   TEST_ASSERT(15 == test1.getCurrentPP());
   TEST_ASSERT("raise attack sharply" == test1.getDescription());
   TEST_ASSERT("test" == test1.getName());
   TEST_ASSERT(0 == test1.getPower());
   TEST_ASSERT(15 == test1.getTotalPP());
   TEST_ASSERT(type_dark == test1.getType());
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // use move see stat changes applied
   test1.useStatsChangingMove(
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_dark, type_fairy
   );
   TEST_ASSERT(2 == attackingPOKEMONSTADIUM_stats.getModifierByName("attack"));
   TEST_ASSERT(14 == test1.getCurrentPP());
   // use move see stat changes applied
   test1.useStatsChangingMove(
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_dark, type_fairy
   );
   TEST_ASSERT(4 == attackingPOKEMONSTADIUM_stats.getModifierByName("attack"));
   TEST_ASSERT(13 == test1.getCurrentPP());
   // use move see stat changes applied
   test1.useStatsChangingMove(
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_dark, type_fairy
   );
   TEST_ASSERT(6 == attackingPOKEMONSTADIUM_stats.getModifierByName("attack"));
   TEST_ASSERT(12 == test1.getCurrentPP());
   // use move see stat chagnes do not apply
   test1.useStatsChangingMove(
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_dark, type_fairy
   );
   TEST_ASSERT(6 == attackingPOKEMONSTADIUM_stats.getModifierByName("attack"));
   TEST_ASSERT(11 == test1.getCurrentPP());
   delete co;
   TestFramework::EndTest();
}

void PokemonStadium::TestStatsChangingMove() {
   TestStatsChangingMove_Move();
   TestStatsChangingMove_MissMove();
   TestStatsChangingMove_OverLoadModifier();
}

void TestStatusConditionMove_MoveGets() {
   TestFramework::BeginTest("Test StatusConditionMove: Test Move Gets");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatusConditionMove test1 = StatusConditionMove(co, "test1", type_poison, 15, 100,
      "poisons target", "poison");
   // check move gets
   TEST_ASSERT(100 == test1.getAccuracy());
   TEST_ASSERT("status" == test1.getCategory());
   TEST_ASSERT(15 == test1.getCurrentPP());
   TEST_ASSERT("poisons target" == test1.getDescription());
   TEST_ASSERT("test1" == test1.getName());
   TEST_ASSERT(0 == test1.getPower());
   TEST_ASSERT(15 == test1.getTotalPP());
   TEST_ASSERT(type_poison == test1.getType());
   TEST_ASSERT(!test1.isMovedLocked());
   delete co;
   TestFramework::EndTest();
}

void TestStatusConditionMove_MoveWithMultConditions() {
   TestFramework::BeginTest("Test StatusConditionMove: Test Move With Multiple Conditions");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatusConditionMove test1 = StatusConditionMove(co, "test1", type_poison, 15, 100,
      "poisons target", "poison");
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // use move see status condition changed
   test1.useStatusConditionMove(
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_dark, type_fairy
   );
   TEST_ASSERT("poison" == defendingPokemonStatusCondition.getCondition());
   TEST_ASSERT(14 == test1.getCurrentPP());
   StatusConditionMove test2 = StatusConditionMove(co, "test2", type_psychic, 15, 100,
      "confuses target", "confused");
   // use move see target is now confused
   test2.useStatusConditionMove(
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_dark, type_fairy
   );
   TEST_ASSERT(defendingPokemonStatusCondition.isConfused());
   StatusConditionMove test3 = StatusConditionMove(co, "test3", type_electric, 15, 100,
      "paralyzes target", "paralyzed");
   // use move see target status condition doesn't change
   test3.useStatusConditionMove(
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_dark, type_fairy
   );
   TEST_ASSERT("poison" == defendingPokemonStatusCondition.getCondition());
   TEST_ASSERT(14 == test3.getCurrentPP());
   // cure confusion
   defendingPokemonStatusCondition.cureConfusion();
   StatusConditionMove test4 = StatusConditionMove(co, "test4", type_normal, 15, 100,
      "cures user");
   // used move on target with condition, see condition is cured
   test4.useStatusConditionMove(
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_poison, type_grass
   );
   TEST_ASSERT("" == defendingPokemonStatusCondition.getCondition());
   TEST_ASSERT(14 == test4.getCurrentPP());
   // use move nothing happens because user is already cured
   test4.useStatusConditionMove(
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_poison, type_grass
   );
   TEST_ASSERT("" == defendingPokemonStatusCondition.getCondition());
   TEST_ASSERT(13 == test4.getCurrentPP());
   // use move, doesn't work because type cannot be poison
   test1.useStatusConditionMove(
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition,
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition, type_poison, type_grass
   );
   TEST_ASSERT("" == attackingPokemonStatusCondition.getCondition());
   delete co;
   TestFramework::EndTest();
}

void TestStatusConditionMove_MissMove() {
   TestFramework::BeginTest("Test StatusConditionMove: Test Miss Move");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   StatusConditionMove test1 = StatusConditionMove(co, "test", type_fire, 15, 1,
      "burns target", "burned");
   TEST_ASSERT(1 == test1.getAccuracy());
   TEST_ASSERT("status" == test1.getCategory());
   TEST_ASSERT(15 == test1.getCurrentPP());
   TEST_ASSERT("burns target" == test1.getDescription());
   TEST_ASSERT("test" == test1.getName());
   TEST_ASSERT(0 == test1.getPower());
   TEST_ASSERT(15 == test1.getTotalPP());
   TEST_ASSERT(type_fire == test1.getType());
   TEST_ASSERT(!test1.isMovedLocked());
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   // use move, confirm move missed
   test1.useStatusConditionMove(
      &attackingPOKEMONSTADIUM_stats, &attackingPokemonStatusCondition,
      &defendingPOKEMONSTADIUM_stats, &defendingPokemonStatusCondition, type_dark, type_fairy
   );
   TEST_ASSERT("" == defendingPokemonStatusCondition.getCondition());
   TEST_ASSERT(14 == test1.getCurrentPP());
   delete co;
   TestFramework::EndTest();
}

void PokemonStadium::TestStatusConditionMove() {
   TestStatusConditionMove_MoveGets();
   TestStatusConditionMove_MoveWithMultConditions();
   TestStatusConditionMove_MissMove();
}

void TestWeatherChangingMove_MoveGets() {
   TestFramework::BeginTest("Test WeatherChangingMove: Test Move Gets");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   WeatherChangingMove test1 = WeatherChangingMove(co, "test1", type_rock, 15, "starts a sandstorm", &sandstorm);
   // test move gets
   TEST_ASSERT(1000 == test1.getAccuracy());
   TEST_ASSERT("status" == test1.getCategory());
   TEST_ASSERT(15 == test1.getCurrentPP());
   TEST_ASSERT("starts a sandstorm" == test1.getDescription());
   TEST_ASSERT("test1" == test1.getName());
   TEST_ASSERT(0 == test1.getPower());
   TEST_ASSERT(15 == test1.getTotalPP());
   TEST_ASSERT(type_rock == test1.getType());
   TEST_ASSERT("sandstorm" == test1.getWeatherToSet()->getName());
   TEST_ASSERT(!test1.isMovedLocked());
   delete co;
   TestFramework::EndTest();
}

void TestWeatherChangingMove_UsingWeatherChange() {
   TestFramework::BeginTest("Test WeatherChangingMove: Test Weather Change");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   WeatherChangingMove test1 = WeatherChangingMove(co, "test1", type_rock, 15, "starts a sandstorm", &sandstorm);
   Stats attackingPOKEMONSTADIUM_stats = Stats(79, 83, 85, 100, 105, 78);
   StatusCondition attackingPokemonStatusCondition = StatusCondition(co);
   Stats defendingPOKEMONSTADIUM_stats = Stats(78, 84, 109, 78, 85, 100);
   StatusCondition defendingPokemonStatusCondition = StatusCondition(co);
   Weather *battleWeather = new Weather();
   // use move, confirm weather changes
   test1.useWeatherChanginMove(&battleWeather);
   TEST_ASSERT("sandstorm" == battleWeather->getName());
   // loop throgh
   for (size_t turns = 0; turns < WEATHER_TIME_MAX; turns++) {
      TEST_ASSERT(turns == battleWeather->getTurnsSinceStarted());
      TEST_ASSERT(battleWeather->weatherStillActive());
   }
   if (!battleWeather->weatherStillActive()) {
      battleWeather->resetWeather();
      battleWeather = new Weather();
   }
   TEST_ASSERT("clear" == battleWeather->getName());
   delete battleWeather;
   delete co;
   TestFramework::EndTest();
}

void PokemonStadium::TestWeatherChangingMove() {
   TestWeatherChangingMove_MoveGets();
   TestWeatherChangingMove_UsingWeatherChange();
}

void TestPokemonCharacter_PreSetStatsConstructor() {
   TestFramework::BeginTest("Test PokemonCharacter: Test Pre Set Stats Constructor");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   DamageMove char1BattleMove1 = DamageMove(co, "test1", type_bug, "special", 15, 50, 100, "test1 move");
   ChargeMove char1BattleMove2 = ChargeMove(co, "test2", type_dark, "physical", 10, 120, 100, "test2 move", "charge");
   StatsChangingMove char1BattleMove3 = StatsChangingMove(co, "test3", type_dark, 15, 100, "test3 move", {"special attack"}, {"rose sharply"}, {true});
   StatusConditionMove char1BattleMove4 = StatusConditionMove(co, "test4", type_poison, 15, 100, "test4 move", "poison");
   PokemonCharacter character1 = PokemonCharacter(co, "character", type_fairy,
      Stats(79, 83, 85, 100, 105, 78),
      &char1BattleMove1,
      &char1BattleMove2,
      &char1BattleMove3,
      &char1BattleMove4,
      "");
   TEST_ASSERT("character" == character1.getName());
   TEST_ASSERT(type_fairy == character1.getPrimaryType());
   TEST_ASSERT(79 == character1.getStats()->getTotalHeath());
   TEST_ASSERT(79 == character1.getStats()->getCurrentHeath());
   TEST_ASSERT(83 == character1.getStats()->getAttack());
   TEST_ASSERT(85 == character1.getStats()->getSpecialAttack());
   TEST_ASSERT(100 == character1.getStats()->getDefense());
   TEST_ASSERT(105 == character1.getStats()->getSpecialDefense());
   TEST_ASSERT(78 == character1.getStats()->getSpeed());
   TEST_ASSERT(Type() == character1.getSecondaryType());
   TEST_ASSERT("" == character1.getStatusCondition()->getCondition());
   TEST_ASSERT(character1.isBattleMoveUseable("test1"));
   TEST_ASSERT(character1.isBattleMoveUseable("test2"));
   TEST_ASSERT(character1.isBattleMoveUseable("test3"));
   TEST_ASSERT(character1.isBattleMoveUseable("test4"));
   TEST_ASSERT(!character1.isBattleMoveUseable("test5"));
   TEST_ASSERT(character1.isBattleMoveUseable(0));
   TEST_ASSERT(character1.isBattleMoveUseable(1));
   TEST_ASSERT(character1.isBattleMoveUseable(2));
   TEST_ASSERT(character1.isBattleMoveUseable(3));
   TEST_ASSERT(!character1.isBattleMoveUseable(4));
   TEST_ASSERT(0 == character1.getBattleMoveSlot("test1"));
   delete co;
   TestFramework::EndTest();
}

void TestPokemonCharacter_ManualSetStatsConstructor() {
   TestFramework::BeginTest("Test PokemonCharacter: Test Manual Set Stats Constructor");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   DamageMove char1BattleMove1 = DamageMove(co, "test1", type_bug, "special", 15, 50, 100, "test1 move");
   ChargeMove char1BattleMove2 = ChargeMove(co, "test2", type_dark, "physical", 10, 120, 100, "test2 move", "charge");
   StatsChangingMove char1BattleMove3 = StatsChangingMove(co, "test3", type_dark, 15, 100, "test3 move", {"special attack"}, {"rose sharply"}, {true});
   StatusConditionMove char1BattleMove4 = StatusConditionMove(co, "test4", type_poison, 15, 100, "test4 move", "poison");
   PokemonCharacter *character1 = new PokemonCharacter(co, "character", type_fairy,
      79, 83, 85, 100, 105, 78,
      &char1BattleMove1,
      &char1BattleMove2,
      &char1BattleMove3,
      &char1BattleMove4,
      "");
   TEST_ASSERT("character" == character1->getName());
   TEST_ASSERT(type_fairy == character1->getPrimaryType());
   TEST_ASSERT(79 == character1->getStats()->getTotalHeath());
   TEST_ASSERT(79 == character1->getStats()->getCurrentHeath());
   TEST_ASSERT(83 == character1->getStats()->getAttack());
   TEST_ASSERT(85 == character1->getStats()->getSpecialAttack());
   TEST_ASSERT(100 == character1->getStats()->getDefense());
   TEST_ASSERT(105 == character1->getStats()->getSpecialDefense());
   TEST_ASSERT(78 == character1->getStats()->getSpeed());
   TEST_ASSERT(Type() == character1->getSecondaryType());
   TEST_ASSERT("" == character1->getStatusCondition()->getCondition());
   TEST_ASSERT(character1->isBattleMoveUseable("test1"));
   TEST_ASSERT(character1->isBattleMoveUseable("test2"));
   TEST_ASSERT(character1->isBattleMoveUseable("test3"));
   TEST_ASSERT(character1->isBattleMoveUseable("test4"));
   TEST_ASSERT(!character1->isBattleMoveUseable("test5"));
   TEST_ASSERT(character1->isBattleMoveUseable(0));
   TEST_ASSERT(character1->isBattleMoveUseable(1));
   TEST_ASSERT(character1->isBattleMoveUseable(2));
   TEST_ASSERT(character1->isBattleMoveUseable(3));
   TEST_ASSERT(!character1->isBattleMoveUseable(4));
   TEST_ASSERT(0 == character1->getBattleMoveSlot("test1"));
   delete character1;
   delete co;
   TestFramework::EndTest();
}

void TestPokemonCharacter_TwoPokemonCharacters() {
   TestFramework::BeginTest("Test PokemonCharacter: Two Pokemon Characters");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   // create 4 battle moves for the Pokemon character 1
   DamageMove char1BattleMove1 = DamageMove(co, "test1", type_bug, "special", 15, 50, 100, "test1 move");
   ChargeMove char1BattleMove2 = ChargeMove(co, "test2", type_dark, "physical", 10, 120, 100, "test2 move", "charge");
   StatsChangingMove char1BattleMove3 = StatsChangingMove(co, "test3", type_dark, 15, 100, "test3 move", {"special attack"}, {"rose sharply"}, {true});
   StatusConditionMove char1BattleMove4 = StatusConditionMove(co, "test4", type_poison, 15, 100, "test4 move", "poison");
   // Character 1, type Fairy
   // set the Pokemon character with the above battle moves
   PokemonCharacter *character1 = new PokemonCharacter(co, "character 1", type_fairy,
      79, 83, 85, 100, 105, 78,
      &char1BattleMove1, &char1BattleMove2, &char1BattleMove3, &char1BattleMove4,
      "");
   // create 4 battle moves for the Pokemon character 2
   WeatherChangingMove char2BattleMove1 = WeatherChangingMove(co, "test1", type_ice, 15, "test1 move", &hail);
   HealingMove char2BattleMove2 = HealingMove(co, "test", type_normal, 15, 100, "test2 move", .1);
   RechargeMove char2BattleMove3 = RechargeMove(co, "test", type_rock, "special", 5, 150, 100, "test3 move");
   HiddenMove char2BattleMove4 = HiddenMove(co, "test", type_water, "physical", 10, 80, 100, "test4 move", "dove underwater");
   // Character 2, type Ice Flying
   // set the Pokemon character with the above battle moves
   PokemonCharacter *character2 = new PokemonCharacter(co, "character", type_ice,
      78, 84, 109, 78, 85, 100,
      &char2BattleMove1, &char2BattleMove2, &char2BattleMove3, &char2BattleMove4,
      "",
      type_flying);
   Weather *battleWeather = new Weather();
   // Use Character one damage move on Character 2
   character1->useSelectedBattleMove(0, &battleWeather,
      character2->getStats(), character2->getStatusCondition(),
      character2->getPrimaryType(), character2->getSecondaryType());
   TEST_ASSERT(14 == character1->getBattleMoveByName("test1")->getCurrentPP());
   TEST_ASSERT(67 == character2->getStats()->getCurrentHeath());
   // check created move doesn't lose PP
   TEST_ASSERT(15 == char1BattleMove1.getCurrentPP());
   // Use Character 2 weather changing move
   character2->useSelectedBattleMove(0, &battleWeather,
      character1->getStats(), character1->getStatusCondition(),
      character1->getPrimaryType(), character1->getSecondaryType());
   TEST_ASSERT(*battleWeather == hail);
   TEST_ASSERT(14 == character1->getBattleMoveByName("test1")->getCurrentPP());
   TEST_ASSERT(15 == char2BattleMove1.getCurrentPP());
   TEST_ASSERT(79 == character1->getStats()->getCurrentHeath());
   // Check Weather is still active and apply effect
   TEST_ASSERT(battleWeather->weatherStillActive());
   battleWeather->applyWeatherDamages(character1->getStats(),
      character1->getPrimaryType(), character1->getSecondaryType());
   battleWeather->applyWeatherDamages(character2->getStats(),
      character2->getPrimaryType(), character2->getSecondaryType());
   TEST_ASSERT(75 == character1->getStats()->getCurrentHeath());
   TEST_ASSERT(67 == character2->getStats()->getCurrentHeath());
   TEST_ASSERT(!character1->pokemonFainted());
   TEST_ASSERT(!character2->pokemonFainted());
   // Use Character 1 charge move on Character 2
   character1->useSelectedBattleMove(1, &battleWeather,
      character2->getStats(), character2->getStatusCondition(),
      character2->getPrimaryType(), character2->getSecondaryType());
   TEST_ASSERT(9 == character1->getBattleMoveBySlot(1)->getCurrentPP());
   TEST_ASSERT(67 == character2->getStats()->getCurrentHeath());
   TEST_ASSERT(character1->getBattleMoveBySlot(1)->isMovedLocked());
   // Use Character 2 heal move
   character2->useSelectedBattleMove(1, &battleWeather,
      character1->getStats(), character1->getStatusCondition(),
      character1->getPrimaryType(), character1->getSecondaryType());
   TEST_ASSERT(14 == character2->getBattleMoveBySlot(1)->getCurrentPP());
   TEST_ASSERT(74 == character2->getStats()->getCurrentHeath());
   TEST_ASSERT(character1->getBattleMoveBySlot(1)->isMovedLocked());
   delete battleWeather;
   delete character1;
   delete character2;
   delete co;
   TestFramework::EndTest();
}
void
TestPokemonCharacter_TwoPokemonCharactersWithSameBattleMoves() {
   TestFramework::BeginTest("Test PokemonCharacter: Two PokemonCharacter With Same BattleMoves");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   // create 4 battle moves 
   DamageMove battleMove1 = DamageMove(co, "test1", type_bug, "special", 15, 50, 100, "test1 move");
   ChargeMove battleMove2 = ChargeMove(co, "test2", type_dark, "physical", 10, 120, 100, "test2 move", "charge");
   StatsChangingMove battleMove3 = StatsChangingMove(co, "test3", type_dark, 15, 100, "test3 move", {"special attack"}, {"rose sharply"}, {true});
   StatusConditionMove battleMove4 = StatusConditionMove(co, "test4", type_poison, 15, 100, "test4 move", "poison");
   // Character 1, type Fairy
   // set the Pokemon character with the above battle moves
   PokemonCharacter *character1 = new PokemonCharacter(co, "character 1", type_fairy,
      79, 83, 85, 100, 105, 78,
      &battleMove1, &battleMove2, &battleMove3, &battleMove4,
      "");
   PokemonCharacter *character2 = new PokemonCharacter(co, "character 2", type_fire,
      78, 84, 109, 78, 85, 100,
      &battleMove4, &battleMove3, &battleMove2, &battleMove1,
      "");
   Weather *battleWeather = new Weather();
   character1->useSelectedBattleMove(0, &battleWeather,
      character2->getStats(), character2->getStatusCondition(),
      character2->getPrimaryType(), character2->getSecondaryType());
   character2->useSelectedBattleMove(3, &battleWeather,
      character1->getStats(), character1->getStatusCondition(),
      character1->getPrimaryType(), character1->getSecondaryType());
   TEST_ASSERT(14 == character1->getBattleMoveBySlot(0)->getCurrentPP());
   TEST_ASSERT(14 == character2->getBattleMoveBySlot(3)->getCurrentPP());
   delete character1;
   TEST_ASSERT(14 == character2->getBattleMoveBySlot(3)->getCurrentPP());
   delete character2;
   delete battleWeather;
   delete co;
   TestFramework::EndTest();
}

void PokemonStadium::TestPokemonCharacter() {
   TestPokemonCharacter_PreSetStatsConstructor();
   TestPokemonCharacter_ManualSetStatsConstructor();
   TestPokemonCharacter_TwoPokemonCharacters();
   TestPokemonCharacter_TwoPokemonCharactersWithSameBattleMoves();
}

void TestTrainer_Settings() {
   TestFramework::BeginTest("Test Trainer: Test Settings");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   Trainer *trainer1 = new Trainer(co, "test1", ("Trainer 1 "));
   TEST_ASSERT("test1" == trainer1->getId());
   TEST_ASSERT("Trainer 1 " == trainer1->getName());
   // create 4 battle moves for the Pokemon character 1
   DamageMove char1BattleMove1 = DamageMove(co, "move1", type_bug, "special", 15, 50, 100, "test1 move");
   ChargeMove char1BattleMove2 = ChargeMove(co, "move2", type_dark, "physical", 10, 120, 100, "test2 move", "charge");
   StatsChangingMove char1BattleMove3 = StatsChangingMove(co, "move3", type_dark, 15, 100, "test3 move", {"special attack"}, {"rose sharply"}, {true});
   StatusConditionMove char1BattleMove4 = StatusConditionMove(co, "move4", type_poison, 15, 100, "test4 move", "poison");
   // Character 1, type Fairy
   // set the Pokemon character with the above battle moves
   PokemonCharacter *character1 = new PokemonCharacter(co, "character 1", type_fairy,
      79, 83, 85, 100, 105, 78,
      &char1BattleMove1, &char1BattleMove2, &char1BattleMove3, &char1BattleMove4,
      "");
   trainer1->addPokemonToParty(character1);
   // verify pokemon in PokemonParty is the same as character1
   vector<PokemonCharacter *> trainerPokemonParty = trainer1->getPokemonParty();
   for (auto & pokemon : trainerPokemonParty) {
      TEST_ASSERT(pokemon->getName() == character1->getName());
   }
   // verify pokemon in PokemonParty is still the same as character1
   trainerPokemonParty = trainer1->getPokemonParty();
   TEST_ASSERT(trainerPokemonParty.size() == 1);
   for (auto & pokemon : trainerPokemonParty) {
      TEST_ASSERT(pokemon->getName() == character1->getName());
   }
   delete trainer1;
   delete co;
   TestFramework::EndTest();
}


void TestTrainer_UsingPokemonOutBattleMoves() {
   TestFramework::BeginTest("Test PokemonCharacter: Using Pokemon Out's Battle Moves");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   Trainer *trainer1 = new Trainer(co, "test1", ("Trainer 1"));
   TEST_ASSERT("test1" == trainer1->getId());
   TEST_ASSERT("Trainer 1" == trainer1->getName());
   Trainer *trainer2 = new Trainer(co, "test2", ("Trainer 2"));
   TEST_ASSERT("test2" == trainer2->getId());
   TEST_ASSERT("Trainer 2" == trainer2->getName());
   // create 4 battle moves for the Pokemon character 1
   DamageMove char1BattleMove1 = DamageMove(co, "special bug", type_bug, "special", 15, 50, 100, "test1 move");
   ChargeMove char1BattleMove2 = ChargeMove(co, "dark charge", type_dark, "physical", 10, 120, 100, "test2 move", "charge");
   StatsChangingMove char1BattleMove3 = StatsChangingMove(co, "nasty plot", type_dark, 15, 100, "test3 move", {"special attack"}, {"rose sharply"}, {true});
   StatusConditionMove char1BattleMove4 = StatusConditionMove(co, "poison", type_poison, 15, 100, "test4 move", "poison");
   // Character 1, type Fairy
   // set the Pokemon character with the above battle moves
   PokemonCharacter *character1 = new PokemonCharacter(co, "character 1", type_fairy,
      95, 65, 110, 130, 130, 60,
      &char1BattleMove1, &char1BattleMove2, &char1BattleMove3, &char1BattleMove4,
      "");
   // create 4 battle moves for the Pokemon character 2
   WeatherChangingMove char2BattleMove1 = WeatherChangingMove(co, "hail", type_ice, 15, "test1 move", &hail);
   HealingMove char2BattleMove2 = HealingMove(co, "recover", type_normal, 15, 100, "test2 move", .1);
   RechargeMove char2BattleMove3 = RechargeMove(co, "rock hyperbeam", type_rock, "special", 5, 150, 100, "test3 move");
   HiddenMove char2BattleMove4 = HiddenMove(co, "dive", type_water, "physical", 10, 80, 100, "test4 move", "dove underwater");
   // Character 2, type Ice Flying
   // set the Pokemon character with the above battle moves
   PokemonCharacter *character2 = new PokemonCharacter(co, "character 2", type_ice,
      90, 85, 95, 100, 125, 85,
      &char2BattleMove1, &char2BattleMove2, &char2BattleMove3, &char2BattleMove4,
      "",
      type_flying);
   // create 4 battle moves for the Pokemon character 2
   StatChangingEffect *lower_defense_80 = new StatChangingEffect(co, 80, {"defense"}, {"fell"}, {false});
   StatsChangingMove char3BattleMove1 = StatsChangingMove(co, "special growl", type_electric, 15, 100,
      "lowers targets special defense",
      {"special defense"}, {"fell"}, {false});
   DamageMove char3BattleMove2 = DamageMove(co, "iron tail", type_steel, "physical", 15, 100, 100,
      "test2 move",
      lower_defense_80);
   StatusConditionEffect *paralyzed_30 = new StatusConditionEffect(co, 30, "paralyzed");
   DamageMove char3BattleMove3 = DamageMove(co, "thunder", type_electric, "special", 10, 110, 70,
      "test3 move",
      paralyzed_30,
      {rain}, {1000});
   DamageMove char3BattleMove4 = DamageMove(co, "quick attack", type_normal, "physical", 10, 40, 100, "test4 move", 1);
   // Character 3, type Electric
   // set the Pokemon character with the above battle moves
   PokemonCharacter *character3 = new PokemonCharacter(co, "character 3", type_electric,
      90, 85, 95, 100, 125, 85,
      &char3BattleMove1, &char3BattleMove2, &char3BattleMove3, &char3BattleMove4,
      "");
   // add pokemon to trainers
   trainer1->addPokemonToParty(character1);
   trainer1->addPokemonToParty(character2);
   trainer1->addPokemonToParty(character3);
   trainer2->addPokemonToParty(character1);
   trainer2->addPokemonToParty(character2);
   trainer2->addPokemonToParty(character3);
   // set trainers battle parties
   trainer1->setBattleParty({0, 1, 2});
   trainer2->setBattleParty({2, 1, 0});
   Weather *battleWeather = new Weather();
   PokemonCharacter *trainer1PokemonCharacter = trainer1->getPokemonInBattle();
   PokemonCharacter *trainer2PokemonCharacter = trainer2->getPokemonInBattle();
   size_t battleMoveSlot = 2;
   // start battle char1BattleMove3
   trainer1->usePokemonInBattleBattleMove(battleMoveSlot, &battleWeather, trainer1->getName(),
      trainer2PokemonCharacter->getName(), trainer2PokemonCharacter->getStats(),
      trainer2PokemonCharacter->getStatusCondition(), trainer2PokemonCharacter->getPrimaryType(),
      trainer2PokemonCharacter->getSecondaryType());
   TEST_ASSERT(trainer1->getPokemonInBattle()->getBattleMoveBySlot(battleMoveSlot)->getCurrentPP() == 14);
   TEST_ASSERT(trainer1->getPokemonInBattle()->getStats()->getModifierByName("special attack") == 2);
   battleMoveSlot = 1;
   trainer2->usePokemonInBattleBattleMove(battleMoveSlot, &battleWeather, trainer1->getName(),
      trainer1PokemonCharacter->getName(), trainer1PokemonCharacter->getStats(),
      trainer1PokemonCharacter->getStatusCondition(), trainer1PokemonCharacter->getPrimaryType(),
      trainer1PokemonCharacter->getSecondaryType());
   TEST_ASSERT(trainer2->getPokemonInBattle()->getBattleMoveBySlot(battleMoveSlot)->getCurrentPP() == 14);
   TEST_ASSERT(trainer1PokemonCharacter->getStats()->getCurrentHeath() == 93);
   TEST_ASSERT(trainer1->getPokemonInBattle()->getStats()->getCurrentHeath() == 93);
   delete lower_defense_80;
   delete paralyzed_30;
   delete trainer1;
   delete trainer2;
   delete character1;
   delete character2;
   delete character3;
   delete battleWeather;
   TestFramework::EndTest();
}

void TestTrainer_UserActionSwitchOut() {
   TestFramework::BeginTest("Test PokemonCharacter: Using Pokemon Out's Battle Moves");
   stringstream ss;
   ConsoleOutput *co = new ConsoleOutput(ss, "User", "Opp");
   Trainer *trainer1 = new Trainer(co, "test1", ("Trainer 1"));
   TEST_ASSERT("test1" == trainer1->getId());
   TEST_ASSERT("Trainer 1" == trainer1->getName());
   Trainer *trainer2 = new Trainer(co, "test2", ("Trainer 2"));
   TEST_ASSERT("test2" == trainer2->getId());
   TEST_ASSERT("Trainer 2" == trainer2->getName());
   // create 4 battle moves for the Pokemon character 1
   DamageMove char1BattleMove1 = DamageMove(co, "special bug", type_bug, "special", 15, 50, 100, "test1 move");
   ChargeMove char1BattleMove2 = ChargeMove(co, "dark charge", type_dark, "physical", 10, 120, 100, "test2 move", "charge");
   StatsChangingMove char1BattleMove3 = StatsChangingMove(co, "nasty plot", type_dark, 15, 100, "test3 move", {"special attack"}, {"rose sharply"}, {true});
   StatusConditionMove char1BattleMove4 = StatusConditionMove(co, "poison", type_poison, 15, 100, "test4 move", "poison");
   // Character 1, type Fairy
   // set the Pokemon character with the above battle moves
   PokemonCharacter *character1 = new PokemonCharacter(co, "character 1", type_fairy,
      95, 65, 110, 130, 130, 60,
      &char1BattleMove1, &char1BattleMove2, &char1BattleMove3, &char1BattleMove4,
      "");
   // create 4 battle moves for the Pokemon character 2
   WeatherChangingMove char2BattleMove1 = WeatherChangingMove(co, "hail", type_ice, 15, "test1 move", &hail);
   HealingMove char2BattleMove2 = HealingMove(co, "recover", type_normal, 15, 100, "test2 move", .1);
   RechargeMove char2BattleMove3 = RechargeMove(co, "rock hyperbeam", type_rock, "special", 5, 150, 100, "test3 move");
   HiddenMove char2BattleMove4 = HiddenMove(co, "dive", type_water, "physical", 10, 80, 100, "test4 move", "dove underwater");
   // Character 2, type Ice Flying
   // set the Pokemon character with the above battle moves
   PokemonCharacter *character2 = new PokemonCharacter(co, "character 2", type_ice,
      90, 85, 95, 100, 125, 85,
      &char2BattleMove1, &char2BattleMove2, &char2BattleMove3, &char2BattleMove4,
      "",
      type_flying);
   // create 4 battle moves for the Pokemon character 2
   StatChangingEffect *lower_defense_80 = new StatChangingEffect(co, 80, {"defense"}, {"fell"}, {false});
   StatsChangingMove char3BattleMove1 = StatsChangingMove(co, "special growl", type_electric, 15, 100,
      "lowers targets special defense",
      {"special defense"}, {"fell"}, {false});
   DamageMove char3BattleMove2 = DamageMove(co, "iron tail", type_steel, "physical", 15, 100, 100,
      "test2 move",
      lower_defense_80);
   StatusConditionEffect *paralyzed_30 = new StatusConditionEffect(co, 30, "paralyzed");
   DamageMove char3BattleMove3 = DamageMove(co, "thunder", type_electric, "special", 10, 110, 70,
      "test3 move",
      paralyzed_30,
      {rain}, {1000});
   DamageMove char3BattleMove4 = DamageMove(co, "quick attack", type_normal, "physical", 10, 40, 100, "test4 move", 1);
   // Character 3, type Electric
   // set the Pokemon character with the above battle moves
   PokemonCharacter *character3 = new PokemonCharacter(co, "character 3", type_electric,
      90, 85, 95, 100, 125, 85,
      &char3BattleMove1, &char3BattleMove2, &char3BattleMove3, &char3BattleMove4,
      "");
   // add pokemon to trainers
   trainer1->addPokemonToParty(character1);
   trainer1->addPokemonToParty(character2);
   trainer1->addPokemonToParty(character3);
   trainer2->addPokemonToParty(character1);
   trainer2->addPokemonToParty(character2);
   trainer2->addPokemonToParty(character3);
   // set trainers battle parties
   trainer1->setBattleParty({0, 1, 2});
   trainer2->setBattleParty({2, 1, 0});
   Weather *battleWeather = new Weather();
   // check if pokemon in slot 1 can be sent out
   if (trainer1->pickPokemonToSwitch(1)) {
      trainer1->switchPokemon(1);
      TEST_ASSERT(trainer1->getPokemonInBattle()->getName() == character2->getName());
   }
   else {
      // pokemon should of been able to switch out
      TEST_ASSERT(false);
   }
   delete lower_defense_80;
   delete paralyzed_30;
   delete trainer1;
   delete trainer2;
   delete character1;
   delete character2;
   delete character3;
   TestFramework::EndTest();
}

void TestTrainer_PokemonOutFainted() {

}

void PokemonStadium::TestTrainer() {
   TestTrainer_Settings();
   TestTrainer_UsingPokemonOutBattleMoves();
   TestTrainer_UserActionSwitchOut();
}
