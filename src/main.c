#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

bool search(int num, int len, int arr[]){
  for(int i = 0 ; i < len ; i++){
    if(arr[i] == num){
      return true;
    }
  }
  return false;
}

int main(void) {

  FILE *fp=fopen("names.txt","r");
  FILE *fw=fopen("result.txt","w");
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int lineCount = 0;
  int numberOfWinner = 0;

  if(fp == NULL){
    printf("File doesn't exist.");
    return 0;
  }

  while ((read = getline(&line, &len, fp)) != -1) {
    if(strlen(line)>1){
      lineCount++;
    }
  }

  rewind(fp);
  
  printf("Enter number of winners : ");
  scanf("%d", &numberOfWinner);
  while(numberOfWinner < 0 || numberOfWinner > lineCount ){
  printf("Enter a valid number of winners : ");
  scanf("%d", &numberOfWinner);
  }

  fprintf(fw, "Welcome to Giveaway !\n\n");

  int winners[numberOfWinner];
  srand(time(NULL));
  for(int i = 0 ; i < numberOfWinner ; i++){
    int temp = (rand() % lineCount) + 1;
    while(search(temp, numberOfWinner, winners)){
      temp = (rand() % lineCount) + 1;
    }
    winners[i] = temp;
  }

  int tempLineCount = 0;
  int winnersLength = sizeof(winners)/sizeof(winners[0]);
    for(int i = 0 ; i < winnersLength ; i++){
    printf("%d\n", winners[i]);
  }
  int temp = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    if(strlen(line)>1){tempLineCount++;}
    bool exist = search(tempLineCount, winnersLength, winners);
    if(exist){
      temp++;
      printf("%d.Winner : %s", temp, line);
      fprintf(fw,"%d.Winner : %s", temp, line);
    }
  }

  fprintf(fw, "\nGiveaway coded by mehmers on github.com");

  if(line){free(line);}
  
  fclose(fp);
  fclose(fw);
  return 0;
}

