#include "stdafx.h"
#include "FSMTable.h"

FSMTable::FSMTable()
{
	states = nullptr;
	letters = nullptr;
	matrix = nullptr;
	leftGrammar = nullptr;
	rightGrammar = nullptr;
}

FSMTable::FSMTable(const FSMTable& fsm) {
	nstates = fsm.nstates;
	nletters = fsm.nletters;
	int i = 0;
	if (fsm.states) {
		states = new char[nstates];
		for (; i < nstates; ++i)
			states[i] = fsm.states[i];
	}
	if (fsm.letters) {
		letters = new char[nletters + 2];
		for (i = 0; i <= nletters; ++i)
			letters[i] = fsm.letters[i];
	}
	if (fsm.leftGrammar) {
		leftGrammar = new std::string[nstates];
		for (i = 0; i < nstates; ++i)
			leftGrammar[i] = fsm.leftGrammar[i];
	}
	if (fsm.rightGrammar) {
		rightGrammar = new std::string[nstates];
		for (i = 0; i < nstates; ++i)
			rightGrammar[i] = fsm.rightGrammar[i];
	}
	if (fsm.matrix) {
		matrix = new char*[nstates];
		for (i = 0; i < nstates; ++i) {
			matrix[i] = new char[nletters];
			matrix[i] = fsm.matrix[i];
		}
	}
}


FSMTable::~FSMTable()
{
	if (matrix) {
		for (int i = 0; i < nstates; ++i)
			delete[] matrix[i];
		delete[] matrix;
	}
	if (states) delete[] states;
	if (letters) delete[] letters;
	if (leftGrammar) delete[] leftGrammar;
	if (rightGrammar) delete[] rightGrammar;
}


int FSMTable::CheckTerminal(const char temp) {
	int k = 0;
	for (int i = 0; i < nstates; ++i)
		if (temp == states[i]) ++k;
			
	if (!k) return 0;
	return 1;
}


int FSMTable::CheckLetter(const char temp) {
	int k = 0;
	for (int i = 0; i < nletters; ++i)
		if (temp == letters[i]) ++k;

	if (!k) return 0;
	return 1;
}


int FSMTable::MakeStatesArray() {
	states = new char[nstates];
	letters = new char[nletters + 2];

	char* temp = new char[10];
	std::cout << "Type " << nstates << " states' names:" << std::endl;
	std::cin >> temp;
	
	int i = 0;
	for (; i < nstates; ++i)
		states[i] = temp[i];
	delete[] temp;

	temp = new char[10];
	std::cout << "Type " << nletters << " letters' names:" << std::endl;
	std::cin >> temp;

	for (i = 0; i < nletters; ++i)
		letters[i] = temp[i];
	delete[] temp;
	letters[nletters] = '!';

	std::cout << "You've entered states: " << std::endl;
	for (i = 0; i < (nstates - 1); ++i)
		std::cout << states[i] << ", ";
	std::cout << states[i] << "." << std::endl;

	std::cout << "You've entered letters: " << std::endl;
	for (i = 0; i < (nletters - 1); ++i)
		std::cout << letters[i] << ", ";
	std::cout << letters[i] << "." << std::endl;

	return 1;
}


int FSMTable::MakeMatrixUser(const int n, const int m = 2) {
	if (n < 0 || m < 2) return 0;
	nstates = n, nletters = m;
	if (!MakeStatesArray()) return 0;
	matrix = new char*[nstates];
	char temp;
	std::cout << "Fullfill the matrix:" << std::endl;
	for (int i = 0; i < nstates; ++i) {
		matrix[i] = new char[nletters + 1];
		for (int j = 0; j <= nletters; ++j) {

			if (j == nletters) do {
				std::cout << states[i] << letters[j] << ": ";
				std::cin >> temp;
			} while (temp != '1' && temp != '0');

			else do {
				std::cout << states[i] << letters[j] << ": ";
				std::cin >> temp;
			} while (!CheckTerminal(temp));

			matrix[i][j] = temp;
		}
	}
	return 1;
}


