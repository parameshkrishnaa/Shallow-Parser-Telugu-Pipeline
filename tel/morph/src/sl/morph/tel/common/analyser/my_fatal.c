/**
 * my_fatal.c
*/

/** Function: my_fatal
  * This function displays a message  "File not found"  
  * when the files dict_final,suff are not there
  * It takes arguments fpt of char array
  * derived by  K.SWATHI ,koradaswathi13@gmail.com
  */


#ifdef GNU
#endif
#include <stdio.h>
//extern FILE *log_file;
//extern char *logmsg;

void *my_fatal(char fpt[50])
   {
	if(!fpt)        /* fpt is not true */
          {
 		printf("%s    FILE  FOUND",fpt);
 		//sprintf(logmsg,"%s    FILE  FOUND",fpt);PRINT_LOG(log_file,logmsg);
	   }
    }
