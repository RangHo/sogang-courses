#include <stdio.h>

void sort(int m, int x[]);

int main(){
    int marks[5] = {40,90,73,81,35};

    printf("Marks before sorting:\n");
    for(int i = 0; i < 5; i++){
        printf("%d ", marks[i]);
    }
    printf("\n\n");

    sort(5, marks);

    printf("Marks after sorting:\n");
    for(int i = 0; i < 5; i++){
        printf("%d ", marks[i]);
    }
    printf("\n");

    return 0;
}

void sort(int m, int x[]){
    int t;

    for(int i = 00; i < m-1; i++){
        for(int j = 1; j < m-i; j++){
            if(x[j - 1] >= x[j]){
                t = x[j-1];
                x[j-1] = x[j];
                x[j] = t;
            }
        }
    }
}