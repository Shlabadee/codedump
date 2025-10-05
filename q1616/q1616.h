#ifndef Q1616_H
#define Q1616_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef int32_t q1616;

q1616 q1616_add(q1616 a, q1616 b);
q1616 q1616_subtract(q1616 a, q1616 b);
q1616 q1616_multiply(q1616 a, q1616 b);
q1616 q1616_divide(q1616 a, q1616 b);

#ifdef __cplusplus
}
#endif

#endif // Q1616_H
