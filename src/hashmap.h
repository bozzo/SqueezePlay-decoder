/*
 * hashmap.h
 *
 * This file is part of SqueezePlay decoder.
 *
 * SqueezePlay decoder is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SqueezePlay decoder is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with com_mapfactory. If not, see <http://www.gnu.org/licenses/>.
 *
 * Created on 14 févr. 2013
 * By bozzo
 *
 **/

#ifndef HASHMAP_H_
#define HASHMAP_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "uthash.h"

typedef struct hashmap_node {
	char * key;
	void * object;
	UT_hash_handle hh; /* makes this structure hashable */
} hashmap_node_t;

typedef struct hashmap {
	hashmap_node_t * map;
	pthread_rwlock_t lock;
} hashmap_t;

/**
 * initialize the hashmap
 */
int hashmap_init(hashmap_t * map);

/**
 * Delete map structure, doesn't free the hashmap.
 */
int hashmap_free(hashmap_t * map);

/**
 * set the object at the key index
 */
int hashmap_set(hashmap_t * map, char * key, void * object);

/**
 * get the element key if found
 */
void * hashmap_get(hashmap_t * map, char * key);

/**
 * get and remove the element key if found
 */
void * hashmap_pop(hashmap_t * map, char * key);

/**
 * count element in hashmap
 */
int hashmap_count(hashmap_t * map);

/**
 * Delete all elements
 */
int hashmap_delete_all(hashmap_t * map);

/**
 * iterate on all elements
 */
int hashmap_iterate(hashmap_t * map, void (*ptr_func)(char *, void *));

#endif /* HASHMAP_H_ */
