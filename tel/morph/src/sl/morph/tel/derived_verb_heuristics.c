/**
 * FILE Name :derived_verb_heuristics.c
*/

/** derived_verb_heuristics
 * This function depending on suffix below mentioned changes verb to noun
 * The arguments:
 * root of char type ,pdgm of char type, DBM_FLAG of int type ,db of GDBM_db file type
 * answer of char type
 * integer pointer
 * Return : void
 */

 /* HEADER FILES */

#include <gdbm.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./headers/defn.h"
#include "./headers/struct.h"
#include "./headers/struct1.h"
#include "./common/analyser/morph_logger.h"


extern FILE *log_file;
extern char *logmsg;
#define FUNCTION "derived_verb_heuristics()"

/**
 * Prototypes of the functions in this file with a file scope
 */
int size_of_file=0,j,i;
char words[1000][200];
char wrd[15][50];

extern void dict_lookup();
extern int DEBUG;		/* is used for checking existance of root */
void my_grep();

/* suff_info structure contains info of suffix, add, pdgm, category, offset */

extern struct lex_info lex_ar[];

extern int sizeof_lex;

void  derived_verb_heuristics(root,pdgm,DBM_FLAG,db,answer)

char root[SUFFWORDSIZE],pdgm[WORD_SIZE];	/* root of the word, paradigm */
int DBM_FLAG;					/* global dictionary flag ,if 1 then
                                               dictionary is there */
GDBM_FILE db;					/* GNU database manager includes dbm and ndb
                                   compatability and db is used for opening file */
