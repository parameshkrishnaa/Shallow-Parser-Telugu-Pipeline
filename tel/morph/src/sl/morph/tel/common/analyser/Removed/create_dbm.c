/*
Note : Before running this program,
first create two files with 0 bytes by names lex.dir & lex.pag 
in the desired directory
*/
#include <stdio.h>
#include <fcntl.h>
#include <gdbm.h>
#include<string.h>
#include<stdlib.h>


extern void *my_fatal();

#include <lex_head.h>
main()
{
GDBM_FILE db1;

int i,st,derr,SIZEOF_LEX;
char *key;
datum lex_data,tag,tag2;

db1 = gdbm_open("lex",512,GDBM_READER,0666,my_fatal());


for(i=0;i<SIZEOF_LEX;i++)
{
tag.dptr=lex_ar[i].word;
tag.dsize = strlen(lex_ar[i].word);
tag2.dptr=lex_ar[i].pdgm;
tag2.dsize = strlen(lex_ar[i].pdgm);
st = dbm_store(db1,tag,tag2,/*DBM_INSERT*/);
}
dbm_close(db1);
}
