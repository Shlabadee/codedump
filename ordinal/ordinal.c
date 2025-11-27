#include "ordinal.h"

#define ORDINAL_TH 0
#define ORDINAL_ST 1
#define ORDINAL_ND 2
#define ORDINAL_RD 3

static const char* ordinals[] = {"th", "st", "nd", "rd"};

const char* get_ordinal(unsigned int number)
{
	unsigned int ordid;
	unsigned int u100 = number % 100;

	if (u100 > 10 && u100 < 20)
	{
		ordid = ORDINAL_TH;
	}
	else
	{
		switch (number % 10)
		{
			case 1:
				ordid = ORDINAL_ST;
				break;
			case 2:
				ordid = ORDINAL_ND;
				break;
			case 3:
				ordid = ORDINAL_RD;
				break;
			default:
				ordid = ORDINAL_TH;
				break;
		}
	}

	return ordinals[ordid];
}
