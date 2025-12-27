/**
 * FILE Name :vwl_harmony.c
*/


/** vwl_harmony
 * This function checks whether the last char is vowel or not
 * The arguments:
 * in_wrd of char type, pdgm of char type and out_vrd of char type
 * integer pointer
 * Return : void
 */

/* HEADER FILES */
#include <string.h>
#include <stdio.h>
#include "./common/analyser/morph_logger.h"


extern FILE *log_file;
#define FUNCTION "vwl_harmony()"

vwl_harmony(in_wrd,pdgm,out_wrd)

char *in_wrd,*pdgm,*out_wrd;
{
	char *program_name="vwl_harmony.c";
       // PRINT_LOG(log_file," This function checks whether the last char is vowel or not");
	char lst_ch;
	int loop1,q_cnt,ch_cnt,len,loop2;
	/*printf("%s,%s\n",in_wrd,pdgm);*/
	q_cnt = 0;
	len = strlen(pdgm);
	for(loop1=0;loop1<len;loop1++) 
	   {
	    if(pdgm[loop1] == '?')
	      q_cnt++;
	   }
	len = strlen(in_wrd);
	lst_ch = in_wrd[len-1];

	/*printf("%d\n",q_cnt);*/

	if((lst_ch == 'i') || (lst_ch == 'u'))
	  {
	    for(loop1=0;loop1<len;loop1++)
	      if(isvowel(in_wrd[loop1])) 
		{
		  loop2=loop1;
		   break;
		}
	     for(loop1=0;loop1<loop2+1;loop1++) 
		out_wrd[loop1]=in_wrd[loop1];
	     out_wrd[len-1]=in_wrd[len-1];
	     out_wrd[len] = '\0';
	     ch_cnt = 0;
	     for(loop1=len-2;loop1>loop2;loop1--)
		{
		  if(ch_cnt < q_cnt)
		    {
		      if((lst_ch =='i') && (in_wrd[loop1] == 'u')) 
			{
			  out_wrd[loop1] = lst_ch;
			  ch_cnt++;
			}
		      else if((lst_ch =='u') && (in_wrd[loop1] == 'i')) 
			{
			  out_wrd[loop1] = lst_ch;
			  ch_cnt++;
			}
		      else if((lst_ch =='u') && (in_wrd[loop1] == 'a')) 
			{
			   out_wrd[loop1] = lst_ch;
			   ch_cnt++;
			}
		      else if((lst_ch =='u') && (in_wrd[loop1] == 'u')) 
			{
			    out_wrd[loop1] = in_wrd[loop1];
			    ch_cnt++;
			}
		      else if((lst_ch =='i') && (in_wrd[loop1] == 'i')) 
			{
			    out_wrd[loop1] = in_wrd[loop1];
			    ch_cnt++;
			}
		      else
			    out_wrd[loop1]=in_wrd[loop1];
		    }
		  else
		    out_wrd[loop1]=in_wrd[loop1];
		}
	  }
	else out_wrd[0] = '\0';
}
