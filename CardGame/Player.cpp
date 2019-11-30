#include "Player.h"

Player::Player() {
	AI = 1;
	points = 0;
	taken = 0;
	declaration = 0;
}

Player::~Player(){}

//Getters
int Player::getAI(){
	return AI;
}

int Player::getTaken() {
	return taken;
}

int Player::getPoints() {
	return points;
}

int Player::getDeclaration() {
	return declaration;
}

//Setters
void Player::setAI(int AI){
	this->AI = AI;
}

void Player::setTaken(int taken) {
	this->taken = taken;
}

void Player::setPoints(int points) {
	this->points = points;
}

void Player::setDeclaration(int declaration) {
	this->declaration = declaration;
}