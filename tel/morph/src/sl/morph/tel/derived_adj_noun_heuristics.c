/**
 * FILE Name :derived_adj_noun_heuristics.c
*/

/** derived_adj_noun_heuristics
 * This function depending on suffix below mentioned changes adjective to noun
 * The arguments:
 * root of char type ,pdgm of char type, DBM_FLAG of int type ,db_lex of GDBM_LEX file type
 * ans_root of char type, aux_verb of char type
 * integer pointer
 * Return : void
 */

 /* HEADER FILES */

#include <gdbm.h>
#include<stdlib.h>
#include <string.h>
#include <stdio.h>
#include "./headers/defn.h"
#include "./headers/struct.h"
#include "./headers/struct1.h"
#include "./common/analyser/morph_logger.h"


extern FILE *log_file;
extern char *logmsg;
#define FUNCTION "derived_adj_noun_heuristics()"


extern int DEBUG;	/* is used for checking existance of root */

extern int sizeof_adj_xi;
extern int sizeof_adj_ni;
extern int sizeof_adj_nEna;
extern int sizeof_adj_pAti;
extern int sizeof_e_suff;

extern struct suff_info adj_xi_ar[];
extern struct suff_info adj_ni_ar[];
extern struct suff_info adj_nEna_ar[];
extern struct suff_info adj_pAti_ar[];
extern struct suff_info e_suff_info_ar[];

extern void get_derived_rt();

