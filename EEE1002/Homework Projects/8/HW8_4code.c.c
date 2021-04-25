#include <stdio.h>
#include <math.h>

int main(){
    float x[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    float y[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    
    printf("Num | 0.0   0.1   0.2   0.3   0.4   0.5   0.6   0.7   0.8   0.9 \n");
    printf("====|===========================================================\n");
    for(int i = 0; i < 9; i++){
        printf("%.1f |", y[i]);
        for(int j = 0; j < 10; j++){
            printf("%.3f ", sqrt(y[i]+x[j]));
        }
        printf("\n");
    }
}