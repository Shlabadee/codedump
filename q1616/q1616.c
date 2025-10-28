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

Q1616 Q1616_add(Q1616 a, Q1616 b)
{
	Q1616 q;
	int64_t tmp;
	tmp = (int64_t)a.raw + (int64_t)b.raw;
	tmp = h_saturate(tmp);
	q.raw = (int32_t)tmp;
	return q;
}

Q1616 Q1616_subtract(Q1616 a, Q1616 b)
{
	Q1616 q;
	int64_t tmp;
	tmp = (int64_t)a.raw - (int64_t)b.raw;
	q.raw = (int32_t)tmp;
	return q;
}

Q1616 Q1616_multiply(Q1616 a, Q1616 b)
{
	Q1616 q;
	int64_t tmp;
	tmp = (int64_t)a.raw * (int64_t)b.raw;
	tmp = h_saturate(tmp);
	q.raw = (int32_t)tmp;
	return q;
}

Q1616 Q1616_divide(Q1616 a, Q1616 b)
{
	Q1616 q;
	int64_t tmp;
	tmp = ((int64_t)a.raw << Q) / b.raw;
	tmp = h_saturate(tmp);
	q.raw = (int32_t)tmp;
	return q;
}

Q1616 Q1616_from_float(float f)
{
	Q1616 q;
	q.integer = (int16_t)f;
	f -= (float)q.integer;
	q.fraction = (uint16_t)(f * 65536.f);
	return q;
}

float Q1616_to_float(Q1616 q)
{
	float f;
	f = (float)q.integer;
	f += (float)q.fraction / 65536.f;
	return f;
}
