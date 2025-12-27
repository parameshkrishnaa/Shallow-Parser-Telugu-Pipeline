/**
  * File Name : main.c
  */



/** Function : main
  * This function is the main function where we take input word and actual flow of each function
  * from begining to ending is defined here
  * It takes arguments: argv of char type and argc of integer type
  * Return : int, 
  */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<getopt.h>
#include<unistd.h>
#include <fcntl.h>
#include <gdbm.h>

extern void *my_fatal();

#include "struct1.h"
#include "glbl.h"
#include "defn.h"
#include "struct.h"
#include "morph_logger.h"

/* Global Variables */
int DEBUG;
int DEBUG_NEW;
int FINDONCE;
int FOR_USER;                /* for user friendly output */
int DEFAULT_PARADIGM;        /* for choosing default paradigm if it is not
                                   present in the dict */
int ALWAYS_DEFAULT_PARADIGM; /*  always choose the default paradigm ,
                                even though entry is found in dict */
int WORD_NUM;                /* for assigning word number */
int SENT_NUM;                /*for assigning sentence number */
int LINE_NUM_FLAG;           /* checks for line number is there or not */ 
int UWORD_DICT;              /* checks for uword dict is there or not */
int HORI_OUTPUT;             /* checks for Horizontal output  */
int YES_NO;                 /* answer yes if word is present in dict */
int INFLTNL;
int sizeof_prop_noun_lex;    /* size of proper noun lexical information */
struct lex_info prop_noun_lex_ar[Lexsize]; /* lexical information structure */

char *program_name="main";
char *log_filepath="morph.log";
char *message;
FILE *log_file;


 /**
  * Prototypes of the functions in this file with a file scope
  */
extern void fgetword();
extern void fun_close();
extern void chk_uword_dict();
extern void resufun();
extern void resufun_hori();
extern void fun_morph();
extern char fun_read();
extern int snt_num();
extern int end_mark();
extern void print_snt_num();
extern char get_spell_variation();
extern void prnt_spell_variation();

#define FUNCTION "main()"
int  main(argc,argv)

