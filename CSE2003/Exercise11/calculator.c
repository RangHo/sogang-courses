#include <stdio.h>

int main(void)
{
    int command, param1, param2, result;

    while (1) {
        printf("\n[0]: Exit   [1]: Add    [2]: Subtract   [3]: Multiply   [4]: Divide\n");

        scanf("%d", &command);

        if (command == 0) {
            printf("Bye!");
            return 0;
        }

        scanf("%d %d", &param1, &param2);

        switch (command) {
        case 1:
            printf("%d + %d = %d\n", param1, param2, param1 + param2);
            break;

        case 2:
            printf("%d - %d = %d\n", param1, param2, param1 - param2);
            break;

        case 3:
            printf("%d * %d = %d\n", param1, param2, param1 * param2);
            break;

        case 4:
            printf("%d / %d = %d\n", param1, param2, param1 / param2);
            break;
        }
    }

    return 0;
}
