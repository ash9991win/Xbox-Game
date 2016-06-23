#pragma once
#include"LinkedList.h"

template<class Datatype>
class Stack : public LinkedList<Datatype>
{
public: 

	void Push(Datatype data)
	{
		Append(data);
	}
	void Pop()
	{
		removeTail();
	}
	Datatype Top()
	{
		return m_tail->m_data;
	}
	int Count()
	{
		return m_count;
	}
};