char answer[SUFFWORDSIZE];		/* root after the derivation */
    {
	char *program_name="derived_verb_heuristics.c";
        PRINT_LOG(log_file,"this function depending on suffix below mentioned changes verb to noun")
	int len,derived_root;	  /* length of the root, derived root */
         /* different suffixes */
	char suffix_2[3],suffix_3[4],suffix_4[5],suffix_5[6],suffix_6[7];
	char ans_root[SUFFWORDSIZE];	/* final root answer */

	len = strlen(root);   		/* finding length of the root */
	
	if(len>6) strcpy(suffix_6 , root+len-6); else strcpy(suffix_6,"");
	if(len>5) strcpy(suffix_5 , root+len-5); else strcpy(suffix_5,"");
	if(len>4) strcpy(suffix_4 , root+len-4); else strcpy(suffix_4,"");
	if(len>3) strcpy(suffix_3 , root+len-3); else strcpy(suffix_3,"");
	if(len>2) strcpy(suffix_2 , root+len-2); else strcpy(suffix_2,"");

	//sprintf(logmsg,"NAGARAJ INFO:Entering derived_verb_heuristics");PRINT_LOG(log_file,logmsg);

	derived_root = 0;	/* intialising derived_root to 0 */
	ans_root[0] = '\0';	/* intialising ans_root to null */
	answer[0] = '\0';	/* intialising answer to null */

		  FILE *fp;
			char buff[1000];
	char verb_file[BigArray];
	strcpy(verb_file,getenv("setu"));
	strcat(verb_file, "/morph/data_bin/sl/morph/tel/derivation/derived_verb.p");
			//int size_of_file=0,j,i;
			//char words[1000][200];
			//char wrd[15][50];
	//	fp=fopen("derivation/derived_verb.p","r");
		//fp=fopen("/home/guest/oldmorph/data_bin/sl/morph/tel/derivation/derived_verb.p","r");
		//fp=fopen("/home/guest/oldmorph/data_src/sl/morph/tel/pc_data/derivation/derived_verb.p","r");
		//fp=fopen("/var/www/html/morph/telmorph/data_src/sl/morph/tel/pc_data/derivation/derived_verb.p","r");
		//fp=fopen("../data_src/sl/morph/tel/pc_data/derivation/derived_verb.p","r");
		fp=fopen(verb_file,"r");
		//sprintf(logmsg, "Setu=%s", getenv ("setu"));
		if(fp!=NULL){
		//printf("Iam here with Ena_vAdu");
			while(fgets(buff,1000,fp)!=NULL){ 
			buff[strlen (buff) - 1] = '\0';
	                strcpy (words[size_of_file], buff);
			//printf("%s\n",words[size_of_file]);
        	        size_of_file++;
			//printf("%s",buff);
				}
			//printf("%d",size_of_file);
			}
			 else {
                        //sprintf(logmsg,"The file derived_verb.p cannot be opened\n");
			PRINT_LOG(log_file,logmsg);
                        exit(0);
			}
			fclose(fp);
		//Nagaraju
		for(j=0;j<size_of_file;j++) { 
		for(i=0;i<3;i++){
		strcpy(wrd[i],"\0");}
		split_arr(words[j],' ',wrd);
		//printf("%s|%s|%s\n",wrd[0],wrd[1],wrd[2]);
	
	/* comparing iMcu with suffix_4 and paradigm with cUpiMcu
		 executes only when all the conditions are satisfied  */
	//if(!strcmp(suffix_4,"iMcu") && !strcmp(pdgm,"cUpiMcu")) 
	if(!strcmp(suffix_4,wrd[0]) && !strcmp(pdgm,wrd[1])) 
	  {
	    derived_root = 1;
	    strncpy(ans_root,root,len-4);
	    ans_root[len-4] = '\0';
	    if(ans_root[0] != '\0') 	/* executes when ans_root not equal to null */
	      {
		//printf("ans_root=%s|DBM_FLAG=%d|db=%d|answer=%s|\n",ans_root,DBM_FLAG,db,answer);
		my_grep(ans_root,DBM_FLAG,db,answer);
		//printf("ans_root=%s|DBM_FLAG=%d|db=%d|answer=%s|\n",ans_root,DBM_FLAG,db,answer);
		if(answer[0] != '\0')	 /* executes when answer not equal to null */
		   //strcat(answer,"?_iMcu");
		   strcat(answer,wrd[2]);
	//sprintf(logmsg,"NAGARAJ INFO:suffix_4=%s|pdgm=%s|answer=%s",suffix_4,pdgm,answer);PRINT_LOG(log_file,logmsg);
	      }
	  }
	/* comparing padu with suffix_4 and paradigm with padu
		 executes only when all the conditions are satisfied  */
	//if(!strcmp(suffix_4,"padu") && !strcmp(pdgm,"padu")) 
	if(!strcmp(suffix_4,wrd[0]) && !strcmp(pdgm,wrd[1])) 
	  {
	     derived_root = 1;
	     strncpy(ans_root,root,len-4);
	     ans_root[len-4] = '\0';
	     if(ans_root[0] != '\0') /* executes when ans_root not equal to null */
		{
		  my_grep(ans_root,DBM_FLAG,db,answer);
		  if(answer[0] != '\0') 
		    //strcat(answer,"?_padu");
		    strcat(answer,wrd[2]);
	//sprintf(logmsg,"NAGARAJ INFO:suffix_4=%s|pdgm=%s|answer=%s",suffix_4,pdgm,answer);PRINT_LOG(log_file,logmsg);
	        }
	  }
	//if(!strcmp(suffix_4,"avvu") && !strcmp(pdgm,"avvu")) 
	if(!strcmp(suffix_4,wrd[0]) && !strcmp(pdgm,wrd[1])) 
	  {
	    derived_root = 1;
	    strncpy(ans_root,root,len-4);
	    ans_root[len-4] = '\0';
	    if(ans_root[0] != '\0') 
	      {
		//printf("ans_root=%s|DBM_FLAG=%d|db=%d|answer=%s|\n",ans_root,DBM_FLAG,db,answer);
		my_grep(ans_root,DBM_FLAG,db,answer);
		if(answer[0] != '\0') 
		  //strcat(answer,"?_avvu");
		   strcat(answer,wrd[2]);
	//sprintf(logmsg,"NAGARAJ INFO:suffix_4=%s|pdgm=%s|answer=%s",suffix_4,pdgm,answer);PRINT_LOG(log_file,logmsg);
	      }
	  }
	//if(!strcmp(suffix_6,"ceVyyi") && !strcmp(pdgm,"ceVyyi")) 
	if(!strcmp(suffix_6,wrd[0]) && !strcmp(pdgm,wrd[1])) 
	  {
	    derived_root = 1;
	    strncpy(ans_root,root,len-6);
	    ans_root[len-6] = '\0';
	    if(ans_root[0] != '\0') 
	      {
	 	my_grep(ans_root,DBM_FLAG,db,answer);
		if(answer[0] != '\0')
		  //strcat(answer,"?_ceVyyi");
		  strcat(answer,wrd[2]);
	//sprintf(logmsg,"NAGARAJ INFO:suffix_6=%s|pdgm=%s|answer=%s",suffix_6,pdgm,answer);PRINT_LOG(log_file,logmsg);
	      }
	  }
	//if(!strcmp(suffix_6,"veVyyi") && !strcmp(pdgm,"ceVyyi")) 
	if(!strcmp(suffix_6,wrd[0]) && !strcmp(pdgm,wrd[1])) 
	 {
	   derived_root = 1;
	   strncpy(ans_root,root,len-6);
	   ans_root[len-6] = '\0';
	   if(ans_root[0] != '\0') 
	     {
		my_grep(ans_root,DBM_FLAG,db,answer);
		if(answer[0] != '\0') 
		 // strcat(answer,"?_veVyyi");
		  strcat(answer,wrd[2]);
	//sprintf(logmsg,"NAGARAJ INFO:suffix_6=%s|pdgm=%s|answer=%s",suffix_6,pdgm,answer);PRINT_LOG(log_file,logmsg);
	     }
	}
	//if(!strcmp(suffix_6,"paracu") && !strcmp(pdgm,"pannu")) 
	if(!strcmp(suffix_6,wrd[0]) && !strcmp(pdgm,wrd[1])) 
	  {
	   derived_root = 1;
	   strncpy(ans_root,root,len-6);
	   ans_root[len-6] = '\0';
	   if(ans_root[0] != '\0') 
	    {
		my_grep(ans_root,DBM_FLAG,db,answer);
	        if(answer[0] != '\0')
		 // strcat(answer,"?_paracu");
		  strcat(answer,wrd[2]);
	//sprintf(logmsg,"NAGARAJ INFO:suffix_6=%s|pdgm=%s|answer=%s",suffix_6,pdgm,answer);PRINT_LOG(log_file,logmsg);
	    }
	  }
	//if(!strcmp(suffix_4,"lAdu") && !strcmp(pdgm,"Adu")) 
	if(!strcmp(suffix_4,wrd[0]) && !strcmp(pdgm,wrd[1])) 
	  {
	    derived_root = 1;
	    strncpy(ans_root,root,len-4);
	    ans_root[len-4] = '\0';
	    if(ans_root[0] != '\0') 
	     {
	       my_grep(ans_root,DBM_FLAG,db,answer);
	       if(answer[0] != '\0') 
		//strcat(answer,"?_lAdu");
		strcat(answer,wrd[2]);
	//sprintf(logmsg,"NAGARAJ INFO:suffix_4=%s|pdgm=%s|answer=%s",suffix_4,pdgm,answer);PRINT_LOG(log_file,logmsg);
	     }
	  }
	//if(!strcmp(suffix_6,"peVttu") && !strcmp(pdgm,"peVttu")) 
	if(!strcmp(suffix_6,wrd[0]) && !strcmp(pdgm,wrd[1])) 
	  {
	    derived_root = 1;
	    strncpy(ans_root,root,len-6);
	    ans_root[len-6] = '\0';
	    if(ans_root[0] != '\0') 
		{
	//printf("ans_root=%s|DBM_FLAG=%d|db=%d|answer=%s|\n",ans_root,DBM_FLAG,db,answer);
		  my_grep(ans_root,DBM_FLAG,db,answer);
	//printf("After ans_root=%s|DBM_FLAG=%d|db=%d|answer=%s|\n",ans_root,DBM_FLAG,db,answer);
	          if(answer[0] != '\0') 
		   // strcat(answer,"?_peVttu");
		   strcat(answer,wrd[2]);
	//sprintf(logmsg,"NAGARAJ INFO:suffix_6=%s|pdgm=%s|answer=%s",suffix_6,pdgm,answer);PRINT_LOG(log_file,logmsg);
	        }
	  }

	if(DEBUG && derived_root)
	 {
	   //printf("%s\n",ans_root);
	   //printf("%d\n",derived_root);
	    //sprintf(logmsg,"%s\n",ans_root);PRINT_LOG(log_file,logmsg);	  /* prints the final root after adjectives are added */
	    //sprintf(logmsg,"%d\n",derived_root);PRINT_LOG(log_file,logmsg);  /* prints the derived root */
	 }
	}//added by Nagaraju to remove hard coded verb_heuristics
	//sprintf(logmsg,"Exiting derived_verb_heuristics");PRINT_LOG(log_file,logmsg);
    }

