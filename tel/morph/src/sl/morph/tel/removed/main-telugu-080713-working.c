/**
 * File Name : main_telugu.c
 */


/** Function : main
 * This function is the main function where we take input word and actual flow of each function
 * from begining to ending is defined here
 * It takes arguments: argv of char type and argc
 * of integer type
 * Return : int
 */

/* HEADERS  */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <gdbm.h>

#include "./headers/struct1.h"
#include "./headers/glbl.h"
#include "./headers/defn.h"
#include "./headers/struct.h"
#include "./common/analyser/morph_logger.h"
#include "c_api_v2/c_api_v2.h"
//#include "./new_ss.c"


/* Global Variables */
int DEBUG;		/* checks for the existance of word */
int DEBUG_NEW;		
int FINDONCE;		/* indicates existance of word in the dictionary */
int FOR_USER;		/* for user friendly output */
int DEFAULT_PARADIGM;	/* for choosing default paradigm if it is not present in the dict */
int ALWAYS_DEFAULT_PARADIGM;/* always choose the default paradigm , even though entry is
	       found in the dict */
int WORD_NUM;		/* for assigning word number */
int SENT_NUM;		/* for assigning sentence number */
int LINE_NUM_FLAG;	/* checks for line number is there or not */
int UWORD_DICT;		/* checks for uword dict is there or not */
int HORI_OUTPUT;	/* checks for Horizontal output  */
int YES_NO;		/* answer yes if word is present in dict */
int KRIYAMULA;
int direct_ans_flag;
int INFLTNL;

int sizeof_prop_noun_lex;	/* size of proper noun lexical information */
struct lex_info prop_noun_lex_ar[Lexsize]; /* lexical information structure containig info of
	      root,paradigm,offset,category and priority */

char *program_name="main.c";
char *log_filepath="morph.log";
char *logmsg;
char log_messg;
FILE *log_file;


/**
 * Prototypes of the functions in this file with a file scope
 */
extern void *my_fatal();
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
//extern void fun_tam();
extern void tam_split();
//extern void aux_clt_split();
extern void lcat_verify();
extern void verb_lcat_split();
extern void adj_split();
int itr1=0;
node *data_str;
//GDBM_FILE db_clit;
struct LR_word *spw;
#define FUNCTION "main()"
void read_rules(char *rule_file_name,struct sandhi_rule_pool *rule_pool);
	void
read_rules (char *rule_file_name, struct sandhi_rule_pool *rule_pool)
{
	FILE *fp;
	//array size is changed by Paramesh
//	char rls[700][100], ss[100];
	char rls[1000][200], ss[100];
	int size_of_rls = 0, i, j;
	char san[15][50];
	char temp[15][50];
	/*GDBM_FILE db_san;
        datum key1,data1,nextkey1;

		//db_clit = gdbm_open ("/home/sptil/Nagaraju/telmorph/data_bin/sl/morph/tel/clitic_tel", 512, GDBM_READER, 0666, 0);
		db_san = gdbm_open ("../../../../data_bin/sl/morph/tel/sandhi_tel", 512, GDBM_READER, 0666, 0);
        if (!db_san)
        {
                fprintf (stderr, "File sandhi_tel either doesn't exist or is not a gdbm file.\n");
                exit (2);
        }       
	int cnt1=1;
	char srch1[2];
	key1 = gdbm_firstkey ( db_san );
          while ( key1.dptr ) {

	//printf("srch1|cnt =|%s|%d|\n",srch1,cnt1);
        //key1.dptr = srch1;
        //key1.dsize = strlen(srch1);
        data1= gdbm_fetch (db_san, key1);
	//printf("Iam here\n");
	//printf("data=|%s|\n",data1);
	    //free ( key1.dptr );
             nextkey1 = gdbm_nextkey ( db_san, key1 );
             key1 = nextkey1;
        
        if (data1.dsize > 0) {
                //printf ("%s\n", data.dptr);	
		strncpy(ss,data1.dptr,data1.dsize);
		//ss[strlen (ss) - 2] = '\0';
		ss[data1.dsize]='\0';
		//printf("ss=|%s|\n",ss);
		//strcpy(cc,data.dptr);
		//cc[strlen (cc) - 1] = '\0';
		strcpy (rls[size_of_rls], ss);
		//printf("|%s|\n",rls1[size_of_rls1]);
		size_of_rls++;
                free (data1.dptr);
        } 
        else {
                //printf ("Key |%s| not found.\n", key);
               sprintf (logmsg,"Key |%s| not found.\n", key1);PRINT_LOG(log_file,logmsg);
        }
	}
        gdbm_close (db_san);*/

	fp = fopen (rule_file_name, "r");
	if (fp == NULL)
	{
//		printf ("File cannot be opened\n");
	sprintf(logmsg, "Sandhi rule file cannot be opened-Exiting from main"); 
		PRINT_LOG(log_file, logmsg);
		exit (0);
	}

	/* Read The file line by line and  putting into an array */

	while ((fgets (ss, 100, fp)) != NULL)
	{
		ss[strlen (ss) - 2] = '\0';
		strcpy (rls[size_of_rls], ss);
		size_of_rls++;
	}
	fclose (fp);
	//printf ("The size of rules is 1-- %d\n",size_of_rls);
	size_of_rls = size_of_rls - 1;
	//printf ("The size of rules is 2-- %d\n",size_of_rls);
	rule_pool->no_of_rules = size_of_rls;
	rule_pool->rule =
		(struct sandhi_rule *) malloc (sizeof (struct sandhi_rule) *
				(size_of_rls -3 ));


	for (j = 3; j <size_of_rls; j++)
	{
		for (i = 0; i < 10; i++)
		{
			strcpy (san[i], "\0");
		}			// this is to delete previous value  

		      strcpy (temp, rls[j]);
		split_arr (rls[j], '\t', san);

		strcpy (rule_pool->rule[j - 3].rl_no, san[0]);
		strcpy (rule_pool->rule[j - 3].pat, san[1]);
		strcpy (rule_pool->rule[j - 3].br_pt, san[2]);
		strcpy (rule_pool->rule[j - 3].lft_dlt, san[3]);
		strcpy (rule_pool->rule[j - 3].lft_add, san[4]);
		strcpy (rule_pool->rule[j - 3].rt_dlt, san[5]);
		strcpy (rule_pool->rule[j - 3].rt_add, san[6]);
		strcpy (rule_pool->rule[j - 3].lft_mo_call, san[7]);
		strcpy (rule_pool->rule[j - 3].rt_mo_call, san[8]);
		strcpy (rule_pool->rule[j - 3].lft_cond, san[9]);
		strcpy (rule_pool->rule[j - 3].rt_cond, san[10]);



		if (strcmp (rule_pool->rule[j - 3].lft_add, "0") == 0)
			strcpy (rule_pool->rule[j - 3].lft_add, "\0");
		if (strcmp (rule_pool->rule[j - 3].rt_add, "0") == 0)
			strcpy (rule_pool->rule[j - 3].rt_add, "\0");
		if (strcmp (rule_pool->rule[j - 3].lft_cond, "0") == 0)
			strcpy (rule_pool->rule[j - 3].lft_cond, "\0");
		if (strcmp (rule_pool->rule[j - 3].rt_cond, "0") == 0)
			strcpy (rule_pool->rule[j - 3].rt_cond, "\0");
	}
}
void read_clitics(char *rule_file_name1,struct clitic_rule_pool *rule_pool1);
	void
