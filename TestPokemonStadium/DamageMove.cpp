/*
* Pokemon Project
*
* DamageMove.cpp
* A battle move that damages the opponent
*/

#include "DamageMove.h"

PokemonStadium::DamageMove::DamageMove() : BattleMove() {
   this->selfDamageBaseOnDamage = false;
   this->selfDamage = 0;
   // set extra effect to empty
   this->otherEffect = NULL;
   // set Weather to blank
   this->changeAccuracyWeather = {};
   this->changeAccuracyToValues = {};
}

// Constructor for Damage Move with no extras: prority can be change
// self damage defaults to 0
// set name, type, category, pp, power, accuracy, description and priority with battle move
PokemonStadium::DamageMove::DamageMove(ConsoleOutput *out,
   string name, Type type, string category, int pp, 
   int power, int accuracy, string description, int priority) :
   BattleMove(out, name, type, category, pp, power, accuracy, description, priority) {
   this->selfDamageBaseOnDamage = false;
   this->selfDamage = 0;
   // set extra effect to empty
   this->otherEffect = NULL;
   // set Weather to blank
   this->changeAccuracyWeather = {};
   this->changeAccuracyToValues = {};
}
// Constructor for Damage Move with selfDamage
// set name, type, category, pp, power, accuracy, description and priority with battle move
PokemonStadium::DamageMove::DamageMove(ConsoleOutput *out,
   string name, Type type, string category, int pp, int power, 
   int accuracy, string description,
   bool selfDamageBaseOnDamage, double selfDamagePercent) : 
   BattleMove(out, name, type, category, pp, power, accuracy, description) {
   this->selfDamageBaseOnDamage = selfDamageBaseOnDamage;
   this->selfDamage = selfDamagePercent;
   // set extra effect to empty
   this->otherEffect = NULL;
   // set Weather to blank
   this->changeAccuracyWeather = {};
   this->changeAccuracyToValues = {};
}

// Constructor for Damage Move with extra battle move effects.
// self damage defaults to 0
// set name, type, category, pp, power, accuracy, description and priority with battle move
PokemonStadium::DamageMove::DamageMove(ConsoleOutput *out,
   string name, Type type, string category, int pp,
   int power, int accuracy, string description,
   BattleMoveEffects *otherEffect) : 
   BattleMove(out, name, type, category, pp, power, accuracy, description) {
   this->selfDamageBaseOnDamage = false;
   this->selfDamage = 0;
   // sets the other effect to given effect
   setOtherEffect(otherEffect);
   // set Weather info to empty
   this->changeAccuracyWeather = {};
   this->changeAccuracyToValues = {};
}

// Constructor for Damage Move with Weather accuracy changes and no extra battle move effects.
// self damage defaults to 0
// name, type, pp, description, and accuracy with battle move
// Weather changeAccuracyWeather and changeAccuracyToValues vectors must be the same size 
PokemonStadium::DamageMove::DamageMove(ConsoleOutput *out,
   string name, Type type, string category, int pp,
   int power, int accuracy, string description,
   vector<Weather> changeAccuracyWeather, vector<double> changeAccuracyToValues) : 
   BattleMove(out, name, type, category, pp, power, accuracy, description) {
   
   if (changeAccuracyWeather.size() == changeAccuracyToValues.size()) {
      this->selfDamageBaseOnDamage = false;
      this->selfDamage = 0;
      this->changeAccuracyWeather = changeAccuracyWeather;
      this->changeAccuracyToValues = changeAccuracyToValues;
      // set other effects to empty
      this->otherEffect = NULL;
   }
   // if vectors are not the same size throw an error
   else {
      cerr << "vectors are not the same size\n" <<
         "changeAccuracyWeather size = " << changeAccuracyWeather.size() << "\n" <<
         "changeAccuracyToValues size = " << changeAccuracyToValues.size() << "\n";
      exit(EXIT_FAILURE);
   }
}

// Constructor for Damage Move with extra battle effects and Weather accuracy increases.
// self damage defaults to 0
// name, type, pp, description, and accuracy with battle move
// Weather changeAccuracyWeather and changeAccuracyToValues vectors must be the same size 
PokemonStadium::DamageMove::DamageMove(ConsoleOutput *out, 
   string name, Type type, string category, int pp,
   int power, int accuracy, string description,
   BattleMoveEffects *otherEffect,
   vector<Weather> changeAccuracyWeather, vector<double> changeAccuracyToValues) : 
   BattleMove(out, name, type, category, pp, power, accuracy, description) {
   
   if (changeAccuracyWeather.size() == changeAccuracyToValues.size()) {
      this->selfDamageBaseOnDamage = false;
      this->selfDamage = 0;
      // sets the other effect to given effect
      setOtherEffect(otherEffect);
      this->changeAccuracyWeather = changeAccuracyWeather;
      this->changeAccuracyToValues = changeAccuracyToValues;
   }
   // if vectors are not the same size throw an error
   else {
      cerr << "vectors are not the same size\n" <<
         "changeAccuracyWeather size = " << changeAccuracyWeather.size() << "\n" <<
         "changeAccuracyToValues size = " << changeAccuracyToValues.size() << "\n";
      exit(EXIT_FAILURE);
   }
}

