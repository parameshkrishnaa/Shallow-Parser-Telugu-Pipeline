/**
 * File Name:comp_verb_heuristics.c
*/

/** comp_verb_heuristics
 * This function compares with the suffixes and if there are not equal with the given suffix
 * then they are copied into the suffixes respectively
 * It takes arguments:
 * root of char type ,paradigm  char type, comp_verbs char type,
 * Return void
 */

/*  HEADER FILES   */
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "./headers/defn.h"
#include "./common/analyser/morph_logger.h"


//extern FILE *log_file;

extern FILE *log_file;
extern char *program_name;
extern char *logmsg;
//#define FUNCTION "fun_morph()"
#define FUNCTION "comp_verb_heuristics()"



void comp_verb_heuristics(root,pdgm,comp_verbs)

/* root word */
char root[SUFFWORDSIZE];            

/* paradigm */
char pdgm[WORD_SIZE];               

/* compound verbs */
char comp_verbs[Arraysize];                
{ 
//	char *program_name="comp_verb_heuristics.c"; 
//	PRINT_LOG(log_file, "compares with the suffixes and if there are not equal \
				with the given suffix then they are copied into the suffixes respectively "); 


	/* different suffixes  */ 
	char suffix_3[4],suffix_4[5],suffix_2[3]; 
	char suffix_5[6],suffix_6[7],suffix_7[8],suffix_8[9], \
			suffix_9[10],suffix_10[11],suffix_11[12]; 

	/* temporary suffix */ 
	char tmp[SUFFWORDSIZE];   

	/* length of root */
	int len;                  
	//comp_verbs = '\0';
	 len = strlen(root); 
	if(len>=2) strcpy(suffix_2 , root+len-2);    else strcpy(suffix_2,""); 
	if(len>=3) strcpy(suffix_3 , root+len-3);    else strcpy(suffix_3,""); 
	if(len>=4) strcpy(suffix_4 , root+len-4);    else strcpy(suffix_4,""); 
	if(len>=5) strcpy(suffix_5 , root+len-5);    else strcpy(suffix_5,""); 
	if(len>=6) strcpy(suffix_6 , root+len-6);    else strcpy(suffix_6,""); 
	if(len>=7) strcpy(suffix_7 , root+len-7);    else strcpy(suffix_7,""); 
	if(len>=8) strcpy(suffix_8 , root+len-8);    else strcpy(suffix_8,""); 
	if(len>=9) strcpy(suffix_9 , root+len-9);    else strcpy(suffix_9,""); 
	if(len>=10) strcpy(suffix_10 , root+len-10); else strcpy(suffix_10,""); 
	if(len>=11) strcpy(suffix_11 , root+len-11); else strcpy(suffix_11,""); 

	
	//sprintf(logmsg, "NAGARAJ INFO: Entering comp_verb_heuristics"); PRINT_LOG(log_file,logmsg);	
	//comp_verbs = '\0'; 
	comp_verbs[0] = '\0'; 
	
		    FILE *fp;
			char buff[1000];
			int size_of_file=0,j,i;
			char words[1000][200];
			char wrd[15][50];
	char comp_file[BigArray];
	strcpy(comp_file,getenv("setu"));
	strcat(comp_file, "/morph/data_bin/sl/morph/tel/derivation/derived_comp_verbs.p");
		//fp=fopen("derivation/derived_comp_verbs.p","r");
		//fp=fopen("/home/guest/oldmorph/data_bin/sl/morph/tel/derivation/derived_comp_verbs.p","r");
		//fp=fopen("/home/guest/oldmorph/data_src/sl/morph/tel/pc_data/derivation/derived_comp_verbs.p","r");
		//fp=fopen("/var/www/html/morph/telmorph/data_src/sl/morph/tel/pc_data/derivation/derived_comp_verbs.p","r");
		//fp=fopen("../../../../data_src/sl/morph/tel/pc_data/derivation/derived_comp_verbs.p","r");
		fp=fopen(comp_file,"r");
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
                        //sprintf(logmsg,"The file derived_comp_verb.p cannot be opened\n");
			PRINT_LOG(logmsg,log_file);
                        exit(0);}
			fclose(fp);
		//Nagaraju
		for(j=0;j<size_of_file;j++) { 
		for(i=0;i<3;i++){
		strcpy(wrd[i],"\0");}
		split_arr(words[j],' ',wrd);
		//printf("%s|%s|%s\n",wrd[0],wrd[1],wrd[2]);
	//printf("suff_5=%s|wrd0=%s|\n",suffix_5,wrd[0]);
//
	//if((!strcmp(suffix_4,"koVn") || (!strcmp(suffix_2,"ko"))) && !strcmp(pdgm,"kUrco") && ( len > 4 )&&(strlen(comp_verbs)==0)) 
	if((!strcmp(suffix_4,wrd[0]) || (!strcmp(suffix_2,wrd[0]))) && !strcmp(pdgm,wrd[1]) && ( len > 4 )&&(strlen(comp_verbs)==0)) {
		//strcpy(comp_verbs,"koVn"); 
		strcpy(comp_verbs,wrd[2]); 
	//sprintf(logmsg, "NAGARAJ INFO: suffix_4=%s|suffix_2=%s|pdgm=%s|comp_verb=%s|",suffix_4,suffix_2,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if((!strcmp(suffix_8,"akavuMdu") || (!strcmp(suffix_6,"akuMdu"))) && !strcmp(pdgm,"uMdu")&&(strlen(comp_verbs)==0)) 
	else if((!strcmp(suffix_8,wrd[0]) || (!strcmp(suffix_6,wrd[0]))) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
		//strcpy(comp_verbs,"aka_uMdu"); 
		strcpy(comp_verbs,wrd[2]); 
	//sprintf(logmsg, "NAGARAJ INFO: suffix_8=%s|suffix_6=%s|pdgm=%s|comp_verb=%s|",suffix_8,suffix_6,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	} 
	//else if((!strcmp(suffix_8,"okavuMdu") || (!strcmp(suffix_6,"okuMdu"))) && !strcmp(pdgm,"uMdu")&&(strlen(comp_verbs)==0)) 
	/*else if((!strcmp(suffix_8,wrd[0]) || (!strcmp(suffix_6,wrd[0]))) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
		//strcpy(comp_verbs,"aka_uMdu"); 
		strcpy(comp_verbs,wrd[2]); 
	}*/
	//else if((!strcmp(suffix_8,"ekavuMdu") || (!strcmp(suffix_6,"ekuMdu"))) && !strcmp(pdgm,"uMdu")&&(strlen(comp_verbs)==0)) 
	else if((!strcmp(suffix_8,wrd[0]) || (!strcmp(suffix_6,wrd[0]))) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
		//strcpy(comp_verbs,"aka_uMdu"); 
		strcpy(comp_verbs,wrd[2]); 
	//sprintf(logmsg, "NAGARAJ INFO: suffix_8=%s|suffix_6=%s|pdgm=%s|comp_verb=%s|",suffix_8,suffix_6,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	} 
	//else if((!strcmp(suffix_8,"AkavuMdu") || (!strcmp(suffix_6,"AkuMdu"))) && !strcmp(pdgm,"uMdu")&&(strlen(comp_verbs)==0)) 
	else if((!strcmp(suffix_8,wrd[0]) || (!strcmp(suffix_6,wrd[0]))) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
		//strcpy(comp_verbs,"aka_uMdu"); 
		strcpy(comp_verbs,wrd[2]); 
	//sprintf(logmsg, "NAGARAJ INFO: suffix_8=%s|suffix_6=%s|pdgm=%s|comp_verb=%s|",suffix_8,suffix_6,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if((!strcmp(suffix_5,"akapo") || !strcmp(suffix_5,"ekapo") || !strcmp(suffix_5,"Akapo") || !strcmp(suffix_5,"okapo")) && !strcmp(pdgm,"po")&&(strlen(comp_verbs)==0)) 
	else if((!strcmp(suffix_5,wrd[0]))  && (!strcmp(pdgm,wrd[1]))&&(strlen(comp_verbs)==0)) {
		//strcpy(comp_verbs,"aka_po"); 
		//printf("iam here");
		strcpy(comp_verbs,wrd[2]); 
	//sprintf(logmsg, "NAGARAJ INFO: suffix_5=%s|pdgm=%s|comp_verb=%s|",suffix_5,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if((!strcmp(suffix_11,"akuMdAvuMdu") || (!strcmp(suffix_9,"akuMduMdu"))) && !strcmp(pdgm,"uMdu")&&(strlen(comp_verbs)==0))
	else if((!strcmp(suffix_11,wrd[0]) || (!strcmp(suffix_9,wrd[0]))) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  // strcpy(comp_verbs,"akuMdA_uMdu");
		strcpy(comp_verbs,wrd[2]); 
	//sprintf(logmsg, "NAGARAJ INFO: suffix_11=%s|suffix_9=%s|pdgm=%s|comp_verb=%s|",suffix_11,suffix_9,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if((!strcmp(suffix_11,"AkuMdAvuMdu") || (!strcmp(suffix_9,"AkuMduMdu"))) && !strcmp(pdgm,"uMdu")&&(strlen(comp_verbs)==0))
	/*else if((!strcmp(suffix_11,wrd[0]) || (!strcmp(suffix_9,wrd[0]))) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)){
	   //strcpy(comp_verbs,"akuMdA_uMdu");
		strcpy(comp_verbs,wrd[2]); 
	}*/
	//else if((!strcmp(suffix_11,"ekuMdAvuMdu") || (!strcmp(suffix_9,"ekuMduMdu"))) && !strcmp(pdgm,"uMdu")&&(strlen(comp_verbs)==0))
	/*else if((!strcmp(suffix_11,wrd[0]) || (!strcmp(suffix_9,wrd[0]))) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)){
	  //strcpy(comp_verbs,"akuMdA_uMdu");
		strcpy(comp_verbs,wrd[2]); 
	}
	//else if((!strcmp(suffix_11,"okuMdAvuMdu") || (!strcmp(suffix_9,"okuMduMdu"))) && !strcmp(pdgm,"uMdu")&&(strlen(comp_verbs)==0))
	else if((!strcmp(suffix_11,wrd[0]) || (!strcmp(suffix_9,wrd[0]))) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"akuMdA_uMdu");
		strcpy(comp_verbs,wrd[2]); 
	}*/
	//else if(!strcmp(suffix_10,"akuMdAcudu") && !strcmp(pdgm,"cUdu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_10,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"akuMdA_cUdu");
	  strcpy(comp_verbs,wrd[2]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_10=%s|pdgm=%s|comp_verb=%s|",suffix_10,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if(!strcmp(suffix_10,"AkuMdAcudu") && !strcmp(pdgm,"cUdu")&&(strlen(comp_verbs)==0))
	/*else if(!strcmp(suffix_10,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"akuMdA_cUdu");
	  strcpy(comp_verbs,wrd[2]);
	}*/
	//else if(!strcmp(suffix_10,"ekuMdAcudu") && !strcmp(pdgm,"cUdu")&&(strlen(comp_verbs)==0))
	/*else if(!strcmp(suffix_10,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"akuMdA_cUdu");
	  strcpy(comp_verbs,wrd[2]);
	}*/
	//else if(!strcmp(suffix_10,"okuMdAcudu") && !strcmp(pdgm,"cUdu")&&(strlen(comp_verbs)==0))
	/*else if(!strcmp(suffix_10,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"akuMdA_cUdu");
	  strcpy(comp_verbs,wrd[2]);
	}*/
	/*
	else if((!strcmp(suffix_6,"ivuMdu") || (!strcmp(suffix_4,"uMdu"))) && !strcmp(pdgm,"uMdu") && (len > 8) && (!strcmp(suffix_7,"uMtuMdu"))) 
	*/
	//else if(!strcmp(suffix_3,"ipo") && !strcmp(pdgm,"po")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_3,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"i_po");
	  strcpy(comp_verbs,wrd[2]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_3=%s|pdgm=%s|comp_verb=%s|",suffix_3,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if(!strcmp(suffix_3,"Epo") && !strcmp(pdgm,"po")&&(strlen(comp_verbs)==0))
	/*else if(!strcmp(suffix_3,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	 // strcpy(comp_verbs,"i_po");
	  strcpy(comp_verbs,wrd[2]);
	}*/
	//else if(!strcmp(suffix_5,"icUdu") && !strcmp(pdgm,"cUdu")&&(strlen(comp_verbs)==0))
	/*else if(!strcmp(suffix_5,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"i_cUdu");
	  strcpy(comp_verbs,wrd[2]);
	}
	//else if(!strcmp(suffix_5,"iwIru") && !strcmp(pdgm,"kAlu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_5,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"i_wIru");
	  strcpy(comp_verbs,wrd[2]);
	}*/
	//else if(!strcmp(suffix_7,"ipeVttu") && !strcmp(pdgm,"peVttu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_7,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"i_peVttu");
	  //printf("Iam here");
	  strcpy(comp_verbs,wrd[2]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_7=%s|pdgm=%s|comp_verb=%s|",suffix_7,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if(!strcmp(suffix_9,"ipAreVyyi") && !strcmp(pdgm,"ceVyyi")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_9,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"i_pAreVyyi");
	  strcpy(comp_verbs,wrd[2]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_9=%s|pdgm=%s|comp_verb=%s|",suffix_9,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if(((!strcmp(suffix_5,"eVyyi")  || !strcmp(suffix_4,"eyyi")) && (len > 6)) && !strcmp(pdgm,"ceVyyi")&&(strlen(comp_verbs)==0))
	else if(((!strcmp(suffix_5,wrd[0])  || !strcmp(suffix_4,wrd[0])) && (len > 6)) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"i_veVyyi");
	  strcpy(comp_verbs,wrd[2]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_5=%s|suffix_4=%s|pdgm=%s|comp_verb=%s|",suffix_5,suffix_4,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	/* cases for kupo/kuvuMdu/kucUdu/kuwIru/kupeVttu/kupAreVyyi/kuveVyyi :: ku->kuni */
	//else if((!strcmp(suffix_7,"kuvuMdu")) && !strcmp(pdgm,"uMdu") && (len > 9)&&(strlen(comp_verbs)==0))
	else if((!strcmp(suffix_7,wrd[0])) && !strcmp(pdgm,wrd[1]) && (len > 9)&&(strlen(comp_verbs)==0)) {
	  root[len-7] = '\0';
	  //strcat(root,"kunivuMdu");
	  strcat(root,wrd[2]);
	  //strcpy(comp_verbs,"i_uMdu");
	  strcpy(comp_verbs,wrd[3]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_7=%s|pdgm=%s|comp_verb=%s|",suffix_7,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if(!strcmp(suffix_4,"kupo") && !strcmp(pdgm,"po")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_4,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  root[len-4] = '\0';
	  //strcat(root,"kunipo");
	  strcat(root,wrd[2]);
	  //strcpy(comp_verbs,"i_po");
	  strcpy(comp_verbs,wrd[3]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_4=%s|pdgm=%s|comp_verb=%s|",suffix_4,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if(!strcmp(suffix_6,"kucUdu") && !strcmp(pdgm,"cUdu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_6,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  root[len-6] = '\0';
	  //strcat(root,"kunicUdu");
	  //strcpy(comp_verbs,"i_cUdu");
	  strcat(root,wrd[2]);
	  strcpy(comp_verbs,wrd[3]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_6=%s|pdgm=%s|comp_verb=%s|",suffix_6,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if(!strcmp(suffix_6,"kuwIru") && !strcmp(pdgm,"kAlu")&&(strlen(comp_verbs)==0))
	/*else if(!strcmp(suffix_6,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  root[len-6] = '\0';
	  //strcat(root,"kuniwIru");
	  //strcpy(comp_verbs,"i_wIru");
	  strcat(root,wrd[2]);
	  strcpy(comp_verbs,wrd[3]);
	}*/
	//else if(!strcmp(suffix_8,"kupeVttu") && !strcmp(pdgm,"peVttu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_8,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  root[len-8] = '\0';
	  //strcat(root,"kunipeVttu");
	  //strcpy(comp_verbs,"i_peVttu");
	  strcat(root,wrd[2]);
	
	  strcpy(comp_verbs,wrd[3]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_8=%s|pdgm=%s|comp_verb=%s|",suffix_8,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	}
	//else if(!strcmp(suffix_10,"kupAreVyyi") && !strcmp(pdgm,"ceVyyi")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_10,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  root[len-10] = '\0';
	  //strcat(root,"kunipAreVyyi");
	  //strcpy(comp_verbs,"i_pAreVyyi");
	  strcat(root,wrd[2]);
	  strcpy(comp_verbs,wrd[3]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_10=%s|pdgm=%s|comp_verb=%s|",suffix_10,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if((!strcmp(suffix_8,"kuveVyyi") && (len > 7)) && !strcmp(pdgm,"ceVyyi")&&(strlen(comp_verbs)==0))
	else if((!strcmp(suffix_8,wrd[0]) && (len > 7)) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  root[len-8] = '\0';
	  //strcat(root,"kuniveVyyi");
	  //strcpy(comp_verbs,"i_veVyyi");
	  strcat(root,wrd[2]);
	  strcpy(comp_verbs,wrd[3]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_8=%s|pdgm=%s|comp_verb=%s|",suffix_8,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if((!strcmp(suffix_6,"koVccu") && (len > 5)) && !strcmp(pdgm,"vaccu")&&(strlen(comp_verbs)==0))
	else if((!strcmp(suffix_6,wrd[0]) && (len > 5)) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  root[len-6] = '\0';
	  //strcat(root,"koVnivaccu");
	  //strcpy(comp_verbs,"i_vaccu");
	  strcat(root,wrd[2]);
	  strcpy(comp_verbs,wrd[3]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_6=%s|pdgm=%s|comp_verb=%s|",suffix_6,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if(!strcmp(suffix_6,"anivvu") && !strcmp(pdgm,"ivvu")&&(strlen(comp_verbs)==0))
	/*else if(!strcmp(suffix_6,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_ivvu");
	  strcpy(comp_verbs,wrd[2]);
	}
	//else if(!strcmp(suffix_6,"onivvu") && !strcmp(pdgm,"ivvu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_6,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_ivvu");
	  strcpy(comp_verbs,wrd[2]);
	}
	//else if(!strcmp(suffix_6,"Anivvu") && !strcmp(pdgm,"ivvu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_6,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_ivvu");
	  strcpy(comp_verbs,wrd[2]);
	}
	//else if(!strcmp(suffix_6,"enivvu") && !strcmp(pdgm,"ivvu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_6,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_ivvu");
	  strcpy(comp_verbs,wrd[2]);
	}
	//else if(!strcmp(suffix_6,"anuMdu") && !strcmp(pdgm,"uMdu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_6,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_uMdu");
	  strcpy(comp_verbs,wrd[2]);
	}
	//else if(!strcmp(suffix_6,"onuMdu") && !strcmp(pdgm,"uMdu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_6,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_uMdu");
	  strcpy(comp_verbs,wrd[2]);
	}
	//else if(!strcmp(suffix_6,"AnuMdu") && !strcmp(pdgm,"uMdu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_6,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_uMdu");
	  strcpy(comp_verbs,wrd[2]);
	}
	//else if(!strcmp(suffix_6,"enuMdu") && !strcmp(pdgm,"uMdu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_6,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_uMdu");
	  strcpy(comp_verbs,wrd[2]);
	}*/
	//else if(!strcmp(suffix_4,"wUpo") && !strcmp(pdgm,"po")&&(strlen(comp_verbs)==0))
	/*else if(!strcmp(suffix_4,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	 // strcpy(comp_verbs,"wU_po");
	  strcpy(comp_verbs,wrd[2]);
	}
	//else if(!strcmp(suffix_4,"mAnu") && !strcmp(pdgm,"Adu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_4,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"aka_mAnu");
	  strcpy(comp_verbs,wrd[2]);
	}*/
	//else if((!strcmp(suffix_7,"wUvaccu") || !strcmp(suffix_7,"tUvaccu")) && !strcmp(pdgm,"vaccu")&&(strlen(comp_verbs)==0))
	else if((!strcmp(suffix_7,wrd[0])) && (!strcmp(pdgm,wrd[1]))&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"wU_vaccu");
	  strcpy(comp_verbs,wrd[2]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_7=%s|pdgm=%s|comp_verb=%s|",suffix_7,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	/* This is stopped because of unnecessary answers of wArasapaduwunna,etc
	wArasapaduwunna : wArasapadu{v *wU_uMdu_pt_adjl* any } <- unnecessary
	wArasapadu{v *np_adjl* any }
	TEMP OPENED
	*/
	//else if((!strcmp(suffix_5,"wuMdu")|| !strcmp(suffix_5,"tuMdu")) && !strcmp(pdgm,"uMdu")&&(strlen(comp_verbs)==0))
	/*else if((!strcmp(suffix_5,wrd[0])) && (!strcmp(pdgm,wrd[1]))&&(strlen(comp_verbs)==0)) {
	 // strcpy(comp_verbs,"wU_uMdu");
	 //printf("Iam here");
	  strcpy(comp_verbs,wrd[2]);
	}*/
	/* Following case added by AMBA to handle wUvunnAdu case */
	//else if((!strcmp(suffix_7,"wUvuMdu") || !strcmp(suffix_7,"tUvuMdu")) && !strcmp(pdgm,"uMdu")&&(strlen(comp_verbs)==0))
	/*else if((!strcmp(suffix_7,wrd[0])) && (!strcmp(pdgm,wrd[1]))&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"wU_uMdu");
	  strcpy(comp_verbs,wrd[2]);
	}*/
	//else if((!strcmp(suffix_5,"wUMdu") || !strcmp(suffix_5,"tUMdu")) && !strcmp(pdgm,"uMdu")&&(strlen(comp_verbs)==0))
	/*else if((!strcmp(suffix_5,wrd[0])) && (!strcmp(pdgm,wrd[1]))&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"wU_uMdu");
	  strcpy(comp_verbs,wrd[2]);
	}*/
	/* These are moved down, in order to apply wU_uMdu rule before i_uMdu  in case of uMdu suffix */
	//else if((!strcmp(suffix_6,"ivuMdu") || (!strcmp(suffix_4,"uMdu"))) && !strcmp(pdgm,"uMdu") && (len > 8)&&(strlen(comp_verbs)==0))
	else if((!strcmp(suffix_6,wrd[0]) || (!strcmp(suffix_4,wrd[0]))) && !strcmp(pdgm,wrd[1]) && (len > 8)&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"i_uMdu");
	  strcpy(comp_verbs,wrd[2]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_6=%s|suffix_4=%s|pdgm=%s|comp_verb=%s|",suffix_6,suffix_4,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if(!strcmp(suffix_3,"ale") && !strcmp(pdgm,"we")&&(strlen(comp_verbs)==0))
	/*else if(!strcmp(suffix_3,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_le");
	  strcpy(comp_verbs,wrd[2]);
	}
	//else if(!strcmp(suffix_3,"Ale") && !strcmp(pdgm,"we")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_3,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_le");
	  strcpy(comp_verbs,wrd[2]);
	}
	//else if(!strcmp(suffix_3,"ele") && !strcmp(pdgm,"we")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_3,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_le");
	  strcpy(comp_verbs,wrd[2]);
	}
	//else if(!strcmp(suffix_3,"ole") && !strcmp(pdgm,"we")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_3,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_le"); 
	  strcpy(comp_verbs,wrd[2]);
	}*/
	//else if(!strcmp(suffix_5,"wappu") && !strcmp(pdgm,"pannu")&&(strlen(comp_verbs)==0))
	/*else if(!strcmp(suffix_5,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"aka_wappu");
	  strcpy(comp_verbs,wrd[2]);
	}*/	
	/*else if(!strcmp(suffix_5,"abadu") && !strcmp(pdgm,"padu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_badu");
		
	else if(!strcmp(suffix_5,"obadu") && !strcmp(pdgm,"padu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_badu");
	
	else if(!strcmp(suffix_5,"Abadu") && !strcmp(pdgm,"padu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_badu");
	
	else if(!strcmp(suffix_5,"ebadu") && !strcmp(pdgm,"padu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_badu");
	
	else if(!strcmp(suffix_5,"agala") && !strcmp(pdgm,"gala")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_gala");
		
	else if(!strcmp(suffix_5,"Agala") && !strcmp(pdgm,"gala")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_gala");
	
	else if(!strcmp(suffix_5,"ogala") && !strcmp(pdgm,"gala")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_gala");
	
	else if(!strcmp(suffix_5,"egala") && !strcmp(pdgm,"gala")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_gala");
	*/
	//else if((!strcmp(suffix_3,"abo") && !strcmp(pdgm,"po")) || ((!strcmp(suffix_3,"obo") || !strcmp(suffix_3,"Abo") || !strcmp(suffix_3,"ebo")) && !strcmp(pdgm,"po"))&&(strlen(comp_verbs)==0))
	/*else if((!strcmp(suffix_3,wrd[0])) && (!strcmp(pdgm,wrd[1]))&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_po");
	  strcpy(comp_verbs,wrd[2]);
	}*/
	//else if(!strcmp(suffix_5,"amanu") && !strcmp(pdgm,"koVnu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_5,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_manu");
	  strcpy(comp_verbs,wrd[2]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_5=%s|pdgm=%s|comp_verb=%s|",suffix_5,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if((!strcmp(suffix_5,"Amanu")  || !strcmp(suffix_6,"ammanu")) && !strcmp(pdgm,"koVnu")&&(strlen(comp_verbs)==0))
	else if((!strcmp(suffix_5,wrd[0])  || !strcmp(suffix_6,wrd[0])) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_manu");
	  strcpy(comp_verbs,wrd[2]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_5=%s|suffix_6=%s|pdgm=%s|comp_verb=%s|",suffix_5,suffix_6,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if((!strcmp(suffix_5,"omanu") || !strcmp(suffix_7,"oVmmanu")) && !strcmp(pdgm,"koVnu")&&(strlen(comp_verbs)==0))
	else if((!strcmp(suffix_5,wrd[0])  || !strcmp(suffix_7,wrd[0])) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_manu");
	  strcpy(comp_verbs,wrd[2]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_5=%s|suffix_7=%s|pdgm=%s|comp_verb=%s|",suffix_5,suffix_7,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if((!strcmp(suffix_5,"emanu") || !strcmp(suffix_7,"eVmmanu")) && !strcmp(pdgm,"koVnu")&&(strlen(comp_verbs)==0))
	/*else if((!strcmp(suffix_5,wrd[0])  || !strcmp(suffix_7,wrd[0])) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_manu");
	  strcpy(comp_verbs,wrd[2]);
	}
	//else if(!strcmp(suffix_5,"mmanu") && !strcmp(pdgm,"koVnu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_5,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_manu");
	  strcpy(comp_verbs,wrd[2]);
	}*/
	//else if(!strcmp(suffix_7,"axalacu") && !strcmp(pdgm,"pannu")&&(strlen(comp_verbs)==0))
	/*else if(!strcmp(suffix_7,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_xalacu");
	  strcpy(comp_verbs,wrd[2]);
	}*/
	//else if(!strcmp(suffix_7,"oxalacu") && !strcmp(pdgm,"pannu")&&(strlen(comp_verbs)==0))
	/*else if(!strcmp(suffix_7,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_xalacu");
	
	//else if(!strcmp(suffix_7,"exalacu") && !strcmp(pdgm,"pannu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_7,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_xalacu");
	
	else if(!strcmp(suffix_7,"Axalacu") && !strcmp(pdgm,"pannu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_xalacu");
	
	else if(!strcmp(suffix_7,"agoVttu") && !strcmp(pdgm,"peVttu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_goVttu");
	
	else if(!strcmp(suffix_7,"ogoVttu") && !strcmp(pdgm,"peVttu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_goVttu");
	
	else if(!strcmp(suffix_7,"egoVttu") && !strcmp(pdgm,"peVttu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_goVttu");
		
	else if(!strcmp(suffix_7,"AgoVttu") && !strcmp(pdgm,"peVttu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_goVttu");
	
	else if(!strcmp(suffix_7,"abeVttu") && !strcmp(pdgm,"peVttu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_beVttu");
	
	else if(!strcmp(suffix_7,"ebeVttu") && !strcmp(pdgm,"peVttu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_beVttu");
	
	else if(!strcmp(suffix_7,"AbeVttu") && !strcmp(pdgm,"peVttu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_beVttu");
	
	else if(!strcmp(suffix_7,"obeVttu") && !strcmp(pdgm,"peVttu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_beVttu");
	*/
	//else if(!strcmp(suffix_5,"axagu") && !strcmp(pdgm,"pannu")&&(strlen(comp_verbs)==0))
	/*else if(!strcmp(suffix_5,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	 // strcpy(comp_verbs,"a_xagu");
	  strcpy(comp_verbs,wrd[2]);
	}*/
	/*else if(!strcmp(suffix_5,"oxagu") && !strcmp(pdgm,"pannu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_xagu");
	
	else if(!strcmp(suffix_5,"exagu") && !strcmp(pdgm,"pannu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_xagu");
	
	else if(!strcmp(suffix_5,"Axagu") && !strcmp(pdgm,"pannu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_xagu");
	*/
	//else if(!strcmp(suffix_6,"axiyyi") && !strcmp(pdgm,"wiyyi")&&(strlen(comp_verbs)==0))
	/*else if(!strcmp(suffix_6,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_xagu");
	  strcpy(comp_verbs,wrd[2]);
	}*/
	//else if(!strcmp(suffix_7,"agalugu") && !strcmp(pdgm,"poVg?du")&&(strlen(comp_verbs)==0))
	/*else if(!strcmp(suffix_7,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)){
	 strcpy(comp_verbs,wrd[2]); 
	printf("%s\n",pdgm);
	printf("%s\n",root);
	}*/
	/*else if(!strcmp(suffix_7,"ogalugu") && !strcmp(pdgm,"poVg?du")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_galugu");
	
	else if(!strcmp(suffix_7,"egalugu") && !strcmp(pdgm,"poVg?du")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_galugu");
	
	else if(!strcmp(suffix_7,"Agalugu") && !strcmp(pdgm,"poVg?du")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_galugu");
	
	else if(!strcmp(suffix_7,"ajoVccu") && !strcmp(pdgm,"vaccu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_joVccu");
	
	else if(!strcmp(suffix_7,"ojoVccu") && !strcmp(pdgm,"vaccu")&&(strlen(comp_verbs)==0))
  	  strcpy(comp_verbs,"a_joVccu");
	
	else if(!strcmp(suffix_7,"ejoVccu") && !strcmp(pdgm,"vaccu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_joVccu");
	
	else if(!strcmp(suffix_7,"AjoVccu") && !strcmp(pdgm,"vaccu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_joVccu");
	
	else if(!strcmp(suffix_6,"avaccu") && !strcmp(pdgm,"vaccu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_vaccu");
	
	else if(!strcmp(suffix_6,"ivaccu") && !strcmp(pdgm,"vaccu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"i_vaccu");
	*/
	/* in case of oVccu, it can be either a_vaccu or i_vaccu. 
	This cond is to be added in the heuristics. chk for the base.
	Only in case of pannu, there is real clash */
	/*else if(!strcmp(suffix_5,"oVccu") && !strcmp(pdgm,"vaccu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_vaccu");
	
	else if(!strcmp(suffix_6,"Avaccu") && !strcmp(pdgm,"vaccu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_vaccu");
	
	else if(!strcmp(suffix_6,"ovaccu") && !strcmp(pdgm,"vaccu")) 	
	  strcpy(comp_verbs,"a_vaccu");
	
	else if((!strcmp(suffix_5,"agUdu") || !strcmp(suffix_5,"akUdu")) && !strcmp(pdgm,"Adu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_gUdu");
		
	else if(!strcmp(suffix_5,"ajAlu") && !strcmp(pdgm,"kAlu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_jAlu");
	
	else if(!strcmp(suffix_5,"ojAlu") && !strcmp(pdgm,"kAlu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_jAlu");
	
	else if(!strcmp(suffix_5,"ejAlu") && !strcmp(pdgm,"kAlu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_jAlu");
	
	else if(!strcmp(suffix_5,"AjAlu") && !strcmp(pdgm,"kAlu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_jAlu");
	
	else if(!strcmp(suffix_7,"aparacu") && !strcmp(pdgm,"pannu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_paracu");
	
	else if(!strcmp(suffix_6,"komanu") && !strcmp(pdgm,"koVnu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_komanu");
	
	else if(!strcmp(suffix_5,"asAgu") && !strcmp(pdgm,"pannu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_sAgu");
	
	else if(!strcmp(suffix_5,"osAgu") && !strcmp(pdgm,"pannu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_sAgu");
	
	else if(!strcmp(suffix_5,"esAgu") && !strcmp(pdgm,"pannu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_sAgu");
	
	else if(!strcmp(suffix_5,"AsAgu") && !strcmp(pdgm,"pannu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_sAgu");
	
	else if(!strcmp(suffix_7,"ovalayu") && !strcmp(pdgm,"valayu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_valayu");
	
	else if(!strcmp(suffix_7,"evalayu") && !strcmp(pdgm,"valayu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_valayu");
	
	else if(!strcmp(suffix_7,"Avalayu") && !strcmp(pdgm,"valayu")&&(strlen(comp_verbs)==0))
	  strcpy(comp_verbs,"a_valayu");
	*/
	//else if(!strcmp(suffix_10,"nAraMBiMcu") && !strcmp(pdgm,"cUpiMcu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_10,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_nAraMBiMcu");
	  strcpy(comp_verbs,wrd[2]);
	//sprintf(logmsg, "NAGARAJ INFO: suffix_10=%s|pdgm=%s|comp_verb=%s|",suffix_10,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
	//else if(!strcmp(suffix_4,"neru") && !strcmp(pdgm,"Adu")&&(strlen(comp_verbs)==0))
	/*else if(!strcmp(suffix_4,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	  //strcpy(comp_verbs,"a_neru");
	  strcpy(comp_verbs,wrd[2]);
	}*/
	//else if(!strcmp(suffix_6,"valayu") && !strcmp(pdgm,"valayu")&&(strlen(comp_verbs)==0))
	else if(!strcmp(suffix_6,wrd[0]) && !strcmp(pdgm,wrd[1])&&(strlen(comp_verbs)==0)) {
	/*printf("old-RT = %s\n",root); */
	//else if(strcmp(suffix_7,"vvalayu")&&(strlen(comp_verbs)==0))
	if(!strcmp(suffix_7,wrd[2])) 
	
	{
	  /* To account for povAlasina -> povvalayu -> povalayu */
	  strcpy(tmp,"");
	  strncpy(tmp,root,len-7);
	  tmp[len-7] = '\0';
	  //strcat(tmp,"valayu"),strcpy(root,tmp);
	  strcat(tmp,wrd[0]),strcpy(root,tmp);
	  /*printf("new-RT = %s\n",root); */
	}

	//else if(strcmp(suffix_7,"avalayu")&&(strlen(comp_verbs)==0))
	else if(strcmp(suffix_7,wrd[3])&&(strlen(comp_verbs)==0)) {
	 /* To account for ceyAlsina-> ceyvalayu -> ceyavalayu */
	  strcpy(tmp,"");
	  strncpy(tmp,root,len-6);
	  tmp[len-6] = '\0';
	  //strcat(tmp,"avalayu"),strcpy(root,tmp);
	  strcat(tmp,wrd[3]),strcpy(root,tmp);
	  /* printf("%s\n",root); */
	}
	//strcpy(comp_verbs,"a_valayu");
	strcpy(comp_verbs,"wrd[4]");
	//sprintf(logmsg, "NAGARAJ INFO: suffix_7=%s|suffix_6=%s|pdgm=%s|comp_verb=%s|",suffix_7,suffix_6,pdgm,comp_verbs); PRINT_LOG(log_file,logmsg);	
	
	}
//
 }//added by Nagaraju to remove hard coding from comp_verbs

 PRINT_LOG(log_file, "Coming out of comp_verb_hur() ");
}
