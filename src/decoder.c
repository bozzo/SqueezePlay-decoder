/*
 * decoder.c
 *
 *  Created on: 15 févr. 2013
 *      Author: ljrh4054
 */
#include "decoder.h"

int decode(char * inputStr, hashmap_t * map)
{
	char * pch, * tmp, * key, * value;
	char *saveptr1, *saveptr2;

	/* split input string */
	pch = strtok_r (inputStr," ", &saveptr1);
	while (pch != NULL)
	{
		/* url decode the part */
		tmp = url_decode(pch);

		key = strtok_r (tmp,":", &saveptr2);
		value = strtok_r (NULL,":", &saveptr2);

		/* put it into hashmap */
		if (hashmap_set(map,key,value) < 0)
		{
			fprintf(stderr,"can't set decode string into hashmap (%s/%s)\n",key,value);
			return -1;
		}

		/* continue */
		pch = strtok_r (NULL," ", &saveptr1);
	}
	return 0;
}
