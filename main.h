#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

// <--- Constants --->

#define MAX_INPUT 1024
#define VERSION "0.0.1"

// <--- Custom data types --->
// Data structure for user input
typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;

} InputBuffer;

// Defines do_meta_command output values
typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

// Defines prepare_statement output values
typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

// Defines statement types
typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

// Represents a parsed and prepared SQL statement
typedef struct {
    StatementType type;
} Statement;

// <-- Function prototypes -->
void print_welcome(void);
void print_prompt(void);
void read_input(InputBuffer*);
InputBuffer* new_input_buffer(void);
void close_input_buffer(InputBuffer*);
int do_meta_command(InputBuffer*);
int prepare_statement(InputBuffer*, Statement*);
void execute_statement(Statement *);

#endif /* MAIN_H */
