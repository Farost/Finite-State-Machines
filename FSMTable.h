#pragma once
/*
Матричное представление конечного автомата.
Горизонталь: буквы. Вертикаль: состояния.
Задание 1: Вариант 3. Написать программу, строящую лево- и правостороннюю грамматику:
A0::=B, 1A::=C, As::=0, 0B::=D, 1B::=B, Bs::=0, 0C::=C, 1C::=D, Cs::=0, 0D::=D, 1D::=D, Ds::=1. 
Программа должна поддерживать смену нетерминалов в матрице конечного автомата.
  0 1
A|B C 0
B|D B 0
C|C D 0
D|D D 1
*/

#define EPS 'ɛ'
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

class FSMTable
{
public:
	FSMTable();
	FSMTable(const FSMTable& fsm);
	~FSMTable();
	
	int MakeMatrixUser(const int n, const int m);
	void MakeMatrixTask2();
	void MakeMatrixTask3();
	int TestTask3();
	void PrintMatrix();
	int ChangeTerminalAll(const char bf, const char nw);
	int ChangeTerminal(const int n, const int m, const char nw);
	void MakeLeftGrammar();
	void MakeRightGrammar();
	int PrintGrammar(const char rl);
	int nstates = 0, nletters = 0;

private:
	
	char *states, *letters;
	char **matrix;
	int MakeStatesArray();
	int CheckTerminal(const char temp);
	int CheckLetter(const char temp);
	std::string *leftGrammar;
	std::string *rightGrammar;
	
};

