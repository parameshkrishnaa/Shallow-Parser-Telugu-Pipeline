/**
 * File Name : morph_telugu.c
 */

/** Function : fun_morph
 * Description: This function is the main functuon. It extracts suffixes and calls different
 * routines for analysis
 * Input Arguments:morph,fp_pdgm,DBM_FLAG,db_lex,db_suff,ans_ar
 * morph of char array,fp_pdgm filepointer, DBM_FLAG of int type ,db_lex  filepointer of DBM
 * db_suff filepointer of DBM ,ans_ar object of structure ans_struct
 * Return: void
 */

/* HEADER FILES */
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <gdbm.h>
#include <stdlib.h>
#include "./headers/struct1.h"
#include "./headers/struct.h"
#include "./common/analyser/morph_logger.h"


extern FILE *log_file;
extern char *program_name;
extern char *logmsg;
#define FUNCTION "fun_morph()"



/* if word is present FINDONCE will be 1 */
extern int FINDONCE;                

/* default paradigm */
extern int DEFAULT_PARADIGM;        

/*considers only guessed paradigm even pdgm is there */
extern int ALWAYS_DEFAULT_PARADIGM; 

/* check for dictionary if true then it is present */
extern int DBM_FLAG;                

/* word number */
extern int WORD_NUM;                
extern int DEBUG;                   

/* checkf for dictionary existance */
extern int INFLTNL;

/* size of lexical value */
extern int sizeof_lex;              

/* size of proper noun lex */
extern int sizeof_prop_noun_lex;    

/* size of suffix to be added */
extern int sizeof_suff_add;         
extern int direct_ans_flag;

/* object of structure lex_info where lex_info contains i
 * info of root,pdgm,cat etc 
 */
extern struct lex_info lex_ar[];   

/* proper noun object of structure lex_info , 
 * where lex_info contains info of root,pdgm,cat etc 
 */
extern struct lex_info prop_noun_lex_ar[];

/* object of suff_add_info structure, where it contains suffix,add,
 * pdgm[WORD_SIZE], category, offset */
extern struct suff_add_info suff_add_info_ar[];

/**
 * Prototypes of the functions in this file with a file scope
 */
extern void get_paradigm();
extern void get_pdgm_info();
extern void get_suff();
//extern char *delete_yv();
extern char *dbm_suff_tab_lookup();
extern void * my_blk_bsearch();
extern void prop_noun_dict_lookup();
extern void cp_to_struct();
extern void cp_to_struct_chk_pdgm();
extern void dict_lookup();
extern void vwl_harmony();
extern void verify_root();
extern void print_default_ans();

