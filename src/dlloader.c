/*
 * dlloader.c
 *
 *  Created on: 20 févr. 2013
 *      Author: ljrh4054
 */

#include "dlloader.h"

void * dlloader_load(char * filename)
{
	void * handle;

	handle = dlopen (filename, RTLD_LAZY);
	if (! handle) {
		fputs (dlerror (), stderr);
		return NULL;
	}
	return handle;
}

void * dlloader_selfload()
{
	return dlloader_load(NULL);
}

int dlloader_destroy(void * handle)
{
	dlclose(handle);
	return 0;
}

void * dlloader_get(void * handle, char * funcname)
{
	void * ptr;
	char * erreur;

	ptr = dlsym (handle, funcname);
	if ((erreur = dlerror()) != NULL)  {
		fprintf (stderr, "%s", erreur);
		return NULL;
	}
	return ptr;
}


