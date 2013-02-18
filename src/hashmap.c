/*
 * hashmap.c
 *
 *  Created on: 14 févr. 2013
 *      Author: ljrh4054
 */

#include "hashmap.h"

int hashmap_init(hashmap_t * map) {
	map->map = NULL;
	if (pthread_rwlock_init(&map->lock,NULL) != 0) {
		fprintf(stderr,"lock init failed\n");
		return -1;
	}
	return 0;
}

int hashmap_free(hashmap_t * map) {
	if (pthread_rwlock_destroy(&map->lock) != 0) {
		fprintf(stderr,"lock destroy failed\n");
		return -1;
	}
	return 0;
}

int hashmap_set(hashmap_t * map, char * key, void * object) {
	hashmap_node_t * newnode;

	if (pthread_rwlock_wrlock(&map->lock) != 0) {
		fprintf(stderr,"can't acquire write lock\n");
		return -1;
	}
	HASH_FIND_STR(map->map, key, newnode);
	if (newnode) {
		/* HASH_DEL(elts, e); */
		/* num_deld++; */
	} else {
		newnode = (hashmap_node_t *)malloc(sizeof(hashmap_node_t));
		if (!newnode) return -1;
		/*newnode->key = (char *)malloc(strlen(key) * sizeof(char));
		strcpy(newnode->key, key);
		HASH_ADD_STR(map->map, key, newnode);*/
		newnode->key = key;
		HASH_ADD_KEYPTR(hh, map->map, newnode->key, strlen(newnode->key), newnode);
	}
	newnode->object=object;
	pthread_rwlock_unlock(&map->lock);
	return 0;
}

void * hashmap_get(hashmap_t * map, char * key) {
	hashmap_node_t * node;

	if (pthread_rwlock_rdlock(&map->lock) != 0) {
		fprintf(stderr,"can't acquire read lock\n");
		return NULL;
	}
	HASH_FIND_STR(map->map, key, node);
	pthread_rwlock_unlock(&map->lock);

	if (node) {
		return node->object;
	} else {
		return NULL;
	}
}

void * hashmap_pop(hashmap_t * map, char * key) {
	hashmap_node_t * oldnode;
	void * object;

	if (pthread_rwlock_wrlock(&map->lock) != 0) {
		fprintf(stderr,"can't acquire read lock\n");
		return NULL;
	}
	HASH_FIND_STR(map->map, key, oldnode);
	if (oldnode) {
		object = oldnode->object;
		HASH_DEL(map->map, oldnode);
	} else {
		pthread_rwlock_unlock(&map->lock);
		return NULL;
	}

	free(oldnode);
	pthread_rwlock_unlock(&map->lock);

	return object;
}

int hashmap_count(hashmap_t * map) {
	unsigned int num;
	if (pthread_rwlock_rdlock(&map->lock) != 0) {
		fprintf(stderr,"can't acquire read lock\n");
		return -1;
	}
	num = HASH_COUNT(map->map);
	pthread_rwlock_unlock(&map->lock);

	return num;
}

int hashmap_delete_all(hashmap_t * map)
{
	hashmap_node_t * oldnode, * tmp;

	if (pthread_rwlock_wrlock(&map->lock) != 0) {
		fprintf(stderr,"can't acquire read lock\n");
		return -1;
	}
	HASH_ITER(hh, map->map, oldnode, tmp) {
		HASH_DEL(map->map,oldnode);  /* delete; users advances to next */
		free(oldnode->key);
		free(oldnode);            /* optional- if you want to free  */
	}
	pthread_rwlock_unlock(&map->lock);
	return 0;
}

/**
 * iterate on all elements
 */
int hashmap_iterate(hashmap_t * map, void (*ptr_func)(char *, void *))
{
	hashmap_node_t * oldnode, * tmp;

	if (pthread_rwlock_rdlock(&map->lock) != 0) {
		fprintf(stderr,"can't acquire read lock\n");
		return -1;
	}
	HASH_ITER(hh, map->map, oldnode, tmp) {
		(*ptr_func)(oldnode->key,oldnode->object);
	}
	pthread_rwlock_unlock(&map->lock);
	return 0;
}
