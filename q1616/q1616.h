#ifndef Q1616_H
#define Q1616_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef union Q1616 {
	int32_t raw;
	struct
	{
		int16_t integer;
		uint16_t fraction;
	};
} Q1616;

Q1616 Q1616_add(Q1616 a, Q1616 b);
Q1616 Q1616_subtract(Q1616 a, Q1616 b);
Q1616 Q1616_multiply(Q1616 a, Q1616 b);
Q1616 Q1616_divide(Q1616 a, Q1616 b);
Q1616 Q1616_from_float(float f);
float Q1616_to_float(Q1616 q);

#ifdef __cplusplus
}
#endif

#endif // Q1616_H
