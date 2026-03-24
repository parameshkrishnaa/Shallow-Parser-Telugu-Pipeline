/**
 * FILE NAME:print_hori.c
 */

/**
 * Function: resufun_hori
 * This function prints the output in horizontal way for the given input word
 * It takes arguments: root of char array, pdgm of char array ,offset of int type
 * and aux_verb of char array
 * Return:void
 */

/* HEADER FILES */

#include <string.h>
#include <stdio.h>
#include "headers/struct.h"
#include "./common/analyser/morph_logger.h"


extern FILE *log_file;
extern char *logmsg;
#define FUNCTION "resufun_hori()"


/*The function order gives info of category-enumerator-file based on feature-enumerator-file*/
extern struct order_info order[MAX_NO_OF_CAT];

/* fe info */
extern char fe_info[][INFOSIZE];	

/* user friendly output */
extern int FOR_USER;			

/* considers only guessed paradigm even we get pdgm */
extern int ALWAYS_DEFAULT_PARADIGM;	

/* considers only final paradigm */
extern int DEFAULT_PARADIGM;		

void resufun_hori(root,pdgm,offset,aux_verb,root1, cat1, g1, n1, p1, kase1, cm1, tam1)

   char root[WORD_SIZE];	/* root word */
   char pdgm[SUFFWORDSIZE];	/* paradigm */
   int offset;			/* offset, tells about cases */
   char aux_verb[SUFFWORDSIZE];	/* auxilary verb */
   char root1[];
   char cat1[];
   char g1[];
   char n1[];
   char p1[];
   char kase1[];
   char cm1[];
   char tam1[];
   {
	char *program_name="print_hori.c";
	//sprintf(logmsg,"INFO: IN resufun_hori()|"); PRINT_LOG(log_file, logmsg);
    //    PRINT_LOG(log_file,"This function prints the output in horizontal way for the given input word ");
	/* for refering characters of word , offset,feature_value */
        int loop1,loop2,loop3,loop4,loop5;
        int len_fe_info,not_found,no_of_features; /* length of fe , no. of features word have */
        char category[WORD_SIZE]; /*  category */
        char feature[MAX_NO_OF_CAT][WORD_SIZE],feature_value[MAX_NO_OF_CAT][WORD_SIZE];

	len_fe_info = strlen(fe_info[offset-1]);
	for(loop1 = 0;((fe_info[offset-1][loop1] != ' ')&&(fe_info[offset-1][loop1] !='\"')&&(fe_info[offset-1][loop1] != '\0'));++loop1)
           category[loop1] = fe_info[offset-1][loop1];
	category[loop1] = '\0';
	//printf("category=%s\n",category);
	//sprintf(logmsg, "INFO: Calling resufun_hori(),root=%s|pdgm=%s|offset=%d|aux_verb=%s|root1=%s|cat1=%s|g1=%s|n1=%s|p1=%s|case1=%s|cm1=%s|suff1=%s|",root,pdgm,offset,aux_verb,root1, cat1, g1, n1, p1, kase1, cm1, tam1 ); PRINT_LOG(log_file, logmsg);
	//sprintf(logmsg, "INFO: Calling resufun_hori(),root=%s|cat=%s|g=%s|n=%s|p=%s|case=%s|cm=%s|suff=%s|" ); PRINT_LOG(log_file, logmsg);
	if(FOR_USER)     /* executes when there is user friendly output */
	  //printf("ROOT:");
	 {sprintf(logmsg,"ROOT:");PRINT_LOG(log_file,logmsg);}
	//printf("%s{",root);
	sprintf(root1,"%s",root);
	//if(FOR_USER) 			/* for getting user friendly output */
	//  printf("PDGM:");
	//printf("%s ",pdgm);
	if(FOR_USER)			/* for getting user friendly output */
	  //printf("CAT:");
	 {sprintf(logmsg,"CAT:");PRINT_LOG(log_file,logmsg);}
	//printf("%s ",category);
//	 sprintf(cat1,"%s",category);
	if(!strcmp(category,"P"))
	{
	sprintf(cat1,"pn",category);
	if((!strcmp(root,"nenu"))||(!strcmp(root,"memu"))||(!strcmp(root,"meM")))
	{
	strcpy(p1,"1");
	strcpy(g1,"any");
	}
	else if((!strcmp(root,"nuvvu"))||(!strcmp(root,"nIvu"))||(!strcmp(root,"mIru"))||(!strcmp(root,"wamaru"))||(!strcmp(root,"wAmu")))
	{
	strcpy(p1,"2");
	strcpy(g1,"any");
	}
	else if((!strcmp(root,"vAdu"))||(!strcmp(root,"vIdu"))||(!strcmp(root,"iwanu"))||(!strcmp(root,"awadu"))||(!strcmp(root,"awanu"))||(!strcmp(root,"iwadu"))||(!strcmp(root,"eVvadu")))
	{
	strcpy(p1,"3");
	strcpy(g1,"m");
	}
	else if((!!strcmp(root,"vAru"))||(!strcmp(root,"vIru"))||(!strcmp(root,"vAlYlu"))||(!strcmp(root,"vIlYlu"))||(!strcmp(root,"eVvaru"))||(!strcmp(root,"wanu"))||(!strcmp(root,"winu")))
	{
	strcpy(p1,"3");
	strcpy(g1,"fm");
	}
	else if((!!strcmp(root,"AmeV"))||(!strcmp(root,"ImeV"))||(!strcmp(root,"Avida"))||(!strcmp(root,"Ivida"))||(!strcmp(root,"emeV")))
	{
	strcpy(p1,"3");
	strcpy(g1,"f");
	}
	else if((!!strcmp(root,"axi"))||(!strcmp(root,"ixi"))||(!strcmp(root,"exi")))
	{
	strcpy(p1,"3");
	strcpy(g1,"fn");
	}
	}
	else if(!strcmp(category,"Avy"))
	{
	sprintf(cat1,"avy",category); }
	else { 	 sprintf(cat1,"%s",category); }
	loop2=loop1+1;
	loop3=0;
	//sprintf(logmsg,"loop2=%d|len_fe_info=%d\n",loop2,len_fe_info); PRINT_LOG(log_file, logmsg);
	while(loop2<len_fe_info) 	/* executes when loop2 > length of fe info */
	  {
	    for(loop1=loop2;(loop1<len_fe_info && fe_info[offset-1][loop1] != ' '); loop1++)
              feature[loop3][loop1-loop2] = fe_info[offset-1][loop1];
            feature[loop3][loop1-loop2] = '\0';
  	    loop2=loop1+1;
            for(loop1=loop2;(loop1<len_fe_info && fe_info[offset-1][loop1] != ' '); loop1++)
               feature_value[loop3][loop1-loop2] = fe_info[offset-1][loop1];
            feature_value[loop3][loop1-loop2] = '\0';
            loop2=loop1+1;
  	    loop3++;
	  }
	//sprintf(logmsg, "INFO: Calling resufun_hori(),root=%s|pdgm=%s|offset=%d|aux_verb=%s|root1=%s|cat1=%s|g1=%s|n1=%s|p1=%s|case1=%s|cm1=%s|suff1=%s|loop2=%d|len_fe_info=%d",root,pdgm,offset,aux_verb,root1, cat1, g1, n1, p1, kase1, cm1, tam1,loop2,len_fe_info ); PRINT_LOG(log_file, logmsg);
	no_of_features=loop3;
	loop4=0;
	/* executes when category, element of structure order is equal to category */
	//sprintf(logmsg, "INFO: Calling resufun_hori(),root=%s|pdgm=%s|offset=%d|aux_verb=%s|root1=%s|cat1=%s|g1=%s|n1=%s|p1=%s|case1=%s|cm1=%s|suff1=%s|loop2=%d|len_fe_info=%d",root,pdgm,offset,aux_verb,root1, cat1, g1, n1, p1, kase1, cm1, tam1,loop2,len_fe_info ); PRINT_LOG(log_file, logmsg);
	sprintf(logmsg, "INFO: Calling resufun_hori(),order[loop4].category=%s|category=%s|",order[loop4].category,category); PRINT_LOG(log_file, logmsg);
	while(strcmp(order[loop4].category,category))
	{
	//sprintf(logmsg, "INFO: Calling resufun_hori(),order[loop4].category=%s|category=%s|",order[loop4].category,category); PRINT_LOG(log_file, logmsg);
	   loop4++;
	if(loop4==9) //Added by Nagaraju-18052013
	break;	//to solve segmentation issue for numeric words
	}
	loop5=0;
	sprintf(logmsg, "INFO: Calling resufun_hori(),order[loop4].category=%s|category=%s|",order[loop4].category,category); PRINT_LOG(log_file, logmsg);
	/* executes when order[loop4].feature[loop5][0] not equal to null */
	while(order[loop4].feature[loop5][0] != '\0')
	  {
	    not_found=1;
	    for(loop3=0;(loop3<no_of_features && not_found);loop3++)
	      {
		/* executes when order.feature not equal to tam or order.feature not equal to
                     parsarg and order.feature not equal to feature */ 
		if((!strcmp(order[loop4].feature[loop5],"tam")  || !strcmp(order[loop4].feature[loop5],"parsarg")) && !strcmp(order[loop4].feature[loop5],feature[loop3]))
	          {
		    if(strcmp(aux_verb,""))	/* executes when aux_verb equal to " " */
	  	      {	
	  		if(FOR_USER) 	/* for getting user friendly output */
		          //printf("TAM:");
	 sprintf(logmsg,"TAM:");PRINT_LOG(log_file,logmsg);
			 sprintf(tam1, "%s_%s", aux_verb, feature_value[loop3]);
   		        not_found = 0;
	              }
              	    else  
	              { 
		        if(FOR_USER) 	/* for getting user friendly output */
			 // printf("TAM:");
	 {sprintf(logmsg,"TAM:");PRINT_LOG(log_file,logmsg);}
				if(!strcmp(feature_value[loop3],"o")) 
				{
			  sprintf(kase1,"%s","o" );
				}
else if(!strcmp(feature_value[loop3],"d"))
				{
			  sprintf(kase1,"%s","d" );
				}
				else {
				//printf("kase1=|%s|\n",kase1);
			  //sprintf(tam1,"%s",feature_value[loop3]);	//Nagaraju 06-06-13 for clitic-suff
			  strcat(feature_value[loop3],tam1);
			  strcpy(tam1,feature_value[loop3]);
			  //strcat(tam1,feature_value[loop3]);	//Nagaraju 06-06-13 for clitic-suff
				//printf("kase1=|%s|\n",kase1);
				}
  		          not_found = 0;
			}
                  }
		/* Tam & parsarg are already taken care of. Also 'case & gender' in the case of
			 nouns is of no use */
   		if (!strcmp(order[loop4].feature[loop5],feature[loop3]) \
			&& strcmp(order[loop4].feature[loop5],"tam") \
			&& strcmp(order[loop4].feature[loop5],"parsarg") \
			&& strcmp(order[loop4].feature[loop5],"case"))
    		  {
	           if(FOR_USER)		/* for getting user friendly output */
		     //printf("%s:",feature[loop3]);
	 {sprintf(logmsg,"%s:",feature[loop3]);PRINT_LOG(log_file,logmsg);}
			if(!strcmp(feature_value[loop3],"1_e"))
			{
		     	sprintf(g1, "", feature_value[loop3]);
			sprintf(n1, "sg", feature_value[loop3]);
		     	sprintf(p1, "1", feature_value[loop3]);
			}
			else if(!strcmp(feature_value[loop3],"1_ba"))
			{
		     	sprintf(g1, "", feature_value[loop3]);
			sprintf(n1, "pl", feature_value[loop3]);
		     	sprintf(p1, "1", feature_value[loop3]);
			}
			else if(!strcmp(feature_value[loop3],"12_ba"))
			{
		     	sprintf(g1, "", feature_value[loop3]);
			sprintf(n1, "pl", feature_value[loop3]);
		     	sprintf(p1, "2", feature_value[loop3]);
			}
			else if(!strcmp(feature_value[loop3],"23_ba"))
			{
		     	sprintf(g1, "fm", feature_value[loop3]);
			sprintf(n1, "pl", feature_value[loop3]);
		     	sprintf(p1, "3", feature_value[loop3]);
			}
			else if(!strcmp(feature_value[loop3],"2_ba"))
			{
		     	sprintf(g1, "", feature_value[loop3]);
			sprintf(n1, "pl", feature_value[loop3]);
		     	sprintf(p1, "2", feature_value[loop3]);
			}
			else if(!strcmp(feature_value[loop3],"2_ba_3_non_na_ba"))
			{
		     	sprintf(g1, "fm", feature_value[loop3]);
			sprintf(n1, "pl", feature_value[loop3]);
		     	sprintf(p1, "3", feature_value[loop3]);
			}
			else if(!strcmp(feature_value[loop3],"2_e"))
			{
		     	sprintf(g1, "", feature_value[loop3]);
			sprintf(n1, "sg", feature_value[loop3]);
		     	sprintf(p1, "2", feature_value[loop3]);
			}
			else if(!strcmp(feature_value[loop3],"2_e_3_na_ba"))
			{
		     	sprintf(g1, "n", feature_value[loop3]);
			sprintf(n1, "pl", feature_value[loop3]);
		     	sprintf(p1, "3", feature_value[loop3]);
			}
			else if(!strcmp(feature_value[loop3],"3_e_3_na_ba"))
			{
		     	sprintf(g1, "n", feature_value[loop3]);
			sprintf(n1, "pl", feature_value[loop3]);
		     	sprintf(p1, "3", feature_value[loop3]);
			}
			else if(!strcmp(feature_value[loop3],"3_na_ba"))
			{
		     	sprintf(g1, "n", feature_value[loop3]);
			sprintf(n1, "pl", feature_value[loop3]);
		     	sprintf(p1, "3", feature_value[loop3]);
			}
			else if(!strcmp(feature_value[loop3],"3_non_na_ba"))
			{
		     	sprintf(g1, "n", feature_value[loop3]);
			sprintf(n1, "pl", feature_value[loop3]);
		     	sprintf(p1, "3", feature_value[loop3]);
			}
			else if(!strcmp(feature_value[loop3],"3_non_pu_e"))
			{
		     	sprintf(g1, "fn", feature_value[loop3]);
			sprintf(n1, "sg", feature_value[loop3]);
		     	sprintf(p1, "3", feature_value[loop3]);
			}
			else if(!strcmp(feature_value[loop3],"3_pu_e"))
			{
		     	sprintf(g1, "m", feature_value[loop3]);
			sprintf(n1, "sg", feature_value[loop3]);
		     	sprintf(p1, "3", feature_value[loop3]);
			}
			else if(!strcmp(feature_value[loop3],"3_non_na_ba"))
			{
		     	sprintf(g1, "n", feature_value[loop3]);
			sprintf(n1, "pl", feature_value[loop3]);
		     	sprintf(p1, "3", feature_value[loop3]);
			}
			else if(!strcmp(feature_value[loop3],"eka"))
			{
		     	sprintf(g1, "", feature_value[loop3]);
			sprintf(n1, "sg", feature_value[loop3]);
		     	sprintf(p1, "", feature_value[loop3]);
			}
			else if(!strcmp(feature_value[loop3],"bahu"))
			{
		     	sprintf(g1, "", feature_value[loop3]);
			sprintf(n1, "pl", feature_value[loop3]);
		     	sprintf(p1, "", feature_value[loop3]);
			}
			else if(!strcmp(feature_value[loop3],"any"))
			{
		     	sprintf(g1, "any", feature_value[loop3]);
			sprintf(n1, "any", feature_value[loop3]);
		     	sprintf(p1, "any", feature_value[loop3]);
			}
		else{
		     sprintf(g1, "%s", feature_value[loop3]);
		     sprintf(n1, "%s", feature_value[loop3]);
		     sprintf(p1, "%s", feature_value[loop3]); 
		    }
   	           not_found = 0;
		//printf("");//Nagaraju28-06-13
                  }
	      }
	   loop5++;
	  }
	//to avoid deri_cat for avy
	if(offset > 1845 && offset < 1898)
        strcpy(cat1,"\0");

        if(offset > 1918) {
        strcpy(category,"\0");
        strcpy(cat1,"\0");
        }

	//printf("}");
   }
