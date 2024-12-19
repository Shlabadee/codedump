#include <stdint.h>

// Converts double word to catena.
// https://en.wikipedia.org/wiki/Word_(computer_architecture)#cite_note-Dreyfus_1958_Gamma60-3
void dw2ctn(const int32_t input, uint8_t* output)
{
	int32_t truncated = input & 0xffffff;

	if (input < 0)
	{
		truncated |= 0xff000000;
	}

	output[0] = (uint8_t)(truncated & 0xff);         // least significant byte
	output[1] = (uint8_t)((truncated >> 8) & 0xff);  // middle byte
	output[2] = (uint8_t)((truncated >> 16) & 0xff); // most significant byte
}

// Converts catenda to double word.
int32_t ctn2dw(const uint8_t* input)
{
	int32_t result = (input[0] & 0xff) | ((input[1] & 0xff) << 8) | ((input[2] & 0xff) << 16);

	if (result & 0x800000)
	{
		result |= 0xff000000;
	}

	return result;
}
