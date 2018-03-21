// InfixParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"


int main()
{
	Parser infix;

	
	infix.Parse("!3");
	infix.Parse("1+2*3");
	infix.Parse("2+2^2*3");
	infix.Parse("1==2");
	infix.Parse("1+3>2");
	infix.Parse("(4>=4) && 0");
	infix.Parse("(1+2)*3");
	infix.Parse("++2-5*(3^2)");
	
	infix.Parse(")3+2");
	infix.Parse("<3+2");
	infix.Parse("15+3 2");
	infix.Parse("1/0");

	system("pause");
	return 0;
}

