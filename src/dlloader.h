/*
 * dlloader.h
 *
 *  Created on: 20 févr. 2013
 *      Author: ljrh4054
 */

#ifndef DLLOADER_H_
#define DLLOADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

void * dlloader_load(char * filename);

void * dlloader_selfload();

int dlloader_destroy(void * handle);

void * dlloader_get(void * handle, char * funcname);

#endif /* DLLOADER_H_ */
