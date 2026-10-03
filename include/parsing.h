#ifndef PARSE_H
#define PARSE_H

typedef struct
{
    char *name;
    char **arguments;
    int num_arguments;
} command_t;

int parsing(const char *line);

#endif /* PARSE_H */