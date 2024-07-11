#include "main.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void)
{
    print_welcome();

    InputBuffer* ib = new_input_buffer();

    // enter REPL
    while (true) {
        print_prompt();
        read_input(ib);

        // process META commands
        if (ib->buffer[0] == '.') {
            switch (do_meta_command(ib)) {
            case (META_COMMAND_SUCCESS):
                continue;
            case (META_COMMAND_UNRECOGNIZED_COMMAND):
                printf("Unrecognized command: '%s'.\n", ib->buffer);
                continue;
            }
        }

        // generate Statement from SQL command
        Statement statement;
        switch (prepare_statement(ib, &statement)) {
        case (PREPARE_SUCCESS):
            break;
        case (PREPARE_UNRECOGNIZED_STATEMENT):
            printf("Unrecognized keyword at the start of '%s'.\n", ib->buffer);
            continue;
        }

        // execute SQL command
        execute_statement(&statement);
        printf("Statement executed.\n");
    }
}

// Print welcome message to stdout
void print_welcome(void)
{
    // Get the current time
    time_t now = time(NULL);
    struct tm* t = localtime(&now);

    // Print the output in the desired format
    printf("SQLite clone version %s %04d-%02d-%02d %02d:%02d:%02d\n",
        VERSION,
        t->tm_year + 1900,
        t->tm_mon + 1,
        t->tm_mday,
        t->tm_hour,
        t->tm_min,
        t->tm_sec);

    printf("Enter \".help\" for usage hints.\n");
    printf("Enter \".exit\" to quit.\n");
}

// Print prompt string to stdout
void print_prompt(void)
{
    printf("sqlite-clone> ");
}

// Read input from stdin into InputBuffer
void read_input(InputBuffer* ib)
{
    ssize_t nread = getline(&(ib->buffer), &(ib->buffer_length), stdin);

    if (nread <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // Ignore trailing newline
    ib->buffer[nread - 1] = '\0';
    ib->input_length = nread - 1;
}

// Create new input buffer
InputBuffer* new_input_buffer(void)
{
    InputBuffer* ib = malloc(sizeof(InputBuffer));

    if (ib == NULL) {
        printf("Could not allocate memory for input buffer\n");
        exit(1);
    }

    ib->buffer = NULL;
    ib->buffer_length = 0;
    ib->input_length = 0;

    return ib;
}

// Remove input buffer from memory
void close_input_buffer(InputBuffer* ib)
{
    if (ib->buffer != NULL) {
        free(ib->buffer);
    }

    free(ib);
}

// Perform meta command action if valid command
int do_meta_command(InputBuffer* ib)
{

    if (strcmp(ib->buffer, ".exit") == 0) {
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

// Parse SQL statement
int prepare_statement(InputBuffer* ib, Statement* s)
{
    if (strncmp(ib->buffer, "insert", 6) == 0) {
        s->type = STATEMENT_INSERT;
        return PREPARE_UNRECOGNIZED_STATEMENT;
    }
    if (strncmp(ib->buffer, "select", 6) == 0) {
        s->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

// Execute parsed SQL statement
void execute_statement(Statement* s)
{
    switch (s->type) {
    case STATEMENT_INSERT:
        printf("This is where we would insert.\n");
        break;
    case STATEMENT_SELECT:
        printf("This is where we would select.\n");
        break;
    }
}
