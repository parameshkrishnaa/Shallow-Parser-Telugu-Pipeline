/**
 * FILE Name :derived_adv_noun_heuristics.c
*/

/** derived_adv_noun_heuristics
 * This function depending on suffix below mentioned changes noun to adverb
 * The arguments:
 * root of char type ,pdgm of char type, DBM_FLAG of int type ,db_lex of GDBM_LEX file type
 * ans_root of char type, aux_verb of char type
 * integer pointer
 * Return : void
 */

 /* HEADER FILES */

#include <gdbm.h>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./headers/defn.h"
#include "./headers/struct.h"
#include "./headers/struct1.h"
#include "./common/analyser/morph_logger.h"


extern FILE *log_file;
extern char *logmsg;
#define FUNCTION "derived_adv_noun_heuristics()"


extern int DEBUG;		/* is used for checking existance of root */

extern int sizeof_adv_xi;
extern int sizeof_e_suff;

/* suff_info structure contains info of suffix, add, pdgm, category, offset */
extern struct suff_info adv_xi_ar[];
extern struct suff_info e_suff_info_ar[];

/**
 * Prototypes of the functions in this file with a file scope
 */

extern void get_derived_rt();

void derived_adv_noun_heuristics(root,pdgm,DBM_FLAG,db_lex,ans_root,aux_verb)

  char root[SUFFWORDSIZE],pdgm[WORD_SIZE];	/* root of the word, paradigm */
  int DBM_FLAG;					/* global dictionary flag ,if 1 then dictionary
                                                is there */
  GDBM_FILE db_lex;			/* GNU database manager includes dbm and ndb
                                            compatability and db_flex is used for opening file */
  char ans_root[SUFFWORDSIZE];		/*  root after derivation */
  char aux_verb[SUFFWORDSIZE];		/* auxilary verb */
      {
	char *program_name="derived_adv_noun_heuristics.c";
        PRINT_LOG(log_file,"This function depending on suffix below mentioned changes noun to adverb");
	int len,derived_root;		/* length of the root, derived root */
	/* different suffixes */
	char suffix_2[3],suffix_3[4],suffix_4[5],suffix_6[7],suffix_8[9],suffix_10[11];
	char tmp_root[SUFFWORDSIZE];	    /* temporary suffix */
	char offset_aux_str[SUFFWORDSIZE];  /* offset auxilary string */

	len = strlen(root);		   /* finding length of the root */
	strcpy(tmp_root,root);
	if(len>10)strcpy(suffix_10 , root+len-10); else strcpy(suffix_10,"");
	if(len>8)strcpy(suffix_8 , root+len-8); else strcpy(suffix_8,"");
	if(len>6)strcpy(suffix_6 , root+len-6); else strcpy(suffix_6,"");
	if(len>4)strcpy(suffix_4 , root+len-4); else strcpy(suffix_4,"");
	if(len>3)strcpy(suffix_3 , root+len-3); else strcpy(suffix_3,"");
	if(len>2)strcpy(suffix_2 , root+len-2); else strcpy(suffix_2,"");
	
	//sprintf(logmsg,"NAGARAJ INFO:Entering derived_adv_noun_heuristics");PRINT_LOG(log_file,logmsg);

	derived_root = 0;		/* intialising derived_root to 0 */
	ans_root[0] = '\0';		 /* final answer is assigned to null */
	
		    FILE *fp;
			char buff[1000];
			int size_of_file=0,j,i;
			char words[1000][200];
			char wrd[15][50];
	char adv_file[BigArray];
	strcpy(adv_file,getenv("setu"));
	strcat(adv_file, "/morph/data_bin/sl/morph/tel/derivation/derived_adv_noun.p");
	//buff[0]='\0';
	//words[0][0]="\0";
	//wrd[0][0]="\0";
		//fp=fopen("derivation/derived_adv_noun.p","r");
		//fp=fopen("/home/guest/oldmorph/data_bin/sl/morph/tel/derivation/derived_adv_noun.p","r");
		//fp=fopen("/home/guest/oldmorph/data_src/sl/morph/tel/pc_data/derivation/derived_adv_noun.p","r");
		//fp=fopen("/var/www/html/morph/telmorph/data_src/sl/morph/tel/pc_data/derivation/derived_adv_noun.p","r");
		//fp=fopen("../../../../data_src/sl/morph/tel/pc_data/derivation/derived_adv_noun.p","r");
		fp=fopen(adv_file,"r");
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
                        //sprintf(logmsg,"The file derived_adv_noun.p cannot be opened\n");
			PRINT_LOG(log_file,logmsg);
                        exit(0);}
			fclose(fp);
		//Nagaraju
		for(j=0;j<size_of_file;j++) { 
		for(i=0;i<3;i++){
		strcpy(wrd[i],"\0");}
		split_arr(words[j],' ',wrd);
		//printf("%s|%s|%s\n",wrd[0],wrd[1],wrd[2]);
	/*etappudu case */
	/* comparing etappudu with above suffix_8 or eppudu with suffix_6 and 
            paradigm with appudu and ans_root equals to null.executes only 
           when all the conditions are satisfied  */
	//if(((!strcmp(suffix_8,"etappudu")) || (!strcmp(suffix_6,"eppudu"))) && !strcmp(pdgm,"appudu") && ( ans_root[0] == '\0')) 
	if(((!strcmp(suffix_8,wrd[0])) || (!strcmp(suffix_6,wrd[0]))) && !strcmp(pdgm,wrd[1]) && ( ans_root[0] == '\0')) 
	  {
	    derived_root = 1;                                
	    len = strlen(root);
            /* executes when suffix_8 and etappudu are not equal */
	    //if(!strcmp(suffix_8,"etappudu")) 
	    if(!strcmp(suffix_8,wrd[0])) 
               root[len-7] = '\0';
            /* executes when suffix_6 and eppudu are not equal */ 
	    //if(!strcmp(suffix_6,"eppudu")) 
	    if(!strcmp(suffix_6,wrd[0])) 
               root[len-5] = '\0';
             /* This function is used to  to find derivational root */
//	    get_derived_rt(root,e_suff_info_ar->suffix,sizeof_e_suff,sizeof(e_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,"verb",ans_root,aux_verb,offset_aux_str);
	    get_derived_rt(root,e_suff_info_ar->suffix,sizeof_e_suff,sizeof(e_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	    if(ans_root[0] != '\0')    /* executes when ans_root not equal to null */
	      {                                      
	        if(aux_verb[0] != '\0')  /* executes when aux_verb not equal to null */
                   { 
                     strcat(ans_root,"_"); 
                     strcat(ans_root,aux_verb);
                     strcpy(aux_verb,"");
                   }
                //strcat(ans_root,"_e_appudu_adv");
                //strcat(aux_verb,"_e_appudu");
                strcat(aux_verb,wrd[2]);
	//sprintf(logmsg,"NAGARAJ INFO:suffix_6=%s|suffix_8=%s|pdgm=%s|aux_verb=%s",suffix_6,suffix_8,pdgm,aux_verb);PRINT_LOG(log_file,logmsg);
              }
           }
	/*etaMwasepu case */
       /* comparing eMwasepu with above suffix_8 or etaMwasepu with suffix_10 and
            paradigm with munupu and ans_root equals to null.executes only
           when all the conditions are satisfied  */
	//if(((!strcmp(suffix_8,"eMwasepu")) || (!strcmp(suffix_10,"etaMwasepu"))) && !strcmp(pdgm,"munupu") && ( ans_root[0] == '\0')) 
	if(((!strcmp(suffix_8,wrd[0])) || (!strcmp(suffix_10,wrd[0]))) && !strcmp(pdgm,wrd[1]) && ( ans_root[0] == '\0')) 
          {
	     derived_root = 1;                                
	     len = strlen(root);
             /* executes when suffix_8 compared with eMwasepu are not equal */
	     //if(!strcmp(suffix_8,"eMwasepu")) 
	     if(!strcmp(suffix_8,wrd[0])) 
               root[len-7] = '\0';
	     else 
             /* executes when suffix_10 compared with eMwasepu are not equal */
               //if(!strcmp(suffix_10,"etaMwasepu")) 
               if(!strcmp(suffix_10,wrd[0])) 
                 root[len-9] = '\0';
	     /* This function is used to  to find derivational root */
//	     get_derived_rt(root,e_suff_info_ar->suffix,sizeof_e_suff,sizeof(e_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,"verb",ans_root,aux_verb,offset_aux_str);
	     get_derived_rt(root,e_suff_info_ar->suffix,sizeof_e_suff,sizeof(e_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	     if(ans_root[0] != '\0')      /* executes when ans_root not equal to null */        
	       {                                      
	         if(aux_verb[0] != '\0')  /* executes when aux_verb not equal to null */
                   { 
                     strcat(ans_root,"_"); 
                     strcat(ans_root,aux_verb);
                     strcpy(aux_verb,"");
                   }
                 //strcat(ans_root,"_e_appudu_adv");
                 //strcat(aux_verb,"e_appudu_adv");
                 //strcat(aux_verb,"e_appudu");
                 strcat(aux_verb,wrd[2]);
	//sprintf(logmsg,"NAGARAJ INFO:suffix_10=%s|suffix_8=%s|pdgm=%s|aux_verb=%s",suffix_10,suffix_8,pdgm,aux_verb);PRINT_LOG(log_file,logmsg);
               }
          }
	/* vAdu Cases */
       /* comparing vAdu with above suffix_4 paradigm with vAdu and ans_root equals to null.
           executes only when all the conditions are satisfied  */
	//if((!strcmp(suffix_4,"vAdu")) && !strcmp(pdgm,"vAdu") && ( ans_root[0] == '\0')) 
	if((!strcmp(suffix_4,wrd[0])) && !strcmp(pdgm,wrd[1]) && ( ans_root[0] == '\0')) 
	  {
	    derived_root = 1;
	     /* This function is used to  to find derivational root */
//	    get_derived_rt(root,adv_xi_ar->suffix,sizeof_adv_xi,sizeof(adv_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	    get_derived_rt(root,adv_xi_ar->suffix,sizeof_adv_xi,sizeof(adv_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	    if(ans_root[0] != '\0')	/* executes when ans_root not equal to null */
	      {
	        if(aux_verb[0] != '\0') /* executes when aux_verb not equal to null */
                  { 
                    strcat(ans_root,"_"); 
                    strcat(ans_root,aux_verb);
                    strcpy(aux_verb,"");
                  }
                //strcat(ans_root,"_vAdu");
                //strcat(aux_verb,"vAdu");
                strcat(aux_verb,wrd[2]);
	//sprintf(logmsg,"NAGARAJ INFO:suffix_4=%s|pdgm=%s|aux_verb=%s",suffix_4,pdgm,aux_verb);PRINT_LOG(log_file,logmsg);
              }
          }
	/* axi Cases */
       /* comparing axi with above suffix_3 paradigm with axi and ans_root equals to null.
           executes only when all the conditions are satisfied  */
	//if((!strcmp(suffix_3,"axi")) && !strcmp(pdgm,"axi") && ( ans_root[0] == '\0')) 
	if((!strcmp(suffix_3,wrd[0])) && !strcmp(pdgm,wrd[1]) && ( ans_root[0] == '\0')) 
	  {
	     root[len-3] = 'x';
	     root[len-2] = 'i';
	     root[len-1] = '\0';
	     derived_root = 1;
	     /* This function is used to  to find derivational root */
//	     get_derived_rt(root,adv_xi_ar->suffix,sizeof_adv_xi,sizeof(adv_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	     get_derived_rt(root,adv_xi_ar->suffix,sizeof_adv_xi,sizeof(adv_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	     if(ans_root[0] != '\0') 		/* executes when ans_root not equal to null */
		{
		  if(aux_verb[0] != '\0') 	/* executes when aux_verb not equal to null */
                    { 
                      strcat(ans_root,"_"); 
                      strcat(ans_root,aux_verb);
                      strcpy(aux_verb,""); 
                    }
	          //strcat(ans_root,"_xi");
	          //strcat(aux_verb,"xi_");
	          strcat(aux_verb,wrd[2]);
	//sprintf(logmsg,"NAGARAJ INFO:suffix_3=%s|pdgm=%s|aux_verb=%s",suffix_3,pdgm,aux_verb);PRINT_LOG(log_file,logmsg);
		}
	  }
       /* comparing xi with above suffix_2 paradigm with axi and ans_root equals to null.
           executes only when all the conditions are satisfied  */
	//if((!strcmp(suffix_2,"xi")) && !strcmp(pdgm,"axi") && ( ans_root[0] == '\0')) 
	if((!strcmp(suffix_2,wrd[0])) && !strcmp(pdgm,wrd[1]) && ( ans_root[0] == '\0')) 
	   {
	     derived_root = 1;
	     /* This function is used to  to find derivational root */
//	     get_derived_rt(root,adv_xi_ar->suffix,sizeof_adv_xi,sizeof(adv_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	     get_derived_rt(root,adv_xi_ar->suffix,sizeof_adv_xi,sizeof(adv_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	      if(ans_root[0] != '\0') 		/* executes when ans_root not equal to null */
		{
		   if(aux_verb[0] != '\0') 	/* executes when aux_verb not equal to null */
                     { 
                       strcat(ans_root,"_"); 
                       strcat(ans_root,aux_verb);
                       strcpy(aux_verb,"");
                     }
		    //strcat(ans_root,"_xi");
		    //strcat(aux_verb,"xi_");
		    strcat(aux_verb,wrd[2]);
	//sprintf(logmsg,"NAGARAJ INFO:suffix_2=%s|pdgm=%s|aux_verb=%s",suffix_2,pdgm,aux_verb);PRINT_LOG(log_file,logmsg);
		}
	   }
}//added by Nagaraju to removed hardcoding in ad_noun_heuristics

	if(DEBUG && derived_root)	/* executes when word and derived_root exists */
	  {
	    //sprintf(logmsg,"%s\n",ans_root);PRINT_LOG(log_file,logmsg);	  /* prints the final root after adjectives are added */
	    //sprintf(logmsg,"%d\n",derived_root);PRINT_LOG(log_file,logmsg);  /* prints the derived root */
	  }
	//sprintf(logmsg,"NAGARAJ INFO:Exiting derived_noun_adv_heuristics");PRINT_LOG(log_file,logmsg);
      }
