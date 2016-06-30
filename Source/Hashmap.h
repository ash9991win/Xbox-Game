#pragma once
#include<utility>
#include<cstdint>
#include"Vector.h"
#include"SList.h"
#include"EqualityFunctor.h"
namespace Library
{
	template<typename T>
	/*
	\class DefaultHashFunctor
	\brief A templated default hash function, in case the user doesn't provide any
	*/
	class DefaultHashFunctor
	{
	public:
		/*!
		\fn std::uint32_t operator()(std::uint32_t size, std::uint32_t capacity)
		\brief The overlaoded () operator which is the functor
		\params An unsigned int Size and an unsigned Int Capacity
		\return Returns a calculated index of the key
		*/
		std::uint32_t operator()(const T& keyValue) const
		{
			const unsigned char* Bytes = reinterpret_cast<const unsigned char*>(&keyValue);
			std::uint32_t Hash = 0;
			for (int i = 0; i < sizeof(keyValue); i++)
			{
				Hash ^= Bytes[i];
			}
			return Hash;
		}
	};
	template<>
	/*
	\class DefaultHashFunctor<char*>
	\brief A specialization of the  default hash function, in case the user doesn't provide any
	*/
	class DefaultHashFunctor<char*>
	{
	public:
		/*!
		\fn std::uint32_t operator()(std::uint32_t size, std::uint32_t capacity)
		\brief The overlaoded () operator which is the functor
		\params An unsigned int Size and an unsigned Int Capacity
		\return Returns a calculated index of the key
		*/
		std::uint32_t operator()(char* const& keyValue) const
		{
			std::uint32_t Hash = 0;
			for (std::uint32_t i = 0; i < strlen(keyValue); i++)
			{
				Hash ^= keyValue[i];
			}
			return Hash;
		}
	};
	template<>
	/*
	\class DefaultHashFunctor<char*>
	\brief A specialization of the  default hash function, in case the user doesn't provide any
	*/
	class DefaultHashFunctor<std::string>
	{
	public:
		/*!
		\fn std::uint32_t operator()(std::uint32_t size, std::uint32_t capacity)
		\brief The overlaoded () operator which is the functor
		\params An unsigned int Size and an unsigned Int Capacity
		\return Returns a calculated index of the key
		*/
		std::uint32_t DefaultHashFunctor<std::string>::operator()(const std::string&  keyValue) const
		{
			std::uint32_t Hash = 0;
			for (size_t i = 0; i < keyValue.length(); i++)
			{
				Hash ^= keyValue[i];
			}
			return Hash;
		}
	};
	template<typename TKey, typename TData, typename HashFunctor = DefaultHashFunctor<TKey>,typename KeyCompareFunctor = EqualityFunctor<TKey>>
	class Hashmap
	{
		typedef std::pair<TKey, TData> PairType;
		typedef SList<PairType> ChainType;
		typedef Vector<ChainType> BucketType;
	public:
		/*!
		\class Iterator
		\brief A nested class that helps in accessing the elements of the vector
		*/
		class Iterator
		{
			friend  Hashmap;
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
			Iterator(const Iterator& rhs) = default;
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
			Iterator& operator=(const Iterator& rhs) = default;
			/*!
			\fn operator=(const Iterator&)
			\brief The overloaded assignment operator
			\param A const reference to teh Iterator to be copied from
			\return Returns a reference to the Iterator
			*/
			Iterator& operator=(Iterator&& rhs);
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
			std::pair<TKey,TData>& operator*() ;
			/*!
			\fn operator*()
			\brief Overloaded the -> operator
			\return returns the data pointed to by the iterator
			*/
			std::pair<TKey, TData>* operator->() ;
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
			\fn ~Iterator()
			\brief Destructor that clears the Iterator
			*/
			~Iterator() = default;
		private:
			/*!
			\fn Iterator(const Hashmap*,typename ChainType::Iterator, std::uint32_t );
			\brief An overloaded constructor
			\param the list the iterator should point to and the element in the list
			*/
			Iterator(const Hashmap*,typename ChainType::Iterator, std::uint32_t );
			/*!
			\var const Hashmap *Owner
			\brief A const pointer to the owner of the iterator
			*/
			const Hashmap* Owner;
			/*!
			\var ChainType::Iterator ChainIterator
			\brief The node in the bucket that the iterator points to
			*/
			typename ChainType::Iterator ChainIterator;
			/*!
			\var std::uint32_t BucketIterator
			\brief The index of the bucket that the iterator points to
			*/
			std::uint32_t BucketIterator;
		};
		/*!
		\fn Vector(std::uint32_t size)
		\brief A parameterized ctor of the Hashmap class
		\param The new capacity to be reserved for the bucket
		*/
		explicit Hashmap(std::uint32_t size = DefaultSize);
		/*!
		\fn Hashmap(const Hashmap& rhs)
		\brief The copy ctor of the Hashmap class which performs a deep copy
		*/
		Hashmap(const Hashmap& rhs)= default;

