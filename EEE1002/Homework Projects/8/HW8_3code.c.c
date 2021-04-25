#include <stdio.h>

int main(){
    char fname[5];
    char mname[6];
    char lname[6];

    scanf("%s", &fname);
    scanf("%s", &mname);
    scanf("%s", &lname);

    printf("%s %c. %s\n", fname, mname[0], lname);
    printf("%c. %c. %s\n", fname[0], mname[0], lname);
    printf("%s %c. %c.", lname, fname[0], mname[0]);

    return 0;
}