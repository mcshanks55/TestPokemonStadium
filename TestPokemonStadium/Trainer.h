/*
* Pokemon Project
*
* Trainer.h
* Class of the Pokemon Trainer. Each trainer has a name and 6 Pokemon
*
*/
#ifndef POKEMONSTADIUM_TRAINER_H
#define POKEMONSTADIUM_TRAINER_H

#include "PokemonCharacter.h"
#include <deque>
#include <algorithm>
#include <vector>
using std::cin;

namespace PokemonStadium
{
   static const int TOTAL_NUM_POKEMON = 6;
   class PokemonCharacter;

   class Trainer {

   public:
      // Constructor
      Trainer(ConsoleOutput *out, string id, string trainerName);
      // Destructor
      ~Trainer();

      // memeber functions
      string getId() const;
      string getName() const;
      vector<PokemonCharacter*> getPokemonParty() const;
      void addPokemonToParty(PokemonCharacter *pokemon);
      void setPokemonParty(vector<PokemonCharacter *> pokemonParty);
      PokemonCharacter *getPokemonInBattle();
      //void setBattleParty(size_t battlePartySize = 1);
      void setBattleParty(vector<int> battleParty);
      bool pickPokemonToSwitch(size_t battlePartySpot);
      void switchPokemon(size_t battlePartySpot);
      bool pokemonOutHasFainted();
      bool isPokemonInSlotAbleToBattle(size_t slot);
      bool canBattleMoveBePicked(string selectMoveName);
      void usePokemonInBattleBattleMove(size_t selectedMove, Weather **battleWeather, 
         string oppTrainersName, string oppPokemonName,
         Stats *oppPokemonStats, StatusCondition *oppStatusCondition, Type oppPrimaryType, Type oppSecondaryType);
      //void makeDecision();

      void displayPokemonParty();
      void annoucePokemonEnteringBattle();

   private:
      ConsoleOutput *out;
      string id;
      string name;
      vector<PokemonCharacter*> pokemonParty;
      vector<PokemonCharacter*> battleParty;
      size_t pokemonSlotInBattle;
      bool pokemonIsHidden;

   };
}
#endif
