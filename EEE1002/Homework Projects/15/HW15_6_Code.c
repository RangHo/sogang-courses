#include <stdio.h>
#include <math.h>

#define SIZE 5

float std_dev(float a[], int n);
float mean(float a[], int n);

int main(){
    float value[SIZE];
    int i;
    
    printf("Enter %d float values.\n", SIZE);

    for(i = 0; i < SIZE; i++){
        scanf("%f", &value[i]);
    }

    printf("std.deviation is %f\n", std_dev(value, SIZE));

    return 0;
}

float std_dev(float a[], int n){
    int i;
    float x, sum = 0.0;
    x = mean(a,n);
    for(i = 0; i < n; i++){
        sum += (x-a[i])*(x-a[i]);
    }

    return(sqrt(sum/(float)n));
}

float mean(float a[], int n){
    int i;
    float sum = 0.0;
    for(i = 0; i < n; i++){
        sum = sum + a[i];
    }

    return(sum/(float)n);
}
