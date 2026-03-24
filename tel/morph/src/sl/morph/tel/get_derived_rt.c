/**
 * FILE Name :get_derived_rt.c
*/


/** get_derived_rt
 * This function is used to  to find derivational root
 * It takes arguments: key of char type ,base of char type ,nel of int type
 * width of int type and compar is function with integer return type
 * DBM_FLAG of int type ,db_lex of GDBM file type,cat of char type ,ans_root of char type,
 * aux_verb of char type ,offset_aux_str of type
 * Return : void
 */

/* HEADER FILES */

#include <gdbm.h>

#include <string.h>
#include <stdio.h>
#include "./headers/struct.h"
#include "./common/analyser/morph_logger.h"


extern FILE *log_file;
//extern FILE *log_messg;
extern char *logmsg;
#define FUNCTION "get_derived_rt()"


extern struct lex_info lex_ar[];	/* structure contains lexical info of word,paradigm,
                                    category,priority */
extern int sizeof_lex;			/* size of lex */
extern int DEBUG;			/* checks for the existance of root */

/**
 * Prototypes of the functions in this file with a file scope
*/
extern char * my_blk_bsearch();
extern void get_suff();
extern void dict_lookup();
extern void cp_to_struct();
extern void cp_to_struct_chk_pdgm();
extern void match_in_hypothetical_dict();
extern void vwl_harmony();

void get_derived_rt(word,base,nel,width,compar,DBM_FLAG,db_lex,cat,ans_root,aux_verb,offset_aux_str)

char word[SUFFWORDSIZE],*base;	/* input word, base pointer points to the base
                                        address of the suffix table */
int nel,width,DBM_FLAG;		/* table size */
int (* compar)();
GDBM_FILE db_lex;		/* GNU database manager includes dbm and ndb
                                     compatability and db_lex is used for opening lexical file */
