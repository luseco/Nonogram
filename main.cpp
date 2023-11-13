/*                                                                   |
To Do:
Square of info
fill randomly with input %
make symbols customizable
check if row/column matches description
bug with max desc size where last doesnt get printed
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

void clear(bool clrCmd, bool errMsg) {
	if (clrCmd) {
		system("CLS");
	}
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

int StrToInt(string string) {
	int integer = 0;
	for (int i = 0; i < string.size(); i++) {
		integer = append(integer, string[i] - '0');
	}
	return integer;
}

int CharToInt(char character) {
	return character - '0';
}

bool* getCol(int pos, bool dsp[][50]) {
	bool col[50] = {0};

	for (int i = 0; i < 50; i++) {
		col[i] = dsp[i][pos];
	}
	return col;
}

int intRequest(string consoleText, int max) {
	string userInput;
	int number = 0;

	while (true) {
		number = 0;
		cout << consoleText;
		cin >> userInput;

		for (int i = 0; i < userInput.size(); i++) {
			if (userInput[i] >= '0' && userInput[i] <= '9') {
				number = append(number, CharToInt(userInput[i]));
			}
		}
		if (number > max) {
			clear(1, 0);
			cout << "Maximum input is " << max << "." << endl;
		}
		else if (number == 0) {
			clear(1, 1);
		}
		else {
			break;
		}
	}
	clear(1, 0);
	return number;
}

class Nonogram {
private:
	int rowI = 0, colI = 0;
	int dimension = 0;
	string line;

public:
	const int max = 50;
	int dimensions[2] = {15, 15};
	int rows[50][25] = {0}, cols[50][25] = {0};
	bool display[50][50] = {0};
	int cursor[2] = {0};
	string w = {char(176), char(176)}, b = {char(178), char(178)},
		   wC = "  ", bC = {char(219), char(219)};

	void toggle(int x, int y) {
		display[x][y] = !display[x][y];
	}

	void show() {
		cout << char(201)<< string(dimensions[0] * 2.0, char(205)) 
			 << char(187) << endl;
		for (int i = 0; i < dimensions[1]; i++) {
			cout << char(186);
			for (int ii = 0; ii < dimensions[0]; ii++) {
				if (display[i][ii]) {
					if (i == cursor[0] && ii == cursor[1]) {
						cout << bC;
					}
					else {
						cout << b;
					}
				}
				else {
					if (i == cursor[0] && ii == cursor[1]) {
						cout << wC;
					}
					else {
						cout << w;
					}
					
				}
			}
			cout << char(186);
			for (int ii = 0; rows[i][ii] != 0; ii++) {
				cout << rows[i][ii] << ' ';
			}
			cout << endl;
		}
		
		cout << char(200) << string(dimensions[0] * 2.0, char(205))
			 << char(188) << endl;
		for (int i = 0; i < 25; i++) {
			int counter = 0;
			cout << ' ';

			for (int ii = 0; ii < dimensions[0]; ii++) {
				if (cols[ii][i] != 0) {
					if (cols[ii][i] >= 10) {
						cout << cols[ii][i];
					}
					else {
						cout << ' ' << cols[ii][i];
					}
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

	void clean() {
		for (int i = 0; i < sizeof(display[0]) / 4; i++) {
			for (int ii = 0; ii < sizeof(display[0]) / 4; ii++) {
				display[i][ii] = 0;
			}
		}
	}

	int* dsc(bool dsp[]) {
		int description[25] = { 0 };
		int counter = 0;

		for (int i = 0, ii = 0; i < max; i++) {
			if ((dsp[i] == 0 && counter != 0) || i == max - 1) {
				description[ii] = counter;
				counter = 0;
				ii++;
			}
			else if (dsp[i] == 1) {
				counter++;
			}
		}
		return description;
	}

	void dscDsp() {
		bool list[25];

		for (int i = 0; i < max; i++) {
			for (int ii = 0; ii < max / 2; ii++) {
				list[ii] = getCol(i, display)[ii];
			}

			for (int ii = 0; ii < max / 2; ii++) {
				rows[i][ii] = dsc(display[i])[ii];
				cols[i][ii] = dsc(list)[ii];
			}
			cout << endl;
		}
	}

	void import(ifstream& inputFile) {
		getline(inputFile, line);
		dimensions[0] = 0;
		dimensions[1] = 0;

		for (int i = 0; i < line.size(); i++) {
			if (line[i] == ' ') {
				dimension++;
			}
			else {
				dimensions[dimension] = append(dimensions[dimension],
					CharToInt(line[i]));
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
						CharToInt(line[ii]));
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
						CharToInt(line[ii]));
				}
			}
		}
		inputFile.close();

		int temp;
		temp = dimensions[0];
		dimensions[0] = dimensions[1];
		dimensions[1] = temp;
	}
};

void MainMenu();

void Properties(Nonogram& nono) {
	clear(1, 0);
	bool x = true;
	char input[2];
	string fileName;
	fstream inputFile;

	while (x) {
		nono.show();
		cout << endl << "(d)imensions | (c)lean | (f)ill randomly "
			 << "| (m)ake descriptions" << endl
			 << "(s)ymbols | (i)mport | (b)ack" << endl;
		cin.get(input, 2);

		switch (tryUncap(input[0])) {
		case 'd':
			clear(1, 0);

			nono.dimensions[0] = intRequest("x: ", nono.max);
			nono.dimensions[1] = intRequest("y: ", nono.max);

			nono.cursor[0] = 0;
			nono.cursor[1] = 0;

			nono.clean();
			nono.dscDsp();
			
			system("CLS");
			break;
		case 'c':
			nono.clean();
			clear(1, 0);
			break;
		case 'f':
			break;
		case 'm':
			nono.dscDsp();
			clear(1, 0);
			break;
		case 's':
			break;
		case 'i':
			system("CLS");
		{
			while (true) {
				cout << "File name: ";
				cin >> fileName;
				ifstream inputFile(fileName);
				
				if (inputFile.good()) {
					nono.import(inputFile);
					break;
				}
				else if (fileName == "STOP") {
					break;
				}
				else {
					inputFile.close();
					clear(1, 0);
					cout << "File doesn't exist. Try Again. "
						 << "To exit type STOP." << endl;
				}
			}
		}
			clear(1, 0);
			break;
		case 'b':
			clear(1, 0);
			x = !x;
			break;
		default:
			clear(1, 1);
		}
	}
}

void MainMenu() {
	Nonogram nono;
	char input[2];
		
	while(true) {
		nono.show();

		cout << '\r' << "         (w) up" << endl
			 << "(a) left (s) down (d) right | (q) toggle | "
			 << "(p)roperties (e)xit" << endl;
		cin.get(input, 2);

		switch (tryUncap(input[0])) {
		case 'a': case 'w': case 'd': case 's':
			nono.moveCursor(input[0]);
			clear(1, 0);
			break;
		case 'q':
			nono.toggle(nono.cursor[0], nono.cursor[1]);
			clear(1, 0);
			break;
		case 'p':
			Properties(nono);
			break;
		case 'e':
			return;
		default:
			clear(1, 1);
		}
	}
}

int main() {
	MainMenu();
	return 0;
}