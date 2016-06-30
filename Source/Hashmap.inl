#include "Hashmap.h"
namespace Library
{
	
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	std::uint32_t Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::DefaultSize = 11;

	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Hashmap(std::uint32_t size = DefaultSize)
		:Buckets(size,true), BucketSize(size),NumberOfEntries(0)
	{
		if (size == 0)
			throw std::exception("Invalid initialization");
	}
	template<typename TKey, typename TData, typename HashFunctor, typename KeyCompareFunctor>
	Hashmap<TKey, TData, HashFunctor, KeyCompareFunctor>::Hashmap(std::initializer_list<PairType> val)
		:Hashmap()
	{
		for (auto& pair : val)
		{
			Insert(pair);
		}
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Hashmap(Hashmap&& rhs)
	{
		*this = std::move(rhs);
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>& Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::operator=(Hashmap&& rhs)
	{
		if (this != &rhs)
		{
			Buckets = std::move(rhs.Buckets);
			BucketSize = rhs.BucketSize;
			NumberOfEntries = rhs.NumberOfEntries;
			rhs.BucketSize = 0;
			rhs.NumberOfEntries = 0;
		}
		return *this;
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	typename Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Find(const TKey& key) const
	{
		static HashFunctor HashFunction;
		static KeyCompareFunctor CompareKeys;
		std::uint32_t Index = HashFunction(key) % BucketSize;
		if (!Buckets[Index].IsEmpty())
		{
			ChainType::Iterator ChainIterator = Buckets[Index].begin();
			while (ChainIterator != Buckets[Index].end())
			{
				if (CompareKeys((*ChainIterator).first,key))
				{
					return Iterator(this, ChainIterator, Index);
				}
				++ChainIterator;
			}
		}
			return end();
	}
	
	template<typename TKey, typename TData, typename HashFunctor, typename KeyCompareFunctor>
	typename Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator  Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Insert(const PairType& value)
	{
		Iterator FindIterator = Find(value.first) ;
		if (FindIterator == end())
		{
			static HashFunctor HashFunction;
			std::uint32_t index = HashFunction(value.first) % BucketSize;
			NumberOfEntries++;
			return Iterator(this, Buckets[index].PushBackWithIterator(value), index);
		}
		else
		{
			return FindIterator;
		}
	}
	template<typename TKey, typename TData, typename HashFunctor, typename KeyCompareFunctor>
	typename Hashmap<TKey, TData, HashFunctor, KeyCompareFunctor>::Iterator  Hashmap<TKey, TData, HashFunctor, KeyCompareFunctor>::Insert(const PairType& value, bool& result)
	{
		Iterator FindIterator = Find(value.first);
		if (FindIterator == end())
		{
			static HashFunctor HashFunction;
			std::uint32_t index = HashFunction(value.first) % BucketSize;
			NumberOfEntries++;
			result = true;
			return Iterator(this, Buckets[index].PushBackWithIterator(value), index);
		}
		else
		{
			result = false;
			return FindIterator;
		}
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	void Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::ReHash(std::uint32_t newBucketSize)
	{
		Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor> BufferMap(newBucketSize); 
		for (Iterator oldMapIter = begin(); oldMapIter != end(); ++oldMapIter)
		{
			BufferMap.Insert(*(oldMapIter));
		}
		*this = std::move(BufferMap);
	}
	
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	TData& Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::operator[](const TKey& value)
	{
		Iterator insertIterator = Insert(PairType(value, TData()));
		return (*insertIterator).second;
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	void Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Remove(const TKey& value)
	{
		Iterator RemoveIterator = Find(value);
		if (RemoveIterator != end())
		{
			Buckets[RemoveIterator.BucketIterator].Remove((*RemoveIterator));
			NumberOfEntries--;
		}
	}
	template<typename TKey, typename TData, typename HashFunctor, typename KeyCompareFunctor>
	 void Hashmap<TKey, TData, HashFunctor, KeyCompareFunctor>::Remove( Iterator& iter)
	{
		if (iter.Owner != this)
		{
			throw std::exception("Iterator does not belong to this map");
		}
		if (iter != end())
		{
			Buckets[iter.BucketIterator].Remove((*iter));
			NumberOfEntries--;
		}
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	void Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Clear()
	{
		for (auto& CurrentChain : Buckets)
		{
			CurrentChain.Clear();
		}
		NumberOfEntries = 0;
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	std::uint32_t Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Size() const
	{
		return BucketSize;
	}
	template<typename TKey, typename TData, typename HashFunctor, typename KeyCompareFunctor>
	std::uint32_t Hashmap<TKey, TData, HashFunctor, KeyCompareFunctor>::Count() const
	{
		return NumberOfEntries;
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	bool Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::ContainsKey(const TKey& value) const
	{
		return (Find(value) != end());
	}
	template<typename TKey, typename TData, typename HashFunctor, typename KeyCompareFunctor>
	 bool Hashmap<TKey, TData, HashFunctor, KeyCompareFunctor>::ContainsKey(const TKey & value,  TData& outval) const
	{
		Iterator iter = Find(value);
		if (iter == end())
		{
			return false;
		}
		outval = iter->second;
		return true;
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	typename Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::begin() const
	{
		std::uint32_t BucketIndex = 0;
		for (auto& CurrentChain : Buckets)
		{
			if (!CurrentChain.IsEmpty())
			{
				break;
			}
			BucketIndex++;
		}
		if (BucketIndex < BucketSize)
		{
			return Iterator(this, Buckets[BucketIndex].begin(), BucketIndex);
		}
		return end();
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	typename Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::end() const
	{
		return Iterator(this, Buckets[BucketSize-1].end(), BucketSize);
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	 Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator::Iterator()
		 : ChainIterator(),Owner(nullptr),BucketIterator(0)
	{
	}
	 template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	 Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator::Iterator(const Hashmap* newOwner, typename ChainType::Iterator chainIterator, std::uint32_t bucketIterator)
		 :Owner(newOwner),ChainIterator(chainIterator),BucketIterator(bucketIterator)
	 {
	 }
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	 Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator::Iterator(Iterator&& rhs)
	{
		*this = std::move(rhs);
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	typename Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator&  Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator::operator=(Iterator&& rhs)
	{
		if (this != &rhs)
		{
			Owner = rhs.Owner;
			ChainIterator = std::move(rhs.ChainIterator);
			BucketIterator = rhs.BucketIterator;
			rhs.Owner = nullptr;
			rhs.BucketIterator = 0;
		}
		return *this;
	}
	template<typename TKey, typename TData, typename HashFunctor, typename KeyCompareFunctor>
	typename Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator& Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator::operator++()
	{
		if (Owner == nullptr || BucketIterator >= Owner->BucketSize )
			throw std::exception("Invalid increment");

		if (++ChainIterator == Owner->Buckets[BucketIterator].end())
		{
			//Find the next non empty list
			++BucketIterator;
			while (BucketIterator < Owner->BucketSize)
			{
			
				if (!Owner->Buckets[BucketIterator].IsEmpty())
				{
					ChainIterator = Owner->Buckets[BucketIterator].begin();
					break;
				}
		   
				++BucketIterator;
			}
		}
		if (BucketIterator >= Owner->BucketSize)
		{
			*this =  Owner->end();
		}
		return *this;
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	typename Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator::operator++(int)
	{
		Iterator TempIterator = *this;
		operator++();
		return TempIterator;
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	std::pair<TKey,TData>& Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator::operator*() 
	{
		if (Owner == nullptr || BucketIterator >= Owner->BucketSize)
			throw std::exception("Invalid dereference");
		return (*ChainIterator);
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	std::pair<TKey, TData>* Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator::operator->() 
	{
		if (Owner == nullptr || BucketIterator >= Owner->BucketSize)
			throw std::exception("Invalid dereference");
		return &(*ChainIterator);
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	bool Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator::operator==(const Iterator& rhs) const
	{
		return ((Owner == rhs.Owner) && (ChainIterator == rhs.ChainIterator) && (BucketIterator == rhs.BucketIterator));
	}
	template<typename TKey, typename TData, typename HashFunctor,typename KeyCompareFunctor>
	bool Hashmap<TKey, TData, HashFunctor,KeyCompareFunctor>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(operator==(rhs));
	}
}