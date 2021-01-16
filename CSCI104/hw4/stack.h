#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "deque.h"

/** 
 * Your Stack<T> class must be templated and
 * privately inherit from Deque<T>. All
 * operations must run in O(1).
 *
 * Both pop() and top() must throw std::underflow_error
 * if the stack is empty.
 */

template <typename T>
class Stack : private Deque<T>
{
 public:
  Stack();
  size_t size() const;
  bool empty() const;
  void push(const T& item);
  void pop();
  T const & top() const;
};


template <typename T>
Stack<T>::Stack() :
	Deque<T>()
{

}

template <typename T>
size_t Stack<T>::size() const
{
	return Deque<T>::size();
}

template <typename T>
bool Stack<T>::empty() const
{
	return Deque<T>::empty();
}

template <typename T>
void Stack<T>::push(const T& item)
{
	Deque<T>::push_back(item);
}

template <typename T>
void Stack<T>::pop()
{
	//if empty, throw underflow_error
	if(Deque<T>::empty())
	{
		throw std::underflow_error("Stack is already empty");
	}
	Deque<T>::pop_back();
}

template <typename T>
T const & Stack<T>::top() const
{
	//if empty, throw underflow_error
	if(Deque<T>::empty())
	{
		throw std::underflow_error("Stack is already empty");
	}
	return Deque<T>::operator[](Deque<T>::size()-1);
}



#endif
