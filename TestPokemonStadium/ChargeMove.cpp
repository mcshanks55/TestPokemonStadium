/*
* Pokemon Project
*
* ChargeMove.cpp
* A MultipleTurnMove that first charges and then does damage
*
*/

#include "ChargeMove.h"

// no extra effect, given accuracy
// set name, type, pp, description, accuracy, damageMoveType, power with DamageMove Constructor
// set typeOfTurnMove and waitTurnDescription with MultipleTurnMove Constructor
PokemonStadium::ChargeMove::ChargeMove(ConsoleOutput *out,
   string name, Type type, string category, int pp, int power, int accuaracy, string description,
   string waitTurnDescription) :
   MultipleTurnMove(out, name, type, category, pp, power, accuaracy, description, 
      TYPE_OF_MOVE_CHARGE, waitTurnDescription) {
   noChargeWeather = {};
   this->applyDuringCharge = false;
   moveCharged = false;
}

// extra effect, given accuracy
// set name, type, pp, description, accuracy, damageMoveType, power, otherEffects with DamageMove Constructor
// set typeOfTurnMove and waitTurnDescription with MultipleTurnMove Constructor
PokemonStadium::ChargeMove::ChargeMove(ConsoleOutput *out, 
   string name, Type type, string category, int pp, int power, int accuaracy, string description,
   BattleMoveEffects *otherEffects, bool applyDuringCharge,
   string waitTurnDescription) :
   MultipleTurnMove(out, name, type, category, pp, power, accuaracy, description, otherEffects, 
      TYPE_OF_MOVE_CHARGE, waitTurnDescription) {
   noChargeWeather = {};
   this->applyDuringCharge = applyDuringCharge;
   moveCharged = false;
}

// noChargeWeather, no extra effect, given accuracy
// set name, type, pp, description, accuracy, damageMoveType, power, otherEffects with DamageMove Constructor
// set typeOfTurnMove and waitTurnDescription with MultipleTurnMove Constructor
PokemonStadium::ChargeMove::ChargeMove(ConsoleOutput *out, 
   string name, Type type, string category, int pp, int power, int accuaracy, string description,
   string waitTurnDescription, vector<Weather> noChargeWeather) :
   MultipleTurnMove(out, name, type, category, pp, power, accuaracy, description, TYPE_OF_MOVE_CHARGE, waitTurnDescription) {
   this->noChargeWeather = noChargeWeather;
   this->applyDuringCharge = false;
   moveCharged = false;
}

// Constructor that takes in a pointer to another ChargeMove and
// set this ChargeMove to other
PokemonStadium::ChargeMove::ChargeMove(PokemonStadium::ChargeMove *other) :
   MultipleTurnMove(other->out, 
      other->getName(), other->getType(), other->getCategory(), other->getTotalPP(), 
      other->getPower(), other->getAccuracy(), other->getDescription(),
      other->getTypeOfTurnMove(), other->getWaitTurnDescription()) {
   this->noChargeWeather = other->noChargeWeather;
   this->applyDuringCharge = other->applyDuringCharge;
   moveCharged = false;
}

// calls damage move destructor to delete otherEffect if there is one
PokemonStadium::ChargeMove::~ChargeMove() {
}

// takes a turn to charge than on the next turn does the damage.
// if otherEffects they are applied during charging turn
// if the batteFieldWeather is the same as the noChargeWeather then
// damage can be applied on the turn battleMove is called
void PokemonStadium::ChargeMove::useChargeMove(Weather *battleWeather,
   Stats *userPokemonStats, StatusCondition *userStatusCondition, Type userPrimaryType, Type userSecondaryType,
   Stats *oppPokemonStats, StatusCondition *oppStatusCondition, Type oppPrimaryType, Type oppSecondaryType) {

   // if move was just called, start charging
   if (turnMoveCalled) {
      currentPP--;
      out->log(getWaitTurnDescription());

      // if move has other effect that should be apply during charge apply it
      if (getOtherEffect() != NULL && applyDuringCharge) {
         getOtherEffect()->applyEffect(userPokemonStats,
            oppPokemonStats, oppStatusCondition, oppPrimaryType, oppSecondaryType);
      }
      // if the weather is in the noChargeWeather,
      // attack can be apply same turn as charge
      for (auto & weather : noChargeWeather) {
         if (weather == *battleWeather) {
            moveCharged = true;
         }
      }
   }

   // if move is charge, attack. If attack does damage and there is
   // and other effect, apply effect
   if (moveCharged) {
      // logs and applies all attack functions
      bool didDamage = attack(battleWeather,
         userPokemonStats, userStatusCondition, userPrimaryType, userSecondaryType,
         oppPokemonStats, oppStatusCondition, oppPrimaryType, oppSecondaryType);
      // if move has other effect that should be apply after charge see if it should be applied
      if (getOtherEffect() != NULL && !applyDuringCharge && didDamage) {
         getOtherEffect()->applyEffect(userPokemonStats,
            oppPokemonStats, oppStatusCondition, oppPrimaryType, oppSecondaryType);
      }
      moveLocked = false;
      moveCharged = false;
      turnMoveCalled = true;
   }
   // if move needs a turn to charge, locked move and have charge be complete for next turn
   else {
      moveLocked = true;
      moveCharged = true;
      turnMoveCalled = false;
   }
}