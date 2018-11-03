#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main()
{
    char guessWords[][16] ={"green","yellow","purple","windows","linux","apple"};
    int randomIndex = rand() %6;
    int numLives =5;
    int numCorrect =0;
    int oldCorrect =0;

    int lengthOfWord = strlen(guessWords[randomIndex]);
    int letterGueesed[8] ={0,0,0,0,0,0,0,0};

    int quit =0;
    int loopIndex =0;

    char guess[16];
    char letterEntered;

    printf("guessWords:%s randomIndex:%d lengthOfWord:%d\n",
                    guessWords[randomIndex],
                    randomIndex,
                    lengthOfWord);

                    //game loop
    while(numCorrect < lengthOfWord){

        printf("Number correct so far:\n",numCorrect);
        printf("Enter a guess letter:");
        fgets(guess,16,stdin);

        if(strncmp(guess,"quit",4)==0){
            quit =1;
            break;
        }
        letterEntered = guess[0];
        printf("letterEntered :%c\n",letterEntered);

        for(loopIndex=0;loopIndex<lengthOfWord;loopIndex++){


            if(letterGueesed[loopIndex] ==1){
                continue;
            }
            if(letterEntered = guessWords[randomIndex][loopIndex]){
                    letterGueesed[loopIndex] =1;
                    numCorrect++;
            }

        }

    }
    //while loop
    if(quit ==1){
        printf("\n the user quit early\n");
    }
return 0;
    }



