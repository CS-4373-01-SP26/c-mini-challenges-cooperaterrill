#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
void transposeExample(char *s)
{
    printf("%s\n", s);
    int len = strnlen(s, 256);
    for (int i = 0; i < len / 2; i++)
    {
        // pointer arithmetic was specifically requested
        char tmp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = tmp;
    }
    printf("%s\n", s);
}

void work(char *s, void transposer(char *str))
{
    transposer(s);
}

int main()
{
    char *buffer = malloc(256 * sizeof(char));
    read(STDIN_FILENO, buffer, 256);
    int n = strnlen(buffer, 256);
    // remove newline to prevent weird stuff
    buffer[n - 1] = 0x00;
    void (*transposePtr)(char *) = transposeExample;
    work(buffer, transposePtr);
    free(buffer);
    return 0;
}