#include <stdio.h>
#include <string.h>
#include "defn.h"

extern void fgetword();
extern void fgetnumber();

void
get_suff_info(fp_suff,suff,add,ptr,no_of_entries)
FILE *fp_suff;
char add[SUFFWORDSIZE],suff[SUFFWORDSIZE];
int *ptr,*no_of_entries;
{
fgetword(fp_suff,suff,',');
fgetword(fp_suff,add,',');
fgetnumber(fp_suff,ptr,',');
fgetnumber(fp_suff,no_of_entries,',');
}
