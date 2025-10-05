#include <stdint.h>

uint16_t rstate = 0xdead;

uint16_t xorshift16()
{
	rstate ^= rstate << 7;
	rstate ^= rstate >> 9;
	return rstate ^= rstate << 8;
}
