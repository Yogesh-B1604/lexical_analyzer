#include <stdio.h>
#include "lexer.h"
int main(int argc, char *argv[]) {
    if (argc < 2){
        printf("ERROR : Please give the input file with .c extention\n");
        return 0;
    }
    printf("----------------------------------------------------------------------------------------------\n");
    printf("                                        LEXICAL ANALYSER                                       \n ");
    printf("                                  Analyzing file : %s \n",argv[1]);
    printf("----------------------------------------------------------------------------------------------\n");

    initializeLexer(argv[1]); //Token Details

    summary.total_tokens = (summary.keywords +summary.identifiers + summary.numbers + summary.string_literals + summary.char_literals +summary.operators
                            + summary.special_symbols + summary.header_files + summary.preprocessors + summary.comments + summary.unknown_char);
    printf("----------------------------------------------------------------------------------------------\n");
    printf("                                        TOKEN SUMMARY\n");
    printf("----------------------------------------------------------------------------------------------\n");

    printf("%-25s : %d\n", "KEYWORDS", summary.keywords);
    printf("%-25s : %d\n", "IDENTIFIERS", summary.identifiers);
    printf("%-25s : %d\n", "NUMBERS", summary.numbers);
    printf("%-25s : %d\n", "STRING LITERALS", summary.string_literals);
    printf("%-25s : %d\n", "CHAR LITERALS", summary.char_literals);
    printf("%-25s : %d\n", "OPERATORS", summary.operators);
    printf("%-25s : %d\n", "SPECIAL SYMBOLS", summary.special_symbols);
    printf("%-25s : %d\n", "HEADER FILES", summary.header_files);
    printf("%-25s : %d\n", "PREPROCESSORS", summary.preprocessors);
    printf("%-25s : %d\n", "COMMENTS", summary.comments);

    printf("----------------------------------------------------------------------------------------------\n");
    printf("%-25s : %d\n", "TOTAL TOKENS", summary.total_tokens);
    printf("----------------------------------------------------------------------------------------------\n");
    return 0;  
}