read_clitics (char *rule_file_name1, struct clitic_rule_pool *rule_pool1)
//void read_clitics(GDBM_FILE db_clit,struct clitic_rule_pool *rule_pool1);
//	void
//read_clitics (GDBM_FILE db_clit, struct clitic_rule_pool *rule_pool1)
{
	FILE *fp_clitic;
	GDBM_FILE db_clit;
	char rls1[700][100], cc[100];
//	char rls1[1500][300], cc[200];
	char cli[15][50];
			//printf("cli[0][0]=%s\n",cli[0]);
	int size_of_rls1 = 0, i, j;
	char temp1[15][50];
	//GDBM_FILE db_clit;
        /*datum key,data,nextkey;

		//db_clit = gdbm_open ("/home/sptil/Nagaraju/telmorph/data_bin/sl/morph/tel/clitic_tel", 512, GDBM_READER, 0666, 0);
		db_clit = gdbm_open ("../../../../data_bin/sl/morph/tel/clitic_tel", 512, GDBM_READER, 0666, 0);
        if (!db_clit)
        {
                fprintf (stderr, "File clitic_tel either doesn't exist or is not a gdbm file.\n");
                exit (2);
        }       
	int cnt=1;
	char srch[2];
	key = gdbm_firstkey ( db_clit );
          while ( key.dptr ) {

	//printf("srch1|cnt =|%s|%d|\n",srch1,cnt1);
        //key1.dptr = srch1;
        //key1.dsize = strlen(srch1);
        data = gdbm_fetch (db_clit, key);
	//printf("Iam here\n");
	//printf("data=|%s|\n",data1);
	    //free ( key.dptr );
             nextkey = gdbm_nextkey ( db_clit, key );
             key = nextkey;
	//for(cnt=1;cnt<=42;cnt++) {
	//srch="32";
	// srch = (char)(((int)'0')+cnt);
	//srch =(char) cnt;
	//sprintf(srch,"%d",cnt);
	//printf("ch|cnt =|%s|%d|",srch);
        //key.dptr = srch;
        //key.dsize = strlen(srch);
        //data = gdbm_fetch (db_clit, key);
	//printf("Iam here\n");
	//printf("data=|%s|\n",data);
        
        if (data.dsize > 0) {
                //printf ("%s\n", data.dptr);	
		strncpy(cc,data.dptr,data.dsize);
		cc[data.dsize]='\0';
		
		//strcpy(cc,data.dptr);
		//cc[strlen (cc) - 1] = '\0';
		strcpy (rls1[size_of_rls1], cc);
		//printf("|%s|\n",rls1[size_of_rls1]);
		size_of_rls1++;
                free (data.dptr);
        } 
        else {
                //printf ("Key |%s| not found.\n", key);
               sprintf (logmsg,"Key |%s| not found.\n", key);PRINT_LOG(log_file,logmsg);
        }
	}
        gdbm_close (db_clit);*/
	fp_clitic = fopen (rule_file_name1, "r");
	if (fp_clitic == NULL)
	{
		//printf ("Rule File cannot be opened\n");
		sprintf(logmsg, "Clitic rule file cannot be opened-Exiting from Main-Program"); 
		PRINT_LOG(log_file, logmsg);
		exit (0);
	}

	/* Read The file line by line and  putting into an array */

	while ((fgets (cc, 100, fp_clitic)) != NULL)
	{
		cc[strlen (cc) - 1] = '\0';
		strcpy (rls1[size_of_rls1], cc);
		size_of_rls1++;
		//printf("|%s|\n",cc);
	}
	fclose (fp_clitic);
	//size_of_rls1 = size_of_rls1 - 1;
	//printf ("The size of rules is 2-- %d\n",size_of_rls1);
	rule_pool1->no_of_rules1 = size_of_rls1;
	rule_pool1->rule1 =
		(struct clitic_rule *) malloc (sizeof (struct clitic_rule) *
				(size_of_rls1));
	//memset(cli, '\0', 50);
	for (j=2;j<size_of_rls1 ;j++)
	{
		for (i = 0; i < 5; i++)
		{
			//printf("cli[%d][%d]=%s\n",j,i,cli[i]);
			strcpy (cli[i], "\0");
		}			// this is for delete previous value  

		      //strcpy (temp, rls1[j]);
		split_arr (rls1[j], '\t', cli);
		//printf("|%s|\t",cli[0]);
		//printf("|%s|\t",cli[1]);
		//printf("|%s|\t",cli[2]);
		//printf("|%s|\n",cli[3]);
		//printf("|%s|\n",cli[4]);

		strcpy (rule_pool1->rule1[j - 0].rl_no1, cli[0]);
		strcpy (rule_pool1->rule1[j - 0].pat1, cli[1]);
		strcpy (rule_pool1->rule1[j - 0].br_pt1, cli[2]);
		strcpy (rule_pool1->rule1[j - 0].lft_dlt1, cli[3]);
		strcpy (rule_pool1->rule1[j - 0].lft_add1, cli[4]);
		//printf("|%s|%s|%s|%s|%s|\n",rule_pool1->rule1[j - 0].rl_no1,
                //rule_pool1->rule1[j - 0].pat1,
                //rule_pool1->rule1[j - 0].br_pt1,
                //rule_pool1->rule1[j - 0].lft_dlt1,
                //rule_pool1->rule1[j - 0].lft_add1);

		if (strcmp (rule_pool1->rule1[j - 0].lft_add1, "0") == 0)
			strcpy (rule_pool1->rule1[j - 0].lft_add1, "\0");
	}

}


