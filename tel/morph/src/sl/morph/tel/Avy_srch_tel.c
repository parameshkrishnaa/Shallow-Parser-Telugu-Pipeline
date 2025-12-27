/**
 * File Name : Avy_srch_tel.c
 */


/** Function : Avy_srch_tel
 * Avy_srch(morph)
 * This function checks whether the given word is Avy or not.
 * If it is true it returns the numeric value.
 * it takes morph of char type as argument. whrer morph is the input word
 * Return :int , returns a numeric value indicating as a numeral or a special
 * character
 */


/* Header Files */
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "./headers/defn.h"
#include "./headers/struct1.h"
#include "./common/analyser/morph_logger.h"


extern FILE *log_file;
extern char *logmsg;
#define FUNCTION "AVY_srch()"

extern int sizeof_ind;                  /* table size */
extern char indword[][AVYWORDSIZE];     /* table start address */


int AVY_srch(morph) 

/* input word */
char morph[Morphsize];		
{ 
	char *program_name="Avy_srch_tel.c";
       	// PRINT_LOG(log_file," checks whether the given word is Avy or not");
	
	/* to read the characters of the word */
	int loop1;		

	/* tmp to store the word */
	char *tmp;		

	/* allocates  size  bytes and returns a pointer to 
	 * the allocated memory.The memory is not cleared. 
	 * */ 
	void  *malloc();	

	/* pointer of avy , dummy avy */ 
	char dummy_avy[AVYWORDSIZE];

	/* structre contains details of 
	 * avy_dict and declared object pointer avy_ptr 
	 * */
	struct avy_dict  *avy_ptr; 
	void  *my_bsearch(); 

	/* size of the morph */ 
	int morph_size;            
	int ISNUMBER;              
	/* for checking given morph word is number or not */ 
	/********to check if given word is nonalphabet ********/ 

	/* finding length of the morph */ 
	morph_size=strlen(morph);	
	//sprintf(logmsg,"loop1=%d|morph_size=%d|morph=|%s|",loop1,morph_size,morph);PRINT_LOG(log_file,logmsg);
	ISNUMBER = 1;   
	/* check if loop is alpha numeric or not */ 
	for (loop1 = 0;loop1 <= morph_size; ++loop1) 
		/* if morph is alpha numeric */
		if(isalpha(morph[loop1])) { 
			ISNUMBER = 0; 
			break; 
		} 
		if (ISNUMBER) {
	        	return(-3); /* numeral */ 
		} 
		else {   
			/********searching in avy file **********************/ 
			/* this function returns the ptr to the location of the key in the table, 
			 * if it is present else returns a null 
			 * */ 
			avy_ptr=(struct avy_dict *)my_bsearch(morph, \
			(char *)indword,sizeof_ind,sizeof(indword[0]),strcmp); 
			
			/*   SEARCHED IN AVY FILE */ 
			if (avy_ptr != NULL) { 
				return (-1); 
			} 
			else 
			return (-2); 
			/* Neither a numeral nor an avy */ 
		}
}
