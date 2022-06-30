#include "HStack.h"
template<class Type>
class CStack :public HStack<Type>{
private:
	int stackTop;
	int maxSize;
	Type* list;

public:
	CStack();//default stack constructor

	CStack(int sz);//constructor that allows to increase the size of the array if overflowed

	void push(Type in);//function to push elements on stack

	void pop();//removes the last add element into the stack

	Type top();//returns the top element of the stack

	bool empty();//checks if the stack is empty and underflows

	bool full();//checks if the stack is full and overflows

	int length();//return number of elements in stack

	void clear();//clear content of stack

	void toString();//print the concent of the stack

	~CStack();

	//~stack();
};