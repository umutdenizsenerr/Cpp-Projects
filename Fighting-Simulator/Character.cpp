#include "Character.h"
#include <iostream>
#include <string>
Character::Character(string _name, string _type, int _attack, int _defense, int _remainingHealth, int _nMaxRounds) {
this -> name = _name;
this -> type = _type;
this -> attack = _attack;
this -> defense = _defense;
this -> remainingHealth = _remainingHealth;
this -> nMaxRounds = _nMaxRounds;
this -> healthHistory = new int[nMaxRounds+1];
this-> healthHistory[0] = _remainingHealth;
this -> nRoundsSinceSpecial =0;



}

Character::Character(const Character& character) {
//cout << "Copy constructor is called." << endl;

this -> name = character.name;
this -> type = character.type;
this -> attack = character.attack;
this -> defense = character.defense;
this -> remainingHealth = character.remainingHealth;
this -> nMaxRounds = character.nMaxRounds;
this -> healthHistory = new int[character.nMaxRounds+1];
this ->  nRoundsSinceSpecial=character.nRoundsSinceSpecial;
this-> healthHistory[0] = character.remainingHealth;
this->nRoundsSinceSpecial=character.nRoundsSinceSpecial;


}

Character Character::operator=(const Character& character) {
//cout << "Assignment operator is called." << endl;
if(this == &character){
	return *this;
}
this -> name = character.name;
this -> type = character.type;
this -> attack = character.attack;
this -> defense = character.defense;
this -> remainingHealth = character.remainingHealth;
this -> nMaxRounds = character.nMaxRounds;
this ->  nRoundsSinceSpecial=character.nRoundsSinceSpecial;
this -> healthHistory = new int[character.nMaxRounds+1];
this-> healthHistory[0] = character.remainingHealth;
this->nRoundsSinceSpecial=character.nRoundsSinceSpecial;
 return *this;

}

bool Character::operator<(const Character& other) {

	
	
	return this->name<(other.name);


}

Character::~Character() {

if (this->healthHistory != NULL) {
		delete[] this->healthHistory;
	}

}