// Constructor that takes in a pointer to another DamageMove and
// set this DamageMove to other
PokemonStadium::DamageMove::DamageMove(PokemonStadium::DamageMove *other) :
   BattleMove(other->out, other->getName(), other->getType(), other->getCategory(),
      other->getTotalPP(), other->getPower(), other->getAccuracy(), 
      other->getDescription(), other->getPriority()){
   this->selfDamageBaseOnDamage = other->selfDamageBaseOnDamage;
   this->selfDamage = other->selfDamage;
   setOtherEffect(other->otherEffect);
   this->changeAccuracyWeather = other->changeAccuracyWeather;
   this->changeAccuracyToValues = other->changeAccuracyToValues;
}

// destructor delete the other effect if there is one
PokemonStadium::DamageMove::~DamageMove() {
   if (otherEffect != NULL)
      delete otherEffect;
}

// Set other effect
// creates new battle effect of the same type BattleMoveEffects
void PokemonStadium::DamageMove::setOtherEffect(BattleMoveEffects *otherEffect) {
   if (otherEffect == NULL){
      this->otherEffect = NULL;
   }
   else if (StatChangingEffect *statEffect =
      dynamic_cast<StatChangingEffect *>(otherEffect)) {
      this->otherEffect = new StatChangingEffect(statEffect);
   }
   else if (StatusConditionEffect *statusEFfect =
      dynamic_cast<StatusConditionEffect *>(otherEffect)) {
      this->otherEffect = new StatusConditionEffect(statusEFfect);
   }
   else {
      cerr << "Other Effect is not a proper type of BattleMoveEffect\n";
      exit(EXIT_FAILURE);
   }
}

// Gets other effect
PokemonStadium::BattleMoveEffects*
PokemonStadium::DamageMove::getOtherEffect() const {
   return otherEffect;
}

// Gets the Weather the move accuracy increases
vector<PokemonStadium::Weather>
PokemonStadium::DamageMove::getChangeAccuracyWeather() const {
   return changeAccuracyWeather;
}

// Gets the accuaray to change if changeAccuracyWeather
vector<double> 
PokemonStadium::DamageMove::getChangeAccuracyTo() const {
   return changeAccuracyToValues;
}

// Gets the self damage power of the move
double 
PokemonStadium::DamageMove::getSelfDamage() const {
   return selfDamage;
}

// change the pure damage by the battleMoveEffecitveNess, weatherPowerMultipler and typeMultiplier
int
PokemonStadium::DamageMove::totalDamageCalculations(int pureDamage,
   double battleMoveEffecitveNess, double weatherPowerMultipler, double typeMultiplier) const {
   double extras = battleMoveEffecitveNess * weatherPowerMultipler * typeMultiplier;
   // return calulations
   return (int)(pureDamage * extras);
}

// check if the move has a accuracy weather changer
  // if there is a weather, check if it matches the move accuracy weather change
  // and apply changes to weatherAccuracyMultipler if so
bool
PokemonStadium::DamageMove::attemptAttack(Weather battleWeather, Stats *userPokemonStats, Stats *oppPokemonStats) {
   Type moveType = getType();
   double weatherPowerMultipler = 1;
   double weatherAccuracyMultipler = 1;
   // check if move has a change accuracy weather
   if (!changeAccuracyWeather.empty()) {
      // checks if there is a weather on the field
      if (!battleWeather.noWeather()){
         // loop through each of the changeAccuracyWeather and see
         // if name matches the current Weather change the Weather Accuracy Multipler
         for (size_t i = 0; i < changeAccuracyWeather.size(); i++) {
            if (changeAccuracyWeather[i] == battleWeather) {
               weatherAccuracyMultipler *= changeAccuracyToValues[i];
               break;
            }
         }
      }
   }

   // calulates if the moves hit
   if (hit(userPokemonStats->getModifiedStatValue("accuracy"), 
      oppPokemonStats->getModifiedStatValue("evasion"), weatherAccuracyMultipler)) {
      return true;
   }
   // if it did not print that the attack missed
   else {
      return false;
   }
}

