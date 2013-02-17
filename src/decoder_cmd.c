/*
 * decoder_cmd.c
 *
 *  Created on: 14 févr. 2013
 *      Author: ljrh4054
 */
#include "../src/decoder.h"
#include "../src/hashmap.h"

void print_hashmap(char * key, void * value)
{
	fprintf(stdout,"%s ---> %s\n",key,(char *) value);
}

int main(int argc, char **argv)
{
	hashmap_t * map;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s string\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	map = (hashmap_t *)malloc(sizeof(hashmap_t));

	hashmap_init(map);

	decode(argv[1], map);

	hashmap_iterate(map,print_hashmap);

	hashmap_delete_all(map);

	hashmap_free(map);
	free(map);

	exit(0);
}

