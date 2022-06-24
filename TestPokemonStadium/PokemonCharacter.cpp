/*
* Pokemon Project
*
* PokemonCharacter.h
* A class of each Pokemon character's info
*
*/
#include "PokemonCharacter.h"

// Sets the Pokemons name, type, stats-> battle moves, file path of image and secondary type
// default sets seconardy type to empty type. Sets statusConditon to a new StatusCondition
PokemonStadium::PokemonCharacter::PokemonCharacter(ConsoleOutput *out, string name, Type primary_type, Stats stats,
   BattleMove *battleMove1, BattleMove *battleMove2, 
   BattleMove *battleMove3, BattleMove *battleMove4,
   string image, Type secondaryType) {

   this->out = out;
   this->name = name;
   this->primary_type = primary_type;
   this->stats = new Stats(&stats);
   this->image = image;
   this->secondary_type = secondary_type;
   this->statusCondition = new StatusCondition(out);
   setBattleMoves({battleMove1, battleMove2, battleMove3, battleMove4});
}

// Sets the Pokemons name, type, stats-> battle moves, file path of image and secondary type
// default sets seconardy type to empty type. Sets statusConditon to a new StatusCondition
PokemonStadium::PokemonCharacter::PokemonCharacter(ConsoleOutput *out, string name, Type primary_type,
   int health, int attack, int special_attack,
   int defense, int special_defense, int speed,
   BattleMove *battleMove1, BattleMove *battleMove2,
   BattleMove *battleMove3, BattleMove *battleMove4,
   string image, Type secondary_type) {

   this->out = out;
   this->name = name;
   this->primary_type = primary_type;
   this->stats = new Stats(health, attack, special_attack, defense, special_defense, speed);
   this->image = image;
   this->secondary_type = secondary_type;
   this->statusCondition = new StatusCondition(out);
   setBattleMoves({battleMove1, battleMove2, battleMove3, battleMove4});
}

// Constructor that takes in a pointer to another ChargeMove and
// set this ChargeMove to other
PokemonStadium::PokemonCharacter::PokemonCharacter(PokemonCharacter *other) {
   this->out = other->out;
   this->name = other->name;
   this->primary_type = other->primary_type;
   this->stats = new Stats(other->stats);
   this->image = other->image;
   this->secondary_type = other->secondary_type;
   this->statusCondition = new StatusCondition(other->out, other->name);
   vector<BattleMove *> battleMovesList;
   for (size_t i = 0; i < NUM_BATTLE_MOVES; ++i) {
      battleMovesList.push_back(other->battleMoves[i]);
   }
   setBattleMoves(battleMovesList);
}

// destructor, deletes stats, statuscondition, and all battleMoves
PokemonStadium::PokemonCharacter::~PokemonCharacter() {
   delete stats;
   delete statusCondition;
   // loop through and delete all battle moves
   for (size_t i = 0; i < NUM_BATTLE_MOVES; ++i) {
      delete battleMoves[i];
   }
}

// Loops through the give vector of battleMoves and 
// creates new battle move of the same type BattleMove class and stores
// it into battleMovesArray

void PokemonStadium::PokemonCharacter::setBattleMoves(vector<BattleMove *> battleMoves) {
   // loops through the give list of BattleMoves
   for (size_t i = 0; i < battleMoves.size(); ++i) {
      
      if (ChargeMove *cMove =
         dynamic_cast<ChargeMove *>(battleMoves[i])) {
         this->battleMoves[i] = new ChargeMove(cMove);
      }
      else if (HiddenMove *hidMove =
         dynamic_cast<HiddenMove *>(battleMoves[i])) {
         this->battleMoves[i] = new HiddenMove(hidMove);
      }
      else if (RechargeMove *rMove =
         dynamic_cast<RechargeMove *>(battleMoves[i])) {
         this->battleMoves[i] = new RechargeMove(rMove);
      }
      else if (DamageMove *dMove =
         dynamic_cast<DamageMove *>(battleMoves[i])) {
         this->battleMoves[i] = new DamageMove(dMove);
      }
      else if (HealingMove *healMove =
         dynamic_cast<HealingMove *>(battleMoves[i])) {
         this->battleMoves[i] = new HealingMove(healMove);
      }
      else if (StatsChangingMove *statMove =
         dynamic_cast<StatsChangingMove *>(battleMoves[i])) {
         this->battleMoves[i] = new StatsChangingMove(statMove);
      }
      else if (StatusConditionMove *scMove =
         dynamic_cast<StatusConditionMove *>(battleMoves[i])) {
         this->battleMoves[i] = new StatusConditionMove(scMove);
      }
      else if (WeatherChangingMove *scMove =
         dynamic_cast<WeatherChangingMove *>(battleMoves[i])) {
         this->battleMoves[i] = new WeatherChangingMove(scMove);
      }
      else {
         cerr << "Slot " << i << ": is not a proper type of battle move\n";
         exit(EXIT_FAILURE);
      }
   }
}

