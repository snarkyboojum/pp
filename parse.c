/*
 * A brain-dead parser
 */

#import <stdio.h>
#import <stdlib.h>
#import "parse.h"
#import "tokenise.h"
#import "ast.h"


void
show_tokens(token **tokens, int token_count)
{
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
}

void
pretty_print_ast(ast *tree) {
    printf("AST:\n");
}


int
parse(char *file)
{
    token *tokens[MAX_TOKEN_NUM];
    ast *syntax_tree;

    int token_count = tokenise(file, tokens);
    if (tokens == NULL) {
        fprintf(stderr, "Couldn't read file: %s\n", file);
        return -1;
    }

    show_tokens(tokens, token_count);

    build_ast(tokens, syntax_tree);
    if (syntax_tree == NULL) {
        fprintf(stderr, "Couldn't parse file: %s\n", file);
        return -1;
    }

    pretty_print_ast(syntax_tree);

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
        retcode = parse(argv[1]);
    }

    return retcode;
}
