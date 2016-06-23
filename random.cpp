#include <stdlib.h>
#include"baseTypes.h"
#include "random.h"
float_t getRangedRandom(float_t min, float_t max)
{
    int r = rand();

    float_t r1 = (float)r/(float)RAND_MAX;

    r1 *= (max-min);

    r1 += min;

    return r1;
}
int getRangedRandom(int min, int max)
{
    int r = rand();

    float_t r2 = (float)r/(float)RAND_MAX;

    r2 *= ((float)max-(float)min);
	int r1 = (int) r2;

    r1 += min;

    return r1;

}