#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    char* buffer;

    if ((buffer = (char*)malloc(10)) == NULL) {
        printf("malloc failed.\n");
        exit(1);
    }

    printf("Buffer of size %d created \n", _msize(buffer));
    strcpy(buffer, "HYDERABAD");
    printf("\nBuffer contains: %s\n", buffer);

    if ((buffer = (char*)realloc(buffer, 15)) == NULL) {
        printf("Reallocation failed.");
        exit(1);
    }

    printf("\nBuffer size modified.\n");
    printf("Buffer still contains: %s\n", buffer);
    strcpy(buffer, "SECUNDERABAD");
    printf("Buffer now contains: %s\n", buffer);

    free(buffer);

    return 0;
}