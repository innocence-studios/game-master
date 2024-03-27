
// #include "data.h"
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

static string repeatString(string str, int amount) {
    string result;
    for (int i = 0; i < amount; ++i) {
        result += str;
    }
    return result;
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

static int indexOf(vector<string> vec, string val) {
    auto it = find(vec.begin(), vec.end(), val);
    if (it != vec.end()) {
        return static_cast<int>(distance(vec.begin(), it));
    }
    else {
        return -1;
    };
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

static int longestString(vector<string> vec) {
    int maxLength = 0;
    for (const std::string& str : vec) {
        int length = str.length();
        if (length > maxLength) {
            maxLength = length;
        }
    }
    return maxLength;
};

static int choice(vector<string> choices) {
    for (int i = 0; i < choices.size(); i++) {
        display("> " + choices[i]);
    };
    
    display("");

    int i = 0;
    bool keyPressed = false;

    cout << "\r> Option " << i + 1 << "  (" << choices[i] << ")                    \r";

    while (!(GetKeyState(VK_RETURN) & 0x8000)) {
        string spaces = repeatString(" ", (longestString(choices) - choices[i].size()));
        if (GetKeyState(VK_UP) & 0x8000) {
            if (!keyPressed) {
                i = clamp(i - 1, 0, static_cast<int>(choices.size() - 1));
                cout << "\r> Option " << i + 1 << "  (" << choices[i] << ")                    \r";
            };
            keyPressed = true;
        }
        else if (GetKeyState(VK_DOWN) & 0x8000) {
            if (!keyPressed) {
                i = clamp(i + 1, 0, static_cast<int>(choices.size() - 1));
                cout << "\r> Option " << i + 1 << "  (" << choices[i] << ")                    \r";
            }
            keyPressed = true;
        }
        else {
            keyPressed = false;
        };
    };

    display("\n");

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

static string toLowercase(string str) {
    string result;
    for (char c : str) { result += tolower(c); };
    return result;
}

static string firstUpper(string str) {
    return !str.empty() ? (str[0] = toupper(str[0]), str) : str;
};

static int rollDice(int max) {
    int out = -1;
    for (int i = 0; i < getRand(10, 15); i++) {
        out = getRand(1, max);
        cout << "\r" << to_string(out) + " ";
        sleep_for(milliseconds(50));
    };
    display("!");
    return out;
};

static int rollDiceAndCalculateTotal(string attribute, int maxDice = 6) {
    display(attribute + ":");

    vector<int> dice;
    for (int i = 0; i < 4; ++i) { dice.push_back(rollDice(maxDice)); };

    int total = vectorTotal(highestOfVector(dice, 3));

    display("Total: " + to_string(total) + "\n");

    return total;
}

struct Dice {
    int amount;
    int max;
};

enum Bonus {
    Advantage,
    Disadvantage,
    Neutral
};

enum WeaponProperty {
    Range,
    Ammunition,
    Loading,
    Reload,
    TwoHanded,
    Versatile,
    Light,
    Heavy,
    Finesse,
    Thrown,
    Special,
    Reach,
    BurstFire,
};
enum WeaponAttribute {
    Necrotic,
    Slashing,
    Piercing,
    Bludgeoning,
    Radiant,
};
enum WeaponType {
    Martial,
    Simple,
    Firearm,
};
enum WeaponStyle {
    Melee,
    Ranged,
};

class Weapon {
public:
    string name;                       // Weapon name
    double value;                      // Cost in gp
    Dice damage;                       // Dice type
    WeaponAttribute attributes;        // Weapon attribute
    WeaponType type;                   // Martial, Firearm...
    WeaponStyle style;                 // Melee, Ranged...
    double weight;                     // Weight in *kg*
    vector<WeaponProperty> properties; // Weapon properties

    Weapon(string _name, double _value, Dice _damage, WeaponType _type, WeaponAttribute _attributes, WeaponStyle _style, double _weight, vector<WeaponProperty> _properties) :
        name(_name),
        value(_value),
        damage(_damage),
        type(_type),
        attributes(_attributes),
        style(_style),
        weight(_weight),
        properties(_properties)
    {}
};

vector<Weapon> Weapons = {
    //     Name                      Dice Damage   Type                 Attribute                     Style                     Properties
    Weapon("Antimatter Rifle",       -1,  {6, 8},  WeaponType::Firearm, WeaponAttribute::Necrotic,    WeaponStyle::Ranged, 4.5, vector<WeaponProperty>({
            WeaponProperty::Range,
            WeaponProperty::Ammunition,
            WeaponProperty::Reload,
            WeaponProperty::TwoHanded
        })),
    Weapon("Battleaxe",              10,  {1, 8},  WeaponType::Martial, WeaponAttribute::Slashing,    WeaponStyle::Melee,  1.8, vector<WeaponProperty>({
            WeaponProperty::Versatile
        })),
    Weapon("Blowgun",                10,  {1, 1},  WeaponType::Martial, WeaponAttribute::Piercing,    WeaponStyle::Ranged, .4,  vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Loading,
            WeaponProperty::Range
        })),
    Weapon( "Boomerang",             -1,  {1, 4},  WeaponType::Simple,  WeaponAttribute::Bludgeoning, WeaponStyle::Ranged, .4,  vector<WeaponProperty>({
            WeaponProperty::Range
        })),
    Weapon("Club",                   .1,  {1, 4},  WeaponType::Simple,  WeaponAttribute::Bludgeoning, WeaponStyle::Melee,  .9,  vector<WeaponProperty>({
            WeaponProperty::Light
        })),
    Weapon("Crossbow (hand)",        75,  {1, 6},  WeaponType::Martial, WeaponAttribute::Piercing,    WeaponStyle::Ranged, 1.4, vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Range,
            WeaponProperty::Light,
            WeaponProperty::Loading
        })),
    Weapon("Crossbow (heavy)",       50,  {1, 10}, WeaponType::Martial, WeaponAttribute::Piercing,    WeaponStyle::Ranged, 8.2, vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Heavy,
            WeaponProperty::Loading,
            WeaponProperty::Range,
            WeaponProperty::TwoHanded,
        })),
    Weapon("Crossbow (light)",       25,  {1, 8},  WeaponType::Simple,  WeaponAttribute::Piercing,    WeaponStyle::Ranged, 2.3, vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Loading,
            WeaponProperty::Range,
            WeaponProperty::TwoHanded,
        })),
    Weapon("Dagger",                 2,   {1, 4},  WeaponType::Simple,  WeaponAttribute::Piercing,    WeaponStyle::Melee,  .4,  vector<WeaponProperty>({
            WeaponProperty::Finesse,
            WeaponProperty::Light,
            WeaponProperty::Thrown,
            WeaponProperty::Range,
        })),
    Weapon("Dart",                   .05, {1, 4},  WeaponType::Simple,  WeaponAttribute::Piercing,    WeaponStyle::Ranged, .1,  vector<WeaponProperty>({
            WeaponProperty::Finesse,
            WeaponProperty::Thrown,
            WeaponProperty::Range,
        })),
    Weapon("Double-Bladed Scimitar", 100, {2, 4},  WeaponType::Martial, WeaponAttribute::Slashing,    WeaponStyle::Melee,  2.7, vector<WeaponProperty>({
            WeaponProperty::Special,
            WeaponProperty::TwoHanded,
        })),
    Weapon("Flail",                  10,  {1, 8},  WeaponType::Martial, WeaponAttribute::Bludgeoning, WeaponStyle::Melee,  .9,  vector<WeaponProperty>( {     } )),
    Weapon("Glaive",                 20,  {1, 10}, WeaponType::Martial, WeaponAttribute::Slashing,    WeaponStyle::Melee,  2.7, vector<WeaponProperty>({
            WeaponProperty::Heavy,
            WeaponProperty::Reach,
            WeaponProperty::TwoHanded,
        })),
    Weapon("Greataxe",               30,  {1, 12}, WeaponType::Martial, WeaponAttribute::Slashing,    WeaponStyle::Melee,  3.2, vector<WeaponProperty>({
            WeaponProperty::Heavy,
            WeaponProperty::TwoHanded,
        })),
    Weapon("Greatclub",              .2,  {1, 8},  WeaponType::Simple,  WeaponAttribute::Bludgeoning, WeaponStyle::Melee,  4.5, vector<WeaponProperty>({
            WeaponProperty::TwoHanded,
        })),
    Weapon("Greatsword",             50,  {2, 6},  WeaponType::Martial, WeaponAttribute::Slashing,    WeaponStyle::Melee,  2.7, vector<WeaponProperty>({
            WeaponProperty::Heavy,
            WeaponProperty::TwoHanded,
        })),
    Weapon("Halberd",                20,  {1, 10}, WeaponType::Martial, WeaponAttribute::Slashing,    WeaponStyle::Melee,  2.7, vector<WeaponProperty>({
            WeaponProperty::Heavy,
            WeaponProperty::Reach,
            WeaponProperty::TwoHanded,
        })),
    Weapon("Handaxe",                5,   {1, 6},  WeaponType::Simple,  WeaponAttribute::Slashing,    WeaponStyle::Melee,  .9,  vector<WeaponProperty>({
            WeaponProperty::Light,
            WeaponProperty::Thrown,
            WeaponProperty::Range,
        })),
    Weapon("Javelin",                .5,  {1, 6},  WeaponType::Simple,  WeaponAttribute::Piercing,    WeaponStyle::Melee,  .9,  vector<WeaponProperty>({
            WeaponProperty::Thrown,
            WeaponProperty::Range,
        })),
    Weapon("Lance",                  10,  {1, 12}, WeaponType::Martial, WeaponAttribute::Piercing,    WeaponStyle::Melee,  2.7, vector<WeaponProperty>({
            WeaponProperty::Reach,
            WeaponProperty::Special,
        })),
    Weapon("Laser Pistol",           -1,  {3, 6},  WeaponType::Firearm, WeaponAttribute::Radiant,     WeaponStyle::Ranged, .9,  vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Range,
            WeaponProperty::Reload,
        })),
    Weapon("Laser Rifle",            -1,  {3, 8},  WeaponType::Firearm, WeaponAttribute::Radiant,     WeaponStyle::Ranged, 3.2, vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Range,
            WeaponProperty::Reload,
            WeaponProperty::TwoHanded,
        })),
    Weapon("Light Hammer",           2,   {1, 4},  WeaponType::Simple,  WeaponAttribute::Bludgeoning, WeaponStyle::Melee,  .9,  vector<WeaponProperty>({
            WeaponProperty::Light,
            WeaponProperty::Thrown,
            WeaponProperty::Range,
        })),
    Weapon("Longbow",                50,  {1, 8},  WeaponType::Martial, WeaponAttribute::Piercing,    WeaponStyle::Ranged, .9,  vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Heavy,
            WeaponProperty::Range,
            WeaponProperty::TwoHanded,
        })),
    Weapon("Longsword",              15,  {1, 8},  WeaponType::Martial, WeaponAttribute::Slashing,    WeaponStyle::Melee,  1.4, vector<WeaponProperty>({
            WeaponProperty::Versatile,
        })),
    Weapon("Mace",                   5,   {1, 6},  WeaponType::Simple,  WeaponAttribute::Bludgeoning, WeaponStyle::Melee,  1.8, vector<WeaponProperty>( {     } )),
    Weapon("Maul",                   10,  {2, 6},  WeaponType::Martial, WeaponAttribute::Bludgeoning, WeaponStyle::Melee,  4.5, vector<WeaponProperty>({
            WeaponProperty::Heavy,
            WeaponProperty::TwoHanded,
        })),
    Weapon("Morningstar",            15,  {2, 6},  WeaponType::Martial, WeaponAttribute::Piercing,    WeaponStyle::Melee,  1.8, vector<WeaponProperty>( {     } )),
    Weapon("Musket",                 500, {1, 12}, WeaponType::Firearm, WeaponAttribute::Piercing,    WeaponStyle::Ranged, 4.5, vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Range,
            WeaponProperty::Loading,
            WeaponProperty::TwoHanded,
        })),
    Weapon("Net",                    1,   {0, 0},  WeaponType::Martial, WeaponAttribute::Bludgeoning, WeaponStyle::Ranged, 1.4, vector<WeaponProperty>({
            WeaponProperty::Special,
            WeaponProperty::Thrown,
            WeaponProperty::Range,
        })),
    Weapon("Pike",                   5,   {1, 10}, WeaponType::Martial, WeaponAttribute::Piercing,    WeaponStyle::Melee,  8.2, vector<WeaponProperty>({
            WeaponProperty::Heavy,
            WeaponProperty::Reach,
            WeaponProperty::TwoHanded,
        })),
    Weapon("Pistol",                 250, {1, 10}, WeaponType::Firearm, WeaponAttribute::Piercing,    WeaponStyle::Ranged, 1.4, vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Range,
            WeaponProperty::Loading,
        })),
    Weapon("Pistol (Automatic)",     -1,  {2, 6},  WeaponType::Firearm, WeaponAttribute::Piercing,    WeaponStyle::Ranged, 1.4, vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Range,
            WeaponProperty::Reload,
        })),
    Weapon("Quarterstaff",           .2,  {1, 6},  WeaponType::Simple,  WeaponAttribute::Bludgeoning, WeaponStyle::Melee,  1.8, vector<WeaponProperty>({
            WeaponProperty::Versatile,
        })),
    Weapon("Rapier",                 25,  {1, 8},  WeaponType::Martial, WeaponAttribute::Piercing,    WeaponStyle::Melee,  .9,  vector<WeaponProperty>({
            WeaponProperty::Finesse,
        })),
    Weapon("Revolver",               -1,  {2, 8},  WeaponType::Firearm, WeaponAttribute::Piercing,    WeaponStyle::Ranged, 1.4, vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Range,
            WeaponProperty::Reload,
        })),
    Weapon("Revolver (Automatic)",   -1,  {2, 8},  WeaponType::Firearm, WeaponAttribute::Piercing,    WeaponStyle::Ranged, 3.6, vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Range,
            WeaponProperty::Reload,
            WeaponProperty::TwoHanded,
            WeaponProperty::BurstFire,
        })),
    Weapon("Revolver (Hunting)",     -1,  {2, 10}, WeaponType::Firearm, WeaponAttribute::Piercing,    WeaponStyle::Ranged, 3.6, vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Range,
            WeaponProperty::Reload,
            WeaponProperty::TwoHanded,
        })),
    Weapon("Scimitar",               25,  {1, 6},  WeaponType::Martial, WeaponAttribute::Slashing,    WeaponStyle::Melee,  1.4, vector<WeaponProperty>({
            WeaponProperty::Finesse,
            WeaponProperty::Light,
        })),
    Weapon("Shortbow",               25,  {1, 6},  WeaponType::Simple,  WeaponAttribute::Piercing,    WeaponStyle::Ranged, .9,  vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Range,
            WeaponProperty::TwoHanded,
        })),
    Weapon("Shortsword",             10,  {1, 6},  WeaponType::Martial, WeaponAttribute::Piercing,    WeaponStyle::Melee,  .9,  vector<WeaponProperty>({
            WeaponProperty::Finesse,
            WeaponProperty::Light,
        })),
    Weapon("Shotgun",                -1,  {2, 8},  WeaponType::Firearm, WeaponAttribute::Piercing,    WeaponStyle::Ranged, 3.2, vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Range,
            WeaponProperty::Reload,
            WeaponProperty::TwoHanded,
        })),
    Weapon("Sickle",                 1,   {1, 4},  WeaponType::Simple,  WeaponAttribute::Slashing,    WeaponStyle::Melee,  .9,  vector<WeaponProperty>({
            WeaponProperty::Light,
        })),
    Weapon("Sling",                  .1,  {1, 4},  WeaponType::Simple,  WeaponAttribute::Bludgeoning, WeaponStyle::Ranged, 0,   vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Range,
        })),
    Weapon("Spear",                  1,   {1, 6},  WeaponType::Simple,  WeaponAttribute::Piercing,    WeaponStyle::Melee,  1.4, vector<WeaponProperty>({
            WeaponProperty::Ammunition,
            WeaponProperty::Range,
            WeaponProperty::Versatile,
        })),
    Weapon("Trident",                5,   {1, 6},  WeaponType::Martial, WeaponAttribute::Piercing,    WeaponStyle::Melee,  1.8, vector<WeaponProperty>({
            WeaponProperty::Thrown,
            WeaponProperty::Range,
            WeaponProperty::Versatile,
        })),
    Weapon("War Pick",               5,   {1, 8},  WeaponType::Martial, WeaponAttribute::Piercing,    WeaponStyle::Melee,  .9,  vector<WeaponProperty>( {     } )),
    Weapon("Warhammer",              15,  {1, 8},  WeaponType::Martial, WeaponAttribute::Bludgeoning, WeaponStyle::Melee,  .9,  vector<WeaponProperty>({
            WeaponProperty::Versatile,
        })),
    Weapon("Whip",                   2,   {1, 4},  WeaponType::Martial, WeaponAttribute::Slashing,    WeaponStyle::Melee,  1.4, vector<WeaponProperty>({
            WeaponProperty::Finesse,
            WeaponProperty::Reach,
        })),
    Weapon("Yklwa",                  1,   {1, 8},  WeaponType::Simple,  WeaponAttribute::Piercing,    WeaponStyle::Melee,  .9,  vector<WeaponProperty>({
            WeaponProperty::Thrown,
            WeaponProperty::Range,
        }) ),
};

