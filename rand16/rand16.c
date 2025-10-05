#include <stdint.h>

uint16_t rstate = 0xdead;

uint16_t xorshift16()
{
	rstate ^= rstate << 5;
	rstate ^= rstate >> 3;
	return rstate ^= rstate << 7;
}
