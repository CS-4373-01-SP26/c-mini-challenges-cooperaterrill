#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
const int N = 256;
void transposeExample(char *s)
{
    printf("%s\n", s);
    int len = strnlen(s, N);
    for (int i = 0; i < len / 2; i++)
    {
        // pointer arithmetic was specifically requested
        // and pointer arithmetic ye shall receive
        char tmp = (s + i * sizeof(char))[0];
        (s + i * sizeof(char))[0] = (s + (len - 1 - i) * sizeof(char))[0];
        (s + (len - 1 - i) * sizeof(char))[0] = tmp;
    }
    printf("%s\n", s);
}

void work(char *s, void transposer(char *str))
{
    transposer(s);
}

int main()
{
    char *buffer = malloc(N * sizeof(char));
    read(STDIN_FILENO, buffer, N);
    int n = strnlen(buffer, N);
    // remove newline to prevent weird stuff
    buffer[n - 1] = 0x00;
    void (*transposePtr)(char *) = transposeExample;
    work(buffer, transposePtr);
    free(buffer);
    return 0;
}