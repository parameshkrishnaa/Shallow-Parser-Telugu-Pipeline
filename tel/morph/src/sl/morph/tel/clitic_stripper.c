#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <fcntl.h>
//#include "substr.c"
//#include "split_arr.c"
#include <gdbm.h>

//#include "./morph_telugu.c"
#include "./headers/struct1.h"
//#include "./headers/glbl.h"
#include "./headers/defn.h"
//#include "./headers/struct.h"
#include "./common/analyser/morph_logger.h"
//#include "./c_api_v2/c_api_v2.h"

extern FILE *log_file;
extern char *program_name;
extern char *logmsg;
#define FUNCTION "clitic_morph()"

extern void *my_fatal();
extern void fun_morph();

int clitic_morph (char *input_word, struct clitic_rule_pool *rule_pool,
		FILE * fp_pdgm, int DBM_FLAG, GDBM_FILE db_lex,
		GDBM_FILE db_suff, char *clt_lft_word, struct ans_struct *ans_clt_lft,char *tam,int* no_of_ans_left)
	{
	// int split_pos = 0;
	//char *program_name="clitic_stripper.c";
	
	/*GDBM_FILE dbf;
	datum key, data;

        dbf = gdbm_open ("/home/sptil/Nagaraju/telmorph/src/sl/morph/tel/clitic_tel", 512, GDBM_READER, 0666, 0);
        if (!dbf)
        {
                fprintf (stderr, "File clitic_tel either doesn't exist or is not a gdbm file.\n");
                exit (2);
        }       
        char *srch="1";
        key.dptr = srch;
        key.dsize = strlen(srch);
        
        data = gdbm_fetch (dbf, key);
        
        if (data.dsize > 0) {
                printf ("%s\n", data.dptr);
                free (data.dptr);
        }       
        else {
                printf ("Key |%s| not found.\n", key);
        }       
        gdbm_close (dbf);*/

	int pattern_matched[rule_pool->no_of_rules1];
	int i, j, k;
	char left_word_tmp[50];
	char right_word_tmp[50];
	char suffix_1[5],suffix_2[5],suffix_3[5],suffix_4[5];
	char suffix_5[5],suffix_6[5];
	char category[BigArray];
	int len;
	//printf("|%d|\n",rule_pool->no_of_rules1);
	//for (i = 2; i < rule_pool->no_of_rules1; i++)
	//{				// for every rule in rule pool
	//printf("i=|%s|lft_add1=|%s|lft_dlt1=|%s|pat1=|%s|\n",rule_pool->rule1[i].rl_no1,rule_pool->rule1[i].lft_add1,rule_pool->rule1[i].lft_dlt1,rule_pool->rule1[i].pat1);
	//}
			sprintf(logmsg,"In clitic_stripper no_of_rules=|%d|, and input_word is|%s|",rule_pool->no_of_rules1,input_word);PRINT_LOG(log_file,logmsg);
	i=2;
	//printf("i=%d\n",i);
	for (i = 2; i < rule_pool->no_of_rules1; i++)
	{
				// for every rule in rule pool
		int status;
		regex_t re;
		regmatch_t split_pos[2];
	//printf("lft_add1=|%s|lft_dlt1=|%s|\n",rule_pool->rule1[i].lft_add1,rule_pool->rule1[i].lft_dlt1);
		
		size_t no_of_matches = 1;
		if ((regcomp (&re, rule_pool->rule1[i].pat1, REG_EXTENDED) != 0))
		{
			pattern_matched[i] = 0;
			break;
		}
		//printf("Iam here\n");
		status = regexec (&re, input_word, no_of_matches, split_pos, 0);
		regfree (&re);
		if (status != 0)
		{
			pattern_matched[i] = 0;
		}
		else
			pattern_matched[i] = 1;

		if (pattern_matched[i] == 1) {
			strcpy(left_word_tmp,"");
			if (split_pos[0].rm_so == 0)
			{
				substr (input_word, 0, split_pos[0].rm_eo, left_word_tmp);
				substr (input_word, split_pos[0].rm_eo, strlen (input_word),
                                                right_word_tmp);
			//printf("right_word_tmp=|%s|\n",right_word_tmp);
			}
			else
                        {
                                substr (input_word, 0,
                                                split_pos[0].rm_so + atoi (rule_pool->rule1[i].br_pt1),
                                                left_word_tmp);
				substr (input_word,
                                                split_pos[0].rm_so + atoi (rule_pool->rule1[i].br_pt1),
                                                strlen (input_word), right_word_tmp);
			//printf("letf_word_tmp=|%s|%s|%d|\n",left_word_tmp,input_word, split_pos[0].rm_so);

			//printf("letf_word_tmp=|%s|\n",left_word_tmp);
			//printf("right_word_tmp=|%s|\n",right_word_tmp);
			}
			char test_left[50];
			memset(test_left,'\0',50);
			left_word_tmp[strlen (left_word_tmp) -
				atoi (rule_pool->rule1[i].lft_dlt1)] = '\0';
			strcpy (test_left, "");
			strcat (test_left, left_word_tmp);
			strcat (test_left, rule_pool->rule1[i].lft_add1);
			//printf("letf_word_tmp=|%s|test_left=|%s|lft_add1=|%s|lft_dlt1=|%s|\n",left_word_tmp,test_left,rule_pool->rule1[i].lft_add1,rule_pool->rule1[i].lft_dlt1);
			

			sprintf(logmsg,"clitic_pattern no is %s, and clitic_pattern is %s,spliting is at=%d, matched left word is=%s, \n",
					rule_pool->rule1[i].rl_no1, rule_pool->rule1[i].pat1,
					split_pos[0].rm_so, test_left); PRINT_LOG(log_file, logmsg);

			memset(ans_clt_lft, '\0', sizeof(struct ans_struct)*BigArray);

			sprintf(logmsg, "INFO: answer array before fun morph |%s|%d|%s|", ans_clt_lft[0].root, ans_clt_lft[0].offset, ans_clt_lft[0].pdgm); PRINT_LOG(log_file, logmsg);
			sprintf(logmsg, "INFO:before fun morph |%s|%d|%d|%d|", test_left,DBM_FLAG,db_suff,db_lex); PRINT_LOG(log_file, logmsg);
			//fun_morph (input_word, fp_pdgm, DBM_FLAG, db_lex, db_suff, ans_clt_lft,no_of_ans_left);
			if((strlen(test_left)!=0) ) {
			//printf("Iam here\n");
			//fun_morph (test_left, fp_pdgm, DBM_FLAG, db_lex, db_suff, ans_clt_lft,no_of_ans_left);
			fun_morph (test_left, category,fp_pdgm, DBM_FLAG, db_lex, db_suff, ans_clt_lft,no_of_ans_left);
			sprintf(logmsg, "INFO:after fun morph |left=%s|cate=%s|root=%s|", test_left,category,ans_clt_lft[0].root); PRINT_LOG(log_file, logmsg);
			//sprintf(logmsg, "INFO:after fun morph |%s|%d|%d|%d|", test_left,DBM_FLAG,db_suff,db_lex); PRINT_LOG(log_file, logmsg);
			}
			//printf("INFO: answer array before fun morph |%s|%d|%s|\n", ans_clt_lft[0].root, ans_clt_lft[0].offset, ans_clt_lft[0].pdgm);
			char root[BigArray], cat[BigArray],
			     g[BigArray],n[BigArray],
			     p[BigArray], kase[BigArray],
			     //cm[BigArray], tam[BigArray] ;
			      cm[BigArray] ;
			char catl[BigArray],rulecatl[BigArray],cattemp[BigArray];
						memset(rulecatl,'\0',sizeof(rulecatl));
						memset(catl,'\0',sizeof(catl));
			//sprintf(logmsg, "INFO: after clitic-fun morph result root=|%s|offset=|%d|pdgm=|%s|test_left=|%s|", ans_clt_lft[0].root, ans_clt_lft[0].offset, ans_clt_lft[0].pdgm,test_left); PRINT_LOG(log_file, logmsg);

			//resufun_hori(ans_clt_lft[0].root,ans_clt_lft[0].pdgm,ans_clt_lft[0].offset,ans_clt_lft[0].aux_verb,root, cat, g,n,p, kase,cm, tam );
			strcat(tam,"_");
			//printf("word=|%s| suff=|%s|\n",input_word,right_word_tmp);
			len = strlen(input_word);
			strcpy(suffix_1,input_word+len-1);
			strcpy(suffix_2,input_word+len-2);
			strcpy(suffix_3,input_word+len-4);
			//printf("word=|%s|suff=|%s|suff2=|%s|suff3=|%s|\n",input_word,suffix_1,suffix_2,suffix_3);
			//printf("tam=|%s|\n",tam);
			//printf("word=|%s|suff2=|%s|\n",input_word,suffix_2);
			if((strcmp(suffix_2,"le"))==0)// || (strcmp(suffix_2,"gAni"))==0||(strcmp(suffix_2,"A"))==0|| (strcmp(suffix_2,"e"))==0 || (strcmp(suffix_2,"i"))==0 || (strcmp(suffix_2,"I"))==0|| (strcmp(suffix_2,"o"))==0||(strcmp(suffix_2,"U")==0)) {
			{
			//printf("word=|%s|suff2=|%s|\n",input_word,suffix_2);
			strcat(tam,suffix_2);
			}
			else if( (strcmp(suffix_3,"gAni"))==0)//||(strcmp(suffix_3,"A"))==0|| (strcmp(suffix_3,"e"))==0 || (strcmp(suffix_3,"i"))==0 || (strcmp(suffix_3,"I"))==0||(strcmp(suffix_3,"o"))==0|| (strcmp(suffix_3,"U")==0)) {
			{
			strcat(tam,suffix_3);
		}
			else if((strcmp(suffix_1,"A"))==0 || (strcmp(suffix_1,"e"))==0 || (strcmp(suffix_1,"i"))==0 || (strcmp(suffix_1,"o"))==0 || (strcmp(suffix_1,"I"))==0 || (strcmp(suffix_1,"u")==0)||(strcmp(suffix_1,"U"))==0) {
			//printf("word=|%s|suff2=|%s|\n",input_word,suffix_2);
			strcat(tam,suffix_1);
			}
			else {
			}
			//memset(suffix_1,"\0",sizeof(suffix_1));
			//memset(suffix_2,"\0",sizeof(suffix_2));
			strcpy(suffix_1,"\0");
			strcpy(suffix_2,"\0");
		//printf("tam=|%s|\n",tam);
			//strcat(tam,right_word_tmp);
			//sprintf(logmsg, "INFO: after CC-resufun_hori result |%s|%s|%s|%s|%s|\n", root, cat, n,tam,cm); PRINT_LOG(log_file, logmsg);
		//printf("|%d|\n",strlen(ans_clt_lft[0].root));
		//printf("|%d|\n",strlen(ans_clt_lft[0].pdgm));
		//memset(right_word_tmp,'\0',sizeof(right_word_tmp));	
			sprintf(logmsg, "INFO: after clitic-fun morph result root=|%s|offset=|%d|pdgm=|%s|test_left=|%s|tam=|%s|", ans_clt_lft[0].root, ans_clt_lft[0].offset, ans_clt_lft[0].pdgm,test_left,tam); PRINT_LOG(log_file, logmsg);
	if((strlen(ans_clt_lft[0].root)!=0) && (strlen(ans_clt_lft[0].pdgm)!=0)) {
	//printf("inputword=|%s|\n",input_word);
	return 1;
	}
	//else
	//return 0;
		memset(tam,'\0',sizeof(tam));	
		}
	}
	memset(clt_lft_word,'\0',sizeof(clt_lft_word));
	memset(ans_clt_lft,'\0',sizeof(ans_clt_lft));
	return 0;

//	clt_lft_word='\0';
        //printf("LEFT  -- %s\n", clt_lft_word);
//	fp_pdgm='\0';
}
