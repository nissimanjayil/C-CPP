#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main()
{
    srand(time(NULL));
    char guessWords [][16] ={"green","yellow","red","windows","linux","grapefruit"};
    int randomIndex = rand() % 6;
    int numOfLives= 5;
    int numCorrect =0;
    int oldCorrect =0;

    int lengthOfWord = strlen(guessWords[randomIndex]);
    //                       0 1 2 3 4 5
    //                       P u r p l e
    int letterGuessed [8] = {0,0,0,0,0,0,0,0};

    int quit =0;

    int guess[16];
    char guessedLetters;
    printf("guessWords :%s randomIndex :%d lengthOfWord :%d\n",
            guessWords[randomIndex],randomIndex,lengthOfWord);


            //Game loop
    while(numCorrect < lengthOfWord){
        printf("Number correct so far:%d\n",numCorrect);
        printf("Enter a guess letter:");
        fgets(guess,16,stdin);

        if(strncmp(guess,"quit",4)==0){
            quit =1;
            break;
        }
            guessedLetters = guess[0];
            printf("LetterGuessed:%c\n" ,guessedLetters);

            oldCorrect = numCorrect;
        for(int i =0;i<lengthOfWord;i++){
            if(guessedLetters == guessWords[randomIndex][i]){
                letterGuessed[i]=1;
                numCorrect++;
            }else if(letterGuessed[i]==1){
                continue;
            }
        }
        if(oldCorrect==numCorrect){
            numOfLives--;
            printf("Sorry wrong guess\n");

        }else{
            printf("Correct guess :) \n");

        }
    }

    if(quit ==1){
        printf("\nThe user quit early\n");
    }

return 0;
}
