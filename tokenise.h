#import <stdio.h>
#import <stdlib.h>

#define MAX_TOKEN_LENGTH 128
#define MAX_TOKEN_NUM 1024

typedef enum token_type
{
    type       = 0,
    ident      = 1,
    value      = 2,
    operator   = 3,
    terminator = 4,
    unknown    = 99,
} token_type;

typedef struct token
{
    int start_pos;
    int end_pos;
    char data[MAX_TOKEN_LENGTH];
    token_type type;
} token;

int tokenise(char *file, token **tokens);
int is_whitespace(char c);
int is_terminator(char c);
int is_delimiter(char c);

