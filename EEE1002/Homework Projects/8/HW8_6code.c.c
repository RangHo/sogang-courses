#include <stdio.h>

int main(){
    int n = 0, nc = 0, count = 0;;

    printf("Enter an integer : \n");  
    scanf("%d",&n); 

    nc = n;

    while(nc != 0){  
       nc = nc/10; 
       count++;  
    } 

    int forward[count];

    for(int i = (count - 1); i >= 0; i--){
        forward[i] = n%10;
        n /= 10;
    }

    forward[count] = 0;

    int i = count -1;
    while(i >= 0){
        printf("%d", forward[i]);
        i--;
    }

    return 0;
}
