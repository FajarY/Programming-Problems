#include <stdio.h>

void flush()
{
    fflush(stdout);

    return;
}
void get_string(char* buffer)
{
    scanf("%s", buffer);
}
void print_number(int number)
{
    printf("%i", number);
    flush();

    return;
}
void print_string(const char* ptr)
{
    printf("%s", ptr);
    flush();

    return;
}
void print_endl()
{
    printf("\n");
    flush();

    return;
}