static Weapon findWeapon(string name) {
    for (Weapon weapon : Weapons) {
        if (toLowercase(weapon.name) == toLowercase(name)) { return weapon; };
    };
    return Weapon("", 0, { 0, 0 }, WeaponType::Simple, WeaponAttribute::Slashing, WeaponStyle::Melee, 0, vector<WeaponProperty>({ }));
};

static bool addWeapon(string name, vector<Weapon>& _Weapons, int amount = 1) {
    if (findWeapon(name).name == "") { display("Couldn't give you " + name + "... Report bug!"); return false; };
    for (int i = 0; i < amount; i++) { _Weapons.push_back(findWeapon(name)); };
    display("Successfully gave you " + name + " x" + to_string(amount) + "!");
    return true;
};

static bool weaponHasProperty(Weapon weapon, WeaponProperty prop) {
    for (WeaponProperty elem : weapon.properties) {
        if (elem == prop) { return true; }
    };
    return false;
};

static vector<Weapon> shuffleWeapons(const vector<Weapon>& original) {
    vector<Weapon> shuffled = original;
    random_device rd;
    mt19937 g(rd());
    shuffle(shuffled.begin(), shuffled.end(), g);
    return shuffled;
}


class Armor {
public:
    string name;
    double value;
    int bonus;
    bool dexModifier;
    int dexLimit;
    int strength;
    Bonus stealth;
    double weight;