		Hashmap(std::initializer_list<PairType> val);
		/*!
		\fn Hashmap(Hashmap&& rhs)
		\brief The move ctor
		\param A RValue reference for the Hashmap to be moved from
		*/
		Hashmap(Hashmap&& rhs);
		/*!
		\fn operator=(const Hashmap& rhs)
		\brief The overloaded assignment operator
		\param A reference for the Hashmap to be copied from
		*/
		Hashmap& operator=(const Hashmap& rhs) = default;
		/*!
		\fn operator=(Hashmap&& rhs)
		\brief The move assignment operator
		\param A RValue reference for the Hashmap to be moved from
		*/
		Hashmap& operator=(Hashmap&& rhs);
		/*!
		\fin Find(const T& data) const
		\brief Finds the key in teh hashmap and returns an iterator to it
		\return Returns an iterator to the found element ( end if not found)
		*/
		Iterator Find(const TKey& value) const;
		/*!
		\fin Insert(const Pairtype& data) 
		\brief Inserts the pair into the map, if the key already exists, returns a reference to the existing key
		\return Returns an iterator to the inserted or found data
		*/
		Iterator Insert(const PairType& value);
		/*!
		\fn  operator[](std::uint32_t index)
		\brief The overlaoded [] operator which checks if the given key exists, if yes returns a reference to it else inserts a key and returns a reference
		\param An index, the reference of the Value at which has to be returned 
		\return Returns a reference to the value stored in the hashmap or the created data
		*/
		Iterator Insert(const PairType& value, bool& result);
		TData& operator[](const TKey& value);
		/*!
		\fn Remove(const T& data)
		\brief Removes the element passed in
		*/
		void Remove(const TKey& value);
		void Remove( Iterator& iter);
		/*!
		\fn Clear()
		\brief Clears the chains of the map
		*/
		void Clear();
		/*!
		\fn GetSize() const
		\brief Returns the number of buckets in the map
		\return The Size of the map
		*/
		std::uint32_t Size() const;
		/*!
		\fn GetSize() const
		\brief Returns the number of elements in the map
		\return The Size of the map
		*/
		std::uint32_t Count() const;
		/*!
		\fn ContainsKey(const TKey& value) const
		\brief Check if the given key is present in the map
		\return True, if the key is found and false if not
		*/
		bool ContainsKey(const TKey& value) const;
		bool ContainsKey(const TKey& value,  TData& outval) const;
		/*!
		\fn begin() const
		\brief Returns an iterator pointing to the first element of the map
		\return An Iterator to the first element
		*/
		Iterator begin() const;
		/*!
		\fn end() const
		\brief Returns an iterator pointing to the end of the map
		\return An Iterator to the end
		*/
		Iterator end() const;
		/*!
		\fn Rehash(newCapacity)
		\brief Reallocates the map with the number of buckets changed to what was passed in
		\param The bucket to be passed into 
		*/
		void ReHash(std::uint32_t newBucketSize);
		/*!
		\fn ~Hashmap()
		\brief Destructor that clears the map
		*/
		~Hashmap() = default;
		
	private:
		/*!
		\var BucketType Buckets
		\brief A Vector of SLists the is the buckets of the map
		*/
		BucketType Buckets;
		/*!
		\var std::uint32_t BucketSize
		\brief The  number of buckets that the map has
		*/
		std::uint32_t BucketSize;
		/*!
		\var NumbereOfEntries
		\brief The number of key-value pairs the map holds
		*/
		std::uint32_t NumberOfEntries;
		/*!
		\var DefaultSize
		\brief A static variable that the map holds in case the user fails to provide one
		*/
		static std::uint32_t DefaultSize;
		Iterator Find(const TKey& value, std::uint32_t& index) const;

	};
}
#include"Hashmap.inl"