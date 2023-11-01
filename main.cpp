#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

void Clear(bool errMsg) {
	if (errMsg) {
		cout << "Invalid input. Try again." << endl;
	}
	cin.clear();
	cin.ignore(10000, '\n');
}

char UnCap(char character) {
	if (character >= 'A' && character <= 'Z') {
		return character + ' ';
	}
	else {
		return character;
	}
}

void Properties() {
	char input[1];
	
	cout << "(d)imensions s(y)mbols (s)top" << endl;
	cin.get(input, 2);

	switch (UnCap(input[0])) {
	case 'd':
		break;
	case 'y':
		break;
	case 's':
		break;
	default:
		Clear(1);
		Properties();
	}
}

void MainMenu() {
	char input[1];

	cout << "(c)ursor (p)roperties (s)top" << endl;
	cin.get(input, 2);
	
	switch (UnCap(input[0])) {
	case 'c':
		break;
	case 'p':
		Clear(0);
		Properties();
	case 's':
		break;
	default:
		Clear(1);
		MainMenu();
	}
}

int main() {
	MainMenu();
	return 0;
}