#pragma once
#include<stdio.h>
#include<memory.h>
template<class Datatype>
class SListNode
{
public:

	Datatype m_data;
	SListNode *m_next;

	void InsertAfter(Datatype newData)
	{
		SListNode<Datatype> *newNode = new SListNode<Datatype>;
		newNode->m_data = newData;
		newNode->m_next = m_next;

		m_next = newNode;
		m_next->m_next = NULL;
	}
};
template<class Datatype>
class ListIterator;
template<class Datatype>
class LinkedList
{
public:
	SListNode<Datatype> *m_head;
	SListNode<Datatype> *m_tail;
	int m_count;

	LinkedList()
	{
		m_head = 0;
		m_tail = 0;
		m_count = 0;
	}
	~LinkedList()
	{
		SListNode<Datatype> *iterator = m_head;
		SListNode<Datatype> *next;
		while (iterator != 0)
		{
			next = iterator->m_next;
			delete iterator;
			iterator = next;
		}
	}
	void Append(Datatype data)
	{
		if (m_head == 0)
		{
			m_head = m_tail = new SListNode<Datatype>;
			m_head->m_data = data;
			m_head->m_next = NULL;

		}
		else
		{
			m_tail->InsertAfter(data);
			m_tail = m_tail->m_next;
		}
		m_count++;
	}

	
	void Prepend(Datatype data)
	{
		SListNode<Datatype> *newNode = new SListNode<Datatype>;
		newNode->m_data = data;
		newNode->m_next = m_head;

		m_head = newNode;

		if (m_tail == 0)
		{
			m_tail = m_head;
		}
		m_count++;
	}
	void removeHead()
	{
		SListNode<Datatype> *node = new SListNode<Datatype>;
		if (m_head != 0)
		{
			node = m_head->m_next;

			delete m_head;

			m_head = node;

			if (m_head == 0)
			{
				m_tail = 0;
			}
			m_count--;
		}
	}
	void removeTail()
	{
		SListNode<Datatype> *node = m_head;

		if (m_head != 0)
		{
			if (m_head == m_tail)
			{
				delete m_head;
				m_head = m_tail = 0;
			}
			else
			{
				while (node->m_next != m_tail)
				{
					node = node->m_next;
				}
				m_tail = node;
				delete node->m_next;
				node->m_next = 0;
			}
		}
		m_count--;
	}
	bool isEmpty()
	{
		return (m_count <= 0);
	}
	ListIterator<Datatype> getIterator()
	{
		return ListIterator<Datatype>(this, m_head);
	}
};

template<class Datatype>
class ListIterator
{
public:
	SListNode<Datatype> *m_node;
	LinkedList<Datatype> *m_list;
	int currentNode;
	ListIterator(LinkedList<Datatype> *p_list = 0, SListNode<Datatype> *p_node = 0)
	{
		m_node = p_node;
		m_list = p_list;
	}

	void Start()
	{
		if (m_list != 0)
		{
			m_node = m_list->m_head;
		}
		currentNode = 0;
	}
	void forth()
	{
		if (m_node != 0)
		{
			m_node = m_node->m_next;
		}
		currentNode++;
	}
	Datatype& data()
	{
		return m_node->m_data;
	}
	bool Valid()
	{
		return (m_node == 0);
	}
	bool hasReachedEnd()
	{
	/*	if(m_node == NULL)
		{ 
			return true;
		}*/
		/*if (m_node->m_next == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}*/
		return (currentNode == m_list->m_count);
	}
	
};