//#define FUNCTION "main()"
int main(argc,argv)
	int argc;
	char *argv[];
{
	/* file pointers for pdgm,propernoun dict,uword dict */		
	FILE *fpt1,*fp_pdgm,*fp_prop_noun_dict,*fp_uword_dict;
	/* GNU database manager includes dbm and ndb compatability and db_dict,db_suff,db_uword
	   are used for opening dictionary , suff and uword files respectively */
	GDBM_FILE db_dict,db_suff,db_uword;
	GDBM_FILE db_clit;

	char morph[Morphsize];	/* morph word */
	/* filepath , filename ,filepath of dict */
	char fpath[BigArray],fname[BigArray],fpath_dict[BigArray];
	char upath[BigArray],uname[BigArray];	/* uword path , uword file name */
	char category[BigArray];	/* Nagaraju for derived category */
	char line[SmallArray];		 /* input line */
		int ret_clitic=0;

	/* loop1 for reading characters of the input word ,swit1 for switch case and
	   'c' for reads the next character from stream and returns it as an
	   unsigned char cast to an int,*/
	int loop1,swit1,c,k,flag_uword,first=1,pipe_flag;
	/* ans_Struct contains lexical info of root , offset, auxilary verb,paradigm.
	   an object ans_ar is defined for ans_struct */
	
struct ans_struct ans_ar[BigArray],ans_ar_left[BigArray],ans_ar_right[BigArray],ans_clt_left[BigArray];
	int no_of_ans, no_of_ans_left,no_of_ans_right,no_of_ans_clt;
	int no_of_clt_left;
	char uword_ans[BigArray];	/* uword answer after finding morph output */  
	char tam_variation[SmallArray][SmallArray], tam_variation1[SmallArray][SmallArray], lcat_variation[SmallArray][SmallArray], verb_lcat_variation[SmallArray][SmallArray]; 

	char *pdm,*uword,*dict;/*pdm for --pdgmfilepath argument , 
	 uword for --uwordpath argument,
	 dict for --dictfilepath argument*/
	extern char *optarg;
	char *j,*o,iname[BigArray],oname[BigArray];
	extern FILE *stdin;
	extern FILE *stdout;
	char root[BigArray], cat[BigArray], 
	     g[BigArray],n[BigArray],
	     p[BigArray], kase[BigArray],
	     cm[BigArray], tam[BigArray] ;
	char tam_clitic[10];
	char feature_str[BigArray];
	char feature_str_lr[BigArray];

	char cm_variation[BigArray];
//	struct ans_struct ans_ar[2];


	int sizeof_uword;				/* size of uword */
	struct uword_dict uword_ar[Uwordlen];	/* object for uword structure */

	char w;
	int word_count=0;
	int word_count1=0;
	int flag_unk =0;
	/* Intialising variables*/
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
	YES_NO = 0;
	KRIYAMULA = 0;
	logmsg = (char*) malloc(sizeof(char)*500);
	//logmsg = (char*) malloc(sizeof(char)*256);
	memset(logmsg, '\0', 500);
	//memset(logmsg, '\0', 256);

	/* checking whether morph.log file can be opened or not */
	if ((log_file = fopen(log_filepath, "w")) == NULL)
	{
		perror("morph.log");
		//exit(-1);
	}
	sprintf(logmsg, "Entering into main program"); \
		PRINT_LOG(log_file, logmsg);

	while (1)
	{
		static struct option long_options[] =
		{
	{"pdgmfilepath",required_argument, 0, 'p'},
	{"uwordpath",required_argument, 0, 'u'},
	{"dictfilepath",required_argument, 0, 'd'},
	{"in",required_argument, 0, 'j'},
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
	case 'j':
	j=optarg;
	strcpy(iname,j);
	// stdin=fopen(iname,"r");
	break;
	/* option o for output file*/
	case 'o':
	o=optarg;
	strcpy(oname,o);
	// stdout=fopen(oname,"w");
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
	sprintf(logmsg, "INFO: Entering Aplication with inputfile=%s, outputfile=%s", iname, oname); PRINT_LOG (log_file, logmsg);

	if(argc > 4) 
		DEBUG_NEW = argv[4][0]-'0';
	//if (swit1 == 0)
		//fpt1 = fopen("uword","w");
	/*uword contains words which are beyond the scope of the morph**/ 

	strcpy(fpath,pdm);
	strcpy(upath,dict);
	strcpy(fpath_dict,uword);

	strcpy(fname,fpath);
	strcat(fname,"/pdgm_offset_info");
sprintf(logmsg, "INFO: lova raju  with dbmname=%s, path=%s", fname, fpath); PRINT_LOG (log_file, logmsg);
	/* checks for paradigm file can be opened or not */
	if((fp_pdgm=fopen(fname,"r"))==NULL)	  
	{
		printf("Error in %s opening\n",fname);
		sprintf(logmsg,"Error in %s opening-Exiting from program\n",fname);
		//PRINT_LOG(log_file,logmsg);
		exit(0);
	}

	strcpy(uname,upath);
	strcat(uname,"/prop_noun_lex.dic");
	/* checks for proper noun dict file can be opened or not */
	if((fp_prop_noun_dict=fopen(uname,"r"))==NULL)
	{
		printf("Error in %s opening\n",uname);
		sprintf(logmsg,"Error in %s opening-Exiting from program\n",uname);
		//PRINT_LOG(log_file,logmsg);
		exit(0);
	}

	loop1 = 0;
	fgetword(fp_prop_noun_dict,line,',');
	while(strcmp(line,""))
	{
		strcpy(prop_noun_lex_ar[loop1].word,line);
		fgetword(fp_prop_noun_dict,line,',');
		strcpy(prop_noun_lex_ar[loop1].pdgm,line);
		fgetword(fp_prop_noun_dict,line,',');
		strcpy(prop_noun_lex_ar[loop1].cat,line);
		fgetword(fp_prop_noun_dict,line,',');
		loop1++;
	}
	sizeof_prop_noun_lex = loop1;

	strcpy(uname,upath);
	strcat(uname,"/uword.dic");
	/*	printf("%s\n",uname);	*/
	/* checks for uword dictionary file can be opened or not */
	if((fp_uword_dict=fopen(uname,"r"))==NULL)
	{
		printf("Error in %s opening\n",uname);
		sprintf(logmsg,"Error in %s opening-Exiting from program\n",uname);
		//PRINT_LOG(log_file,logmsg);
		exit(0);
	}

	loop1 = 0;
	fgetword(fp_uword_dict,line,' ');
	while(strcmp(line,""))
	{
		strcpy(uword_ar[loop1].sl_word,line);
		fgetword(fp_uword_dict,line,'\n');
		strcpy(uword_ar[loop1].tl_word,line);
		fgetword(fp_uword_dict,line,' ');
		loop1++;
	}
	sizeof_uword = loop1;

	if(DBM_FLAG != 1)
	{
		printf("\tCurrent version supports only dbm files for dictionaries.                          		 Please run with 'D' option\n Exiting ...\n"); 
		sprintf(logmsg,"\tCurrent version supports only dbm files for dictionaries.                          		 Please run with 'D' option\n Exiting ...\n"); PRINT_LOG(log_file,logmsg);
		exit(1);
	}	
	if(DBM_FLAG)
	{
		strcpy(fname,fpath_dict);
sprintf(logmsg, "INFO: XXXXXXXXXXX=%s",fname); PRINT_LOG(log_file, logmsg);
		db_dict = gdbm_open(fname,512,GDBM_READER,0666,my_fatal());

		strcpy(fname,fpath);
		strcat(fname,"/suff");
//sprintf(logmsg, "INFO: XXXXXXXXXXX=%s",fname); PRINT_LOG(log_file, logmsg);

		db_suff = gdbm_open(fname,512,GDBM_READER,0666,my_fatal());

		strcpy(fname,fpath);
		strcat(fname,"/uword");
		//printf("fpath = |%s|\n",fpath);
//sprintf(logmsg, "INFO: XXXXXXXXXXX=%s",fname); PRINT_LOG(log_file, logmsg);
		db_uword = gdbm_open(fname,512,GDBM_READER,0666,my_fatal());//Nagaraju not used
	
		/*db_clit = gdbm_open ("../../../../data_bin/sl/morph/tel/clitic_tel", 512, GDBM_READER, 0666, 0);
        if (!db_clit)
        {
                fprintf (stderr, "File clitic_tel either doesn't exist or is not a gdbm file.\n");
                exit (2);
        }       */

	}
	sprintf(logmsg, "INFO: Opened GDBM database files needed to run morph"); PRINT_LOG(log_file, logmsg);


	while (1)		/* while word exists */
	{
		sprintf(logmsg, "Entered into while loop -1 "); \
	PRINT_LOG(log_file, logmsg);
		if(c == EOF) {  /* executes when c is equql to end of file */
	/* this function checks end of input conditions */
	//kittu  fun_close(fpt1,fp_pdgm,swit1,DBM_FLAG,db_dict,db_suff);
	fun_close(fp_pdgm,swit1,DBM_FLAG,db_dict,db_suff);
	exit(0);
		} else { 
	data_str= create_tree();
	spw=(struct LR_word*)malloc(sizeof(struct LR_word));
	data_str->lwd=spw;
	sprintf(logmsg, "INFO: Going to read input file using SSF API"); PRINT_LOG(log_file, logmsg);
	sprintf(logmsg, "INFO: SSF Input File is |%s|", iname); PRINT_LOG(log_file, logmsg);
	read_ssf_from_file(data_str, iname);
	sprintf(logmsg, "INFO: child count s |%d|", data_str->child_count); PRINT_LOG(log_file, logmsg);
	int var;

	for (var=0; var< data_str->child_count; var++)
	{
	feature_str[0]='\0';
	node *child= get_nth_child(data_str, var);
	/* this function reads the input word */
	sprintf(logmsg, "INFO: Going to call fun_read()"); PRINT_LOG(log_file, logmsg);
	c=fun_read(morph, get_field(child,1));
	sprintf(logmsg, "INFO: Returned from fun_read(), c = |%d| count=%d|word=%s|", c, var, morph); PRINT_LOG(log_file, logmsg);

/*	int i;
	for(i=0;i<strlen(morph);i++) {
	if(root[i]=='^') 
		root[i]='\0';
	} */



	if (strcmp(morph,"\0"))   /* executes when morph equal to null */
	{
	FINDONCE = 0;
	//WORD_NUM++;
	/* executes when user friendly output and not equal to horizontal output */
	if(FOR_USER && !HORI_OUTPUT)
		//printf("@input_word@\n word_num: w%d\n",WORD_NUM);
		{sprintf(logmsg,"@input_word@\n word_num: w%d\n",WORD_NUM);PRINT_LOG(log_file,logmsg);}
	else
		/* executes when not equal to horizontal output and 
		   word is not present in the dictionary */
		if(!HORI_OUTPUT && !YES_NO)
	//printf("input_word\nw%d\n",WORD_NUM);	
	{sprintf(logmsg,"input_word\nw%d\n",WORD_NUM);PRINT_LOG(log_file,logmsg);}
	//if((morph[0] == '@') || (LINE_NUM_FLAG && end_mark(morph)))
	//if((morph[0] == '') || (LINE_NUM_FLAG && end_mark(morph)))
	if((LINE_NUM_FLAG && end_mark(morph)))
	{
		if(!HORI_OUTPUT)
	//printf("AVY\n%s\n",morph);/* print the marked words as they are */
	{sprintf(logmsg,"AVY\n%s\n",morph);PRINT_LOG(log_file,logmsg);}/* print the marked words as they are */
		else
	//printf("%s",morph);/* print the marked words as they are */
	{sprintf(logmsg,"%s",morph);PRINT_LOG(log_file,logmsg);}/* print the marked words as they are */
	}
	else 
	{
		/* This function checks the Unkown word is present
		   in the UDictionary or not */
		chk_uword_dict(morph,uword_ar->sl_word,sizeof_uword,sizeof(uword_ar[0]),strcmp,uword_ans,DBM_FLAG,db_uword);//Nagaraju because it is unused
		if((uword_ans[0] != '\0') && (UWORD_DICT))
	if((!HORI_OUTPUT) && !YES_NO)
	//printf("AVY\n%s\n",uword_ans);
	{sprintf(logmsg,"AVY\n%s\n",uword_ans);PRINT_LOG(log_file,logmsg);}
	else 
	if(YES_NO)
	//printf("%s",morph);
	{sprintf(logmsg,"%s",morph);PRINT_LOG(log_file,logmsg);}
	else
	//printf("%s",uword_ans);
	{sprintf(logmsg,"%s",uword_ans);PRINT_LOG(log_file,logmsg);}
		else
		{
	memset(g, '\0', sizeof(g));
	memset(n, '\0', sizeof(n));
	memset(p, '\0', sizeof(p));
	memset(kase, '\0', sizeof(kase));
	memset(cm, '\0', sizeof(cm));
	memset(tam, '\0', sizeof(tam));

	/* This function is the main functuon. It extracts suffixes and
	   calls different routines for analysis */
	struct clitic_rule_pool clitic_pool;
	char lft_word[50],rt_word[50];
	char clt_lft_word[50];
	int flag_clt=0;
	//read_clitics ("../../../../data_bin/sl/morph/tel/clitics", &clitic_pool);
	//read_clitics ("../../../../data_src/sl/morph/tel/pc_data/clitics-rls", &clitic_pool);
	read_clitics ("../../../../data_src/sl/morph/tel/pc_data/clitics-rls", &clitic_pool);
	//printf("Iam here\n");
	//memset(clt_lft_word,'\0',50);
	sprintf(logmsg, "INFO: Calling fun_morph() for the word |%s|", morph); PRINT_LOG(log_file, logmsg);
	//fun_morph(morph,fp_pdgm,DBM_FLAG,db_dict,db_suff,ans_ar,&no_of_ans);
	fun_morph(morph,category,fp_pdgm,DBM_FLAG,db_dict,db_suff,ans_ar,&no_of_ans);
	if(!strcmp(category,"noun"))
        strcpy(category,"n");
        if(!strcmp(category,"verb"))
        strcpy(category,"v");

		//printf("no_of_ans=%d|%s\n",no_of_ans,morph);
	sprintf(logmsg, "INFO: fun_morph() returned |%s|%s|%d|%s|",morph, ans_ar[var].root, ans_ar[var].offset, ans_ar[var].pdgm); PRINT_LOG(log_file, logmsg);
	ret_clitic=0;
	//printf("INFO: fun_morph() returned |%s|%s|%d|%s|\n",morph, ans_ar[var].root, ans_ar[var].offset, ans_ar[var].pdgm); 
		char suffix_1[2],suffix_2[3],suffix_3[5],suffix_4[7],suffix_5[4];
		int len=strlen(morph);
		strcpy(suffix_1,morph+len-1);
		strcpy(suffix_2,morph+len-2);
		strcpy(suffix_3,morph+len-4);
		strcpy(suffix_4,morph+len-6);
		strcpy(suffix_5,morph+len-3);
		
		//printf("suffix1=|%s|%s|\n",suffix_1,morph);
		//printf("suffix2=|%s|%s|\n",suffix_2,morph);
		//printf("suffix3=|%s|%s|\n",suffix_3,morph);
		//printf("suffix4=|%s|%s|\n",suffix_4,morph);
		//printf("suffix5=|%s|%s|\n",suffix_5,morph);
		if(strcmp(suffix_1,"A")==0||strcmp(suffix_1,"u")==0||strcmp(suffix_1,"e")==0 || strcmp(suffix_1 ,"o")==0||strcmp(suffix_1,"I")==0||strcmp(suffix_1,"i")==0
||strcmp(suffix_1,"U")==0||strcmp(suffix_2,"le")==0||strcmp(suffix_3,"gAni")==0||strcmp(suffix_4,"leVMdi")==0||strcmp(suffix_3,"aMdi")==0||strcmp(suffix_5,"uta")==0||
strcmp(suffix_5,"Ata")==0||strcmp(suffix_5,"ata")==0||strcmp(suffix_3,"aMta")==0){
		//if(strcmp(suffix_1,"A")==0||strcmp(suffix_1,"u")==0||strcmp(suffix_1,"e")==0 || strcmp(suffix_1 ,"o")==0||strcmp(suffix_1,"I")==0||strcmp(suffix_1,"U")==0||strcmp(suffix_2,"le")==0||strcmp(suffix_3,"gAni")==0||strcmp(suffix_3,"aMdi")==0){
		//printf("Iam here|%s|\n",morph);
		sprintf(logmsg,"INFO: Calling clitic-stripper left word before clitic split,now in main |%s|%s|%d|",clt_lft_word,ans_clt_left[0].root,no_of_clt_left);PRINT_LOG(log_file,logmsg);
			
		ret_clitic=clitic_morph(morph,&clitic_pool,fp_pdgm,DBM_FLAG,db_dict,db_suff,lft_word,ans_clt_left,tam,&no_of_ans_clt);
		//ret_clitic=clitic_morph(morph,&clitic_pool,fp_pdgm,DBM_FLAG,db_dict,db_suff,clt_lft_word,ans_clt_left,tam,&no_of_ans_left);
		sprintf(logmsg,"INFO: left word after clitic split,now in main |%s|%s|%d|ret_clitic=%d|",ans_clt_left,ans_clt_left[0].root,no_of_ans,ret_clitic);PRINT_LOG(log_file,logmsg);
		sprintf(logmsg,"Iam morph=|%s| and root=|%s| offset=|%d|and pdgm=|%s| and cat=|%s| tam=|%s| cm=|%s|", morph, ans_clt_left[0].root, ans_clt_left[0].offset,ans_clt_left[0].pdgm, cat,tam,cm);PRINT_LOG(log_file,logmsg);
		if(ret_clitic == 1 && ans_ar[0].offset!=0) {
		strcpy(tam_clitic,tam);	//Nagaraju-070613 for clitic info
		flag_unk=2;	
		}
			}
		//printf("INFO: left word after clitic split,now in main |%s|%s|%d|ret_clitic=%d|\n",ans_clt_left,ans_clt_left[0].root,no_of_ans,ret_clitic);
	struct sandhi_rule_pool rule_pool;
	strcpy(fpath,pdm);
	strcpy(fname,fpath);
//  printf("fpath  -- %s\n", fname);
//  fpath  -- /home/teltamilmt/sampark/data_bin/sl/morph/tel/
	strcat(fname,"/rls");
	//read_rules ("./rls", &rule_pool);
	read_rules (fname, &rule_pool);
	//read_clitics (fname, &clitic_pool);
	//memset(lft_word,'\0',50);
	memset(rt_word, '\0',50);
	/* if offest is not equal to -2 */
	//if(ans_ar[0].offset == -2 && ans_clt_left[0].offset==-2) //does'nt print unk words
	if(ans_ar[0].offset == -2)// && ans_clt_left[0].offset == -2)
	//if(ans_ar[0].offset == -2 && ans_clt_left[0].offset ==0)//changed Nagaraj 03-07-13
	{
	sprintf(logmsg, "INFO: Checking word for ajFAwa "); PRINT_LOG(log_file, logmsg);
	if(YES_NO)	/* if answer is there */
	//printf("%s<ajFAwa>",morph);
	{sprintf(logmsg,"%s<ajFAwa>",morph);PRINT_LOG(log_file,logmsg);}
	if (swit1 == 0)
	{	
	if (!ispunct(c))
	{
		sprintf(logmsg, "INFO: entered into not punctuation"); PRINT_LOG(log_file, logmsg);
		sprintf(logmsg, "INFO: left word and right word before split |%s|%s|",lft_word,rt_word); PRINT_LOG(log_file, logmsg);
		int ret_status=0;
		category[0]='\0';
		ret_status = sandhi_split (morph, &rule_pool, fp_pdgm, DBM_FLAG, db_dict,db_suff, lft_word, rt_word,ans_ar_left,ans_ar_right,&no_of_ans_left,&no_of_ans_right);
		sprintf(logmsg, "INFO: left word and right word after sandhi split,now in main |%s|%s|%s|%s|%d|%d|%d|%s|",lft_word,rt_word,ans_ar_left[0].root,ans_ar_right[0].root,no_of_ans_left,no_of_ans_right,ret_status,tam); PRINT_LOG(log_file, logmsg);
		//printf("ret_status=|%d|\n",ret_status);
		//int ret_clitic=0;
		//printf("|%d|%d|\n",strlen(lft_word),strlen(rt_word));

//memset(ans_ar_left[0].root,'\0',sizeof(ans_ar_left[0].root));
//printf (" ret_status=|%d|, ans_ar_left=|%d|, ans_ar_ri8=|%d|, rt_word=|%s|, lft_word=|%s|\n",ret_status, ans_ar_left[0].offset, ans_ar_right[0].offset, rt_word, lft_word);
	/*
	   AVY_srch returns
	   -1 if the word is avy
	   -2 if the word is not a number & not an avy
	   -3 if the word is a numeral
	   */
	/* offset is given as !=0 to handle the unk forms after sandhi_split
1	raagaalanu	ret_status=|0|, ans_ar_left=|-2|, ans_ar_ri8=|0|, rt_word=||, lft_word=||
2	puswakamEwe	ret_status=|1|, ans_ar_left=|914|, ans_ar_ri8=|1919|, rt_word=|Ewe|, lft_word=|puswakaM|
3	raagaalanu	ret_status=|1|, ans_ar_left=|0|, ans_ar_ri8=|0|, rt_word=||, lft_word=||
	*/
	// original_030712  if((ret_status == 1) && (ans_ar_left[0].offset != -2) && (ans_ar_right[0].offset !=-2) && (lft_word != '\0') && (rt_word != '\0'))
	if((ret_status == 1)&&(ans_ar_left[0].offset != 0) && (ans_ar_right[0].offset != 0) && (lft_word != '\0') && (rt_word != '\0'))
		{
		//printf("Iam here\n");
	flag_unk=1;
		}
		else if(ret_clitic==1)
		flag_unk=2;
		else {
		//else if(ret_clitic!=1) {
		//printf("Iam here\n");
		//printf("1 morph=|%s| ret_Cl=|%d|\n",morph,ret_clitic);
		strcpy(root, morph); strcpy(cat, "unk");
		strcpy(g, ""); strcpy(n, "");
		strcpy(p, ""); strcpy(kase, "");
		strcpy(cm, ""); strcpy(tam, "");
		strcat(feature_str,"<fs "); strcat(feature_str, "af='");
		strcat(feature_str, root); strcat(feature_str, ",");
		strcat(feature_str, cat); strcat(feature_str, ",");
		strcat(feature_str, g); strcat(feature_str, ",");
		strcat(feature_str, n); strcat(feature_str, ",");
		strcat(feature_str, p); strcat(feature_str, ",");
		strcat(feature_str, kase); strcat(feature_str, ",");
		strcat(feature_str, cm); strcat(feature_str, ",");
		strcat(feature_str, tam); strcat(feature_str, "'>");
		}
		//else {
		//printf("2morph=|%s| ret_Cl=|%d|\n",morph,ret_clitic);
		//break;
		//}
	} 

	}
	}
	//if( ans_ar[0].offset != -2 || flag_unk == 1 )//Nagaraj for clt-stripper-110613
	if( ans_ar[0].offset != -2 || flag_unk == 1||flag_unk==2 )
	{
	if(YES_NO) 	/* if answer is there */
	//printf("%s",morph);
	{sprintf(logmsg,"%s",morph);PRINT_LOG(log_file,logmsg);}
	else
	{
	sprintf(logmsg, "INFO: left word and right word after sandhi split,now in main |%s|%s|%s|%s|",lft_word,rt_word,ans_ar_left[0].root,ans_ar_right[0].root); PRINT_LOG(log_file, logmsg);
		strcpy(child->left5,lft_word);
		strcpy(child->rgt5,rt_word);
	loop1=0;
	pipe_flag=0;
	/* executes when ans_ar.offset is <=-2 */
	//while(ans_ar[loop1].offset !=-2)
	//while(ans_ar[loop1].offset !=-2 || ans_ar_left[0].offset !=-2)
	int word_count=0;
	while(1) {
//	printf("next word is goint to print\n");
	int loopsize=0;
	struct ans_struct* ans_ar_tmp;
	//struct ans_struct* ans_ar_tmp2;
	//if( (flag_unk == 0 && word_count ==0)){//||(flag_unk ==2 && word_count==0) ){
	if( (flag_unk == 0 && word_count ==0)||(flag_unk ==2 && word_count==0) ){
	//if(flag_unk == 0 && word_count ==0){
	//printf("The ans_ar is %s", ans_ar);
	ans_ar_tmp = ans_ar;
	loopsize = no_of_ans;
	//}
		//printf("0no_of_ans=%d|%s|%s\n",no_of_ans,ans_ar,ans_ar_tmp);
		//printf("0no_of_ans=%d|%s|%s|%d|%s|\n",no_of_ans_clt,ans_clt_left,ans_ar_tmp[0].root,ans_ar_tmp[0].offset,ans_ar_tmp[0].pdgm);
	} 
	else if( flag_unk == 2 && word_count==1&&(strlen(ans_clt_left[0].root)!=0) ){
	//else if( flag_unk == 2 && word_count==1){//&&(strlen(ans_clt_left[0].root)!=0) ){
	//if( flag_unk == 2 && word_count==0 )
	//flag_unk1=flag_unk;
	//printf("The ans_ar is %s\n", ans_clt_left);
	ans_ar_tmp = ans_clt_left;
	loopsize = no_of_ans_clt;
	//flag_unk = 0;
	//word_count = 0;
	//ans_ar_tmp2 = ans_ar;
	//int loopsize2 = no_of_ans;
	//flag_unk1=flag_unk;
	//ans_ar_tmp2 = ans_ar;
	//int loopsize2 = no_of_ans;
	//strcat(ans_ar_tmp,ans_ar_tmp2);
	//loopsize=loopsize+loopsize2;
		//printf("1no_of_ans=%d|%s|%s\n",no_of_ans_clt,ans_clt_left,ans_ar_tmp);
		//printf("1no_of_ans=%d|%s|%s|%d|%s|\n",no_of_ans_clt,ans_clt_left,ans_ar_tmp[0].root,ans_ar_tmp[0].offset,ans_ar_tmp[0].pdgm);
	//	flag_unk=0;
	}
	else if( flag_unk == 1 && word_count == 0 ){
		//printf("the ans_ar_left %s\n", ans_ar_left);
	ans_ar_tmp = ans_ar_left;
//	ans_ar_tmp = ans_ar;
	loopsize = no_of_ans_left;
	}
	else if( flag_unk == 1 && word_count == 1 ){
		//printf("the ans_ar_right %s\n", ans_ar_right);
	ans_ar_tmp = ans_ar_right;
	loopsize = no_of_ans_right;
// 040611 introduced by paramesh, In input if a ind.word comes below input of split words,flag_num need 2 be "0"
	flag_unk = 0;
	word_count = 0;
	}
	else 
	break;
	if(!strcmp(child->left5,""))
{
strcpy(child->left5,child->node_tkn);
}

		word_count++;
		loop1 = 0;
	// 020611 changed by paramesh, this allows to give more than an analysis.
	//printf("ans_ar_tmp[loop1].offset=%s\n",ans_ar_tmp[loop1].pdgm);	
	while(ans_ar_tmp[loop1].offset !=-2)//||flag_unk1==2)//||ans_ar_tmp2[loop1].offset!=-2)
	//while(ans_ar_right[loop1].offset !=-2)
	{
		if(pipe_flag)
	strcat(feature_str, " ");
		pipe_flag=1;
		if(ans_ar_tmp[loop1].offset == -1)  /* checks for Avy */
	/* executes when output is not there */
	if(!HORI_OUTPUT)
	//printf("Avy\n%s\n",ans_ar_tmp[loop1].root);
	{sprintf("Avy\n%s\n",ans_ar_tmp[loop1].root);PRINT_LOG(log_file,logmsg);}
	else
	//printf("%s{Avy}",ans_ar_tmp[loop1].root);
	{sprintf("Avy\n%s\n",ans_ar_tmp[loop1].root);PRINT_LOG(log_file,logmsg);}
		else
	if(ans_ar_tmp[loop1].offset == -3) /* Case of Numeral */
	/* executes when output is not there */
	if(!HORI_OUTPUT) {
	//printf("Avy\n%s\n",ans_ar_tmp[loop1].root);
	{sprintf("Avy\n%s\n",ans_ar_tmp[loop1].root);PRINT_LOG(log_file,logmsg);}
	} else {
	if(ispunct(ans_ar_tmp[loop1].root[0])) {
		strcpy(root, ans_ar_tmp[loop1].root); strcpy(cat, "punc");
		strcpy(g, ""); strcpy(n, ""); strcpy(p, "");
		strcpy(kase, ""); strcpy(cm, ""); strcpy(tam, "");
		strcpy(feature_str,"");
		strcat(feature_str,"<fs "); strcat(feature_str, "af='");

// paramesh: NCR Values are introduced here 310112 Starting.....

if(!strcmp(root,"!")) { 
	strcpy(root,"&exm;");
}
if(!strcmp(root,".")) { 
	strcpy(root,"&dot;");
}
if(!strcmp(root,",")) { 
	strcpy(root,"&comma;");
}
if(!strcmp(root,"<")) { 
	strcpy(root,"&lang;");
}
if(!strcmp(root,">")) { 
	strcpy(root,"&rang;");
}
if(!strcmp(root,"/")) { 
	strcpy(root,"&frasl;");
}
if(!strcmp(root,"?")) { 
	strcpy(root,"&qus;");
}
if(!strcmp(root,";")) { 
	strcpy(root,"&scol;");
}
if(!strcmp(root,":")) { 
	strcpy(root,"&col;");
}
if(!strcmp(root,"\"")) { 
	strcpy(root,"&bdquo;");
}
if(!strcmp(root,"'")) { 
	strcpy(root,"&apos;");
}
if(!strcmp(root,"[")) { 
	strcpy(root,"&lsbrs;");
}
if(!strcmp(root,"]")) { 
	strcpy(root,"&rsbrs;");
}
if(!strcmp(root,"{")) { 
	strcpy(root,"&lfbrs;");
}
if(!strcmp(root,"}")) { 
	strcpy(root,"&rfbrs;");
}
//if(!strcmp(root,"\/")) { 
//strcpy(root,"&brasl;");
//}
if(!strcmp(root,"|")) { 
	strcpy(root,"&pipe;");
}
if(!strcmp(root,"=")) { 
	strcpy(root,"&equl;");
}
if(!strcmp(root,"+")) { 
	strcpy(root,"&add;");
}
if(!strcmp(root,"-")) { 
	strcpy(root,"&minus;");
}
if(!strcmp(root,"_")) { 
	strcpy(root,"&unds;");
}
if(!strcmp(root,"(")) { 
	strcpy(root,"&rcbrs;");
}
if(!strcmp(root,")")) { 
	strcpy(root,"&lcbrs;");
}
if(!strcmp(root,"*")) { 
	strcpy(root,"&lowast;");
}
if(!strcmp(root,"&")) { 
	strcpy(root,"&amp;");
}
if(!strcmp(root,"^")) { 
	strcpy(root,"&circ;");
}
if(!strcmp(root,"%")) { 
	strcpy(root,"&perc;");
}
if(!strcmp(root,"$")) { 
	strcpy(root,"&dol;");
}
if(!strcmp(root,"#")) { 
	strcpy(root,"&hash;");
}
if(!strcmp(root,"@")) { 
	strcpy(root,"&atrat;");
}
if(!strcmp(root,"~")) { 
	strcpy(root,"&tilde;");
}
if(!strcmp(root,"`")) { 
	strcpy(root,"&acute;");
}
if(!strcmp(root,"‘")) { 
	strcpy(root,"&lsquo;");
}
if(!strcmp(root,"’")) { 
	strcpy(root,"&rsquo;");
}
if(!strcmp(root,"‚")) { 
	strcpy(root,"&sbquo;");
}
if(!strcmp(root,"“")) { 
	strcpy(root,"&ldquo;");
}
if(!strcmp(root,"”")) { 
	strcpy(root,"&rdquo;");
}
if(!strcmp(root,"...")) { 
	strcpy(root,"&hellep;");
}

// paramesh: NCR Values are introduced here 310112 ...Ending


		strcat(feature_str, root); strcat(feature_str, ",");
		strcat(feature_str, cat); strcat(feature_str, ",");
		strcat(feature_str, g); strcat(feature_str, ",");
		strcat(feature_str, n); strcat(feature_str, ",");
		strcat(feature_str, p); strcat(feature_str, ",");
		strcat(feature_str, kase); strcat(feature_str, ",");
		strcat(feature_str, cm); strcat(feature_str, ",");
		strcat(feature_str, tam); strcat(feature_str, "'>");
	} else { 
		strcpy(root, ans_ar_tmp[loop1].root); strcpy(cat, "num");
		strcpy(g, ""); strcpy(n, ""); strcpy(p, "");
		strcpy(kase, ""); strcpy(cm, ""); strcpy(tam, "");
		strcat(feature_str,"<fs "); strcat(feature_str, "af='");
		strcat(feature_str, root); strcat(feature_str, ",");
		strcat(feature_str, cat); strcat(feature_str, ",");
		strcat(feature_str, g); strcat(feature_str, ",");
		strcat(feature_str, n); strcat(feature_str, ",");
		strcat(feature_str, p); strcat(feature_str, ",");
		strcat(feature_str, kase); strcat(feature_str, ",");
		strcat(feature_str, cm); strcat(feature_str, ",");
		strcat(feature_str, tam); strcat(feature_str, "'>");

	}
	}

	else  if(HORI_OUTPUT)
	/* executes when output is there */
	{

	/* This function prints the output
	   in horizontal way for the given input word */
	if((flag_unk == 2 && word_count == 1)) 
	memset(tam, '\0', sizeof(tam));	//Nagaraju 05-06-13 for suff in clitics
	memset(cm, '\0', sizeof(cm));
	memset(cm_variation, '\0', sizeof(cm_variation));
	memset(lcat_variation, '\0', sizeof(lcat_variation));
	memset(verb_lcat_variation, '\0', sizeof(verb_lcat_variation));
	//sprintf(logmsg, "INFO: Calling resufun_hori(),|root=%s|cat=%s|g=%s|n=%s|p=%s|case=%s|cm=%s|suff=%s|", root, cat, g, n, p, kase, cm, tam ); PRINT_LOG(log_file, logmsg);
	//strcpy(root,"\0");
	sprintf(logmsg, "INFO: Calling resufun_hori(),ans_ar_tmp[loop1].root=%s|ans_ar_tmp[loop1].pdgm=%s|ans_ar_tmp[loop1].offset=%d|ans_ar_tmp[loop1].aux_verb=%s|root=%s|cat=%s|g=%s|n=%s|p=%s|case=%s|cm=%s|suff=%s|",ans_ar_tmp[loop1].root,ans_ar_tmp[loop1].pdgm,ans_ar_tmp[loop1].offset,ans_ar_tmp[loop1].aux_verb,root, cat, g, n, p, kase, cm, tam ); PRINT_LOG(log_file, logmsg);
	resufun_hori(ans_ar_tmp[loop1].root,ans_ar_tmp[loop1].pdgm,ans_ar_tmp[loop1].offset,ans_ar_tmp[loop1].aux_verb,root, cat, g,n,p, kase,cm, tam );
	sprintf(logmsg, "INFO: Calling resufun_hori(),root=%s|cat=%s|g=%s|n=%s|p=%s|case=%s|cm=%s|suff=%s|", root, cat, g, n, p, kase, cm, tam ); PRINT_LOG(log_file, logmsg);
	//												                                                                                                        resufun_hori(ans_ar_right[loop1].root,ans_ar_right[loop1].pdgm,ans_ar_right[loop1].offset,ans_ar_right[loop1].aux_verb,root, cat, g,n,p, kase,cm, tam );

//													sprintf(logmsg, "INFO: Calling resufun_hori(),|root=%s|cat=%s|g=%s|n=%s|p=%s|case=%s|cm=%s|suff=%s|", root, cat, g, n, p, kase, cm, tam ); PRINT_LOG(log_file, logmsg);

	strcat(feature_str,"<fs ");
	strcat(feature_str, "af='");
	strcat(feature_str, root);
	strcat(feature_str, ",");
	verb_lcat_split(tam,verb_lcat_variation,word_count);
	lcat_verify(tam,lcat_variation,word_count);
	if(lcat_variation)  {
	if((!strcmp(lcat_variation[0],"adv"))&&((!strcmp(tam,""))||(strcmp(tam,"0_adv")))){
	strcpy(lcat_variation[0],"nst");
		sprintf(logmsg, "INFO: iam here with Calling |cat=%s|lcat_veriation=%s|", cat, lcat_variation); PRINT_LOG(log_file, logmsg);
	}
		sprintf(logmsg, "INFO: Calling |cat=%s|lcat_veriation=%s|", cat, lcat_variation); PRINT_LOG(log_file, logmsg);
		
	if(!strcmp(lcat_variation[0],"")) {
	sprintf(logmsg, "INFO: Calling |lcat_veriation=%s|", cat); PRINT_LOG(log_file, logmsg);
	//code for derived category Nagaraju
	if(category[0]=='\0'){//if fun_morph doesnt return root word category
		//printf("cat=%s",cat);
		strcat(feature_str, cat);}//contains derived word category 
	else {
		strcat(feature_str, category);}//contains root word category
	//code for derived category Nagaraju
	//strcat(feature_str, cat);
		}
		else { strcat(feature_str,lcat_variation[0]); }
	}
	//removed hard coded strings into file(main.p)	
	FILE *fp1;
	char buff1[1000];
	int size_of_file1=0,i1,j1;
	char words1[1000][200];
	char words2[1000][200];
	char wrd1[15][50];
	//char wrd[50][100];
	//fp1=fopen("derivation/main.p","r");
	//fp1=fopen("/home/guest/oldmorph/data_bin/sl/morph/tel/derivation/main.p","r");
	//fp1=fopen("/home/guest/oldmorph/data_src/sl/morph/tel/pc_data/derivation/main.p","r");
	fp1=fopen("../../../../data_src/sl/morph/tel/pc_data/derivation/main.p","r");
	if(fp1!=NULL){
		//printf("main.p opned");
		while(fgets(buff1,1000,fp1)!=NULL){ 
			buff1[strlen (buff1) - 1] = '\0';
			strcpy (words1[size_of_file1], buff1);
			//printf("%s\n",words[size_of_file]);
			size_of_file1++;
			//printf("%s",buff);
		}
		//printf("%d",size_of_file);
	}
		else {
			//printf("The file main.p cannot be opened\n");
			sprintf(logmsg,"The file main.p cannot be opened\n");PRINT_LOG(log_file,logmsg);
			exit(0);
		}
			fclose(fp1);
		//Nagaraju
			for(j1=0;j1<size_of_file1;j1++) { 
				//for(i1=0;i1<3;i1++){
				//strcpy(wrd1[i1],"\0");}
				split_arr(words1[j1],' ',wrd1);
				//printf("root=%s|wrd1[0]=%s|wrd1[0]=%s\n",root,wrd1[0],wrd1[0]);
				if(!strcmp(cat,"pn")) {
					memset(g, '\0', sizeof(g));
					memset(p, '\0', sizeof(p));
					if((!strcmp(root,wrd1[0]))){
						strcpy(p,wrd1[1]);
						strcpy(g,wrd1[2]);
	sprintf(logmsg,"Nagaraj Info:In main with cat=%s|p=%s|g=%s|",cat,p,g);PRINT_LOG(log_file,logmsg);
						break;
						//printf("p=%s|g=%s\n",p,g);
					}	
	/*if(!strcmp(cat,"pn")) {
		memset(g, '\0', sizeof(g));
		memset(p, '\0', sizeof(p));
		if((!strcmp(root,"nenu"))||(!strcmp(root,"memu"))||(!strcmp(root,"meM"))||(!strcmp(root,"manaM")))
		{
	strcpy(p,"1");
	strcpy(g,"any");
		}
		else if((!strcmp(root,"nuvvu"))||(!strcmp(root,"nIvu"))||(!strcmp(root,"mIru"))||(!strcmp(root,"wamaru"))||(!strcmp(root,"wAmu")))
		{
	strcpy(p,"2");
	strcpy(g,"any");
		}
		else if((!strcmp(root,"vAdu"))||(!strcmp(root,"vIdu"))||(!strcmp(root,"iwanu"))||(!strcmp(root,"awadu"))||(!strcmp(root,"awanu"))||(!strcmp(root,"iwadu"))||(!strcmp(root,"eVvadu")))
		{
	strcpy(p,"3");
	strcpy(g,"m");
		}
		else if((!strcmp(root,"vAru"))||(!strcmp(root,"vIru"))||(!strcmp(root,"vAlYlu"))||(!strcmp(root,"vIlYlu"))||(!strcmp(root,"eVvaru"))||(!strcmp(root,"wanu"))||(!strcmp(root,"winu")))
		{
	strcpy(p,"3");
	strcpy(g,"fm");
		}
		else if((!strcmp(root,"AmeV"))||(!strcmp(root,"ImeV"))||(!strcmp(root,"Avida"))||(!strcmp(root,"Ivida"))||(!strcmp(root,"emeV")))
		{
	strcpy(p,"3");
	strcpy(g,"f");
		}
		else if((!strcmp(root,"axi"))||(!strcmp(root,"ixi"))||(!strcmp(root,"exi")))
		{
	strcpy(p,"3");
	strcpy(g,"fn")
		}*/;
		}
		//sprintf(logmsg, "new- gnp for Pronoun|gen=%s|per=%s|", g, p); PRINT_LOG(log_file, logmsg);
	}
		sprintf(logmsg, "new- gnp for Pronoun|gen=%s|per=%s|", g, p); PRINT_LOG(log_file, logmsg);
	strcat(feature_str, ",");
	strcat(feature_str, g);
		memset(g, '\0', sizeof(g));
	strcat(feature_str, ",");
	strcat(feature_str, n);
		memset(n, '\0', sizeof(n));
	strcat(feature_str, ",");
	strcat(feature_str, p);
		memset(p, '\0', sizeof(p));
	strcat(feature_str, ",");
	strcpy(cm,tam);
	memset(tam_variation, '\0', sizeof(tam_variation));
	if((!strcmp(cat,"n"))||(!strcmp(cat,"pn"))) {
	tam_split(tam,tam_variation,word_count);
	if(!strcmp(cm,"0")) {
	strcpy(kase,"d");
	}
	if(!strcmp(tam,"obl")) {
	strcpy(kase,"o");
	strcat(feature_str, kase);
	memset(kase,'\0',sizeof(kase));
	strcat(feature_str, ",");
	strcpy(tam,"ti");
	strcpy(cm,tam);
	}
	 else if(strcmp(tam_variation[0],"")){
	strcat(feature_str, kase);
	memset(kase,'\0',sizeof(kase));
	strcat(feature_str, ",");
	strcpy(cm,tam_variation[0]);
	}
	else{ 
	strcat(feature_str, kase);
memset(kase,'\0',sizeof(kase));
	strcat(feature_str, ",");
	strcpy(cm,tam);
	}
	} else {
	memset(kase, '\0', sizeof(kase));
	strcat(feature_str, kase);
	strcat(feature_str, ",");
	strcpy(cm,tam);
	}
	if((strcmp(cm,"0"))&&(strcmp(cm,""))&&(!strcmp(cat,"adv"))) {
	memset(cat, '\0', sizeof(cat));
	strcpy(cat,"nst");
	}
	if(!strcmp(cat,"v")) {
		if(tam) {
	tam_split(tam,tam_variation,word_count);
	if(strcmp(tam_variation[0],""))
	{
	strcpy(cm, tam_variation[0]);
	strcat(feature_str, cm);
memset(cm,'\0',sizeof(cm));
	strcat(feature_str, ",");
	} 
	else {
	strcpy(cm, tam);
	strcat(feature_str, cm);
memset(cm,'\0',sizeof(cm));
	strcat(feature_str, ",");
	}
	}

		} else {
	strcat(feature_str, cm);
memset(cm,'\0',sizeof(cm));
	strcat(feature_str, ",");
		}
	strcat(feature_str, tam);
memset(tam,'\0',sizeof(tam));
	strcat(feature_str, "' ");
	//code for derived category Nagaraju
	if(category[0]!='\0'&&cat[0]!='\0'&&strcmp(category,cat)){
	//if(category[0]!='\0'&&cat[0]!='\0'){
		//strcat(feature_str, ",");
		strcat(feature_str, "deri_cat='");
		strcat(feature_str,cat);
		memset(cat,'\0',sizeof(cat));
		strcat(feature_str, "'");
	}
	//code for derived category Nagaraju            
	strcat(feature_str, "'>");
	//if(flag_unk==2&&word_count==1) 
	if(flag_unk==2) 
	strcpy(tam,tam_clitic);	//Nagaraju-070613 for clitic info
	}
		sprintf(logmsg, "lopp1 is and FS=%s", feature_str); PRINT_LOG(log_file, logmsg);
		//printf("loop1 is and FS=%s\n", feature_str);
		strcpy(ans_ar_tmp[loop1].root,"");
		ans_ar_tmp[loop1].offset = 0;
		strcpy(ans_ar_tmp[loop1].aux_verb,"");
		strcpy(ans_ar_tmp[loop1].pdgm,"");
		loop1++;
	}
itr1+=1;
	 if(itr1==1||(itr1==2&&flag_unk==2)){
	 //if(itr1==1)
                        strcat(feature_str_lr,feature_str);
                        //strcpy(feature_str_lr,feature_str);
                      feature_str[0]='\0';
                             }
//								printf("first word completed\n");
	}
itr1=0;
	} 
	} 
	}
	}
	if((c=='.') || (c == '?')||(c=='"'))
	{
		WORD_NUM++;
		/* checks for Horizontal output and YES_NO if word is present in dict */
		if(!HORI_OUTPUT && !YES_NO)
	/* This function prints the output in horizontal way for
	   the given input word */
	//printf("input_word\nw%d\nAVY\n%c\n",WORD_NUM,c);
	{sprintf(logmsg,"input_word\nw%d\nAVY\n%c\n",WORD_NUM,c);PRINT_LOG(log_file,logmsg);}
		else 
	if(!YES_NO) 
	//  printf("%c\n",c);
	//printf("",c);
	{sprintf(logmsg,"",c);PRINT_LOG(log_file,logmsg);}
	else 
	//printf("%c",c); 
	{sprintf(logmsg,"%c",c);PRINT_LOG(log_file,logmsg);}
		SENT_NUM++;
	}
	}
	child->OR= read_or_node( feature_str_lr);	
	child->OR1=read_or_node(feature_str);
	feature_str_lr[0]='\0';

	}
	print_tree_to_file(data_str, oname);
	sprintf(logmsg, "out write sucessfully", feature_str); PRINT_LOG(log_file, logmsg);
	fun_close(fp_pdgm,swit1,DBM_FLAG,db_dict,db_suff);
	exit(0);
		}  
	}
}
