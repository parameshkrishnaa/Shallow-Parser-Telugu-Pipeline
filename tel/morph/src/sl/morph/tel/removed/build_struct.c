/**
  * File Name : build_struct.c
  */

/** Function: build_struct
  * This function creates a specfic structure for the rootword,priority pdgm and 
  * category. it copies the required data from the dictionary
  * It takes arguments: word of char array, ch_ar1 and ch_ar2 of 2 dimensional char arrays
  * Return : void
  */

/* HEADER FILES */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/defn.h"
#include "common/analyser/morph_logger.h"


extern FILE *log_file;
#define FUNCTION "build_struct()"

/* structure cotaining lexical information */
struct lex_info    
{
	/*  word */
	char word[LEXWORDSIZE];     

	/* paradigm */
	char pdgm[Pdgmsize];     

	/* category */
	char cat[Arraysize];      
};

void build_struct(word,ch_ar1,ch_ar2)

char word[SUFFWORDSIZE];    /* given input word */
char ch_ar1[SmallArray][LargeArray];
char ch_ar2[SmallArray][LargeArray];
{ 
	char *program_name="build_struct.c"; 
	PRINT_LOG(log_file, " This function creates a specfic  \
		structure for the rootword,priority pdgm and category. \ 
		it copies the required data from the dictionary "); 

	/* structure containig lexical info has 2 objects tag and dummy */
	struct lex_info *tag,dummy; 

	/* dummy tag pointer */
	char * tag_dummy;	    

	/* tmp word */
	char  tmp[Lexsize];         

	/* reading characters of ch_ar1*/
	int loop1,loop2,loop3,loop4;   

	loop1=0;
	tag= (struct lex_info *)malloc(sizeof(struct lex_info));

	/* guessed suff to null */
	while(ch_ar1[loop1][0] !='\0')	{ 
		strcpy(tag->word,word); 
		loop3=0;

		/* executes when suff != ',' nad not equal to null */ 
		while((ch_ar1[loop1][loop3] != ',') && (ch_ar1[loop1][loop3] != '\0')) {
			tmp[loop3] = ch_ar1[loop1][loop3]; 
			loop3++; 
		} 
		if(loop3>1) 
			tmp[loop3] = '\0'; 
		else 
			tmp[0] = '\0'; 
		strcpy(tag->pdgm,tmp);
	    	loop4 = loop3; 
		loop3=0; 

		/* executes when suff != " nad not equal to null */ 
		while(ch_ar1[loop1][loop4] != ',' && ch_ar1[loop1][loop4] != '\0') 
			tmp[loop3++] = ch_ar1[loop1][loop4++]; 
			if(loop3>1) 
				tmp[loop3] = '\0'; 
			else 
				tmp[0] = '\0'; 
				strcpy(tag->cat,tmp); 
		tag_dummy = (char *)tag; 
		for(loop2=0;loop2<sizeof(dummy);loop2++) 
		ch_ar2[loop1][loop2] = tag_dummy[loop2]; 
		loop1++; 
	}
	strcpy(ch_ar2[loop1],"");
}
