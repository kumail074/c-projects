#include <stdio.h>
#include <stdlib.h>
//#include <sys/mem.h>
#include <string.h>
//#include <sys/type.h>

enum token{
    tok_eof = -1,

    tok_def = -2,
    tok_extern = -3,

    tok_identifier = -4,
    tok_number = -5
};

static char *identifierStr[];
static double numVal;

static int gettok(){
    static int lastChar = ' ';

    while(isspace(lastChar))
        lastChar = getchar();

    if(isalpha(lastChar)){
        identifierStr = lastChar;
        while(isalnum((lastChar = getchar())))
            identifierStr += lastChar;

        if(identifierStr == "def")
            return tok_def;
        if(identifierStr == "extern")
            return tok_extern;

        return tok_identifier;
    }

    if(isdigit(lastChar) || lastChar == '.'){
        char numStr[];

        do{
            numStr += lastChar;
            lastChar = getchar();
        } while(isdigit(lastChar) || lastChar == '.');

        numVal = strtod(numStr, 0);
        return tok_number;
    }

    if(lastChar == '#'){
        do
            lastChar = getchar();
        while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

        if(lastChar != EOF)
            return gettok();
    }

    if(lastChar == EOF)
        return tok_eof;

    int thisChar = lastChar;
    lastChar = getchar();
    return thisChar;
}
