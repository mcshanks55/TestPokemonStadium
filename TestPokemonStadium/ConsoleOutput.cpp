/*
* Pokemon Project
*
* ConsoleOutput.h
* Takes in the statments to be print out to the console
*
*/
#include "ConsoleOutput.h"
#include "iostream"

// initialize out with given ostream 
PokemonStadium::ConsoleOutput::ConsoleOutput(ostream &o) : out(o) {
   user = "";
   opp = "";
}

// initialize out with given ostream and set the user Pokemon and opp Pokemon names
PokemonStadium::ConsoleOutput::ConsoleOutput(ostream &o, string user, string opp) : out(o) {
   this->user = user;
   this->opp = opp;
}

// set the user to the given Pokemon Name
void
PokemonStadium::ConsoleOutput::setUser(string name) {
   user = name;
}

// set the opp to the given Pokemon Name
void
PokemonStadium::ConsoleOutput::setOpp(string name) {
   opp = name;
}

// logs statements into the console
void
PokemonStadium::ConsoleOutput::log(string statements) {
   out << statements << "\n";
}

// log statments into the console with the user's (trainer) pokemon name
void
PokemonStadium::ConsoleOutput::userLog(string statements) {
   out << user << " " << statements << "\n";
}

// log statments into the console with the opp's (trainer) pokemon name
void
PokemonStadium::ConsoleOutput::oppLog(string statements) {
   out << opp << " " << statements << "\n";
}

// displays Pokemon Characteristics (battlemoves, stats) in console (might not be needed)
void
PokemonStadium::ConsoleOutput::display(string display) {
   out << display;
}
