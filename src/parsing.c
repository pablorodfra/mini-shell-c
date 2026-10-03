#include "parsing.h"
#include <stdio.h>

int parsing(const char *line)
{
    command_t command = {0};

    for(int i = 0; line[i] != '\0'; i++)
    {
        int is_command = 1;
        int index_argument = 0;

        if(line[i] != ' ' && is_command == 1)
        {
            command.name[i] = line[i];
        }
        else
        {
            is_command = 0;
        }

        if(line[i] != ' ' && is_command == 0)
        {
            command.arguments[command.num_arguments][index_argument] = line[i];
            index_argument++;
        }
        else
        {
            command.arguments[command.num_arguments][index_argument+1] = '\0';
            command.num_arguments++;
            index_argument = 0;
        }
    }
    printf("El nombre del comando es: %s", command.name, '\n');
    printf("El primer argumento es: %s", command.arguments[0], '\n');
    printf("El segundo argumento es: %s", command.arguments[1], '\n');
    printf("El numero de argumentos es: %d", command.num_arguments, '\n');

    return 1;
}