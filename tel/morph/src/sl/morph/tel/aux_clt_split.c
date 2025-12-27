
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

#define FUNCTION "tam_split()"

#define RULE 10
#define LEN 100
#define BIGGER_LEN 300

int clt_spt(char orig[LEN],char words[RULE][LEN],int word_count )
{
	char *str_M_rep_z,*check;
	
	str_M_rep_z=(char *)malloc((strlen(orig)+1)*sizeof(char));
	strcpy(str_M_rep_z,orig);


	if(strlen(orig)>=12) {
		check=&str_M_rep_z[strlen(orig)-12];
		if(strstr(check,"nAraMBiMcu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
	}

else if(strlen(orig)>=10) {
		check=&str_M_rep_z[strlen(orig)-10];
		if(strstr(check,"pAreVyyi_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
	}

	else if(strlen(orig)>=8) {
		check=&str_M_rep_z[strlen(orig)-8];
		if(strstr(check,"valayu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"beVttu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"galugu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"goVttu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"joVccu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"komanu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"paracu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"peVttu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"veVyyi_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"xalacu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';


	}

	else if(strlen(orig)>=7) {
		check=&str_M_rep_z[strlen(orig)-7];
		if(strstr(check,"xiyyi_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
	}
	else if(strlen(orig)>=6) {
		check=&str_M_rep_z[strlen(orig)-6];
		if(strstr(check,"badu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"cUdu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"gala_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"gUdu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"ivvu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"jAlu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"koVn_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"manu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"mAnu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"neru_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"sAgu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"uMdu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"vaccu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"wIru_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"xagu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';
		else if(strstr(check,"wappu_A")!=NULL)
			str_M_rep_z[strlen(orig)-0]='\0';

	}



	if(strcmp(orig,str_M_rep_z)!=0)
		strcpy(words[word_count++],"yes");
	free(str_M_rep_z);
	return word_count; /*returns the word size after replacing*/
}

extern void fun_morph();
char aux_clt_split(orig,words,word_count,lcat)
char orig[LEN];
char words[RULE][LEN];
int word_count;
{
	int loop1,loop2,test_eof;
	char sort[RULE],morph_path[LEN],cmd[BIGGER_LEN],cmd1[BIGGER_LEN];
	FILE *file,*file_orig;
        //PRINT_LOG(log_file, "This is get_spell_variation()\n");
	
	 word_count=0;
	
	word_count=clt_spt(orig,words,word_count);
//	strcpy(words,orig);


	//printf("iam here with %s\n",orig);
	
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
