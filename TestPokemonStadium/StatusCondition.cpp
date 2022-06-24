/*
* Pokemon
*
* StatusCondition.cpp
* The status condition of the Pokemon during battle
* All of the Status Condition: asleep, burned, frozen,
*                              paralyzed, poison, badly poison, confused
*/
#include "StatusCondition.h"

// empty constructor
PokemonStadium::StatusCondition::StatusCondition() {
   this->out = NULL;
   this->condition = "";
   sleepTurns = 0;
   badlyPoison = false;
   incPoisonDamage = 0;
   confusion = false;

}

// sets console output and Pokemon status condition (default is empty), sleep counter to 0
PokemonStadium::StatusCondition::StatusCondition(ConsoleOutput *out, string condition) {
   this->out = out;
   this->condition = condition;
   sleepTurns = 0;
   badlyPoison = false;
   incPoisonDamage = 0;
   confusion = false;
   // create the random see for rand
   srand((unsigned)time(NULL));
}

// Gets the condition of the Status Condition
string
PokemonStadium::StatusCondition::getCondition() const {
   return condition;
}

// Sets the condition and set counters or stat lower if applied
void
PokemonStadium::StatusCondition::setCondition(string condition, Stats *pokemonsStats) {
   if (*find(allConditions.begin(), allConditions.end(), condition) == condition) {
      // if condition is badly poison, set badlyPoison and condition to poison
      if (condition == "badly poison") {
         badlyPoison = true;
         condition = "poison";
      }
      // if burn, lower attack by BURN_ATTACK_REDUCTION
      else if (condition == "burned") {
         pokemonsStats->addStatusConditionModifier("attack", BURN_ATTACK_REDUCTION);
      }
      // if paralyze, lower speed by PARALYZE_SPEED_REDUCTION
      else if (condition == "paralyzed") {
         pokemonsStats->addStatusConditionModifier("speed", PARALYZE_SPEED_REDUCTION);
      }
      
      // if sleep, sets how many turns the pokemon will be asleep for
      else if (condition == "asleep") {
         sleepTurns = 1 + (rand() % SLEEP_TURNS);
      }

      this->condition = condition;
      out->userLog( + "is " + condition);
   }
   else {
      cerr << condition << " is not a condition";
   }
}

// returns if its confused or not
bool
PokemonStadium::StatusCondition::isConfused() const {
   return confusion;
}

// sets confused to true
void 
PokemonStadium::StatusCondition::setConfusion() {
   confusionTurns = 1 + (rand() % CONFUSION_TURNS);
   confusion = true;
}
// Asleep effects:
// Pokemon is not allow to attack. Can get out of
// sleep by waking up
bool 
PokemonStadium::StatusCondition::asleep() {
   // if sleepTurns has drop down to, remove sleep
   if (sleepTurns == 0) {
      condition = "";
      out->userLog("woke up");
      return false;
   }
   // else pokemon is stil fast asleep and unable to attack
   else {
      sleepTurns--;
      out->userLog("is fast asleep");
      return true;
   }
}

// Get how many turns Pokemon will be alseep for
// (only used for testing)
int 
PokemonStadium::StatusCondition::getSleepTurns() {
   return sleepTurns;
}

// Confused effects:
// Pokemon has a CONFUSED percent chance of not attacking and
// damage the itself
bool
PokemonStadium::StatusCondition::confused(Stats *pokemonStats) {
   // check if Pokemon is still confused
   if (confusionTurns > 0) {
      out->userLog("is confused");
      confusionTurns--;
      // create a random number out of 100
      int random = rand() % 100;
      if (random <= CONFUSION_CHANCE) {
         // the user pokemon recieve the amount of damage of a power 40 physical attack
         int damage = calculatePureDamage(CONFUSION_POWER,
            pokemonStats->getAttack(),
            pokemonStats->getDefense());
         pokemonStats->damageToHealth(damage);
         out->userLog("It hurt itself in its confusion");
         return true;
      }
      else {
         return false;
      }
   }
   // if confusion turns are up cure confusion and allow attack
   else {
      cureConfusion();
      out->userLog("snapped out of confusion");
      return false;
   }
}

// Cures the pokemon of their status condition
void 
PokemonStadium::StatusCondition::cured(Stats *pokemonsStats) {
   condition = "";
   sleepTurns = 0;
   incPoisonDamage = 0;
   pokemonsStats->clearStatusConditionModifier();
}

// Remove the pokemon confusion
void
PokemonStadium::StatusCondition::cureConfusion() {
   confusion = false;
}


// Burned effects:
// Pokemon recieves damage by BURN_DAMAGE amount
void
PokemonStadium::StatusCondition::burned(Stats *pokemonStats) {
   pokemonStats->damagePercentToHealth(BURN_DAMAGE);
   out->userLog("is hurt by burn!");
}

