/**
  * File Name : chk_cons_ending_for_words.c
  */

/** Function: chk_cons_ending_for_words
  * This function checks whether the given word contains consonants at the end of the word
  * It takes arguments:root of char type,pdgm of char type ,DBM_FLAG of int type ,
  * db_lex of GDBM file type ,ans_root of char type and ,aux_verb of char type
  * Return : void
  */

 /* HEADER FILES */

#include <gdbm.h>

#include <string.h>
#include <stdio.h>
#include "./headers/defn.h"
#include "./headers/struct.h"
#include "./headers/struct1.h"
#include "./common/analyser/morph_logger.h"

extern FILE *log_file;
extern char *logmsg;
#define FUNCTION "chk_cons_ending_for_words()"


/* indicates word existance */
extern int DEBUG;     

/* size of word */
extern int sizeof_lex;  

/* contains lexical info for input word, ie contains word,
 * pdgm,cat,prority and lex_ar is object array declared 
 */
extern struct lex_info lex_ar[];  

void chk_cons_ending_for_wrds(root,pdgm,DBM_FLAG,db_lex,ans_root,aux_verb)

/* root of word, paradigm */
char root[SUFFWORDSIZE],pdgm[WORD_SIZE];    

/* global dictionary flag,if 1 then dictionary is there */    
/* GNU database manager includes dbm and ndb 
 * compatability and db is used for opening file 
 * */
int DBM_FLAG;                      
GDBM_FILE db_lex;                  

/* ans_root is after finding the consonant in the word */    
char ans_root[SUFFWORDSIZE];        

/* auxilary verb */
char aux_verb[SUFFWORDSIZE];        
{
	char *program_name="chk_cons_ending_for_words.c";
	//PRINT_LOG(log_file, " This function checks whether the given word contains consonants at the end of te word ");
	
	/* length of the word, derived root, position of each char 
	 * in the word ,and loop2 is reading characters from the word 
	 * */
	int len,derived_root,pos1,loop2;  

	/* temporary root */
	char tmp_root[SUFFWORDSIZE];   

	/* structure contains lexical info of the word ( root,offset ,
	 * paradigm and priority)declared an object array  ans_table 
	 * */
	struct lex_info ans_table[SmallArray];   

	/* lexical word */
	char ans_ar[SmallArray][LargeArray];   

	strcpy(tmp_root,root);
	len = strlen(root);
	
	/* executes when last char of root is "u" and paradigm != meku */
	if((root[len-1] == 'u') && !strcmp(pdgm,"meku")) { 
		root[len-1] = '\0'; 
		/* This function checks the word in the dictionary */ 
		dict_lookup(root,DBM_FLAG,db_lex,lex_ar->word,sizeof_lex,sizeof(lex_ar[0]),strcmp,ans_ar); 
		pos1 = 0; 
		/* This function copies data ie Priority , pdgm,
		 * cat,word to the structure 
		 * */ 
		cp_to_struct(ans_ar,ans_table,&pos1); 
		loop2=0; 
		/* executes until lexical word is not null */ 
		while(ans_table[loop2].word[0] !='\0') { 
			/* executes when ans_table.word and root are not same && paradigm is not rikRA */ 
			if(!strcmp(ans_table[loop2].word,root) && !strcmp(ans_table[loop2].pdgm,"rikRA")) { 
				strcpy(ans_root,root); 
				goto LAST; 
			} 
			loop2++; 
		}  
		LAST: 
		if(ans_root[0] != '\0') {
			if(aux_verb[0] != '\0') { 
				strcat(ans_root,"_"); 
				strcat(ans_root,aux_verb); 
				strcpy(aux_verb,""); 
			} 
			strcat(ans_root,"_u"); 
		} else {
			/* executes when ans_root andderived root are existing */
			if(DEBUG && derived_root) { 
				//printf("%s\n",ans_root); 
				//printf("%d\n",derived_root); 
				sprintf(logmsg,"%s\n",ans_root);
				PRINT_LOG(log_file,logmsg);
				sprintf(logmsg,"%d\n",derived_root); 
				PRINT_LOG(log_file,logmsg);
			} 
		root[len-1] = 'u'; 
		/* restore back the character */
	    	}
	 }
}
