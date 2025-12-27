#include <stdio.h>

//This Program takes input word and returns substrings for morph to perform add and delete rules
extern FILE *log_file;
extern char *program_name;
extern char *logmsg;
#include "./common/analyser/morph_logger.h"

//#define LINE_LENGTH 40
//#define MATCH_LENGTH 25 

/* main()
{
	char word[LINE_LENGTH],str1[25];
	printf("Enter The string\n");
	gets(word);
	
	substr(word,2,5,str1);
	printf("%s\n",str1);
}*/


#define FUNCTION "substr()"
   substr(char word1[20],int start, int last,char str[25])	

    {		
	int i,p;
	i=strlen(word1);
	if(last>i) {
		sprintf(logmsg,"substr.c failure\n");PRINT_LOG(log_file,logmsg);
		//printf("sorry\n");
	 }
	else {
	   for(p=0;p<=last-1;p++)
		{
		  str[p]=word1[start];
		  start++;
		}
}
	str[p]='\0';	
}