void derived_adj_noun_heuristics(root,pdgm,DBM_FLAG,db_lex,ans_root,aux_verb)

  char root[SUFFWORDSIZE],pdgm[WORD_SIZE];   /* root of the word, paradigm */
  int DBM_FLAG;                              /* global dictionary flag ,if 1 then dictionary
                                                is there */
  GDBM_FILE db_lex;                          /* GNU database manager includes dbm and ndb
                                            compatability and db_flex is used for opening file */  char ans_root[SUFFWORDSIZE];               /*  root after derivation */
  char aux_verb[SUFFWORDSIZE];               /* auxilary verb */
    {
	char *program_name="derived_adj_noun_heuristics.c";
        PRINT_LOG(log_file,"this function depending on suffix below mentioned changes adjective to noun");
      int len,derived_root;                  /* length of the root */
       /* different suffixes */
      char suffix_2[3],suffix_3[4],suffix_4[5],suffix_5[6],suffix_6[7],suffix_7[8],suffix_10[11];      
	char tmp_root[SUFFWORDSIZE];           /* temporary suffix */
      char offset_aux_str[SUFFWORDSIZE];     /* offset auxilary string */

      len = strlen(root);             /* finding length of the root */
      strcpy(tmp_root,root);

	if(len>10) strcpy(suffix_10 , root+len-10); else strcpy(suffix_10,"");
	if(len>7)strcpy(suffix_7 , root+len-7); else strcpy(suffix_7,"");
	if(len>6)strcpy(suffix_6 , root+len-6); else strcpy(suffix_6,"");
	if(len>5)strcpy(suffix_5 , root+len-5); else strcpy(suffix_5,"");
	if(len>4)strcpy(suffix_4 , root+len-4); else strcpy(suffix_4,"");
	if(len>3)strcpy(suffix_3 , root+len-3); else strcpy(suffix_3,"");	
	if(len>2)strcpy(suffix_2 , root+len-2); else strcpy(suffix_2,"");
	
	        //sprintf(logmsg, "NAGARAJ INFO: Entering derived_adj_noun_heuristics"); PRINT_LOG(log_file,logmsg);

	derived_root = 0;
	ans_root[0] = '\0';

		    FILE *fp;
			char buff[1000];
			int size_of_file=0,j,i;
			char words[1000][200];
			char wrd[15][50];
	char adj_file[BigArray];
	strcpy(adj_file,getenv("setu"));
	strcat(adj_file, "/morph/data_bin/sl/morph/tel/derivation/derived_adj_noun.p");
	//buff[0]='\0';
	//words[0][0]="\0";
	//wrd[0][0]="\0";
		//fp=fopen("derivation/derived_adj_noun.p","r");
		//fp=fopen("/home/guest/oldmorph/data_bin/sl/morph/tel/derivation/derived_adj_noun.p","r");
		//fp=fopen("/home/guest/oldmorph/data_src/sl/morph/tel/pc_data/derivation/derived_adj_noun.p","r");
		//fp=fopen("/var/www/html/morph/telmorph/data_src/sl/morph/tel/pc_data/derivation/derived_adj_noun.p","r");
		//fp=fopen("../../../../data_src/sl/morph/tel/pc_data/derivation/derived_adj_noun.p","r");
		fp=fopen(adj_file,"r");
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
                        //sprintf(logmsg,"The file derived_adj_noun.p cannot be opened\n");
			PRINT_LOG(log_file,logmsg);
                        exit(0);}
			fclose(fp);
		//Nagaraju
		for(j=0;j<size_of_file;j++) { 
		for(i=0;i<3;i++){
		strcpy(wrd[i],"\0");}
		split_arr(words[j],' ',wrd);
		//printf("%s|%s|%s\n",wrd[0],wrd[1],wrd[2]);

	/* comparing vAdEnavAdu with above suffix_10 and paradigm with vAdu
         if not equal then executes  */
	 /* vAdEnavAdu Cases */

	//if((!strcmp(suffix_10,"vAdEnavAdu")) && !strcmp(pdgm,"vAdu")) 
	if((!strcmp(suffix_10,wrd[0])) && (!strcmp(pdgm,wrd[1])) && (ans_root[0] == '\0')) 
	  {
	    root[len-7] = 'u';
	    root[len-6] = '\0';
	    derived_root = 1;
	    /* This function is used to  to find derivational root */
//	    get_derived_rt(root,adj_ni_ar->suffix,sizeof_adj_ni,sizeof(adj_ni_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	    get_derived_rt(root,adj_ni_ar->suffix,sizeof_adj_ni,sizeof(adj_ni_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	    if(ans_root[0] != '\0') 		/* executes when ans_root is not null */
	      {
		if(aux_verb[0] != '\0')		/* executes when aux_verb not null */
		 {
		   strcat(ans_root,"_");
		  // strcat(ans_root,aux_verb);
		  // strcat(ans_root,aux_verb);
		   strcpy(aux_verb,"");
		 }
		//strcat(ans_root,"_adj_ni_vAdu_Ena_vAdu");
		//strcat(aux_verb,"ni_vAdu_Ena_vAdu_adj");
		//strcat(aux_verb,"ni_vAdu_Ena_vAdu");
		//printf("iam hre");
		strcat(aux_verb,wrd[2]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_10=%s|pdgm=%s|aux_verb=%s|",suffix_10,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
		      }
	    else
	      {
		/* This function is used to  to find derivational root */
//		get_derived_rt(root,adj_xi_ar->suffix,sizeof_adj_xi,sizeof(adj_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
		get_derived_rt(root,adj_xi_ar->suffix,sizeof_adj_xi,sizeof(adj_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	        if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
		 {
		   if(aux_verb[0] != '\0')	/* executes when aux_verb not null */
		     { 
			strcat(ans_root,"_");
			strcat(ans_root,aux_verb);
		        strcpy(aux_verb,"");
		     }
		   //strcat(ans_root,"_adj_vAdu_Ena_vAdu");
		   //strcat(aux_verb,"vAdu_Ena_vAdu_adj");
		   //strcat(aux_verb,"vAdu_Ena_vAdu");
		   strcat(aux_verb,wrd[3]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_10=%s|pdgm=%s|aux_verb=%s|",suffix_10,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
		 }
	      }
	    strcpy(root,tmp_root);
	  }
		/* compares suffix_10 with vArEnavAru Cases  and pdgm with vAru and executes
          when both cases are not equal */
	//if((!strcmp(suffix_10,"vArEnavAru")) && !strcmp(pdgm,"vAru")) 
	if((!strcmp(suffix_10,wrd[0])) && (!strcmp(pdgm,wrd[1])) && (ans_root[0] == '\0')) 
	  {
	    root[len-7] = 'u';
	    root[len-6] = '\0';
	    derived_root = 1;
	    /* This function is used to  to find derivational root */
//	    get_derived_rt(root,adj_ni_ar->suffix,sizeof_adj_ni,sizeof(adj_ni_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	    get_derived_rt(root,adj_ni_ar->suffix,sizeof_adj_ni,sizeof(adj_ni_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	    if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
	     {
	       if(aux_verb[0] != '\0') 	/* executes when aux_verb not null */
		{
		  strcat(ans_root,"_");
		  strcat(ans_root,aux_verb);
		  strcpy(aux_verb,"");
		}
	       //strcat(ans_root,"_adj_ni_vAru_Ena_vAru");
	       //strcat(aux_verb,"ni_vAru_Ena_vAru_adj");
	       //strcat(aux_verb,"ni_vAru_Ena_vAru");
	       strcat(aux_verb,wrd[2]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_10=%s|pdgm=%s|aux_verb=%s|",suffix_10,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
	     }
	    else
	     {
		/* This function is used to  to find derivational root */
//		get_derived_rt(root,adj_xi_ar->suffix,sizeof_adj_xi,sizeof(adj_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
		get_derived_rt(root,adj_xi_ar->suffix,sizeof_adj_xi,sizeof(adj_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	        if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
		 {
		   if(aux_verb[0] != '\0')	/* executes when aux_verb not null */
		    {
		      strcat(ans_root,"_"); 
		      strcat(ans_root,aux_verb);
		      strcpy(aux_verb,"");
		    }
		  // strcat(ans_root,"_adj_vAru_Ena_vAru");
		   //strcat(aux_verb,"vAru_Ena_vAru_adj");
		   //strcat(aux_verb,"vAru_Ena_vAru");
		   strcat(aux_verb,wrd[3]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_10=%s|pdgm=%s|aux_verb=%s|",suffix_10,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
	
		 }
	     }
	    strcpy(root,tmp_root);
	  }	
	/* compares suffix_7 with xEnaxi  and pdgm with axi and executes only when both
	 Cases are not  equal respectively  */
	//if((!strcmp(suffix_7,"xEnaaxi")) && !strcmp(pdgm,"axi")) 
	if((!strcmp(suffix_7,wrd[0])) && !strcmp(pdgm,wrd[1]) && (ans_root[0] == '\0')) 
	 {
	   root[len-6] = 'i';
	   root[len-5] = '\0';
	   derived_root = 1;
	   /* This function is used to  to find derivational root */
//	   get_derived_rt(root,adj_ni_ar->suffix,sizeof_adj_ni,sizeof(adj_ni_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	   get_derived_rt(root,adj_ni_ar->suffix,sizeof_adj_ni,sizeof(adj_ni_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	   if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
	     {
		if(aux_verb[0] != '\0')		/* executes when aux_verb not null */
		 {
		   strcat(ans_root,"_"); 
		   strcat(ans_root,aux_verb);
		   strcpy(aux_verb,"");
		 }
	        //strcat(ans_root,"_adj_ni_xi_Ena_xi");
	        //strcat(aux_verb,"ni_xi_Ena_xi_adj");
	        //strcat(aux_verb,"ni_xi_Ena_xi");
	        strcat(aux_verb,wrd[2]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_7=%s|pdgm=%s|aux_verb=%s|",suffix_7,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
	     }
	   else
	     {
		/* This function is used to  to find derivational root */
//	      get_derived_rt(root,adj_xi_ar->suffix,sizeof_adj_xi,sizeof(adj_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	      get_derived_rt(root,adj_xi_ar->suffix,sizeof_adj_xi,sizeof(adj_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	      if(ans_root[0] != '\0')	/* executes when ans_root is not null */
	       {
		if(aux_verb[0] != '\0') 	/* executes when aux_verb not null */
		 {
		   strcat(ans_root,"_"); 
		   strcat(ans_root,aux_verb);
		   strcpy(aux_verb,"");
		 }
	//	strcat(ans_root,"_adj_xi_Ena_xi");
		//strcat(aux_verb,"xi_Ena_xi_adj");
		//strcat(aux_verb,"xi_Ena_xi");
		strcat(aux_verb,wrd[3]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_7=%s|pdgm=%s|aux_verb=%s|",suffix_7,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
	
	       }
	     }
	    strcpy(root,tmp_root);
	  }
		
	//if((!strcmp(suffix_6,"xEnaxi")) && !strcmp(pdgm,"axi")) 
	if((!strcmp(suffix_6,wrd[0])) && !strcmp(pdgm,wrd[1]) && (ans_root[0] == '\0')) 
	 {
	   root[len-5] = 'i';
	   root[len-4] = '\0';
	   derived_root = 1;
	   /* This function is used to  to find derivational root */
//	   get_derived_rt(root,adj_ni_ar->suffix,sizeof_adj_ni,sizeof(adj_ni_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	   get_derived_rt(root,adj_ni_ar->suffix,sizeof_adj_ni,sizeof(adj_ni_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	   if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
	    {
	      if(aux_verb[0] != '\0')	/* executes when aux_verb not null */
		{
		 strcat(ans_root,"_"); 
		 strcat(ans_root,aux_verb);
		 strcpy(aux_verb,"");
		}
	     // strcat(ans_root,"_adj_ni_xi_Ena_xi");
	      //strcat(aux_verb,"ni_xi_Ena_xi_adj");
	      //strcat(aux_verb,"ni_xi_Ena_xi");
	      strcat(aux_verb,wrd[2]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_6=%s|pdgm=%s|aux_verb=%s|",suffix_6,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
	    }
	   else
	    {
		/* This function is used to  to find derivational root */
//	      get_derived_rt(root,adj_xi_ar->suffix,sizeof_adj_xi,sizeof(adj_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	      get_derived_rt(root,adj_xi_ar->suffix,sizeof_adj_xi,sizeof(adj_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	      if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
	       {
	         if(aux_verb[0] != '\0')	/* executes when aux_verb not null */
		  {
		    strcat(ans_root,"_"); 
		    strcat(ans_root,aux_verb);
		    strcpy(aux_verb,"");
		  }
	//	 strcat(ans_root,"_adj_xi_Ena_xi");
		 //strcat(aux_verb,"xi_Ena_xi_adj");
		 //strcat(aux_verb,"xi_Ena_xi");
		 strcat(aux_verb,wrd[3]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_6=%s|pdgm=%s|aux_verb=%s|",suffix_6,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
	       }
	    }
	   strcpy(root,tmp_root);
	 }
	/* compares suffix_7 with EnvAru and pdgm with vAru ,executes only when both conditions
          are not same respectively */
	//if((!strcmp(suffix_7,"EnavAru")) && !strcmp(pdgm,"vAru") && ( ans_root[0] == '\0')) 
	if((!strcmp(suffix_7,wrd[0])) && !strcmp(pdgm,wrd[1]) && ( ans_root[0] == '\0')) 
	 {
	  derived_root = 1;
	   /* This function is used to  to find derivational root */
//	  get_derived_rt(root,adj_nEna_ar->suffix,sizeof_adj_nEna,sizeof(adj_nEna_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	  get_derived_rt(root,adj_nEna_ar->suffix,sizeof_adj_nEna,sizeof(adj_nEna_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	  if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
	   {
	     if(aux_verb[0] != '\0')	/* executes when aux_verb not null */
	      {
		strcat(ans_root,"_");
		strcat(ans_root,aux_verb);
		strcpy(aux_verb,"");
	      }
	    // strcat(ans_root,"_adj_nEna_vAru");
	     //strcat(aux_verb,"nEna_vAru_adj");
	     //strcat(aux_verb,"nEna_vAru");
	     strcat(aux_verb,wrd[2]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_7=%s|pdgm=%s|aux_verb=%s|",suffix_7,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
	   }
	  strcpy(root,tmp_root);
	 }
	/*compares suffix_7 with EnvAdu and pdgm with vAdu ,executes only when both conditions
           are not same respectively  */
	//if((!strcmp(suffix_7,"EnavAdu")) && !strcmp(pdgm,"vAdu") && ( ans_root[0] == '\0')) 
	if((!strcmp(suffix_7,wrd[0])) && !strcmp(pdgm,wrd[1]) && ( ans_root[0] == '\0')) 
	 {
	   derived_root = 1;
	     /* This function is used to  to find derivational root */
//	   get_derived_rt(root,adj_nEna_ar->suffix,sizeof_adj_nEna,sizeof(adj_nEna_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	   get_derived_rt(root,adj_nEna_ar->suffix,sizeof_adj_nEna,sizeof(adj_nEna_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	   if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
	    {
	      if(aux_verb[0] != '\0') 	/* executes when aux_verb not null */
	       {
		 strcat(ans_root,"_"); 
		 strcat(ans_root,aux_verb);
		 strcpy(aux_verb,"");
	       }
	     // strcat(ans_root,"_adj_nEna_vAdu");
	      //strcat(aux_verb,"nEna_vAdu_adj");
	      //strcat(aux_verb,"nEna_vAdu");
	      strcat(aux_verb,wrd[2]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_7=%s|pdgm=%s|aux_verb=%s|",suffix_7,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
	    }
	   strcpy(root,tmp_root);
	 }
	/* compares suffix_6 with Enaaxi cases  and pdgm with axi ,executes only when both
        conditions are not same respectively  */
	//if((!strcmp(suffix_6,"Enaaxi")) && !strcmp(pdgm,"axi") && ( ans_root[0] == '\0')) 
	if((!strcmp(suffix_6,wrd[0])) && !strcmp(pdgm,wrd[1]) && ( ans_root[0] == '\0')) 
	 {
	   root[len-3] = 'x';
	   root[len-2] = 'i';
	   root[len-1] = '\0';
	   derived_root = 1;
		/* This function is used to  to find derivational root */
//	   get_derived_rt(root,adj_nEna_ar->suffix,sizeof_adj_nEna,sizeof(adj_nEna_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	   get_derived_rt(root,adj_nEna_ar->suffix,sizeof_adj_nEna,sizeof(adj_nEna_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	   if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
	    {
	     if(aux_verb[0] != '\0') 	/* executes when aux_verb not null */
	      {
		strcat(ans_root,"_"); 
		strcat(ans_root,aux_verb);
	        strcpy(aux_verb,"");
	      }
//	     strcat(ans_root,"_adj_nEna_xi");
	     //strcat(aux_verb,"nEna_xi_adj");
	     //strcat(aux_verb,"nEna_xi");
	     strcat(aux_verb,wrd[2]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_6=%s|pdgm=%s|aux_verb=%s|",suffix_6,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
	
	    }
	   strcpy(root,tmp_root);
	 }
		/* compares suffix_5 with Enaxi cases  and pdgm with axi ,executes only when both
        conditions are not same respectively  */
	//if((!strcmp(suffix_5,"Enaxi")) && !strcmp(pdgm,"axi") && ( ans_root[0] == '\0')) 
	if((!strcmp(suffix_5,wrd[0])) && !strcmp(pdgm,wrd[1]) && ( ans_root[0] == '\0')) 
	 {
	  derived_root = 1;
		/* This function is used to  to find derivational root */
//	  get_derived_rt(root,adj_nEna_ar->suffix,sizeof_adj_nEna,sizeof(adj_nEna_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	  get_derived_rt(root,adj_nEna_ar->suffix,sizeof_adj_nEna,sizeof(adj_nEna_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	  if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
	   {	
	     if(aux_verb[0] != '\0') 	/* executes when aux_verb not null */
	      {
	        strcat(ans_root,"_"); 
		strcat(ans_root,aux_verb);
		strcpy(aux_verb,"");
	      }
	   //  strcat(ans_root,"_adj_nEna_xi");
	     //strcat(aux_verb,"nEna_xi_adj");
	     //strcat(aux_verb,"nEna_xi");
	     strcat(aux_verb,wrd[2]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_5=%s|pdgm=%s|aux_verb=%s|",suffix_5,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
	
	   }
	 strcpy(root,tmp_root);
	 }
	/* compares suffix_7 with pAtixi cases  and pdgm with axi ,executes only when both
        conditions are not same respectively  */
	//if((!strcmp(suffix_7,"pAtiaxi")) && !strcmp(pdgm,"axi") && ( ans_root[0] == '\0')) 
	if((!strcmp(suffix_7,wrd[0])) && !strcmp(pdgm,wrd[1]) && ( ans_root[0] == '\0')) 
	 {
	   root[len-3] = 'x';
	   root[len-2] = 'i';
	   root[len-1] = '\0';
	   derived_root = 1;
		/* This function is used to  to find derivational root */
//	   get_derived_rt(root,adj_pAti_ar->suffix,sizeof_adj_pAti,sizeof(adj_pAti_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	   get_derived_rt(root,adj_pAti_ar->suffix,sizeof_adj_pAti,sizeof(adj_pAti_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	   if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
	    {
	      if(aux_verb[0] != '\0') 	/* executes when aux_verb not null */
		{
		  strcat(ans_root,"_"); 
		  strcat(ans_root,aux_verb);
		  strcpy(aux_verb,"");
		}
	    //  strcat(ans_root,"_adj_pAti_xi");
	      //strcat(aux_verb,"pAti_xi_adj");
	      //strcat(aux_verb,"pAti_xi");
	      strcat(aux_verb,wrd[2]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_7=%s|pdgm=%s|aux_verb=%s|",suffix_7,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
	    }
	   strcpy(root,tmp_root);
	 }
	 /* compares suffix_6 with pAtixi csases and pdgm with axi ,executes only when both
         conditions   are not same respectively  */
	//if((!strcmp(suffix_6,"pAtixi")) && !strcmp(pdgm,"axi") && ( ans_root[0] == '\0')) 
	if((!strcmp(suffix_6,wrd[0])) && !strcmp(pdgm,wrd[1]) && ( ans_root[0] == '\0')) 
	 {
	   derived_root = 1;
		/* This function is used to  to find derivational root */
//	   get_derived_rt(root,adj_pAti_ar->suffix,sizeof_adj_pAti,sizeof(adj_pAti_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	   get_derived_rt(root,adj_pAti_ar->suffix,sizeof_adj_pAti,sizeof(adj_pAti_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	   if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
	    {
	     if(aux_verb[0] != '\0')	/* executes when aux_verb not null */
	      {
		strcat(ans_root,"_"); 
		strcat(ans_root,aux_verb);
		strcpy(aux_verb,"");
	      }
	//     strcat(ans_root,"_adj_pAti_xi");
	     //strcat(aux_verb,"pAti_xi_adj");
	     //strcat(aux_verb,"pAti_xi");
	     strcat(aux_verb,wrd[2]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_6=%s|pdgm=%s|aux_verb=%s|",suffix_6,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
		    }
	   strcpy(root,tmp_root);
	 }
	/*compares suffix_4 with vAdu and pdgm with vAdu , and ans_root equal to null
       executes only when all conditions  are satisfied respectively  */
	//if((!strcmp(suffix_4,"vAdu")) && !strcmp(pdgm,"vAdu") && ( ans_root[0] == '\0')) 
	if((!strcmp(suffix_4,wrd[0])) && !strcmp(pdgm,wrd[1]) && ( ans_root[0] == '\0')) 
	 {
	   derived_root = 1;
		/* This function is used to  to find derivational root */
//	   get_derived_rt(root,adj_ni_ar->suffix,sizeof_adj_ni,sizeof(adj_ni_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	   get_derived_rt(root,adj_ni_ar->suffix,sizeof_adj_ni,sizeof(adj_ni_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	   if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
	    {
	      if(aux_verb[0] != '\0') 	/* executes when aux_verb not null */
	       {
		 strcat(ans_root,"_"); 
		 strcat(ans_root,aux_verb);
		 strcpy(aux_verb,"");
	       }
	    //  strcat(ans_root,"_adj_ni_vAdu");
	      //strcat(aux_verb,"ni_vAdu_adj");
	      //strcat(aux_verb,"ni_vAdu");
	      strcat(aux_verb,wrd[2]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_4=%s|pdgm=%s|aux_verb=%s|",suffix_4,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
		    }
	  else
	   {
		/* This function is used to  to find derivational root */
//	     get_derived_rt(root,adj_xi_ar->suffix,sizeof_adj_xi,sizeof(adj_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	     get_derived_rt(root,adj_xi_ar->suffix,sizeof_adj_xi,sizeof(adj_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	     if(ans_root[0] != '\0') /* executes when ans_root is not null */
	      {
		if(aux_verb[0] != '\0') 	/* executes when aux_verb not null */
		 {
		   strcat(ans_root,"_"); 
		   strcat(ans_root,aux_verb);
		   strcpy(aux_verb,"");
		 }
//		strcat(ans_root,"_adj_vAdu");
		//strcat(aux_verb,"vAdu_adj");
		//strcat(aux_verb,"vAdu");
		strcat(aux_verb,wrd[3]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_4=%s|pdgm=%s|aux_verb=%s|",suffix_4,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
	      }
	   }
	  strcpy(root,tmp_root);
	 }
	/*compares suffix_4 with vAru and pdgm with vAru ,executes only when both conditions         are not same respectively  */
	//if((!strcmp(suffix_4,"vAru")) && !strcmp(pdgm,"vAru") && ( ans_root[0] == '\0')) 
	if((!strcmp(suffix_4,wrd[0])) && !strcmp(pdgm,wrd[1]) && ( ans_root[0] == '\0')) 
	  {
	   derived_root = 1;
		/* This function is used to  to find derivational root */
//	   get_derived_rt(root,adj_ni_ar->suffix,sizeof_adj_ni,sizeof(adj_ni_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	   get_derived_rt(root,adj_ni_ar->suffix,sizeof_adj_ni,sizeof(adj_ni_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	   if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
	    {
	      if(aux_verb[0] != '\0') 	/* executes when aux_verb not null */
	       {
		 strcat(ans_root,"_"); 
		 strcat(ans_root,aux_verb);
		 strcpy(aux_verb,"");
	       }
	      //strcat(ans_root,"_ni_vAru_adj");
	      //strcat(aux_verb,"ni_vAru_adj");
	      //strcat(aux_verb,"ni_vAru");
	      strcat(aux_verb,wrd[2]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_4=%s|pdgm=%s|aux_verb=%s|",suffix_4,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
	    }
	   else
	    {
		/* This function is used to  to find derivational root */
//	      get_derived_rt(root,adj_xi_ar->suffix,sizeof_adj_xi,sizeof(adj_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	      get_derived_rt(root,adj_xi_ar->suffix,sizeof_adj_xi,sizeof(adj_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	      if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
		{
		  if(aux_verb[0] != '\0') 	/* executes when aux_verb not null */
		   { 
		     strcat(ans_root,"_");
		     strcat(ans_root,aux_verb);
		     strcpy(aux_verb,"");
		   }
		// strcat(ans_root,"_vAru_adj");
		 //strcat(aux_verb,"vAru_adj");
		 //strcat(aux_verb,"vAru");
		 strcat(aux_verb,wrd[3]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_4=%s|pdgm=%s|aux_verb=%s|",suffix_4,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);
		}
	    }
	  strcpy(root,tmp_root);
	 }
	/*compares suffix_3 with axi and pdgm with axi and ans_root equal to null
        executes only when all conditions are satisfied   */
	//if((!strcmp(suffix_3,"axi")) && !strcmp(pdgm,"axi") && ( ans_root[0] == '\0')) 
	if((!strcmp(suffix_3,wrd[0])) && !strcmp(pdgm,wrd[1]) && ( ans_root[0] == '\0')) 
	 {
	  root[len-3] = 'x';
	  root[len-2] = 'i';
	  root[len-1] = '\0';
	  derived_root = 1;
		/* This function is used to  to find derivational root */
//	  get_derived_rt(root,adj_ni_ar->suffix,sizeof_adj_ni,sizeof(adj_ni_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	  get_derived_rt(root,adj_ni_ar->suffix,sizeof_adj_ni,sizeof(adj_ni_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	  if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
	   {
	    if(aux_verb[0] != '\0')
	      {
		strcat(ans_root,"_");
		strcat(ans_root,aux_verb);
		strcpy(aux_verb,"");
	      }
	    //strcat(ans_root,"_ni_xi");
	    //strcat(aux_verb,"ni_xi_adj");
	    //strcat(aux_verb,"ni_xi");
	    //printf("iam here");
	    strcat(aux_verb,wrd[2]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_3=%s|pdgm=%s|aux_verb=%s|",suffix_3,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);	
	   }
	  else
	   {
		/* This function is used to  to find derivational root */
//	     get_derived_rt(root,adj_xi_ar->suffix,sizeof_adj_xi,sizeof(adj_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	     get_derived_rt(root,adj_xi_ar->suffix,sizeof_adj_xi,sizeof(adj_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	     if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
	      {
	        if(aux_verb[0] != '\0')	/* executes when aux_verb not null */
		 {
		   strcat(ans_root,"_"); 
		   strcat(ans_root,aux_verb);
		   strcpy(aux_verb,"");
		 }
	//	strcat(ans_root,"_xi");
		//strcat(aux_verb,"xi_adj");
		//strcat(aux_verb,"xi");
		strcat(aux_verb,wrd[3]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_3=%s|pdgm=%s|aux_verb=%s|",suffix_3,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);	
	
	      }
	   }
	  strcpy(root,tmp_root);
	 }
	 /*compares suffix_2 with xi and pdgm with axi and ans_root equal to null,executes
           when all conditions are satisfied  respectively  */
	//if((!strcmp(suffix_2,"xi")) && !strcmp(pdgm,"axi") && ( ans_root[0] == '\0')) 
	if((!strcmp(suffix_2,wrd[0])) && !strcmp(pdgm,wrd[1]) && ( ans_root[0] == '\0')) 
	 {
	   derived_root = 1;
		/* This function is used to  to find derivational root */
//	   get_derived_rt(root,adj_ni_ar->suffix,sizeof_adj_ni,sizeof(adj_ni_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	   get_derived_rt(root,adj_ni_ar->suffix,sizeof_adj_ni,sizeof(adj_ni_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	   if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
	    {
	      if(aux_verb[0] != '\0') 	/* executes when aux_verb not null */
	       {
		 strcat(ans_root,"_"); 
		 strcat(ans_root,aux_verb);
		 strcpy(aux_verb,"");
	       }
	     // strcat(ans_root,"_ni_xi");
	      //strcat(aux_verb,"ni_xi_adj");
	      //strcat(aux_verb,"ni_xi");
	     //printf("iam here");
	      strcat(aux_verb,wrd[2]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_2=%s|pdgm=%s|aux_verb=%s|",suffix_2,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);	
	    }
	   else
	    {
		/* This function is used to  to find derivational root */
//	      get_derived_rt(root,adj_xi_ar->suffix,sizeof_adj_xi,sizeof(adj_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"noun",ans_root,aux_verb,offset_aux_str);
	      get_derived_rt(root,adj_xi_ar->suffix,sizeof_adj_xi,sizeof(adj_xi_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	      if(ans_root[0] != '\0') 	/* executes when ans_root is not null */
		{
	          if(aux_verb[0] != '\0')	/* executes when aux_verb not null */
		   {
		     strcat(ans_root,"_");
		     strcat(ans_root,aux_verb);
		     strcpy(aux_verb,"");
		   }
		//  strcat(ans_root,"_xi");
		//  strcat(aux_verb,"xi_adj");
		  //strcat(aux_verb,"xi");
		  strcat(aux_verb,wrd[3]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_2=%s|pdgm=%s|aux_verb=%s|",suffix_2,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);		
	        }
	    }
	   strcpy(root,tmp_root);
	 }
	/*compares suffix_10 with etatuvaMti and pdgm with maMci ,and ans_root equal to null
          executes when all conditions are satisfied respectively  */
	//if((!strcmp(suffix_10,"etatuvaMti")) && !strcmp(pdgm,"maMci") && ( ans_root[0] == '\0')) 
	if((!strcmp(suffix_10,wrd[0])) && !strcmp(pdgm,wrd[1]) && ( ans_root[0] == '\0')) 
	 {
	   derived_root = 1;                                
	   len = strlen(root);
	   root[len-9] = '\0';
	   /* This function is used to  to find derivational root */
//	   get_derived_rt(root,e_suff_info_ar->suffix,sizeof_e_suff,sizeof(e_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,"verb",ans_root,aux_verb,offset_aux_str);
	   get_derived_rt(root,e_suff_info_ar->suffix,sizeof_e_suff,sizeof(e_suff_info_ar[0]),strcmp,DBM_FLAG,db_lex,"",ans_root,aux_verb,offset_aux_str);
	   if(ans_root[0] != '\0') /* executes when ans_root is not null */                      
	    {                                      
	      if(aux_verb[0] != '\0') 	/* executes when aux_verb not null */
		{
		  strcat(ans_root,"_"); 
		  strcat(ans_root,aux_verb);
		  strcpy(aux_verb,"");
		}
	     // strcat(ans_root,"_e_tatuvaMti");
	     // strcat(aux_verb,"e_tatuvaMti_adj");
	      //strcat(aux_verb,"e_tatuvaMti");
	      strcat(aux_verb,wrd[2]);
	        //sprintf(logmsg, "NAGARAJ INFO:suffix_10=%s|pdgm=%s|aux_verb=%s|",suffix_10,pdgm,aux_verb); PRINT_LOG(log_file,logmsg);		
	    }
	 }
}//to remove hardcoded from adj_noun_heuristics by Nagaraju
	if(DEBUG && derived_root)
	 {
	   //sprintf(logmsg,"%s\n",ans_root);PRINT_LOG(logmsg,log_file);
	   //sprintf(logmsg,"%d\n",derived_root);PRINT_LOG(logmsg,log_file);
	 }
	//sprintf(logmsg, "NAGARAJ INFO:Exiting derived_adj_noun_heuristics"); PRINT_LOG(log_file,logmsg);	
	
    }
