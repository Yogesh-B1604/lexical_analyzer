#ifndef LEXER_H
#define LEXER_H

#define MAX_KEYWORDS 21
#define MAX_TOKEN_SIZE 100

typedef enum {
    KEYWORD,
    OPERATOR,
    SPECIAL_CHARACTER,
    CONSTANT,
    IDENTIFIER,
    UNKNOWN
} TokenType;

typedef struct {
    char lexeme[MAX_TOKEN_SIZE];
    TokenType type;
} Token;

typedef struct
{
    FILE *source_file;
    int current_char;
    int line_number;
    int next_char;
    char cur_word[100];
} LexerState;

typedef struct
{
    int keywords;
    int identifiers;
    int numbers;
    int string_literals;
    int char_literals;
    int operators;
    int special_symbols;
    int header_files;
    int preprocessors;
    int comments;
    int unknown_char;
    int total_tokens;
} TokenSummary;

extern TokenSummary summary;
void initializeLexer(char* filename);
void advance(LexerState *lexer);
void peek(LexerState *lexer);

#endif
