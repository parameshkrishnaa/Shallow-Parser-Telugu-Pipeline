#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <fcntl.h>
#include "substr.c"
#include "split_arr.c"
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
#define FUNCTION "sandhi_splitter()"





extern void *my_fatal();
extern void fun_morph();


int sandhi_split (char *input_word, struct sandhi_rule_pool *rule_pool,
		FILE * fp_pdgm, int DBM_FLAG, GDBM_FILE db_lex,
		GDBM_FILE db_suff, char *left_word, char *right_word,struct ans_struct *ans_ar_left, struct ans_struct *ans_ar_right,
		int* no_of_ans_left, int* no_of_ans_right);
void read_rules (char *rule_file_name, struct sandhi_rule_pool *rule_pool);


/*
	int
main (int argc, char *argv[])
{
	//  struct sandhi temp_out;
	struct sandhi_rule_pool rule_pool;
	char lft_word[50], rt_word[50];
	FILE *fp;
	char *line = NULL;
	size_t len = 0, read;

	FILE *fp_pdgm;
	int DBM_FLAG;
	GDBM_FILE db_lex;
	GDBM_FILE db_suff;
*/
	/* checks for paradigm file can be opened or not */
/*	if ((fp_pdgm = fopen ("/pdgm_offset_info", "r")) == NULL)
	{
		printf ("Error in opening pdgm_offset_info file\n ");
		exit (0);
	}
	DBM_FLAG =1;
	if (DBM_FLAG)
	{
		//      strcpy (fname, fpath_dict);
		db_lex = gdbm_open ("dict-tel", 512, GDBM_READER, 0666, my_fatal ());

		//      strcpy (fname, fpath);
		//      strcat (fname, "/suff");
		db_suff = gdbm_open ("/suff", 512, GDBM_READER, 0666, my_fatal ());

		//      strcpy (fname, fpath);
		//      strcat (fname, "/uword");
		//      db_uword = gdbm_open ("/uword"fname, 512, GDBM_READER, 0666, my_fatal ());

	}





	read_rules ("rls", &rule_pool);

	sandhi_split ("abaxXamannamAta", &rule_pool, fp_pdgm, DBM_FLAG, db_lex,
			db_suff, lft_word, rt_word);
	sandhi_split ("abaxXamaMtAvA", &rule_pool, fp_pdgm, DBM_FLAG, db_lex,
			db_suff, lft_word, rt_word);
	sandhi_split ("aBAvAwmakamEwe", &rule_pool, fp_pdgm, DBM_FLAG, db_lex,
			db_suff, lft_word, rt_word);
	sandhi_split ("aBAvAwmakamE", &rule_pool, fp_pdgm, DBM_FLAG, db_lex,
			db_suff, lft_word, rt_word);
	sandhi_split ("aBAvArWakamEnappatiki", &rule_pool, fp_pdgm, DBM_FLAG,
			db_lex, db_suff, lft_word, rt_word);
	sandhi_split ("aBAvArWakamavuwuMxi", &rule_pool, fp_pdgm, DBM_FLAG, db_lex,
			db_suff, lft_word, rt_word);
	sandhi_split ("aBAvamugala", &rule_pool, fp_pdgm, DBM_FLAG, db_lex, db_suff,
			lft_word, rt_word);
	sandhi_split ("ABaraNAlannI", &rule_pool, fp_pdgm, DBM_FLAG, db_lex,
			db_suff, lft_word, rt_word);

	fp = fopen ("ss.rin", "r");
	if (fp == NULL)
	{
		printf ("File cannot be opened\n");
		exit (0);
	}

	while ((read = getline (&line, &len, fp)) != -1)
	{
		printf ("Retrieved line of length %zu :", read);
		printf ("%s\n", line);
		sandhi_split (line, &rule_pool, fp_pdgm, DBM_FLAG, db_lex, db_suff,
				lft_word, rt_word);
		printf
			("\n****#################*************################************###########\n");
	}

	if (line)
		free (line);
	fclose (fp);


	return 0;
}
*/
	void
