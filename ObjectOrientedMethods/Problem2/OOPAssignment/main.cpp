#include <iostream>
#include "COperations.h"
int main()
{	
	std::string infix, postfix, prefix;
	std::unique_ptr<COperations>operations(new COperations);

	std::cout << "Enter An Infix Expression" << std::endl;
	std::getline(std::cin, infix);
	std::cout << "INFIX EXPRESSION: " << infix << std::endl;
	postfix = operations->infixToPostfix(infix);
	std::cout << std::endl
		<< "POSTFIX CONVERSION: " << postfix;
	std::cout << std::endl
		<< "POSTFIX EVALUATION: " << operations->evaluatePostfix(postfix);
	for (int i = 0; i < 10; i++)
	{
		operations->numbers.insert('0' + i);
	}
	prefix = operations->infixToPrefix(infix);
	std::cout << std::endl
		<< "PREFIX CONVERSION: " << prefix;
	std::cout << std::endl
		<< "PREFIX EVALUATION: " << operations->evaluatePrefix(prefix);	
}