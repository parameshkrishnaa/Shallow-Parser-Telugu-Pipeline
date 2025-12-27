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


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <gdbm.h>
 
/* HEADER FILES */
#include "defn.h"

#include "morph_logger.h"

extern FILE *log_file;

extern int YES_NO;  /* for answer is exists or not */  

/**********THIS FUNCTION CHECKS END OF INPUT CONDITIONS *****/
//#define FUNCTION "fun_close()"
void fun_close(fpt,fp_suff,swit,DBM_FLAG,db1,db2)
GDBM_FILE db1,db2;

FILE *fpt,*fp_suff;    /* file pointers for dict and suff */
int swit,DBM_FLAG;     /* switch and database manager flag */
{
      if (swit == 0)
                fclose(fpt);
        if (DBM_FLAG == 1)
	      {
                gdbm_close(db1);
                gdbm_close(db2);
	      }
        fclose(fp_suff);
        exit(1);
}



/***********THIS FUNCTION READS INPUT WORD ***************/
#define FUNCTION "fun_read()"
int fun_read(morph)

//char num_str[Morphsize];    /* number string used for SSF format */

char morph[Morphsize];      /* morph word */
{
int loop1,loop2;
int c;                     /* reads the next character from  stream  and  returns  
                              it  as  an unsigned char cast to an int */
char * line = NULL;
size_t len = 0;
ssize_t read;

char *program_name="read_file.c";
//PRINT_LOG(log_file,"Reading the input word\n");

loop2=0;
//scanf("%s" ,num_str);
c=getc(stdin);
while (!isalnum(c) && (c != EOF))   /* executes when c is not alpha numeric and end of file */
       {if(c=='?'){printf("%c",c);}
	if(c=='.'){printf("%c",c);}
        if(c == '\n') {printf("%c",c);}
	if(YES_NO) 
          printf("%c",c);
        c = getc(stdin);
      } 
while(isalnum(c))                   /* executes when c is alpha numeric */
 {
       morph[loop2] = c; loop2++;
       c = getc(stdin); 
     } 
for (loop1 = loop2;loop1< Morphsize;++loop1) 
       morph[loop1] = '\0';
	ungetc(c,stdin);
return(c);

}
