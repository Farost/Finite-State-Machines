#include "FSMTable.h"

void InNumbers(int *n, int *m) {

	std::cout << "Number of states: ";
	while (!(std::cin >> *n) || (*n < 1) || (*n > 20)) {
		std::cout << "ERROR: Not an integer between 1 and 20.\nNumber of states: ";
		std::cin.clear();
		std::cin.ignore(132, '\n');
	}

	std::cout << "Number of letters: ";
	while (!(std::cin >> *m) || (*m < 1) || (*m > 20)) {
		std::cout << "ERROR: Not an integer between 1 and 20.\nNumber of letters: ";
		std::cin.clear();
		std::cin.ignore(132, '\n');
	}
}


void ChangeState(FSMTable *FSM) {
	int n, m, s, l, ifchange = 1;
	char c;
	do {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Do you want to change a cell? (1/0)" << std::endl;
		std::cin >> n;
		if (n != 1 && n != 0)
			std::cout << "ERROR: Type the number '1' or '0'." << std::endl;
		else if (n) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "State: ";
			std::cin >> s;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Letter: ";
			std::cin >> l;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "New cell's info: ";
			std::cin >> c;
			if (!FSM->ChangeTerminal(s, l, c)) std::cout << "ERROR: Cannot change this cell." << std::endl;
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "The matrix have been changed. Do you want to print it? (1/0)" << std::endl;
				std::cin >> m;
				if (m) FSM->PrintMatrix();
			}
		}
		else ifchange = 0;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (ifchange);
}


void ChangeStatesName(FSMTable *FSM) {
	int n, m, ifchange = 0;
	char c, nw;
	do {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Do you want to change a state's name? (1/0)" << std::endl;
		std::cin >> n;
		if (n != 1 && n != 0)
			std::cout << "ERROR: Type the number '1' or '0'." << std::endl;
		else if (n) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Prev state's name: ";
			std::cin >> c;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "New state's name: ";
			std::cin >> nw;
			if (!FSM->ChangeTerminalAll(c, nw))
				std::cout << "State's names duplicate or they are the same." << std::endl;
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Do you want to print matrix? (1/0)" << std::endl;
				std::cin >> m;
				if (m) FSM->PrintMatrix();
			}
		}
		else ifchange = 1;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (!ifchange);
}


void Task1(FSMTable *FSM) {
	FSM->MakeRightGrammar();
	FSM->MakeLeftGrammar();
	std::cout << "Right grammar:" << std::endl;
	if (!FSM->PrintGrammar('r')) std::cout << "Error in printing Right grammar." << std::endl;
	std::cout << "Left grammar:" << std::endl;
	if (!FSM->PrintGrammar('l')) std::cout << "Error in printing Left grammar." << std::endl;
}


void Task2(FSMTable *FSM) {
	std::cout << "Our language: every 3rd symbol - 1." << std::endl;
	FSM->MakeMatrixTask2();
	std::cout << "Printing the Task 2 Matrix:" << std::endl;
	FSM->PrintMatrix();
	FSM->MakeRightGrammar();
	FSM->MakeLeftGrammar();
	std::cout << "Right grammar:" << std::endl;
	FSM->PrintGrammar('r');
	std::cout << "Left grammar:" << std::endl;
	FSM->PrintGrammar('l');
}

void Task3(FSMTable *FSM) {
	std::cout << "Our language - Fortran's integers. Latin's alphabet & numbers." << std::endl;
	FSM->MakeMatrixTask3();
	std::cout << "Printing the Task 3 Matrix:" << std::endl;
	FSM->PrintMatrix();
	FSM->MakeRightGrammar();
	FSM->MakeLeftGrammar();
	std::cout << "Right grammar:" << std::endl;
	FSM->PrintGrammar('r');
	std::cout << "Left grammar:" << std::endl;
	FSM->PrintGrammar('l');

	int test;
	char k;
	std::cout << "Do you want to type a word? (0/1)" << std::endl;
	std::cin >> k;
	if (k == '1') do {
		test = FSM->TestTask3();
		if (!test) std::cout << "ERROR: First symbol is incorrect. Needed I, J, K, L, M or N (or low)." << std::endl;
		else if (test == -1) std::cout << "ERROR: Second symbol is incorrect." << std::endl
			<< "Use the whole latin alphabet and numbers." << std::endl;
		else if (test == -2) std::cout << "ERROR: Third or futher symbol is incorrect." << std::endl
			<< "Use the whole latin alphabet and numbers." << std::endl;
		else std::cout << "Your word is ok!" << std::endl;

		std::cout << "Do you want to type another word? (0/1)" << std::endl;
		std::cin >> k;
	} while (k == '1');
	
}


int main()
{
	char task;
	int br = 0;
	FSMTable Task1FSM, Task2FSM, Task3FSM;
	do {
		std::cout << "What task do you want to check?" << std::endl;
		std::cin >> task;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (task) {
		case '0':
			br = 1;
			break;
		case '1':
			int n, m;
			InNumbers(&n, &m);
			if (!Task1FSM.MakeMatrixUser(n, m))
				std::cout << "ERROR: Cannot make matrix." << std::endl;
			else {
				std::cout << "Matrix made successfully." << std::endl;
				Task1FSM.PrintMatrix();
			}

			ChangeState(&Task1FSM);
			ChangeStatesName(&Task1FSM);

			Task1(&Task1FSM);
			break;

		case '2':
			Task2(&Task2FSM);
			break;

		case '3':
			Task3(&Task3FSM);
			break;

		default:
			std::cout << "I don't understand you. Please retry." << std::endl;
			break;
		}
	} while (!br);

	std::cout << "Thank you, goodbye!" << std::endl;
	system("pause");
    return 0;
}

