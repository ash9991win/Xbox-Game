#pragma once
#include<cstdint>
namespace Library
{
	/*!
	\class ReservationFunctor
	\brief A functor that acts as the default reservation strategy, in case the user doesn't provide one */
	class DefaultFunctor
	{
	public:
		/*!
		\fn std::uint32_t operator()(std::uint32_t size, std::uint32_t capacity)
		\brief The overlaoded () operator which is the functor
		\params An unsigned int Size and an unsigned Int Capacity
		\return Returns a calculated new capacity of the Vector
		*/
		std::uint32_t operator()(std::uint32_t size, std::uint32_t capacity);

	};
}

