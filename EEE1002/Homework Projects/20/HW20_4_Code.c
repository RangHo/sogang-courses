#include <stdio.h>

int main()
{
    int size = 0, temp = 0, new;
    int* ptr;
    int arr[100] = { 0 };
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

    // 문제에서 주어진 수열은 이미 크기순으로 정렬되어 있다고 하였기 때문에 정렬 알고리즘은 포함하지
    // 않았습니다.

    ptr = arr;

    printf("\nArray:\n");
    ptr = arr;
    for (int i = 0; i < size; i++) {
        printf("%d ", *ptr);
        ptr++;
    }

    printf("\nEnter New Element: ");
    scanf("%d", &new);
    arr[size] = new;
    size++;

    ptr = arr;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                ptr++;
            }
        }
    }

    printf("\nNew Array:\n");
    ptr = arr;
    for (int i = 0; i < size; i++) {
        printf("%d ", *ptr);
        ptr++;
    }

    return 0;
}
