#ifndef PARSING_H
#define PARSING_H

typedef struct
{
    char *name;
    char **arguments;
    int num_arguments;
} command_t;

int parsing(const char *line);

#endif /* PARSING_H */