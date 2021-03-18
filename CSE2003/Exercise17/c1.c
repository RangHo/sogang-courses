#include <stdio.h>

void Josephus(int, int);

int main(void)
{
    int n, k;
    scanf("%d %d", &n, &k);

    Josephus(n, k);

    printf("\n");

    return 0;
}

void Josephus(int n, int k)
{
    int target[n];
    for (int i = 0; i < n; i++)
        target[i] = i + 1;

    int target_left = n;
    int index = 0;

    while (target_left > k) {
        for (int i = 0; i < (k - 1); i++) {
            // Try incrementing, why not
            index++;

            if (target[index % n] == 0) // If this guy is already dead
                i--;                    // skip the guy and try again
        }

        printf("%d ", target[index % n]); // Printing the selected guy
        target[index % n] = 0;            // and actually kill the guy
        index++;
        while (target[index % n] == 0)
            index++;

        target_left--; // Decrement counter 'cause reasons
    }
}
