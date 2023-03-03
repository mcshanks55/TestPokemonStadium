/*
* Pokemon Project
*
* Trainer.cpp
* Class of the Pokemon Trainer. Each trainer has a name and a Pokemon party in a 
* queue
*
*/

#include "Trainer.h"

// sets the name of the trainer and a queue of Pokemon
PokemonStadium::Trainer::Trainer(ConsoleOutput *out, string id, string trainerName) {
   this->out = out;
   this->id = id;
   this->name = trainerName;
   pokemonParty = {};
   battleParty = {};
   // setting pokemon in battle empty
   pokemonInBattleSlotA = 0;
   pokemonInBattleSlotB = 0;
   switchingPokemonOut = false;
   // switchingPokemon: addd the first pokemon being switch out follow 
   // by the pokemon that is being switch with
   // Maxium Pokemon being switch out = 2
   vector<size_t> switchingPokemon = {4};
}

// Destructor - destroyies all Pokemon in pokemonParty
PokemonStadium::Trainer::~Trainer() {
   for (size_t slot = 0; slot < pokemonParty.size(); slot++) {
      delete pokemonParty[slot];
   }
}

// Gets the id of Trainer
string
PokemonStadium::Trainer::getId() const {
   return id;
}

// Gets the name of Trainer
string 
PokemonStadium::Trainer::getName() const {
   return name;
}

// Gets the pokemon party
vector<PokemonStadium::PokemonCharacter *>
PokemonStadium::Trainer::getPokemonParty() const {
   return pokemonParty;
}

// adds a Pokemon to the pokemon party
void PokemonStadium::Trainer::addPokemonToParty(PokemonCharacter *pokemon) {
   PokemonCharacter *new_pokemon = new PokemonCharacter(pokemon);
   pokemonParty.push_back(new_pokemon);
}

// Sets trainer's pokemon party to the given pokemon party
void
PokemonStadium::Trainer::setPokemonParty(vector<PokemonCharacter*> pokemonParty) {
   // loop through the given pokemonParty list and add each Pokemon
   // as new Pokemon to pokemon party
   for (auto & pokemon : pokemonParty) {
      PokemonCharacter *new_pokemon = new PokemonCharacter(pokemon);
      this->pokemonParty.push_back(new_pokemon);
   }
}

// set the pokemon party to the battle party by taking in
// a list of the battle slots of the current pokemonParty order
// to be in during the battle; 
void
PokemonStadium::Trainer::setBattleParty(vector<int> battleSlots) {
   for (auto & slot : battleSlots) {
     battleParty.push_back(pokemonParty[slot]);
   }
}

// Gets the Pokemon current in battle (only use for single battle)
PokemonStadium::PokemonCharacter *
PokemonStadium::Trainer::getPokemonInBattle() {
   return battleParty[pokemonInBattleSlotA];
}

// Gets the Pokemon in slot A
PokemonStadium::PokemonCharacter *
PokemonStadium::Trainer::getPokemonAInBattle() {
   return battleParty[pokemonInBattleSlotA];
}

// Gets the Pokemon in slot B
PokemonStadium::PokemonCharacter *
PokemonStadium::Trainer::getPokemonBInBattle() {
   return battleParty[pokemonInBattleSlotB];
}

// reset switching pokemon out back to not active
void
PokemonStadium::Trainer::resetSwitchingPokemon() {
   switchingPokemonOut = false;
}
// checks if the Pokemon in battle can be switch out with a pokemon in the
// battle party. Returns true if its possible returns false if not
bool 
PokemonStadium::Trainer::pickPokemonToSwitch(size_t battlePartySpot) {
   // if the given number is out of range
   if (battlePartySpot < 1 || battlePartySpot > battleParty.size()) {
      out->log(std::to_string(battlePartySpot) + " battlePartySpot is not available for switching");
      return false;
   }
   // if given number is the pokemon already out
   else if(battlePartySpot == pokemonInBattleSlotA || battlePartySpot == pokemonInBattleSlotB){
      out->log("Pokemon is already out");
      return false;
   }
   // else pokemon is able to be switched out
   else {
      // if Pokemon has not fainted it can be switchout
      // otherwise it cannot
      if (isPokemonInSlotAbleToBattle(battlePartySpot)) {
      switchingPokemonOut = true;
      return true;
      }
      else
         return false;
   }
}

