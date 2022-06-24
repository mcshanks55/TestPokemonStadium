/*
* Pokemon
*
* Stats.h
* The stats of a Pokemon.
* Each Pokemon have indiviuals stats:
*    Health, Attack, Special Attack, Defense, Special Defense, Speed
* All Pokemon also have a accuracy and evasion stat that is only used during
* a battle and start off at 100%.
* Current health can be decrease by damage and increase healing during battle
* All other stats are only changed by changing modifiers during battle
*
*/

#ifndef POKEMONSTADIUM_STATS_H
#define POKEMONSTADIUM_STATS_H

#include "Global.h"
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iostream>

using std::cerr;
#define ACCURACY_DENOMINATOR 3
#define STAT_DENOMINATOR 2

namespace PokemonStadium
{

   class Stats {
   public:
      // Constructor
      Stats();
      Stats(int health, int attack, int special_attack,
         int defense, int special_defense, int speed);
      Stats(Stats *other);

      // memeber functions
      int getTotalHeath() const;
      int getAttack() const;
      int getSpecialAttack() const;
      int getDefense() const;
      int getSpecialDefense() const;
      int getSpeed() const;
      int getCurrentHeath() const;
      void damageToHealth(int damage);
      void damagePercentToHealth(double damagePer);
      void healHealth(int heahealingPower);
      void healPercentageHealth(double healingPower);
      int getStatValueByName(string statName) const;
      int getModifierByName(string statName) const;
      double getModifiedStatValue(string stat);
      // changes stat modifiers to change the stat
      bool canModifierBeChanged(string stat, int changingPower);
      // changes stat modifiers to change the stat
      void changeModifier(string stat, int changingPower);
      void addStatusConditionModifier(string stat, double reduceValue);
      void resetModifiers();
      void clearStatusConditionModifier();
      void cannotMiss();

   private:
      int current_health;
      int total_health;
      int attack;
      int special_attack;
      int defense;
      int special_defense;
      int speed;
      int m_attack;
      int m_special_attack;
      int m_defense;
      int m_special_defense;
      int m_speed;
      int m_accuracy;
      int m_evasion;
      string statusConditionReduceStat;
      double statusConditionReduceValue;
   };
}
#endif