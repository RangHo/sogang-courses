#include <stdio.h>

#define SENTENCE_LENGTH 500
#define WORD_LENGTH 20

char* LGame(char*);
int IsVowel(char);
char ToLower(char);

int main(void)
{
    char* thing = LGame("Hello!");
    printf("%s\n", thing);

    return 0;
}

char* LGame(char* word)
{
    // Find word length
    int word_length = 0;
    while (word[word_length] != '\0')
        word_length++;

    // Copy word
    char old_word[WORD_LENGTH] = { 0 };
    for (int i = 0; i < word_length; i++)
        old_word[i] = word[i];

    // String to attach later
    char* postfix;
    int postfix_length;

    // Index to copy from
    int from;

    // Get the first character, and determine which string to append
    if (IsVowel(word[0])) {
        // If it is, add -ay or -y depending on the last character
        if (word[word_length - 1] == 'a') {
            postfix = "y";
            postfix_length = 1;
        } else {
            postfix = "ay";
            postfix_length = 2;
        }

        from = 0;
    } else {
        // If not, then append the first character followed by -ay
        char temp[3] = { word[0], 'a', 'y' };
        postfix = temp;
        postfix_length = 3;

        from = 1;
    }

    // Create a new character array, and copy the rest of the substring
    for (int i = 0; i < word_length - from; i++) {
        word[i] = old_word[from + i];
    }

    // Append -ay ending
    for (int i = 0; i < postfix_length; i++) {
        word[word_length - from + i] = postfix[i];
    }

    // Return the thing
    return word;
}

int IsVowel(char target)
{
    switch (ToLower(target)) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return 1;

    default:
        return 0;
    }
}

char ToLower(char target)
{
    if (target >= 'A' && target <= 'Z')
        return target - ('a' - 'A');
    else
        return target;
}