    Armor(string _name, double _value, int _bonus, bool _dexModifier, int _dexLimit, int _strength, Bonus _stealth, double _weight) :
        name(_name),
        value(_value),
        bonus(_bonus),
        dexModifier(_dexModifier),
        dexLimit(_dexLimit),
        strength(_strength),
        stealth(_stealth),
        weight(_weight)
    {}
};

vector<Armor> Armors = {
    Armor("Breastplate Armor",       400,  14, true,  2,  0,  Bonus::Neutral,      9),
    Armor("Chain Mail Armor",        75,   16, false, -1, 13, Bonus::Neutral,      25),
    Armor("Chain Shirt Armor",       50,   13, true,  2,  0,  Bonus::Neutral,      9),
    Armor("Half Plate Armor",        750,  15, true,  2,  0,  Bonus::Disadvantage, 18),
    Armor("Hide Armor",              10,   12, true,  2,  0,  Bonus::Neutral,      5.4),
    Armor("Leather Armor",           10,   11, true,  -1, 0,  Bonus::Neutral,      4.5),
    Armor("Padded Armor",            5,    11, true,  -1, 0,  Bonus::Disadvantage, 3.6),
    Armor("Plate Armor",             1500, 18, false, -1, 15, Bonus::Disadvantage, 29.5),
    Armor("Pride Silk Outfit",       500,  11, true,  -1, 0,  Bonus::Neutral,      1.8),
    Armor("Ring Mail Armor",         30,   14, false, -1, 0,  Bonus::Disadvantage, 18),
    Armor("Scale Mail Armor",        50,   14, true,  2,  0,  Bonus::Disadvantage, 20.4),
    Armor("Spiked Armor Armor",      75,   14, true,  2,  0,  Bonus::Disadvantage, 20.4),
    Armor("Splint Armor",            200,  17, false, -1, 15, Bonus::Disadvantage, 27.2),
    Armor("Studded Leather Armor",   45,   12, true,  -1, 15, Bonus::Neutral,      5.9)
};

