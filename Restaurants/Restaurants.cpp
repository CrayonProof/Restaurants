// Restaurants.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void DisplayMenu();
void EnterYourSelection();
void DisplayMenu();
void DisplayRestaurants();
void AddRestaurant();
void RemoveRestaurant();
int Find(string name);
void GetLineNotWS(string& inpString);

bool quit = false;
string latestInput;
vector<string> restaurants;
istringstream inSS;
int toRemove;

//returns the index of the restauraunt if it exists, returns -1 if it does not
int Find(vector<string> collection, string itemName) {

	for (int i = 0; i < collection.size(); i++) {

		if (collection.at(i) == itemName) {
			return i;
		}
	}
	return -1;
}

void RemoveRestaurant() {

	cout << "What is the name of the restaurant you want to remove?" << endl;
	GetLineNotWS(latestInput);

	toRemove = Find(restaurants, latestInput);
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
		restaurants.resize(restaurants.size() + 1);
		restaurants.at(restaurants.size()-1) = latestInput;
		cout << endl << latestInput << " has been added." << endl;
	}
	else {
		cout << endl << "That restaurant is already in the list, you can not add it again." << endl;
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

void EnterYourSelection() {

	cout << "Enter your selection: ";
	GetLineNotWS(latestInput);
	cout << endl;

	if (latestInput == "quit") {
		quit = true;
	}
	if (latestInput == "display") {
		DisplayRestaurants();
		EnterYourSelection();
	}
	if (latestInput == "add") {
		AddRestaurant();
		EnterYourSelection();
	}
	if (latestInput == "remove") {
		RemoveRestaurant();
	}
	if (latestInput == "cut") {

	}
	if (latestInput == "shuffle") {

	}
	if (latestInput == "battle") {

	}
	if (latestInput == "options") {
		DisplayMenu();
		EnterYourSelection();
	}

}

void DisplayMenu() {

	cout << "Menu: Please select one of the following options:" << endl << endl;

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

	cout << "Welcome to the restaurant battle!  Enter \"options\" to see options." << endl << endl;

	while (!quit) {

		EnterYourSelection();
	}

    return 0;
}

