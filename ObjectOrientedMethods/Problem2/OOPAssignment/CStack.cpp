#include "CStack.h"
template<class Type>

CStack<Type>::CStack() {
    maxSize = 10000;
    stackTop = -1;
    list = new Type[10000];
}

template<class Type>
CStack<Type>::CStack(int sz) {
    if (sz <= 0) {
        std::cout << "Size must be positive" << std::endl;
        exit(0);
    }
    maxSize = 10 * sz;
    stackTop = -1;
    list = new Type[maxSize];

}

template<class Type>
void CStack<Type>::push(Type in) {
    if (full()) {
        std::cout << "Stack is full" << std::endl;
        return;
    }
    stackTop++;
    list[stackTop] = in;
}

template<class Type>
void CStack<Type>::pop() {
    if (empty()) {
        std::cout << "Stack is empty" << std::endl;
    }
    stackTop--;
}

template<class Type>
Type CStack<Type>::top() {
    if (stackTop == -1) {
        std::cout << "Stack is empty" << std::endl;
        exit(0);
    }
    return list[stackTop];
}

template<class Type>
bool CStack<Type>::empty() {
    return (stackTop == -1);
}

template<class Type>
bool CStack<Type>::full() {
    return (stackTop + 1 == maxSize);
}

template<class Type>
int CStack<Type>::length() {
    return stackTop + 1;
}

template<class Type>
void CStack<Type>::clear() {
    stackTop = -1;
}

template<class Type>
void CStack<Type>::toString() {
    if (stackTop == -1) {
        std::cout << "Stack is empty" << std::endl;
        return;
    }
    for (int i = stackTop; i >= 0; i--) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

}

//template<class Type>
//CStack<Type>::~CStack() {
//    delete[] list;
//}
