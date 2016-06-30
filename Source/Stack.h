#pragma once
#include"Vector.h"
namespace Library
{
	template<typename T>
	/*!
	\class Stack
	\brief The templated class of stack
	*/
	class Stack 
	{
	public:
		/*!
		\fn stack()
		\brief The parameterless constructor that initializes the stack
		*/
		Stack();
		Stack(std::initializer_list<T> list);
		/*!
		\fn stack(const stack& rhs)
		\brief The copy ctor of the stack class which performs a deep copy
		*/
		Stack(const Stack& rhs);
		/*!
		\fn stack(stack&& rhs)
		\brief The move ctor
		\param A RValue reference for the stack to be moved from
		*/
		Stack(Stack&& rhs);
		/*!
		\fn operator=(const stack& rhs)
		\brief The overloaded assignment operator
		\param A reference for the stack to be copied from
		*/
		Stack& operator=(const Stack& rhs);
		/*!
		\fn operator=(stack&& rhs)
		\brief The move assignment operator
		\param A RValue reference for the stack to be moved from
		*/
		Stack& operator=(Stack&& rhs);
		/*!
		\fn Push(const T&data)
		\param A const reference to the data to be pushed into the stack
		*/
		void Push(const T& data);
		/*
		!
		\fn Pop()
		\brief removes the last element from the stack
		*/
		void Pop();
		/*!
		\fn Top()
		\brief Returns a reference to top element of the stack
		\return Returns a reference to the top element
		*/
		T& Top();
		/*!
		\fn Front() const
		\brief Returns a const reference to top element of the stack
		\return Returns a  const reference to the top element
		*/
		const T& Top() const;
		/*!
		\fn Size() const
		\brief Returns the number of elements in the stack
		\return The Size of the list
		*/
		std::uint32_t Size() const;
		/*!
		\fn IsEmpty() const
		\brief Checks if the list is empty
		\bool Returns true if the stack is empty
		*/
		bool IsEmpty() const;
		/*!
		\fn Clear()
		\brief Destroys the stack
		*/
		void Clear();
		/*!
		\fn ~stack()
		\brief Destructor that clears the container reference
		*/
		~Stack();
	private:
		Vector<T> Container;
	};
}
#include"Stack.inl"