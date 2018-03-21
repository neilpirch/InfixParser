#ifndef PARSER_H_
#define PARSER_H_

#pragma once
#include <stack>
#include <iostream>
#include <iomanip>
#include <string>
#include "Syntax_Error.h"

using namespace std;

class Parser
{
public:
	Parser();
	void Parse(string);
	void ParseOperator(char);
	void Calculate();
	void Display();

private:
	bool isOperator(char op) const {
		return OPERATORS.find(op) != string::npos;
	}
	bool isDouble(char op) const {
		return DOUBLES.find(op) != string::npos;
	}
	int precedence(char op) const {
		return PRECEDENCE[OPERATORS.find(op)];
	}
	
	static const string OPERATORS;
	//for checking if an operator could be double
	static const string DOUBLES;
	static const int PRECEDENCE[];
	stack<int> operandStack;
	stack<char> operatorStack;
};

#endif
