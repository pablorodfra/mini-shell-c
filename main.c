#include <stdio.h>
#include <string.h>

void main() {
    int exit = 0;
    char comando[1024];
    int a = strcmp(comando, "ext");
    while (exit == 0) {
        printf("myshell>");
        fflush(stdout);
        fgets(comando, sizeof(comando), stdin);
        comando[strcspn(comando, "\n")] = 0;

        if(strcmp(comando, "exit") == 0) {
            exit++;
            printf("Adios...");
        } else if(strcmp(comando, "hola") == 0) {
            printf("%s", "Hola buenos dias\n");
        }
    }
}