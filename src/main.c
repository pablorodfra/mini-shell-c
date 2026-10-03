#include <stdio.h>
#include <string.h>
#include "parsing.h"
#include "parsing.c"

int main(void)
{
    char line[1024];

    while (1)
    {
        printf("myshell>");
        fflush(stdout);
        if(fgets(line, sizeof(line), stdin) == NULL)
        {
            printf("\n");
            break;
        }

        line[strcspn(line, "\n")] = 0;

        if(strcmp(line, "exit") == 0)
        {
            printf("Bye...");
            break;
        }
        else if(strcmp(line, "hello") == 0)
        {
            printf("Good morning\n");
        }
        else if(strcmp(line, "ls") == 0)
        {
            parsing(line);
        }
        else if(line[0] != '\0')
        {
            printf("Command \"%s\" not found\n", line);
        }
    }
    return 0;
}