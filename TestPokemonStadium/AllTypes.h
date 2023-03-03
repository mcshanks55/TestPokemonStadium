/* All of the types:
*   Bug, Dark, Dragon, Electric, Fairy, Fighting,
*   Fire, Flying, Ghost, Grass, Ground, Ice, Mage
*   Normal, Poison, Psychic, Rock, Steel, Water
*/

#include "Type.h"

// None
static const PokemonStadium::Type type_none = PokemonStadium::Type();
// Bug
static const PokemonStadium::Type type_bug = PokemonStadium::Type(
   "Bug",
   {"Dark","Grass","Psychic"}, // offensive super effective
   {"Fairy","Fighting","Fire","Flying","Ghost","Poison","Steel"}, // offensive not very effective
   {}, // offensive no effect
   {"Fire","Flying","Rock"}, // defensive super effective
   {"Fighting","Grass","Ground"}, // defensive not very effective 
   {} // defensive no effect
);

// Dark
static const PokemonStadium::Type type_dark = PokemonStadium::Type(
   "Dark",
   {"Ghost","Psychic"}, // offensive super effective
   {"Dark","Fairy","Fighting"}, // offensive not very effective
   {}, // offensive no effect
   {"Bug","Fairy","Fighting"}, // defensive super effective
   {"Dark","Ghost"}, // defensive not very effective 
   {"Psychic"} // defensive no effect
);

// Dragon
static const PokemonStadium::Type type_dragon = PokemonStadium::Type(
   "Dragon",
   {"Dragon"}, // offensive super effective
   {"Steel"}, // offensive not very effective
   {"Fairy"}, // offensive no effect
   {"Dragon","Fairy","Ice"}, // defensive super effective
   {"Electric","Fire","Grass","Water"}, // defensive not very effective 
   {} // defensive no effect
);

// Electric
static const PokemonStadium::Type type_electric = PokemonStadium::Type(
   "Electric",
   {"Flying","Water"}, // offensive super effective
   {"Dragon","Electric","Grass"}, // offensive not very effective
   {"Ground"}, // offensive no effect
   {"Ground"}, // defensive super effective
   {"Electric","Flying","Steel"}, // defensive not very effective 
   {} // defensive no effect
);

// Fairy
static const PokemonStadium::Type type_fairy = PokemonStadium::Type(
   "Fairy",
   {"Dark","Dragon","Fighting"}, // offensive super effective
   {"Fire","Poison","Steel"}, // offensive not very effective
   {}, // offensive no effect
   {"Poison","Steel"}, // defensive super effective
   {"Bug","Dark","Fighting"}, // defensive not very effective 
   {"Dragon"} // defensive no effect
);

// Fighting
static const PokemonStadium::Type type_fighting = PokemonStadium::Type(
   "Fighting",
   {"Dark","Ice","Normal","Rock","Steel"}, // offensive super effective
   {"Bug","Fairy","Flying","Poison","Psychic"}, // offensive not very effective
   {"Ghost"}, // offensive no effect
   {"Fairy","Flying","Psychic"}, // defensive super effective
   {"Bug","Fairy","Fire","Grass", "Ice", "Steel"}, // defensive not very effective 
   {} // defensive no effect
);

// Fire
static const PokemonStadium::Type type_fire = PokemonStadium::Type(
   "Fire",
   {"Bug","Grass","Ice","Steel"}, // offensive super effective
   {"Dragon","Fire","Rock","Water"}, // offensive not very effective
   {}, // offensive no effect
   {"Ground","Rock","Water"}, // defensive super effective
   {"Bug","Fairy","Fire","Grass", "Ice", "Steel"}, // defensive not very effective 
   {} // defensive no effect
);

// Flying
static const PokemonStadium::Type type_flying = PokemonStadium::Type(
   "Flying",
   {"Bug","Fighting","Grass"}, // offensive super effective
   {"Electric","Rock","Steel"}, // offensive not very effective
   {}, // offensive no effect
   {"Electric","Ice","Rock"}, // defensive super effective
   {"Bug","Fighting","Grass"}, // defensive not very effective 
   {"Ground"} // defensive no effect
);

// Ghost
static const PokemonStadium::Type type_ghost = PokemonStadium::Type(
   "Ghost",
   {"Ghost","Psychic"}, // offensive super effective
   {"Dark"}, // offensive not very effective
   {"Normal"}, // offensive no effect
   {"Dark","Ghost"}, // defensive super effective
   {"Bug","Poison"}, // defensive not very effective 
   {"Normal","Fighting"} // defensive no effect
);

