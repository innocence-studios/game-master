
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

static int getRand(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(min, max);

    return dis(gen);
};

static void display(string str, bool hasEndl = true) {
    for (char c : str) {
        cout << c;

        switch (c) {
        case '.':
        case '?':
        case '!':
        case ':':
            sleep_for(milliseconds(getRand(250, 750)));
            break;
        case '\n':
            break;
        default:
            sleep_for(milliseconds(getRand(25, 75)));
            break;
        };

    };
    if (hasEndl) { cout << endl; };
};

static string input(string str) {
    display(str + "\n> ", false);
    string output;
    getline(cin, output);
    return output;
};

static int clamp(int value, int min, int max) {
    return (value < min) ? min : (value > max) ? max : value;
}

static int choice(vector<string> choices) {
    for (int i = 0; i < choices.size(); i++) {
        display("> " + choices[i]);
    };

    int i = 0;

    bool keyPressed = false;

    while (!(GetKeyState(VK_RETURN) & 0x8000)) {
        cout << "\r> Option " << i + 1 << "  (" << choices[i] << ")";
        if (GetKeyState(VK_UP) & 0x8000) {
            if (!keyPressed) i = clamp(i + 1, 0, choices.size() - 1);
            keyPressed = true;
        }
        else if (GetKeyState(VK_DOWN) & 0x8000) {
            if (!keyPressed) i = clamp(i - 1, 0, choices.size() - 1);
            keyPressed = true;
        }
        else {
            keyPressed = false;
        };
    };

    return i;
};

static bool vectorHasValue(vector<string> vec, string val) {
    return find(vec.begin(), vec.end(), val) != vec.end();
};

static vector<int> highestOfVector(vector<int> vec, int amount) {
    sort(vec.begin(), vec.end(), greater<int>());
    return vector<int>(vec.begin(), vec.begin() + amount);
}

static int vectorTotal(vector<int> vec) {
    int total = 0;
    for (int value : vec) { total += value; };
    return total;
};

static string toLowercase(const string& str) {
    string result;
    for (char c : str) { result += tolower(c); };
    return result;
}

static string firstUpper(string str) {
    return !str.empty() ? (str[0] = toupper(str[0]), str) : str;
};

static int rollDice(int max = 6) {
    int out = -1;
    for (int i = 0; i < getRand(10, 15); i++) {
        out = getRand(1, max);
        cout << "\r" << to_string(out) + " ";
        sleep_for(milliseconds(50));
    };
    display("!");
    return out;
};

static int rollDiceAndCalculateTotal(const string& attribute, int maxDice = 6) {
    display(attribute + ":");

    vector<int> dice;
    for (int i = 0; i < 4; ++i) { dice.push_back(rollDice(maxDice)); };

    int total = vectorTotal(highestOfVector(dice, 3));

    display("Total: " + to_string(total) + "\n");

    return total;
}

class ArmorStats {
public:
    double Defense;
    double Weight;
    double Agility;

    ArmorStats(double _Defense, double _Weight, double _Agility) :
        Defense(_Defense),
        Weight(_Weight),
        Agility(_Agility)
    {}
};

class Armor {
public:
    string Name;
    ArmorStats Stats;

    Armor(string _Name, ArmorStats _Stats = ArmorStats(0, 0, 0)) :
        Name(_Name),
        Stats(_Stats)
    {}
};

class ShieldStats {
public:
    double Defense;
    double Weight;

    ShieldStats(double _Defense, double _Weight) :
        Defense(_Defense),
        Weight(_Weight)
    {}
};

class Shield {
public:
    string Name;
    ShieldStats Stats;

    Shield(string _Name, ShieldStats _Stats = ShieldStats(0, 0)) :
        Name(_Name),
        Stats(_Stats)
    {}
};

class ArmorClass {
public:
    Armor Armor;
    Shield Shield;
};

class WeaponStats {
public:
    double Damage;
    double Speed;
    double Weight;

    WeaponStats(double _Damage, double _Speed, double _Weight) :
        Damage(_Damage),
        Speed(_Speed),
        Weight(_Weight)
    {}
};

class Weapon {
public:
    string Name;
    string Type;
    WeaponStats Stats;

    Weapon(string _Name, string _Type, WeaponStats _Stats = WeaponStats(0, 0, 0)) :
        Name(_Name),
        Type(_Type),
        Stats(_Stats)
    {}
};

class Equipment {
public:
    ArmorClass Armor;
    vector<Weapon> Weapons;

    Equipment(ArmorClass _Armor, vector<Weapon> _Weapons) :
        Armor(_Armor),
        Weapons(_Weapons)
    {}
};

class Player {
public:
    string Name;

    string Class;

    string Species;

    int Strength;
    int Dexterity;
    int Constitution;
    int Intelligence;
    int Wisdom;
    int Charisma;