// switches out the pokemon in the battle with given Pokemon
// battle spot in the battle party
// Only use for Single Battles
void
PokemonStadium::Trainer::switchPokemon(size_t battlePartySpot) {
   pokemonInBattleSlotA = battlePartySpot;
}

// switches out the pokemon in the battle slot A with given Pokemon
// battle spot in the battle party
void
PokemonStadium::Trainer::switchPokemonInSlotA(size_t battlePartySpot) {
   pokemonInBattleSlotA = battlePartySpot;
}

// switches out the pokemon in the battle slot B with given Pokemon
// battle spot in the battle party
void
PokemonStadium::Trainer::switchPokemonInSlotB(size_t battlePartySpot) {
   pokemonInBattleSlotB = battlePartySpot;
}

// get move priority of the Pokemon in slot A
int
PokemonStadium::Trainer::getSlotAMovePriority() {
   return slotAMovePriority;
}

// get move priority of the Pokemon in slot B
int
PokemonStadium::Trainer::getSlotBMovePriority() {
   return slotAMovePriority;
}

// set move priority of the Pokemon in slot A
void
PokemonStadium::Trainer::setSlotAMovePriority(int priority) {
   this->slotAMovePriority = priority;
}

// set move priority of the Pokemon in slot B
void
PokemonStadium::Trainer::setSlotBMovePriority(int priority) {
   this->slotAMovePriority = priority;
}

// checks if the pokemon has fainted, if it has, remove
// Pokemon from battle party and return true
bool
PokemonStadium::Trainer::hasPokemonOutHasFainted() {
   if (getPokemonInBattle()->pokemonFainted()) {
      out->log(name + " 's " + getPokemonInBattle()->getName()
         + " has fainted");
      return true;
   }
   else {
      return false;
   }
}

// Checks if the Pokemon in the given slot has not fainted
bool 
PokemonStadium::Trainer::isPokemonInSlotAbleToBattle(size_t slot) {
   return !battleParty[(slot)]->pokemonFainted();
}

// returns true if the Pokemon the battle move
// get BattleMoveBy name will handle error if name doesn't exist
// has pp left
bool
PokemonStadium::Trainer::canBattleMoveBePicked(string selectMoveName) {
   // Gets the battle move of te given battle name from pokemon in battle
   BattleMove *pickedMoved = getPokemonInBattle()->getBattleMoveByName(selectMoveName);
   if (pickedMoved->getCurrentPP() == 0) {
      out->log(pickedMoved->getName() + " is out of pp");
      return false;
   }
   // else battle move can be used
   else {
      return true;
   }
}

// Logs the Trainer's is using the Pokemon in battle selected battle move and then
// uses battle move against opponent
// Note: This function will not be called if move is locked
void 
PokemonStadium::Trainer::usePokemonInBattleBattleMove(size_t selectedMove, Weather **battleWeather,
   string oppTrainersName, string oppPokemonName,
   Stats *oppPokemonStats, StatusCondition *oppStatusCondition, Type oppPrimaryType, Type oppSecondaryType) {
   PokemonCharacter *pokemon = getPokemonInBattle();
   // print "$Trainer command $PokemonName to use $battleMoveName"
   out->log(name + " commands " + pokemon->getName() + " to use " + 
      pokemon->getBattleMoveBySlot(selectedMove)->getName());
   pokemon->useSelectedBattleMove(selectedMove, battleWeather,
      oppPokemonStats, oppStatusCondition, oppPrimaryType, oppSecondaryType);
}

// display the name of each Pokemon in the Pokemon Party
void
PokemonStadium::Trainer::displayPokemonParty() {
   for (auto & pokemon : pokemonParty) {
      out->display(pokemon->getName());
   }
}

// displays a description of each Pokemon in the battle party
void
PokemonStadium::Trainer::annoucePokemonEnteringBattle() {
   out->display(name + " sends out " + getPokemonInBattle()->getName());
}
