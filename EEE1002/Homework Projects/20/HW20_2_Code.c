#include<stdio.h>

struct date{
    int day;
    int month;
    int year;
};

struct date read(struct date input);
int validate(struct date input);
int print(struct date input);


int main(){
    struct date data;

    data = read(data);
    if(validate(data) == 0){
        print(data);
    }
    else{
        printf("\nInvalid Date!\n");
    }


    printf("\n");
    return 0; 
}

struct date read(struct date input){
    printf("Enter day, month, year:\n");
    scanf("%d %d %d", &input.day, &input.month, &input.year);
    return(input);
}


int validate(struct date input){

    if(input.month < 1 || input.month > 12){
        return 1;
    }

    if(input.day <= 0){
        return 1;
    }

    else if(input.month == 2){
        if(input.year % 4 == 0){
            if(input.year % 100 == 0){
                if(input.year % 400 == 0){
                    if(input.day > 29){
                        return 1;
                    }
                }
                else{
                    if(input.day > 28){
                        return 1;
                    }
                }
            }
            else{
                if(input.day > 29){
                    return 1;
                }
            }
        }
        else if(input.day > 28){
            return 1;
        }
    }

    else if(input.month == 4 || input.month == 6){
        if(input.day > 30){
            return 1;
        }
    }

    else if(input.month <= 7 && input.month % 2 == 1){
        if(input.day > 31){
            return 1;
        }
    }
    
    else if(input.month >=8 && input.month % 2 == 0){
        if(input.day > 31){
            return 1;
        }
    }

    else if(input.month >= 8 && input.month % 2 == 1){
        if(input.day > 30){
            return 1;
        }
    }

    return 0;

}






int print(struct date input){
    
    switch (input.month)
    {
    case 1:
        printf("\nJanuary ");
        break;
    case 2:
        printf("\nFebruary ");
        break;
    case 3:
        printf("\nMarch ");
        break;
    case 4:
        printf("\nApril ");
        break;
    case 5:
        printf("\nMay ");
        break;
    case 6:
        printf("\nJune ");
        break;
    case 7:
        printf("\nJuly ");
        break;
    case 8:
        printf("\nAugust ");
        break;
    case 9:
        printf("\nSeptember ");
        break;
    case 10:
        printf("\nOctober ");
        break;
    case 11:
        printf("\nNovember ");
        break;
    case 12:
        printf("\nDecember ");
        break;
    }

    if(input.year < 0){
        printf("%d, BCE %d\n", input.day, input.year * (-1));
    }
    else{
        printf("%d, %d\n", input.day, input.year);
    }
}