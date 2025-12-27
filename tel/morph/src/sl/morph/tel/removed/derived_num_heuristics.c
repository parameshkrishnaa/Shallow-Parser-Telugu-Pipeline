/**
 * FILE Name :derived_num_heuristics.c
*/

/** derived_num_heuristics
 * This function derives numerical values 
 *The arguments:
 * root of char type ,pdgm of char type, DBM_FLAG of int type ,db_lex of GDBM_LEX file type
 * ans_root of char type, aux_verb of char type
 * integer pointer
 * Return : void
 */

 /* HEADER FILES */
#include <gdbm.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./headers/defn.h"
#include "./headers/struct.h"
#include "./headers/struct1.h"
#include "./common/analyser/morph_logger.h"


extern FILE *log_file;
#define FUNCTION "derived_num_heuristics()"

extern int DEBUG;	/* is used for checking existance of root */

extern int sizeof_num_suff;
/* suff_info structure contains info of suffix, add, pdgm, category, offset */
extern struct suff_info num_suff_ar[];

/**
 * Prototypes of the functions in this file with a file scope
 */
extern void get_derived_rt();

void derived_num_heuristics(root,pdgm,DBM_FLAG,db_lex,ans_root)

  char root[SUFFWORDSIZE],pdgm[WORD_SIZE];	/* root of the word, paradigm */
  int DBM_FLAG;					/* global dictionary flag ,if 1 then
                                               dictionary is there */
  GDBM_FILE db_lex;				/* GNU database manager includes dbm and ndb
                                   compatability and db_flex is used for opening file */

  char ans_root[SUFFWORDSIZE];		/*  root after derivation */
     {
	char *program_name="derived_num_heuristics.c";
        PRINT_LOG(log_file," ");
	int len,derived_root;		/* length of the root,derived root,  */
	char tmp_root[SUFFWORDSIZE];	/* temporary root */
	char suff[SUFFWORDSIZE];	/* suffix of the word */
	char offset_aux_str[SUFFWORDSIZE];	/* offset_aux_string */

	len = strlen(root);   /* finding the length of the root */
	strcpy(tmp_root,root);  /* copying the root to temporary root */

	derived_root = 0;	/* intialising derived_root to 0 */
	ans_root[0] = '\0';	/* intialising ans_root to null */


	if(DEBUG && derived_root)	/* executes when word and derived_root exists */
	  {
	     printf("%s\n",ans_root);	/* prints the final root after adjectives are added */
	     printf("%d\n",derived_root);/* prints the derived root */
	  }
     }
