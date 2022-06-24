/*
* Pokemon Project
*
* MultipleTurnMove.cpp
* A damage move that takes more than one turn
*
*/

#include "MultipleTurnMove.h"

// no waitTurnDescription, extra effect, given accuracy
// set name, type, pp, description, accuracy, damageMoveType, power with DamageMove Constructor
PokemonStadium::MultipleTurnMove::MultipleTurnMove(ConsoleOutput *out, 
   string name, Type type, string category, int pp, int power, int accuaracy, string description,
   string typeOfTurnMove) :
   DamageMove(out, name, type, category, pp, power, accuaracy, description) {
   this->typeOfTurnMove = typeOfTurnMove;
   this->waitTurnDescription = waitTurnDescription;
   // default turnMoveCalled to true so when move is called the first actions are applied
   turnMoveCalled = true;

}

// no extra effect, given accuracy
// set name, type, pp, description, accuracy, damageMoveType, power with DamageMove Constructor
PokemonStadium::MultipleTurnMove::MultipleTurnMove(ConsoleOutput *out, 
   string name, Type type, string category, int pp, int power, int accuaracy, string description, 
   string typeOfTurnMove, string waitTurnDescription) :
   DamageMove(out, name, type, category, pp, power, accuaracy, description) {
   this->typeOfTurnMove = typeOfTurnMove;
   this->waitTurnDescription = waitTurnDescription;
   // default turnMoveCalled to true so when move is called the first actions are applied
   turnMoveCalled = true;
}

// extra effect, given accuracy
// set name, type, pp, description, accuracy, damageMoveType, power with DamageMove Constructor
PokemonStadium::MultipleTurnMove::MultipleTurnMove(ConsoleOutput *out,
   string name, Type type, string category, int pp, int power, int accuaracy, string description,
   BattleMoveEffects *otherEffect,
   string typeOfTurnMove, string waitTurnDescription) :
   DamageMove(out, name, type, category, pp, power, accuaracy, description, otherEffect) {
   this->typeOfTurnMove = typeOfTurnMove;
   this->waitTurnDescription = waitTurnDescription;
   // default turnMoveCalled to true so when move is called the first actions are applied
   turnMoveCalled = true;
}

// Gets the type Of Multiple Turn Move
string
PokemonStadium::MultipleTurnMove::getTypeOfTurnMove() {
   return typeOfTurnMove;
}

// Gets the description of what to print out during the turn not attacking
string
PokemonStadium::MultipleTurnMove::getWaitTurnDescription() {
   return waitTurnDescription;
}
