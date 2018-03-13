#include "stdafx.h"
#include "Parser.h"
#include <sstream>
#include <math.h>


const string Parser::OPERATORS = "><+-*/%^!()[]{}";
const int Parser::PRECEDENCE[] = { 4, 4, 5, 5, 6, 6, 6, 7, 8, -1, -1, -1, -1, -1, -1 };
Parser::Parser()
{
}

void Parser::Parse(string infixExpr)
{
	char next_token;
	cout << infixExpr << " = ";

	istringstream infix_tokens(infixExpr);

	while (infix_tokens >> next_token)
	{
		if (isdigit(next_token))
		{
			infix_tokens.putback(next_token);
			int value;
			infix_tokens >> value;
			operandStack.push(value);
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
	if (operatorStack.empty() || (op == '(') || (op == '[') || (op == '{'))
	{
		if (op == ')' || op == ']' || op == '}') {
			throw Syntax_Error("Expression can't start with a closing parenthesis @ char: 0");
		}	else if (op == '<' || op == '>') { 
			throw Syntax_Error("Expression can't start with a binary operator @ char: 0"); 
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
					else {throw Syntax_Error("Unmatched close parentheses");}
				}
				else if (op == ']') {
					if (!operatorStack.empty()
						&& (operatorStack.top() == '[')) {
						operatorStack.pop();
					}
					else {throw Syntax_Error("Unmatched close parentheses");}
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
	int result = operandStack.top();
	operandStack.pop();
	cout << result << endl;
	return;
}
