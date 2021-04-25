#include <stdio.h>

int main(){
    char my_char;
    printf("Please type a character: ");
    my_char = getchar();

    int val = my_char;
    if(val > 96 && val < 123){
        val -=32;
        my_char = val;
    }

    printf("Your capital character: ");
    putchar(my_char);
}