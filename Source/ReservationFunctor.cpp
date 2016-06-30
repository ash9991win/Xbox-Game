#include "ReservationFunctor.h"
namespace Library
{
	std::uint32_t DefaultFunctor::operator()(std::uint32_t size, std::uint32_t capacity)
	{
		if (capacity == 0)
		{
			return 3U;
		}
		else
		{
			return (capacity * 2);
		}
	}
}