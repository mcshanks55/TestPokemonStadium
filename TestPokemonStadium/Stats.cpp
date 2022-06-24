/*
* Pokemon
*
* Stats.h
* The stats of a Pokemon.
* Each Pokemon have indiviuals stats:
*    Health, Attack, Special Attack, Defense, Special Defense, Speed
* All Pokemon also have a accuracy and evasion stat that is only used during
* a battle and start off at 100%.
* Current health can be decrease by damage and increase healing during battle
* All other stats are only changed by changing modifiers during battle
*
*/

#include "Stats.h"

// default Stats
PokemonStadium::Stats::Stats() {
   current_health = 0;
   total_health = 0;
   attack = 0;
   special_attack = 0;
   defense = 0;
   special_defense = 0;
   speed = 0;
   resetModifiers();
   clearStatusConditionModifier();
}

// initializes all the stats
PokemonStadium::Stats::Stats(int health, int attack, int special_attack,
   int defense, int special_defense, int speed) {
   // total health is set to health, current
   // health start equal to total health and changes during battle
   this->total_health = health;
   this->current_health = total_health;
   // all stats can be changed during battle
   this->attack = attack;
   this->special_attack = special_attack;
   this->defense = defense;
   this->special_defense = special_defense;
   this->speed = speed;
   resetModifiers();
   clearStatusConditionModifier();
}

PokemonStadium::Stats::Stats(Stats *other) {
   this->total_health = other->total_health;
   this->current_health = this->total_health;
   this->attack = other->attack;
   this->special_attack = other->special_attack;
   this->defense = other->defense;
   this->special_defense = other->special_defense;
   this->speed = other->speed;
   resetModifiers();
   clearStatusConditionModifier();
}

// gets the total health
int
PokemonStadium::Stats::getTotalHeath() const {
   return total_health;
}

// gets the attack
int
PokemonStadium::Stats::getAttack() const {
   return attack;
}

// gets the special attack
int
PokemonStadium::Stats::getSpecialAttack() const {
   return special_attack;
}

// gets the defense
int
PokemonStadium::Stats::getDefense() const {
   return defense;
}

// gets the special defense
int
PokemonStadium::Stats::getSpecialDefense() const {
   return special_defense;
}

// gets the speed
int
PokemonStadium::Stats::getSpeed() const {
   return speed;
}

// gets the given stat name original stat value
int
PokemonStadium::Stats::getStatValueByName(string statName) const {

   // accuracy and evasion stat original stat is 100%
   if (statName == "accuracy") {
      return 1;
   }
   else if (statName == "evasion") {
      return 1;
   }

   // all other stats are set at initialization
   // total health = original stat health
   else if (statName == "health") {
      return total_health;
   }

   else if (statName == "attack") {
      return attack;
   }
   else if (statName == "special attack") {
      return special_attack;
   }
   else if (statName == "defense") {
      return defense;
   }
   else if (statName == "special defense") {
      return special_defense;
   }
   else if (statName == "speed") {
      return speed;
   }

   else {
      cerr << statName << " is not an accpetable stat";
      exit(EXIT_FAILURE);
   }
}

// gets the given stat name original stat value
int
PokemonStadium::Stats::getModifierByName(string statName) const {
   if (statName == "accuracy") {
      return m_accuracy;
   }
   else if (statName == "evasion") {
      return m_evasion;
   }

   if (statName == "attack") {
      return m_attack;
   }
   else if (statName == "special attack") {
      return m_special_attack;
   }
   else if (statName == "defense") {
      return m_defense;
   }
   else if (statName == "special defense") {
      return m_special_defense;
   }
   else if (statName == "speed") {
      return m_speed;
   }

   else {
      cerr << statName << " is not an accpetable stat";
      exit(EXIT_FAILURE);
   }
}

// gets the current health
int
PokemonStadium::Stats::getCurrentHeath() const {
   return current_health;
}

// subtracts damage from current health
// current health cannot be less than 0
void
PokemonStadium::Stats::damageToHealth(int damage) {
   // damage is larger than current health, set current health to 0
   if (damage >= current_health) {
      current_health = 0;
   }
   // else minus damage from current health
   else {
      current_health -= damage;
   }
}

