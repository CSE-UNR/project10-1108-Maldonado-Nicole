//Project 10
//Nicole Maldonado

#include <stdio.h>
#include <stdbool.h>

#define LENGTH 5
#define TIMES 6
#define WORD "word.txt"

void arrays(char twordle[][LENGTH], char mysteryWord[LENGTH]);
void guesses(char twordle[][LENGTH], int attempt);
void win(char twordle[][LENGTH], char word[], int attempt, int *result);
void lowerCase(char twordle[][LENGTH], char word[], int attempt);
void printResult(char twordle[][LENGTH], char word[], int attempt);
void gameOver(int result, int attempt);



int main(){
	int attempt = 0; 
	int result = 0;
	char twordleArr[TIMES][LENGTH];
	char mysteryWord[LENGTH];
	
	
	arrays(twordleArr, mysteryWord);
	
	while (result == 0 && attempt < TIMES) {
		guesses(twordleArr, attempt);
		lowerCase(twordleArr, mysteryWord, attempt);		
		
		win(twordleArr, mysteryWord, attempt, &result);
		
		printResult(twordleArr, mysteryWord, attempt);
		attempt++;
		
		if (result == 1) {
			gameOver(result, attempt);
			return 0;
			}
		}
	gameOver(result, attempt);
	
	return 0;
	}



void arrays(char twordle[][LENGTH], char mysteryWord[LENGTH]) {
	
	FILE* wordPtr = fopen(WORD, "r");
	if(wordPtr == NULL){
		printf("Could not open %s, goodbye!", WORD);
		}
	fscanf(wordPtr, "%5s", mysteryWord);
	
	for (int i = 0; i < LENGTH; i++) {
		if (mysteryWord[i] == '\n' || mysteryWord[i] == '\r') {	
			mysteryWord[i] = '\0';
			}
		}
	fclose(wordPtr);
	
	mysteryWord[5] = '\0';
	}

void guesses(char twordle[][LENGTH], int attempt){
	bool valid = false;
	
	while(!valid) {
		printf("GUESS #%d! Enter your guess: ", attempt + 1);
		scanf(" %5s", twordle[attempt]); 
		twordle[attempt][5] = '\0';
	
		int count = 0;
		while (twordle[attempt][count] != '\0') {
			count++;
			}
		if (count == 5) {
			valid = true;
			}
		else {
			printf("Invalid! Enter a word with 5 letters! ");
			}	
		}
	}

void win(char twordle[][LENGTH], char word[], int attempt, int *result){
	int matching = 0;
	for (int i = 0; i < 5; i++) {
		if (twordle[attempt][i] == word[i]) {
			matching++;
			}
		}
	if (matching == 5) {
		*result = 1;
		}
	}

void printResult(char twordle[][LENGTH], char word[], int attempt){ 
	printf("----------------------------------\n");
	for (int row = 0; row < TIMES; row++) {
		if (row <= attempt) {
			for (int i = 0; i < LENGTH; i++) {
				if (twordle[row][i] == word[i]) {
					printf("%c", twordle[row][i] - 32);
					}
				else {
					printf("%c", twordle[row][i]);
					}
				}
			printf("\n");
			
			for (int i = 0; i < LENGTH; i++) {
				if (twordle[row][i] == word[i]) {
					printf(" ");
					}
				else {
					int found = 0;
					int ind = 0;
					while (ind < LENGTH && found == 0) {
						if (twordle[row][i] == word[ind] && twordle[row][ind] != word[ind]) {
							found = 1;
							}
						ind++;
						}
					if (found == 1) {
						printf("^");
						}
					else {
						printf(" ");
						}
					}
				}
			printf("\n");
			}
		}
	}

void lowerCase(char twordle[][LENGTH], char word[], int attempt) {
	for (int index = 0; twordle[attempt][index] != '\0'; index++) {
		if (twordle[attempt][index] >= 'A' && twordle[attempt][index] <= 'Z') {
			twordle[attempt][index] += 32;
			}
		}
	}


void gameOver(int result, int attempt) {
	if (result == 1) {
		if (attempt == 1) {
		printf("Got it in one!\n Impressive!!\n");
		}
		else if (attempt >= 1) {
			printf("You got it!! It took you %d out of %d guesses!\n", attempt, TIMES);
			}	
		else {
			printf("Good try!\n");
			}
		}
	}



