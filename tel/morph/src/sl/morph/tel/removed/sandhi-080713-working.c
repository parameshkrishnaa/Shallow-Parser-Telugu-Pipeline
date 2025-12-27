#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <fcntl.h>
#include <unistd.h>
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
extern int clitic_morph();
extern void read_clitics();

int sandhi_split (char *input_word, struct sandhi_rule_pool *rule_pool,
		FILE * fp_pdgm, int DBM_FLAG, GDBM_FILE db_lex,
		GDBM_FILE db_suff, char *lft_word, char *rt_word, struct ans_struct *ans_ar_left,struct ans_struct *ans_ar_right,
		int* no_of_ans_left, int* no_of_ans_right,int *split_flag)
{
	// int split_pos = 0;
	int pattern_matched[rule_pool->no_of_rules];
	int i, j, k;
	char left_word_tmp[50], right_word_tmp[50];
	char category[BigArray];

	for (i = 0; i < rule_pool->no_of_rules - 3; i++)
	{				// for every rule in rule pool
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

		if (pattern_matched[i] == 1) {
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
			memset(test_left,'\0',50);
			memset(test_right,'\0', 50);
			left_word_tmp[strlen (left_word_tmp) -
				atoi (rule_pool->rule[i].lft_dlt)] = '\0';
			strcpy (test_left, "");
			strcat (test_left, left_word_tmp);
			

			strcat (test_left, rule_pool->rule[i].lft_add);
			
			strcat (test_right, rule_pool->rule[i].rt_add);
			//printf("test_left=|%s|\ttest_right=|%s|\n",test_left,test_right);
			strcat (test_right, right_word_tmp + atoi (rule_pool->rule[i].rt_dlt));

			sprintf(logmsg,"pattern no is %s, and pattern is %s,spliting is at=%d, matched left word is=%s, right word is=%s\n",
					rule_pool->rule[i].rl_no, rule_pool->rule[i].pat,
					split_pos[0].rm_so, test_left, test_right); PRINT_LOG(log_file, logmsg);



			memset(ans_ar_left, '\0', sizeof(struct ans_struct)*BigArray);
			memset(ans_ar_right, '\0',sizeof(struct ans_struct)*BigArray);

			sprintf(logmsg, "INFO: answer array before fun morph |%s|%d|%s|\n", ans_ar_left[0].root, ans_ar_left[0].offset, ans_ar_left[0].pdgm); PRINT_LOG(log_file, logmsg);
			//printf("INFO: answer array after fun morph |%s|%d|%s|\n", test_left, ans_ar_left[0].offset, ans_ar_left[0].pdgm);
			//fun_morph (test_left, fp_pdgm, DBM_FLAG, db_lex, db_suff, ans_ar_left,no_of_ans_left);
			fun_morph (test_left,category, fp_pdgm, DBM_FLAG, db_lex, db_suff, ans_ar_left,no_of_ans_left);
			int ret_clitic=0,no_of_ans_clt_lft;;
			char lft_word1[50],tam[BigArray],tam_clitic[10];
			char temp_root[BigArray];
			struct clitic_rule_pool clitic_pool;
			struct ans_struct *ans_clt_lft;
			sprintf(logmsg, "INFO: answer array after fun morph |%s|%d|%s|\n", ans_ar_left[0].root, ans_ar_left[0].offset, ans_ar_left[0].pdgm); PRINT_LOG(log_file, logmsg);
			//printf("ans_ar_left[0].offset=%d|word=%s|pdgm=%s|\n",ans_ar_left[0].offset,test_left,ans_ar_left[0].pdgm);
			//printf("pdgm=|%s|strlen(pdgm)=|%d|\n",ans_ar_left[0].pdgm,strlen(ans_ar_left[0].pdgm));
			strcpy(temp_root,ans_ar_left[0].root);
			if(ans_ar_left[0].pdgm !='\0'){//&& ans_ar_left[0].offset==-2) {
			//if(strlen(ans_ar_left[0].pdgm)==0) {
			read_clitics ("../../../../data_src/sl/morph/tel/pc_data/clitics-rls", &clitic_pool);
		sprintf(logmsg,"before cli_str in sandhi_splitter test_left=|%s|lft_word1=|%s|ans_ar_left[0].root=|%s|\n",test_left,lft_word1,ans_ar_left[0].root);PRINT_LOG(log_file,logmsg);
		ret_clitic=clitic_morph(test_left,&clitic_pool,fp_pdgm,DBM_FLAG,db_lex,db_suff,lft_word1,ans_ar_left,tam,&no_of_ans_clt_lft);
		sprintf(logmsg,"after cli_str in sandhi_splitter test_left=|%s|lft_word1=|%s|ans_ar_left[0].root=|%s|offset=|%d|\n",test_left,lft_word1,ans_ar_left[0].root,ans_ar_left[0].offset);PRINT_LOG(log_file,logmsg);
		if(ret_clitic == 1) {
                strcpy(tam_clitic,tam); //Nagaraju-070613 for clitic info
                //int flag_unk=2;
                	}
			else {
			memset(ans_ar_left[0].root,'\0',sizeof(ans_ar_left[0].root));
			memset(ans_ar_left[0].pdgm,'\0',sizeof(ans_ar_left[0].pdgm));
			memset(ans_ar_left[0].aux_verb,'\0',sizeof(ans_ar_left[0].aux_verb));
			}
		strcpy(ans_ar_left[0].root,temp_root);
		}
			//printf("ans_ar_left[0].offset=%d|word=%s|pdgm=%s|\n",ans_ar_left[0].offset,test_left,ans_ar_left[0].pdgm);
			//printf("ans_ar_left[0].offset=%d|\n",ans_ar_left[0].offset);
			char root[BigArray], cat[BigArray],
			     g[BigArray],n[BigArray],
			     p[BigArray], kase[BigArray],
			     cm[BigArray];//, tam[BigArray] ;
			char catl[BigArray],catr[BigArray],rulecatl[BigArray],rulecatr[BigArray],cattemp[BigArray];
						memset(rulecatr,'\0',sizeof(rulecatr));
						memset(rulecatl,'\0',sizeof(rulecatl));
						memset(catl,'\0',sizeof(catl));
						memset(catr,'\0',sizeof(catr));
			sprintf(logmsg, "INFO: after SS-fun morph result |%s|%d|%s|%s|%s|\n", ans_ar_left[0].root, ans_ar_left[0].offset, ans_ar_left[0].pdgm,test_left,tam); PRINT_LOG(log_file, logmsg);

			memset(tam,'\0',sizeof(tam));
			resufun_hori(ans_ar_left[0].root,ans_ar_left[0].pdgm,ans_ar_left[0].offset,ans_ar_left[0].aux_verb,root, cat, g,n,p, kase,cm, tam );
			//strcat(tam,tam_clit);
			sprintf(logmsg, "INFO: after SS-resufun_hori result |%s|%s|%s|%s|\n", root, cat, n,tam); PRINT_LOG(log_file, logmsg);
			int ci,cj;
			char cond_word[20];
			strcpy(cond_word,cat);
			
			strcpy(catl,cat);
			strcat(cat,",");
			strcat(cat,tam);		
			strcpy(catr,tam);
				sprintf(logmsg, "INFO: left conditions expected are |%s|%s|\n",cat, rule_pool->rule[i].lft_cond); PRINT_LOG(log_file, logmsg);
				strcpy(cattemp,rule_pool->rule[i].lft_cond);
				ci=cj=0;
				for(ci=0;ci<strlen(cattemp);ci++){
					if(cattemp[ci]==','){
						strcpy(rulecatl,rulecatr);
						memset(rulecatr,'\0',sizeof(rulecatr));
						cj=0;
					}
					else
						rulecatr[cj++]=cattemp[ci];
				}
				if(strcmp(rulecatl,"")==0){
					
						strcpy(rulecatl,rulecatr);
						memset(rulecatr,'\0',sizeof(rulecatr));
					}
		
				sprintf(logmsg, "Splitting words1  |%s|%s|%s|%s|\n",catl, rulecatl, catr,rulecatr); PRINT_LOG(log_file, logmsg);

				if((strcmp(cat, rule_pool->rule[i].lft_cond)==0 || strcmp(catl,rulecatl)==0 || strcmp(catr,rulecatr)==0)&& (strcmp(cat,",")==1))   {

				sprintf(logmsg, "INFO:this is if  left condition matched |%s|%s|%s|%s|\n",root, cat, rule_pool->rule[i].lft_cond,test_left); PRINT_LOG(log_file, logmsg);
				strcpy(lft_word,test_left);
				strcpy(rt_word, test_right);


				memset(ans_ar_right, '\0', sizeof(struct ans_struct)*2);

				sprintf(logmsg, "INFO: answer array before right fun morph |%s|%d|%s|\n", ans_ar_right[0].root, ans_ar_right[0].offset, ans_ar_right[0].pdgm); PRINT_LOG(log_file, logmsg);
				//fun_morph (test_right, fp_pdgm, DBM_FLAG, db_lex, db_suff, ans_ar_right,no_of_ans_right);
				fun_morph (test_right,category, fp_pdgm, DBM_FLAG, db_lex, db_suff, ans_ar_right,no_of_ans_right);

				memset(root, '\0', BigArray);
				memset(cat, '\0', BigArray);
				memset(g, '\0', BigArray);
				memset(n, '\0', BigArray);
				memset(kase, '\0', BigArray);
				memset(cm, '\0', BigArray);
				memset(tam, '\0', BigArray);

				resufun_hori(ans_ar_right[0].root,ans_ar_right[0].pdgm,ans_ar_right[0].offset,ans_ar_right[0].aux_verb,root, cat, g,n,p,kase,cm,tam);
				sprintf(logmsg, "INFO: after fun morph for right word result |%s|%d|%s|%s|\n", ans_ar_right[0].root, ans_ar_right[0].offset, ans_ar_right[0].pdgm,test_right); PRINT_LOG(log_file, logmsg);
				sprintf(logmsg, "INFO: after resufun_hori right word result |%s|%s|%s|%s|\n", root, cat,n,tam); PRINT_LOG(log_file, logmsg);

				memset(cond_word, '\0',20);
				strcpy(cond_word,cat);
				strcat(cat,",");
				strcat(cat,tam);
				sprintf(logmsg, "INFO: right conditions expected are |%s|%s|\n",cat, rule_pool->rule[i].rt_cond); PRINT_LOG(log_file, logmsg);
			if( strcmp(cat, rule_pool->rule[i].rt_cond)==0 ) {
					sprintf(logmsg, "INFO:if if right right condition matched right |%s|%s|%s|%s|\n",root, cat, rule_pool->rule[i].rt_cond,test_right); PRINT_LOG(log_file, logmsg);
					strcpy(lft_word,test_left);
					strcpy(rt_word, test_right);					
					sprintf(logmsg, "INFO: split is successful |%s|%s|\n",lft_word,rt_word); PRINT_LOG(log_file, logmsg);
			split_flag=1;	
				return 1;
		}

else if(strcmp(cat,",")==0){ continue; }
					else  {
					sprintf(logmsg, "INFO:if right else right condition matched right |%s|%s|%s|%s|\n",root, cat, rule_pool->rule[i].rt_cond,test_right); PRINT_LOG(log_file, logmsg);
					strcpy(lft_word,test_left);
					strcpy(rt_word, test_right);					
					sprintf(logmsg, "INFO: split is successful |%s|%s|\n",lft_word,rt_word); PRINT_LOG(log_file, logmsg);
			split_flag=1;	
				return 1;
				}
						}
		}
	}
	memset(lft_word,'\0',sizeof(lft_word));
	memset(rt_word,'\0',sizeof(rt_word));
	memset(ans_ar_left,'\0',sizeof(ans_ar_left));
	memset(ans_ar_right,'\0',sizeof(ans_ar_right));
//	lft_word='\0';
//	rt_word='\0';
        //printf("LEFT  -- %s\n", lft_word);
        //printf("RIGHT  -- %s\n",rt_word);
        //
//	fp_pdgm='\0';
}
