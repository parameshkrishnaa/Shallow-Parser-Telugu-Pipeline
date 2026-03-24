/**
 * FILE NAME: read_file.c
*/

/** Function:fun_read   and fun_close
 *  These functions are used for
 *  1: Reads the input word
 *  2: Checks the end of the input conditions
 *  3: if null the file exits
 *   fun_read() takes arguments
 *   fun_close takes arguments:fpt,fp_suff db1,db2 are FILE pointers and swit
 *   and DBM_FLAG are of int type
 *   Return : int for fun_Read() and void for fun_close
 */
 /* HEADER files */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <gdbm.h>

#include "./headers/defn.h"
#include "./common/analyser/morph_logger.h"


extern FILE *log_file;
extern FILE *logmsg;
#define FUNCTION "fun_read()"


extern int YES_NO;	/* for answer is exists or not */

/**********THIS FUNCTION CHECKS END OF INPUT CONDITIONS *****/

//kittu void fun_close(fpt,fp_suff,swit,DBM_FLAG,db1,db2)
void fun_close(fp_suff,swit,DBM_FLAG,db1,db2)

   GDBM_FILE db1,db2;		/* GNU database manager includes dbm and ndb
                                     compatability and db1 and db2 is used for opening file */
   //kittu FILE *fpt,*fp_suff;		/* file pointers for dict and suff */
   FILE *fp_suff;		/* file pointers for dict and suff */
   int swit,DBM_FLAG;		/* switch and database manager flag for checking dictionary
                                  is there or not */
    {
        //kittu if (swit == 0)
          //kittu      fclose(fpt);
        if (DBM_FLAG == 1)		/* executes when dictionary is not present */
	      {
                gdbm_close(db1);
                gdbm_close(db2);
	      }
        fclose(fp_suff);
        exit(1);
    }



/***********THIS FUNCTION READS INPUT WORD ***************/

int fun_read(morph,word)
  
  char morph[Morphsize];		/* morph word */
   char word[100];
    {
	char *program_name="read_file_tel.c";
        PRINT_LOG(log_file,"These functions are used for reading the input word ");
	int loop1,loop2,loop3;
	int c;	/* reads the next character from  stream  and  returns
                              it  as  an unsigned char cast to an int */
	loop2=0;
	loop3=0;
	//c=getc(stdin);
	c= (int)word[loop3];
	int size=strlen(word);
	/* executes when c is not alpha numeric and  end of file */
	while (!isalnum(c)) /* && (c != EOF))*/
          {
	     loop3++;
		if(loop3)
		{
		break;
		}

	   /* if(c=='?')
	     {
	        printf("%c",c);
	     }
            if(c=='.')
	     {
	       printf("%c",c);
	     }
            if(c == '\n') 
	     {
		printf("%c",c);
	     }*/
            if(YES_NO) 
	      //printf("%c",c);
	      {sprintf(logmsg,"%c",c);PRINT_LOG(log_file,logmsg);}
           // c = getc(stdin);
	   c= (int)word[loop3];
          }
	while((isalnum(c))||(ispunct(c)))		/* executes when c is alpha numeric */
	//while((isalnum(c)))		/* executes when c is alpha numeric */
	{
	   loop3++;
           morph[loop2] = c;
	   loop2++;
          // c = getc(stdin);
	   c= (int)word[loop3];
		if(size==1)	// Nagaraju beacuse punctuations are concadenated with some junk characters
		break;
         } 
	/*while((ispunct(c)))		// executes when c is alpha numeric 
	{
	   loop3++;
           morph[loop2] = c;
	   loop2++;
          // c = getc(stdin);
	   c= (int)word[loop3];
		//printf("|%d|\n",strlen(word));
		if(size==1) {
		printf("Iam size=%d\n",size);
		break;
		}
         } */
	for (loop1 = loop2;loop1< Morphsize;++loop1)
        {
	  loop3++;
         morph[loop1] = '\0';
        }
       return(c);
   }
