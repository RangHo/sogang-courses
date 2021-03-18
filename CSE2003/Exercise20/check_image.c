#include <stdio.h>

#define FILENAME_LENGTH 255

int main(void)
{
    char input_name[FILENAME_LENGTH];

    printf("Enter file name: ");
    scanf("%s", input_name);

    FILE* input = fopen(input_name, "rb");

    const char magic_value[3] = { 0xff, 0xd8, 0xff };

    char signature[3];
    fread(signature, sizeof(char), 3, input);

    int is_valid = 1;
    for (int i = 0; i < 3; i++)
        if (magic_value[i] != signature[i])
            is_valid = 0;

    if (is_valid) {
        rewind(input);

        printf("It is a valid JPEG file.\n");

        FILE* output = fopen("sogang.jpg", "wb");

        char cache;
        while (!feof(input)) {
            fread(&cache, sizeof(char), 1, input);
            fwrite(&cache, sizeof(char), 1, output);
        }

        fclose(output);
    } else {
        printf("It is not a valid JPEG file.\n");
    }

    fclose(input);

    return 0;
}
