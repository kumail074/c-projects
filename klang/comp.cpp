#include <iostream>

using namespace std;

enum token {
    tok_eof = -1,

    tok_def = -2,
    tok_extern = -3,

    tok_identifier = -4,
    tok_number = -5,
};

static string IdentifierStd;
static double NumVal;
