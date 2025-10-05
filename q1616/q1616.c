#include <stdint.h>
#include <string.h>

#include "q1616.h"

#define Q 16
#define K (1 << (Q - 1))

static int64_t h_saturate(int64_t n)
{
	if (n > 0x7fffffffLL)
		n = 0x7fffffffLL;
	if (n < -0x80000000LL)
		n = -0x80000000LL;

	return n;
}

q1616 q1616_add(q1616 a, q1616 b)
{
	int64_t tmp;
	tmp = (int64_t)a + (int64_t)b;
	tmp = h_saturate(tmp);

	return (q1616)tmp;
}

q1616 q1616_subtract(q1616 a, q1616 b)
{
	int64_t tmp;
	tmp = (int64_t)a - (int64_t)b;
	return (q1616)tmp;
}

q1616 q1616_multiply(q1616 a, q1616 b)
{
	int64_t tmp = (int64_t)a * (int64_t)b;
	tmp >>= Q;
	return (q1616)h_saturate(tmp);
}

q1616 q1616_divide(q1616 a, q1616 b)
{
	int64_t tmp = ((int64_t)a << Q) / b;
	return (q1616)h_saturate(tmp);
}
