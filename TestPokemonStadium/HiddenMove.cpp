/*
* Pokemon Project
*
* HiddenMove.cpp
* A MultipleTurnMove that hides the Pokemon for a turn
* then attacks
*
*/
#include "HiddenMove.h"

// no extra effect, given accuracy
// set name, type, pp, description, accuracy, damageMoveType, power with DamageMove Constructor
// set typeOfTurnMove and waitTurnDescription with MultipleTurnMove Constructor
PokemonStadium::HiddenMove::HiddenMove(ConsoleOutput *out, 
   string name, Type type, string category,
   int pp, int power, int accuaracy, string description,
   string waitTurnDescription) :
   MultipleTurnMove(out, name, type, category, pp, power, accuaracy, description,
      TYPE_OF_MOVE_HIDDEN, waitTurnDescription) {}

// Constructor that takes in a pointer to another HiddenMove and
// set this HiddenMove to other
PokemonStadium::HiddenMove::HiddenMove(PokemonStadium::HiddenMove *other) :
   MultipleTurnMove(other->out, other->getName(), other->getType(), other->getCategory(),
      other->getTotalPP(), other->getPower(), other->getAccuracy(), other->getDescription(),
      other->getTypeOfTurnMove(), other->getWaitTurnDescription()) {}

// takes a turn to charge than on the next turn does the damage.
// if otherEffects they are applied during charging turn
// if the batteFieldWeather is the same as the noChargeWeather then
// damage can be applied on the turn battleMove is called
void PokemonStadium::HiddenMove::useHiddenMove(Weather *battleWeather,
   Stats *userPokemonStats, StatusCondition *userStatusCondition, Type userPrimaryType, Type userSecondaryType,
   Stats *oppPokemonStats, StatusCondition *oppStatusCondition, Type oppPrimaryType, Type oppSecondaryType) {
   // if move hasn't been used yet, hide pokemon
   if (turnMoveCalled) {
      currentPP--;
      out->userLog(getWaitTurnDescription());
      // hide pokemon by increasing there evasion to 6, pokemon can only
      // be hit by a never miss 
      userPokemonStats->changeModifier("evasion", NEVER_MISS);
      // lock move and prepare to do second actions
      turnMoveCalled = false;
      moveLocked = true;
   }
   // if move has been use, unhide pokemon and attack
   else {
      // unhide user pokemon by set evasion stat back
      userPokemonStats->changeModifier("evasion", -NEVER_MISS);
      attack(battleWeather,
         userPokemonStats, userStatusCondition, userPrimaryType, userSecondaryType,
         oppPokemonStats, oppStatusCondition, oppPrimaryType, oppSecondaryType);
      // reset move to be able to be called again
      turnMoveCalled = true;
      moveLocked = false;
   }
}
