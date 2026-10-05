#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
TODO:
    - Hacer mas eficiente la reserva de memoria, no reservar el espacio de una linea entera
    - Probar que el resultado funciona con: "", "ls", "ls -l" y " ls -l -a "
*/

int parsing(const char *line)
{
    command_t command = {0};
    size_t len = strlen(line);

    //! Este metodo es muy ineficiente pq reserva el espacio de la linea entera
    command.name = calloc(len+1, sizeof(char *));
    command.arguments = calloc(len, sizeof(char *));
    
    int is_command = 1;
    int index_argument = 0;

    // Para verificar si habia una palabra antes de añadir un argumento
    int word = 0;

    for(int i = 0; line[i] != '\0'; i++)
    {
        if(line[i] != ' ' && is_command == 0)
        {
            //! Este metodo es muy ineficiente pq reserva el espacio de la linea entera
            if(!word) command.arguments[command.num_arguments] = calloc(len+1, sizeof(char *));

            command.arguments[command.num_arguments][index_argument] = line[i];
            index_argument++;
            word = 1;
        }
        else if(line[i] == ' ' && word && is_command == 0)
        {
            command.arguments[command.num_arguments][index_argument+1] = '\0';
            command.num_arguments++;
            index_argument = 0;
            word = 0;
        }

        if(line[i] != ' ' && is_command == 1)
        {
            command.name[index_argument] = line[i];
            index_argument++;
            word = 1;
        }
        else if(line[i] == ' ' && word && is_command == 1)
        {
            command.name[i] = '\0';
            is_command = 0;
            index_argument = 0;
            word = 0;
        }
    }

    if(word && !is_command) {
        command.num_arguments++;
    }

    printf("El nombre del comando es: %s \n", command.name);
    printf("El primer argumento es: %s \n", command.arguments[0]);
    printf("El segundo argumento es: %s \n", command.arguments[1]);
    printf("El numero de argumentos es: %d \n", command.num_arguments);

    //! De momento uso esto para poder probar la logica, no se si es eficiente
    for (int i = 0; i < command.num_arguments; i++)
    {
        free(command.arguments[i]);
    }
    free(command.arguments);
    free(command.name);

    return 1;
}