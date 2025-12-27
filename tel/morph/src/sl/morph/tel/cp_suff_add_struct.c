/**
 * File Name: cp_suff_add_struct.c
*/

/** cp_suff_add_struct
 * This function adds the suffix to the root word
 * it takes arguments:
 * suff_add and ch_ar of char type
 * Return : void
 */

/* HEADER FILES */

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "./headers/struct1.h"
#include "./headers/struct.h"
#include "morph_logger.h"


//FILE *log_file;
#define FUNCTION "cp_suff_add_struct()"

cp_suff_add_struct(suff_add,ch_ar)

char suff_add[SUFFWORDSIZE];	/* suffix word */
char ch_ar[SUFFWORDSIZE];	/* added to the root word */
{
	char *program_name = "cp_suff_add_struct.c";
       // PRINT_LOG(log_file," This function adds the suffix to the root word ");

	struct suff_add_info dummy;/* structure  contains details of suffix */
	int loop1,size;		   /* size of suffix */
	loop1=0;
	size=sizeof(dummy);
	for(loop1=0;loop1<size;loop1++)	/* if loop equal size. where size is
                                           size of  object dummmy of suff_add_info */
	suff_add[loop1]=*ch_ar++;
}
