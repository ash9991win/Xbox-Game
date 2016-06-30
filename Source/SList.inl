#pragma once

namespace Library
{
#pragma region SList
	template<typename T>
	SList<T>::SList()
		: Count(0), FrontNode(nullptr), BackNode(nullptr)
	{
	}
	template<typename T>
	SList<T>::SList(const SList& rhs)
		: Count(0), FrontNode(nullptr), BackNode(nullptr)
	{
		CopyContent(rhs);
	}
	template<typename T>
	SList<T>::~SList()
	{
		Clear();
	}
	template<typename T>
	SList<T> SList<T>::operator=(const SList& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			CopyContent(rhs);
		}
		return *this;
	}
	template<typename T>
	void SList<T>::CopyContent(const SList& rhs)
	{
		Node *iterator = rhs.FrontNode;
		while (iterator != nullptr)
		{
			PushBack(iterator->Data);
			iterator = iterator->Next;
		}
	}
	template<typename T>
	void SList<T>::PushFront(const T& pData)
	{
		Node *newNode = new Node(pData);
		if (Count == 0)
		{
			BackNode = newNode;
		}
		else
		{
			newNode->Next = FrontNode;
		}
		FrontNode = newNode;
		Count++;
	}
	template<typename T>
	T& SList<T>::Front()
	{
		if (Count == 0)
			throw out_of_range("List is empty");

			return FrontNode->Data;
	}
	template<typename T>
	void SList<T>::PopFront()
	{
		if (Count == 0)
			return;

		Node *frontNode;
		if (FrontNode != nullptr)
		{
			frontNode = FrontNode->Next;
			delete FrontNode;
			FrontNode = frontNode;
		}
		if (FrontNode == nullptr)
		{
			BackNode = nullptr;
		}
		Count--;
	}
	template<typename T>
	void SList<T>::PushBack(const T& pData)
	{
		Node *newNode = new Node(pData);
		if (Count == 0)
		{
			FrontNode = newNode;
			BackNode = newNode;
		}
		else
		{
			BackNode->Next = newNode;
			BackNode = BackNode->Next;
		}
		Count++;
	}
	template<typename T>
	typename SList<T>::Iterator SList<T>::PushBackWithIterator(const T& pData)
	{
		PushBack(pData);
		return Iterator(this, BackNode);
	}
	template<typename T>
	T& SList<T>::Back()
	{
		if (Count == 0)
			throw out_of_range("List is Empty");

		return BackNode->Data;
	}
	template<typename T>
	bool SList<T>::IsEmpty() const
	{
		return (Count == 0);
	}
	template<typename T>
	std::uint32_t SList<T>::Size() const
	{
		return Count;
	}
	template<typename T>
	void SList<T>::Clear()
	{
		while (Count > 0)
		{
			PopFront();
		}
		FrontNode = BackNode = nullptr;
	}
	template<typename T>
    typename  SList<T>::Iterator SList<T>::begin() const
	{
		return Iterator(this,FrontNode);
	}
	template<typename T>
	 typename  SList<T>::Iterator SList<T>::end() const
	{
		return Iterator(this,nullptr);
	}
	template<typename T>
	void SList<T>::InsertAfter(Iterator& position, T data)
	{
		if (position.Owner != this)
			throw std::exception("Invalid list");

		if (position == end())
		{
			PushBack(data);
		}
		else
		{
			Node *NodeToInsert = new Node(data, position.CurrentNode->Next);
			position.CurrentNode->Next = NodeToInsert;
			Count++;
		}
	}
	template<typename T>
	typename SList<T>::Iterator SList<T>::Find(const T& value) const
	{
		for (Iterator iter = begin(); iter != end(); ++iter)
		{
			if (*iter == value)
			{
				return iter;
			}
		}
		return end();
	}
	template<typename T>
	void SList<T>::Remove(const T& value)
	{
		if (Count == 0)
			return;
		Iterator RemoveIterator = Find(value);
		if (RemoveIterator == begin())
		{
			PopFront();
		}
		else
		{
			Iterator PrevIterator = begin();
			while (PrevIterator.CurrentNode->Next != RemoveIterator.CurrentNode)
			{
				++PrevIterator;
			}
			PrevIterator.CurrentNode->Next = RemoveIterator.CurrentNode->Next;
			if (PrevIterator.CurrentNode->Next == nullptr)
			{
				BackNode = PrevIterator.CurrentNode;
			}
			delete RemoveIterator.CurrentNode;

			--Count;
		}
	}
#pragma endregion
#pragma region Iterator
	template<typename T>
	SList<T>::Iterator::Iterator()
		: Owner(nullptr), CurrentNode(nullptr)
	{
	}
	template<typename T>
	SList<T>::Iterator::Iterator(const SList<T> *newList = nullptr, Node* newNode = nullptr)
		: Owner(newList), CurrentNode(newNode)
	{
	}
	template<typename T>
	SList<T>::Iterator::Iterator(const Iterator& rhs)
		: Owner(nullptr), CurrentNode(nullptr)
	{
		if (this != &rhs)
		{
			Owner = rhs.Owner;
			CurrentNode = rhs.CurrentNode;
		}
	}
	template<typename T>
	SList<T>::Iterator::Iterator(Iterator&& rhs)
	{
		operator=(rhs);
	}
	template<typename T>
    typename SList<T>::Iterator& SList<T>::Iterator::operator=(Iterator&& rhs)
	{
		if (this != &rhs)
		{
			Owner = rhs.Owner;
			CurrentNode = rhs.CurrentNode;
			rhs.Owner = nullptr;
			rhs.CurrentNode = nullptr;
		}
		return *this;
	}
	template<typename T>
	T& SList<T>::Iterator::operator*()
	{
		if (Owner == nullptr || CurrentNode == nullptr)
			throw std::exception("Cannot dereference an empty list");

		return CurrentNode->Data;
	}
	template<typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			Owner = rhs.Owner;
			CurrentNode = rhs.CurrentNode;
		}
		return *this;
	}
	template<typename T>
	bool SList<T>::Iterator::operator==(const Iterator& rhs) const
	{
		return ((Owner == rhs.Owner) && (CurrentNode == rhs.CurrentNode));
	}
	template<typename T>

	bool SList<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(operator==(rhs));
	}
	template<typename T>

	typename SList<T>::Iterator& SList<T>::Iterator::operator++()
	{
		if ((Owner == nullptr) || (*this == Owner->end()) )
			throw std::exception("Illegal increment");

		CurrentNode = CurrentNode->Next;
		return *this;
	}
	template<typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		Iterator tempIter(*this);
		operator++();
		return tempIter;
	}
	template<typename T>
	SList<T>::Iterator::~Iterator()
	{
	}
#pragma endregion
}