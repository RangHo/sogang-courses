#include<stdio.h>

int fun1();
int fun2();
int fun3();
int x;

int main(){
    x = 10;
    printf("x = %d\n",x);
    printf("x = %d\n",fun1());
    printf("x = %d\n",fun2());
    printf("x = %d\n",fun3());


    return 0;
}

fun1(){
    x = x+10;
}

fun2(){
    int x;
    x = 1;
    return(x);
}

fun3(){
    x = x+10;
}