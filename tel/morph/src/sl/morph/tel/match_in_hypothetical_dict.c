/**
 * File Name : match_in_hypothetical_dict.c
*/

 /** Function: match_dict
  * This function compares the guessed root, pdgm,cat in the derived nouns,verbs adverbs,numeric
  *  in the dictionary file
  * It takes the arguments root of char array ,pdgm of char array ,cat of char array ,
  * DBM_FLAG of int type , db_lex of FILE GDBM ans_rootof char type and aux_verb of char type
  * Return:void
  */

/* HEADER FILES */
#include <gdbm.h>

#include <string.h>
#include <stdio.h>
#include "./headers/defn.h"
#include "./common/analyser/morph_logger.h"


extern FILE *log_file;
extern char *program_name;
extern char *logmsg;
#define FUNCTION "match_in_hypothetical_dict()"



/**
 * Prototypes of the functions in this file with a file scope
 */

extern void derived_noun_heuristics();
extern void derived_noun1_heuristics();
extern void derived_verb_heuristics();
extern int comp_verbs();

extern int DEBUG;		/* checks for word existance */
extern int DEBUG_NEW;
extern int KRIYAMULA;

void match_in_hypothetical_dict(root,pdgm,cat,DBM_FLAG,db_lex,ans_root,aux_verb)
  
  /* root of the word, paradigm ,category */
  char root[SUFFWORDSIZE],pdgm[WORD_SIZE],cat[Arraysize];
  int DBM_FLAG;		/* global dictionary flag,if 1 then dictionary is there */
  GDBM_FILE db_lex;	/* GNU database manager includes dbm and ndb
                                            compatability and db_flex is used for opening file */

  char ans_root[SUFFWORDSIZE]; /* final root answer */
  char aux_verb[SUFFWORDSIZE];	/* auxilary verb */
     {
	char aux_v[SUFFWORDSIZE];	/* auxilary verb */
	/* intialising ans_root and aux_v to null */
	ans_root[0] = '\0';
	aux_v[0] = '\0';

	sprintf(logmsg, "INFO: Entering with  match_in_hypothetical() is |root=%s|cat=%s| ",root,cat); PRINT_LOG(log_file,logmsg);
	  /* executes when cstegory is not equal to verb */
	if(!strcmp(cat,"verb"))
	//if(!strcmp(cat,"v"))
	  {
	    /* This function is used to  check any  match is there between heuristic string 
		and guessed string */
	    if(comp_verbs(root,pdgm,DBM_FLAG,db_lex,ans_root,aux_v))
/*	       if(ans_root != '\0') */
	      {
	sprintf(logmsg, "PARAMESHDICT: Entering with  ans_root=%s|aux_verb=%s",ans_root, aux_verb); PRINT_LOG(log_file,logmsg);
	
		if(strcmp(aux_v,""))	/* executes when aux_v is equal to " " */
		  {
		    if(strcmp(aux_verb,""))  /* executes when aux_v is equal to " " */
		      {
			strcat(aux_v,"_");
			strcat(aux_v,aux_verb);
			strcpy(aux_verb,aux_v);
	sprintf(logmsg, "PARAMESHDICT2: Entering with  ans_root=%s|aux_verb=%s",ans_root, aux_verb); PRINT_LOG(log_file,logmsg);
		      }
		    else 
		      strcpy(aux_verb,aux_v);
		  }
              }
	    else
	      if(KRIYAMULA)	
		 /* This function depending on suffix below mentioned changes verb to noun */
		derived_verb_heuristics(root,pdgm,DBM_FLAG,db_lex,ans_root,aux_verb);
	sprintf(logmsg, "PARAMESHNOUN: Entering with  ans_root=%s|aux_verb=%s",ans_root, aux_verb); PRINT_LOG(log_file,logmsg);
		 /* Always given preference to comp verbs than other combination */
          }
	//if(!strcmp(cat,"noun")||!strcmp(cat,"adj"))		/* executes when cat is not equal to verb */
	if(!strcmp(cat,"noun"))		/* executes when cat is not equal to verb */
	  {
	    aux_verb[0] = '\0';/* This line is added after getting the junk o/p for peVxavi */
		 /* This function checks whether the given word contains consonants at
                 the end of the word */
	    chk_cons_ending_for_wrds(root,pdgm,DBM_FLAG,db_lex,ans_root,aux_verb);
	sprintf(logmsg, "INFO1: in match_in_hypothetical() is |root=%s|pdgm=%s|ans_root=%s|aux_verb=%s|cat=%s| ",root,pdgm,ans_root,aux_verb,cat); PRINT_LOG(log_file,logmsg);
	    if(ans_root[0] == '\0'){
	      /* This function depending on suffix below mentioned changes noun to noun */
		derived_noun_heuristics(root,pdgm,DBM_FLAG,db_lex,ans_root,aux_verb);
		sprintf(logmsg,"ans_root=%s|%d|",ans_root,strlen(ans_root));PRINT_LOG(log_file,logmsg);
		//if(strlen(ans_root)>0)
		//strcpy(cat,"adj");
		}
	sprintf(logmsg, "INFO2: in match_in_hypothetical() is |root=%s|pdgm=%s|ans_root=%s|aux_verb=%s|cat=%s| ",root,pdgm,ans_root,aux_verb,cat); PRINT_LOG(log_file,logmsg);
	    if(ans_root[0] == '\0')
		/* This function depending on suffix below mentioned changes noun to noun */
		derived_noun1_heuristics(root,pdgm,DBM_FLAG,db_lex,ans_root,aux_verb);
	    if(ans_root[0] == '\0')
		/* This function depending on suffix below mentioned changes adjective to noun */
		derived_adj_noun_heuristics(root,pdgm,DBM_FLAG,db_lex,ans_root,aux_verb);
	    if(ans_root[0] == '\0')
		/* This function depending on suffix below mentioned changes noun to adverb  */
		derived_adv_noun_heuristics(root,pdgm,DBM_FLAG,db_lex,ans_root,aux_verb);
	    /* if(ans_root[0] == '\0')
		derived_num_heuristics(root,pdgm,DBM_FLAG,db_lex,ans_root,aux_verb);*/
	    if(DEBUG_NEW == 2) 
		{
		  if(ans_root[0] != '\0')   /* executes when final root not equal to null */
		   { 
		     //printf("derived noun root = %s\n",ans_root);
		     sprintf(logmsg,"derived noun root = %s\n",ans_root);PRINT_LOG(log_file,logmsg);
		     /* exit(8); */
       	           }	
                }
	    else if(DEBUG_NEW) 
		DEBUG_NEW++;
	  }
    }