// caluclates the total damage base on weather, user and opponents status and the effectiveNess the move type
// has on the pokemon
int
PokemonStadium::DamageMove::calculateDamages(Weather *battleWeather, 
   Stats *userPokemonStats, Stats *oppPokemonStats,
   double battleMoveEffectiveNess, double typeMultipler) {
   // if there is a change power Weather check if the damage move type 
// gets affect by Weather and change the WeatherPowerMultipler if it does
   double weatherPowerMultipler = battleWeather->typeStatMultiplier(getType());

   int attackingStat;
   int defendingStat;
   // if damage move type is physical, use the user Pokemon Attack Stat
   // and the opponents Pokemon Defense Stat
   if (getCategory() == CATEGORY_PHSYICAL) {
      attackingStat = userPokemonStats->getAttack();
      defendingStat = oppPokemonStats->getDefense();
   }
   // if damage move type is special, use the user Pokemon Special Attack Stat
   // and the opponents Pokemon Special Defense Stat
   else if (getCategory() == CATEGORY_SPECIAL) {
      attackingStat = userPokemonStats->getSpecialAttack();
      defendingStat = oppPokemonStats->getSpecialDefense();
   }
   // Damage Move should only be physical or special
   else {
      cerr << "category can only be physical or special";
      exit(EXIT_FAILURE);;
   }

   // calculate damages pure damage base on the power, attackingStat, and defendingStat
   // then times that by battleMoveEffectiveNess, weatherPowerMultipler and typeMultipler
   int damage = totalDamageCalculations(calculatePureDamage(getPower(), (double)attackingStat, (double)defendingStat),
      battleMoveEffectiveNess, weatherPowerMultipler, typeMultipler);
   oppPokemonStats->damageToHealth(damage);
   return damage;
}

// Pokemon attacks the other opponent's Pokemon
// check if it had effect and if it hit and if so
// calcutates damage and applies damages to other pokemon
// and returns true otherwise it returns false.
// if there is self damage, the percent of the damage done
// is applied to the attacking Pokemon
bool 
PokemonStadium::DamageMove::attack(Weather *battleWeather,
   Stats *userPokemonStats, StatusCondition *userStatusCondition, Type userPrimaryType, Type userSecondaryType,
   Stats *oppPokemonStats, StatusCondition *oppStatusCondition, Type oppPrimaryType, Type oppSecondaryType) {
   logBattleMove();
   double battleMoveEffectiveNess = getType().attackEffectiveNess(oppPrimaryType, oppSecondaryType);
   if (battleMoveEffectiveNess == 0) {
      out->log("It had no effect");
      return false;
   }
   // checks if the move landed or missed
   else if (!attemptAttack(*battleWeather, userPokemonStats, oppPokemonStats)) {
      out->log("It missed");
      return false;
   }

   else {
      double typeMultipler;
      // if the move type is the same as either the primary or secondary type increase damage
      if (getType() == userPrimaryType || getType() == userSecondaryType) {
         typeMultipler = TYPE_INC_DAMAGE;
      }
      // else no increase damage
      else {
         typeMultipler = 1;
      }
      int damageDone = calculateDamages(battleWeather, userPokemonStats, oppPokemonStats, battleMoveEffectiveNess, typeMultipler);
      // print if the move is super or not very effective
      if (battleMoveEffectiveNess >= SUPER_EFFECTIVE)
         out->log("Its super effective!");
      else if (battleMoveEffectiveNess <= NOT_VERY_EFFECTIVE)
         out->log("its not very effective.");

      // if the attack cause self damage, apply to pokemon now
      if (selfDamage > 0) {
         // recoild damage = the given selfDamage times the damage the target recieved
         int recoilDamage = (int) (selfDamage * damageDone);
         userPokemonStats->damageToHealth(recoilDamage);
      }
      return true;
   }
}

// Minus the pp, attacks the pokemons and applies damage if has effect
// and attack landed. If Pokemon
void
PokemonStadium::DamageMove::useDamageMove(Weather *battleWeather,
   Stats *userPokemonStats, StatusCondition *userStatusCondition, Type userPrimaryType, Type userSecondaryType,
   Stats *oppPokemonStats, StatusCondition *oppStatusCondition, Type oppPrimaryType, Type oppSecondaryType) {
   currentPP--;
   bool didDamage = attack(battleWeather,
      userPokemonStats, userStatusCondition, userPrimaryType, userSecondaryType,
      oppPokemonStats, oppStatusCondition, oppPrimaryType, oppSecondaryType);

   // if battle move has another effect, check and see if the affect is active
  // and if is apply it
   if (otherEffect != NULL && didDamage) {
      otherEffect->applyEffect(userPokemonStats,
         oppPokemonStats, oppStatusCondition,
         oppPrimaryType, oppSecondaryType);
   }
}

// prints the Damage move name, type, power, accuracy, pp, category and description
void
PokemonStadium::DamageMove::display() const {
   string accuracyDisplay;
   if (getAccuracy() == NEVER_MISS) {
      accuracyDisplay = "--";
   }
   else {
      accuracyDisplay = getAccuracy();
   }
   //out->display(getName() + "\n" +
   //   "Type: " + getType().getName() + " Power: " + power + " Accuracy: " + getAccuracy() + accuracyDisplay + "%" +
   //   " PP: " + totalPP + " Category:" + getCategory() + "\n" << getDescription());
}
