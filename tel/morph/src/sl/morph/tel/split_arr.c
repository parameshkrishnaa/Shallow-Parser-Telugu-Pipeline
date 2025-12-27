/* this function splits the array with a special char given */

#include<stdio.h>
#include<string.h>
// void split_arr(char[],char,char[][]);
/* main()
{
char arr1[10];
int size1,i;
char new[10][10];
printf("Enter the array =" );
gets(arr1);
arr1[strlen(arr1)]='\0';
split_arr(arr1,'\t',new);
	   i=0;
           while ( strcmp(new[i],"\0") != 0)
	   {
		 printf("%s\n",new[i]);
		i++;
	   }
}
*/
void split_arr(char arr[300],char ch,char new[15][50])
    {				
	int col=0,k,i;
	int row=0;
	strcpy(new[0],"\0");
	strcat(arr,"\n");	
	for(k=0;k<strlen(arr);k++)
	{
               if(arr[k] == '\n') 
	 	{
		  //strcpy(new[row],"\0");
		  break;
		}
		 if (arr[k] != ch)
		{
	  	 new[row][col]=arr[k];
		   col++;
		}
		else
		{
	 	  new[row][col]='\0';
		   row++;
		   col=0;
		}
	  }
	new[row][col]='\0';
		 strcpy(new[row+1],"\0");
       // strcpy(new[row+1],"\0");	
   }