    int StrengthModifier;
    int DexterityModifier;
    int ConstitutionModifier;
    int IntelligenceModifier;
    int WisdomModifier;
    int CharismaModifier;

    string Background;

    Equipment Equipment;

    Player(const string& _name, const string& _class, const string& _species,
        int _str, int _dex, int _con, int _intl, int _wis, int _cha,
        const string& _background)
        : Name(_name), Class(_class), Species(_species),
        Strength(_str), Dexterity(_dex), Constitution(_con), Intelligence(_intl), Wisdom(_wis), Charisma(_cha),
        Background(_background)
    {}
};

vector<Weapon> Weapons = {
    Weapon("Longsword", "Two-Handed", WeaponStats(0.6, 0.4, 1.15)),
    Weapon("Warhammer", "Two-Handed", WeaponStats(0.7, 0.3, 1.3)),
    Weapon("Dagger", "One-Handed", WeaponStats(0.3, 0.7, 0.2)),
    Weapon("Battleaxe", "Two-Handed", WeaponStats(0.8, 0.2, 1.5)),
    Weapon("Mace", "One-Handed", WeaponStats(0.6, 0.4, 0.6)),
    Weapon("Spear", "Two-Handed", WeaponStats(0.5, 0.5, 0.4)),
    Weapon("Rapier", "One-Handed", WeaponStats(0.5, 0.6, 0.4)),
    Weapon("Greatsword", "Two-Handed", WeaponStats(0.9, 0.1, 1.8)),
    Weapon("Quarterstaff", "Two-Handed", WeaponStats(0.4, 0.6, 0.3)),
    Weapon("Flail", "One-Handed", WeaponStats(0.7, 0.3, 0.7))
};

vector<Armor> Armors = {
    Armor("Leather Armor", ArmorStats(0.4, 0.2, 1.1)),
    Armor("Chainmail", ArmorStats(0.6, 0.5, 1.3)),
    Armor("Plate Armor", ArmorStats(0.8, 0.8, 1.5)),
    Armor("Robes", ArmorStats(0.2, 0.1, 1.2)),
    Armor("Scale Mail", ArmorStats(0.7, 0.6, 1.4)),
    Armor("Hide Armor", ArmorStats(0.5, 0.3, 1.1)),
    Armor("Breastplate", ArmorStats(0.7, 0.7, 1.4)),
    Armor("Chain Shirt", ArmorStats(0.5, 0.4, 1.1)),
    Armor("Padded Armor", ArmorStats(0.3, 0.2, 1.05)),
    Armor("Splint Armor", ArmorStats(0.6, 0.7, 1.2))
};

vector<Shield> Shields = {
    Shield("Wooden Shield", ShieldStats(0.3, 0.4)),
    Shield("Buckler", ShieldStats(0.2, 0.3)),
    Shield("Tower Shield", ShieldStats(0.5, 0.7)),
    Shield("Round Shield", ShieldStats(0.3, 0.5)),
    Shield("Kite Shield", ShieldStats(0.4, 0.6)),
    Shield("Heater Shield", ShieldStats(0.4, 0.5)),
    Shield("Targe", ShieldStats(0.2, 0.3)),
    Shield("Spiked Shield", ShieldStats(0.4, 0.6)),
    Shield("Pavise Shield", ShieldStats(0.5, 0.8)),
    Shield("Scutum", ShieldStats(0.5, 0.7))
};


vector<string> Classes = {
	"Barbarian",
	"Bard",
	"Cleric",
	"Druid",
	"Fighter",
	"Monk",
	"Paladin",
	"Ranger",
	"Rogue",
	"Sorcerer",
	"Warlock",
	"Wizard"
};

vector<string> AllSpecies = {
	"Dragonbord",
	"Dwarf",
	"Elf",
	"Fairy",
	"Gnome",
	"Goblin",
	"Halfing",
	"Human",
	"Tiefling"
};

vector<vector<string>> bigNumbers = {
	{
		"          ",
		"          ",
		"     1    ",
		"          ",
		"          "
	},
	{
		"          ",
		"          ",
		"     2    ",
		"          ",
		"          "
	},
	{
		"          ",
		"          ",
		"     3    ",
		"          ",
		"          "
	},
	{
		"          ",
		"          ",
		"     4    ",
		"          ",
		"          "
	},
	{
		"          ",
		"          ",
		"     5    ",
		"          ",
		"          "
	},
	{
		"          ",
		"          ",
		"     6    ",
		"          ",
		"          "
	},
	{
		"          ",
		"          ",
		"     7    ",
		"          ",
		"          "
	},
	{
		"          ",
		"          ",
		"     8    ",
		"          ",
		"          "
	},
	{
		"          ",
		"          ",
		"     9    ",
		"          ",
		"          "
	}
};
