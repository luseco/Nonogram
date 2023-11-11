#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

void clear(bool errMsg) {
	system("CLS");
	if (errMsg) {
		cout << "Invalid input. Try again." << endl;
	}
	cin.clear();
	cin.ignore(10000, '\n');
}

char tryUncap(char character) {
	if (character >= 'A' && character <= 'Z') {
		return character + ' ';
	}
	else {
		return character;
	}
}

int append(int integer, int toAppend) {
	return integer * 10 + toAppend;
}

int SToInt(string string) {
	int integer = 0;
	for (int i = 0; i < string.size(); i++) {
		integer = append(integer, string[i] - '0');
	}
	return integer;
}

int CToInt(char character) {
	return character - '0';
}

class Nonogram {
private:
	int rowI = 0, colI = 0;
	int dimension = 0;
	string line;

public:
	ifstream inputFile;
	const int max = 50;
	int dimensions[2] = { 0 };
	int rows[50][25] = { 0 }, cols[50][25] = { 0 };
	bool display[50][50] = { 0 };
	int cursor[2] = { 0 };
	
	Nonogram() {
		dimensions[0] = 13;
		dimensions[1] = 13;
	}

	Nonogram(string fileName) : inputFile(fileName) {
		getline(inputFile, line);
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == ' ') {
				dimension++;
			}
			else {
				dimensions[dimension] = append(dimensions[dimension],
										CToInt(line[i]));
			}
		}

		for (int i = 0; i < dimensions[0]; i++) {
			getline(inputFile, line);
			for (int ii = 0; ; ii++) {
				if (line[ii] == ' ') {
					rowI++;
				}
				else if (line[ii] == '0') {
					rowI = 0;
					break;
				}
				else {
					rows[i][rowI] = append(rows[i][rowI],
									CToInt(line[ii]));
				}
			}
		}

		for (int i = 0; i < dimensions[1]; i++) {
			getline(inputFile, line);
			for (int ii = 0; ; ii++) {
				if (line[ii] == ' ') {
					colI++;
				}
				else if (line[ii] == '0') {
					colI = 0;
					break;
				}
				else {
					cols[i][colI] = append(cols[i][colI],
									CToInt(line[ii]));
				}
			}
		}
		inputFile.close();

		int temp;
		temp = dimensions[0];
		dimensions[0] = dimensions[1];
		dimensions[1] = temp;
	}

	void toggle(int x, int y) {
		display[x][y] = !display[x][y];
	}

	void show() {
		cout << string(dimensions[0] * 2 + 2, '_') << endl;
		for (int i = 0; i < dimensions[1]; i++) {
			cout << '|';
			for (int ii = 0; ii < dimensions[0]; ii++) {
				if (display[i][ii]) {
					if (i == cursor[0] && ii == cursor[1]) {
						cout << char(219) << char(219);
					}
					else {
						cout << "##";
					}
				}
				else {
					if (i == cursor[0] && ii == cursor[1]) {
						cout << "  ";
					}
					else {
						cout << "[]";
					}
					
				}
			}
			cout << "| ";
			for (int ii = 0; rows[i][ii] != 0; ii++) {
				cout << rows[i][ii] << ' ';
			}
			cout << endl;
		}
		cout << string(dimensions[0] * 2 + 2, 238) << endl;
		
		for (int i = 0; i < 20; i++) {
			int counter = 0;
			for (int ii = 0; ii < dimensions[0]; ii++) {
				if (cols[ii][i] != 0) {
					cout << ' ' << cols[ii][i];
				}
				else {
					cout << "  ";
				}
				counter += cols[ii][i];
			}
			
			if (counter == 0) {
				break;
			}
			cout << endl;
		}
	}

	int intRequest(string consoleText) {
		string userInput;
		int number = 0;

		cout << consoleText;
		cin >> userInput;

		for (int i = 0; i < userInput.size(); i++) {
			if (number <= max) {
				if (userInput[i] >= '0' || userInput[i] <= '9') {
					number = append(number, CToInt(userInput[i]));
				}
			}
			else {
				number = max;
			}
		}
		return number;
	}

	void moveCursor(char direction) {
		if (direction == 'a' && cursor[1] > 0) {
			cursor[1]--;
		}
		else if (direction == 'w' && cursor[0] > 0) {
			cursor[0]--;
		}
		else if (direction == 'd' && cursor[1] < dimensions[0] - 1) {
			cursor[1]++;
		}
		else if (direction == 's' && cursor[0] < dimensions[1] - 1) {
			cursor[0]++;
		}
	}
};

void MainMenu();

void Properties(Nonogram& nono) {
	clear(0);
	bool x = true;
	char input[2];

	while (x) {
		nono.show();

		cout << endl << "(d)imensions (c)lean (f)ill randomly "
			 << "(m)ake descriptions s(y)mbols | (b)ack" << endl;
		cin.get(input, 2);

		switch (tryUncap(input[0])) {
		case 'd':
			nono.dimensions[0] = intRequest("x: ", nono);
			nono.dimensions[1] = intRequest("y: ", nono);
			break;
		case 'c':
			for (int i = 0; i < sizeof(nono.display[0]) / 4; i++) {
				for (int ii = 0; ii < sizeof(nono.display[0]) 
					/ 4; ii++) {
					nono.display[i][ii] = { 0 };
				}
			}
			clear(0);
			break;
		case 'f':
			break;
		case 'm':
			break;
		case 'y':
			break;
		case 'b':
			clear(0);
			x = !x;
			break;
		default:
			clear(1);
		}
	}
}

void MainMenu() {
	Nonogram nono("pi.txt");
	char input[2];
		
	while(true) {
		nono.show();

		cout << endl << "left (a) up (w) right (d) down (s) |"
			 << " toggle (q) | (p)roperties (e)xit" << endl;
		cin.get(input, 2);

		switch (tryUncap(input[0])) {
		case 'a': case 'w': case 'd': case 's':
			nono.moveCursor(input[0]);
			clear(0);
			break;
		case 'q':
			nono.toggle(nono.cursor[0], nono.cursor[1]);
			clear(0);
			break;
		case 'p':
			Properties(nono);
			break;
		case 'e':
			return;
		default:
			clear(1);
		}
	}
}

int main() {
	//MainMenu();
	string s;
	cin >> s;
	cout << s.size();
	return 0;
}