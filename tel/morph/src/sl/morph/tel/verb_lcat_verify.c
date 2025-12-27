
/**
 * FILE NAME : get_spell_variation.c 
 */

/** Function:  get_spellvariation
 *  This function is used for identifying the second letter of Hindi alphabets.
 *  Removes or replaces with the small letter in the input word.
 *  Arguments:orig of char array,words of 2 dimensional array ,
 *  word_count of int type and return type is char type
 * Return : char , return morph word after spel variation is done
 */ 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "morph_logger.h"

extern char *program_name;
extern FILE *log_file;
extern char *log_messg;

#define FUNCTION "lcat_verify()"

#define RULE 10
#define LEN 100
#define BIGGER_LEN 300

int verb_lcat_verify(char orig[LEN],char words[RULE][LEN],int word_count )
{
	char *str_M_rep_z,*check,*check1,temp;
	
	str_M_rep_z=(char *)malloc((strlen(orig)+1)*sizeof(char));
	strcpy(str_M_rep_z,orig);

	if(strlen(orig)>=4)
		{
	//	check1=&str_M_rep_z[strlen(orig)-4];
		check=&str_M_rep_z[strlen(orig)-7];
	//	printf("check----%s\n",check);
	//	check=strrev(check1);
	//	printf("check----%s\n",check);
		if(strstr(check,"_ani")!=NULL)
			 strcpy(str_M_rep_z,"v"); 
		else if(strstr(check,"_ina")!=NULL)
			 strcpy(str_M_rep_z,"v"); 
		}
	
		
	if(strcmp(orig,str_M_rep_z)!=0)
		strcpy(words[word_count++],str_M_rep_z);
	free(str_M_rep_z);
	return word_count; /*returns the word size after replacing*/
}
		
extern void fun_morph();
char verb_lcat_split(orig,words,word_count)
char orig[LEN];
char words[RULE][LEN];
int word_count;
{
	int loop1,loop2,test_eof;
	char sort[RULE],morph_path[LEN],cmd[BIGGER_LEN],cmd1[BIGGER_LEN];
	FILE *file,*file_orig;
        //PRINT_LOG(log_file, "This is get_spell_variation()\n");
	
	 word_count=0;
	word_count=verb_lcat_verify(orig,words,word_count);
	
	/* for sorting uniquely the words and writing it to the file */
	for(loop1=0;loop1<word_count;loop1++)
		sort[loop1]='U';
	
	for(loop1=0;loop1<word_count-1;loop1++)
		{
		if(sort[loop1]!='U')
			continue;
		for(loop2=loop1+1;loop2<word_count;loop2++)
			{
			if(!strcmp(words[loop1],words[loop2]))
				sort[loop2]='D';
			}
	return (words);  /*returns the word after Spell variaton is performed*/
		}
		

}
