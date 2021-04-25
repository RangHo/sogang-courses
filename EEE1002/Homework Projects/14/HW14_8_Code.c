#include <stdio.h>

int find(char array[], char, int);

int main(){
    char line[100], character,search;
    int c = 0;

    printf("Enter a character array.\n");
    do{
        character = getchar();
        line[c] = character;
        c++;
    }
    while(character != '\n');

    c = c-1;

    line[c] = '\0';

    printf("Enter the character to find in the string.\n");
    search = getchar();

    int n = sizeof(line)/sizeof(line[0]) -1;

    int tf = find(line,search, n);

    if(tf == 1){
        printf("1");
    }
    else{
        printf("Could not find character in string.");
    }
    
}

int find(char arr[], char c, int n){
    
    for(int i = 0; i < n; i ++){
        if(arr[i]==c){
            return 1;
        }
    }
    return 0;
}