/**
 * File Name : isvowel.c
 */


/** Function : isvowel()
 * This function checks whether the given word's first character contains vowel or not .
 * If it is true it returns the numeric value 1 else 0.
 * it takes ch of char type as argument. whrer ch is the input word's first char
 * Return :int , returns a numeric value indicating as a true if numeral 1 and 0 for false
 */


/* Header Files */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./common/analyser/morph_logger.h"


extern FILE *log_file;
#define FUNCTION "isvowel()"

int isvowel(ch)
char ch;
{
	char *program_name="isvowel.c"; 
	//  PRINT_LOG(log_file," This function checks whether the given word's first character contains vowel or not"); 
	if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' ) 
		/* indicates ch is vowel */
		return 1; 	
	else 
		/* indicates ch is not vowel */
		return 0;	
}

