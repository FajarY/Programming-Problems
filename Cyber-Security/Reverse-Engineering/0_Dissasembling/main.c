#include <stdio.h>
#include <string.h>

int main()
{
    const char* password = "This is a vurnerable password!";
    char buffer[100] = {0};

    while (strcmp(password, buffer) != 0)
    {
        memset(buffer, 0, 100);
        fgets(buffer, 100, stdin);
        int len = strlen(buffer);
        buffer[len - 1] = 0;
    }
    
    printf("You're In!");

    return 0;
}