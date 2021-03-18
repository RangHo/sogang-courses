#include <stdio.h>

#define TEXT_MAX 1024

int main(void)
{
    FILE* encoded_data = fopen("text.bin", "rb");

    char result[TEXT_MAX];

    char data[4] = { 0 };

    int count = 0;
    do {
        fread(data, sizeof(char), 4, encoded_data);

        result[count] = data[0];
        count++;
    } while (!feof(encoded_data));

    printf("%s\n", result);

    fclose(encoded_data);

    return 0;
}
