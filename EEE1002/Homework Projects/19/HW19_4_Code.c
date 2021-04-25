#include<stdio.h>
int* larger(int*, int*);

int main(){
    int a  = 10;
    int b = 20;
    int* p;
    p = larger(&a, &b);
    printf("%d", *p);

    return 0; 
}

int* larger(int* x, int* y){
    if(*x > *y){
        return(x);
    }
    else{
        return(y);
    }
}