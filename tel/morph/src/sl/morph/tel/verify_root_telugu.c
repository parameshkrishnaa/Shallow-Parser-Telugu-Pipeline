/**
 * FILE NAME : verify_root_telugu.c
*/

/** Function : verify_root
 *  This function compares the guessed root , paradigm,category with the data in the dictionary
 *  It takes arguments: INFLTNL of int type,guessed_root of char array ,pdgm of char array,
 *  cat of char array ,offset of int type ,ans_table is object of lex_info structure
 *  ans_ar is object of the structure os ans_struct, loop2 is integer file pointer
 *  DBM_FLAG is of int type and db is object of file dbm
 *  Return : void
 */

/* HEADER FILES */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gdbm.h>

#include "./headers/defn.h"
#include "./headers/struct.h"
#include "./headers/struct1.h"
#include "./common/analyser/morph_logger.h"

extern char *program_name;
extern char *logmsg;
extern FILE *log_file;
#define FUNCTION "verify_root()"

/**
 * Prototypes of the functions in this file with a file scope
 */

extern int match_in_dict();
extern void match_in_hypothetical_dict();
extern int direct_ans_flag;
extern int DEBUG_NEW;
extern int INFLTNL;

//extern struct lex_info lex_ar[];       
/* structure contains lexical info of word,paradigm,
                                    category,priority */
//extern int sizeof_lex;


void verify_root(INFLTNL,guessed_root,pdgm,cat,offset,ans_table,ans_ar,loop2,DBM_FLAG,db_lex)

  char guessed_root[SUFFWORDSIZE],pdgm[WORD_SIZE],cat[CATEGORYWORDSIZE];
   int offset,*loop2; /* offset for cases ie direct or indirect case */

   struct lex_info ans_table[SmallArray]; /* lexical structure object , structure contains
                                          details of word , paradigm,category ,priority */
   struct ans_struct ans_ar[Arraysize];/* ans_struct structure object, this structure contains
                                          root,offset,auxilary verb and paradigm */
   int DBM_FLAG,INFLTNL; /*global dictionary flag */

   GDBM_FILE db_lex;            /* GNU database manager includes dbm and ndb
                                            compatability and db_flex is used for opening file */

     {
	char *program_name= "verify_root_telugu.c";
//        PRINT_LOG(log_file,"This function compares the guessed root , paradigm,category with the data in the dictionary ");
	int match1;		/* matching root */
	int pos1;
	char ans_root[SUFFWORDSIZE];/* final root answer */
	char aux_verb[SUFFWORDSIZE];/* auxilary verb */
	
	aux_verb[0] = '\0';		/* intialising aux_verb to null */
	match1 = 0;

	if(INFLTNL)
	  /* This function compares the guessed root, pdgm,cat in the dictionary file */
	  match1 = match_in_dict(guessed_root,pdgm,cat,offset,ans_table,ans_ar,loop2);
	if(!INFLTNL)
	  {
	    if(offset <= 902) 
	     {
	       strcpy(cat,"verb");
	     }
	    else
	      if(offset > 902) 
		{
		  strcpy(cat,"noun");
		} 
		/* This function compares the guessed root, pdgm,cat in the dictionary file */
sprintf(logmsg, "PARAMESHINFO: Derivational Morph |guessed_root=%s|pdgm=%s|cat=%s|ans_root=%s|aux_verb=%s\n",guessed_root, pdgm, cat, ans_root, aux_verb); PRINT_LOG(log_file, logmsg);
	     match_in_hypothetical_dict(guessed_root,pdgm,cat,DBM_FLAG,db_lex,ans_root,aux_verb);
//sprintf(logmsg, "PARAMESHINFO1: Derivational Morph |guessed_root=%s|pdgm=%s|cat=%s|ans_table=%s|ans_ar=%s\n",guessed_root, pdgm, cat, ans_table, ans_ar); PRINT_LOG(log_file, logmsg);

sprintf(logmsg, "PARAMESHINFO: Derivational Morph |guessed_root=%s|pdgm=%s|cat=%s|ans_root=%s|aux_verb=%s\n",guessed_root, pdgm, cat, ans_root, aux_verb); PRINT_LOG(log_file, logmsg);

	     if(strcmp(ans_root,""))
		{
		 //strcpy(ans_ar[*loop2].root , "0_"); /* Always derived answer has least priority */
		  strcat(ans_ar[*loop2].root , ans_root);
	          ans_ar[*loop2].offset = offset;
		  strcat(ans_ar[*loop2].aux_verb,aux_verb); 
		  strcpy(ans_ar[*loop2].pdgm,pdgm); 

sprintf(logmsg, "INFO: Derivational Morph |root=%s|offset=%d|aux_verb=%s|pdgm=%s|\n", ans_ar[*loop2].root, ans_ar[*loop2].offset,ans_ar[*loop2].aux_verb, ans_ar[*loop2].pdgm); PRINT_LOG(log_file, logmsg);

		  if(!INFLTNL) 
		    strcat(ans_ar[*loop2].pdgm,"_deri"); 
		  (*loop2)++;
		  if(DEBUG_NEW)
		    {
		      if(*loop2 == DEBUG_NEW)
			{
			   //printf("Exiting from Verify root\n"); 
			   sprintf(logmsg,"Exiting from Verify root\n"); PRINT_LOG(log_file,logmsg);
			   /* fflush(); */
			   exit(9); /*TEMP  AMBA */
			}
		    }
		}
	  }
     }	
