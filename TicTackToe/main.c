#include <stdio.h>
#include <stdlib.h>

const NOUGHTS =1;
const CROSSES =2;
const empty =0;
const BORDER =3;

const int ConvertTo25 ={
    6,7,8,
    11,12,13,
    16,17,18
};

void InitialiseBoard(int *board){

    for(int index =0;index <25;index++){
        board[index] =BORDER;
    }
    for(int index =0;index <9;index++){
        board[ConvertTo25[index]] =EMPTY;
    }

}

void PrintBoard(const int*board){
    int index=0;
    printf("\nBoard:\n");


}
int main()
{
    printf("Hello world!\n");
    return 0;
}
