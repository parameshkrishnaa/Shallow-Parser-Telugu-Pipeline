/**
 * FILE Name :delete_yv.c
*/


/** delete_yv
 * This function is used to delete characters y and v in starting of the word
 * The arguments: * morph of char type
 * Return : char type and returns the new_morph after deleting y and v
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./common/analyser/morph_logger.h"


extern FILE *log_file;
#define FUNCTION "delete_yv()"


char *delete_yv(morph)
char *morph;		/* input word pointer */
{
	char *program_name="delete_yv.c";
        PRINT_LOG(log_file," This function is used to delete characters y and v in starting of the word");

	char *new_morph;	/* current morph pointer */
	morph++;
	new_morph = morph;
	return (new_morph);
}
