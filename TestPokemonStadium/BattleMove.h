/*
* Pokemon Project
*
* BattleMove.h
* A base class for all moves when in battle
* Every battle mode has a name, type, accuracy
*
*/
#ifndef POKEMONSTADIUM_BATTLEMOVE_H
#define POKEMONSTADIUM_BATTLEMOVE_H

#include "Weather.h"
#include "Global.h"
#include "Stats.h"
#include "StatusCondition.h"
#include "ConsoleOutput.h"

#define CATEGORY_PHSYICAL "physical"
#define CATEGORY_SPECIAL "special"
#define CATEGORY_STATUS "status"

namespace PokemonStadium
{
   class BattleMove {
   public:
      // Constructor
      BattleMove();
      BattleMove(ConsoleOutput *out,
         string name, Type type, string category, int pp, int power, int accuracy,
         string description, int priorty = 0);
      // memeber functions
      ConsoleOutput *getConsoleOutput();
      string getName() const;
      Type getType() const;
      string getCategory() const;
      int getTotalPP() const;
      int getCurrentPP() const;
      int getPower() const;
      int getAccuracy() const;
      string getDescription() const;
      int getPriority() const;
      bool isMovedLocked() const;
      bool hit(double userAccuracy, double oppEvasion, double fieldAccuracyMultipler);
      void logBattleMove();
      virtual void display() const;

   protected:
      ConsoleOutput *out;
      int totalPP;
      int currentPP;
      int power;
      string category;
      bool moveLocked;
      int priority;

   private:
      string name;
      Type type;
      int accuracy;
      string description;
   };
}
#endif
