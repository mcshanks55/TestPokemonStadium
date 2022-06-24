/*
* Pokemon Project
*
* ConsoleOutput.h
* Takes in the statments to be print out to the console
*
*/
#ifndef POKEMONSTADIUM_CONSOLEOUTPUT_H
#define POKEMONSTADIUM_CONSOLEOUTPUT_H

#include "ostream"
using std::ostream;
#include "string"
using std::string;

namespace PokemonStadium
{
   class ConsoleOutput {
   public:
      // Constructor
      ConsoleOutput(ostream &o);
      ConsoleOutput(ostream &o, string user, string opp);
      void setUser(string name);
      void setOpp(string name);
      void log(string statements);
      void userLog(string statements);
      void oppLog(string statements);
      void display(string display);

   private:
      ostream &out;
      string user;
      string opp;

   };
}
#endif