void FSMTable::PrintMatrix() {
	if (!nstates || !nletters) std::cout << "Matrix is empty." << std::endl;
	else {
		std::cout << "  ";
		for (int i = 0; i <= nletters; ++i)
			std::cout << letters[i] << " ";
		std::cout << std::endl;
		for (int i = 0; i < nstates; ++i) {
			std::cout << states[i] << " ";
			for (int j = 0; j <= nletters; ++j) {
				std::cout << matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
}


void FSMTable::ChangeTerminalAll(const char bf, const char nw) {
	for (int i = 0; i < nstates; ++i) {
		if (states[i] == bf) states[i] = nw;
		for (int j = 0; j < nletters; ++j) {
			if (matrix[i][j] == bf) matrix[i][j] = nw;
		}
	}
}


int FSMTable::ChangeTerminal(const int n, const int m, const char nw) {
	if (n < 0 || n > nstates - 1 || m < 0 || m > nletters) return 0;

	if (m == nletters) 
		if (nw != '0' && nw != '1') return 0;
	if (m < nletters && !CheckTerminal(nw)) return 0;

	matrix[n][m] = nw;
	return 1;
}


void FSMTable::MakeRightGrammar() {
	rightGrammar = new std::string[nstates];
	std::string temp = "";
	int flag = 0;
	for (int i = 0; i < nstates; ++i) {
		temp.clear();
		temp += states[i];
		temp += "::=";
		flag = 0;
		for (int j = 0; j <= nletters; ++j) 
			if (matrix[i][j] != ' ' && !(j == nletters && matrix[i][j] == '0')) {
				if (flag) temp += '|';
				if (j != nletters) temp += letters[j];
				if (j == nletters) temp += EPS;
				else temp += matrix[i][j];
				++flag;
			}
		rightGrammar[i] = temp;
	}
}


void FSMTable::MakeLeftGrammar() {
	leftGrammar = new std::string[nstates];
	std::string temp = "";
	int flag = 0;
	for (int i = 0; i < nstates; ++i) {
		temp.clear();
		temp += states[i];
		temp += "::=";
		flag = 0;
		for (int k = 0; k < nstates; ++k) {
			for (int j = 0; j < nletters; ++j)
				if (matrix[k][j] == states[i]) {
					if (flag) temp += '|';
					temp += states[k];
					temp += letters[j];
					++flag;
				}
		}
		if (!flag) temp += EPS;
		leftGrammar[i] = temp;
	}
}

int FSMTable::PrintGrammar(const char rl) {
	std::string* it;
	if (rl == 'r') it = rightGrammar;
	else if (rl == 'l') it = leftGrammar;
	else return 0;
	for (int i = 0; i < nstates; ++i)
		std::cout << it[i] << std::endl;
	return 1;
}


void FSMTable::MakeMatrixTask2() {
	nstates = 6, nletters = 2;
	states = new char[nstates];
	states[0] = 'A';
	states[1] = 'B';
	states[2] = 'C';
	states[3] = 'D';
	states[4] = 'E';
	states[5] = 'F';
	letters = new char[nletters + 2];
	letters[0] = '0';
	letters[1] = '1';
	letters[2] = 'e';
	matrix = new char*[nstates];
	for (int i = 0; i < nstates; ++i)
		matrix[i] = new char[nletters + 1];
	matrix[0][0] = 'B', matrix[0][1] = 'C', matrix[0][2] = '0';
	matrix[1][0] = 'E', matrix[1][1] = 'D', matrix[1][2] = '1';
	matrix[2][0] = 'E', matrix[2][1] = 'D', matrix[2][2] = '1';
	matrix[3][0] = 'A', matrix[3][1] = 'F', matrix[3][2] = '1';
	matrix[4][0] = 'A', matrix[4][1] = 'F', matrix[4][2] = '1';
	matrix[5][0] = 'B', matrix[5][1] = 'C', matrix[5][2] = '1';
}


void FSMTable::MakeMatrixTask3() {
	nstates = 2, nletters = 62;
	states = new char[nstates];
	states[0] = 'S';
	states[1] = 'I';
	letters = new char[nletters + 2];
	for (char ch = 65; ch < 91; ++ch)
		letters[ch - 65] = ch;
	for (char ch = 97; ch < 123; ++ch)
		letters[ch - 71] = ch;
	for (char ch = 48; ch < 58; ++ch)
		letters[ch + 4] = ch;
	letters[nletters] = '!';
	matrix = new char*[nstates];

	matrix[0] = new char[nletters + 1];
	for (int j = 0; j < nletters; ++j) 
		if (letters[j] == 'I' || letters[j] == 'i' || letters[j] == 'J' || letters[j] == 'j' ||
			letters[j] == 'K' || letters[j] == 'k' || letters[j] == 'L' || letters[j] == 'l' ||
			letters[j] == 'M' || letters[j] == 'm' || letters[j] == 'N' || letters[j] == 'n')
			matrix[0][j] = 'I';
		else matrix[0][j] = ' ';
	
	matrix[1] = new char[nletters + 1];
	for (int j = 0; j <= nletters; ++j) {
		matrix[1][j] = 'I';
	}

	matrix[0][nletters] = '0';
	matrix[1][nletters] = '1';
}