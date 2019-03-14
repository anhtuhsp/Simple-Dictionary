#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/anhtu/C advance/Gtk learning/C_project/src/bt/inc/btree.h"

#define KEY_LENGTH 50
#define DATA_LENGTH 10000

void parseNewLine(char* source);

void main(int argc, char* argv[]){
  if(argc < 3)
    {
      printf("Invalid argumets!\n"
	     "<program><dict-tab file><output b-tree file>\n");
      exit(EXIT_FAILURE);
    }

  FILE* dic = fopen(argv[1], "r");
  if(dic == NULL)
    {
      printf("Couldn't open file %s for convertinf!\n", argv[1]);
      exit(EXIT_FAILURE);
    }

  BTA* database = btcrt(argv[2], 0, FALSE);
  char key[KEY_LENGTH], data[DATA_LENGTH];
  int wordCount = 0;

  printf("Converting...\n");
  while(fscanf(dic,"%[^\t]", key) == 1){
    fgets(data, DATA_LENGTH, dic);

    parseNewLine(data);
    btins(database, key, data, strlen(data)+1);
    wordCount++;
    if((wordCount%50000)== 0)
      printf("%d words converted.\n", wordCount);

  }

  printf("\nConverting completed! With total %d words.\n", wordCount);
  btcls(database);
  fclose(dic);  
}

void parseNewLine(char *source)
{
  //Ititial j = 1 too remove the '\t' character at the beginning
  int i = 0, j = 1;
  
  while(source[j] != '\0')
    {
      if(source[j] == '\\' && source[j+1] == 'n')
	{
	  source[i++] = '\n';
	  j += 2;
	}
      else
	{
	  if( i != j)
	    source[i++] = source[j++];
	  else
	    {
	      i++;
	      j++;
	    }
	}
    }
  source[i] = '\0';
}