class ArmorClass {
public:
    Armor armor;
    bool shield;

    ArmorClass(Armor _armor, bool _shield) :
        armor(_armor),
        shield(_shield)
    {}
};



class Item {
public:
    string name;
    double value;
    double weight;

    Item(string _name, double _value, double _weight) :
        name(_name),
        value(_value),
        weight(_weight)
    {}
};

class Equipment {
public:
    ArmorClass armor;
    vector<Weapon> weapons;
    vector<Item> inventory;

    Equipment(ArmorClass _armor, vector<Weapon> _weapons, vector<Item> _inventory) :
        armor(_armor),
        weapons(_weapons),
        inventory(_inventory)
    {}
};

class Player {
public:
    string name;

    string class_;

    string species;

    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;

    int strengthModifier;
    int dexterityModifier;
    int constitutionModifier;
    int intelligenceModifier;
    int wisdomModifier;
    int charismaModifier;

    string background;

    Equipment equipment;

    Player(string _name, string _class, string _species, int _str, int _dex, int _con, int _intl, int _wis, int _cha, int _strM, int _dexM, int _conM, int _intlM, int _wisM, int _chaM, string _background, Equipment _Equipment) :
        name(_name), class_(_class), species(_species),
        strength(_str), dexterity(_dex), constitution(_con), intelligence(_intl), wisdom(_wis), charisma(_cha),
        strengthModifier(_strM), dexterityModifier(_dexM), constitutionModifier(_conM), intelligenceModifier(_intlM), wisdomModifier(_wisM), charismaModifier(_cha),
        background(_background), equipment(_Equipment)
    {}
};

vector<Item> Items = {
    Item("Explorer's Pack", 10, 26)
};

static Item findItem(string name) {
    for (Item item : Items) {
        if (toLowercase(item.name) == toLowercase(name)) { return item; };
    };
    return Item("", .0, .0);
};

static Armor findArmor(string name) {
    for (Armor armor : Armors) {
        if (toLowercase(armor.name) == toLowercase(name)) { return armor; };
    };
    return Armor("", 0, 0, false, 0, 0, Bonus::Neutral, 0);
};

static bool addArmor(string name, ArmorClass& _ArmorClass) {
    if (findArmor(name).name == "") { display("Couldn't give you " + name + "... Report bug!"); return false; };
    _ArmorClass.armor = findArmor(name);
    display("Successfully gave you " + name + "!");
    return true;
};

static bool addItem(string name, vector<Item>& _Inventory, int amount = 1) {
    if (findItem(name).name == "") { display("Couldn't give you " + name + "... Report bug!"); return false; };
    for (int i = 0; i < amount; i++) { _Inventory.push_back(findItem(name)); };
    display("Successfully gave you " + name + " x" + to_string(amount) + "!");
    return true;
};

enum Ability {
    Strength,
    Dexterity,
    Constitution,
    Intelligence,
    Wisdom,
    Charisma
};

class Class {
public:
    string name;
    Dice hit;
    vector<Ability> ability;
    vector<Ability> saves;

    Class(string _name, Dice _hit, vector<Ability> _ability, vector<Ability> _saves) :
        name(_name),
        hit(_hit),
        ability(_ability),
        saves(_saves)
    {}
};

