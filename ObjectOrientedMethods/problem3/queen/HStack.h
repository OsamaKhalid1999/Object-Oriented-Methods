template<class Type>
class HStack//abstract class to store operations performed by the stack
{
	virtual void push(Type v) = 0;
	virtual void pop() = 0;
	virtual bool empty() = 0;
	virtual Type top() = 0;
	virtual bool full() = 0;
	virtual int length() = 0;
	virtual void clear() = 0;
	virtual void toString() = 0;
};