#include <string>
class HOperations//abstract class that stores the functions performed by the operation class
{
	virtual int precedence(char c) = 0;
	virtual std::string infixToPostfix(std::string infix) = 0;
	virtual double evaluatePostfix(std::string postfix) = 0;	
	virtual bool IsOperator(char C) = 0;
	virtual std::string infixToPrefix(std::string infix) = 0;
	virtual double evaluatePrefix(std::string postfix) = 0;
};