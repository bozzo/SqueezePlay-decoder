/*
 * decoder.h
 *
 *  Created on: 14 févr. 2013
 *      Author: ljrh4054
 */

#ifndef DECODER_H_
#define DECODER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashmap.h"
#include "urlcoder.h"

int decode(char * inputStr, hashmap_t * map);

#endif /* DECODER_H_ */
