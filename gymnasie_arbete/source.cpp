#include <iostream>

#include "mainGame.h"

using namespace std;

#undef main

int main() {
	cout << "Hello world." << endl;

	mainGame mainApp(420, 420);
	mainApp.run();

	return 0;
}