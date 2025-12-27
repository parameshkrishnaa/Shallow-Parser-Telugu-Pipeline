/**
 * File Name :print.c
 */

/** Function: resufun
 * This function prints the root, pdgm,priority ,category
 * It takes arguments: root of char array, pdgm of char array ,offset of int type and aux_verb of * char array
 * Return :void
 */

/* HEADER FILES */

#include <string.h>
#include <stdio.h>
#include "./headers/struct.h"
#include "./common/analyser/morph_logger.h"


extern FILE *log_file;
#define FUNCTION "resufun()"

/*The function order gives descrption of category-enumerator-file based on feature-enumerator-file*/
extern struct order_info order[MAX_NO_OF_CAT];

extern char fe_info[][INFOSIZE];	/*feature information */
extern int FOR_USER;			/* for user friendly output */
extern int ALWAYS_DEFAULT_PARADIGM;	/*  always choose the default paradigm ,
                                     even though entry is found in dict */
extern int DEFAULT_PARADIGM;		/* neglect when paradigm is found */

void resufun(root,pdgm,offset,aux_verb)

   char root[WORD_SIZE];			/* root of the word */
   char pdgm[SUFFWORDSIZE];		/* paradigm of the word */
   int offset;				/* offset value */
   char aux_verb[SUFFWORDSIZE];		/* auxilary verb */
    {
	char *program_name="print_telugu.c";
       // PRINT_LOG(log_file," This function prints the root, pdgm,priority ,category");
	/* loop1 to loop5 are for reading characters of category,feature value */
	int loop1,loop2,loop3,loop4,loop5;
	/* length of fe,root not found, number of features */
	int len_fe_info,not_found,no_of_features;
	char category[WORD_SIZE];	/* category of the word */
	/* feature and feature value of word */
	char feature[MAX_NO_OF_CAT][WORD_SIZE],feature_value[MAX_NO_OF_CAT][WORD_SIZE];

	len_fe_info = strlen(fe_info[offset-1]);
	for(loop1 = 0;((fe_info[offset-1][loop1] != ' ')&&(fe_info[offset-1][loop1] !='\"')&&(fe_info[offset-1][loop1] != '\0'));++loop1)
	   category[loop1] = fe_info[offset-1][loop1];
	category[loop1] = '\0';
	if(FOR_USER)		/* to check for user friendly output  for category */ 
	   printf("@category: ");
	printf("%s\n",category);
	if(FOR_USER) 		/* to check for user friendly output  for root */
	  printf("@root:@ ");
	printf("%s\n",root);
	if(FOR_USER)		/* to check for user friendly output  for paradigm */
	  printf("@pdgm:@ ");
	printf("%s\n",pdgm);
	/* if(ALWAYS_DEFAULT_PARADIGM || DEFAULT_PARADIGM)
	 {	if(FOR_USER) printf("INFO: "); printf("my_pdgm\n");} */
	loop2=loop1+1;
	loop3=0;	
	while(loop2<len_fe_info) 	/* executes when loop2 lessthan length of fe info */
	  {
		/* executes until loop1<len_fe_info && fe_info[offset-1][loop1] != ' ' */
	    for(loop1=loop2;(loop1<len_fe_info && fe_info[offset-1][loop1] != ' '); loop1++)
              feature[loop3][loop1-loop2] = fe_info[offset-1][loop1];
            feature[loop3][loop1-loop2] = '\0';
  	    loop2=loop1+1;
		/* executes until loop1<len_fe_info && fe_info[offset-1][loop1] != ' ' */
            for(loop1=loop2;(loop1<len_fe_info && fe_info[offset-1][loop1] != ' '); loop1++)
               feature_value[loop3][loop1-loop2] = fe_info[offset-1][loop1];
            feature_value[loop3][loop1-loop2] = '\0';
            loop2=loop1+1;
            loop3++;
          }
	no_of_features=loop3;
	loop4=0;
	/* executes when order.category and guessed category are same */
	while(strcmp(order[loop4].category,category))
	 loop4++;
	loop5=0;
		/* executes when order.feature not null */
	while(order[loop4].feature[loop5][0] != '\0')
	  {
	    not_found=1;
		/* executes until loop3<no_of_features && not_found */
	    for(loop3=0;(loop3<no_of_features && not_found);loop3++)
		{
		/* executes when feature value is not equal to tam */
	          if(!strcmp(order[loop4].feature[loop5],"tam"))
        	    {
			/* executes when auxilary verb is equal to " " */
		      if(strcmp(aux_verb,""))
			{
		          if(FOR_USER)	/* gets user friendly output when FOR_USER is true */
          		   {
		   		printf("@%s :",feature[loop3]);
		   		printf("%s_",aux_verb);	
   				printf("%s@\n",feature_value[loop3]);
           		   }
	   		 else 
           		   {
		        	printf("%s_",aux_verb);
   				printf("%s\n",feature_value[loop3]);
           		   }
	   		not_found = 0;
			}
              	      else  
	        	{ 
	                   printf("%s\n",feature_value[loop3]);
   		           not_found = 0;
                        }
                    }
	         if(!strcmp(order[loop4].feature[loop5],feature[loop3]) && strcmp(order[loop4].feature[loop5],"tam"))
    		   {
		     if(FOR_USER)	/* gets user friendly output when FOR_USER is true */
			{
		       	  printf("@%s :",feature[loop3]);
 		   	  printf("%s@\n",feature_value[loop3]);
			}
		     else 
			printf("%s\n",feature_value[loop3]);
	             not_found = 0;
  		   }
		}
	      if(not_found) 		/* executes when not_found is true */
		{
		  if(FOR_USER)		/* gets user friendly output when FOR_USER is true */
		   printf("@%s :@",order[loop4].feature[loop5]);
		  printf("\n");
		}
	      loop5++;
	  }
   }