// Grass
static const PokemonStadium::Type type_grass = PokemonStadium::Type(
   "Grass",
   {"Ground","Rock","Water"}, // offensive super effective
   {"Bug","Dragon","Fire","Flying","Grass","Poison","Steel"}, // offensive not very effective
   {}, // offensive no effect
   {"Bug","Fire","Flying","Ice","Poison"}, // defensive super effective
   {"Electric","Grass","Ground","Water"}, // defensive not very effective 
   {} // defensive no effect
);

// Ground
static const PokemonStadium::Type type_ground = PokemonStadium::Type(
   "Ground",
   {"Electric","Fire","Poison","Rock","Steel"}, // offensive super effective
   {"Bug","Grass"}, // offensive not very effective
   {"Flying"}, // offensive no effect
   {"Grass","Ice","Water"}, // defensive super effective
   {"Poison","Rock"}, // defensive not very effective 
   {"Electric"} // defensive no effect
);

// Ice
static const PokemonStadium::Type type_ice = PokemonStadium::Type(
   "Ice",
   {"Dragon","Flying","Grass","Ground"}, // offensive super effective
   {"Fire","Ice","Steel","Water"}, // offensive not very effective
   {}, // offensive no effect
   {"Fighting","Fire","Rock","Steel"}, // defensive super effective
   {"Ice"}, // defensive not very effective 
   {} // defensive no effect
);

// Normal
static const PokemonStadium::Type type_normal = PokemonStadium::Type(
   "Normal",
   {}, // offensive super effective
   {"Rock","Steel"}, // offensive not very effective
   {"Ghost"}, // offensive no effect
   {"Fighting"}, // defensive super effective
   {}, // defensive not very effective 
   {"Ghost"} // defensive no effect
);

// Poison
static const PokemonStadium::Type type_poison = PokemonStadium::Type(
   "Poison",
   {"Fairy","Grass"}, // offensive super effective
   {"Poison","Ground","Rock","Ghost"}, // offensive not very effective
   {"Steel"}, // offensive no effect
   {"Ground","Psychic"}, // defensive super effective
   {"Fighting","Poison","Bug","Grass","Fairy"}, // defensive not very effective 
   {} // defensive no effect
);

// Psychic
static const PokemonStadium::Type type_psychic = PokemonStadium::Type(
   "Psychic",
   {"Fighting","Poison"}, // offensive super effective
   {"Psychic","Steel"}, // offensive not very effective
   {"Dark"}, // offensive no effect
   {"Bug","Dark","Ghost"}, // defensive super effective
   {"Fighting","Psychic"}, // defensive not very effective 
   {} // defensive no effect
);

// Rock
static const PokemonStadium::Type type_rock = PokemonStadium::Type(
   "Rock",
   {"Bug","Fire","Flying","Ice"}, // offensive super effective
   {"Fighting","Ground","Steel"}, // offensive not very effective
   {}, // offensive no effect
   {"Fighting","Grass","Ground","Steel","Water"}, // defensive super effective
   {"Fire","Flying","Normal","Poison"}, // defensive not very effective 
   {} // defensive no effect
);

// Steel
static const PokemonStadium::Type type_steel = PokemonStadium::Type(
   "Steel",
   {"Fairy","Ice","Rock"}, // offensive super effective
   {"Electic","Fire","Steel","Water"}, // offensive not very effective
   {}, // offensive no effect
   {"Fighting","Fire","Ground"}, // defensive super effective
   {"Bug","Dragon","Fairy","Flying","Grass","Ice","Normal","Psychic","Rock","Steel"}, // defensive not very effective 
   {"Poison"} // defensive no effect
);

// Water
static const PokemonStadium::Type type_water = PokemonStadium::Type(
   "Water",
   {"Fire","Ground","Rock"}, // offensive super effective
   {"Dragon","Grass","Water"}, // offensive not very effective
   {}, // offensive no effect
   {"Electric","Grass",}, // defensive super effective
   {"Fire","Ice","Steel","Water", "Ice"}, // defensive not very effective 
   {} // defensive no effect
);

// Mage
static const PokemonStadium::Type type_mage = PokemonStadium::Type(
   "Mage",
   {"Fairy", "Fighting", "Ghost"}, // offensive super effective
   {"Mage"}, // offensive not very effective
   {"Dragon"}, // offensive no effect
   {"Dark", "Dragon"}, // defensive super effective
   {"Ghost", "Mage"}, // defensive not very effective 
   {"Fairy"} // defensive no effect
);

//static const vector<PokemonStadium::Type> listAllTypes = {type_bug, type_dark, type_dragon,
//                                         type_electric, type_fairy, type_fighting,
//                                         type_fire, type_flying, type_ghost, type_grass,
//                                         type_ground, type_ice, type_normal, type_poison,
//                                         type_psychic, type_rock, type_steel, type_water};

