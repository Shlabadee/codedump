#include <stdint.h>
#ifdef DEBUG
	#include <stdio.h>
#endif

#include <string.h>

unsigned int gtdigitcount(uint32_t value)
{
	unsigned int count = 0;
	while (value > 0)
	{
		++count;
		value /= 10;
	}
	return count;
}

unsigned int gtmoneystr(char* str, uint32_t value)
{
	if (value == 0)
	{
		strcpy(str, "0.00");
		return 4;
	}

	unsigned int digitcount = gtdigitcount(value);
	unsigned int nullpos;
	unsigned int pointpos;
	unsigned int commapos = INT32_MAX;
	unsigned int strsize;
	if (digitcount > 6)
	{
		strcpy(str, "TOOBIG!");
		return 0;
	}

#ifdef DEBUG
	memset(str, ' ', 8);
#else
	memset(str, 0, 8);
#endif

	if (digitcount < 4)
	{
		digitcount = 3;
		strsize = 5;
		pointpos = 1;
	}
	else
	{
		// digitcount + the point + the null terminator
		strsize = digitcount + 1 + 1;
		pointpos = digitcount - 2;
	}

	nullpos = strsize - 1;

	if (digitcount > 5)
	{
		commapos = 1;
		++strsize;
		++pointpos;
		++nullpos;
		str[commapos] = ',';
	}

#ifdef DEBUG
	printf("\t     value: %u\n", value);
	printf("\tdigitcount: %u\n", digitcount);
	printf("\t   nullpos: %u\n", nullpos);
	printf("\t  pointpos: %u\n", pointpos);
	printf("\t  commapos: %u\n", commapos);
	printf("\t   strsize: %u\n", strsize);
#endif

	str[pointpos] = '.';
	str[nullpos] = '\0';

	for (int i = strsize - 2; i >= 0; --i)
	{
		if (i == pointpos || i == commapos)
		{

#ifdef DEBUG
			printf("\t\t%i: .\n", i);
#endif
			continue;
		}

		const char m = (value % 10) + '0';
		value /= 10;
		str[i] = m;

#ifdef DEBUG
		printf("\t\t%i: %s\n", i, str);
#endif
	}

	return strsize;
}
