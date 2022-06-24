/*
* Pokemon Project
* main.cpp
*/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "UnitTest.h"

int main()
{

   // Initialize
   PokemonStadium::Initialize(cout);

   // Run tests
   PokemonStadium::DisplaySummary();
   PokemonStadium::TestAllTypes();
   PokemonStadium::TestStats();
   PokemonStadium::TestWeather();
   PokemonStadium::TestStatusCondition();
   PokemonStadium::TestDamageMove();
   PokemonStadium::TestChargeMove();
   PokemonStadium::TestHiddenMove();
   PokemonStadium::TestRechargeMove();
   PokemonStadium::TestHealingMove();
   PokemonStadium::TestStatsChangingMove();
   PokemonStadium::TestStatusConditionMove();
   PokemonStadium::TestWeatherChangingMove();
   PokemonStadium::TestPokemonCharacter();
   PokemonStadium::TestTrainer();

   // Display test results
   PokemonStadium::DisplaySummary();

   // Wait for user response
   cout << endl << "Press enter to continue...";
   cin.get();
}
