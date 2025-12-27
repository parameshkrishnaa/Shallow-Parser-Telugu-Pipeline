/**
 * FILE NAME:print_spell_variation.c
*/

/** Function: prnt_spell_variation
 *  This function is used for printing the words that are identifed by the function
 *  get_spell_variation in horizontal way.
 *  Arguments:morph_spell_variation of char array, ans_ar is object array of structure ans_struct
 *  Return : void 
 */

/* HEADER FILES */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct1.h"
#include "morph_logger.h"

extern FILE *log_file;

#define FUNCTION "prnt_spell_variation()"

/**
 * Prototypes of the functions in this file with a file scope
*/

extern void resufun();
 int YES_NO;	    	/* answer is present or not */	
 int HORI_OUTPUT;       /* horizontal output */
 char morph;            /* input word */
void prnt_spell_variation(morph_spell_variation,ans_ar)
 
char morph_spell_variation[100];     /* speel variant word */
struct ans_struct ans_ar[100];       /* object of structure ans_structr  which contains info
                                        of root,aux_verb,offset, paradigm */             
 {
      int i,pipe_flag;
	 char *program_name="print_spell_variation.c";
        PRINT_LOG(log_file, "This is prnt_spell_variation()\n");
	if(ans_ar[0].offset!=-2)      /* checks for case ie direct or indirect */
          if(YES_NO)                  /* if answer is there */
             printf("%s",morph);      

          else
           { 
             i=0;
		pipe_flag=0;
             while(ans_ar[i].offset !=-2) /* executes when offset is not -2  */
              { 
		if(pipe_flag) printf("|"); pipe_flag=1;
	        if(ans_ar[i].offset == -1)  /* if offset is direct case */
                  if(!HORI_OUTPUT)          /* not equal to horizontal output */
	            printf("Avy\n%s\n",ans_ar[i].root);
                  else
	            printf("%s{Avy}",ans_ar[i].root);
	        else
		  if(ans_ar[i].offset == -3) /* Case of Numeral */
                    if(!HORI_OUTPUT)
		      printf("Avy\n%s\n",ans_ar[i].root);
                    else
		      printf("%s",ans_ar[i].root);
		  else
                    if(HORI_OUTPUT)     /* if horizontal output is there */
                      resufun_hori(ans_ar[i].root,ans_ar[i].pdgm,ans_ar[i].offset,ans_ar[i].aux_verb);
 /*This function prints the output in horizontal way for the given input word*/
                   // else
                      //resufun(ans_ar[i].root,ans_ar[i].pdgm,ans_ar[i].offset,ans_ar[i].aux_verb);
/*This function prints the output  including auxilary verbs in horizontal way for the given input word*/
                    strcpy(ans_ar[i].root,"");
                    ans_ar[i].offset = 0;
                    strcpy(ans_ar[i].aux_verb,"");
                    strcpy(ans_ar[i].pdgm,"");
                    i++;
                //    if(HORI_OUTPUT)
                  //     printf("|");
              } 
           } 
 } 
