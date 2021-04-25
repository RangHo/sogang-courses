#include<stdio.h>

int main(){

    struct marks{
        int sub[3];
        int total;
    };

    struct marks student[3] = {{45,67,81,0},{75,53,69,0},{57,36,71,0}};
    struct marks total = {0};

    int i,j;
    
    for(i = 0; i <= 2; i++){
        for(int j = 0; j <= 2; j++){

            student[i].total += student[i].sub[j];
            total.sub[j] += student[i].sub[j];
        }

        total.total += student[i].total;
    }

   printf("Student   Total\n");
    for(i = 0; i <= 2; i++){
        printf("Student[%d] %d\n", i+1, student[i].total);
    }
    printf("\nSubject   Total\n");
    for(j = 0; j <= 2; j++){
        printf("Subject %d %d\n", j+1, total.sub[j]);
    }
    printf("\nGrand total : %d\n", total.total);







    return 0;
}