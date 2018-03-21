#include "stdafx.h"
#include "Parser.h"
#include <sstream>
#include <math.h>


const string Parser::OPERATORS = "><+-*/%^!()[]{}";
const string Parser::DOUBLES = "<>=&|+-!";
const int Parser::PRECEDENCE[] = { 4, 4, 5, 5, 6, 6, 6, 7, 8, -1, -1, -1, -1, -1, -1 };
Parser::Parser()
{
}

void Parser::Parse(string infixExpr)
{
	char next_token;
	char next_token1;
	cout << infixExpr << " = ";
	char tmp = 'F';
	istringstream infix_tokens(infixExpr);
	while (infix_tokens >> next_token)
	{
		if (tmp != 'F') {
			bool doubled = true;
			if (tmp == '+' && next_token == '+')
				ParseOperator('I');
			else if (tmp == '-' && next_token == '-')
				ParseOperator('D');
			else if (tmp == '>' && next_token == '=')
				ParseOperator('G');
			else if (tmp == '<' && next_token == '=')
				ParseOperator('L');
			else if (tmp == '=' && next_token == '=')
				ParseOperator('E');
			else if (tmp == '!' && next_token == '=')
				ParseOperator('N');
			else if (tmp == '&' && next_token == '&')
				ParseOperator('A');
			else if (tmp == '|' && next_token == '|')
				ParseOperator('O');
			else
			{
				doubled = false;
				ParseOperator(tmp);
			}
			tmp = 'F'; //Clear tmpval
			if (doubled)
				continue;
		}
		if (isdigit(next_token))
		{
			infix_tokens.putback(next_token);
			int value;
			infix_tokens >> value;
			operandStack.push(value);
		}
		else if (isDouble(next_token))
		{
			tmp = next_token;
		}
		else if (isOperator(next_token))
		{
			ParseOperator(next_token);
		}
		else {
			throw Syntax_Error("Invalid Character Encountered");
		}
	}

	while (!operatorStack.empty())
	{
		Calculate();
	}

	Display();

	return;
}

void Parser::ParseOperator(char op)
{
	string a = "Expression can't start with a closing parenthesis, >, or < @ char: 0";
	
	//This try catch section will catch the errors of statements starting with ), ], }, <, >

	if (operatorStack.empty() || (op == '(') || (op == '[') || (op == '{'))
	{
		if (op == ')' || op == ']' || op == '}' || op == '<' || op == '>')
			try {
			if (op == ')' || op == ']' || op == '}')
			{
				throw op;
			}
		}
		catch (char op)
		{
			cout << a << endl;
		}

		try {
			if (op == '<' || op == '>')
			{
				throw op;
			}
		}
		catch (char op)
		{
			cout << a << endl;
		}
		operatorStack.push(op);
	}
	else
	{
		if (precedence(op) > precedence(operatorStack.top())) {
			operatorStack.push(op);
		}
		else {
			// Pop all stacked operators with equal
			// or higher precedence than op.
			while (!operatorStack.empty()
				&& (operatorStack.top() != '(')
				&& (operatorStack.top() != '[')
				&& (operatorStack.top() != '{')
				&& (precedence(op) <= precedence(operatorStack.top())))
			{
				Calculate();

			}
			// assert: Operator stack is empty or 
			//         top of stack is '(' or current
			//         operator precedence > top of stack operator
			//         precedence;
			if (op == ')') {
				if (!operatorStack.empty() && (operatorStack.top() == '(')) {
					operatorStack.pop();
				}
				else { throw Syntax_Error("Unmatched close parentheses"); }
			}
			else if (op == ']') {
				if (!operatorStack.empty()
					&& (operatorStack.top() == '[')) {
					operatorStack.pop();
				}
				else { throw Syntax_Error("Unmatched close parentheses"); }
			}
			else if (op == '}') {
				if (!operatorStack.empty()
					&& (operatorStack.top() == '{')) {
					operatorStack.pop();
				}
				else {
					throw Syntax_Error("Unmatched close parentheses");
				}
			}
			else {
				operatorStack.push(op);
			}
		}
	}
	return;
}

void Parser::Calculate()
{
	int 	rightOperand, leftOperand, result;
	char op;

	op = operatorStack.top();
	operatorStack.pop();


	rightOperand = operandStack.top();
	operandStack.pop();

	switch (op)
	{
	case('!'): 	result = !rightOperand;
		operandStack.push(result);
		return;
	}
	if (operandStack.empty()) {
		return;
	}

	leftOperand = operandStack.top();
	operandStack.pop();



	switch (op)			//cases: ^, *, /, +, - Add error checking
	{
	case('>'): 	result = leftOperand > rightOperand;
		operandStack.push(result);
		break;
	case('<'): 	result = leftOperand < rightOperand;
		operandStack.push(result);
		break;
	case('^'): 	result = pow(leftOperand, rightOperand);
		operandStack.push(result);
		break;
	case('*'): 	result = leftOperand * rightOperand;
		operandStack.push(result);
		break;
	case('E'): result = leftOperand == rightOperand;
		operandStack.push(result);
		break;
	case('G'): result = leftOperand >= rightOperand;
		operandStack.push(result);
		break;
	case('A'): result = leftOperand && rightOperand;
		operandStack.push(result);
		break;
	case('/'):
		if (rightOperand == 0)
		{
			cout << "Division by zero";
		}

		else {
			result = leftOperand / rightOperand;
			operandStack.push(result);
		}
		break;
	case('+'): 	result = leftOperand + rightOperand;
		operandStack.push(result);
		break;
	case('-'): 	result = leftOperand - rightOperand;
		operandStack.push(result);
		break;
	}
	return;
}

void Parser::Display()
{
	//Displays the function 1/0
	if (operandStack.empty()) {
		return;
	}
	//Displays the function 15+3 2
	else if (operandStack.size() > 1) {
		cout << "Cannot have two operands in a row" << endl;
		while (!operandStack.empty()) {
			operandStack.pop();
		}
	}
	else {
		int result = operandStack.top();
		operandStack.pop();
		cout << result << endl;
	}
		return;
}