// takes the given damage percentage times the total health stat
// and then subtract that value from the current health stat
void
PokemonStadium::Stats::damagePercentToHealth(double damagePer) {
   int damage = (int)(total_health * damagePer);
   damageToHealth(damage);
}

// adds health back to the current health
// cannot be heal more than total health
void
PokemonStadium::Stats::healHealth(int healingPower) {
   // if healing power is more than total health, set current
   // health to toal health
   if (current_health + healingPower >= total_health) {
      current_health = total_health;
   }
   // else add healing power to current health
   else {
      current_health += healingPower;
   }
}

// takes the given damage percentage times the total health stat
// and then subtract that value from the current health stat
void
PokemonStadium::Stats::healPercentageHealth(double healingPowerPer) {
   int healingPower = (int)(total_health * healingPowerPer);
   healHealth(healingPower);
}

// Calculates the new attack value based on how much its has been modified
double
PokemonStadium::Stats::getModifiedStatValue(string stat) {

   // store the original stat value and its modifier value
   double original_stat = (double)getStatValueByName(stat);
   double modifier = (double)getModifierByName(stat);

   double denominator;
   // accuracy and evasion  have a different denominator than 
   // the other stats
   if (stat == "accuracy" || stat == "evasion") {
      denominator = ACCURACY_DENOMINATOR;
   } // all other stats denominator
   else {
      denominator = STAT_DENOMINATOR;
   }

   double statusConditionModifier = 1;
   if (stat == statusConditionReduceStat) {
      statusConditionModifier = statusConditionReduceValue;
   }

   // increase stat calculations
   if (modifier >= 0) {
      return original_stat * ((modifier + denominator) / denominator) * statusConditionModifier;
   }
   // decrease stat calculations
   else {
      return original_stat * (denominator / (denominator - modifier)) * statusConditionModifier;
   }
}

// checks if a stat has can be changed, return true
// If the modifier max has been reached, return false.
bool
PokemonStadium::Stats::canModifierBeChanged(string stat, int changingAmount) {
   // finds the stat base on the stat name, changes the stat's modifier if it
   // not greater the MAX_MODIFIER or less than the -MAX_MODIFIER
   int modifier = getModifierByName(stat);
   return (modifier + changingAmount <= MAX_MODIFIER && modifier + changingAmount >= -MAX_MODIFIER);
}

// takes in a stat and how much each of the stat should be changed by
// changes the stat modifier 
void
PokemonStadium::Stats::changeModifier(string stat, int changingAmount) {

   if (stat == "attack") {
      m_attack += changingAmount;
   }
   else if (stat == "special attack") {
      m_special_attack += changingAmount;
   }
   else if (stat == "defense") {
      m_defense += changingAmount;
   }
   else if (stat == "special defense") {
      m_special_defense += changingAmount;
   }
   else if (stat == "speed") {
      m_speed += changingAmount;
   }
   else if (stat == "accuracy") {
      m_accuracy += changingAmount;
   }

   else if (stat == "evasion") {
      m_evasion += changingAmount;
   }
   else {
      cerr << stat << " is not an accpetable stat";
      exit(EXIT_FAILURE);
   }

}

// if the pokemon has a stats condition that effects a stat,
// set the statusConditionModifyStat & the statusConditionModifyValue
// 
void
PokemonStadium::Stats::addStatusConditionModifier(string stat, double modifyValue) {

   if (stat == "attack" || stat == "special attack" || 
      stat == "defense" || stat == "special defense" ||
      stat == "speed" || stat == "accuracy" || stat == "evasion") {
      statusConditionReduceStat = stat;
      statusConditionReduceValue = modifyValue;
   }
   else {
      cerr << stat << " is not an accpetable stat";
      exit(EXIT_FAILURE);
   }

}

void
PokemonStadium::Stats::resetModifiers() {
   m_attack = 0;
   m_special_attack = 0;
   m_defense = 0;
   m_special_defense = 0;
   m_speed = 0;
   m_accuracy = 0;
   m_evasion = 0;
}

// Clear status condition modifier
void
PokemonStadium::Stats::clearStatusConditionModifier() {
   statusConditionReduceStat = "";
   statusConditionReduceValue = 0;
}

// Raises the accuracy stat to the point that they will never be able 
// to miss. 
void
PokemonStadium::Stats::cannotMiss() {
   m_accuracy = NEVER_MISS;
}