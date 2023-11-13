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
public:
	const int max = 50;
	int dimensions[2] = {10, 10};
	int rows[50][25] = {0}, cols[50][25] = {0};
	bool display[50][50] = {0};
	int cursor[2] = {0};
	char w = char(176), b = char(178), wC = ' ', bC = char(219);

	void toggle(int x, int y) {
		display[x][y] = !display[x][y];
	}

	void show() {
		cout << char(201) << string(dimensions[0] * 2.0, 
				char(205)) << char(187) << endl;
		for (int i = 0; i < dimensions[1]; i++) {
			bool matching = true;
			
			cout << char(186);
			for (int ii = 0; ii < dimensions[0]; ii++) {
				if (display[i][ii]) {
					if (i == cursor[0] && ii == cursor[1]) {
						cout << bC << bC;
					}
					else {
						cout << b << b;
					}
				}
				else {
					if (i == cursor[0] && ii == cursor[1]) {
						cout << wC << wC;
					}
					else {
						cout << w << w;
					}
				}
			}
			cout << char(186);
			for (int ii = 0; ii < max / 2; ii++) {
				if (dsc(display[i])[ii] != rows[i][ii]) {
					matching = false;
				}
			}

			if (matching) {
				cout << char(157) << ' ';
			}
			else {
				cout << "O ";
			}

			for (int ii = 0; rows[i][ii] != 0; ii++) {
				cout << rows[i][ii] << ' ';
			}
			cout << endl;
		}
		
		cout << char(200) << string(dimensions[0] * 2.0, 
				char(205)) << char(188) << endl << ' ';
		
		for (int i = 0; i < dimensions[0]; i++) {
			bool matching = true;
			bool list[50] = { 0 };

			for (int ii = 0; ii < 50; ii++) {
				list[ii] = getCol(i, display)[ii];
			}
			
			for (int ii = 0; ii < 25; ii++) {
				if (dsc(list)[ii] != cols[i][ii]) {
					matching = false;
				}
			}

			if (matching) {
				cout << ' ' << char(157);
			}
			else {
				cout << " O";
			}
		}
		cout << endl;

		for (int i = 0; i < max; i++) {
			int counter = 0;
			cout << ' ';

			for (int ii = 0; ii < dimensions[0]; ii++) {
				if (cols[ii][i] != 0) {
					if (cols[ii][i] >= 10 && cols[ii][i] <= 35) {
						cout << ' ' << char(cols[ii][i] + 55);
					}
					else if (cols[ii][i] >= 36) {
						cout << ' ' << char(cols[ii][i] + 61);
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
		for (int i = 0; i < max; i++) {
			for (int ii = 0; ii < max; ii++) {
				display[i][ii] = 0;
			}
		}
		cursor[0] = 0;
		cursor[1] = 0;
	}

	int* dsc(bool dsp[]) {
		int description[25] = { 0 };
		int counter = 0;

		for (int i = 0, ii = 0; i < max; i++) {
			if (i == max - 1 && dsp[i] == 1) {
				counter++;
				description[ii] = counter;
			}
			if ((dsp[i] == 0 && counter != 0)) {
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
		bool list[50] = { 0 };

		for (int i = 0; i < max; i++) {
			for (int ii = 0; ii < max; ii++) {
				list[ii] = getCol(i, display)[ii];
			}

			for (int ii = 0; ii < max/2; ii++) {
				rows[i][ii] = dsc(display[i])[ii];
				cols[i][ii] = dsc(list)[ii];
			}
			cout << endl;
		}
	}

	void import(ifstream& inputFile) {
		int rowI = 0, colI = 0;
		int dimension = 0;
		string line;
		getline(inputFile, line);

		dimensions[0] = 0;
		dimensions[1] = 0;

		for (int i = 0; i < 50; i++) {
			for (int ii = 0; ii < 25; ii++) {
				rows[i][ii] = 0;
				cols[i][ii] = 0;
			}
		}

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

	void fillRand(double prc) {
		srand(time(0));
		prc = prc / 100;
		int grid = dimensions[0] * dimensions[1];

		for (int i = 0; i < int(grid * prc + 0.5);) {
			int z = rand() % (grid);
			int x = z / dimensions[0], y = z % dimensions[0];
			if (display[x][y] == 0) {
				toggle(x, y);
				i++;
			}
		}
	}
};

void MainMenu();

void Properties(Nonogram& nono) {
	clear(1, 0);
	bool x = true;
	char input[2];

	while (x) {
		nono.show();
		cout << endl << "(d)imensions | (c)lean  | (f)ill randomly "
			 << "| (m)ake descriptions" << endl
			 << "(s)ymbols    | (i)mport | (b)ack" << endl;
		cin.get(input, 2);

		switch (tryUncap(input[0])) {
		case 'd':
			clear(1, 0);

			nono.dimensions[0] = intRequest("x: ", nono.max);
			nono.dimensions[1] = intRequest("y: ", nono.max);

			nono.clean();
			nono.dscDsp();
			
			system("CLS");
			break;
		case 'c':
			nono.clean();
			clear(1, 0);
			break;
		case 'f':
		{
			double prc;
			clear(1, 0);
			prc = intRequest("Percentage of the grid to fill: ", 100);

			nono.clean();
			nono.fillRand(prc);
			break;
		}
		case 'm':
			nono.dscDsp();
			clear(1, 0);
			break;
		case 's':
		{
			system("CLS");
			string symbol;
			string UserSymbol;

			while (true) {
				cout << "Choose the symbol to change:" << endl
					<< "(1) white | (2) black | "
					<< "(3) white cursor | (4) black cursor" << endl;
				cin >> symbol;

				if (symbol[0] >= '1' && symbol[0] <= '4') {
					clear(1, 0);
					break;
				}
				else {
					clear(1, 1);
				}
			}
			cout << "Symbol: ";
			cin >> UserSymbol;
			switch (symbol[0]) {
			case '1':
				nono.w = UserSymbol[0];
				break;
			case '2':
				nono.b = UserSymbol[0];
				break;
			case '3':
				nono.wC = UserSymbol[0];
				break;
			case '4':
				nono.bC = UserSymbol[0];
				break;
			}
			clear(1, 0);
			break;
		}
		case 'i':
		{
			nono.clean();
			system("CLS");
			string fileName;
		
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
						 << "To exit type: STOP" << endl;
				}
			}
			clear(1, 0);
			break;
		}
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

	nono.fillRand(50);
	nono.dscDsp();
	nono.clean();
	system("CLS");

	int Len = 30;
	cout << char(201) << string(Len, char(205)) << char(187) << endl
		 << "  Name: Ibraheem Ahmed" << endl
		 << "  Studentnumber: 4147936" << endl
		 << "  Course: Computer Science" << endl
		 << "  Date: 13/11/2023" << endl
		 << "  Functionality: " << endl
		 << "  " << endl
		 << "  " << endl
		 << char(200) << string(Len, char(205)) << char(188) << endl
		 << endl;

	while(true) {
		nono.show();

		cout << endl << "         (w) up" << endl
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