// Frozen effects:
// Pokemon is not allow to attack. Can get out of
// frozen once the pokemon dethaws
bool 
PokemonStadium::StatusCondition::frozen() {
   // create a random number out of 100
   int random = rand() % 100;
   // Pokemon has a DETHAW_CHANCE percent chance that it will dethaw
   // and remove condition
   if (random > DETHAW_CHANCE) {
      condition = "";
      out->userLog("thawed out");
      return false;
   }
   // else pokemon is stil frozen and unable to attack
   else {
      out->userLog("is frozen solid");
      return true;
   }
}

// Paralyze effects:
// Pokemon has a percentage chance of being able to attack.
bool
PokemonStadium::StatusCondition::paralyzed() {
   // create a random number out of 100
   int random = rand() % 100;
   // Pokemon has a PARALYZE_CANT_MOVE percent chance that it will can attack
   if (random > PARALYZE_CANT_MOVE) {
      return false;
   }
   // else pokemon is paralyze and cannot attack
   else {
      out->userLog("is paralyzed and cannot move!");
      return true;
   }
}

// Poison effects:
// Pokemon recieves damage by POISON_DAMAGE amount plus
// increase damage if badly poison
void
PokemonStadium::StatusCondition::poison(Stats *pokemonStats) {
   double total_damage = POISON_DAMAGE;
   // if badly damage increase damage by BADLY_POISON_DAMAGE_INC * incPoisonDamage
   if (badlyPoison) {
      total_damage += BADLY_POISON_DAMAGE_INC * incPoisonDamage;
      incPoisonDamage++;
   }
   pokemonStats->damagePercentToHealth(total_damage);
   out->userLog("hurt by poison!");
}

// returns true if the affects are applied and user is unable to attack
// defaults to false
bool 
PokemonStadium::StatusCondition::applyPreAffects(Stats *pokemonStats) {
   
   bool cannotAttack = false;
   // if asleep check if the pokemon has woke up yet or not
   if (condition == "asleep")
      cannotAttack = asleep();
   // if frozen check if the pokemon has thawed out yet or not
   else if (condition == "frozen")
      cannotAttack = frozen();
   // if paralyzed check if pokemon is too paralyze to attack
   else if (condition == "paralyzed")
      cannotAttack = paralyzed();

   // if pokemon is confused and hasn't been block by another
   // conditoin, check if pokemon is does damage to itself
   if (isConfused() && !cannotAttack)
      cannotAttack = confused(pokemonStats);

   return cannotAttack;
}

// applies damamges to the Pokemon depending on condition
void
PokemonStadium::StatusCondition::applyPostAffect(Stats *pokemonStats) {
   if (condition == "burned") {
      burned(pokemonStats);
   }

   else if (condition == "poison")
      poison(pokemonStats);
}

bool
PokemonStadium::StatusCondition::statusConditionCanBeChanged(string conditionToCause,
   Type POKEMONSTADIUM_primary_type, Type POKEMONSTADIUM_secondary_type) {
   // if Pokemon has a type matching the moveType it has no effect
   if (conditionToCause == "confused") {
      // pokemon cannot be confused if its already confused
      if (isConfused()) {
         out->userLog("is already confused"); // needs to not be printed every check
         return false;
      }
      else {
         return true;
      }
   }
   else {
      // status condition cannot be changed if it already has a status condition
      if (condition != "") {
         out->userLog("is already " + condition); // needs to not be printed every check
         return false;
      }
      else {
         // check if pokemon type prevents them from getting the condiiton
         // Fire types cannot be burned
         if ((POKEMONSTADIUM_primary_type.getName() == IMMUNE_TO_BURN ||
              POKEMONSTADIUM_secondary_type.getName() == IMMUNE_TO_BURN) &&
              conditionToCause == "burned") {
            return false;
         }
         // Ice types cannot be frozen
         else if ((POKEMONSTADIUM_primary_type.getName() == IMMUNE_TO_FREEZING ||
            POKEMONSTADIUM_secondary_type.getName() == IMMUNE_TO_FREEZING) &&
            conditionToCause == "frozen") {
            return false;
         }
         // Electric types cannot be paralyed
         else if ((POKEMONSTADIUM_primary_type.getName() == IMMUNE_TO_PARALYZE ||
            POKEMONSTADIUM_secondary_type.getName() == IMMUNE_TO_PARALYZE) &&
            conditionToCause == "paralyzed") {
            return false;
         }
         // Poison types cannot be poison
         else if (((POKEMONSTADIUM_primary_type.getName() == IMMUNE_TO_POISON_1 ||
            POKEMONSTADIUM_secondary_type.getName() == IMMUNE_TO_POISON_1) ||
            POKEMONSTADIUM_primary_type.getName() == IMMUNE_TO_POISON_2 ||
            POKEMONSTADIUM_secondary_type.getName() == IMMUNE_TO_POISON_2) &&
            conditionToCause == "poison") {
            return false;
         }
         // else the status condition can be set
         else {
            return true;
         }
      }
   }
}