vector<Class> Classes = {
    Class("Barbarian", { 1, 12 }, { Ability::Strength }, { Ability::Strength, Ability::Constitution }),
    Class("Bard", { 1, 8 }, { Ability::Charisma }, { Ability::Dexterity, Ability::Charisma }),
    Class("Cleric", { 1, 8 }, { Ability::Wisdom }, { Ability::Wisdom, Ability::Charisma }),
    Class("Druid", { 1, 8 }, { Ability::Wisdom }, { Ability::Intelligence, Ability::Wisdom }),
    Class("Fighter", { 1, 10 }, { Ability::Strength }, { Ability::Strength, Ability::Constitution }),
    Class("Monk", { 1, 8 }, { Ability::Dexterity, Ability::Wisdom }, { Ability::Strength, Ability::Dexterity }),
    Class("Paladin", { 1, 10 }, { Ability::Strength, Ability::Charisma }, { Ability::Wisdom, Ability::Charisma }),
    Class("Ranger", { 1, 10 }, { Ability::Dexterity, Ability::Wisdom }, { Ability::Strength, Ability::Dexterity }),
    Class("Rogue", { 1, 8 }, { Ability::Dexterity }, { Ability::Dexterity, Ability::Intelligence }),
    Class("Sorcerer", { 1, 6 }, { Ability::Charisma }, { Ability::Constitution, Ability::Charisma }),
    Class("Warlock", { 1, 8 }, { Ability::Charisma }, { Ability::Wisdom, Ability::Charisma }),
    Class("Wizard", { 1, 6 }, { Ability::Intelligence }, { Ability::Intelligence, Ability::Wisdom }),
};