// gets the name of the Pokemon 
string 
PokemonStadium::PokemonCharacter::getName() const {
   return name;
}

// gets the primary type of the Pokemon 
PokemonStadium::Type 
PokemonStadium::PokemonCharacter::getPrimaryType() const {
   return primary_type;
}

// gets pointer to the stats of the Pokemon 
PokemonStadium::Stats*
PokemonStadium::PokemonCharacter::getStats() {
   return stats;
}

// gets the image file of the Pokemon
string
PokemonStadium::PokemonCharacter::getImage() const {
   return image;
}

// gets the primary type of the Pokemon 
PokemonStadium::Type 
PokemonStadium::PokemonCharacter::getSecondaryType() const {
   return secondary_type;
}

// gets pointer to status conditon of the pokemon
PokemonStadium::StatusCondition*
PokemonStadium::PokemonCharacter::getStatusCondition(){
   return statusCondition;
}

// checks if the PP is greater than 0, otherwise prints a mesage
bool 
PokemonStadium::PokemonCharacter::checkPPLeft(int pp, string battleMoveName) const {
   if (pp > 0)
      return true;
   else {
      out->log(battleMoveName + " is out of pp");
      return false;
   }
}
// checks if the given battle move name is in the list of battle moves and if
// it is, checks it has pp to use the move. 
bool 
PokemonStadium::PokemonCharacter::isBattleMoveUseable(string batteMoveName) const {
   for (int battleSlot = 0; battleSlot < NUM_BATTLE_MOVES; battleSlot++) {
      if (batteMoveName == battleMoves[battleSlot]->getName()) {
         return checkPPLeft(battleMoves[battleSlot]->getCurrentPP(), batteMoveName);
      }
   }
   // if battle move was not found in batteMoves, print a message and return false
   out->log(batteMoveName + " is not a battle move of " + name);
   return false;
}

// checks if the given battle move slot is in the list of battle moves and if
// it is, checks it has pp to use the move. 
bool
PokemonStadium::PokemonCharacter::isBattleMoveUseable(size_t battleSlot) const {
   // if battle slot is in range of the battle moves, check if there is PP left
   if (battleSlot >= 0 && battleSlot < NUM_BATTLE_MOVES) {
      return checkPPLeft(battleMoves[battleSlot]->getCurrentPP(), battleMoves[battleSlot]->getName());
   }
   // else, print a message and return false
   else {
      out->log(battleSlot + " is outside the range of battle moves");
      return false;
   }
}

// returns the battle slot of the given battle move name
size_t
PokemonStadium::PokemonCharacter::getBattleMoveSlot(string batteMoveName) const {
   // loops through a each battle move and returns the battle slot of the given name
   for (size_t battleSlot = 0; battleSlot < NUM_BATTLE_MOVES; battleSlot++) {
      if (batteMoveName == battleMoves[battleSlot]->getName()) {
         return battleSlot;
      }
   }
   // if battle move was not found in batteMoves, print a message and return false
   out->log(batteMoveName + " is not a battle move of " + name + "\n");
   return false;
}
// returns the BattleMove base on slot
PokemonStadium::BattleMove*
PokemonStadium::PokemonCharacter::getBattleMoveBySlot(size_t slot) {
   // return battle move at slot if slot is in range
   if (slot >= 0 && slot < NUM_BATTLE_MOVES) {
      return battleMoves[slot];
   }
   // else throw an error
   else {
      cerr << slot << " is outside the range of battle moves\n";
      exit(EXIT_FAILURE);
   }
}