//void fun_morph(morph,fp_pdgm,DBM_FLAG,db_lex,db_suff,ans_ar,no_of_ans)
void fun_morph(morph,category,fp_pdgm,DBM_FLAG,db_lex,db_suff,ans_ar,no_of_ans)

	/* file pointer for paradigm file */
	FILE   *fp_pdgm;              

	/* GNU database manager includes dbm and ndb 
	 * compatability and db is used for opening file 
	 * */
	GDBM_FILE db_lex,*db_suff;    

	/* morph input word */
	char morph[Morphsize];  

	/* checks for existance of the word */
	int DBM_FLAG;           

	/* ans_struct structure,it contains of root, 
	 * offset,aux_verb,pdgm 
	 * */
	struct ans_struct ans_ar[Arraysize];

	int* no_of_ans;

	char category[BigArray];
{
	sprintf(logmsg, "INFO:In fun_morph"); PRINT_LOG(log_file,logmsg);

	/* morph size, isnumeral */
	int morph_size,ISNUM;

	/* loop1 reading characters of word */
	int loop1,loop2,loop3,pos,pos1,offset,loop;
	int num;

	/* The  fseek() function sets the file position 
	 * indicator for the stream pointed to by stream.  
	 */
	int fseek_ptr; 

	/* suffix of word, guessed root, temporary suffix */
	char suff[SUFFWORDSIZE],guessed_root[SUFFWORDSIZE],tmp_suff[SUFFWORDSIZE];

	/* paradigm , category, temporary paradigm */
	//char pdgm[WORD_SIZE],category[CATEGORYWORDSIZE],my_pdgm[WORD_SIZE];
	char pdgm[WORD_SIZE],my_pdgm[WORD_SIZE];

	/* ans_ar1 is lexical morph word */
	char ans_ar1[SmallArray][LargeArray];

	/* vowel harmony of word, temporary word */
	char vwl_hrmn_wrd[SUFFWORDSIZE],tmp_wrd[SUFFWORDSIZE];

	/* gives lexical info of word it contains info of
	 * word,paradigm,category,priority
	 */
	struct lex_info  ans_table[SmallArray]; 

	/* tag suffix */
	char *tag_suff;

	/* contains suffix info ie suff, address,no. of entries and integer pointer */
	struct suff_add_info tag_suff_ar[Arraysize],dummy;

	/* intial size of suffix */
	int sizeof_dummy;

	/**
	 * Prototypes of the functions in this file with a file scope
	 */
	int AVY_srch();

	/* Intialising pos and direct_ans_flag to zero */
	pos = 0;
	direct_ans_flag = 0;
	/* finding size of dummy and storing in sizeof_dummy */
	sizeof_dummy = sizeof(dummy);	

	/* calling routine for finding if given word is avy */
	for(loop1=0;loop1<20;loop1++) {
		ans_ar[loop1].root[0]='\0';
		ans_ar[loop1].offset = 0;
		ans_ar[loop1].aux_verb[0] = '\0';
		ans_ar[loop1].pdgm[0] = '\0';
	}
	/* ISNUM = AVY_srch(morph,ans_ar,&pos); */
	/* This function checks whether the given word is Avy or not */
	sprintf(logmsg, "INFO:Entering in AVY_srch() with word:|%s|loop1=%d",morph,loop1); PRINT_LOG(log_file,logmsg);
	ISNUM = AVY_srch(morph);
	sprintf(logmsg, "INFO:Return of AVY_srch() with word:|%d| which should be -2 ",ISNUM); PRINT_LOG(log_file,logmsg);
	/*
	   AVY_srch returns
	   -1 if the word is avy
	   -2 if the word is not a number & not an avy
	   -3 if the word is a numeral
	   */

	/* checks for isnum is equal to-2 or not */
	if (ISNUM != -2)   {
		strcpy(ans_ar[pos].root,morph);
		ans_ar[pos].offset = ISNUM;
		strcpy(ans_ar[pos].aux_verb,"");
		strcpy(ans_ar[pos].pdgm,"");
		pos++;
	}	

	/***if given word is neither a numeral nor an avy***/
	if (ISNUM !=  -3) {	
		suff[0]='\0';
		morph_size = strlen(morph);  /* finding the size of the morph and storing 
						the size in morph_size */
		/* loop not les than 2 and not equal to pos */
		for(loop=0;loop<2 && !pos;loop++) {
			if(!loop) 
				INFLTNL = 1;
			else
				INFLTNL = 0; 
			for(loop3= morph_size;loop3>=0;loop3--)/* executes until loop3 value becomes 0 */
			{
				/* If the given word is found in the dict. then do not analyse further.
				   e.g. maMcivAdu -/-> maMci + vAdu, if maMcivAdu is found in the dict. */
				/*       if((l== morph_size-1) && (pos > 0)) { goto LAST;}  */

				sprintf(logmsg,"loop1=%d|loop2=|%d|tag_suff_ar[loop2].no_of_entries=%d\n",loop1,loop2,tag_suff_ar[0].no_of_entries);PRINT_LOG(log_file,logmsg);
				if(loop3==morph_size) /* executes when loop3 is equal to morph size */
					suff[0]='\0';
				else
					/* This function concatenates the root word with the suffix */
					get_suff(morph,suff,loop3);
				sprintf(logmsg, "INFO:Assumed suffix from get_suff() for word|%s| suff|%s| ", morph, suff);PRINT_LOG(log_file,logmsg);
				if(DBM_FLAG)	/* executes when the word exists */
				{
					if(suff[0] == '\0')	/*executes when suff[0] is null */
						strcpy(suff,"0");
					/* This function checks the suffix word is present in the suff file */
					sprintf(logmsg,"suff=%s",suff);	PRINT_LOG(log_file,logmsg);
					tag_suff =  dbm_suff_tab_lookup(suff,db_suff);
					sprintf(logmsg, "INFO:Assumed tag suffix from dbm_suff_tab_lookup() for tag_suff|%s| ",tag_suff); PRINT_LOG(log_file,logmsg);
					/* compares  for suff value with 0 and executes only when false */
					if(!strcmp(suff,"0")) 
						strcpy(suff,"");
				}
				else
					/*  this function returns the ptr to the location of the key
					    in the table, if it is present else returns a null */
					tag_suff = (char *)my_blk_bsearch(suff,suff_add_info_ar->suff,sizeof_suff_add,sizeof(suff_add_info_ar[0]),strcmp);
				loop1=0;
				loop2=0; //Nagaraju for seg fault when called from clitic stirpper
				while(tag_suff!=NULL)	/* executes until tag_suff!=null */
				{
					/* This function adds the suffix to the root word */
					cp_suff_add_struct(&tag_suff_ar[loop1],tag_suff);
				sprintf(logmsg,"loop1=%d|loop2=|%d|tag_suff_ar[loop1].no_of_entries=%d",loop1,loop2,tag_suff_ar[loop1].no_of_entries);PRINT_LOG(log_file,logmsg);
					sprintf(logmsg, "INFO:After deleting from root the suffix to be added from cp_suff_add_struct() for tag_suff|%s|", tag_suff);PRINT_LOG(log_file,logmsg);
					tag_suff+=sizeof(dummy);
					//tag_suff+=sizeof(&dummy);
					/* compares suffix value with guessed suff  */
					sprintf(logmsg,"tag_suff_ar=|%s|suff=|%s|entries=|%d|",tag_suff_ar[loop1].suff,suff,tag_suff_ar[loop2].no_of_entries);PRINT_LOG(log_file,logmsg);
					if(strcmp(tag_suff_ar[loop1].suff,suff)){
					sprintf(logmsg,"loop1=|%d|tag_suff_loop1=|%s|suff=|%s|",loop1,tag_suff_ar[loop1].suff,suff);PRINT_LOG(log_file,logmsg);
						break;}
					loop1++;
				}
				/* if(tag_suff!='\0') */
				sprintf(logmsg,"loop1=%d|loop2=|%d|tag_suff_ar[loop2].no_of_entries=%d\n",loop1,loop2,tag_suff_ar[0].no_of_entries);PRINT_LOG(log_file,logmsg);
				loop2=0;
				sprintf(logmsg,"loop1=%d|loop2=|%d|tag_suff_ar[loop2].no_of_entries=%d\n",loop1,loop2,tag_suff_ar[loop2].no_of_entries);PRINT_LOG(log_file,logmsg);
				if(loop1>0)	/* checks for loop1>0 */
				{
					strcpy(tmp_suff,tag_suff_ar[loop2].suff);
					/*executes only when suff and tmp_sff are not same */
					while(!strcmp(tmp_suff,suff))
					{
						sprintf(logmsg, "INFO:while loop of guessed_rt() |guessed_root=%s|morph=%s|",guessed_root,morph );PRINT_LOG(log_file,logmsg);
						strncpy(guessed_root,morph,loop3);
						guessed_root[loop3]='\0';
						strcat(guessed_root,tag_suff_ar[loop2].add);
						//sprintf(logmsg,"tag_suff_ar[loop2].add=%s\n",tag_suff_ar[loop2].add);PRINT_LOG(log_file,logmsg);
						/* this function checks the word in the proper noun dictionary */
						prop_noun_dict_lookup(guessed_root,prop_noun_lex_ar->word,sizeof_prop_noun_lex,sizeof(prop_noun_lex_ar[0]),strcmp,ans_ar1);
						pos1 = 0;
						/* This function copies data ie Priority , pdgm,cat,word
						   to the structure */
						cp_to_struct(ans_ar1,ans_table,&pos1);
						/* this function checks the word in the  dictionary */	
						dict_lookup(guessed_root,DBM_FLAG,db_lex,lex_ar->word,sizeof_lex,sizeof(lex_ar[0]),strcmp,ans_ar1);
						//sprintf(logmsg, "INFO:guessed_root after dict_lookup() |guessed_root=%s| ans_ar1|%s|cat|%s|",guessed_root, ans_ar1,category); PRINT_LOG(log_file,logmsg);
						/* This function copies data ie Priority , pdgm,cat,
						   word to the structure */
						cp_to_struct(ans_ar1,ans_table,&pos1);
						strcpy(tmp_wrd,guessed_root);
						fseek_ptr = tag_suff_ar[loop2].ptr;
						/* exeutes until loop1 <no. of entries */
				sprintf(logmsg,"tag_suff_ar[loop2].no_of_entries=%d\n",tag_suff_ar[loop2].no_of_entries);PRINT_LOG(log_file,logmsg);
						for(loop1=0;loop1<tag_suff_ar[loop2].no_of_entries ; loop1++)
						{
							strcpy(guessed_root,tmp_wrd);
							/* This function sets the position for the required 
							   pdgm, cat, offset in the specified file */
							get_pdgm_info(fp_pdgm,pdgm,category,&offset,&fseek_ptr);
						//sprintf(logmsg, "INFO:get PDGM info from cat |PDGM=%s|CAT=%s|", pdgm, category); PRINT_LOG(log_file,logmsg);
							if(index(pdgm,'?')) /* if it is a vwl_hrmn_pdgm modify the guessed root by changing the vowels so as to bring in vowel harmony */
							{
								/*vwl_harmony(guessed_root,vwl_hrmn_wrd);*/
								/* This function checks whether the last char is
								   vowel or not */
								vwl_harmony(guessed_root,pdgm,vwl_hrmn_wrd);
								if((vwl_hrmn_wrd[0] != '\0') && strcmp(guessed_root,vwl_hrmn_wrd))
								{
									/* this function checks the word in the  dictionary */
									dict_lookup(vwl_hrmn_wrd,DBM_FLAG,db_lex,lex_ar->word,sizeof_lex,sizeof(lex_ar[0]),strcmp,ans_ar1);
									/*  This function copies data ie Priority , pdgm,
									    cat,word from the structure after comparing
									    paradigm with lexical paradigm */
									cp_to_struct_chk_pdgm(ans_ar1,ans_table,&pos1,pdgm);
								}
								strcpy(guessed_root,vwl_hrmn_wrd);
							}
							/* This function compares the guessed root , paradigm,category
							   with the data in the dictionary */
	verify_root(INFLTNL,guessed_root,pdgm,category,offset,ans_table,ans_ar,&pos,DBM_FLAG,db_lex);
	sprintf(logmsg, "INFO:After verify_root()|guessed_root=%s|category =%s|pdgm=%s|offset=%d|ans_table=%s|ans_ar=%s|",guessed_root, category,pdgm,offset,ans_table,ans_ar);PRINT_LOG(log_file,logmsg);
			if(!INFLTNL) { //Added by Nagaraju for root word category
						memset(ans_table[0].cat,'\0',sizeof(ans_table[0].cat));
						memset(ans_table[1].cat,'\0',sizeof(ans_table[1].cat));
						memset(ans_table[2].cat,'\0',sizeof(ans_table[2].cat));
						dict_lookup(ans_ar,DBM_FLAG,db_lex,lex_ar->word,sizeof_lex,sizeof(lex_ar[0]),strcmp,ans_ar1);
						pos1=0;
						cp_to_struct(ans_ar1,ans_table,&pos1);
						//printf("cat1=%s|cat2=%s|cat3=%s|\n",ans_ar[0].cat,ans_ar[1].cat,ans_ar[2].cat);
						//printf("Iam her\n");
						//copies first category 
						strcpy(ans_ar[0].cat,ans_table[0].cat);
						//copies second category if exists
                                                if(ans_table[1].cat!='\0')
                                                strcpy(ans_ar[1].cat,ans_table[1].cat);
                                                if(ans_table[2].cat!='\0')
                                                strcpy(ans_ar[2].cat,ans_table[2].cat);
                                                if(ans_table[3].cat!='\0')
                                                strcpy(ans_ar[3].cat,ans_table[3].cat);
						//printf("cat1=%s|cat2=%s|cat3=%s|\n",ans_ar[0].cat,ans_ar[1].cat,ans_ar[2].cat);
						sprintf(logmsg,"ans_ar=%s|cat=%s|ans_table[0].cat=%s|",ans_ar,category,ans_table[0].cat);PRINT_LOG(log_file,logmsg);
						//strcpy(category,ans_table[0].cat);
}
							// sprintf(logmsg, "INFO:Verify root with all other vales in verify_root()  |guessed_root=%s|pdgm=%s|cat=%s|ans_ar=%s|offset=%d|", guessed_root, pdgm, category, ans_ar, offset); \
							 PRINT_LOG(log_file,logmsg);
						}
						/* gets finall output only when ALWAYS_DEFAULT_PARADIGM
						   is true or word !=null and default pdgm is true */
						if((ALWAYS_DEFAULT_PARADIGM) || ((ans_table[0].word[0] == '\0') && (DEFAULT_PARADIGM)))
						{
							if(suff[0]!='\0') 
							{
								/* this function is used to get paradigm */
								get_paradigm(guessed_root,my_pdgm);
								if(!strcmp(my_pdgm,pdgm)) /* checks pdgm is not 
											     same as of guessed pdgm */
								{
									strcpy(ans_ar[pos].root,guessed_root);
									ans_ar[pos].offset = offset;
									strcpy(ans_ar[pos].aux_verb,"");
									strcpy(ans_ar[pos].pdgm,pdgm);
									pos++;
								}
							}
						}
						/*  *tag_suff++; */
						loop2++;
						strcpy(tmp_suff,tag_suff_ar[loop2].suff);
					}	/* end of the while loop*/
				}
			}
		}		/* end of the for loop */
		
		*no_of_ans = loop;
		/*LAST:*/
		if(pos > 0) 	/* checks for pos > 0 */
			FINDONCE = 1;
		else 		/* executes when pos is <0 */
			FINDONCE = 0;
		if (!FINDONCE) 	 /* checks for FINDONCE is false */
		{
			if (ALWAYS_DEFAULT_PARADIGM || DEFAULT_PARADIGM)
				/* This function gives the output in horizontal way when there is 
				   singular direct case */
				print_default_ans(morph);
			sprintf(logmsg, "INFO:The default ans is |morph=%s|",morph);PRINT_LOG(log_file,logmsg);
		}
	}
	strcpy(ans_ar[pos].root,morph);
	ans_ar[pos].offset = -2; /* End of ar marker */
	strcpy(ans_ar[pos].aux_verb,"");
	strcpy(ans_ar[pos].pdgm,"");
					//printf("INFO:After deleting from root the suffix to be added from cp_suff_add_struct() for tag_suff|%s|\n", tag_suff); 
} /*end of the fun_morph*/
