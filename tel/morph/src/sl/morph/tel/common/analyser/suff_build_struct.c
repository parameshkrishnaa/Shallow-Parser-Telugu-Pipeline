/**
 * FILE NAME : suff_build_struct.c 
 */

/** Function: suff_build_struct
 *  This function creates a table which contains suffix of the word, No of entries, 
 *  word size and position of the word
 *  It takes arguments: word of char array,ch_ar1 of 2 dimensional array and ch_ar2 is 
 *  object of suff_add_info structure
 *  Return: void
*/


#include "stdio.h"
#include "string.h"
#include "defn.h"
#include "struct.h"
#include "morph_logger.h"

extern FILE *log_file;
extern char  *logmsg;

#define FUNCTION "suff_build_struct()"

void suff_build_struct(word,ch_ar1,ch_ar2)
 char word[SUFFWORDSIZE];                /* morph word */
 char ch_ar1[SmallArray][LargeArray];    /* suf word */
 struct suff_add_info ch_ar2[SmallArray];/* suffix structure which contains suffix word
                                              and added data pointer and number of entries */ 
  {
    char  tmp[SmallArray];		 /* temp word */
    char  tmp1[SmallArray];		 /* temp word */
    int loop1,loop2,loop3,loop4;
    char *program_name="suff_build_struct.c";
    //PRINT_LOG(log_file, "creating table containing suffix of the word, No of entries, word size and position of the word\n");

    loop1=0;
    while(ch_ar1[loop1][0] !='\0')       /* whiel suff is not null */
     {
       if(!strcmp(word,"0"))             /* compares word with null */
         strcpy(ch_ar2[loop1].suff,"");
       else
         strcpy(ch_ar2[loop1].suff,word);
       loop3=0;
       while(ch_ar1[loop1][loop3] != ',' && ch_ar1[loop1][loop3] != '\0') {
		   tmp[loop3] = ch_ar1[loop1][loop3];
		   loop3++;
	   }
         if(loop3>0)
           tmp[loop3] = '\0';
         else
           tmp[0] = '\0';
         strcpy(ch_ar2[loop1].add,tmp);
         loop3++;
         loop4 = loop3;
         loop3=0;
	//sprintf(logmsg,"loop1=%d|loop2=%d|loop3=%d|loop4=%d|\n",loop1,loop2,loop3,loop4);PRINT_LOG(log_file,logmsg);
         while(ch_ar1[loop1][loop4] != ',' && ch_ar1[loop1][loop4] != '\0') {
			 tmp[loop3++] = ch_ar1[loop1][loop4];
			 loop4++;
		 }
           if(loop3>0)
             tmp[loop3] = '\0';
           else
             tmp[0] = '\0';
	//sprintf(logmsg,"tmp[0]=|%s|\n",ch_ar1);PRINT_LOG(log_file,logmsg);
          // ch_ar2[loop1].ptr = atoi(tmp);
	strcpy(tmp1,tmp);
	//sprintf(logmsg,"tmp[0]=|%s|\n",ch_ar1);PRINT_LOG(log_file,logmsg);
		//sprintf(logmsg,"tmp=%s|ch_ar2=%d\n",tmp,ch_ar2[loop1].ptr);PRINT_LOG(log_file,logmsg);
           loop4++;
           loop3=0;//loop2=0;
	//sprintf(logmsg,"loop1=%d|loop2=%d|loop3=%d|loop4=%d|\n",loop1,loop2,loop3,loop4);PRINT_LOG(log_file,logmsg);
         while(ch_ar1[loop1][loop4] != ',' && ch_ar1[loop1][loop4] != '\0') tmp[loop3++] = ch_ar1[loop1][loop4++];
	//sprintf(logmsg,"tmp[0]=|%s|\n",ch_ar1);PRINT_LOG(log_file,logmsg);
             if(loop3>0)
               tmp[loop3] = '\0';
             else
               tmp[0] = '\0';
           ch_ar2[loop1].ptr = atoi(tmp1);
             ch_ar2[loop1].no_of_entries = atoi(tmp);
		sprintf(logmsg,"tmp1=%s|ch_ar2=%d",tmp1,ch_ar2[loop1].ptr);PRINT_LOG(log_file,logmsg);
		sprintf(logmsg,"tmp=%d|ch_ar2=%d",tmp,ch_ar2[loop1].no_of_entries);PRINT_LOG(log_file,logmsg);
           loop4++;
             loop1++;
     }
   strcpy(ch_ar2[loop1].suff,"#");
  }