void my_grep(ans_root,DBM_FLAG,db,answer)
   char ans_root[SUFFWORDSIZE],answer[SUFFWORDSIZE];
   int DBM_FLAG;
   GDBM_FILE db;
   {
	char tmp[SUFFWORDSIZE];
	int loop1,FLAG;
	char ans_ar[SmallArray][LargeArray];
	strcpy(answer,"");
	strcpy(tmp,ans_root);
	FLAG = 0;
 	//added by Nagaraju for removing hard coding
	 for(j=0;j<size_of_file;j++) {
                for(i=0;i<3;i++){
                strcpy(wrd[i],"\0");}
                split_arr(words[j],' ',wrd);//hard coded remover

	for(loop1=0;((loop1<5) && (!FLAG));loop1++)
	 {
	  strcpy(ans_root,tmp);
	  //if(loop1==1)
	  if(loop1==wrd[0])
	  //if(!strcmp(loop1,wrd[0]))
	    {
		//strcat(ans_root,"u");
		strcat(ans_root,wrd[1]);
	    }
	/*else if(loop1==2)
	 {
	   strcat(ans_root,"i");
	   //strcat(ans_root,wrd[1]);
	 }
	else if(loop1==3)
	 {
	   strcat(ans_root,"a");
	   //strcat(ans_root,wrd[1]);
	 }
	else if(loop1==4) 
	 {
	   strcat(ans_root,"eV");
	   //strcat(ans_root,wrd[1]);
	 }*/
	/*This function checks the word in the dictionary */
	dict_lookup(ans_root,DBM_FLAG,db,lex_ar->word,sizeof_lex,sizeof(lex_ar[0]),strcmp,ans_ar);
	if(ans_ar[0][0] != '\0')
	  {
	/*
	printf(logmsg,"answer = %s\n",ans_ar[0]);
	*/
	strcpy(answer,ans_ar[0]);
	FLAG = 1;
	  }
	 }
	/*
	printf("answer = %s\n",answer);
	*/
	}//added by Nagaraju to remove hard coded verb_heuristics
    }