char ans_root[SUFFWORDSIZE],cat[Arraysize];  /* root output ,category */
char aux_verb[SUFFWORDSIZE];			/* auxilary verb */
char offset_aux_str[SUFFWORDSIZE];		/* offset */
{
	char *program_name="get_derived_rt.c";
        PRINT_LOG(log_file," This function is used to  to find derivational root");
      int len,loop1,pos1,loop2;            /* length of the word , pos1 is position of word  */
      char suff[SUFFWORDSIZE];             /* suffix */
      /* proposed rootword , vowel harmony of word */
      char proposed_root[SUFFWORDSIZE],vwl_hrmn_wrd[SUFFWORDSIZE];
      char aux_v[SUFFWORDSIZE];                    /* auxilary verb */

      struct suff_info *tag_suff;         /* structure containing suffix information taking
                                               tag_suff as an object */
      struct lex_info ans_table[SmallArray];   /* structure containing lexical information taking                                                  ans_table as an object */
      char ans_ar[SmallArray][LargeArray];

	ans_root[0] = '\0';
	aux_v[0] = '\0';
	len = strlen(word);		/* length of the word */
	for(loop1=len;loop1>=0;loop1--)  /* reading length from last */
	{
	  if(loop1==len) 		 /* if len is equal to loop1 then suff is null */
	    suff[0] = '\0';
	  else 		
	    /* This function concatenates the root word with the suffix */
	    get_suff(word,suff,loop1);
		/* This function returns the ptr to the location of the key in the table,
            if it is present  else returns a null  */
	  tag_suff = (struct suff_info *) my_blk_bsearch(suff,base,nel,width,compar);
	  if(tag_suff != '\0')			
	   {
	      while(!strcmp(tag_suff->suffix,suff))	/* executes when suffix is not
                                                       equal guessed suff */
		{
		  strncpy(proposed_root,word,loop1);
		  proposed_root[loop1]='\0';
		  if(DEBUG)
		   sprintf (logmsg,"get_derived_rt1: %s\n",proposed_root);PRINT_LOG(log_file,logmsg);
		   strcat(proposed_root,tag_suff->add);
		  /* This function checks the word in the dictionary */
		   dict_lookup(proposed_root,DBM_FLAG,db_lex,lex_ar->word,sizeof_lex,sizeof(lex_ar[0]),strcmp,ans_ar);
		   pos1 = 0;
		   /* This function copies data ie Priority , pdgm,cat,word to the structure */
		   cp_to_struct(ans_ar,ans_table,&pos1);
		//sprintf(logmsg,"ans_table.cat=%s|",ans_table[0].cat);
		sprintf(logmsg,"cat=%s|ans_table.cat=%s|",cat,ans_table[0].cat);
		PRINT_LOG(log_file,logmsg);
		//strcpy(cat,ans_table[0].cat);
		   loop2=0;	
		   while(ans_table[loop2].word[0] !='\0')
		    {
			/* compares word with the proposed root and paradigm
                         to the tagg-suff paradigm */
		      if(!strcmp(ans_table[loop2].word,proposed_root) && !strcmp(ans_table[loop2].pdgm,tag_suff->pdgm))
			 {
			  strcpy(ans_root,proposed_root);
			  /* copies the auxilary verb to the offset that we got from the
                               my_blk_bsearch function */
			  name_comp_offset(tag_suff->offset,aux_v);
			  sprintf(logmsg,"aux verb value is |%s| ",aux_v);
			  PRINT_LOG(log_file,"value of aux verb is ");
			  strcpy(offset_aux_str,aux_v);
			  if((aux_verb[0] != '\0') && (aux_v[0] != '\0'))
			    {
			      strcat(aux_v,"_");
			      strcat(aux_v,aux_verb);
			      strcpy(aux_verb,aux_v);
			    }
			  if((aux_verb[0] == '\0') && (aux_v[0] != '\0'))
			    {
			      strcpy(aux_verb,aux_v);
			    }
			  goto LAST;
			 }
		        loop2++;
		    }  
		if(index(tag_suff->pdgm,'?')) /* if it is a vwl_hrmn_pdgm modify the guessed root by changing the vowels so as to bring in vowel harmony */
		 {
		   /*vwl_harmony(proposed_root,vwl_hrmn_wrd);*/
		   vwl_harmony(proposed_root,tag_suff->pdgm,vwl_hrmn_wrd);
		  if((vwl_hrmn_wrd[0] != '\0') && strcmp(proposed_root,vwl_hrmn_wrd))
		    {
		      dict_lookup(vwl_hrmn_wrd,DBM_FLAG,db_lex,lex_ar->word,sizeof_lex,sizeof(lex_ar[0]),strcmp,ans_ar);
		      pos1 = 0;
		      cp_to_struct_chk_pdgm(ans_ar,ans_table,&pos1,tag_suff->pdgm);
		      loop2=0;
		      while(ans_table[loop2].word[0] !='\0')
			 {
			   if(!strcmp(ans_table[loop2].word,vwl_hrmn_wrd) && !strcmp(ans_table[loop2].pdgm,tag_suff->pdgm))
			     {
			       strcpy(ans_root,vwl_hrmn_wrd);
			       name_comp_offset(tag_suff->offset,aux_v);
			       strcpy(offset_aux_str,aux_v);
			       if((aux_verb[0] != '\0') && (aux_v[0] != '\0'))
				 {
				   strcat(aux_v,"_");
				   strcat(aux_v,aux_verb);
				   strcpy(aux_verb,aux_v);
				 }
			       if((aux_verb[0] == '\0') && (aux_v[0] != '\0'))
				 {
				   strcpy(aux_verb,aux_v);
				 }
			       goto LAST;
			     }
			   loop2++;
			 }  
		    }
		 strcpy(proposed_root,vwl_hrmn_wrd); 
		/* This is done,since if the rt is still not found, now this vwl_hrm_wrds
			is to be serached in the derived_rt dict */
		 }
	    /* If still answer not found check whether proposed root itself  is a derived root */
	    if(suff[0] != '\0') /* condition added to avoid infinite loop */
		{
		  if(DEBUG)
		    sprintf (logmsg,"get_derived_rt2: %s\n",proposed_root);PRINT_LOG(log_file,logmsg);
		  match_in_hypothetical_dict(proposed_root,tag_suff->pdgm,cat,DBM_FLAG,db_lex,ans_root,aux_v);
		//	printf("%s",ans_root);
		//	printf("%s",aux_v);
		//	printf("%s",cat);
		  if(ans_root[0] != '\0')
		    {
		     /* 127 to 138 were in comments . Do not Know why? It was not analysinig
			pIkipAresipoyAdu, pIkipAreVyyamannA, etc. So removed from comments */
			if((aux_verb[0] != '\0') && (aux_v[0] != '\0'))
			 {
			   strcat(aux_v,"_");
			   strcat(aux_v,aux_verb);
			   strcpy(aux_verb,aux_v);
			 }
			if((aux_verb[0] == '\0') && (aux_v[0] != '\0'))
			  {
			    strcpy(aux_verb,aux_v);
			  }
			name_comp_offset(tag_suff->offset,aux_v);
			strcpy(offset_aux_str,aux_v);
			if(aux_v[0] != '\0')
			  {
			   strcat(aux_verb,"_");
			   strcat(aux_verb,aux_v);
			  }
			 /* 127 to 138 was in comments. removed from comments, for reasons as explained above*/
			goto LAST;
		    }
		}  
	      *tag_suff++;
	      }  
	   }
	}
      LAST:
      if(DEBUG)     /* if root exists */
	sprintf(logmsg,"get_derived_rt3:%s\n",ans_root);PRINT_LOG(log_file,logmsg);
}
