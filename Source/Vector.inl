#include "Vector.h"
namespace Library
{
#pragma region Vector
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	IncrementFunctor Vector<T, IncrementFunctor>::ReserveStrategy;

	template<typename T, typename IncrementFunctor>
	std::uint32_t Vector<T, IncrementFunctor>::DefaultCapacity = 3;

	template<typename T,typename IncrementFunctor = DefaultFunctor>
	Vector<T,IncrementFunctor>::Vector()
		:Size(0),Capacity(0),Array(nullptr)
	{
		Reserve(DefaultCapacity);
	}
	template<typename T, typename IncrementFunctor>
	 Vector<T, IncrementFunctor>::Vector(std::initializer_list<T> list)
		 :Vector<T,IncrementFunctor>()
	{
		for (auto& items : list)
		{
			PushBack(items);
		}
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	Vector<T,IncrementFunctor>::Vector(std::uint32_t capacity, bool fixedSize = false)
		:Size(0), Capacity(0), Array(nullptr)
	{
		Reserve(capacity, fixedSize);
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	Vector<T,IncrementFunctor>::Vector(const Vector& rhs)
		:Size(0), Capacity(0), Array(nullptr)
	{
		operator=(rhs);
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	Vector<T,IncrementFunctor>::Vector(Vector&& rhs)
		: Size(0), Capacity(0), Array(nullptr)
	{
		*this = std::move(rhs);
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	Vector<T,IncrementFunctor>& Vector<T,IncrementFunctor>::operator=(const Vector& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			Reserve(rhs.Capacity);
			for (std::uint32_t i = 0; i < rhs.Size; ++i)
			{
				PushBack(rhs[i]);
			}
		}
		return *this;
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	Vector<T,IncrementFunctor>& Vector<T,IncrementFunctor>::operator=(Vector&& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			Capacity = rhs.Capacity;
			Size = rhs.Size;
			Array = rhs.Array;
			rhs.Size = 0;
			rhs.Capacity = 0;
			rhs.Array = nullptr;
		}
		return *this;
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	T& Vector<T,IncrementFunctor>::operator[](std::uint32_t index)
	{
		if (index >= Size)
			throw std::exception("Invalid index");
		return Array[index];
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	const T& Vector<T,IncrementFunctor>::operator[](std::uint32_t index) const
	{
		if (index >= Size)
			throw std::exception("Invalid index");
		return Array[index];
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	void Vector<T,IncrementFunctor>::PopBack()
	{
		if (!IsEmpty())
		{
			Array[Size - 1].~T();
			--Size;
		}	
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	bool Vector<T,IncrementFunctor>::IsEmpty() const
	{
		return (Size == 0);
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	T& Vector<T,IncrementFunctor>::Front()
	{
		if (IsEmpty())
			throw std::exception("Empty List");
		return Array[0];
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	const T& Vector<T,IncrementFunctor>::Front() const
	{
		if (IsEmpty())
			throw std::exception("Empty List");
		return Array[0];
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	T& Vector<T,IncrementFunctor>::Back()
	{
		if (IsEmpty())
			throw std::exception("Empty List");
		return Array[Size - 1];
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	const T& Vector<T,IncrementFunctor>::Back() const
	{
		if (IsEmpty())
			throw std::exception("Empty List");
		return Array[Size - 1];
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	std::uint32_t Vector<T,IncrementFunctor>::GetSize() const
	{
		return Size;
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	std::uint32_t Vector<T,IncrementFunctor>::GetCapacity() const
	{
		return Capacity;
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	typename Vector<T,IncrementFunctor>::Iterator Vector<T,IncrementFunctor>::begin() const
	{
		return Iterator(this, 0);
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	typename Vector<T,IncrementFunctor>::Iterator Vector<T,IncrementFunctor>::end() const
	{
		return Iterator(this, Size);
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	void Vector<T,IncrementFunctor>::PushBack(const T& data)
	{
		if(Size >= Capacity)
		{
			std::uint32_t NewCapacity = ReserveStrategy(Size, Capacity);
			if (NewCapacity < Capacity)
			{
				throw std::exception("Invalid Capactiy allocation");
			}
			Reserve(NewCapacity);
		}
		new (Array + Size)T(data);
		++Size;
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	typename Vector<T,IncrementFunctor>::Iterator Vector<T,IncrementFunctor>::PushBackWithIterator(const T& data)
	{
		PushBack(data);
		return Iterator(this,Size-1);
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	T& Vector<T,IncrementFunctor>::At(std::uint32_t index)
	{
		return operator[](index);
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	const T& Vector<T,IncrementFunctor>::At(std::uint32_t index) const
	{
		return operator[](index);
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	void Vector<T,IncrementFunctor>::Reserve(std::uint32_t newCapacity, bool fixedSize = false)
	{
		if (newCapacity > Capacity)
		{
			T* TempArray = reinterpret_cast<T*>(std::realloc(Array, (sizeof(T) * newCapacity)));
			Array = TempArray;
			Capacity = newCapacity;
			if (fixedSize)
			{
				for (std::uint32_t Index = Size; Index < Capacity; Index++)
				{
					new (Array + Index)T();
				}
				Size = Capacity;
			}
		}
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	typename Vector<T,IncrementFunctor>::Iterator Vector<T,IncrementFunctor>::Find(const T& data) const
	{
		Iterator FindIterator = begin();
		for (; FindIterator != end(); ++FindIterator)
		{
			if (*FindIterator == data)
			{
				break;
			}
		}
		return FindIterator;
	}
	template<typename T, typename IncrementFunctor>
	 bool Vector<T, IncrementFunctor>::IsFound(const T & data) const
	{
		return (Find(data) != end());
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	void Vector<T,IncrementFunctor>::Clear()
	{
		while (Size > 0)
		{
			PopBack();
		}
		Capacity = 0;
		if (Array)
		{
			free(Array);
			Array = nullptr;
		}
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	void Vector<T,IncrementFunctor>::Erase(std::uint32_t index)
	{
		if (!IsEmpty())
		{
			if (index > (Size - 1))
				return;
			if (index == (Size - 1))
			{
				PopBack();
				return;
			}
			Array[index].~T();
			std::memmove(Array + index, Array + index + 1, (sizeof(T) * (Size - index - 1)));
			--Size;
		}
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	void Vector<T,IncrementFunctor>::Remove(const T& data)
	{
		Iterator FindIterator = Find(data);
		Erase(FindIterator.Index);
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	void Vector<T,IncrementFunctor>::Remove(const Iterator& from, const Iterator& to)
	{
		if ((from.Owner != this) || (to.Owner != this))
		{
			throw std::exception("Invalid list");
		}
		if (from.Index > to.Index)
		{
			throw std::exception("Invalid Iterators");
		}
		std::uint32_t NumberOfElementsToBeDeleted = to.Index - from.Index;
		for (std::uint32_t i = 0; i < NumberOfElementsToBeDeleted; i++)
		{
			Erase(from.Index);
		}
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	Vector<T,IncrementFunctor>::~Vector()
	{
		Clear();
	}
#pragma endregion
#pragma region Iterator
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	Vector<T,IncrementFunctor>::Iterator::Iterator()
		:Owner(nullptr),Index(0)
	{
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	Vector<T,IncrementFunctor>::Iterator::Iterator(const Iterator& rhs)
	{
		operator=(rhs);
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	Vector<T,IncrementFunctor>::Iterator::Iterator(Iterator&& rhs)
		:Iterator(rhs.Owner,rhs.Index)
	{
		rhs.Owner = nullptr;
		rhs.Index = 0;
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	Vector<T,IncrementFunctor>::Iterator::Iterator(const Vector* newOwner = nullptr, std::uint32_t index = 0)
		: Owner(newOwner),Index(index)
	{}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	typename Vector<T,IncrementFunctor>::Iterator& Vector<T,IncrementFunctor>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			Owner = rhs.Owner;
			Index = rhs.Index;
		}
		return *this;
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	typename Vector<T,IncrementFunctor>::Iterator& Vector<T,IncrementFunctor>::Iterator::operator=(Iterator&& rhs)
	{
		if (this != &rhs)
		{
			Owner = rhs.Owner;
			Index = rhs.Index;
			rhs.Owner = nullptr;
			rhs.Index = 0;
		}
		return *this;
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	bool Vector<T,IncrementFunctor>::Iterator::operator==(const Iterator& rhs) const
	{
		return ((Owner == rhs.Owner) && (Index == rhs.Index));
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	bool Vector<T,IncrementFunctor>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(operator==(rhs));
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	typename Vector<T,IncrementFunctor>::Iterator& Vector<T,IncrementFunctor>::Iterator::operator++()
	{
		if (Index >= (Owner->Size ) || Owner == nullptr)
			throw std::exception("Invalid increment");
		Index++;
		return *this;
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	typename Vector<T,IncrementFunctor>::Iterator Vector<T,IncrementFunctor>::Iterator::operator++(int)
	{
		Iterator TempIterator = *this;
		operator++();
		return TempIterator;
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	T& Vector<T,IncrementFunctor>::Iterator::operator*()
	{
		return const_cast<T&>(static_cast<const Vector<T,IncrementFunctor>::Iterator*>(this)->operator*());
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	const T& Vector<T,IncrementFunctor>::Iterator::operator*() const
	{
		if (Owner == nullptr)
			throw std::exception("Empty list");
		if (Index >= Owner->Size)
			throw std::exception("Invalid Index");
		return Owner->Array[Index];
	}
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	Vector<T,IncrementFunctor>::Iterator::~Iterator()
	{
		Owner = nullptr;
		Index = 0;
	}
#pragma endregion
}