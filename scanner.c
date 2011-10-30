/*
 * A brain-dead scanner
 */

#import <stdio.h>
#import <stdlib.h>

#define MAX_TOKEN_LENGTH 128
#define MAX_TOKEN_NUM 1024

int scan(char *file);
int is_whitespace(char c);
int is_terminator(char c);
int is_delimiter(char c);

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


int
is_whitespace(char c)
{
    if (c == ' ' || c == '\n')
        return 1;
    else
        return 0;
}

int
is_terminator(char c)
{
    if (c == ';')
        return 1;
    else
        return 0;
}

int
is_delimiter(char c)
{
    if (is_whitespace(c) || c == '!' || c == '<' || c == '>' || c == ';' || c == '=' || c == '{' || c == '}' || c == '(' || c == ')' || c == '&' || c == '|' || c == EOF)
        return 1;
    else
        return 0;
}

int
is_double_delimiter(char c, char nc)
{
    if ((c == '<' || c == '>' || c == '!' || c == '=') && nc == '=')
        return 1;
    else if (c == '&' && nc == '&')
        return 1;
    else if (c == '|' && nc == '|')
        return 1;
    else
        return 0;
}

int
scan(char* file)
{
    int file_pos    = 0;
    int token_count = 0;
    int token_pos   = 0;

    char c;
    token *t = NULL;
    token *tokens[MAX_TOKEN_NUM];
    FILE *fh;

    fh = fopen(file, "r");

    if (fh == NULL) {
        printf("Couldn't find file: %s\n", file);
        return -1;
    }
    else {
        printf("Scanning file: %s\n", file);
    }


    while ((c = getc(fh))) {

        if (c != EOF)
            printf("%c", c);

        // we're outside a token
        if (is_delimiter(c)) {

            // we're fallen off the end of a token
            if (t != NULL) {
                t->end_pos = file_pos;
                tokens[token_count] = t;
                token_count++;
                t = NULL;
            }

            // build a token for the delimiter
            if (! is_whitespace(c) && c != EOF) {
                token_pos = 0;
                t = (token*) malloc(sizeof(token));

                t->data[token_pos] = c;
                t->start_pos = file_pos;

                // peek ahead
                char nc = getc(fh);

                if (is_double_delimiter(c, nc))
                    t->data[++token_pos] = nc;
                else
                    ungetc(nc, fh);

                t->end_pos = file_pos + (token_pos + 1);

                tokens[token_count] = t;
                token_count++;
                t = NULL;
            }
            else {
                if (c == EOF)
                    break;
                // we skip whitespace
            }
        }
        // we're in a token
        else {
            // this is a new token
            if (t == NULL) {
                t = (token*) malloc(sizeof(token));
                t->start_pos = file_pos;
                token_pos = 0;
            }
            // slurp char up
            t->data[token_pos] = c;
            token_pos++;
        }

        file_pos++;
    }

    fclose(fh);

    printf("Number of tokens found: %d\n", token_count);

    int i;
    for (i = 0; i < token_count; i++) {
        token *t = tokens[i];
        printf("[%d]: ", i);

        int token_length = t->end_pos - t->start_pos;
        printf("%d: ", token_length);

        int j;
        for (j = 0; j <= token_length; j++) {
            printf("%c", t->data[j]);
        }
        printf("\n");
    }

    return 0;
}

int
main(int argc, char **argv)
{
    int retcode = 0;

    if (argv[1] == NULL) {
        printf("Need a source file\n");
    }
    else {
        retcode = scan(argv[1]);
    }

    return retcode;
}
