/**
 * FILE Name :comp_verbs.c
*/


/** comp_verb
 * This function is used to  check any  match is there between heuristic
 * string and guessed string
 * The arguments:
 * ch_ar of char type, struct_ar object of the structure lex_info and
 * integer pointer
 * Return : int
 */


/* HEADER FILES */

#include <gdbm.h>

#include <stdio.h>
#include <string.h>
#include "./headers/defn.h"
#include "./headers/struct.h"
#include "./headers/struct1.h"
#include "./common/analyser/morph_logger.h"


extern FILE *log_file;
extern FILE *logmsg;
#define FUNCTION "comp_verb()"


/* structure contains info of word,paradigm, 
 * category,priority and aux_info_ar is array object 
 * */ 
extern struct suff_info aux_info_ar[];  

/* size of auxilary verb */ 
extern int sizeof_aux;                  

/** * Prototypes of the functions in this file with a file scope */ 
extern void comp_verb_heuristics(); 
extern void get_derived_rt();

/* checks for word existance */
extern int DEBUG;	

int comp_verbs(root,pdgm,DBM_FLAG,db_lex,ans_root,aux_verb) 

/* root of the word,paradigm */
char root[SUFFWORDSIZE],pdgm[WORD_SIZE];     

/* flag for checking required file existance */
int DBM_FLAG;                                

/* GNU database manager includes dbm and ndb compatability and db_lex is used for opening file */
GDBM_FILE db_lex;                           

/* derived root */ 
char ans_root[SUFFWORDSIZE];            

/* auxilary verb */   
char aux_verb[SUFFWORDSIZE];            
{ 
	char *program_name="comp_verb.c";
       // PRINT_LOG(log_file, " This function is used to  check any  match is there between heuristic string and guessed string"); 
       
       /* guessed auxilary verb */ 
       char aux_verbs[SUFFWORDSIZE];	  
       
       /* temp verb */ 
       char tmp_aux_verbs[SUFFWORDSIZE]; 
       char cur_aux_str[SUFFWORDSIZE]; 
       aux_verbs[0] = '\0'; 
       tmp_aux_verbs[0] = '\0'; 
       ans_root[0] = '\0'; 
       /*This function compares with the suffixes and 
	* if there are not equal with the given suffix  
	* then they are copied into the suffixes respectively 
	* */ 
       comp_verb_heuristics(root,pdgm,tmp_aux_verbs); 
       if(strcmp(tmp_aux_verbs,"")) { 
       		/* This function is used to  to find derivational root */
		//	     get_derived_rt(root,aux_info_ar->suffix,sizeof_aux,sizeof(aux_info_ar[0]),strcmp,DBM_FLAG,db_lex,"verb",ans_root,aux_verbs,cur_aux_str);
/*PARAMESH	     	get_derived_rt(root,aux_info_ar->suffix,sizeof_aux,sizeof(aux_info_ar[0]), \
			strcmp,DBM_FLAG,db_lex,"verb",ans_root,aux_verbs,cur_aux_str); */
	     
			get_derived_rt(root,aux_info_ar->suffix,sizeof_aux,sizeof(aux_info_ar[0]),strcmp,DBM_FLAG,db_lex,"verb",ans_root,aux_verbs,cur_aux_str);
	//printf ( "PARAMESHTMP_AUX_VERBS::ans_root=%s|aux_verb=%s|aux_verbs=%s|cur_aux_str=%s|tmp_aux_verbs=%s\n",ans_root, aux_verb, aux_verbs, cur_aux_str,tmp_aux_verbs); 

	     /* executes when the ans_root is equal to "" */ 
	     if(strcmp(ans_root,"")) { 

//	printf ( "PARAMESHCOMVERBS: Entering with  ans_root=%s|aux_verb=%s|aux_verbs=%s|cur_aux_str=%s|tmp_aux_verbs=%s\n",ans_root, aux_verb, aux_verbs, cur_aux_str,tmp_aux_verbs); 
	     		/* executes when current auxilary string and temporary auxilary vers are same */ 
			if(!strcmp(cur_aux_str,tmp_aux_verbs)) { 

			/* executes when the aux_verb is equal to "" */
				if(strcmp(aux_verb,""))  { 
					strcat(aux_verbs,"_"); 
					strcat(aux_verbs,aux_verb); 
					strcpy(aux_verb,aux_verbs); 
				} else  

				/* executes when the aux_verb is not equal to "" */
				strcpy(aux_verb,aux_verbs); 
			} else  { 

				/* executes when the ans_root is not equal to "" */ 
				/*reinitialise  ans_root*/ 
				strcpy(ans_root,"");
				/* If word exists */
				if(DEBUG) {
					   //printf("heuristics string %s does not match with guessed_string %s \n",tmp_aux_verbs,aux_verb);
					   sprintf(logmsg,"heuristics string %s does not match with guessed_string %s \n",tmp_aux_verbs,aux_verb);PRINT_LOG(logmsg,log_file);
				  	 //printf("aux_verb = %s\n aux_verbs = %s\n",aux_verb,aux_verbs);
				  	sprintf(logmsg,"aux_verb = %s\n aux_verbs = %s\n",aux_verb,aux_verbs);
				PRINT_LOG(logmsg,log_file);
				} 
				return 0; 
			}
		} 
		return 1; 
	} 
	return 0;
}