// see if the battleMove name exist
bool
PokemonStadium::PokemonCharacter::doesBattleMoveNameExist(string batteMoveName) const {
   // loops through a each battle move and returns the battle slot of the given name
   for (size_t battleSlot = 0; battleSlot < NUM_BATTLE_MOVES; battleSlot++) {
      if (batteMoveName == battleMoves[battleSlot]->getName()) {
         return true;
      }
   }
   // if it cannot find the battle move return false
   return false;
}
// returns the BattleMove base on name
PokemonStadium::BattleMove*
PokemonStadium::PokemonCharacter::getBattleMoveByName(string batteMoveName) {
   // loops through a each battle move and returns the battle slot of the given name
   for (size_t battleSlot = 0; battleSlot < NUM_BATTLE_MOVES; battleSlot++) {
      if (batteMoveName == battleMoves[battleSlot]->getName()) {
         return battleMoves[battleSlot];
      }
   }
   // if battle move was not found in batteMoves, print a message and return false
   cerr << batteMoveName << " is not a battle move of " << name << "\n";
   exit(EXIT_FAILURE);
}

// uses the Pokemon's battle move from the selected battle slot with the given battleWeather and 
// the opp information
// Note: This function will be called if move is locked
void
PokemonStadium::PokemonCharacter::useSelectedBattleMove(size_t selectedMove, Weather **battleWeather,
   Stats *oppPokemonStats, StatusCondition *oppStatusCondition, 
   Type oppPrimaryType, Type oppSecondaryType) {
   // Use RTTI to determine type of battle move and run the move function
   if (ChargeMove *cMove =
      dynamic_cast<ChargeMove *>(battleMoves[selectedMove])) {
      cMove->useChargeMove(*battleWeather,
         stats, statusCondition, primary_type, secondary_type,
         oppPokemonStats, oppStatusCondition, oppPrimaryType, oppSecondaryType
         );
   }
   else if (HiddenMove *hidMove =
      dynamic_cast<HiddenMove *>(battleMoves[selectedMove])) {
      hidMove->useHiddenMove(*battleWeather,
         stats, statusCondition, primary_type, secondary_type,
         oppPokemonStats, oppStatusCondition, oppPrimaryType, oppSecondaryType
         );
   }
   else if (RechargeMove *rMove =
      dynamic_cast<RechargeMove *>(battleMoves[selectedMove])) {
      rMove->useRechargeMove(*battleWeather,
         stats, statusCondition, primary_type, secondary_type,
         oppPokemonStats, oppStatusCondition, oppPrimaryType, oppSecondaryType
         );
   }
   else if (DamageMove *dMove =
      dynamic_cast<DamageMove *>(battleMoves[selectedMove])) {
      dMove->useDamageMove(*battleWeather,
         stats, statusCondition, primary_type, secondary_type,
         oppPokemonStats, oppStatusCondition, oppPrimaryType, oppSecondaryType
      );
   }
   else if (HealingMove *healMove =
      dynamic_cast<HealingMove *>(battleMoves[selectedMove])) {
      healMove->useHealMove(*battleWeather,
         stats, oppPokemonStats);
   }
   else if (StatsChangingMove *statMove =
      dynamic_cast<StatsChangingMove *>(battleMoves[selectedMove])) {
      statMove->useStatsChangingMove(stats, statusCondition,
         oppPokemonStats, oppStatusCondition, oppPrimaryType, oppSecondaryType);
   }
   else if (StatusConditionMove *scMove =
      dynamic_cast<StatusConditionMove *>(battleMoves[selectedMove])) {
      scMove->useStatusConditionMove(stats, statusCondition,
         oppPokemonStats, oppStatusCondition, oppPrimaryType, oppSecondaryType);
   }
   else if (WeatherChangingMove *wcMove =
      dynamic_cast<WeatherChangingMove *>(battleMoves[selectedMove])) {
      wcMove->useWeatherChanginMove(battleWeather);
   }
}

