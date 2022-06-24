/*
* Pokemon Project
* 
* PokemonCharacter.h
* A class of each Pokemon character's info
*
*/
#ifndef POKEMONSTADIUM_POKEMONCHARACTER_H
#define POKEMONSTADIUM_POKEMONCHARACTER_H

// include all battle moves
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

namespace PokemonStadium
{

   class PokemonCharacter {

   public:
      static const int NUM_BATTLE_MOVES = 4;
      // Stats already set Constructor
      PokemonCharacter(ConsoleOutput *out, 
         string name, Type primary_type, Stats stats,
         BattleMove *battleMove1, BattleMove *battleMove2,
         BattleMove *battleMove3, BattleMove *battleMove4, 
         string image, Type secondary_type=Type());
      // Manual Stat constructor
      PokemonCharacter(ConsoleOutput *out, 
         string name, Type primary_type,
         int health, int attack, int special_attack,
         int defense, int special_defense, int speed,
         BattleMove *battleMove1, BattleMove *battleMove2,
         BattleMove *battleMove3, BattleMove *battleMove4,
         string image, Type secondary_type = Type());
      PokemonCharacter(PokemonCharacter *other);
      // destructor
      ~PokemonCharacter();

      // memeber functions
      string getName() const;
      Type getPrimaryType() const;
      Stats *getStats();
      string getImage() const;
      Type getSecondaryType() const;
      StatusCondition *getStatusCondition();
      bool checkPPLeft(int pp, string battleMoveName) const;
      bool isBattleMoveUseable(string battleMoveName) const;
      bool isBattleMoveUseable(size_t battleSlot) const;
      size_t getBattleMoveSlot(string batteMoveName) const;
      BattleMove *getBattleMoveBySlot(size_t slot);
      bool doesBattleMoveNameExist(string batteMoveName) const;
      BattleMove *getBattleMoveByName(string batteMoveName);
      void useSelectedBattleMove(size_t selectedMove, Weather **battleWeather,
         Stats *oppPokemonStats, StatusCondition *oppStatusCondition, Type oppPrimaryType, Type oppSecondaryType);
      void changeStat(string statsToChange, int changingAmount);
      void changeStatusCondition(string newCondition);
      void tookDamaged(int damage);
      void tookPercentDamaged(double damage);
      bool applyStatusCondPreAffs();
      void applyStatusCondPostAffs();
      bool pokemonFainted() const;
      void display() const;
      void displayBattleMoves() const;
      void displayBattleMoveDescription() const;
      void displayInBattle(bool showType) const;

   private:
      ConsoleOutput *out;
      string name;
      Type primary_type;
      Stats *stats;
      BattleMove* battleMoves[NUM_BATTLE_MOVES];
      string image;
      StatusCondition* statusCondition;
      Type secondary_type;
      void setBattleMoves(vector<BattleMove *> battleMoves);
   };
}
#endif
