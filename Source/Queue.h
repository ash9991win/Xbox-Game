#pragma once
#include"LinkedList.h"
template<class Datatype>
class Queue : public LinkedList<Datatype>
{
public:

	void Eneque(Datatype data)
	{
		Append(data);
	}
	void Dequeue()
	{
		removeHead();
	}

	Datatype Front()
	{
		return m_head->m_data;
	}
};