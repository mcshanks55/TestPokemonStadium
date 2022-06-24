/*
* Pokemon
*
* StatusMove.cpp
*/

#include "StatusMove.h"

// empty constructor
PokemonStadium::StatusMove::StatusMove() :
   BattleMove() {}

// Constructor for Status Move
// default priority defaults to 0
// set the give name, type, pp, accuracy, description, priority with Battle move
// sets category to CATEGORY_STATUS, power to 0
PokemonStadium::StatusMove::StatusMove(ConsoleOutput *out, 
   string name, Type type, int pp, int accuracy, string description, int priority) :
   BattleMove(out, name, type, CATEGORY_STATUS, pp, 0, accuracy, description, priority){}

// prints the Damage move name, type, power, accuracy, pp, category and description
void
PokemonStadium::StatusMove::display() const {
   string accuracyDisplay;
   if (getAccuracy() == NEVER_MISS) {
      accuracyDisplay = "--";
   }
   else {
      accuracyDisplay = getAccuracy();
   }
   //out->display(getName() + "\n" +
   //   "Type: " + getType().getName() + " Power: " + power + " Accuracy: " + getAccuracy() + accuracyDisplay + "%" +
   //   " PP: " + totalPP + " Category:" + getCategory() + "\n" + getDescription());
}