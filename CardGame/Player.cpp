#include "Player.h"

Player::Player() {
	AI = 1;
	taken = 0;
}

Player::Player(const Player& pattern){
	this->deck = pattern.deck;
	this->points = pattern.points;
	this->taken = pattern.taken;
	this->AI = pattern.AI;
}

Player::~Player(){}

//Getters
int Player::getAI(){
	return AI;
}

int Player::getTaken() {
	return taken;
}

int Player::getPoints(int position) {
	if (position == -1) {
		int sum = 0;
		for (int el : points)
			if (el >= 0)
				sum += el;
		return sum;
	}
	else {
		if (int(points.size())  <= position)
			return 1000;
		else
			return points[position];
	}
}

int Player::getDeclaration() {
	if (points.size() == 0) 
		return -1000;
	else
		return points[points.size() - 1];
}

//Setters
void Player::setAI(int AI){
	this->AI = AI;
}

void Player::setTaken(int taken) {
	this->taken = taken;
}

void Player::setDeclaration(int declaration) {
	if (points.size() > 0 && points[points.size() - 1] == -1000)
		points[points.size() - 1] = declaration;
	else
		points.push_back(declaration);
}

void Player::pointsScore(bool result){
	if (result) {
		points[points.size() - 1] += 10;
	}
	else
		points[points.size() - 1] *= (-1);
	points.push_back(-1000);
}
