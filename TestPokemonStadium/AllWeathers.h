/* All of the Weather:
*   Clear Skies, Hailing, Harsh Sun, Raining, Sandstorm
*/

#include "ChangePowerWeather.h"
#include "DamageWeather.h"
#include "AllTypes.h"

static PokemonStadium::Weather clear_skies = PokemonStadium::Weather();

static PokemonStadium::DamageWeather hail = PokemonStadium::DamageWeather("hail", 
   "It started to hail!", "Hail continues to fall.", "The hail stopped.", 
   {type_ice});

static PokemonStadium::ChangePowerWeather harsh_sun = PokemonStadium::ChangePowerWeather("harsh sun", 
   "The sunlight turned harsh!", "The sunlight is strong.", "The harsh sunlight faded.",
   {type_fire}, {type_water});

static PokemonStadium::ChangePowerWeather rain = PokemonStadium::ChangePowerWeather("rain", 
   "It started to rain!", "Rain continues to fall.", "The rain stopped.",
   {type_water}, {type_fire});

static PokemonStadium::DamageWeather sandstorm = PokemonStadium::DamageWeather("sandstorm", 
   "A sandstorm kicked up!", "The sandstorm rages.", "The sandstorm subsided.",
   {type_ground, type_rock, type_steel});
