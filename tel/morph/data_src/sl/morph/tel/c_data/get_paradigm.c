/*
#include <stdio.h>
#include <string.h>

main()
{
char word[50];
getline(word);
while(word[0]!='\0')
{
get_paradigm(word,pdgm);
printf("%s,%s",word,pdgm);
getline(word);
}
}

*/
#include "defn.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
get_paradigm(word,pdgm)
char word[WORD_SIZE];
char pdgm[WORD_SIZE];
{
strcpy(pdgm,"Adu");/* just a filler  Rules are not yet obtained from Dr U.M.Rao*/
}