read_rules (char *rule_file_name, struct sandhi_rule_pool *rule_pool)
{
	FILE *fp;
	//array size is changed by Paramesh
//	char rls[700][100], ss[100];
	char rls[1000][200], ss[100];
	int size_of_rls = 0, i, j;
	char san[15][50];

	fp = fopen (rule_file_name, "r");
	if (fp == NULL)
	{
//		printf ("File cannot be opened\n");
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
				(size_of_rls - 3));


	for (j = 3; j < size_of_rls; j++)
	{
		for (i = 0; i < 10; i++)
		{
			strcpy (san[i], "\0");
		}			// this is for delete previous value  

		//      strcpy (temp, rls[j]);
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


	int
sandhi_split (char *input_word, struct sandhi_rule_pool *rule_pool,
		FILE * fp_pdgm, int DBM_FLAG, GDBM_FILE db_lex,
		GDBM_FILE db_suff, char *lft_word, char *rt_word, struct ans_struct *ans_ar_left,struct ans_struct *ans_ar_right,
		int* no_of_ans_left, int* no_of_ans_right)
{
	// int split_pos = 0;
	int pattern_matched[rule_pool->no_of_rules];
	int i, j, k;
	char left_word_tmp[50], right_word_tmp[50];

	for (i = 0; i < rule_pool->no_of_rules - 3; i++)
	{				// for every rule in rule pool
		pattern_matched[i] = 0;
		int status;
		regex_t re;
		regmatch_t split_pos[2];
		
		size_t no_of_matches = 1;
		if ((regcomp (&re, rule_pool->rule[i].pat, REG_EXTENDED) != 0))
		{
			pattern_matched[i] = 0;
			break;
		}
		status = regexec (&re, input_word, no_of_matches, split_pos, 0);
		regfree (&re);
		if (status != 0)
		{
			pattern_matched[i] = 0;
		}
		else
			pattern_matched[i] = 1;

		if (pattern_matched[i] == 1)
		{
			strcpy(left_word_tmp,"");
			if (split_pos[0].rm_so == 0)
			{
				substr (input_word, 0, split_pos[0].rm_eo, left_word_tmp);
				substr (input_word, split_pos[0].rm_eo, strlen (input_word),
						right_word_tmp);
			}
			else
			{
				substr (input_word, 0,
						split_pos[0].rm_so + atoi (rule_pool->rule[i].br_pt),
						left_word_tmp);
				substr (input_word,
						split_pos[0].rm_so + atoi (rule_pool->rule[i].br_pt),
						strlen (input_word), right_word_tmp);
			}

			char test_left[50],test_right[50];
			memset(test_left, '\0',50);
			memset(test_right, '\0', 50);
			left_word_tmp[strlen (left_word_tmp) -
				atoi (rule_pool->rule[i].lft_dlt)] = '\0';
//			printf("left word tmep %s\n",left_word_tmp);
			strcpy (test_left, "");
			strcat (test_left, left_word_tmp);
			
			//paramesh
		//	int k;
			//for (k = 0; k < rule_pool->no_of_rules - 3; i++) {
	 		//regex_t re2;
			//char buffer[1024];
			//if (regcomp(&re2,  rule_pool->rule[i].lft_add, 0) != 0)
			  //  { /* failed */ }
		//	int status = regexec(&re, buffer, (size_t) 0, NULL, 0);
		//	regfree(&re);

			strcat (test_left, rule_pool->rule[i].lft_add);
//			printf ("st-left--adding left--%s\n",rule_pool->rule[i].lft_add);
		//	}
			//paramesh
			
			strcat (test_right, rule_pool->rule[i].rt_add);
			strcat (test_right, right_word_tmp + atoi (rule_pool->rule[i].rt_dlt));

			// blocked by chris
			// printf("pattern no is %s, and pattern is %s,spliting is at=%d, matched left word is=%s, right word is=%s\n,left condition is |%s| ",rule_pool->rule[i].rl_no, rule_pool->rule[i].pat, split_pos[0].rm_so, test_left, test_right,rule_pool->rule[i].lft_cond);
			sprintf(logmsg,"pattern no is %s, and pattern is %s,spliting is at=%d, matched left word is=%s, right word is=%s\n",
					rule_pool->rule[i].rl_no, rule_pool->rule[i].pat,
					split_pos[0].rm_so, test_left, test_right); PRINT_LOG(log_file, logmsg);


			//              call for fun_morph

			memset(ans_ar_left, '\0', sizeof(struct ans_struct)*BigArray);
			memset(ans_ar_right, '\0',sizeof(struct ans_struct)*BigArray);

			sprintf(logmsg, "INFO: answer array before fun morph |%s|%d|%s|\n", ans_ar_left[0].root, ans_ar_left[0].offset, ans_ar_left[0].pdgm); PRINT_LOG(log_file, logmsg);
			fun_morph (test_left, fp_pdgm, DBM_FLAG, db_lex, db_suff, ans_ar_left,no_of_ans_left);

			char root[BigArray], cat[BigArray],
			     g[BigArray],n[BigArray],
			     p[BigArray], kase[BigArray],
			     cm[BigArray], tam[BigArray] ;

			resufun_hori(ans_ar_left[0].root,ans_ar_left[0].pdgm,ans_ar_left[0].offset,ans_ar_left[0].aux_verb,root, cat, g,n,p, kase,cm, tam );
			sprintf(logmsg, "INFO: after fun morph result |%s|%d|%s|%s|\n", ans_ar_left[0].root, ans_ar_left[0].offset, ans_ar_left[0].pdgm,test_left); PRINT_LOG(log_file, logmsg);
			sprintf(logmsg, "INFO: after resufun_hori result |%s|%s|%s|%s|\n", root, cat, n,tam); PRINT_LOG(log_file, logmsg);

			char cond_word[20];
			strcpy(cond_word,cat);
			strcat(cat,",");
			strcat(cat,tam);		
				sprintf(logmsg, "INFO: left conditions expected are |%s|%s|\n",cat, rule_pool->rule[i].lft_cond); PRINT_LOG(log_file, logmsg);
			if( strcmp(cat, rule_pool->rule[i].lft_cond)==0 ) {
				sprintf(logmsg, "INFO: left condition matched |%s|%s|%s|%s|\n",root, cat, rule_pool->rule[i].lft_cond,test_left); PRINT_LOG(log_file, logmsg);
				strcpy(lft_word,test_left);
				strcpy(rt_word, test_right);


				//   for right word
				memset(ans_ar_right, '\0', sizeof(struct ans_struct)*2);

				sprintf(logmsg, "INFO: answer array before right fun morph |%s|%d|%s|\n", ans_ar_right[0].root, ans_ar_right[0].offset, ans_ar_right[0].pdgm); PRINT_LOG(log_file, logmsg);
				fun_morph (test_right, fp_pdgm, DBM_FLAG, db_lex, db_suff, ans_ar_right,no_of_ans_right);

				memset(root, '\0', BigArray);
				memset(cat, '\0', BigArray);
				memset(g, '\0', BigArray);
				memset(n, '\0', BigArray);
				memset(tam, '\0', BigArray);

				resufun_hori(ans_ar_right[0].root,ans_ar_right[0].pdgm,ans_ar_right[0].offset,ans_ar_right[0].aux_verb,root, cat, g,n,p, kase,cm, tam );
				sprintf(logmsg, "INFO: after fun morph for right word result |%s|%d|%s|%s|\n", ans_ar_right[0].root, ans_ar_right[0].offset, ans_ar_right[0].pdgm,test_right); PRINT_LOG(log_file, logmsg);
				sprintf(logmsg, "INFO: after resufun_hori right word result |%s|%s|%s|%s|\n", root, cat, n,tam); PRINT_LOG(log_file, logmsg);

				memset(cond_word, '\0',20);
				strcpy(cond_word,cat);
				strcat(cat,",");
				strcat(cat,tam);
				sprintf(logmsg, "INFO: right conditions expected are |%s|%s|\n",cat, rule_pool->rule[i].rt_cond); PRINT_LOG(log_file, logmsg);
				if( strcmp(cat, rule_pool->rule[i].rt_cond)==0 ) {
					sprintf(logmsg, "INFO: right condition matched right |%s|%s|%s|%s|\n",root, cat, rule_pool->rule[i].rt_cond,test_right); PRINT_LOG(log_file, logmsg);
					strcpy(lft_word,test_left);
					strcpy(rt_word, test_right);					
					sprintf(logmsg, "INFO: split is successful |%s|%s|\n",lft_word,rt_word); PRINT_LOG(log_file, logmsg);
					return 1;
				}
			}


			//	fun_morph (rt_word, fp_pdgm, DBM_FLAG, db_lex, db_suff, ans_ar);
			//	printf("fun morph done for right word and offset is %d\n",ans_ar[0].offset);
			//	sprintf(logmsg, "INFO: right word morph result |%s|%d|%s|", ans_ar[0].root, ans_ar[0].offset, ans_ar[0].pdgm); PRINT_LOG(log_file, logmsg);

			//        strcpy (lft_word, left_word_tmp);
			//        strcpy (rt_word, right_word_tmp);
			//              return 0;
		}
	}
	lft_word='\0';
	rt_word='\0';

}
