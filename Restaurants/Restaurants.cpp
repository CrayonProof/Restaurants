// Restaurants.cpp : Defines the entry point for the console application.

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
using namespace std;



int Find(vector<string> collection, string itemName);
void DisplayRestaurants();
void AddRestaurant();
void RemoveRestaurant();
void Cut();
void Shuffle();
void Battle();

vector<string> GetSubVector(vector<string> collection, int start, int end);
vector<string> addItem(vector<string> collection, string item);

void DisplayMenu();
bool EnterYourSelection();
bool TakeInput(int inputType);
bool TakeBattleInput(int firstRestaurant);
void GetLineNotWS(string& inpString);
bool IsPowerOfTwo(int arg0);
int WhatPowerOfTwo(int arg0, bool PowerOfTwoChecked);

bool quit;
string latestInput;
int latestIntInput;
vector<string> restaurants;
vector<string> restaurantsToBattle;

void Battle() {
	if (IsPowerOfTwo((int)restaurants.size())) {

		restaurantsToBattle = restaurants;

		int whichRound = 0;
		while ((int) restaurantsToBattle.size() > 1) {

			cout << "Round: " << whichRound + 1;

			int tournamentIterations = ((int)restaurantsToBattle.size()) / 2;

			for (int j = 0; j < tournamentIterations; j++) {

				if (TakeBattleInput(j)) {
					restaurantsToBattle.erase(restaurantsToBattle.begin() + j + ((latestIntInput) % 2));
				}
			}

			whichRound++;
		}

		restaurants = restaurantsToBattle;
		cout << endl << "The winning restaurant is " << restaurants.at(0) << "." << endl;
	}
	else {
		cout << endl << "The current tournament size (" << (int)restaurants.size() << ") is not a power of two (2, 4, 8...)." << endl;
		cout << "A battle is not possible. Please add or remove restaurants." << endl << endl;
	}
}

vector<string> GetSubVector(vector<string> collection, int start, int end) {
	vector<string> subVector;
	for (int i = start; i < end; i++) {
		subVector = addItem(subVector, collection.at(i));
	}
	return subVector;
}

vector<string> addItem(vector<string> collection, string item) {
	collection.resize(collection.size() + 1);
	collection.at(collection.size() - 1) = item;
	return collection;
}

void Shuffle() {

	if (IsPowerOfTwo((int)restaurants.size())) {

		vector<string> topHalf = GetSubVector(restaurants, ((int) restaurants.size()) / 2, (int) restaurants.size());
		vector<string> lowerHalf = GetSubVector(restaurants, 0, ((int) restaurants.size()) / 2);

		int topHalfIndex = 0;
		int lowerHalfIndex = 0;

		for (int i = 0; i < (int)restaurants.size(); i++) {
			//even
			if (i % 2 == 0) {

				restaurants.at(i) = topHalf.at(topHalfIndex);
				topHalfIndex++;
			}
			//odd
			else {

				restaurants.at(i) = lowerHalf.at(lowerHalfIndex);
				lowerHalfIndex++;
			}
		}
		cout << endl;
	}
	else {
		cout << endl << "The current tournament size (" << (int)restaurants.size() << ") is not a power of two (2, 4, 8...)." << endl;
		cout << "A shuffle is not possible. Please add or remove restaurants." << endl << endl;
	}
}

void Cut() {

	if (TakeInput(0)) {
		if ((latestIntInput != 0) && (latestIntInput != (int) restaurants.size())) {

			int cutPoint = latestIntInput;
			vector<string> topHalf = GetSubVector(restaurants, cutPoint, restaurants.size());

			for (int i = (int)topHalf.size() - 1; i >= 0; i--) {
				restaurants.insert(restaurants.begin(), topHalf.at(i));
				restaurants.erase(restaurants.begin() + ((int)restaurants.size() - 1));
			}
		}
	}
}

//returns the index of the restauraunt if it exists, returns -1 if it does not
int Find(vector<string> collection, string itemName) {

	for (int i = 0; i < (int) collection.size(); i++) {

		if (collection.at(i) == itemName) {
			return i;
		}
	}
	return -1;
}

//recursively determines if argument is a power of two
bool IsPowerOfTwo(int arg0) {
	if (arg0 == 2) {
		return true;
	}
	else if ((arg0 == 0) || (arg0 % 2 != 0)) {
		return false;
	}
	else {
		return IsPowerOfTwo(arg0 / 2);
	}
}

//recursively determines which power of two the argument is after checking that it is a power of two
int WhatPowerOfTwo(int arg0, bool PowerOfTwoChecked) {
	if (!PowerOfTwoChecked) {
		if (IsPowerOfTwo(arg0)) {
			if (arg0 == 2) {
				return 1;
			}
			else {
				return WhatPowerOfTwo(arg0 / 2, true) + 1;
			}
		}
		else {
			return -1;
		}
	}
	else {
		if (arg0 == 2) {
			return 1;
		}
		else {
			return WhatPowerOfTwo(arg0 / 2, true) + 1;
		}
	}
}

