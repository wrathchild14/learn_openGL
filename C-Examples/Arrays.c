#include<stdio.h>
// For some reason doesn't work - counldn't find out why
/* count digits, white space, others */
int main()
{
    int character, i, nWhiteSpace, nOther;
    int nDigit[10];
    nWhiteSpace = nOther = 0;

    // Fill the array with zeroes
    for (i = 0; i < 10; ++i) {
        nDigit[i] = 0;
    }

    // Keep track of every character's count in an array - also keep count of whitespace and other
    while ((character = getchar()) != EOF) {
        if (character >= '0' && character <= '9') {
            ++nDigit[character - '0'];
        }
        else if (character == ' ' || character == '\n' || character == '\t') {
            ++nWhiteSpace;
        }
        else {
            ++nOther;
        }
    }
    
    printf("digits =");
    for (i = 0; i < 10; ++i) {
        printf(" %d", nDigit[i]);
    }

    printf(", white space = %d, other = %d\n",
           nWhiteSpace, nOther);

    return 0;
}