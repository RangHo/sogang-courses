#include <stdio.h>
int main(){

    int array[5][5];
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            array[i][j] = 0;
        }
    }

    for(int i = 0; i < 5; i++){
        for(int j = 5 - i; j < 5; j++){
            array[i][j] = -1;
        }
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 4 - i; j++){
            array[i][j] = +1;
        }
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            printf("%+d ", array[i][j]);
        }
        printf("\n");
    }
    return 0;
}