int argc;
char *argv[];
 {    
    /* file pointers for pdgm,propernoun dict,uword dict */
    FILE *fpt1,*fp_pdgm,*fp_prop_noun_dict,*fp_uword_dict;
    GDBM_FILE db_dict,db_suff,db_uword;    /* global dictionary objects */
    
  //  char num_str[Morphsize];    /* number string used for ssf in fun_read */
    char morph[Morphsize];    /* morph word */
    /* filepath , filename ,filepath of dict */
    char fpath[BigArray],fname[BigArray],fpath_dict[BigArray];
    char upath[BigArray],uname[BigArray];    /* uword path, uword name */
    char line[SmallArray];
    int loop1,swit1,c,k,flag_uword,first=1,pipe_flag;
    struct ans_struct ans_ar[Arraysize];   
        /* lexical info of word , ie word,rootword, pdgm,cat */
   char uword_ans[BigArray]; /* uword ans*/
   char *pdm,*uword,*dict;/*pdm for --pdgmfilepath argument , 
			      uword for --uwordpath argument,
			        dict for --dictfilepath argument*/
   extern char *optarg;
   char *i,*o,iname[10],oname[10];
   extern FILE *stdin;
   extern FILE *stdout;
   

   int sizeof_uword;  /* size of uword */
   struct uword_dict uword_ar[Uwordlen];  
   char morph_spell_variation[SmallArray][SmallArray];  /* morph word */
   int word_count=0;   /* word count */
   char w;//

/* intialising variables */
swit1 = 1;
DEBUG = 0;
DEBUG_NEW = 0;
FINDONCE =0;
FOR_USER =0;
DEFAULT_PARADIGM =0;
ALWAYS_DEFAULT_PARADIGM =0;
WORD_NUM = 0;
SENT_NUM = 0;
LINE_NUM_FLAG = 0;
UWORD_DICT = 0;
HORI_OUTPUT = 0;
YES_NO = 0;
INFLTNL = 1;

if ((log_file = fopen(log_filepath, "w")) == NULL)
        {
                perror("morph.log");
                //exit(-1);
        }
PRINT_LOG(log_file, " Entering the main program\n");
    while (1)
         {
           static struct option long_options[] =
             {
               {"pdgmfilepath",required_argument, 0, 'p'},
               {"uwordpath",required_argument, 0, 'u'},
               {"dictfilepath",required_argument, 0, 'd'},
	       {"in",required_argument, 0, 'i'},
	       {"out",required_argument, 0, 'o'},
               {0, 0, 0, 0}
             };
           int option_index=0;

	k = getopt_long(argc, argv, "pudioUFPADLHWGY",
                           long_options , &option_index);
       if (k==-1)
	break;
         switch(k) {
/* OPTION 'p' pdgm path    */
        case 'p':
		pdm=optarg;
		break;
/*option u for uword dict path*/
	case 'u':
		uword=optarg;
		break;
/* option d for dictpath*/
	case 'd':
		dict=optarg;
		break;
/*option i for input file*/
	case 'i':
		i=optarg;
                strcpy(iname,i);
                stdin=fopen(iname,"r");
                 break;
/* option o for output file*/
	case 'o':
                o=optarg;
                strcpy(oname,o);
                stdout=fopen(oname,"w");
                break;

/** OPTION 'U' CREATES A FILE UWORD WHICH CAPTURES THE WORDS BEYOND
                    THE SCOPE OF THE MORPH   ****************/
	case 'U':
                swit1 = 0; 
		break;
/* option 'F' is used for user friendly output. */
	case 'F':
		FOR_USER = 1;
		break;
/* Choose the default paradigm , if entry is not found in dict */
	case'P':
		DEFAULT_PARADIGM = 1;
		break;
/* Always choose the default paradigm ,even though entry is found in dict */
	case 'A':
		ALWAYS_DEFAULT_PARADIGM = 1;
		break;
/* dbm files are being used. */
        case 'D':
                DBM_FLAG = 1;
		break;
/*  Line numbers are being provided by some other program*/
        case 'L':
                LINE_NUM_FLAG = 1;
		break;
          case 'H':
                HORI_OUTPUT = 1;
		break;
 /* Check the Uword dict */
          case 'W':
                UWORD_DICT = 1;
		break;        
	     case 'G':
                DEBUG = 1;
		break;
/* answers yes if morph recognises, else answers no */
           case 'Y':
                YES_NO = 1;
		break;
	   default:
              printf("**************USAGE***************\n\t --pdgmpath <pdgm_offset_info> --uwordpath <uword_dict_path> --dictpath <dict_path> -ULDWH"); 
		break;
    }
   }   


   if(argc > 4)  /* argument is less than 3 */
      DEBUG_NEW = argv[4][0]-'0';
   if (swit1 == 0)
      fpt1 = fopen("uword","w");/* uword contains words which are 
                                     beyond the scope of the morph*/

   strcpy(fpath,pdm);
   strcpy(fpath_dict,uword);
   strcpy(upath,dict);
   strcpy(fname,fpath);
   strcat(fname,"/pdgm_offset_info");
   /* check for pdgm file is not readable or not */
   if((fp_pdgm=fopen(fname,"r"))==NULL)  
      {
        printf("Error in %s opening\n",fname);
        exit(0);
      }

    strcpy(uname,upath);
    strcat(uname,"/prop_noun_lex.dic");
    if((fp_prop_noun_dict=fopen(uname,"r"))==NULL) /* check for dict
                                                     is readable or not */
     {
       printf("Error in %s opening\n",uname);
       exit(0);
     }
    loop1 = 0;
   /* This function fetches the next wordfrom the current line of the specified file. */
    fgetword(fp_prop_noun_dict,line,','); 
    while(strcmp(line,""))  /* comparing line with " " */
    {
      strcpy(prop_noun_lex_ar[loop1].word,line);   
  /* This function fetches the next word from the current line of 
     the specified file. */
      fgetword(fp_prop_noun_dict,line,',');   
      strcpy(prop_noun_lex_ar[loop1].pdgm,line);
 /* This function fetches the next word from the current line of the specified file. */
      fgetword(fp_prop_noun_dict,line,',');  
      strcpy(prop_noun_lex_ar[loop1].cat,line);
  /* This function fetches the next word from the current line of the specified file. */
      fgetword(fp_prop_noun_dict,line,',');
      loop1++;
     } 
     sizeof_prop_noun_lex = loop1;
     strcpy(uname,upath);
     strcat(uname,"/uword.dic");
     /*
       printf("%s\n",uname);`
     */
     /* check for uword dict is readable or not */
     if((fp_uword_dict=fopen(uname,"r"))==NULL)   
       {
         printf("Error in %s opening\n",uname);
         exit(0);
        }
      loop1 = 0;
     /* This function fetches the next word from the current line of the specified file. */
      fgetword(fp_uword_dict,line,' ');  
      while(strcmp(line,""))   /* compares line with " " */
       {
         strcpy(uword_ar[loop1].sl_word,line);
    /* This function fetches the next word from the current line of the specified file. */
         fgetword(fp_uword_dict,line,'\n');                               
         strcpy(uword_ar[loop1].tl_word,line);
/* This function fetches the next word from the current line of the specified file. */
         fgetword(fp_uword_dict,line,' ');                     
         loop1++;
        }
        sizeof_uword = loop1;
        if(DBM_FLAG != 1)  /* DBM_FLAG is not equal old dicts */
         {   
           printf("\tCurrent version supports only dbm files for dictionaries. \
                        Plesae run with 'D' option\n Exiting ...\n"); 
           exit(1);
          }
         if(DBM_FLAG)   /* if DBM_FLAG is true */
           {
            strcpy(fname,fpath_dict);
            /* my_fatal: This function displays a message  "File not found"
                  when the files dict_final,suff are not there */
            db_dict = gdbm_open(fname,512,GDBM_READER,0666,my_fatal(fname));
            strcpy(fname,fpath);
            strcat(fname,"/suff");
            /* my_fatal: This function displays a message  "File not found"
                when the files dict_final,suff are not there */
            db_suff = gdbm_open(fname,512,GDBM_READER,0666,my_fatal(fname));
            strcpy(fname,fpath);
            strcat(fname,"/uword.dbm");
            /* my_fatal: This function displays a message  "File not found"
                    when the files dict_final,suff are not there */
            db_uword = gdbm_open(fname,512,GDBM_READER,0666,my_fatal(fname));
            }
           SENT_NUM++;
           if(LINE_NUM_FLAG == 0)  /* check for LINE_NUM_FLAG is 0 */
           if((!HORI_OUTPUT) && !YES_NO) /* HORI_OUTPUT AND YES_NO are not true */
           printf("# s%d/n",SENT_NUM);
           c = getc(stdin);
		ungetc(c,stdin);
           while (1) /* while word is there */
            { 
             if(c == EOF)  /* checks for endof file */
               {
                /* Checks the end of the input conditions. if null the file exits */
                fun_close(fpt1,fp_pdgm,swit1,DBM_FLAG,db_dict,db_suff);
                exit(0);
                }
              else 
               {
               /* ungetc(c,stdin); */
               c=fun_read(morph);   /* 1: Reads the input word */
		/*if(!strcmp(num_str,"NW"))
		// { printf("\n ");
		//	PRINT_LOG(log_file, " End of  main program\n");
	//		exit(0);}
	//	else { if (first)  {printf("%s",num_str); first = 0;} else  printf("\n%s",num_str); }*/
		if(!strcmp(morph,"NW"))/* checks for the given word is NOT WORD */
               { 
                /* Checks the end of the input conditions. if null the file exits */
                fun_close(fpt1,fp_pdgm,swit1,DBM_FLAG,db_dict,db_suff); 
                exit(0);
                }
			
		//printf("\n%s\t",morph);
		//printf("%s\t\t",morph);
		printf("%s\t",morph);
               if (strcmp(morph,"\0")) /* checks for morph is null or not */
         	{ 
                FINDONCE = 0;
                 /* checks fo r line no. , snt no., and o/p are there or not */  
                if((LINE_NUM_FLAG && snt_num(morph)) && (!HORI_OUTPUT) && (!YES_NO))
               /* snt_num() This function marks a sentence number to the word */
                   print_snt_num(morph);
		else    /* checks fo r line no. , snt no., and o/p are there  */                                   {
                   WORD_NUM++;
                   if(FOR_USER && !HORI_OUTPUT)  /* o/p is not there */
                     printf("@input_word@\n word_num: w%d\n",WORD_NUM);
                   else
                 /* if answer is not there and hori_output is not there */
                    if(!HORI_OUTPUT && !YES_NO)  
                      printf("input_word\nw%d\n",WORD_NUM);
                    if((morph[0] == '@') || (LINE_NUM_FLAG && end_mark(morph)))                                       /* morph= @*/
                      {
                       if(!HORI_OUTPUT) /*checks for output not there */
                          printf("AVY\n%s\n",morph);/* print the marked words as they are */
                       else
           		printf("%s",morph);/* print the marked words as they are */
	               }
                     else 
                       { 
  /* This function checks the Unkown word is present in the UDictionary or not */                                        chk_uword_dict(morph,uword_ar->sl_word,sizeof_uword,sizeof(uword_ar[0]),strcmp,uword_ans,DBM_FLAG,db_uword); 
                  /* checks for uword not null and uword_dict is there */
                        if((uword_ans[0] != '\0') && (UWORD_DICT)) 
                        if(!HORI_OUTPUT && ! YES_NO)  /* checks output and answer not there */
                           printf("AVY\n%s\n",uword_ans);
                        else if(YES_NO)  /* if answer is there */
                           printf("%s",morph);
		        else               /* if answer is not there */
		           printf("%s",uword_ans);
                        else
 /* This function is the main functuon. It extracts suffixes and calls different routines for
   analysis */ 
        	           fun_morph(morph,swit1,fpt1,fp_pdgm,DBM_FLAG,db_dict,db_suff,ans_ar);
                            if(ans_ar[0].offset == -2)    /* if offest is not equal to -2 */
                            {
      		             if(YES_NO)  /* checks for ajFAwa*/
                               printf("%s<ajFAwa>",morph);  

/* This function is used for identifying the second letter of Hindi alphabets.
 Removes or replaces with the small letter in the input word. */
          			get_spell_variation(morph,morph_spell_variation,word_count);

				flag_uword=1;
	        		for(loop1=0;loop1<=word_count;loop1++)  /* loop will execute until loop1 is less than or equal to word_count */
                                {
    /* This function is the main functuon. It extracts suffixes and calls different routines for    analysis */
		                 fun_morph(morph_spell_variation[loop1],swit1,fpt1,fp_pdgm,DBM_FLAG,db_dict,db_suff,ans_ar);
			//	if(swit1 == 0) 	fprintf(fpt1,"w%d %s\n",WORD_NUM,morph);
/* This function prints the output  including auxilary verbs in horizontal way for the given input word */
				  prnt_spell_variation(morph_spell_variation[loop1],ans_ar);
				  if(ans_ar[0].offset != -2)
					{ 
						 flag_uword=0; 
					}

		                }
                               if ((swit1 == 0) && (flag_uword))  /*checks for  uword contains words which are beyond the scope of the morph is true*/
                                  fprintf(fpt1,"w%d %s\n",WORD_NUM,morph);
                               }    
                               else   /* checks for morph is there */
                                {
     		                 if(YES_NO)  /* checks for answer is true */
                                    printf("%s",morph);
     	                         else     /* if answer is not there */
                                   {
                                    loop1=0;
				    pipe_flag=0;
                                    while(ans_ar[loop1].offset !=-2) /* checks for offset is not eual to -2 */
                                     {
				     if(pipe_flag) printf("|"); pipe_flag = 1;
		                     if(ans_ar[loop1].offset == -1) /* checks for offset is not eual to -1 */
                                       if(!HORI_OUTPUT)   /* if output not there */
	                  	         printf("Avy\n%s\n",ans_ar[loop1].root);
                                       else
                                         printf("%s{Avy}",ans_ar[loop1].root);
                                      else
   				         if(ans_ar[loop1].offset == -3) /* Case of Numeral */
                	                  if(!HORI_OUTPUT)  /* if output not there */
				            printf("Avy\n%s\n",ans_ar[loop1].root);
		                          else  /* if answer is there */
				            printf("%s",ans_ar[loop1].root);
		 		         else   
                                    if(HORI_OUTPUT) 
                            /* This function prints the output in horizontal way for the given input word */
                                       resufun_hori(ans_ar[loop1].root,ans_ar[loop1].pdgm,ans_ar[loop1].offset,ans_ar[loop1].aux_verb); 
                                    else 
                                 /* This function prints the root, pdgm,priority ,category */
                                       resufun(ans_ar[loop1].root,ans_ar[loop1].pdgm,ans_ar[loop1].offset,ans_ar[loop1].aux_verb);
                                 strcpy(ans_ar[loop1].root,"");
	                         ans_ar[loop1].offset = 0;
	                         strcpy(ans_ar[loop1].aux_verb,"");
	                         strcpy(ans_ar[loop1].pdgm,"");
	                         loop1++;
			//if(HORI_OUTPUT) /* checks for the  output is true   */
			//		printf("|");
		                    	 } 
                   			} 
                  	       }
                       }
	//	if(HORI_OUTPUT)
	//	{ printf(" "); }
		}
                 if((c=='.') || (c == '?'))  /* if for c is equal to '.' '?' */
                  { 
                   WORD_NUM++;                 
	           if(!HORI_OUTPUT && !YES_NO)  /* This function prints the output in horizontal way for the given input word */
	             printf("input_word\nw%d\nAVY\n%c\n",WORD_NUM,c);
	           else
                     if(!YES_NO)
                       printf("%c\n",c);
                     else 
                       printf("%c",c);                       
                     SENT_NUM++;
                     c=getc(stdin);
                     if((c!=EOF) && (LINE_NUM_FLAG ==0))
                     if(!HORI_OUTPUT && !YES_NO)
				  /*if out put is not true and answere is also not there */  
	            printf("# s%d\n",SENT_NUM);

       		     }
            
                 }//else printf("\n");
               }
	}
} 