// calls the change stat modifier with the give stat to change and how much to change it by,
// returns true if change was successful
void
PokemonStadium::PokemonCharacter::changeStat(string statToChange, int changingPower) {
   stats->changeModifier(statToChange, changingPower);
}

// set the Pokemon Status Condition to the given condition
void
PokemonStadium::PokemonCharacter::changeStatusCondition(string newCondition) {
   // if condition to be set is confusion, call set confusion
   if (newCondition == "confused") {
      statusCondition->setConfusion();
   }
   // else set new condition and change stats if needed
   else {
      statusCondition->setCondition(newCondition, stats);
   }
   
}

// calls stats damage to health to apply damages pokemon took
void
PokemonStadium::PokemonCharacter::tookDamaged(int damage) {
   stats->damageToHealth(damage);
}

// calls stats damage to health to apply percent damages pokemon took
void
PokemonStadium::PokemonCharacter::tookPercentDamaged(double damage) {
   stats->damagePercentToHealth(damage);
}

// returns status condtion pre affects to see if the pokemon
// is block by status condition
bool
PokemonStadium::PokemonCharacter::applyStatusCondPreAffs() {
   return statusCondition->applyPreAffects(stats);
}

// calls Pokemon status condition apply affects to see and runs the 
// status condition post affects if there are any
void 
PokemonStadium::PokemonCharacter::applyStatusCondPostAffs() {
   statusCondition->applyPostAffect(stats);
}

// prints out the Pokemon's name, Type/s, each stat and battle move
void
PokemonStadium::PokemonCharacter::display() const {
   out->display(name + "\n");
      
   if (secondary_type == Type()) {
      out->display("Type: " + primary_type.getName() + "\n");
   }
   else {
      out->display("Primary Type: " + primary_type.getName() + "\n"
         + "Secondary Type: " + secondary_type.getName() + "\n");
   }
   //out->display("Health: " + (string)stats->getCurrentHeath() + "\n" +
   //   "Attack: " + stats->getAttack() + "\n" +
   //   "Special Attack: " + stats->getSpecialAttack() + "\n" +
   //   "Defense: " + stats->getDefense() + "\n" +
   //   "Special Defense: " + stats->getSpecialDefense() + "\n" +
   //   "Speed: " + stats->getSpeed() + "\n" +
   //   "Batte Moves: ");
   // loop through and print each battle move name
   for (int i = 0; i < NUM_BATTLE_MOVES; i++) {
      if (i + 1 == NUM_BATTLE_MOVES) {
         out->display(battleMoves[i]->getName() + ", ");
      }
      else {
         out->display(battleMoves[i]->getName() + ", ");
      }
   }
}

// display the number slot of the battle move and it name
void
PokemonStadium::PokemonCharacter::displayBattleMoves() const {
   for (size_t spotNum = 0; spotNum < NUM_BATTLE_MOVES; spotNum++) {
      out->display(spotNum + 1 + ": " + battleMoves[spotNum]->getName());
   }
}

// display the description of the battle moves of the Pokemon
void
PokemonStadium::PokemonCharacter::displayBattleMoveDescription() const {

   for (auto & battleMove : battleMoves) {
      battleMove->display();
   }
}

// display Pokemon name, health to be seeing during battle
// show type determines if the type should be shown as well
void 
PokemonStadium::PokemonCharacter::displayInBattle(bool showType) const {
   out->display("Name: " + name);
   // if showType print the primary and secondary type
   if (showType) {
      out->display("Type: " + primary_type.getName()
         + " " + secondary_type.getName());
   }
   out->display("Health: " + stats->getCurrentHeath());
}

// returns true if the Pokemon health has drop to 0
bool 
PokemonStadium::PokemonCharacter::pokemonFainted() const {
   if (stats->getCurrentHeath() <= 0) {
      return true;
   }
   else {
      return false;
   }
}
