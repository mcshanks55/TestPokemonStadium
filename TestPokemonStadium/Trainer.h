/*
* Pokemon Project
*
* Trainer.h
* Class of the Pokemon Trainer. Each trainer has a name and 6 Pokemon,
* Trainer will be in either a one-on-one or two-on-two Pokemon battle
* where the trainer can have one or two poekmon out
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
      PokemonCharacter *getPokemonAInBattle();
      PokemonCharacter *getPokemonBInBattle();
      int getSlotAMovePriority();
      int getSlotBMovePriority();
      void setSlotAMovePriority(int priority);
      void setSlotBMovePriority(int priority);
      void setBattleParty(vector<int> battleParty);
      void resetSwitchingPokemon();
      bool pickPokemonToSwitch(size_t battlePartySpot);
      void switchPokemon(size_t battlePartySpot);
      void switchPokemonInSlotA(size_t battlePartySpot);
      void switchPokemonInSlotB(size_t battlePartySpot);
      bool hasPokemonOutHasFainted();
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
      size_t pokemonInBattleSlotA;
      size_t pokemonInBattleSlotB;
      int slotAMovePriority;
      int slotBMovePriority;
      bool pokemonIsHidden;
      bool switchingPokemonOut;
      vector<size_t> switchingPokemon;
   };
}
#endif
