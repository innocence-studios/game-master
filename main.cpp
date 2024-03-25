
#include "data.h"
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>
#include <windows.h>

using namespace std;
using namespace chrono;
using namespace this_thread;

int main() {
    display("Hey. I am your Game Master. Let's define your character:\n");
    
    string _Name = input("What is your name?");

    display(_Name + "... Nice name.");

    bool validClass = false;
    string _Class = "";

    while (!validClass) {
        string __Class = firstUpper(toLowercase(input("What class are you?")));
        if (!vectorHasValue(Classes, __Class)) { display("That's not a class!"); }
        else { validClass = true; _Class = __Class; };
    };

    display("So you are a " + _Class + "...");

    display("By the way, ", false);

    bool validSpecies = false;
    string _Species = "";

    while (!validSpecies) {
        string __Species = firstUpper(input("What species are you?"));
        if (!vectorHasValue(AllSpecies, __Species)) { display("Is that really a species?"); }
        else { validSpecies = true; _Species = __Species; };
    };
    
    display("Right.\nOk so now, for your hit points...\nI dont want to bother you, so I will choose myself...\nLet's roll some dice:\n");

    int _Strength = rollDiceAndCalculateTotal("Strength");
    int _Dexterity = rollDiceAndCalculateTotal("Dexterity");
    int _Constitution = rollDiceAndCalculateTotal("Constitution");
    int _Intelligence = rollDiceAndCalculateTotal("Intelligence");
    int _Wisdom = rollDiceAndCalculateTotal("Wisdom");
    int _Charisma = rollDiceAndCalculateTotal("Charisma");

    int _StrengthModifier = floor((_Strength - 10) / 2);
    display("Your strength modifier is... " + to_string(_StrengthModifier) + "\n");
    int _DexterityModifier = floor((_Dexterity - 10) / 2);
    display("Your dexterity modifier is... " + to_string(_DexterityModifier) + "\n");
    int _ConstitutionModifier = floor((_Constitution - 10) / 2);
    display("Your constitution modifier is... " + to_string(_ConstitutionModifier) + "\n");
    int _IntelligenceModifier = floor((_Intelligence - 10) / 2);
    display("Your intelligence modifier is... " + to_string(_IntelligenceModifier) + "\n");
    int _WisdomModifier = floor((_Wisdom - 10) / 2);
    display("Your wisdom modifier is... " + to_string(_WisdomModifier) + "\n");
    int _CharismaModifier = floor((_Charisma - 10) / 2);
    display("Your charisma modifier is... " + to_string(_CharismaModifier) + "\n");
    

    string _Background = input("What is your background?");

    display("Right, right! So, for your starting equipment...");


};

