/**
 * FILE Name :derived_root_heuristics.c
*/

/** Function Name : derived_root_heuristics
 * This function depending on suffix below mentioned changes its derived root
 *The arguments:
 * root of char type ,pdgm of char type, DBM_FLAG of int type ,db_lex of GDBM_LEX file type
 * ans_root of char type, aux_verb of char type
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
#define FUNCTION "derived_root_heuristics()"


extern int DEBUG;	/* is used for checking existance of root */

extern int sizeof_adaM_suff;
extern int sizeof_wunna_suff;
extern int sizeof_ani_suff;
extern int sizeof_ina_suff;
extern int sizeof_e_suff;

/* suff_info structure contains info of suffix, add, pdgm, category, offset */
extern struct suff_info adaM_suff_info_ar[];
extern struct suff_info wunna_suff_info_ar[];
extern struct suff_info ani_suff_info_ar[];
extern struct suff_info ina_suff_info_ar[];
extern struct suff_info e_suff_info_ar[];

derived_roots_heuristics(root,pdgm,DBM_FLAG,db_lex,ans_root)

   char root[SUFFWORDSIZE],pdgm[WORD_SIZE];	/* root of the word, paradigm */
    int DBM_FLAG;				/* global dictionary flag ,if 1 then
                                               dictionary is there */
   GDBM_FILE db_lex;		/* GNU database manager includes dbm and ndb
                                   compatability and db_flex is used for opening file */
   
   char ans_root[SUFFWORDSIZE];	 /*  root after derivation */
    {
	char *program_name="derived_root_heuristics.c";
        PRINT_LOG(log_file," This function depending on suffix below mentioned changes root");
	int len,derived_root;   /* length of the root,derived root,  */
	char tmp_root[SUFFWORDSIZE];/* temporary root */
		    /* different suffixes */
	char suffix_2[3],suffix_3[4],suffix_4[5],suffix_5[6],suffix_6[7],suffix_7[8],suffix_8[9],suffix_9[10];
	
	strcpy(tmp_root,root);	/* cpoiest root to temporary root */
	len = strlen(root);

	if(len>9) strcpy(suffix_9 , root+len-9); else strcpy(suffix_9,"");
	if(len>9) strcpy(suffix_8 , root+len-8); else strcpy(suffix_8,"");
	if(len>9) strcpy(suffix_7 , root+len-7); else strcpy(suffix_7,"");
	if(len>9) strcpy(suffix_6 , root+len-6); else strcpy(suffix_6,"");
	if(len>9) strcpy(suffix_5 , root+len-5); else strcpy(suffix_5,"");
	if(len>9) strcpy(suffix_4 , root+len-4); else strcpy(suffix_4,"");
	if(len>9) strcpy(suffix_3 , root+len-3); else strcpy(suffix_3,"");
	if(len>9) strcpy(suffix_2 , root+len-2); else strcpy(suffix_2,"");

	derived_root = 0;
	ans_root[0] = '\0';
	/* iMcu case */
	/* comparing iMcu with suffix _4 and   paradigm with cUpiMcu
           executes only when all the  conditions are satisfied  */
	if(!strcmp(suffix_4,"iMcu") && !strcmp(pdgm,"cUpiMcu")) 
	  {
	    derived_root = 1;
	    strncpy(ans_root,root,len-4);
	    ans_root[len-4] = '\0';
	    if(ans_root[0] != '\0') 	/* executes when ans_root not equal to null */
		//strcat(ans_root,"?_iMcu");
		strcat(aux_verb,"iMcu_");
	    strcpy(root,tmp_root);
	  }
	/* wunna Cases */
	/* comparing wunnavAdu with suffix_9 or cunnavAdu with suffix_9 and   paradigm with vAdu
           executes only when all the  conditions are satisfied  */
	else if((!strcmp(suffix_9,"wunnavAdu") || !strcmp(suffix_9,"cunnavAdu")) && !strcmp(pdgm,"vAdu")) 
	   {
	     derived_root = 1;
		/* this function is used to find the derivational root */
	     get_derived_rt(root,wunna_suff_info_ar->suffix,sizeof_wunna_suff,sizeof(wunna_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	     if(ans_root[0] != '\0') /* executes when ans_root not equal to null */
		//strcat(ans_root,"_wunna_vAdu");
		strcat(aux_verb,"vAdu_");
	   }
	/* comparing wunnavAru with suffix_9 or cunnavAru with suffix_9 and   paradigm with vAdu
           executes only when all the  conditions are satisfied  */
	else if((!strcmp(suffix_9,"wunnavAru") || !strcmp(suffix_9,"cunnavAru")) && !strcmp(pdgm,"vAru")) 
	   {
	      derived_root = 1;
		/* this function is used to find the derivational root */
	      get_derived_rt(root,wunna_suff_info_ar->suffix,sizeof_wunna_suff,sizeof(wunna_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	      if(ans_root[0] != '\0') /* executes when ans_root not equal to null */
	        //strcat(ans_root,"_wunna_vAru");
	        strcat(aux_verb,"vAru_");
	   }	
	/* comparing wunnaaxi with suffix_8 or cunnaaxiu with suffix_5 and   paradigm with vAdu
           executes only when all the  conditions are satisfied  */
	else if((!strcmp(suffix_8,"wunnaaxi") || !strcmp(suffix_8,"cunnaaxi")) && !strcmp(pdgm,"axi")) 
	  {
	    derived_root = 1;
	    len = strlen(root);
	    root[len-3] = 'x';
	    root[len-2] = 'i';
	    root[len-1] = '\0';
		/* this function is used to find the derivational root  */
	    get_derived_rt(root,wunna_suff_info_ar->suffix,sizeof_wunna_suff,sizeof(wunna_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	    if(ans_root[0] != '\0') 	 /* executes when ans_root not equal to null */
		//strcat(ans_root,"_wunna_axi");
		strcat(aux_verb,"axi_");
	    strcpy(root,tmp_root);
	  }
	/* comparing wunnaxi with suffix_7 or cunnaxiu with suffix_5 and   paradigm with vAdu
           executes only when all the  conditions are satisfied  */
	else if((!strcmp(suffix_7,"wunnaxi") || !strcmp(suffix_7,"cunnaxi")) && !strcmp(pdgm,"axi")) 
	  {
	    derived_root = 1;
		/* thsi function is used to find the derivational root  */
	    get_derived_rt(root,wunna_suff_info_ar->suffix,sizeof_wunna_suff,sizeof(wunna_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	    if(ans_root[0] != '\0')  /* executes when ans_root not equal to null */
	      //strcat(ans_root,"_wunna_axi");
	      strcat(aux_verb,"axi_");
	  }
	/* ani cases */
	/* comparing univAdu with suffix_6 and  paradigm with vAdu
           executes only when all the  conditions are satisfied  */
	else if(!strcmp(suffix_6,"nivAdu") && !strcmp(pdgm,"vAdu")) 
	  {
	    derived_root = 1;
		/* thsi function is used to find the derivational root  */
	    get_derived_rt(root,ani_suff_info_ar->suffix,sizeof_ani_suff,sizeof(ani_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	    if(ans_root[0] != '\0') 	/* executes when ans_root not equal to null */
		//strcat(ans_root,"_fin_negp_vAdu");
		strcat(aux_verb,"vAdu_");
	  }
	/* comparing nivAru with suffix_6  paradigm with vAru
           executes only when all the  conditions are satisfied  */
	else if(!strcmp(suffix_6,"nivAru") && !strcmp(pdgm,"vAru")) 
	  {
	    derived_root = 1;
		/* this function is used to find the derivational root */
	    get_derived_rt(root,ani_suff_info_ar->suffix,sizeof_ani_suff,sizeof(ani_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	    if(ans_root[0] != '\0')    /* executes when ans_root not equal to null */
		 //strcat(ans_root,"_fin_negp_vAru");
		 strcat(aux_verb,"vAru_");
	  }
	/* comparing naxi with suffix_4 paradigm with axi
           executes only when all the  conditions are satisfied  */
	else if(!strcmp(suffix_4,"naxi") && !strcmp(pdgm,"axi")) 
	  {
	    derived_root = 1;
	    len = strlen(root);
	    root[len-3] = 'x';
	    root[len-2] = 'i';
	    root[len-1] = '\0';
	    get_derived_rt(root,ani_suff_info_ar->suffix,sizeof_ani_suff,sizeof(ani_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	    if(ans_root[0] != '\0')
	     	 //strcat(ans_root,"_fin_negp_axi");
	     	 strcat(aux_verb,"axi_");
	    strcpy(root,tmp_root);
	  }
	/* comparing naxi with suffix_4 paradigm with axi
           executes only when all the  conditions are satisfied  */
	else if(!strcmp(suffix_4,"naxi") && !strcmp(pdgm,"axi")) 
	  {
	     derived_root = 1;
	     /* this function is used to find the derivational root */
	     get_derived_rt(root,ani_suff_info_ar->suffix,sizeof_ani_suff,sizeof(ani_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	     if(ans_root[0] != '\0') /* executes when ans_root not equal to null */
		 //strcat(ans_root,"_fin_negp_axi");
		 strcat(aux_verb,"axi_");
	  }
	/* ina cases */
	/* comparing inavAdu with suffix_7 or nnavAdu with suffix_5  paradigm with vAdu
           executes only when all the  conditions are satisfied  */
	else if((!strcmp(suffix_7,"inavAdu") || !strcmp(suffix_7,"nnavAdu")) && !strcmp(pdgm,"vAdu")) 
	  {
	    derived_root = 1;
            /* this function is used to find the derivational root */
	    get_derived_rt(root,ina_suff_info_ar->suffix,sizeof_ina_suff,sizeof(ina_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	    if(ans_root[0] != '\0')  /* executes when ans_root not equal to null */
		//strcat(ans_root,"_ina_vAdu");
		strcat(aux_verb,"vAdu_");
	  }
	/* comparing inavAru with suffix_7 or nnavAru with suffix_5  paradigm with vAru
           executes only when all the  conditions are satisfied  */
	else if((!strcmp(suffix_7,"inavAru") || !strcmp(suffix_7,"nnavAru")) && !strcmp(pdgm,"vAru")) 
	  {
	    derived_root = 1;
		/* this function is used to find the derivational root */
	    get_derived_rt(root,ina_suff_info_ar->suffix,sizeof_ina_suff,sizeof(ina_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	    if(ans_root[0] != '\0')	/* executes when ans_root not equal to null */
	 	 //strcat(ans_root,"_ina_vAru");
	 	 strcat(aux_verb,"vAru_");
	  }
	/* comparing inaaxi with suffix_6 or nnaxi with suffix_5  paradigm with axi
           executes only when all the  conditions are satisfied  */
	else if((!strcmp(suffix_6,"inaaxi") || !strcmp(suffix_5,"nnaxi") ) && !strcmp(pdgm,"axi")) 
	  {
	     derived_root = 1;
	     len = strlen(root);
	     root[len-3] = 'x';
	     root[len-2] = 'i';
	     root[len-1] = '\0';
	     /* this function is used to find the derivational root */
	     get_derived_rt(root,ina_suff_info_ar->suffix,sizeof_ina_suff,sizeof(ina_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	     if(ans_root[0] != '\0') /* executes when ans_root not equal to null */
		//strcat(ans_root,"_ina_axi");
		strcat(aux_verb,"axi_");
	     strcpy(root,tmp_root);
	  }
	/* comparing inaxi with suffix_5 paradigm with axi
           executes only when all the  conditions are satisfied  */
         else if(!strcmp(suffix_5,"inaxi") && !strcmp(pdgm,"axi")) 
	   {
	     derived_root = 1;
	     /* this function is used to find the derivational root */
	     get_derived_rt(root,ina_suff_info_ar->suffix,sizeof_ina_suff,sizeof(ina_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	     if(ans_root[0] != '\0')	/* executes when ans_root not equal to null */
		 //strcat(ans_root,"_ina_axi");
		 strcat(aux_verb,"axi_");
	   }
	/* e cases */
	/* comparing uvAdu with suffix_5 or evAdu with suffix_5  paradigm with vAdu
           executes only when all the  conditions are satisfied  */
	else if((!strcmp(suffix_5,"uvAdu") || !strcmp(suffix_5,"evAdu")) && !strcmp(pdgm,"vAdu")) 	   {
	     derived_root = 1;
	     /* this function is used to find the derivational root */
	     get_derived_rt(root,e_suff_info_ar->suffix,sizeof_e_suff,sizeof(e_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	     if(ans_root[0] != '\0')    /* executes when ans_root not equal to null */
		//strcat(ans_root,"_e_vAdu");
		strcat(aux_verb,"vAdu_");
	  }
	 /* comparing uvAr with suffix_5 or evAru with suffix_5  paradigm with vAdu
           executes only when all the  conditions are satisfied  */ 
	else if((!strcmp(suffix_5,"uvAru") || !strcmp(suffix_5,"evAru")) && !strcmp(pdgm,"vAru")) 	   {
	    derived_root = 1;
	    /* this function is used to find the derivational root */
	    get_derived_rt(root,e_suff_info_ar->suffix,sizeof_e_suff,sizeof(e_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	    if(ans_root[0] != '\0')  /* executes when ans_root not equal to null */
		//strcat(ans_root,"_e_vAru");
		strcat(aux_verb,"vAru_");
	  }
	 /* comparing unaxi with suffix_5 or eaxi with the suffix_4 and paradigm with  eaxi
		 with suffix_4  and paradigm with axi */
	    else if((!strcmp(suffix_5,"unaxi") || !strcmp(suffix_4,"eaxi")) && !strcmp(pdgm,"axi")) 
	     {
	    derived_root = 1;
	    len = strlen(root);
	    root[len-3] = 'x';
	    root[len-2] = 'i';
	    root[len-1] = '\0';
	    /* this function is used to find the derivational root */
	    get_derived_rt(root,e_suff_info_ar->suffix,sizeof_e_suff,sizeof(e_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	    if(ans_root[0] != '\0')	/* executes when ans_root not equal to null */
	      //strcat(ans_root,"_e_axi");
	      strcat(aux_verb,"axi_");
	    strcpy(root,tmp_root);
	  }
	 /* comparing exi with suffix_3 and paradigm with axi
           executes only when all the  conditions are satisfied  */
	else if(!strcmp(suffix_3,"exi") && !strcmp(pdgm,"axi")) 
	  {
	     derived_root = 1;
	     /* this function is used to find the derivational root */
	     get_derived_rt(root,e_suff_info_ar->suffix,sizeof_e_suff,sizeof(e_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	     if(ans_root[0] != '\0')	/* executes when ans_root not equal to null */
		 //strcat(ans_root,"_e_axi");
		 strcat(aux_verb,"axi_");
	  }
	/*adaM cases */
        /* comparing adaM with suffix_4 or ataM with suffix_4 or adamu with suffix_5 or
        atamu with suffix_5  or otaM with suffix_4 or odaM with suffix_4 or otamu with suffix_5
         or odamu with suffix_5 or ddaM with suffix_4 or ttaM with suffix_4
        and paradigm with puswakaM  executes only when all the  conditions are satisfied  */
	else if((!strcmp(suffix_4,"adaM") || (!strcmp(suffix_4,"ataM")) || !strcmp(suffix_5,"atamu") || !strcmp(suffix_5,"adamu") || !strcmp(suffix_4,"otaM") || !strcmp(suffix_4,"odaM") || !strcmp(suffix_5 ,"otamu") || !strcmp(suffix_5,"odamu") || !strcmp(suffix_4,"ddaM") || !strcmp(suffix_4,"ttaM")) && !strcmp(pdgm,"puswakaM")) 
	  {
	    derived_root = 1;
		/* this function is used to find the derivational root */
	    get_derived_rt(root,adaM_suff_info_ar->suffix,sizeof_adaM_suff,sizeof(adaM_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	    if(ans_root[0] != '\0') 	/* executes when ans_root is equal to null */
	      	//strcat(ans_root,"_adaM");
	      	strcat(aux_verb,"adaM_");
	  }
	 /* comparing uta with suffix_3 and paradigm with kota ,
             executes only when all the conditions are satisfied  */
	else if(!strcmp(suffix_3,"uta") && !strcmp(pdgm,"kota")) 
	  {
	    derived_root = 1;
	     /* this function is used to find the derivational root */
	    get_derived_rt(root,adaM_suff_info_ar->suffix,sizeof_adaM_suff,sizeof(adaM_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,ans_root);
	    if(ans_root[0] != '\0') 	/* executes when ans_root is equal to null */
		//strcat(ans_root,"_adaM");
		strcat(aux_verb,"adaM_");
	  }
	if(DEBUG && derived_root)	/* executes when word and derived_root exists */
	  {
	     printf("%s\n",ans_root);	/* prints the final root after adjectives are added */
	     printf("%d\n",derived_root);/* prints the derived root */
	  }
    }
