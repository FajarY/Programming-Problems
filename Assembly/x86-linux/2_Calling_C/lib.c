#include <stdio.h>

int add_number(int left, int right)
{
    return left + right;
}
void print_number(int number)
{
    printf("%i", number);
}
void print_something(const char* ptr)
{
    printf("%s", ptr);
}
void print_endl()
{
    printf("\n");
}
void flush()
{
    fflush(stdout);
}