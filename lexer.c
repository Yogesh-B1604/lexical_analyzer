#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#define COMMENT_INDENT "                                "

static LexerState lexer;
TokenSummary summary = {0};
static const char* keywords[MAX_KEYWORDS] = {
    "int", "float", "return", "if", "else", "while", "for", "do", "break", "continue",
    "char", "double", "void", "switch", "case", "default", "const", "static", "sizeof", "struct" , "enum"
};

static const char* operators = "+-*/%=!<>|&~^?";
static const char* specialCharacters = ",;{}()[]:.";
static const char* valid_two_operators[19] = {"==", "!=", "<=", ">=", "++", "--", "+=", "-=", "*=", "/=", "%=","&&", "||", "<<", ">>", "&=", "|=", "^=","->"};

void initializeLexer(char* filename){
    if(strstr(filename,".c") == NULL){
        printf("ERROR : Please give .c file as Input!\n");
        return ;
    }
    lexer.source_file = fopen(filename,"r");
    if(lexer.source_file == NULL){
        printf("ERROR : Unable to open file!\n");
        return ;
    }
    lexer.line_number = 1;
    lexer.current_char = '\0';
    advance(&lexer);
    while (lexer.current_char != EOF)
    {
        if (lexer.current_char == ' ' || lexer.current_char == '\t' || lexer.current_char == '\n' || lexer.current_char == '\r') // 1. Whitespace
            advance(&lexer);

        else if (isalpha(lexer.current_char) || lexer.current_char == '_')// 2. Identifier / Keyword 
            {
                int i = 0;  /* First character */
                lexer.cur_word[i++] = lexer.current_char;
                advance(&lexer);

                while (isalpha(lexer.current_char) || isdigit(lexer.current_char) || lexer.current_char == '_' ) // Remaining characters
                {
                    lexer.cur_word[i++] = lexer.current_char;
                    advance(&lexer);
                }
                lexer.cur_word[i] = '\0';
                
                int keyword_index = 0, keyword_flag = 0;
                while (keyword_index < MAX_KEYWORDS)// Check keyword 
                {
                    if (strcmp(keywords[keyword_index], lexer.cur_word) == 0)
                    {
                        keyword_flag = 1;
                        break;
                    }
                    keyword_index++;
                }
                if (keyword_flag)
                {
                    printf("[LINE %-3d] %-18s : %s\n", lexer.line_number,"KEYWORD",lexer.cur_word);
                    summary.keywords++;
                }
                else{
                    printf("[LINE %-3d] %-18s : %s\n", lexer.line_number,"IDENTIFIER",lexer.cur_word);
                    summary.identifiers++;
                }
            }
        else if (isdigit(lexer.current_char)) // 3. Number
            {
                int int_index = 0;
                //int data_type = 0;
                while(isdigit(lexer.current_char) || lexer.current_char == '.'){
                    peek(&lexer);
                    if(lexer.current_char == '0' && (lexer.next_char == 'x' || lexer.next_char == 'X') ){
                        while(lexer.current_char != ' ' && lexer.current_char != '\t' && lexer.current_char != '\n' && lexer.current_char != '\r' && lexer.current_char != ';' && lexer.current_char != EOF){
                            lexer.cur_word[int_index++] = lexer.current_char;
                            advance(&lexer); 
                        }
                        break;
                    }
                    lexer.cur_word[int_index++] = lexer.current_char;
                    advance(&lexer); 
                }
                lexer.cur_word[int_index] = '\0';
                if(strchr(lexer.cur_word,'.') != NULL)
                    printf("[LINE %-3d] %-18s : %s\n", lexer.line_number,"FLOAT NUMBER" , lexer.cur_word);
                else if (strchr(lexer.cur_word,'x') != NULL || strchr(lexer.cur_word,'X') != NULL )
                    printf("[LINE %-3d] %-18s : %s\n", lexer.line_number,"HEXA NUMBER", lexer.cur_word);
                else
                    printf("[LINE %-3d] %-18s : %s\n", lexer.line_number,"INT NUMBER", lexer.cur_word);
                summary.numbers++;    
            }
        else if (lexer.current_char == '/') // 4. Single and multiline comment
        {
            peek(&lexer);
            int cmt_index = 0;
            if(lexer.next_char == '/'){
                while(lexer.current_char != '\n' && lexer.current_char != EOF){
                    lexer.cur_word[cmt_index++] = lexer.current_char; 
                    advance(&lexer);
                }
                lexer.cur_word[cmt_index] = '\0';
                printf("[LINE %-3d] %-18s : %s\n",lexer.line_number,"SINGLE COMMENT",lexer.cur_word);
                summary.comments++;

            }
            else if (lexer.next_char == '*'){
                printf("[LINE %-3d] %-18s : ", lexer.line_number, "MULTILINE COMMENT");
                while(lexer.current_char != EOF){
                    lexer.cur_word[cmt_index++] = lexer.current_char; 
                    if(lexer.current_char == '*'){
                        peek(&lexer);
                        if (lexer.next_char == '/')
                        {
                            advance(&lexer);
                            lexer.cur_word[cmt_index++] = lexer.current_char;
                            advance(&lexer);
                            break;
                        }
                    }
                    advance(&lexer);
                }
                lexer.cur_word[cmt_index] = '\0';
                for(int i = 0; lexer.cur_word[i] != '\0'; i++)
                {
                    putchar(lexer.cur_word[i]);

                    if(lexer.cur_word[i] == '\n' && lexer.cur_word[i + 1] != '\0')
                        printf("%s", COMMENT_INDENT);
                }
                printf("\n");
                summary.comments++;
            }
            else{
                lexer.cur_word[0] = lexer.current_char;
                lexer.cur_word[1] = lexer.next_char;
                lexer.cur_word[2] = '\0';
                int i = 0, found = 0;
                while (i < 19)
                {
                    if (strcmp(valid_two_operators[i], lexer.cur_word) == 0)
                    {
                        printf("[LINE %-3d] %-18s : %s\n", lexer.line_number,"OPERATOR", lexer.cur_word);
                        summary.operators++;
                        advance(&lexer);
                        advance(&lexer);
                        found = 1;
                        break;
                    }
                    i++;
                }
                if (found == 0)
                {
                    printf("[LINE %-3d] %-18s : %c\n", lexer.line_number,"OPERATOR",lexer.current_char);
                    summary.operators++;
                    advance(&lexer);
                }
            }
        }
        else if(lexer.current_char == '#') // 5.Preprocessor
        {
            int index = 0;
            while(lexer.current_char != '\n' && lexer.current_char != EOF){
                lexer.cur_word[index++] = lexer.current_char;
                advance(&lexer);
            }
            lexer.cur_word[index] = '\0';
            if(strstr(lexer.cur_word,".h") != NULL){
                printf("[LINE %-3d] %-18s : %s\n",lexer.line_number,"HEADER FILE",lexer.cur_word);
                summary.header_files++;
            }

            else{
                printf("[LINE %-3d] %-18s : %s\n",lexer.line_number,"PREPROCESSOR",lexer.cur_word);
                summary.preprocessors++;
            }
        } 
        else if(strchr(operators,lexer.current_char) != NULL) // 6.Operator
            {   peek(&lexer);
                lexer.cur_word[0] = lexer.current_char;
                lexer.cur_word[1] = lexer.next_char;
                lexer.cur_word[2] = '\0';
                int i = 0, found = 0;
                while (i < 19)
                {
                    if (strcmp(valid_two_operators[i], lexer.cur_word) == 0)
                    {
                        printf("[LINE %-3d] %-18s : %s\n", lexer.line_number,"OPERATOR", lexer.cur_word);
                        summary.operators++;
                        advance(&lexer);
                        advance(&lexer);
                        found = 1;
                        break;
                    }
                    i++;
                }
                if (found == 0)
                {
                    printf("[LINE %-3d] %-18s : %c\n", lexer.line_number,"OPERATOR", lexer.current_char);
                    summary.operators++;
                    advance(&lexer);
                }
            }
        else if(strchr(specialCharacters,lexer.current_char) != NULL)// 7. Special character
            {
                        printf("[LINE %-3d] %-18s : %c\n", lexer.line_number,"SPECIAL SYMBOL", lexer.current_char);
                        summary.special_symbols++;
                        advance(&lexer);
            }
        else if(lexer.current_char == '"')// 8.String Literals
        {
                int str_index = 0;
                lexer.cur_word[str_index++] = lexer.current_char;
                advance(&lexer); 
                while(lexer.current_char != '"' && lexer.current_char != EOF){
                    if (lexer.current_char == '\\')
                    {
                        lexer.cur_word[str_index++] = lexer.current_char;
                        advance(&lexer);
                        if(lexer.current_char != EOF)
                        {
                            lexer.cur_word[str_index++] = lexer.current_char;
                            advance(&lexer);
                        }
                        continue;
                    }
                    lexer.cur_word[str_index++] = lexer.current_char; 
                    advance(&lexer);
                }
                if(lexer.current_char == '"'){
                    lexer.cur_word[str_index++] = lexer.current_char;
                    lexer.cur_word[str_index] = '\0';
                    printf("[LINE %-3d] %-18s : %s\n", lexer.line_number,"STRING", lexer.cur_word);
                    summary.string_literals++;
                    advance(&lexer); 
                }        
        }   
        else if(lexer.current_char == '\'')// 9.character Literals
        {
                int char_index = 0;
                lexer.cur_word[char_index++] = lexer.current_char;
                advance(&lexer);
                while(lexer.current_char != '\'' && lexer.current_char != EOF)
                {
                    if (lexer.current_char == '\\')
                    {
                        lexer.cur_word[char_index++] = lexer.current_char;
                        advance(&lexer);
                        if(lexer.current_char != EOF)
                        {
                            lexer.cur_word[char_index++] = lexer.current_char;
                            advance(&lexer);
                        }
                        continue;
                    }
                    lexer.cur_word[char_index++] = lexer.current_char; 
                    advance(&lexer);
                }
                if(lexer.current_char == '\'')
                {
                    lexer.cur_word[char_index++] = lexer.current_char; 
                    lexer.cur_word[char_index] = '\0';
                    printf("[LINE %-3d] %-18s : %s\n", lexer.line_number,"CHARACTER", lexer.cur_word);
                    summary.char_literals++;
                    advance(&lexer); 
                }        
        }
        else  // 10.Unknown Character.
            {
                printf("[LINE %-3d] %-18s : %c , ASCII = %d\n", lexer.line_number,"UNKNOWN CHARACTER", lexer.current_char, lexer.current_char);
                summary.unknown_char++;
                advance(&lexer);
            }
        
    }   
    fclose(lexer.source_file);
}
void advance(LexerState *lexer){
    if(lexer->current_char == '\n')
                lexer->line_number++;
    lexer->current_char = fgetc(lexer->source_file);
    return;
}
void peek(LexerState *lexer){
    lexer->next_char = fgetc(lexer->source_file);
    fseek(lexer->source_file,-1,SEEK_CUR);
}