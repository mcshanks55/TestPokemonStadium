/*
* Pokemon
*
* StatusCondition.h
* The status condition of the Pokemon during battle
* All of the Status Condition: Normal, Burn, Paralyzed, Frozen, Asleep

*/
#ifndef POKEMONSTADIUM_STATUSCONDITION_H
#define POKEMONSTADIUM_STATUSCONDITION_H

#include <string>
using std::string;
#include <iostream>
using std::cerr;
#include "ConsoleOutput.h"
#include<time.h>
#include "Stats.h"
using PokemonStadium::Stats;
#include "Type.h"
using PokemonStadium::Type;

namespace PokemonStadium
{
   // random seed for how long sleep will last
   static const int SLEEP_TURNS = 4; // plus 1 gets added to sleep turn
   // percentage pokemon will dethaw
   static const int DETHAW_CHANCE = 20;
   // the type that is immune to being frozen
   static const string IMMUNE_TO_FREEZING = "Ice";
   // modifier for reduce attack stat
   static const double BURN_ATTACK_REDUCTION = .5;
   // percentage burn damage does to user
   static const double BURN_DAMAGE = 0.0625;
   // the type that is immune to being burned
   static const string IMMUNE_TO_BURN = "Fire";
   // modifier for reduce speed stat
   static const double PARALYZE_SPEED_REDUCTION = .5;
   // percentage that paralyzed pokemon cannot attack
   static const int PARALYZE_CANT_MOVE = 25;
   // the type that is immune to being paralyze
   static const string IMMUNE_TO_PARALYZE = "Electric";
   // percentage poison damage does to the user
   static const double POISON_DAMAGE = 0.125;
   static const double BADLY_POISON_DAMAGE_INC = 0.0625;
   // the type that is immune to being poison
   static const string IMMUNE_TO_POISON_1 = "Poison";
   static const string IMMUNE_TO_POISON_2 = "Steel";

   // random seed for how long confusion will last
   static const int CONFUSION_TURNS = 4;
   static const int CONFUSION_CHANCE = 50;
   static const int CONFUSION_POWER = 40;

   // Status Conditions
   static const vector<string> allConditions = {"asleep", "burned", "confused", "frozen", "paralyzed", "poison", "badly poison"};

   class StatusCondition {
      
   public:
      // Constructor
      StatusCondition();
      StatusCondition(ConsoleOutput *out, string condition = "");
      // memeber funcitons
      string getCondition() const;
      void setCondition(string condition, Stats *pokemonStats);
      int getSleepTurns();
      bool isConfused() const;
      void setConfusion();
      bool applyPreAffects(Stats *pokemonStats);
      void applyPostAffect(Stats *pokemonStats);
      void cured(Stats *pokemonsStats);
      void cureConfusion();
      bool statusConditionCanBeChanged(string conditionToCause,
         Type primary_type, Type secondary_type = Type());


   protected:
      bool asleep();
      bool confused(Stats *pokemonStats);
      void burned(Stats *pokemonStats);
      bool frozen();
      bool paralyzed();
      void poison(Stats *pokemonStats);

   private:
      ConsoleOutput *out;
      string condition;
      int sleepTurns;
      bool badlyPoison;
      int incPoisonDamage;
      bool confusion;
      int confusionTurns;
   };
}
#endif