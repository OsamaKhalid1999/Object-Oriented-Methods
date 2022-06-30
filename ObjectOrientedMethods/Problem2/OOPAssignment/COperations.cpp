#include "COperations.h"
#include<sstream>
#include "CStack.cpp"
#include <memory>



int COperations::precedence(char c)//operators precedence during the calculations
{
	if (c == '/' || c == '*')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}

std::string COperations::infixToPostfix(std::string infix)
{
	std::unique_ptr<CStack<int>>conversion(new CStack<int>);
	for (int i = 0; i < infix.length(); i++)
	{

		//if the current token is a space then skip it
		if (infix[i] == ' ')
			continue;

		//if the current token is an opening bracket then push it to the stack
		else if (infix[i] == '(')
		{
			conversion->push(infix[i]);
		}
		

		// If the scanned character is
		// an operand, add it to output string.
		else if (isdigit(infix[i]))
		{			
			int operand = 0;
			while (i < infix.length() && isdigit(infix[i]))
			{
				operand = (operand * 10) + (infix[i] - '0');//if the character is a multi digit number
				i++;
			}
			std::string str;
			std::stringstream ss;
			ss << operand;
			ss >> str;
			i--;

			postfix += str;
			postfix += " ";			
			
		}



		// If the scanned character is an
		// ‘(‘, push it to the stack.
		else if (infix[i] == '(')
			conversion->push(infix[i]);

		// If the scanned character is an ‘)’,
		// pop and to output string from the stack
		// until an ‘(‘ is encountered.
		else if (infix[i] == ')') {


			while (!conversion->empty() && conversion->top() != '(')
			{

				postfix += conversion->top();
				conversion->pop();
				postfix += " ";
			}
			conversion->pop();
		}

		//If an operator is scanned
		else {
			while (!conversion->empty() && precedence(infix[i]) <= precedence(conversion->top())) {


				postfix += conversion->top();
				conversion->pop();
				postfix += " ";
			}
			conversion->push(infix[i]);
		}
	}
	
	// Pop all the remaining elements from the stack		
	while (!conversion->empty()) {
		postfix += conversion->top();
		conversion->pop();
		postfix += " ";
	}
	
	
	
	
	conversion.reset();
	return postfix;
	postfix.clear();
}

double COperations::evaluatePostfix(std::string postfix)
{
	
	std::unique_ptr<CStack<double>>evaluation(new CStack<double>);
	for (int i = 0; i < postfix.length(); i++)
	{

		// Scanning each token from left.
		// If token is a delimiter, skip it.
		if (postfix[i] == ' ' || postfix[i] == ',') continue;

		// If token is operator, pop two elements from stack, perform operation and push the result back.
		else if (IsOperator(postfix[i]))
		{
			// Pop two operands.
			double operand2 = evaluation->top(); evaluation->pop();
			double operand1 = evaluation->top(); evaluation->pop();

			//operand1 and operand2 are reversed in case of Prefix Expression

			// Perform operation
			switch (postfix[i]) {
			case '+':
				evaluation->push(operand1 + operand2);
				break;
			case '-':
				evaluation->push(operand1 - operand2);
				break;
			case '*':
				evaluation->push(operand1 * operand2);
				break;
			case '/':
				evaluation->push(operand1 / operand2);
				break;
			}

			
		}
		else if (isdigit(postfix[i]))
		{
			// Extract the numeric operand from the string
			// Keep incrementing till is a number
			int operand = 0;
			while (i < postfix.length() && isdigit(postfix[i]))
			{
				// For a number with more than one digits, as we are scanning from left to right.
				// Everytime , we get a digit towards right, we can multiply current total in operand by 10
				// and add the new digit.
				operand = (operand * 10) + (postfix[i] - '0');
				i++;
			}
			//decrement as i is incremented inside the loop			
			i--;

			// Push operand on stack.
			evaluation->push(operand);
		}
	}
	// If expression is in correct format, Stack will finally have one element. This will be the output.
	return evaluation->top();
	evaluation.reset();

}


bool COperations::IsOperator(char C)
{
	if (C == '+' || C == '-' || C == '*' || C == '/')
		return true;

	return false;
}

std::string COperations::infixToPrefix(std::string infix)
{

	
	std::unique_ptr<CStack<int>>conversion(new CStack<int>);
	
	//reverse the string
	reverse(infix.begin(), infix.end());

	//considering opening and close brackets reversed
	for (int i = 0; i < infix.length(); i++) {
		if (infix[i] == '(') {
			infix[i] = ')';
		}
		else if (infix[i] == ')') {
			infix[i] = '(';
		}
	}

	//addign brackets for the simplicity of checking
	infix = "(" + infix + ")";

	// iterate through infix string
	for (int i = 0; i < infix.size(); i++)
	{
		
		if (numbers.find(infix[i]) != numbers.end())
		{
			// delete last space to continue number
			if (numbers.find(infix[i - 1]) != numbers.end())
			{
				prefix.pop_back();
			}
			// add number to expression
			prefix += infix[i];
			prefix += " ";
		}
		else if (infix[i] == '(')
		{
			conversion->push('(');
		}
		else if (infix[i] == ')')
		{
			// remove everithing within the brackets
			while (conversion->top() != '(')
			{
				prefix += conversion->top();
				conversion->pop();
				prefix += " ";
			}
			// ignore open bracket
			conversion->pop();
		}
		else if (IsOperator(infix[i]))
		{
			// add lower priority operators to string
			while (precedence(infix[i]) < precedence(conversion->top()))
			{
				prefix += conversion->top();
				conversion->pop();
				prefix += " ";
			}
			conversion->push(infix[i]);
		}
	}
	// delete last space
	prefix.pop_back();
	reverse(prefix.begin(), prefix.end());
	return prefix;
	prefix.clear();

	
}

double COperations::evaluatePrefix(std::string prefix)
{

	std::unique_ptr<CStack<double>>evaluation(new CStack<double>);
	for (int j = prefix.size() - 1; j >= 0; j--) {

		// if the current token is the delimiter ( which is
		// space in this case) then skip it
		if (prefix[j] == ' ')
			continue;

		// Push operand to Stack
		
		if (isdigit(prefix[j])) {

			// there may be more than
			// one digits in a number
			int num = 0, i = j;
			while (j < prefix.size() && isdigit(prefix[j]))
				j--;
			j++;

			// from [j, i] exprsn contains a number
			for (int k = j; k <= i; k++)
				num = num * 10 + int(prefix[k] - '0');

			evaluation->push(num);
		}
		else {

			// Operator encountered
			// Pop two elements from Stack
			double o1 = evaluation->top();
			evaluation->pop();
			double o2 = evaluation->top();
			evaluation->pop();

			// Use switch case to operate on o1
			// and o2 and perform o1 O o2.
			switch (prefix[j]) {
			case '+':
				evaluation->push(o1 + o2);
				break;
			case '-':
				evaluation->push(o1 - o2);
				break;
			case '*':
				evaluation->push(o1 * o2);
				break;
			case '/':
				evaluation->push(o1 / o2);
				break;
			}
		}
	}

	return evaluation->top();
	evaluation.reset();
}
