#include <stdio.h>

int main()
{

    int size = 0, arr[100] = { 0 };
    int* ptr;
    char c;

    ptr = arr;

    printf("\nEnter array. Press 'Enter' to terminate: ");

    for (int i = 0; i < 100; i++) {
        scanf("%d%c", ptr, &c);
        size++;
        ptr++;

        if (c == '\n') {
            break;
        }
    }

    ptr--;
    size--;

    printf("\nEntered array in reverse: ");

    for (int i = size; i >= 0; i--) {
        printf("%d ", *ptr);
        ptr--;
    }

    return 0;
}