static Class findClass(string name) {
    for (Class _class : Classes) {
        if (toLowercase(_class.name) == toLowercase(name)) { return _class; };
    };
    return Class("", { 0, 0 }, { Ability::Strength }, { Ability::Strength, Ability::Strength });
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




int main() {
    display(to_string(Weapons.size()) + " weapons");
    display(to_string(Armors.size()) + " armors");
    display("Hey. I am your Game Master. Let's define your character:\n");
    /*
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

    display("Right, right! So, for your starting equipment...\nChoose which one you like the most:");
    */

    Class _Class = findClass("Bard");

    ArmorClass _ArmorClass = ArmorClass(Armor("", 0, 0, false, 0, 0, Bonus::Neutral, 0), false);
    vector<Weapon> _Weapons;
    vector<Item> _Inventory;
    Equipment _Equipment = Equipment(_ArmorClass, _Weapons, _Inventory);

    if (_Class.name == "") {}

    else if (_Class.name == "Barbarian") {
        vector<string> eq_0 = { "Greataxe", "Other Martial Weapon" };
        int eq_0_c = choice(eq_0);
        if (eq_0_c == indexOf(eq_0, "Greataxe")) {
            addWeapon("Greataxe", _Weapons);
        }
        else if (eq_0_c == indexOf(eq_0, "Other Martial Weapon")) {
            display("Which one do you want?");
            vector<string> eq_0_1;

            for (Weapon weapon : shuffleWeapons(Weapons)) {
                if (weapon.type == WeaponType::Martial && eq_0_1.size() < 9 && weapon.name != "Greataxe") eq_0_1.push_back(weapon.name);
            };

            int eq_0_1_c = choice(eq_0_1);
            addWeapon(eq_0_1[eq_0_1_c], _Weapons);
        };

        vector<string> eq_1 = { "Two Handaxes", "Other Simple Weapon" };
        int eq_1_c = choice(eq_1);
        if (eq_1_c == indexOf(eq_1, "Two Handaxes")) {
            addWeapon("Handaxe", _Weapons, 2);
        }
        else if (eq_1_c == indexOf(eq_1, "Other Simple Weapon")){
            display("Which one do you want?");
            vector<string> eq_1_1;

            for (Weapon weapon : shuffleWeapons(Weapons)) {
                if (weapon.type == WeaponType::Simple && eq_1_1.size() < 9 && weapon.name != "Greataxe") eq_1_1.push_back(weapon.name);
            };

            int eq_1_1_c = choice(eq_1_1);
            addWeapon(eq_1_1[eq_1_1_c], _Weapons);
        };

        addWeapon("Javelin", _Weapons, 4);
        addItem("Explorer's Pack", _Inventory);
    }

    else if (_Class.name == "Bard") {
        vector<string> eq_0 = { "Rapier", "Longsword", "Other Simple Weapon"};
        int eq_0_c = choice(eq_0);
        if (eq_0_c == indexOf(eq_0, "Other Simple Weapon")) {
            display("Which one do you want?");
            vector<string> eq_0_1;

            for (Weapon weapon : Weapons) {
                if (weapon.type == WeaponType::Simple && eq_0_1.size() < 9) eq_0_1.push_back(weapon.name);
            };

            int eq_0_1_c = choice(eq_0_1);

            addWeapon(eq_0_1[eq_0_1_c], _Weapons);
        }
        else if (eq_0_c == indexOf(eq_0, "Rapier")) {
            addWeapon("Rapier", _Weapons);
        }
        else if (eq_0_c == indexOf(eq_0, "Longsword")) {
            addWeapon("Longsword", _Weapons);
        };

        vector<string> eq_1 = { "Diplomat's Pack", "Entertainer's Pack" };
        int eq_1_c = choice(eq_1);
        if (eq_1_c == indexOf(eq_1, "Diplomat's Pack")) {
            addItem("Diplomat's Pack", _Inventory);
        }
        else if (eq_1_c == indexOf(eq_1, "Entertainer's Pack")) {
            addItem("Entertainer's Pack", _Inventory);
        };

        addArmor("Leather Armor", _ArmorClass);
        addWeapon("Dagger", _Weapons);
    }

    else if (_Class.name == "Cleric") {
        vector<string> eq_0 = { "Mace", "Warhammer" };
        int eq_0_c = choice(eq_0);
        if (eq_0_c == indexOf(eq_0, "Mace")) {
            addWeapon("Mace", _Weapons);
        }
        else if (eq_0_c == indexOf(eq_0, "Warhammer")) {
            addWeapon("Warhammer", _Weapons);
        };

        vector<string> eq_1 = { "Scale Mail", "Leather Armor", "Chain Mail"};
        int eq_1_c = choice(eq_1);
        if (eq_1_c == indexOf(eq_1, "Scale Mail")) {
            addArmor("Scale Mail", _ArmorClass);
        }
        else if (eq_1_c == indexOf(eq_1, "Leather Armor")) {
            addArmor("Leather Armor", _ArmorClass);
        }
        else if (eq_1_c == indexOf(eq_1, "Chain Mail")) {
            addArmor("Chain Mail", _ArmorClass);
        };

        vector<string> eq_2 = { "Light Crossbow + 20 bolts", "Other Simple Weapon" };
        int eq_2_c = choice(eq_2);
        if (eq_2_c == indexOf(eq_2, "Light Crossbow + 20 bolts")) {
            addWeapon("Light Crossbow", _Weapons);
            addItem("Bolt", _Inventory, 20);
        }
        else if (eq_2_c == indexOf(eq_2, "Other Simple Weapon")) {
            display("Which one do you want?");
            vector<string> eq_2_1;

            for (Weapon weapon : Weapons) {
                if (weapon.type == WeaponType::Simple && eq_2_1.size() < 9) eq_2_1.push_back(weapon.name);
            };

            int eq_2_1_c = choice(eq_2_1);

            addWeapon(eq_2_1[eq_2_1_c], _Weapons);
        };

        vector<string> eq_3 = { "Priest's Pack", "Explorer's Pack" };
        int eq_3_c = choice(eq_3);
        if (eq_3_c == indexOf(eq_3, "Priest's Pack")) {
            addItem("Priest's Pack", _Inventory);
        }
        else if (eq_3_c == indexOf(eq_3, "Explorer's Pack")) {
            addItem("Explorer's Pack", _Inventory);
        };

        _ArmorClass.shield = true;
        addItem("Holy Symbol", _Inventory);
    }

    else if (_Class.name == "Druid") {
        vector<string> eq_0 = { "Shield", "Other Simple Weapon" };
        int eq_0_c = choice(eq_0);
        if (eq_0_c == indexOf(eq_0, "Shield")) {
            _ArmorClass.shield = true;
        }
        else if (eq_0_c == indexOf(eq_0, "Other Simple Weapon")) {
            display("Which one do you want?");
            vector<string> eq_0_1;

            for (Weapon weapon : shuffleWeapons(Weapons)) {
                if (weapon.type == WeaponType::Simple && eq_0_1.size() < 9) eq_0_1.push_back(weapon.name);
            };

            int eq_0_1_c = choice(eq_0_1);
            addWeapon(eq_0_1[eq_0_1_c], _Weapons);
        };

        vector<string> eq_1 = { "Scimitar", "Other Simple Melee Weapon" };
        int eq_1_c = choice(eq_1);
        if (eq_1_c == indexOf(eq_1, "Scimitar")) {
            addWeapon("Scimitar", _Weapons);
        }
        else if (eq_1_c == indexOf(eq_1, "Other Simple Melee Weapon")) {
            display("Which one do you want?");
            vector<string> eq_1_1;

            for (Weapon weapon : shuffleWeapons(Weapons)) {
                if (weapon.type == WeaponType::Simple && weapon.style == WeaponStyle::Melee && eq_1_1.size() < 9) eq_1_1.push_back(weapon.name);
            };

            int eq_1_1_c = choice(eq_1_1);
            addWeapon(eq_1_1[eq_1_1_c], _Weapons);
        };

        addArmor("Leather Armor", _ArmorClass);
        addItem("Explorer's Pack", _Inventory);
        addItem("Druidic Focus", _Inventory);
    }

    else if (_Class.name == "Fighter") {
        vector<string> eq_0 = { "Chain Mail Armor", "Leather Armor + Longbow + 20 Arrows" };
        int eq_0_c = choice(eq_0);
        if (eq_0_c == indexOf(eq_0, "Chain Mail Armor")) {
            addArmor("Chain Mail Armor", _ArmorClass);
        }
        else if (eq_0_c == indexOf(eq_0, "Leather Armor + Longbow + 20 Arrows")) {
            addArmor("Leather Armor", _ArmorClass);
            addWeapon("Longbow", _Weapons);
            addItem("Arrows", _Inventory, 20);
        };

        vector<string> eq_1 = { "Martial Weapon + Shield", "2 Martial Weapons" };
        int eq_1_c = choice(eq_1);
        if (eq_1_c == indexOf(eq_1, "Martial Weapon + Shield")) {
            display("Which one do you want?");
            vector<string> eq_1_1;

            for (Weapon weapon : shuffleWeapons(Weapons)) {
                if (weapon.type == WeaponType::Martial && eq_1_1.size() < 9) eq_1_1.push_back(weapon.name);
            };

            int eq_1_1_c = choice(eq_1_1);
            addWeapon(eq_1_1[eq_1_1_c], _Weapons);
            _ArmorClass.shield = true;
        }
        else if (eq_1_c == indexOf(eq_1, "2 Martial Weapons")) {
            for (int i = 0; i < 2; i++) {
                display("Which one do you want?");
                vector<string> eq_1_2;

                for (Weapon weapon : shuffleWeapons(Weapons)) {
                    if (weapon.type == WeaponType::Martial && eq_1_2.size() < 9) eq_1_2.push_back(weapon.name);
                };

                int eq_1_2_c = choice(eq_1_2);
                addWeapon(eq_1_2[eq_1_2_c], _Weapons);
            };
        };

        vector<string> eq_2 = { "Light Crossbow + 20 bolts", "2 Handaxes" };
        int eq_2_c = choice(eq_2);
        if (eq_2_c == indexOf(eq_2, "Light Crossbow + 20 bolts")) {
            addWeapon("Light Crossbow", _Weapons);
            addItem("Bolt", _Inventory, 20);
        }
        else if (eq_2_c == indexOf(eq_2, "2 Handaxes")) {
            addWeapon("Handaxe", _Weapons, 2);
        };

        vector<string> eq_3 = { "Dungeoneer's Pack", "Explorer's Pack" };
        int eq_3_c = choice(eq_3);
        if (eq_3_c == indexOf(eq_3, "Dungeoneer's Pack")) {
            addItem("Dungeoneer's Pack", _Inventory);
        }
        else if (eq_3_c == indexOf(eq_3, "Explorer's Pack")) {
            addItem("Explorer's Pack", _Inventory);
        };
    }

    else if (_Class.name == "Monk") {
        vector<string> eq_0 = { "Shortsword", "Other Simple Weapon" };
        int eq_0_c = choice(eq_0);
        if (eq_0_c == indexOf(eq_0, "Shortsword")) {
            addWeapon("Shortsword", _Weapons);
        }
        else if (eq_0_c == indexOf(eq_0, "Other Simple Weapon")) {
            display("Which one do you want?");
            vector<string> eq_0_1;

            for (Weapon weapon : Weapons) {
                if (weapon.type == WeaponType::Simple && eq_0_1.size() < 9) eq_0_1.push_back(weapon.name);
            };

            int eq_0_1_c = choice(eq_0_1);

            addWeapon(eq_0_1[eq_0_1_c], _Weapons);
        };

        vector<string> eq_1 = { "Dungeoneer's Pack", "Explorer's Pack" };
        int eq_1_c = choice(eq_1);
        if (eq_1_c == indexOf(eq_1, "Dungeoneer's Pack")) {
            addItem("Dungeoneer's Pack", _Inventory);
        }
        else if (eq_1_c == indexOf(eq_1, "Explorer's Pack")) {
            addItem("Explorer's Pack", _Inventory);
        };

        addWeapon("Dart", _Weapons, 10);
    }

    else if (_Class.name == "Paladin") {
        vector<string> eq_0 = { "Martial Weapon + Shield", "2 Martial Weapons" };
        int eq_0_c = choice(eq_0);
        if (eq_0_c == indexOf(eq_0, "Martial Weapon + Shield")) {
            display("Which one do you want?");
            vector<string> eq_0_1;

            for (Weapon weapon : shuffleWeapons(Weapons)) {
                if (weapon.type == WeaponType::Martial && eq_0_1.size() < 9) eq_0_1.push_back(weapon.name);
            };

            int eq_0_1_c = choice(eq_0_1);
            addWeapon(eq_0_1[eq_0_1_c], _Weapons);
            _ArmorClass.shield = true;
        }
        else if (eq_0_c == indexOf(eq_0, "2 Martial Weapons")) {
            for (int i = 0; i < 2; i++) {
                display("Which one do you want?");
                vector<string> eq_0_2;

                for (Weapon weapon : shuffleWeapons(Weapons)) {
                    if (weapon.type == WeaponType::Martial && eq_0_2.size() < 9) eq_0_2.push_back(weapon.name);
                };

                int eq_0_2_c = choice(eq_0_2);
                addWeapon(eq_0_2[eq_0_2_c], _Weapons);
            };
        };

        vector<string> eq_1 = { "5 Javelins", "Other Simple Melee Weapon" };
        int eq_1_c = choice(eq_1);
        if (eq_1_c == indexOf(eq_1, "Scimitar")) {
            addWeapon("Javelin", _Weapons, 5);
        }
        else if (eq_1_c == indexOf(eq_1, "Other Simple Melee Weapon")) {
            display("Which one do you want?");
            vector<string> eq_1_1;

            for (Weapon weapon : shuffleWeapons(Weapons)) {
                if (weapon.type == WeaponType::Simple && weapon.style == WeaponStyle::Melee && eq_1_1.size() < 9) eq_1_1.push_back(weapon.name);
            };

            int eq_1_1_c = choice(eq_1_1);
            addWeapon(eq_1_1[eq_1_1_c], _Weapons);
        };

        vector<string> eq_2 = { "Priest's Pack", "Explorer's Pack" };
        int eq_2_c = choice(eq_2);
        if (eq_2_c == indexOf(eq_2, "Priest's Pack")) {
            addItem("Priest's Pack", _Inventory);
        }
        else if (eq_2_c == indexOf(eq_2, "Explorer's Pack")) {
            addItem("Explorer's Pack", _Inventory);
        };

        addArmor("Chain Mail Armor", _ArmorClass);
        addItem("Holy Symbol", _Inventory);
    }

    else if (_Class.name == "Ranger") {
        vector<string> eq_0 = { "Scale Mail Armor", "Leather Armor" };
        int eq_0_c = choice(eq_0);
        if (eq_0_c == indexOf(eq_0, "Chain Mail Armor")) {
            addArmor("Scale Mail Armor", _ArmorClass);
        }
        else if (eq_0_c == indexOf(eq_0, "Leather Armor + Longbow + 20 Arrows")) {
            addArmor("Leather Armor", _ArmorClass);
        };

        vector<string> eq_1 = { "2 Shortswords", "Other Simple Melee Weapon" };
        int eq_1_c = choice(eq_1);
        if (eq_1_c == indexOf(eq_1, "2 Shortswords")) {
            addWeapon("Shortsword", _Weapons, 2);
        }
        else if (eq_1_c == indexOf(eq_1, "Other Simple Melee Weapon")) {
            display("Which one do you want?");
            vector<string> eq_1_1;

            for (Weapon weapon : shuffleWeapons(Weapons)) {
                if (weapon.type == WeaponType::Simple && weapon.style == WeaponStyle::Melee && eq_1_1.size() < 9) eq_1_1.push_back(weapon.name);
            };

            int eq_1_1_c = choice(eq_1_1);
            addWeapon(eq_1_1[eq_1_1_c], _Weapons);
        };

        vector<string> eq_2 = { "Dungeoneer's Pack", "Explorer's Pack" };
        int eq_2_c = choice(eq_2);
        if (eq_2_c == indexOf(eq_2, "Dungeoneer's Pack")) {
            addItem("Dungeoneer's Pack", _Inventory);
        }
        else if (eq_2_c == indexOf(eq_2, "Explorer's Pack")) {
            addItem("Explorer's Pack", _Inventory);
        };
        
        addWeapon("Longbow", _Weapons);
        addItem("Arrow", _Inventory, 20);
    }

    else if (_Class.name == "Rogue") {
        vector<string> eq_0 = { "Rapier", "Shortsword" };
        int eq_0_c = choice(eq_0);
        if (eq_0_c == indexOf(eq_0, "Rapier")) {
            addWeapon("Rapier", _Weapons);
        }
        else if (eq_0_c == indexOf(eq_0, "Shortsword")) {
            addWeapon("Shortsword", _Weapons);
        }

        vector<string> eq_1 = { "Shortbow + 20 Arrows", "Shortsword" };
        int eq_1_c = choice(eq_1);
        if (eq_1_c == indexOf(eq_1, "Shortbow + 20 Arrows")) {
            addWeapon("Shortbow", _Weapons);
            addItem("Arrow", _Inventory, 20);
        }
        else if (eq_1_c == indexOf(eq_1, "Shortsword")) {
            addWeapon("Shortsword", _Weapons);
        };

        vector<string> eq_2 = { "Burglar's Pack", "Dungeoneer's Pack", "Explorer's Pack" };
        int eq_2_c = choice(eq_2);
        if (eq_2_c == indexOf(eq_2, "Burglar's Pack")) {
            addItem("Burglar's Pack", _Inventory);
        }
        else if (eq_2_c == indexOf(eq_2, "Dungeoneer's Pack")) {
            addItem("Dungeoneer's Pack", _Inventory);
        }
        else if (eq_2_c == indexOf(eq_2, "Explorer's Pack")) {
            addItem("Explorer's Pack", _Inventory);
        };

        addArmor("Leather Armor", _ArmorClass);
        addWeapon("Dagger", _Weapons, 2);
        addItem("Thieve's Tools", _Inventory);
    }

    else if (_Class.name == "Sorcerer") {
        vector<string> eq_0 = { "Light Crossbow + 20 Bolts", "Other Simple Weapon" };
        int eq_0_c = choice(eq_0);
        if (eq_0_c == indexOf(eq_0, "Light Crossbow + 20 Bolts")) {
            addWeapon("Light Crossbow", _Weapons);
            addItem("Bolt", _Inventory, 20);
        }
        else if (eq_0_c == indexOf(eq_0, "Other Simple Weapon")) {
            display("Which one do you want?");
            vector<string> eq_0_1;

            for (Weapon weapon : shuffleWeapons(Weapons)) {
                if (weapon.type == WeaponType::Simple && eq_0_1.size() < 9) eq_0_1.push_back(weapon.name);
            };

            int eq_0_1_c = choice(eq_0_1);
            addWeapon(eq_0_1[eq_0_1_c], _Weapons);
        };

        vector<string> eq_1 = { "Component Pouch", "Arcane Focus" };
        int eq_1_c = choice(eq_1);
        if (eq_1_c == indexOf(eq_1, "Component Pouch")) {
            addItem("Component Pouch", _Inventory);
        }
        else if (eq_1_c == indexOf(eq_1, "Arcane Focus")) {
            addItem("Arcane Focus", _Inventory);
        };

        vector<string> eq_2 = { "Dungeoneer's Pack", "Explorer's Pack" };
        int eq_2_c = choice(eq_2);
        if (eq_2_c == indexOf(eq_2, "Dungeoneer's Pack")) {
            addItem("Dungeoneer's Pack", _Inventory);
        }
        else if (eq_2_c == indexOf(eq_2, "Explorer's Pack")) {
            addItem("Explorer's Pack", _Inventory);
        };

        addWeapon("Dagger", _Weapons, 2);
    }

    else if (_Class.name == "Warlock") {
        vector<string> eq_0 = { "Light Crossbow + 20 Bolts", "Other Simple Weapon" };
        int eq_0_c = choice(eq_0);
        if (eq_0_c == indexOf(eq_0, "Light Crossbow + 20 Bolts")) {
            addWeapon("Light Crossbow", _Weapons);
            addItem("Bolt", _Inventory, 20);
        }
        else if (eq_0_c == indexOf(eq_0, "Other Simple Weapon")) {
            display("Which one do you want?");
            vector<string> eq_0_1;

            for (Weapon weapon : shuffleWeapons(Weapons)) {
                if (weapon.type == WeaponType::Simple && eq_0_1.size() < 9) eq_0_1.push_back(weapon.name);
            };

            int eq_0_1_c = choice(eq_0_1);
            addWeapon(eq_0_1[eq_0_1_c], _Weapons);
        };

        vector<string> eq_1 = { "Component Pouch", "Arcane Focus" };
        int eq_1_c = choice(eq_1);
        if (eq_1_c == indexOf(eq_1, "Component Pouch")) {
            addItem("Component Pouch", _Inventory);
        }
        else if (eq_1_c == indexOf(eq_1, "Arcane Focus")) {
            addItem("Arcane Focus", _Inventory);
        };

        vector<string> eq_2 = { "Scholar's Pack", "Dungeoneer's Pack" };
        int eq_2_c = choice(eq_2);
        if (eq_2_c == indexOf(eq_2, "Scholar's Pack")) {
            addItem("Scholar's Pack", _Inventory);
        }
        else if (eq_2_c == indexOf(eq_2, "Dungeoneer's Pack")) {
            addItem("Dungeoneer's Pack", _Inventory);
        };

        display("Which one do you want?");
        vector<string> eq_0_1;

        for (Weapon weapon : shuffleWeapons(Weapons)) {
            if (weapon.type == WeaponType::Simple && eq_0_1.size() < 9) eq_0_1.push_back(weapon.name);
        };

        int eq_0_1_c = choice(eq_0_1);
        addWeapon(eq_0_1[eq_0_1_c], _Weapons);

        addArmor("Leather Armor", _ArmorClass);
        addWeapon("Dagger", _Weapons, 2);
    }

    else if (_Class.name == "Wizard") {
        vector<string> eq_0 = { "Quarterstaff", "Dagger" };
        int eq_0_c = choice(eq_0);
        if (eq_0_c == indexOf(eq_0, "Quarterstaff")) {
            addWeapon("Quarterstaff", _Weapons);
        }
        else if (eq_0_c == indexOf(eq_0, "Dagger")) {
            addWeapon("Dagger", _Weapons);
        }

        vector<string> eq_1 = { "Component Pouch", "Arcane Focus" };
        int eq_1_c = choice(eq_1);
        if (eq_1_c == indexOf(eq_1, "Component Pouch")) {
            addItem("Component Pouch", _Inventory);
        }
        else if (eq_1_c == indexOf(eq_1, "Arcane Focus")) {
            addItem("Arcane Focus", _Inventory);
        };

        vector<string> eq_2 = { "Scholar's Pack", "Dungeoneer's Pack" };
        int eq_2_c = choice(eq_2);
        if (eq_2_c == indexOf(eq_2, "Scholar's Pack")) {
            addItem("Scholar's Pack", _Inventory);
        }
        else if (eq_2_c == indexOf(eq_2, "Dungeoneer's Pack")) {
            addItem("Dungeoneer's Pack", _Inventory);
        };

        addItem("Spellbook", _Inventory);
    };

    display("Yay coward");

    // const Player Character = Player(_Name, _Class, _Species, _Strength, _Dexterity, _Constitution, _Intelligence, _Wisdom, _Charisma, _Background, _Equipment);
};
