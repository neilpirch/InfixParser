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
	struct token {
		string	symbol;
		string	tokenType;  //enum, op, eof
		int		intValue;
		int		precedence;
		bool	isUnary;	// inc, dec, neg, not -> true
	};
	Parser();
	void Parse(string);
	void ParseOperator(char);
	void Calculate();
	void Display();

private:
	// these functions will move to be inside the parser
	bool isOperator(char op) const {
		return OPERATORS.find(op) != string::npos;
	}
	bool isDouble(char op) const {
		return DOUBLES.find(op) != string::npos;
	}
	int precedence(char op) const {
		return PRECEDENCE[OPERATORS.find(op)];
	}
	
	// these variables won't matter anymore
	static const string OPERATORS;
	//for checking if an operator could be double
	static const string DOUBLES;
	static const int PRECEDENCE[];
	stack<int> operandStack;
	stack<char> operatorStack;
};

#endif
