/*
* Pokemon
*
* BattleMove.cpp
*/

#include "BattleMove.h"

// default constructor -- might need to remove
PokemonStadium::BattleMove::BattleMove(){
   this->out = NULL;
   this->name = "";
   this->type = Type();
   this->category = "";
   this->totalPP = 0;
   this->currentPP = 0;
   this->power = 0;
   this->accuracy = 0;
   this->description = "";
   this->priority = LOWEST_PRIORTY;
   this->moveLocked = false;
}

// Sets the name, type, category, pp, power, accuracy, description, priority
// turns of the battle move. totalTurns is set to 1 by default
PokemonStadium::BattleMove::BattleMove(ConsoleOutput *out,
   string name, Type type, string category, int pp, int power,
   int accuracy, string description, int priority) {
   this->out = out;
   this->name = name;
   this->type = type;
   this->category = category;
   this->totalPP = pp;
   this->currentPP = pp;
   this->power = power;
   this->accuracy = accuracy;
   this->description = description;
   this->priority = priority;
   this->moveLocked = false;
}

PokemonStadium::ConsoleOutput *
PokemonStadium::BattleMove::getConsoleOutput() {
   return out;
}

// Gets the name of the battle move 
string 
PokemonStadium::BattleMove::getName() const {
   return name;
}

// Gets the Type of battle move
PokemonStadium::Type 
PokemonStadium::BattleMove::getType() const {
   return type;
}

// Gets the category of the battle move 
string
PokemonStadium::BattleMove::getCategory() const {
   return category;
}

// Gets the power of the battle move
int 
PokemonStadium::BattleMove::getPower() const {
   return power;
}

// Gets the accuracy of the battle move
int 
PokemonStadium::BattleMove::getAccuracy() const {
   return accuracy;
}

// Gets the TotalPower Points of the battle move
int
PokemonStadium::BattleMove::getTotalPP() const {
   return totalPP;
}

// Gets the Current Power Points of the battle move
int
PokemonStadium::BattleMove::getCurrentPP() const {
   return currentPP;
}

// Gets the description of the battle move
string 
PokemonStadium::BattleMove::getDescription() const {
   return description;
}

// Gets the priority of the battle move
int
PokemonStadium::BattleMove::getPriority() const {
   return priority;
}

// Gets if the move is locked
bool 
PokemonStadium::BattleMove::isMovedLocked() const {
   return moveLocked;
}

// calucates if the move will hit by taking in the user accurary, 
// opponents accuracy, and move accuracy for the percent chance it will hit
bool
PokemonStadium::BattleMove::hit(double userAccuracy, double oppEvasion, double fieldAccuracyMultipler) {
   // if attack is a never miss return true
   if (accuracy == NEVER_MISS) {
      return true;
   }
   else {
      // modifiers value should never be 0 so add 1 to MAX_MODIFIER 
      int modifier_limit = MAX_MODIFIER + 1;
      // if user accuracy and oppEvasion haven't been changed, modifiers should equal 1
      // if user accuracy has been increase more than oppEvasion, modifier should be greater than 1
      // if user accuracy has been decreased or oppEvasion has been increased more than user accuracy
      // modifiers should be less than 1
      double modifiers = (modifier_limit + (userAccuracy - oppEvasion)) / modifier_limit;
      double battleAccuracy = this->accuracy * fieldAccuracyMultipler * modifiers;
      int random = rand() % 100;
      if (random <= battleAccuracy)
         return true;
      else
         return false;
   }
}

// logs the user Pokemon uses battle move
void 
PokemonStadium::BattleMove::logBattleMove() {
   out->userLog("used " + name);
}

// virtual function, display the battle move
void
PokemonStadium::BattleMove::display() const {}