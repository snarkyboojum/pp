/*
 * A brain-dead scanner
 */

#import <stdio.h>
#import <stdlib.h>

#define MAX_TOKEN_LENGTH 128
#define MAX_TOKEN_NUM 1024

int scan(char *file);

typedef enum token_type {
    type       = 0,
    ident      = 1,
    value      = 2,
    operator   = 3,
    terminator = 4,
    unknown    = 99,
} token_type;

typedef struct token {
    int start_pos;
    int end_pos;
    char data[MAX_TOKEN_LENGTH];
    token_type type;
} token;


char SEPARATOR = ' ';
char NEWLINE   = '\n';


int is_space (char c) {
    if (c == SEPARATOR || c == NEWLINE) {
        return 1;
    }
    else {
        return 0;
    }
}

int
scan(char* file) {
    int file_pos    = 0;
    int token_count = 0;
    int token_pos   = 0;

    char c;
    char last_seen;

    token *t;
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

    while ((c = getc(fh)) != EOF) {

        printf("%c", c);

        if ( ! is_space(c) ) {
            // start of a token
            if ( is_space(last_seen) || file_pos == 0) {
                token_pos = 0;
                t = (token*) malloc(sizeof(token));
                t->start_pos = file_pos;
            }
            // middle of a token
            t->data[token_pos] = c;
            token_pos++;
        }
        // end of a token
        else if (is_space(c) && (! is_space(last_seen) && file_pos !=0)) {
            t->end_pos = file_pos;
            tokens[token_count] = t;
            token_count++;
        }

        last_seen = c;
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
main(int argc, char **argv) {

    int retcode = 0;

    if (argv[1] == NULL) {
        printf("Need a source file\n");
    }
    else {
        retcode = scan(argv[1]);
    }

    return retcode;
}
