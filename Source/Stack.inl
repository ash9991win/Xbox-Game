#include "Stack.h"
#pragma once
namespace Library
{
	template<typename T>
	Stack<T>::Stack()
		: Container()
	{
	}
	template<typename T>
	 Stack<T>::Stack(std::initializer_list<T> list)
		 :Stack()
	{
		for (auto& l : list)
		{
			Push(l);
		}
	}
	template<typename T>
	Stack<T>::Stack(const Stack& rhs)
		:Container(rhs.Container)
	{
	}
	template<typename T>
	Stack<T>::Stack(Stack&& rhs)
		:Container(std::move(rhs.Container))
	{
	}
	template<typename T>
	Stack<T>& Stack<T>::operator=(const Stack& rhs)
	{
		if (this != &rhs)
		{
			Container = rhs.Container;
		}
		return *this;
	}
	template<typename T>
	Stack<T>& Stack<T>::operator=(Stack<T>&& rhs)
	{
		if (this != &rhs)
		{
			Container = std::move((rhs.Container));
		}
		return *this;
	}
	template<typename T>
	void Stack<T>::Push(const T& data)
	{
		Container.PushBack(data);
	}
	template<typename T>
	void Stack<T>::Pop()
	{
		if (IsEmpty())
			return;
		Container.PopBack();
	}
	template<typename T>
	T& Stack<T>::Top()
	{
		
		return Container.Back();
	}
	template<typename T>
	const T& Stack<T>::Top() const
	{
		
		return Container.Back();
	}
	template<typename T>
	bool Stack<T>::IsEmpty() const
	{
		return Container.IsEmpty();
	}
	template<typename T>
	std::uint32_t Stack<T>::Size() const
	{
			return Container.GetSize();
	}
	template<typename T>
	void Stack<T>::Clear()
	{
			Container.Clear();
	}
	template<typename T>
	Stack<T>::~Stack()
	{
		Clear();
	}
}