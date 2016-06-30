#pragma once
#include<cstdint>
#include<exception>
#include<new>
#include<memory>
#include"ReservationFunctor.h"
namespace Library
{
	
#pragma region Vector
	template<typename T, typename IncrementFunctor = DefaultFunctor>
	/*!
	\class Vector
	\brief A templated class of Vector. The two templates are: The datatype to be stored in the vector and a functor that calculates the capacity
	*/
	class Vector
	{
	public:
		//Forward declaration of the Iterator to be used by the functions of the vector class
		class Iterator;
		/*!
		\fn Vector()
		\brief The parameterless constructor that initializes the vector with a capacity of 3
		*/
		Vector();
		Vector(std::initializer_list<T> list);
		/*!
		\fn Vector(std::uint32_t capacity)
		\brief A parameterized ctor of the Vector class
		\param The new capacity to be reserved
		*/
		Vector(std::uint32_t capacity, bool fixedSize = false);
		/*!
		\fn Vector(const Vector& rhs)
		\brief The copy ctor of the Vector class which performs a deep copy
		*/
		Vector(const Vector& rhs);
		/*!
		\fn Vector(Vector&& rhs)
		\brief The move ctor
		\param A RValue reference for the vector to be moved from
		*/
		Vector(Vector&& rhs);
		/*!
		\fn operator=(const Vector& rhs)
		\brief The overloaded assignment operator
		\param A reference for the vector to be copied from
		*/
		Vector& operator=(const Vector& rhs);
		/*!
		\fn operator=(Vector&& rhs)
		\brief The move assignment operator
		\param A RValue reference for the vector to be moved from
		*/
		Vector& operator=(Vector&& rhs);
		/*!
		\fn  operator[](std::uint32_t index)
		\brief The overlaoded [] operator
		\param An index, the reference of the Value at which has to be returned
		\return Returns a reference to the value stored in the index
		*/
		T& operator[](std::uint32_t index);
		/*!
		\fn  operator[](std::uint32_t index) const
		\brief The overlaoded [] operator
		\param An index, the const reference of the Value at which has to be returned
		\return Returns a const reference to the value stored in the index
		*/
		const T& operator[](std::uint32_t index) const;
		/*
		!
		\fn PopBack()
		\brief removes the last element from the vector
		*/
		void PopBack();
		/*!
		\fn IsEmpty() const
		\brief Checks if the list is empty
		\bool Returns true if the vector is empty
		*/
		bool IsEmpty() const;
		/*!
		\fn Front()
		\brief Returns a reference to first element of the vector
		\return Returns a reference to the first element 
		*/
		T& Front();
		/*!
		\fn Front() const
		\brief Returns a const reference to first element of the vector
		\return Returns a  const reference to the first element
		*/
		const T& Front() const;
		/*!
		\fn Back() 
		\brief Returns a reference to last element of the vector
		\return Returns a  reference to the last element
		*/
		T& Back();
		/*!
		\fn Back() const
		\brief Returns a const reference to last element of the vector
		\return Returns a  const reference to the last element
		*/
		const T& Back() const;
		/*!
		\fn GetSize() const
		\brief Returns the number of elements in the vector
		\return The Size of the list
		*/
		std::uint32_t GetSize() const;
		/*!
		\fn GetCapacity() const
		\brief Returns the maximum number of elements that can be stored in the list
		\return returns the capacity
		*/
		std::uint32_t GetCapacity() const;
		/*!
		\fn begin() const
		\brief Returns an iterator pointing to the first element of the list
		\return An Iterator to the first element
		*/
		Iterator begin() const;
		/*!
		\fn end() const
		\brief Returns an iterator pointing to the end of the list
		\return An Iterator to the end
		*/
		Iterator end() const;
		/*!
		\fn PushBack(const T&data)
		\param A const reference to the data to be pushed into the vector
		*/
		void PushBack(const T& data);
		/*!
		\fn PushBackWithIterator(const T& data)
		\brief Pushes a data at the end of the vector and returns an iterator referencing it
		\return An Iterator pointint to the data inserted
		*/
		Iterator PushBackWithIterator(const T& data);
		/*!
		\fn At(Index)
		\brief Returns a reference to the element at the given index
		\return Returns a reference to the element at the index
		*/
		T& At(std::uint32_t index);
		/*!
		\fn At(Index) const
		\brief Returns a const reference to the element at the given index
		\return Returns a const reference to the element at the index
		*/
		const T& At(std::uint32_t index) const;
		/*!
		\fn Reserve(newCapacity)
		\brief Allocates the amount of memry passed in
		\param The memory to be allocated
		*/
		void Reserve(std::uint32_t newCapacity, bool fixedSize = false);
		/*!
		\fin Find(const T& data) const
		\brief Finds the data in teh vector and returns an iterator to it
		\return Returns an iterator to the found element ( end if not found)
		*/
		Iterator Find(const T& data) const;
		bool IsFound(const T& data) const;
		/*!
		\fn Clear()
		\brief Destroys the vector
		*/
		void Clear();
		/*!
		\fn Remove(const T& data)
		\brief Removes the element passed in 
		*/
		void Remove(const T& data);
		/*!
		\fn Erase(index)
		\brief removes the element at the particular index
		*/
		void Erase(std::uint32_t index);
		/*!
		\fn Remove(Iterator begin, Iterator end)
		\brief Removes all the elements between the two iterators
		\param Two const references to Iteraross
		*/
		void Remove( const Iterator& from, const Iterator& to);
		/*!
		\fn ~Vector()
		\brief Destructor that clears the list
		*/
		~Vector();
		static std::uint32_t DefaultCapacity;
#pragma region Iterator
		/*!
		\class Iterator
		\brief A nested class that helps in accessing the elements of the vector
		*/
		class Iterator
		{
		public:
			/*!
			\fn Iterator()
			\brief The parameterless constructor
			*/
			Iterator();
			/*!
			\fn Iterator(const Iterator&)
			\brief The copy ctor
			*/
			Iterator(const Iterator& rhs);
			/*!
			\fn Iterator(Iterator&& )
			\brief A move constructor
			*/
			Iterator(Iterator&& rhs);
			/*!
			\fn operator=(const Iterator&)
			\brief The overloaded assignment operator
			\param A const reference to teh Iterator to be copied from
			\return Returns a reference to the Iterator
			*/
			Iterator& operator=(const Iterator& rhs);
			/*!
			\fn operator=(Iterator&&)
			\brief A move assignment operator
			\param A const reference to teh Iterator to be moved from
			\return Returns a reference to the Iterator
			*/
			Iterator& operator=(Iterator&& rhs);
			/*!
			\fn operator==(const Iterator& rhs) const;
			\brief Checks if the iterators are equal
			\param The iterator to be compared to
			\return Returns true if the two iterators are equal
			*/
			bool operator==(const Iterator& rhs) const;
			/*!
			\fn operator!=(const Iterator& rhs) const;
			\brief Checks if the iterators are not equal
			\param The iterator to be compared to
			\return Returns true if the two iterators are not equal
			*/
			bool operator!=(const Iterator& rhs) const;
			/*!
			\fn operator++()
			\brief Overloaded pre increment opeerator
			\return Returns an iterator reference
			*/
			Iterator& operator++();
			/*!
			\fn operator++(int)
			\brief Overloaded post increment opeerator
			\return Returns an iterator reference
			*/
			Iterator operator++(int);
			/*!
			\fn operator*()
			\brief Overloaded the dereference operator
			\return returns the data pointed to by the iterator
			*/
			T& operator*();
			/*!
			\fn operator*() const
			\brief Overloaded the dereference operator
			\return returns a const reference to the data pointed to by the iterator
			*/
			const T& operator*() const;
			/*!
			\fn ~Iterator()
			\brief Destructor that clears the Iterator
			*/
			~Iterator();
		private:
			/*!
			\fn Iterator(const Vector *rhs, std::uint32_t index )
			\brief An overloaded constructor
			\param the list the iterator should point to and the element in the list
			*/
			Iterator(const Vector *rhs, std::uint32_t index);
			/*!
			\var const Vector *Owner
			\brief A const pointer to the owner of the iterator
			*/
			const Vector *Owner;
			/*!
			\var std::uint32_t Index
			\brief The index of the vector that the iterator points to
			*/
			std::uint32_t Index;
			friend class Vector;
		};
#pragma endregion

	
	private:
		/*!
		\var std::uint32_t Capacity
		\brief The maximum number of elements the Vector can hold
		*/
		std::uint32_t Capacity;
		/*!
		\var std::uint32_t Size;
		\brief The number of elements in the VEctor 
		*/
		std::uint32_t Size;
		/*!
		\var T* Array
		\brief A pointer to the element to be held by the vector
		*/
		T *Array;
		/*!
		\var IncrementFunctor ReserveStrategy
		\brief A functor object 
		*/
		static IncrementFunctor ReserveStrategy;
	};
#pragma endregion
}


#include"Vector.inl"