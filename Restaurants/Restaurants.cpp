// Restaurants.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void DisplayMenu();
void EnterYourSelection();
void DisplayMenu();

bool quit = false;
string latestInput;

void EnterYourSelection() {

	cout << "Enter your selection: ";
	cin >> latestInput;
	cout << endl;

	if (latestInput == "quit") {
		quit = true;
	}
	if (latestInput == "display") {

	}
	if (latestInput == "add") {

	}
	if (latestInput == "remove") {

	}
	if (latestInput == "cut") {

	}
	if (latestInput == "shuffle") {

	}
	if (latestInput == "battle") {

	}
	if (latestInput == "options") {
		DisplayMenu();
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

	EnterYourSelection();
}

int main() {

	cout << "Welcome to the restaurant battle!  Enter \"options\" to see options." << endl << endl;

	while (!quit) {

		EnterYourSelection();
	}

    return 0;
}

