/**
 * File Name:chk_uword_dict.c
*/

/**Function Name: chk_uword_dict
 * This function checks the Unkown word is present in the UDictionaryor not
 * It takes arguments:
 * word of char type ,base of char type, width of char type, nel of int type,
 * answer of char type, compar is function with int return type,
 * DBM_FLAG of iint type and
 * db object of DBM
 * Return void
 */


/* HEADER FILES */

#include <string.h>
#include <stdio.h>
#include <gdbm.h>
#include<stdlib.h>
#include <fcntl.h>
#include "headers/defn.h"
#include "headers/struct1.h"
#include "./common/analyser/morph_logger.h"

extern FILE *log_file;
#define FUNCTION "chk_uword_dict()"


/**
 * Prototypes of the functions in this file with a file scope
 */
extern char * my_blk_bsearch();

void chk_uword_dict(word,base,nel,width,compar,answer,DBM_FLAG,db)

/* base address of the table, word is input word */
char base[WORD_SIZE],word[WORD_SIZE];  

/* nel is table size and table width */
int nel,width;                         
int (*compar)();

/* answer is the word after search */
char answer[200];                      

/* global dictionary flag,if 1 then dictionary is there */
int DBM_FLAG;                       

/* GNU database manager includes dbm and ndb 
 * compatability and db is used for opening file 
 * */
GDBM_FILE db;                          
{
	char *program_name="chk_uword_dict.c";
	//PRINT_LOG(log_file, " This function checks the Unkown word is present in the UDictionaryor not"); 
	
	/* datum is function of gdbm , 
	 * db_tag is key and db_out is content 
	 * */ 
	datum db_tag,db_out;              

	/* uword_dict structure contains source 
	 * language and target language words 
	 * */ 
	struct uword_dict *tag_out;       
	
	/* If DBM_FLAG is true ie dictionary is existing */ 
	if(DBM_FLAG) { 
		db_tag.dptr = word; 
		db_tag.dsize = strlen(word); 
		db_out = gdbm_fetch(db,db_tag); 

		/* if morph size is not equal null */
		if(db_out.dptr != '\0')	{ 
			strncpy(answer,db_out.dptr,db_out.dsize); 
			answer[db_out.dsize] = '\0'; 
		} else				
		answer[0]='\0'; /* if zero then answer is null */
	} else {
	  
	  /* This function returns the ptr to the location 
	   * of the key in the table, 
	   * if it is present  else returns a null 
	   * */ 
	  tag_out = (struct uword_dict *)my_blk_bsearch(word,base,nel,width,compar); 

	  /* if tag_out is not equal to null copy tl_word to answer */
	  if(tag_out != '\0')	
	  strcpy(answer,tag_out->tl_word);
	  else				/* answer is equal to null */
	    answer[0]='\0';
       } 
}
