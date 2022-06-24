/*
* Pokemon Project
*
* RechargeMove.cpp
* A MultipleTurnMove that unless the attack and then needs a recharge
* the next turn
*
*/

#include "RechargeMove.h"

// no extra effect, given accuracy
// set name, type, pp, description, accuracy, damageMoveType, power with DamageMove Constructor
// set typeOfTurnMove and waitTurnDescription with MultipleTurnMove Constructor
PokemonStadium::RechargeMove::RechargeMove(ConsoleOutput *out, 
   string name, Type type, string category, int pp, int power, int accuaracy, string description) : 
   MultipleTurnMove(out, name, type, category, pp, power, accuaracy, description,
      TYPE_OF_MOVE_RECHARGE, WAIT_TURN_DESC) {}

// Constructor that takes in a pointer to another RechargeMove and
// set this RechargeMove to other
PokemonStadium::RechargeMove::RechargeMove(PokemonStadium::RechargeMove *other) :
   MultipleTurnMove(other->out,
      other->getName(), other->getType(), other->getCategory(), other->getTotalPP(), 
      other->getPower(), other->getAccuracy(), other->getDescription(),
      other->getTypeOfTurnMove(), other->getWaitTurnDescription()) {}

// takes a turn to charge than on the next turn does the damage.
// if otherEffects they are applied during charging turn
// if the batteFieldWeather is the same as the noChargeWeather then
// damage can be applied on the turn battleMove is called
void PokemonStadium::RechargeMove::useRechargeMove(Weather *battleWeather,
   Stats *userPokemonStats, StatusCondition *userStatusCondition, Type userPrimaryType, Type userSecondaryType,
   Stats *oppPokemonStats, StatusCondition *oppStatusCondition, Type oppPrimaryType, Type oppSecondaryType) {

   // if move hasn't been used, attack
   if (turnMoveCalled) {
      currentPP--;
      attack(battleWeather,
         userPokemonStats, userStatusCondition, userPrimaryType, userSecondaryType,
         oppPokemonStats, oppStatusCondition, oppPrimaryType, oppSecondaryType);
      turnMoveCalled = false;
      moveLocked = true;
   }
   // if the move has been use, pokemon needs to recharge
   else {
      out->userLog("needs to charge");
      turnMoveCalled = true;
      moveLocked = false;
   }
}
