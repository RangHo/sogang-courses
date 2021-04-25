#include <stdio.h>

int main(){
    char line[100], character;
    int c = 0;
    printf("Enter a phrase.\n");
    do{
        character = getchar();
        line[c] = character;
        c++;
    }
    while(character != '\n');

    c = c-1;

    line[c] = '\0';

    for(int i = 0; i < c; i++){
        if((line[i] >= 65)&&(line[i] <= 90)){
            line[i] = line[i] + 32;
        }
    }

    char front[c-1];
    char rear[c-1];

    for(int i = 0; i < c; i++){
        front[i] = line[i];
        rear[c-1-i] = line[i];
    }

    for(int i = 0; i < c; i++){
        if(front[i] != rear[i]){
            printf("Given string is NOT a palindrome.");
            return 0;
        }
    }

    printf("Given string is a palindrome.");

    return 0;
}