bool TakeInput(int inputType) {

	if (inputType == 0) {
		cout << endl;
		cout << "How many restaurants should be taken from the top and put on the bottom? " << endl;

		cin >> latestIntInput;

		if (!cin) {
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');

			cout << endl;
			cout << "The cut number must be between 0 and " << restaurants.size();
			cout << endl;

			return TakeInput(0);
		}
		else if ((latestIntInput >= 0) && (latestIntInput <= (int) restaurants.size())) {
			return true;
		}
		else {
			cout << endl;
			cout << "The cut number must be between 0 and " << restaurants.size();
			cout << endl;

			//function recursively calls itself until valid input received
			return TakeInput(0);
		}
	}
	return false;
}

bool TakeBattleInput(int firstRestaurant) {
	cout << endl;
	cout << "Type \"1\" if you prefer " << restaurantsToBattle.at(firstRestaurant) << " or" << endl;
	cout << "type \"2\" if you prefer " << restaurantsToBattle.at(firstRestaurant + 1) << endl << "Choice: ";

	cin >> latestIntInput;

	if (!cin) {
		cin.clear();
		cin.ignore(std::numeric_limits<int>::max(), '\n');

		cout << endl;
		cout << "Invalid choice";
		cout << endl;

		return TakeBattleInput(0);
	}
	else if ((latestIntInput == 1) || (latestIntInput == 2)) {
		return true;
	}
	else {
		cout << endl;
		cout << "Invalid choice";
		cout << endl;

		//function recursively calls itself until valid input received
		return TakeBattleInput(firstRestaurant);
	}
	return false;
}

void RemoveRestaurant() {

	cout << "What is the name of the restaurant you want to remove?" << endl;
	GetLineNotWS(latestInput);

	int toRemove = Find(restaurants, latestInput);
	if (toRemove == -1) {
		cout << endl << "That restaurant is not on the list, you can not remove it." << endl;
	}
	else {
		restaurants.erase(restaurants.begin() + (toRemove));
		cout << endl << latestInput << " has been removed." << endl;
	}  
	cout << endl;
}

void AddRestaurant() {

	cout << "What is the name of the restaurant you want to add?" << endl;
	GetLineNotWS(latestInput);

	if (Find(restaurants, latestInput) == -1) {
		restaurants = addItem(restaurants, latestInput);
		cout << endl << latestInput << " has been added." << endl;
	}
	else {
		cout << endl << "That restaurant is already on the list, you can not add it again." << endl;
	}
	cout << endl;
}

void DisplayRestaurants() {

	cout << endl << "Here are the current restaurants:" << endl << endl;

	for (string restaurantName : restaurants) {
		cout << "\t\"" << restaurantName << "\"" << endl;
	}

	cout << endl;

}

bool EnterYourSelection() {

	cout << "Enter your selection: ";
	GetLineNotWS(latestInput);
	cout << endl;

	if (latestInput == "quit") {
		return false;
	}
	if (latestInput == "display") {
		DisplayRestaurants();
		return (EnterYourSelection());
	}
	if (latestInput == "add") {
		AddRestaurant();
		return (EnterYourSelection());
	}
	if (latestInput == "remove") {
		RemoveRestaurant();
		return (EnterYourSelection());
	}
	if (latestInput == "cut") {
		Cut();
		return (EnterYourSelection());
	}
	if (latestInput == "shuffle") {
		Shuffle();
		return (EnterYourSelection());
	}
	if (latestInput == "battle") {
		Battle();
		return (EnterYourSelection());
	}
	if (latestInput == "options") {
		DisplayMenu();
		return (EnterYourSelection());
	}
	else {
		cout << "Invalid Selection" << endl;
		DisplayMenu();
		return (EnterYourSelection());
	}
	return true;
}

void DisplayMenu() {

	cout << "Please select one of the following options:" << endl << endl;

	cout << "quit - Quit the program" << endl;
	cout << "display - Display all restaurants" << endl;
	cout << "add - Add a restaurant" << endl;
	cout << "remove - Remove a restaurant" << endl;
	cout << "cut - \"Cut\" the list of restaurants" << endl;
	cout << "shuffle - \"Shuffle\" the list of restaurants" << endl;
	cout << "battle - Begin the tournament" << endl;
	cout << "options - Print the options menu" << endl << endl;
}

void GetLineNotWS(string& inpString) {

	getline(cin, inpString);
	if (inpString.find_first_not_of(" \t") == std::string::npos) {
		getline(cin, inpString);
	}
}

int main() {

	quit = false;

	cout << "Welcome to the restaurant battle!  Enter \"options\" to see options." << endl << endl;

	while (true) {

		if (!EnterYourSelection()) {
			break;
		}
	}

	cout << endl << "Goodbye!";
    return 0;
}

