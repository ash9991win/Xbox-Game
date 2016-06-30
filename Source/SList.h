#pragma once
#include<iostream>
#include<exception>
#include<cstdint>
using namespace std;
/*
\class SList
\brief  A templated class that has the Head and tail pointer of the list
*/
namespace Library
{
	template<typename T>
	class SList
	{
#pragma region Node
		/*
		\class Node
		\brief  A templated nested class that stores a data of type Nodetype and a pointer to the next node
		*/
		class Node
		{
		public:
			/*!
			\var Nodetype mData;
			\brief The data to be stored in the node
			*/
			T Data;
			/*!
			\var Node *mNext;
			\brief A pointer to the next node
			*/
			Node     *Next;
			/*!
			\fn Node()
			\brief A parameterless constructor that initializes the mNext to a nullptr
			*/
			Node() :Next(nullptr)
			{
			}
			Node(T newData, Node* next = nullptr)
				: Data(newData), Next(next)
			{
			}
			bool operator==(const Node& rhs)
			{
				return ((Data == rhs.Data) && (Next == rhs.Next));
			}
		};
#pragma endregion

		/*!
		\var Node<Datatype> *mHead;
		\brief A Node pointer that stores the head of the list
		*/
		Node *FrontNode;
		/*!
		\var Node<Datatype> *mTail;
		\brief A Node pointer that stores the tail ( or the end) of the list
		*/
		Node *BackNode;
		/*!
		\var unsigned int mCount;
		\brief An integer that stores the size of the list
		*/
		std::uint32_t Count;
#pragma region Iterator
	public:
		/*!
		\class Iterator
		\brief The iterator class for a list of type T
		*/
		class Iterator
		{
			/*!
			\var const SList *mList
			\brief A constant pointer to the list that the iterator is pointing to
			*/
			const SList *Owner;
			/*!
			\var Node *currentNode
			\brief The position or the node of the list that the iterator is pointing to
			*/
			Node *CurrentNode;
			/*
			\fn Iterator(const SList<T>  *newList, Node* newNode)
			\brief A constructor which sets the list and the node in the list of the iterator
			*/
			Iterator(const SList<T>  *newList, Node* newNode);
		public:
			/*
			\fn Iterator()
			\brief A parameterless constructor
			*/
			Iterator();
			/*!
			\fn Iterator(const Iterator& rhs)
			\brief A copy constructor which performs a deep copy
			*/
			Iterator(const Iterator& rhs);
			/*!
			\fn T& operator*()
			\brief Overloading the dereference operator which returns the data stored in the current node
			*/
			Iterator(Iterator&& rhs);
			T& operator*();
			/*!
			\fn Iterator operator=(const Iterator& rhs)
			\brief Overloading the assignment operator to perform a deep copy
			*/
			Iterator operator=(const Iterator& rhs);
			/*!
			\fn bool operator==(const Iterator& rhs) const;
			\brief Checks if the two iterators are equal or not
			*/
			Iterator& operator=(Iterator&& rhs);
			bool operator==(const Iterator& rhs) const;
			/*!
			\fn bool operator!=(const Iterator& rhs) const;
			\brief Checks if the two iterators are equal or not
			*/
			bool operator!=(const Iterator& rhs) const;
			/*!
			\fn Iterator&  operator++();
			\brief Increments the node to point to the next element in the list
			*/
			Iterator&  operator++();
			/*!
			\fn Iterator  operator++(int);
			\brief Post-Increments the node to point to the next element in the list
			*/
			Iterator operator++(int);
			/*!
			\fn ~Iterator()
			\brief The destructor
			*/
			~Iterator();
			friend class SList;
		};
#pragma endregion
		/*!
		\fn SList()
		\brief A parameterless constructor that initializes the mNext to a nullptr
		*/
		SList();
		/*!
		\fn SList(const SList& rhs)
		\brief A copy constructor that performs a deep copy
		\param rhs The SList reference to be copied from
		*/
		SList(const SList& rhs);
		/*!
		\fn ~SList()
		\brief A destructor that clears the list
		*/
		~SList();
		/*!
		\fn operator=(const SList& rhs)
		\brief Overloading the assignment operator to perform a deep copy
		\param rhs A SList reference to be assigned to
		*/
		SList<T> operator=(const SList& rhs);

		/*!
		\fn CopyContent
		\brief A function that copies the contents of the given list
		\param rhs A SList reference to be assigned to
		*/
		void CopyContent(const SList& rhs);

		/*!
		\fn PushFront(T pData)
		\brief This function pushes the passed data into the list through the front
		\param pData The data of type T
		*/
		void PushFront(const T& pData);
		/*!
		\fn const T& Front() const
		\brief returns a reference at the front of the list. It is marked const because it need not modify any member of the SList class
		*/
		T& Front();
		/*!
		\fn void PopFront()
		\brief Removes the first element of the list and returns it into the passed value
		\param returnedValue The popped value is returned via the parameter
		*/
		void PopFront();
		/*!
		\fn PushBack(T pData)
		\brief This function pushes the passed data into the list through the back
		\param pData The data of type T
		*/
		void PushBack(const T& pData);
		Iterator PushBackWithIterator(const T& pData);
		/*!
		\fn const Datatype& Back() const
		\brief returns a reference at the back of the list. It is marked const because it need not modify any member of the SList class
		*/
		T& Back();
		/*!
		\fn isEmpty()
		\brief Checks if the list is empty, Returns true, if it is.
		*/
		bool IsEmpty() const;
		/*!
		\fn Size()
		\brief Returns the number of elements in the list
		*/
		std::uint32_t Size() const;
		/*!
		\fn Clear()
		\brief Clears the list and deletes any memory allocated on the heap
		*/
		void Clear();
		/*
		\fn Iterator begin() const
		\brief Returns an iterator pointing to the beginning of the list
		*/
	    Iterator begin() const;
		/*
		\fn Iterator end() const
		\brief Returns an iterator pointing to the end of the list
		*/
	    Iterator end() const;
		/*
		\fn void InsertAfter(Iterator& position, T data);
		\brief Inserts the data 'data' after the position given by the iterator
		*/
		void InsertAfter(Iterator& position, T data);
		/*
		\fn Iterator Find(const T& value) const;
		\brief Searches for the given data in the list, and returns an iterator to it
		*/
		Iterator Find(const T& value) const;
		/*
		\fn void Remove(const T& data);
		\brief Removes the first occurence of the data in the list
		*/
		void Remove(const T& data);
	};
}
#include"SList.inl"