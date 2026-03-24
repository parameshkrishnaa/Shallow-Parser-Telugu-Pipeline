/**
  * File Name : new_build_struct.c
  */

/** Function: build_struct
  * This function creates a specfic structure for the rootword,priority pdgm and
  * category. it copies the required data from the dictionary
  * It takes arguments: word of char array, ch_ar1 and ch_ar2 of 2 dimensional char arrays
  * Return : void
  */

/* Header Files */


#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include "headers/struct.h"
#include "./common/analyser/morph_logger.h"


extern FILE *log_file;
extern char *logmsg;
#define FUNCTION "build_struct()"

void build_struct(word,ch_ar1,ch_ar2)
/* morph word */
char word[SUFFWORDSIZE];            
char ch_ar1[SmallArray][LargeArray];
char ch_ar2[SmallArray][LargeArray];
{
	char *program_name="new_build_struct.c";
        //PRINT_LOG(log_file,"This function creates a specfic structure for the rootword,priority pdgm and category. it copies the required data from the dictionary");
	/* lexical structure contains info of word,category,paradigm priority.
	 * declared object pointer and dummy object 
	 */
	struct lex_info *tag,dummy;  

	/* dummy tag pointer */
        char * tag_dummy;            

	/* tmp word */
        char  tmp[Lexsize];          
        //char  tmp[SmallArray];          

	/* to read the characters of the word */
        int loop1,loop2,loop3,loop4;  
        loop1=0;
        tag= (struct lex_info *)malloc(sizeof(struct lex_info));
	/* executes until guessed suffnotequal to null */
        while(ch_ar1[loop1][0] !='\0')   {
              strcpy(tag->word,word);
              loop3=0;
	      //tag->priority=ch_ar1[i][k]; /* Currently priorities range between 0 to 9 */
              loop3++;  /* To absorb priority */
              loop3++;  /* To absorb " */
              loop3++;  /* To absorb , */
              loop3++;  /* To absorb " */
             /* executes when suff != " and not equal to null */
              while((ch_ar1[loop1][loop3] != '"') && (ch_ar1[loop1][loop3] != '\0'))
                {
                  tmp[loop3-4] = ch_ar1[loop1][loop3];
                  loop3++;
                }
             if(loop3>1)
                tmp[loop3-4] = '\0';
             else
                tmp[0] = '\0';
             strcpy(tag->pdgm,tmp);
             loop3++;  /*To absorb " */
             loop3++; /* To absorb ,*/
             loop3++;  /*To absorb " */ //added for root word category
	     loop4 = loop3;
             loop3=0;
		//printf("ch_ar1[loop1][loop4]=%s\n",ch_ar1);
             /* executes when suff != " and not equal to null */
             while(ch_ar1[loop1][loop4] != '"' && ch_ar1[loop1][loop4] != '\0'){
		//printf("tmp[loop1][loop4]=|%d|%d|%c|\n",loop1,loop4,ch_ar1[loop1][loop4]);
                 //tmp[loop3++] = ch_ar1[loop1][loop4++];
                 tmp[loop3++] = ch_ar1[loop1][loop4++];
		
                 //tmp[loop3++] = ch_ar1[loop1][loop4];
		}
		//printf("word=%d\n",loop3);
             //if(loop3>1)
             if(loop3>=1)//changed to get root word category
                tmp[loop3] = '\0';
             else
                tmp[0] = '\0';
             strcpy(tag->cat,tmp);
		sprintf(logmsg,"tmp=|%s|",tag->cat);PRINT_LOG(log_file,logmsg);
             /* sscanf(ch_ar1[i],"%s,%s",tag->pdgm,tag->cat); */
             tag_dummy = (char *)tag;
             for(loop2=0;loop2<sizeof(dummy);loop2++)
                ch_ar2[loop1][loop2] = tag_dummy[loop2];
              loop1++;
        }
        strcpy(ch_ar2[loop1],"");
}
