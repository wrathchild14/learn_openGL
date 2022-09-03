#include<stdio.h>
#define IN 1  /* inside a word */
#define OUT 0 /* outside a word */
/* count lines, words, and characters in input */
int main()
{
    int c, numLines, numWords, numChars, state;
    state = OUT;
    numLines = numWords = numChars = 0;
    while ((c = getchar()) != EOF)
    {
        ++numChars;
        if (c == '\n'){
            ++numLines;
        }
        if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
        }
        else if (state == OUT)
        {
            state = IN;
            ++numWords;
        }
    }
    printf("%d %d %d\n", numLines, numWords, numChars);

    return 0;
}