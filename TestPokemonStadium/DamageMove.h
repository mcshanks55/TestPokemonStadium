/*
* Pokemon Project
*
* DamageMove.h
* A battle move that damages the opponent
*
*/
#ifndef POKEMONSTADIUM_DAMAGEMOVE_H
#define POKEMONSTADIUM_DAMAGEMOVE_H

#include "BattleMove.h"
#include "StatChangingEffect.h"
using PokemonStadium::StatChangingEffect;
#include "StatusConditionEffect.h"
using PokemonStadium::StatusConditionEffect;

#define TYPE_INC_DAMAGE 1.5

namespace PokemonStadium
{

   class DamageMove : public BattleMove {
   public:
   // Constructor
   // empty constructor
   DamageMove();

   // no extra effect; Only one that can change priorty
   DamageMove(ConsoleOutput *out,
      string name, Type type, string category, int pp, int power, int accuracy, string description,
      int priorty = NO_PRIORTY);

   // Self Damage move decides if self damage should be taken by userDamage or base on health
   DamageMove(ConsoleOutput *out,
      string name, Type type, string category, int pp, int power, int accuracy, string description,
      bool selfDamageBaseOnDamage, double selfDamagePercent);

   // extra battle move effect
   DamageMove(ConsoleOutput *out,
      string name, Type type, string category, int pp, int power, int accuracy, string description,
      BattleMoveEffects *otherEffect);

   // Weather accuracy increase
   DamageMove(ConsoleOutput *out,
      string name, Type type, string category, int pp, int power, int accuracy, string description,
      vector<Weather> changeAccuracyWeathers, vector<double> changeAccuracyToValues);

   // extra battle move effect, Weather accuracy increase
   DamageMove(ConsoleOutput *out,
      string name, Type type, string category, int pp, int power, int accuracy, string description,
      BattleMoveEffects *otherEffect,
      vector<Weather> changeAccuracyWeathers, vector<double> changeAccuracyToValues);

   // constructor that takes in a pointer to a damage move
   DamageMove(DamageMove *dMove);

   // destructor
   ~DamageMove();

   // memeber functions
   double getSelfDamage() const;
   BattleMoveEffects* getOtherEffect() const;
   vector<Weather> getChangeAccuracyWeather() const;
   vector<double> getChangeAccuracyTo() const;
   bool attack(Weather *battleWeather,
      Stats *userPokemonStats, StatusCondition *userStatusCondition, Type userPrimaryType, Type userSecondaryType,
      Stats *oppPokemonStats, StatusCondition *oppStatusCondition, Type oppPrimaryType, Type oppSecondaryType);
   void useDamageMove(Weather *battleWeather,
      Stats *userPokemonStats, StatusCondition *userStatusCondition, Type userPrimaryType, Type userSecondaryType,
      Stats *oppPokemonStats, StatusCondition *oppStatusCondition, Type oppPrimaryType, Type oppSecondaryType);
   virtual void display() const;

   protected:
      bool attemptAttack(Weather battleWeather, Stats *userPokemonStats, Stats *oppPokemonStats);
      int calculateDamages(Weather *battleWeather, Stats *userPokemonStats, Stats *oppPokemonStats,
         double battleMoveEffectiveNess, double typeMultipler);
      int totalDamageCalculations(int pureDamage,
         double battleMoveEffecitveNess, double weatherPowerMultipler, double typeMultiplier) const;
      

   private:
      bool selfDamageBaseOnDamage;
      double selfDamage;
      BattleMoveEffects *otherEffect;
      vector<Weather> changeAccuracyWeather;
      vector<double> changeAccuracyToValues;
      void setOtherEffect(BattleMoveEffects *otherEffect);
   };
}
#endif
